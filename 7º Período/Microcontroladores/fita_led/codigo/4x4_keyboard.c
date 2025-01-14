// Define pin references
#define LINHA0 PIN_B7
#define LINHA1 PIN_B6
#define LINHA2 PIN_B5
#define LINHA3 PIN_B4
#define COLUN0 PIN_B3
#define COLUN1 PIN_B2
#define COLUN2 PIN_B1
#define COLUN3 PIN_B0

// 4x4 keyboard matrix
uint8_t linhas[4] = {LINHA0, LINHA1, LINHA2, LINHA3};
uint8_t colunas[4] = {COLUN0, COLUN1, COLUN2, COLUN3};

// 4x4 keyboard map
char input_array[4][4] = {{'1','2','3','A'},{'4','5','6','B'},{'7','8','9','C',},{'*','0','#','D'}};

// Cursor position is controled mannually 
uint8_t pos_cursor = 0;

// Color being edited: 0 => red; 1 => green; 2 => blue
uint8_t color_selected = 0;

// import the whole math.h uses many resources. Prefered to only implement ipow
int ipow(uint16_t base, uint16_t exp)
{
    uint16_t result = 1;
    for (;;)
    {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        if (!exp)
            break;
        base *= base;
    }

    return result;
}


// write the current color on display
void write_color(uint16_t color) {
   pos_cursor = 0;
   setCursor(cursor_map[color_selected], 1);
   printlong(color);  
   setCursor(cursor_map[color_selected], 1);
   rgb_buffer[color_selected] = rgb_map[color_selected];
}

// show error mesage (when color > 255)
void showErr() {
   rgb_buffer[color_selected] = rgb_map[color_selected];
   
   setCursor(cursor_map[color_selected], 1);
   char error_msg[4] = "ERR";
   printstr(error_msg);
   
   setCursor(cursor_map[color_selected], 1);
   delay_ms(500);

   write_color(rgb_map[color_selected]);
}


// deal with user input
void user_input(uint16_t digited) {
   // convert from ascii to int
   digited = digited - 48;
 
   // if *
   if (digited == 65530) {
      if (rgb_map[color_selected] > 0) {
         // decrease
         write_color(--rgb_map[color_selected]);
         delay_ms(40);
      }       
   }
   
   // if #
   else if (digited == 65523) {
       if (rgb_map[color_selected] < 255) {
         // increase
         write_color(++rgb_map[color_selected]);
         delay_ms(40);
      }       
   }
   
   // if A -> C
   else if (digited >= 17 && digited <=19) {
      if(rgb_buffer[color_selected] <= 255) {
         rgb_map[color_selected] = rgb_buffer[color_selected];
         // go to digited -17 (color 0, 1 or 2)
         color_selected = (digited-17);
         setCursor(cursor_map[color_selected], 1);
      } else {
         showErr();   
      }
   }
   
   // if D
   else if (digited == 20) {
      // clean everybody
      for (color_selected = 0; color_selected < 3; color_selected++) {
         rgb_buffer[color_selected] = rgb_map[color_selected] = 0;
         write_color(rgb_map[color_selected]);
      }
      
      delay_ms(100);
      
      // go to color 0
      color_selected = 0;
      setCursor(cursor_map[color_selected], 1);
   }
   
   // if 0-9, should type
   else {
      printint(digited);
      
      // reset buffer if is char 0
      if (pos_cursor==0) rgb_buffer[color_selected] = 0;
      
      // decimal multiplier
      rgb_buffer[color_selected] += digited*ipow(10, 2-pos_cursor++);
      
      // if is the 3rd char, go to next color
      if (pos_cursor > 2) {
         if(rgb_buffer[color_selected] <= 255) {
            pos_cursor = 0;
            rgb_map[color_selected] = rgb_buffer[color_selected];
            color_selected = (++color_selected%3);
            setCursor(cursor_map[color_selected], 1);
         } else {
            showErr();
         }
      } 
      
      delay_ms(200); 
   }
}

// scan 4x4 keyboard ports
void scanPorts() {
   for (int linha = 0; linha <= 3; linha++) {
      output_low(linhas[linha]);
      
      for (int coluna = 0; coluna <= 3; coluna++) {
         // if pressed, deal with the input
         if (!input(colunas[coluna])) {
            user_input(input_array[linha][coluna]);
         }
      }
      
      output_high(linhas[linha]);
   }
}


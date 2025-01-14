// flags for control
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00


// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

// flags for backlight control
#define LCD_BACKLIGHT 0x08
#define LCD_NOBACKLIGHT 0x00

// function flags
#define En 0b00000100  // Enable bit
#define Rw 0b00000010  // Read/Write bit

uint8_t _address;
uint8_t _backlightVal = LCD_BACKLIGHT;
uint8_t _displayControl;
uint8_t _displayFunction;
uint8_t _displayMode;
uint8_t _rows;
uint8_t _columns;

// sends code to pcf8574 so it redirects to the display
void expanderWrite(uint8_t _data) {
   I2C_Start();
   I2C_Write(_address);
   // Always write the backlight val
   I2C_Write((int)(_data) | _backlightval);
   I2C_stop();
}


// Pulse enable to write command
void pulseEnable(uint8_t _data) {
   expanderWrite(_data | En);
   delay_us(1);
   
   expanderWrite(_data & ~En);
   delay_us(50);
}

// Send 4 bits to expander, than pulse enable
void write4bits(uint8_t value) {
   expanderWrite(value);
   pulseEnable(value);
}

// Send 8 bits dividing in two nibbles
void send(uint8_t value, uint8_t mode) {
   uint8_t MSB = value & 0b11110000;
   uint8_t LSB = (value << 4) & 0b11110000;
   write4bits((MSB)|mode);
   write4bits((LSB)|mode);
}

// Command uses RS = 0
void command(uint8_t value) {
   send(value, 0b00000000);
}

// Write uses RS = 1
int write(uint8_t value) {
   send(value, 0b00000001);
   return 1;
}

// Change display configurations
void display() {
   _displayControl |= LCD_DISPLAYON;
   command(LCD_DISPLAYCONTROL | _displayControl);
}

// Clear display
void clear() {
   command(LCD_CLEARDISPLAY);
   delay_us(2000);
}

// Put cursor home
void home() {
   command(LCD_RETURNHOME);
   delay_us(2000);
}

// Put cursor on specified column/row
// PS: Rows and Columns start with 0
void setCursor(uint8_t col, uint8_t row){
   int row_offsets[] = { 0x00, 0x40 };
   row = (row%_rows);    
   command(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}


// Write an array of chars
void printstr(char *c[]) {
   int i = 0;
   while (c[i]) {
      write(c[i]);
      i++;
   }
}

// print single int
void printint(uint16_t d) {
    char c[16];
    sprintf(c, "%lu", d);
    printstr(c);
}

// print long in form 00X -> XXX
void printlong(uint16_t d) {
    char c[16];
    sprintf(c, "%03lu", d);
    printstr(c);
}

// Automatic display configuration
void initializeLCD(uint8_t address, uint8_t columns, uint8_t rows) {
   _address = address;
   _columns = columns;
   _rows = rows;
   
   _displayFunction = LCD_4BITMODE | LCD_2LINE | LCD_5x8DOTS;
   delay_ms(500);
   expanderWrite(_backlightval);
   delay_ms(1000);
   
   write4bits(0x03 << 4);
   delay_us(4500);
   
   write4bits(0x03 << 4);
   delay_us(4500);
   
   write4bits(0x03 << 4);
   delay_us(1500);
   
   write4bits(0x02 << 4);
   
   command(LCD_FUNCTIONSET | _displayFunction);
   
   _displaycontrol = LCD_DISPLAYON | LCD_CURSORON | LCD_BLINKON;
   
   display();
   
   clear();
   
   _displayMode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
   
   command(LCD_ENTRYMODESET | _displayMode);
   
   home();
}



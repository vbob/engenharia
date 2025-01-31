#include "../Bibliotecas/iQueue.h"
#include <stdlib.h>

#define TAMANHO 20

// Codigo de cores:
// G -> VERDE B -> AZUL R -> VERMELHO

void imprimirMatriz(char matriz[][TAMANHO]);
void colorirMatriz(int XOriginal, int YOriginal, iQueue *X, iQueue *Y, char matriz[][TAMANHO], char novaCor);
int main() {
	iQueue X, Y;
	init(&X);
	init(&Y);

	char matriz[TAMANHO][TAMANHO];


	// PREENCHE A MATRIZ
	for (int i = 0; i < TAMANHO; i++) {
		for (int j = 0; j < TAMANHO; j++) {
			if (j%2 == 1 || j < 5)		
				matriz[i][j] = '*';
			else
				matriz[i][j] = '#';
			if (j == 9)		
				matriz[i][j] = '#';
			if (j > 17)		
				matriz[i][j] = '#';
			if (i == 19)		
				matriz[i][j] = '*';
			if (i == 0)		
				matriz[i][j] = '#';
			if (i == 8)		
				matriz[i][j] = '#';
		}
	
	}
	
	printf("MATRIZ ORIGINAL\n\n");
	imprimirMatriz(matriz);
	
	printf("\n\nMATRIZ COLORIDA\n\n");	
	colorirMatriz(9, 1, &X, &Y, matriz, '%'); 

	imprimirMatriz(matriz);

}

void imprimirMatriz(char matriz[][TAMANHO]) {
	for (int i = 0; i < TAMANHO; i++) {
		for (int j = 0; j< TAMANHO; j++)
			printf("%c ", matriz[j][i]);
		printf("\n");
	}
}

void colorirMatriz(int XOriginal, int YOriginal, iQueue *X, iQueue *Y, char matriz[][TAMANHO], char novaCor) {
	enqueue(X, XOriginal);
	enqueue(Y, YOriginal);
	
	char corOriginal = matriz[peek(X)][peek(Y)];

	while (!isEmpty(X)) {

		if(matriz[peek(X)+1][peek(Y)] == corOriginal) {
			enqueue(X, peek(X)+1);
			enqueue(Y, peek(Y));	
		}

		if(matriz[peek(X)-1][peek(Y)] == corOriginal) {
			enqueue(X, peek(X)-1);
			enqueue(Y, peek(Y));	
		}

		if(matriz[peek(X)][peek(Y)+1] == corOriginal) {
			enqueue(X, peek(X));
			enqueue(Y, peek(Y)+1);	
		}

		if(matriz[peek(X)][peek(Y)-1] == corOriginal) {
			enqueue(X, peek(X));
			enqueue(Y, peek(Y)-1);	
		}

		matriz[dequeue(X)][dequeue(Y)] = novaCor; 	
	}
}


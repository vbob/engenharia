#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cStack.h"

int main() {
	char palavraOriginal[6] = "ARARA\0";
	char palavraModificada[6];
	cStack pilha;
	init(&pilha);

	for (int i = 0; i < 5; i++)
		push(&pilha, palavraOriginal[i]);

	for (int i = 0; i < 5; i++)
		palavraModificada[i] = pop(&pilha);

	printf("%s",(strcmp(palavraOriginal, palavraModificada)==0)?"Palíndroma!\n":"Não é palíndroma!\n");

	return EXIT_SUCCESS;
}


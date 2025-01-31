//Biblioteca sStack.h de VITOR BRUNO DE OLIVEIRA BARTH

#ifndef SSTACK_H
#define SSTACK_H

#define SIZE 10

#include <string.h>
#include <stdio.h>

// STRUCT DECLARATION 
typedef struct sStack {
	char values[SIZE][100]; // Duas dimensões, pois string é um vetor de chars
	int top;	 
} sStack;

// SUBROUTINE DECLARATION
void sInit(sStack *stack); // Coloca o topo = -1
void sPush(sStack *stack, char *element); // Se não cheia, salva o elemento em values[topo++]
char* sPop(sStack *stack); // Se não vazia, decrementa o topo e retorna values[topo+1]
char* sTop(sStack *stack); // Retorna values[topo]
int sIsEmpty(sStack *stack); // Retorna true se topo == -1
int sIsFull(sStack *stack); // Retorna true se topo == SIZE-1
int sSize(sStack *stack); // Retorna SIZE
int sCapacity(sStack *stack); // Retorna SIZE-(topo+1)
void sShow(sStack *stack); // Enquanto não vazia, imprime o pop

// SUBROUTINE CODE
void sInit(sStack *stack) {
	stack->top = -1;
}

void sPush(sStack *stack, char *element) {
	if(!sIsFull(stack)) {
		stack->top++;
		strcpy(stack->values[stack->top], element);
	}
	else
		printf("ERROR! CAN'T PUSH, STACK IS FULL");
}

char* sPop(sStack *stack) {
	if(!sIsEmpty(stack)) {
		stack->top--;
		return stack->values[stack->top+1];
	}
	else {
		printf("ERROR! CAN'T POP, STACK IS EMPTY");
		return "-1";
	}
}

char* sTop(sStack *stack) {
	if(!sIsEmpty(stack))
		return stack->values[stack->top];
	else {
		printf("ERROR! CAN'T SHOW TOP, STACK IS EMPTY");
		return "-1";
	}
}

int sIsEmpty(sStack *stack) {
	return stack->top == -1;
}

int sIsFull(sStack *stack) {
	return stack->top == SIZE-1;
}

int sSize(sStack *stack) {
	return SIZE;
}

int sCapacity(sStack *stack) {
	return SIZE-(stack->top+1);
}

void sShow(sStack *stack) {
	while (!sIsEmpty(stack))
		printf(" %s \n", sPop(stack));
}

#endif

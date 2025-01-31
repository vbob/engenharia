#include "../Bibliotecas/iQueue.h"
#include <stdlib.h>
#define TEMPOEXECUCAO 200
#define TEMPOTOTAL 3000

#define NUCLEOS 3

void zerar(int *vetor) {
	for ( int i = 0; i < NUCLEOS; i++)
		vetor[i] = 0;
}

int main() {
	int tempo, processoAtual[NUCLEOS], tempoPrevisto, tempoOcioso[NUCLEOS], tempoEstimadoReal =0, teste2 = 0;
	zerar(processoAtual); zerar(tempoOcioso);
	iQueue processos;
	init(&processos);
	enqueue(&processos, 232);
	enqueue(&processos, 111);
	enqueue(&processos, 222);
	enqueue(&processos, 428);
	enqueue(&processos, 303);
	enqueue(&processos, 282);
	enqueue(&processos, 586);
	enqueue(&processos, 294);
	enqueue(&processos, 513);
	enqueue(&processos, 771);
	enqueue(&processos, 248);
	enqueue(&processos, 691);
	enqueue(&processos, 523);

	for (tempo = 0; !isEmpty(&processos) || ((tempo%TEMPOEXECUCAO !=0) && tempo>0); tempo++) {
		/*if (tempo%3 == 0 && tempo < TEMPOTOTAL)
			enqueue(&processos, (int) 200 + rand() % 1000);*/
		
		if ((tempo-1)%TEMPOEXECUCAO == 0) {
			for (int i = 0; i < NUCLEOS; i++) {
				if (tempo>0 && processoAtual[i] != 0) enqueue(&processos, processoAtual[i]);
				if (!isEmpty(&processos)) processoAtual[i] = dequeue(&processos);
			}
		}
	
		/*for (int i = 0; i < NUCLEOS; i++)
			printf("\n%d TEMPO DO PROCESSO ATUAL: %d NUCLEO: %d", tempo, processoAtual[i], i);*/

		for (int i = 0; i < NUCLEOS; i++) {
			if(processoAtual[i] != 0)
				processoAtual[i]--;
	
			if(processoAtual[i] == 0 && tempo%TEMPOEXECUCAO!=0)
				tempoOcioso[i]++;
		}
		
		if (tempo%TEMPOEXECUCAO == 0) {
			tempoPrevisto = 0;
			tempoEstimadoReal = 0;
			for(int i = 0; i < size(&processos); i++) {
				tempoPrevisto += peek(&processos);
				enqueue(&processos, dequeue(&processos));
				tempoEstimadoReal += (((int) peek(&processos) / 200) + 1) * 200;
			}

			printf("\n\nTEMPO ESTIMADO RESTANTE SEM PREEMPCAO: %d", (int) tempoPrevisto/NUCLEOS);
			printf("\nTEMPO ESTIMADO REAL %d", (int) tempoEstimadoReal/NUCLEOS);
		}
	}

	printf("\n\n\nTEMPO TOTAL GASTO: %d", tempo);
	for (int i = 0; i < NUCLEOS; i++)
		printf("\nTEMPO TOTAL OCIOSO NUCLEO %d : %d\n\n", i, tempoOcioso[i]);

	return 0;
}

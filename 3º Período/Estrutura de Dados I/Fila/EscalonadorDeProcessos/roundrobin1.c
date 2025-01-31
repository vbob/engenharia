#include "../Bibliotecas/iQueue.h"
#include <stdlib.h>
#define TEMPOEXECUCAO 200
#define TEMPOTOTAL 3000

#define NUCLEOS 2

int main() {
	int tempo, processoAtual = 1, tempoPrevisto, tempoOcioso = 0, teste1 =0, teste2 = 0;
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
			if(tempo>0 && processoAtual != 0) enqueue(&processos, processoAtual);
			processoAtual = dequeue(&processos);
		}


		//printf("\n%d TEMPO DO PROCESSO ATUAL: %d", tempo, processoAtual);

		
		//printf("\nTEMPO PROCESSO ATUAL: %d", processoAtual);	
		if(processoAtual != 0)
			processoAtual--;
	
		if(processoAtual == 0 && tempo%TEMPOEXECUCAO!=0)
			tempoOcioso++;

		if (tempo%TEMPOEXECUCAO == 0) {
			tempoPrevisto = 0;
			teste1 = 0;
			for(int i = 0; i < size(&processos); i++) {
				tempoPrevisto += peek(&processos);
				enqueue(&processos, dequeue(&processos));
				teste1 += (((int) peek(&processos) / 200) + 1) * 200;
			}

			printf("\n\nTEMPO ESTIMADO RESTANTE SEM PREEMPCAO: %d", tempoPrevisto);
			printf("\nTEMPO ESTIMADO REAL %d", teste1);
			/* printf("\nTEMPO TOTAL GASTO: %d", tempo);
			printf("\nTEMPO TOTAL OCIOSO: %d", tempoOcioso); */
		}
	}

	printf("\n\n\nTEMPO TOTAL GASTO: %d", tempo);
	printf("\nTEMPO TOTAL OCIOSO: %d\n\n", tempoOcioso);

	return 0;
}

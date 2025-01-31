#include "../Bibliotecas/iQueue.h"

int main() {
	iQueue queue;
	init(&queue);

	dequeue(&queue);

	for(int i = 0; i < 11; i++)
		enqueue(&queue, i);

	dequeue(&queue);
	dequeue(&queue);
	dequeue(&queue);

	printf("%i \n", peek(&queue));

	enqueue(&queue, 12);
	enqueue(&queue, 1997);
	show(&queue);

	return 0;
}


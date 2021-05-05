#include <stdio.h>

#define MAX_QUEUE_SIZE 5

typedef int element;
typedef struct {
	element data[MAX_QUEUE_SIZE];
	element front;
	element rear;
}QueueType;

void init(QueueType* q) {
	q->front = 0;
	q->rear = 0;
}

int is_empty(QueueType* q) {
	return (q->rear == q->front);
}

int is_full(QueueType* q) {
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void enqueue(QueueType *q, element data) {
	if (!is_full(q)) {
		q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
		q->data[q->rear] = data;
	}
}

element dequeue(QueueType* q) {
	if (!is_empty(q)) {
		q->front = (q->front + 1) % MAX_QUEUE_SIZE;
		return (q->data[q->front]);
	}
}

// ��ȯ�ϰ� ���� �Ǻ���ġ ������ ���� ��°(th)�� �Ű������� �Է� 
element fibonacchi(QueueType* q, int th) {
	int result, delete;
	if (th == 1)
		return(0);
	else if (th == 2)
		return(1);
	else {
		enqueue(q, 0);
		enqueue(q, 1);
		for (int i = 0; i < th-2; i++) {
			delete = dequeue(q);
			result = q->data[q->rear] + delete;
			enqueue(q, result);
		}
	}
	return(result);
}

int main(void) {
	QueueType q;
	int th;
	init(&q);
	printf("�Ǻ���ġ ������ ���° ���� ��ȯ�ұ��?");
	scanf("%d", &th);

	printf("�Ǻ���ġ ������ %d��° �� : %d",th, fibonacchi(&q, th));

	return(0);
}

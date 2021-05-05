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

// 반환하고 싶은 피보나치 수열의 수의 번째(th)를 매개변수로 입력 
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
	printf("피보나치 수열의 몇번째 수를 반환할까요?");
	scanf("%d", &th);

	printf("피보나치 수열의 %d번째 수 : %d",th, fibonacchi(&q, th));

	return(0);
}

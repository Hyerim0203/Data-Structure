#include <stdio.h>
#include <stdlib.h>

// ===== ����ť �ڵ� =====
#define MAX_QUEUE_SIZE 5
typedef int element;
typedef struct { // ť Ÿ��
	element data[MAX_QUEUE_SIZE];
	int front, rear;
} QueueType;

// ���� �Լ�
void error(char* message)
{
	fprintf(stderr, "%sn", message);
	exit(1);
}

// ť �ʱ�ȭ(����) �Լ�
void init_queue(QueueType* q)
{
	q->front = q->rear = 0; // ���� ť������ 0���� ����
}

// ���� ���� ���� �Լ�
int is_empty(QueueType* q)
{
	return (q->front == q->rear);
}

// ��ȭ ���� ���� �Լ�
int is_full(QueueType* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// ����ť ��� �Լ�
void display(QueueType* q)
{
	printf("QUEUE(front=%d, rear=%d) = ", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % MAX_QUEUE_SIZE;
			printf("%d | ", q->data[i]);
			if (i == q->rear)
				break;
		} while (i != q->front); // �ѹ��� ���� ���� ����
	}
	printf("\n");
}

// ���� �Լ�
void enqueue(QueueType* q, element item)
{
	if (is_full(q)) 
		error("ť�� ��ȭ�����Դϴ�");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

// ���� �Լ�
element dequeue(QueueType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

// �� �տ� �ִ� ����(���� ���� ������ ����) ���
element peek(QueueType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	return (q->data[(q->front + 1) % MAX_QUEUE_SIZE]);
}

// === ���� ===
int main(void) {
	QueueType q1;
	QueueType q2;

	init_queue(&q1);
	init_queue(&q2);
	// 1.
	printf("-----------------1.------------------\n");
	enqueue(&q1, 3);
	enqueue(&q1, 4);
	enqueue(&q1, 5);
	display(&q1);
	dequeue(&q1); display(&q1);
	dequeue(&q1); display(&q1);
	dequeue(&q1); display(&q1);
	printf("\n");
	// 2.
	printf("-----------------2.--------------------");
	for (int i = 0; i < 100; i++) {
		if (i % 4 == 0) printf("\n");
		printf("[%d�� iteration] - ", i+1);
		enqueue(&q2, 103);
		enqueue(&q2, 1);
		dequeue(&q2);
		dequeue(&q2);
		printf("front : %d, rear : %d ", q2.front, q2.rear);
		
	}

}
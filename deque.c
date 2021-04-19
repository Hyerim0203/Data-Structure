#include <stdio.h>
#include <stdlib.h>

// ===== ������ �ڵ� =====
#define MAX_DEQUE_SIZE 5
typedef int element;
typedef struct {
	element data[MAX_DEQUE_SIZE];
	int front, rear;
} DequeType;

// ���� �Լ�
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// �ʱ�ȭ
void init_deque(DequeType* q)
{
	q->front = q -> rear = 0;
}

// ���� ���� ���� �Լ�
int is_empty(DequeType* q)
{
	return (q->rear == q->front);
}

// ��ȭ ���� ���� �Լ�
int is_full(DequeType* q)
{
	return (q->front == ((q->rear + 1) % MAX_DEQUE_SIZE));
}

// �� ��� �Լ�
void display(DequeType* q)
{
	printf("DEQUE(front=%d, rear=%d) = ", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i+1)%MAX_DEQUE_SIZE;
			printf("%d | ", q->data[i]);
			if (i == q->rear) break;
		} while (q->front != i);
	}
	printf("\n");
}
// �� ���� �Լ�
void add_front(DequeType* q, element item)
{
	if (is_full(q))
		error("���� ��ȭ�����Դϴ�");
	q -> data[q->front] = item;
	q->front = (q->front - 1 + MAX_DEQUE_SIZE) % MAX_DEQUE_SIZE;
}

// �� ���� �Լ�
void add_rear(DequeType* q, element item)
{
	if (is_full(q))
		error("���� ��ȭ�����Դϴ�");
	q->rear = (q->rear + 1) % MAX_DEQUE_SIZE;
	q->data[q->rear] = item;
}

// �� ���� �Լ�
element delete_front(DequeType* q)
{
	if (is_empty(q))
		error("���� ��������Դϴ�");
	q->front = (q->front + 1) % MAX_DEQUE_SIZE;
	return (q->data[q->front]);
}

// �� ���� �Լ�
element delete_rear(DequeType* q)
{
	if (is_empty(q))
		error("���� ��������Դϴ�.");
	element temp = q->data[q->rear];
	q->rear = (q->rear - 1 + MAX_DEQUE_SIZE) % MAX_DEQUE_SIZE;
	return (temp);
}

// front�� �ִ� �� ��ȯ
element get_front(DequeType* q)
{
	if (is_empty(q))
		error("���� ��������Դϴ�.");
	return (q -> data[(q->rear + 1) % MAX_DEQUE_SIZE]);
}

// rear�� �ִ� �� ��ȯ
element get_rear(DequeType* q)
{
	if (is_empty(q))
		error("���� ��������Դϴ�.");
	return (q->data[q->rear]);
}

// ===== ���� =====
int main(void)
{
	DequeType d;

	init_deque(&d);

	add_front(&d, 1);
	add_front(&d, 2);
	add_front(&d, 3);
	display(&d);
	delete_rear(&d);
	display(&d);
	delete_rear(&d);
}

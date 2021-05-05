#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 100

typedef int element;
typedef struct {
	element data[MAX_QUEUE_SIZE];
	int top;
}StackType;

void init(StackType* s) {
	s->top = -1;
}

int is_empty(StackType*s) {
	return (s->top == -1);
}

int is_full(StackType* s) {
	return (s->top == MAX_QUEUE_SIZE - 1);
}

void push(StackType* s, element data) {
	if (!is_full(s))
		s->data[++(s->top)] = data;
}

element pop(StackType* s) {
	if (!is_empty(s))
		return (s->data[(s->top)--]);
}

element peek(StackType* s) {
	if (!is_empty(s))
		return (s->data[s->top]);
}

void display(StackType* s) {
	if (!is_empty(s)) {
		for (int i = 0; i < s->top+1; i++)
			printf("%d -> ", s->data[i]);
	}
	printf("\n");
}

typedef struct {
	StackType* s1; // �Է��� �޴� ����
	StackType* s2; // ����� �ϴ� ����
}QueueType;

void init_queue(QueueType* q) {
	// ���� �Ҵ�
	q->s1 = (StackType*)malloc(sizeof(StackType));
	q->s2 = (StackType*)malloc(sizeof(StackType));
	// �ʱ�ȭ
	init(q->s1);
	init(q->s2); 
}

void enqueue(QueueType* q, element data) {
	if (!is_full(q->s1))
		push(q->s1, data);
}

element dequeue(QueueType* q) {
	if (is_empty(q->s2)) {
		for (int i = q->s1->top; i >= 0; i--)
			push(q->s2, pop(q->s1));
	}
	return (q->s2->data[(q->s2->top)--]);
}

void queue_display(QueueType* q) {
	printf("stack1 : ");
	display(q->s1);
	printf("stack2 : ");
	display(q->s2);
}

int main(void) {
	QueueType q;
	element input;
	init_queue(&q);

	printf("queue�� ���� ���Ҹ� �Է��ϼ��� : ");
	scanf("%d", &input);
	enqueue(&q, input);
	queue_display(&q);
	printf("queue�� ���� ���Ҹ� �Է��ϼ��� : ");
	scanf("%d", &input);
	enqueue(&q, input);
	queue_display(&q);

	printf("queue�� ���� ���Ҹ� �Է��ϼ��� : ");
	scanf("%d", &input);
	enqueue(&q, input);
	queue_display(&q);

	dequeue(&q);
	queue_display(&q);
	dequeue(&q);
	queue_display(&q);
	
	return(0);
}
#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct{
	element* data; // data�� �����ͷ� ����
	int capacity;  // ����ũ��
	int top;	  
} StackType;

// ���� ���� �Լ�
void init_stack(StackType* s)
{
	s->top = -1;
	s->capacity = 1;
	s->data = (element*)malloc(s->capacity * sizeof(element)); // ����ũ�⸸ŭ �迭�� �����س���
}

// ���� ���� ���� �Լ�
int is_empty(StackType*s)
{
	return (s->top == -1);
}

// ��ȭ ���� ���� �Լ�
int is_full(StackType* s)
{
	return (s->top == (s->capacity - 1));
}

// ���ο� �� �ֱ�
void push(StackType* s, element item)
{
	if (is_full(s)) {
		s->capacity *= 2; // �迭�� ũ�⸦ 2��� �ø���
		s->data =
			(element*)realloc(s->data, s->capacity * sizeof(element)); // �Ҵ��ϰ� �����ϰ� �ٿ��ֱ�
	}
	s->data[++(s->top)] = item; // top�� ũ�⸦ 1�ø� �� ���� ����
}

// �����Լ�
element pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1); // ���������ϴµ� ������ �߻��ߴٴ� ���� ���� 
		// return�� �޹����� �����ϸ鼭 �����ϴ� �ݸ� exit�� �ٷ� ����
	}
	else return s->data[(s->top)--]; // top�� ���� ������ ��, top�� ���� �Ѱ� ����
}

int main(void) {
	StackType s;
	init_stack(&s); // �ּҸ� ���ڷ� �־���
	push(&s, 1);
	push(&s, 2);
	push(&s, 3);
	printf("%d\n", pop(&s));
	printf("%d\n", pop(&s));
	free(s.data);
	return 0;
}


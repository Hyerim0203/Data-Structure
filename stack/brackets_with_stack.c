#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100

typedef int element;

// ���� ����ü ����
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
}StackType;

// ���� �ʱ�ȭ
void initialize(StackType*s) {
	s->top = -1; // -1�� �ʱ�ȭ
}

// ���� á���� Ȯ��
int is_full(StackType* s) {
	return (s->top == (MAX_STACK_SIZE - 1));
}

// ������� Ȯ��
int is_empty(StackType* s) {
	return (s->top == -1);
}

// ���� ����
void push(StackType* s, element data) {
	if (!is_full(s)) {
		s->data[++(s->top)] = data;
	}
}

// ���� ����
element pop(StackType* s) {
	if (!is_empty(s))
		return (s->data[(s->top)--]);
}

// �� ������ ���� ��ȯ
element peek(StackType* s) {
	if (!is_empty(s))
		return (s->data[s->top]);
}

void matching(StackType*s, char *data) {
	int i;
	int idx = 0;
	for (i = 0; i < strlen(data); i++)
	{	
		if ('(' == data[i]) {
			push(s, ++idx);
			printf("%d ", peek(s));
		}
		else if (')' == data[i])
			printf("%d ", pop(s));
	}
}

int main(void) {
	StackType stack1;
	char* brackets[MAX_STACK_SIZE];
	printf("���� : ");
	scanf("%s", brackets);
	initialize(&stack1);
	printf("��ȣ �� : ");
	matching(&stack1, brackets);

	return(0);
}
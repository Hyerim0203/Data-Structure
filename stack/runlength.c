#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100

typedef char element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
}StackType;

void initialize(StackType* s) {
	s->top = -1;
}

int is_empty(StackType* s) {
	return (s->top == -1);
}

int is_full(StackType* s) {
	return (s->top == MAX_STACK_SIZE - 1);
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

void run_length(char*data) {
	int i;
	int str_len = strlen(data);
	element input;
	StackType stack;
	initialize(&stack);

	for (i = 0; i < str_len; i++) {
		input = data[i]; // stack�� ���� ���ڿ�
		if (('A' <= data[i]) && ((data[i]) <= 'Z'))
			input = input + 32; // �ҹ��ڷ� ��ȯ
		
		if (is_empty(&stack))
			push(&stack, input);

		else if (peek(&stack)!= input) {
			printf("%d%c", (stack.top) + 1, peek(&stack)); // ��� 
			initialize(&stack); // ���� �ʱ�ȭ
			push(&stack, input);
		}
		else
			push(&stack, input); // stack�� ���ڿ� �Է�
	}
	printf("%d%c", (stack.top) + 1, peek(&stack)); // ���ÿ� ���� �� ���
}

int main(void) {
	char data[MAX_STACK_SIZE];
	
	printf("���ڿ��� �Է��Ͻÿ� : ");
	scanf("%s", data);
	printf("����� ���ڿ� : ");
	run_length(data);

	return(0);
}

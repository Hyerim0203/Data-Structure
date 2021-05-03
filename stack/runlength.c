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
		input = data[i]; // stack에 넣을 문자열
		if (('A' <= data[i]) && ((data[i]) <= 'Z'))
			input = input + 32; // 소문자로 변환
		
		if (is_empty(&stack))
			push(&stack, input);

		else if (peek(&stack)!= input) {
			printf("%d%c", (stack.top) + 1, peek(&stack)); // 출력 
			initialize(&stack); // 스택 초기화
			push(&stack, input);
		}
		else
			push(&stack, input); // stack에 문자열 입력
	}
	printf("%d%c", (stack.top) + 1, peek(&stack)); // 스택에 남은 것 출력
}

int main(void) {
	char data[MAX_STACK_SIZE];
	
	printf("문자열을 입력하시오 : ");
	scanf("%s", data);
	printf("압축된 문자열 : ");
	run_length(data);

	return(0);
}

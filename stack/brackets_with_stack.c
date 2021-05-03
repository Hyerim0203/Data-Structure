#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100

typedef int element;

// 스택 구조체 정의
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
}StackType;

// 스택 초기화
void initialize(StackType*s) {
	s->top = -1; // -1로 초기화
}

// 가득 찼는지 확인
int is_full(StackType* s) {
	return (s->top == (MAX_STACK_SIZE - 1));
}

// 비었는지 확인
int is_empty(StackType* s) {
	return (s->top == -1);
}

// 값을 삽입
void push(StackType* s, element data) {
	if (!is_full(s)) {
		s->data[++(s->top)] = data;
	}
}

// 값을 삭제
element pop(StackType* s) {
	if (!is_empty(s))
		return (s->data[(s->top)--]);
}

// 맨 마지막 값을 반환
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
	printf("수식 : ");
	scanf("%s", brackets);
	initialize(&stack1);
	printf("괄호 수 : ");
	matching(&stack1, brackets);

	return(0);
}
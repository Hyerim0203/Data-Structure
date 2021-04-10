#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct{
	element* data; // data를 포인터로 정의
	int capacity;  // 현재크기
	int top;	  
} StackType;

// 스택 생성 함수
void init_stack(StackType* s)
{
	s->top = -1;
	s->capacity = 1;
	s->data = (element*)malloc(s->capacity * sizeof(element)); // 현재크기만큼 배열을 생성해놓음
}

// 공백 상태 검출 함수
int is_empty(StackType*s)
{
	return (s->top == -1);
}

// 포화 상태 검출 함수
int is_full(StackType* s)
{
	return (s->top == (s->capacity - 1));
}

// 새로운 값 넣기
void push(StackType* s, element item)
{
	if (is_full(s)) {
		s->capacity *= 2; // 배열의 크기를 2배로 늘리기
		s->data =
			(element*)realloc(s->data, s->capacity * sizeof(element)); // 할당하고 복사하고 붙여넣기
	}
	s->data[++(s->top)] = item; // top의 크기를 1늘린 후 값을 참조
}

// 삭제함수
element pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1); // 강제종료하는데 에러가 발생했다는 것을 전함 
		// return은 뒷문장을 실행하면서 종료하는 반면 exit은 바로 종료
	}
	else return s->data[(s->top)--]; // top의 값을 참조한 후, top의 값을 한개 줄임
}

int main(void) {
	StackType s;
	init_stack(&s); // 주소를 인자로 넣어줌
	push(&s, 1);
	push(&s, 2);
	push(&s, 3);
	printf("%d\n", pop(&s));
	printf("%d\n", pop(&s));
	free(s.data);
	return 0;
}


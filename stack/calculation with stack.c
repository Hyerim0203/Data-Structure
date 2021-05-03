#include <stdio.h>
#include <stdlib.h>
#define CHAR_MAX_SIZE 1000

typedef char element;
typedef struct {
	element data[CHAR_MAX_SIZE]; // data를 포인터로 정의
	int top;
} StackType;

// 스택 생성 함수
void init_stack(StackType* s)
{
	s->top = -1;
}

// 공백 상태 검출 함수
int is_empty(StackType* s)
{
	return (s->top == -1);
}

// 포화 상태 검출 함수
int is_full(StackType* s)
{
	return (s->top == (CHAR_MAX_SIZE - 1));
}

// 새로운 값 넣기
void push(StackType* s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러");
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

// 피크함수
element peek(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러");
		exit(1);
	}
	else
		return s->data[s->top];
}

// 연산자의 우선순위를 반영하여야 한다.
int prec(char op)
{
	switch (op) {
	case '(': case ')': return 0; // 가장 낮은 우선순위
	case '+': case '-': case '%': return 1;
	case '*': case '/': return 2; // 가장 높은 우선순위
	}
	return -1;
}

// 중위 표기 수식 -> 후위 표기 수식
StackType infix_to_postfix(char exp[]) // 문자열을 받음
{
	int i, idx = 0;
	char ch, top_op;
	int len = strlen(exp);
	StackType p_s;
	StackType s;

	init_stack(&p_s); // 스택 초기화
	init_stack(&s); // 스택 초기화
	for (i = 0; i < len; i++)
	{
		ch = exp[i];
		switch (ch) { // 만약 연산자라면
		case '+': case '-': case '*': case '/': case '%':
			// 스택에 있는 연산자의 우선순위가 더 크거나 같으면 출력
			while (!is_empty(&s) && (prec(ch)) <= prec(peek(&s)))
			{	
				push(&p_s, pop(&s));
			}
			push(&s, ch); // 스택에 새로운 연산자 쌓음
			break;
		case '(': // 왼쪽 괄호
			push(&s, ch); // 무조건 스택에 삽입
			break;
		case ')': // 오른쪽 괄호
			top_op = pop(&s);
			// 왼쪽 괄호를 만날때까지 출력, 왼쪽 괄호도 삭제
			while (top_op != '(') {
				push(&p_s, top_op);
				top_op = pop(&s);
			}
			break;
		default: // 피연산자
			push(&p_s, ch);
			break;
		}
	}
	while (!is_empty(&s)) // 스택에 남은 연산자들 출력
		push(&p_s, pop(&s));
	p_s.data[(p_s.top)+1] = '\0';
	printf("%d", p_s.top);
	return p_s;
}

// 후위 표기 수식 계산 함수
int eval(StackType p_s)
{	
	int op1, op2, value, i = 0;
	int len = p_s.top+1;
	char* exp = p_s.data;
	char ch;
	StackType s;

	init_stack(&s); // stack 초기화
	for (i = 0; i < len; i++) {
		ch = exp[i];
		if (ch != '+' && ch != '-' && ch != '*' && ch != '/' && ch != '%') {
			// 해당 문자의 아스키코드를 진짜 숫자값의 아스키코드로 변경
			value = ch - '0';
			push(&s, value);
		}
		else {
			op2 = pop(&s);
			op1 = pop(&s);
			switch (ch) {
			case '+': push(&s, op2 + op1); break;
			case '-': push(&s, op1 - op2); break;
			case '*': push(&s, op1 * op2); break;
			case '/': push(&s, op1 / op2); break;
			case '%': push(&s, op1 % op2); break;
			}
		}
	}
	return pop(&s);
}
int main(void)
{
	char* s = "3*(4+5)";
	printf("입력 : %s \n", s);
	StackType p_s = infix_to_postfix(s);
	printf("후위표시수식 : %s\n", p_s.data);
	printf("계산결과 : %d", eval(p_s));
	return 0;
}



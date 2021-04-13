#include <stdio.h>
#include <stdlib.h>
#define CHAR_MAX_SIZE 1000

typedef char element;
typedef struct {
	element data[CHAR_MAX_SIZE]; // data�� �����ͷ� ����
	int top;
} StackType;

// ���� ���� �Լ�
void init_stack(StackType* s)
{
	s->top = -1;
}

// ���� ���� ���� �Լ�
int is_empty(StackType* s)
{
	return (s->top == -1);
}

// ��ȭ ���� ���� �Լ�
int is_full(StackType* s)
{
	return (s->top == (CHAR_MAX_SIZE - 1));
}

// ���ο� �� �ֱ�
void push(StackType* s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "���� ��ȭ ����");
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

// ��ũ�Լ�
element peek(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����");
		exit(1);
	}
	else
		return s->data[s->top];
}

// �������� �켱������ �ݿ��Ͽ��� �Ѵ�.
int prec(char op)
{
	switch (op) {
	case '(': case ')': return 0; // ���� ���� �켱����
	case '+': case '-': case '%': return 1;
	case '*': case '/': return 2; // ���� ���� �켱����
	}
	return -1;
}

// ���� ǥ�� ���� -> ���� ǥ�� ����
StackType infix_to_postfix(char exp[]) // ���ڿ��� ����
{
	int i, idx = 0;
	char ch, top_op;
	int len = strlen(exp);
	StackType p_s;
	StackType s;

	init_stack(&p_s); // ���� �ʱ�ȭ
	init_stack(&s); // ���� �ʱ�ȭ
	for (i = 0; i < len; i++)
	{
		ch = exp[i];
		switch (ch) { // ���� �����ڶ��
		case '+': case '-': case '*': case '/': case '%':
			// ���ÿ� �ִ� �������� �켱������ �� ũ�ų� ������ ���
			while (!is_empty(&s) && (prec(ch)) <= prec(peek(&s)))
			{	
				push(&p_s, pop(&s));
			}
			push(&s, ch); // ���ÿ� ���ο� ������ ����
			break;
		case '(': // ���� ��ȣ
			push(&s, ch); // ������ ���ÿ� ����
			break;
		case ')': // ������ ��ȣ
			top_op = pop(&s);
			// ���� ��ȣ�� ���������� ���, ���� ��ȣ�� ����
			while (top_op != '(') {
				push(&p_s, top_op);
				top_op = pop(&s);
			}
			break;
		default: // �ǿ�����
			push(&p_s, ch);
			break;
		}
	}
	while (!is_empty(&s)) // ���ÿ� ���� �����ڵ� ���
		push(&p_s, pop(&s));
	p_s.data[(p_s.top)+1] = '\0';
	printf("%d", p_s.top);
	return p_s;
}

// ���� ǥ�� ���� ��� �Լ�
int eval(StackType p_s)
{	
	int op1, op2, value, i = 0;
	int len = p_s.top+1;
	char* exp = p_s.data;
	char ch;
	StackType s;

	init_stack(&s); // stack �ʱ�ȭ
	for (i = 0; i < len; i++) {
		ch = exp[i];
		if (ch != '+' && ch != '-' && ch != '*' && ch != '/' && ch != '%') {
			// �ش� ������ �ƽ�Ű�ڵ带 ��¥ ���ڰ��� �ƽ�Ű�ڵ�� ����
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
	printf("�Է� : %s \n", s);
	StackType p_s = infix_to_postfix(s);
	printf("����ǥ�ü��� : %s\n", p_s.data);
	printf("����� : %d", eval(p_s));
	return 0;
}



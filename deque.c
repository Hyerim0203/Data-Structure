#include <stdio.h>
#include <stdlib.h>

// ===== 원형덱 코드 =====
#define MAX_DEQUE_SIZE 5
typedef int element;
typedef struct {
	element data[MAX_DEQUE_SIZE];
	int front, rear;
} DequeType;

// 오류 함수
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// 초기화
void init_deque(DequeType* q)
{
	q->front = q -> rear = 0;
}

// 공백 상태 검출 함수
int is_empty(DequeType* q)
{
	return (q->rear == q->front);
}

// 포화 상태 검출 함수
int is_full(DequeType* q)
{
	return (q->front == ((q->rear + 1) % MAX_DEQUE_SIZE));
}

// 덱 출력 함수
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
// 앞 삽입 함수
void add_front(DequeType* q, element item)
{
	if (is_full(q))
		error("덱이 포화상태입니다");
	q -> data[q->front] = item;
	q->front = (q->front - 1 + MAX_DEQUE_SIZE) % MAX_DEQUE_SIZE;
}

// 뒤 삽입 함수
void add_rear(DequeType* q, element item)
{
	if (is_full(q))
		error("덱이 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_DEQUE_SIZE;
	q->data[q->rear] = item;
}

// 앞 삭제 함수
element delete_front(DequeType* q)
{
	if (is_empty(q))
		error("덱이 공백상태입니다");
	q->front = (q->front + 1) % MAX_DEQUE_SIZE;
	return (q->data[q->front]);
}

// 뒷 삭제 함수
element delete_rear(DequeType* q)
{
	if (is_empty(q))
		error("덱이 공백상태입니다.");
	element temp = q->data[q->rear];
	q->rear = (q->rear - 1 + MAX_DEQUE_SIZE) % MAX_DEQUE_SIZE;
	return (temp);
}

// front에 있는 값 반환
element get_front(DequeType* q)
{
	if (is_empty(q))
		error("덱이 공백상태입니다.");
	return (q -> data[(q->rear + 1) % MAX_DEQUE_SIZE]);
}

// rear에 있는 값 반환
element get_rear(DequeType* q)
{
	if (is_empty(q))
		error("덱이 공백상태입니다.");
	return (q->data[q->rear]);
}

// ===== 실행 =====
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

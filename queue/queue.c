#include <stdio.h>
#include <stdlib.h>

// ===== 원형큐 코드 =====
#define MAX_QUEUE_SIZE 5
typedef int element;
typedef struct { // 큐 타입
	element data[MAX_QUEUE_SIZE];
	int front, rear;
} QueueType;

// 오류 함수
void error(char* message)
{
	fprintf(stderr, "%sn", message);
	exit(1);
}

// 큐 초기화(선언) 함수
void init_queue(QueueType* q)
{
	q->front = q->rear = 0; // 원형 큐에서는 0부터 시작
}

// 공백 상태 검출 함수
int is_empty(QueueType* q)
{
	return (q->front == q->rear);
}

// 포화 상태 검출 함수
int is_full(QueueType* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// 원형큐 출력 함수
void display(QueueType* q)
{
	printf("QUEUE(front=%d, rear=%d) = ", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % MAX_QUEUE_SIZE;
			printf("%d | ", q->data[i]);
			if (i == q->rear)
				break;
		} while (i != q->front); // 한바퀴 도는 것을 방지
	}
	printf("\n");
}

// 삽입 함수
void enqueue(QueueType* q, element item)
{
	if (is_full(q)) 
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

// 삭제 함수
element dequeue(QueueType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

// 맨 앞에 있는 원소(제일 먼저 삭제될 원소) 출력
element peek(QueueType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	return (q->data[(q->front + 1) % MAX_QUEUE_SIZE]);
}

// === 실행 ===
int main(void) {
	QueueType q1;
	QueueType q2;

	init_queue(&q1);
	init_queue(&q2);
	// 1.
	printf("-----------------1.------------------\n");
	enqueue(&q1, 3);
	enqueue(&q1, 4);
	enqueue(&q1, 5);
	display(&q1);
	dequeue(&q1); display(&q1);
	dequeue(&q1); display(&q1);
	dequeue(&q1); display(&q1);
	printf("\n");
	// 2.
	printf("-----------------2.--------------------");
	for (int i = 0; i < 100; i++) {
		if (i % 4 == 0) printf("\n");
		printf("[%d번 iteration] - ", i+1);
		enqueue(&q2, 103);
		enqueue(&q2, 1);
		dequeue(&q2);
		dequeue(&q2);
		printf("front : %d, rear : %d ", q2.front, q2.rear);
		
	}

}

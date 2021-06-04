#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50 // �ִ� ���� ����

// global ������ �������־�� ��ȯ�ϸ鼭 ��� ��� ����
int visited_dfs[MAX_VERTICES] = { 0 , };
int visited_bfs[MAX_VERTICES] = { 0, };

typedef struct {
	int n; // ������ ����
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
}GraphType;

// �׷��� �ʱ�ȭ
void init(GraphType* g) {
	int r, c;
	g->n = 0; // ��� ���� �ʱ�ȭ
	// ���� �ʱ�ȭ
	for (r = 0; r < MAX_VERTICES; r++)
		for (c = 0; c < MAX_VERTICES; c++)
			g->adj_mat[r][c] = 0;
}

// ���� ���� ����
void insert_vertex(GraphType* g) {
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "�׷���: ������ ���� �ʰ�");
		return;
	}
	g->n++;
}

// ���� ���� ����
void insert_edge(GraphType* g, int start, int end) {
	// �׷����� ��� ��ȣ�� 0���� ����(Ʈ���� ��� ��ȣ�� 1���� ����)
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
		return;
	}
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}

// ���� ��� ��� �Լ�
void print_adj_mat(GraphType* g) {
	for (int i = 0; i < g->n; i++) {
		for (int j = 0; j < g->n; j++) {
			printf("%2d ", g->adj_mat[i][j]);
		}
		printf("\n");
	}
}

void DFS_mat(GraphType* g, int node) {
	visited_dfs[node] = 1; // �湮 ǥ��
	printf("���� %d -> ", node);

	for (int i = 0; i < g->n; i++) {
		if (g->adj_mat[node][i] && !visited_dfs[i])
			DFS_mat(g, i);
	}
}

typedef struct {
	int data[MAX_VERTICES];
	int front, rear;
}QueueType;

void init_queue(QueueType* q) {
	q->front = q->rear = 0;
}

int is_empty(QueueType* q) {
	return(q->front == q->rear);
}

int is_full(QueueType* q) {
	return(q->front == (q->rear + 1) % MAX_VERTICES);
}

void enqueue(QueueType* q, int item) {
	if (is_full(q)) {
		fprintf(stderr, "ť ��ȭ����");
		return;
	}
	q->rear = (q->rear + 1) % MAX_VERTICES;
	q->data[q->rear] = item;
}

int dequeue(QueueType* q) {
	if (is_empty(q)) {
		fprintf(stderr, "ť �������");
		return 0;
	}
	q->front = (q->front + 1) % MAX_VERTICES;
	return q->data[q->front];
}

void BFS_mat(GraphType* g, int node) {
	QueueType q;
	init_queue(&q);
	enqueue(&q, node);
	visited_bfs[node] = 1;
	while (!is_empty(&q)) {
		node = dequeue(&q, node);
		printf("���� %d -> ", node);
		for (int i = 0; i < g->n; i++)
			if (g->adj_mat[node][i] && !visited_bfs[i]) {
				enqueue(&q, i);
				visited_bfs[i] = 1;
			}
	}
}

int main(void) {
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	init(g);
	// 5���� ��� ����
	for (int i = 0; i < 5; i++)
		insert_vertex(g);

	insert_edge(g, 0, 1);
	insert_edge(g, 0, 2);
	insert_edge(g, 0, 4);
	insert_edge(g, 1, 2);
	insert_edge(g, 2, 3);
	insert_edge(g, 2, 4);
	insert_edge(g, 3, 4);

	printf("----------------������� �̿�---------------\n");
	printf("[  DFS  ]\n");
	DFS_mat(g, 0);
	printf("\n");
	printf("[  BFS  ]\n");
	BFS_mat(g, 0);

	return 0;
}

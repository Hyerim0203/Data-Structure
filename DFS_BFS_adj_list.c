#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50

int visited_dfs_list[MAX_VERTICES] = { 0, };
int visited_bfs_list[MAX_VERTICES] = { 0, };

typedef struct {
	int vertex;
	struct GraphNode* link;
}GraphNode;

// 정점들의 집합을 저장해놓을 배열
typedef struct {
	int n; // 정점의 개수
	GraphNode* adj_list[MAX_VERTICES]; // 점점들의 배열
}GraphType_list;

// 그래프 초기화
void init_list(GraphType_list* g) {
	int v;
	g->n = 0;
	for (v = 0; v < MAX_VERTICES; v++)
		g->adj_list[v] = NULL;
}

// 정점 삽입 연산
void insert_vertex_list(GraphType_list* g) {
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "그래프 : 정점의 개수 초과");
		return;
	}
	g->n++;
}

// 간선 삽입 연산, v를 u의 인접 리스트에 삽입한다.
void insert_edge_list(GraphType_list* g, int u, int v) {
	if (u >= g->n || v >= g->n) {
		fprintf(stderr, "그래프 : 정점 번호 오류");
		return;
	}
	GraphNode* node = (GraphNode*)malloc(sizeof(GraphNode));
	node->vertex = v;
	// 연결 리스트의 맨 처음에 있던 노드와 이어줌
	node->link = g->adj_list[u];
	// u의 연결 리스트의 맨 처음에 삽입
	g->adj_list[u] = node;
}

void print_adj_list(GraphType_list* g) {
	for (int i = 0; i < MAX_VERTICES; i++) {
		GraphNode* p = g->adj_list[i];
		while (p != NULL) {
			printf("%2d", p->vertex);
			p = p->link;
		}
		printf("\n");
	}
}

void DFS_list(GraphType_list* g, int node) {
	GraphNode* t = g->adj_list[node];
	visited_dfs_list[node] = 1;
	printf("정점 %d -> ", node);
	while (t) {
		if (!visited_dfs_list[t->vertex])
			DFS_list(g, t->vertex);
		t = t->link;
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
		fprintf(stderr, "큐 포화상태\n");
		return;
	}
	q->rear = (q->rear + 1) % MAX_VERTICES;
	q->data[q->rear] = item;
}

int dequeue(QueueType* q) {
	if (is_empty(q)) {
		fprintf(stderr, "큐 공백상태\n");
		return 0;
	}
	q->front = (q->front + 1) % MAX_VERTICES;
	return q->data[q->front];
}

void BFS_list(GraphType_list* g, int node) {
	QueueType q;
	init_queue(&q);

	enqueue(&q, node);
	visited_bfs_list[node] = 1;

	while (!is_empty(&q)) {
		node = dequeue(&q);
		printf("정점 %d -> ", node);
		for (GraphNode* t = g->adj_list[node]; t; t = t->link) {
			if (!visited_bfs_list[t->vertex]) {
				enqueue(&q, t->vertex);
				visited_bfs_list[t->vertex] = 1;
			}
		}
	}
}

int main(void) {
	GraphType_list* g = (GraphType_list*)malloc(sizeof(GraphType_list));
	init_list(g);

	for (int i = 0; i < 5; i++)
		insert_vertex_list(g);

	// 인접 리스트는 edge를 양방향 모두로 지정해주어야 함
	insert_edge_list(g, 0, 1);
	insert_edge_list(g, 1, 0);
	insert_edge_list(g, 0, 2);
	insert_edge_list(g, 2, 0);
	insert_edge_list(g, 0, 4);
	insert_edge_list(g, 4, 0);
	insert_edge_list(g, 1, 2);
	insert_edge_list(g, 2, 1);
	insert_edge_list(g, 2, 3);
	insert_edge_list(g, 3, 2);
	insert_edge_list(g, 2, 4);
	insert_edge_list(g, 4, 2);
	insert_edge_list(g, 3, 4);
	insert_edge_list(g, 4, 3);

	printf("----------------인접리스트 이용---------------\n");
	printf("[  DFS  ]\n");
	DFS_list(g, 0);
	printf("\n");
	printf("[  BFS  ]\n");
	BFS_list(g, 0);


	return 0;
}
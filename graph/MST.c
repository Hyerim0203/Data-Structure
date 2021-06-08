// 신장트리
// 모든 정점들이 연결되어 있어야 하고, 사이클을 포함하지 않는
// 최소 간선 개수로 모든 정점들을 포함하는 트리
// 즉 n개의 노드가 있다면 n-1개의 간선을 가짐
// MST는 네트워크에 있는 모든 정점들을 가장 적은 수의 간선과 비용으로 연결하는 것

// kruskal_mst -> greedy method
// 각 단계에서 사이클을 이루지 않는 최소 비용 간선을 선택함으로써 최종적인 해답에 도달

#include <stdio.h>
#define MAX_VERTICES 100
#define INF 1000

// 히프의 요소 타입 정의
// 일반트리에서 heap은 정점을 배열에 저장했던 것와 달리 MST에서는 간선을 배열에 저장
// 트리는 노드 순번이 1부터 시작하지만, 그래프는 노드 순번이 0부터 시작
typedef struct {
	int key;
	int u; // 정점1
	int v; // 정점2
}element;

typedef struct {
	element heap[MAX_VERTICES];
	int heap_size;
}HeapType;

// 히프트리에서의 삽입함수
void insert_min_heap(HeapType* h, element edge) {
	int i;
	i = ++(h->heap_size);
	
	while ((i != 1)&&(edge.key<h->heap[i/2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = edge;
}

// 히프트리에서의 삭제함수
element delete_min_heap(HeapType* h) {
	int parent, child;
	element item, temp;
	item = h->heap[1];
	temp = h->heap[(h->heap_size)--]; // 원래 그래프의 맨 마지막 노드
	parent = 1; 
	child = 2;
	while (child <= h->heap_size) {
		if ((child < h->heap_size) && ((h->heap[child]).key > h->heap[child + 1].key))
			child++;
		if (temp.key <= h->heap[child].key) break;
		//한 단계 아래로 이동
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

HeapType* create() {
	return(HeapType*)malloc(sizeof(HeapType));
}

void init(HeapType* h) {
	h->heap_size = 0;
}

// union-find
int parent[MAX_VERTICES]; // 각 노드의 부모 노드
int num[MAX_VERTICES];    // 각 집합의 크기

// 초기화
void set_init(int n) {
	int i;
	for (i = 0; i < n; i++) {
		parent[i] = -1;
		num[i] = 1;
	}
}


// vertex가 속하는 집합 반환
int set_find(int vertex) {
	int p, s, i = 1;
	for (i = vertex; (p = parent[i]) >= 0; i = p); // 루트노드까지 반복
	s=i; // 집합의 대표 원소
	for (i = vertex; (p = parent[i]) >= 0; i = p)
		parent[i] = s; // 집합의 모든 원소들의 부모를 s로 설정 -> 높이가 1인 트리
	return s;
}

// 두 개의 원소가 속한 집합을 합함
void set_union(int s1, int s2) {
	if (num[s1] < num[s2]) {
		parent[s1] = s2;
		num[s2] += num[s1];
	}
	else {
		parent[s2] = s1;
		num[s1] += num[s2];
	}
}

void insert_heap_edge(HeapType* h, int u, int v, int weight) {
	element e;
	e.u = u;
	e.v = v;
	e.key = weight;
	insert_min_heap(h, e);
}

void insert_all_edges(HeapType* h) {
	insert_heap_edge(h, 0, 1, 29);
	insert_heap_edge(h, 1, 2, 16);
	insert_heap_edge(h, 2, 3, 12);
	insert_heap_edge(h, 3, 4, 22);
	insert_heap_edge(h, 4, 5, 27);
	insert_heap_edge(h, 5, 0, 10);
	insert_heap_edge(h, 6, 1, 15);
	insert_heap_edge(h, 6, 3, 18);
	insert_heap_edge(h, 6, 4, 25);
}

// kruskal의 최소 비용 신장 트리 프로그램
void kruskal(int n) {
	int edge_accepted = 0; // 현재까지 선택된 간선의 수
	HeapType h;
	int uset, vset; // 정점 u와 정점 v의 집합 번호
	element e;      // 히프 요소
	init(&h);
	set_init(n);    // 집합 초기화
	insert_all_edges(&h); // 히프에 간선들을 삽입
	while (edge_accepted < (n - 1)) {
		e = delete_min_heap(&h); // 최소 히프에서 삭제
		uset = set_find(e.u);
		vset = set_find(e.v);
		if (uset != vset) { // 서로 속한 집합이 다르면
			printf("(%d, %d) %d \n", e.u, e.v, e.key);
			edge_accepted++;
			set_union(uset, vset); // 두개의 집합을 합친다
		}
	}
}

// Prim Algorithm
// 시작정점에서부터 출발하여 신장 트리 집합을 단계적으로 확장해나감
// krukal Algorithm이 간선 기준이라면 Prim Algorithm은 정점 기준
// 인접한 정점 중에서 최저 간선으로 연결된 정점을 선택하여 추가
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES_PRIM 7
#define INF 1000L

int weight[MAX_VERTICES_PRIM][MAX_VERTICES_PRIM] = {
	{0,29,INF,INF,INF,10,INF},
	{29,0,16,INF,INF,INF,15},
	{INF,16,0,12,INF,INF,INF},
	{INF, INF,12,0,22,INF,18},
	{INF,INF,INF,22,0,27,25},
	{10,INF,INF,INF,27,0,INF},
	{INF,15,INF,18,25,INF,0}
};

int selected[MAX_VERTICES_PRIM];
int dist[MAX_VERTICES_PRIM]; // 이 정점으로 오는데의 최소 비용을 저장하는 배열

// 아직 가지 않은 노드 중 최소 비용의 정점을 반환
int get_min_vertex(int n) {
	int v, i;
	for (i = 0; i < n; i++)
		if (!selected[i]) {
			v = i;
			break;
		}
	for (i = 0; i < n; i++)
		if (!selected[i] && (dist[i] < dist[v]))v = i;
	return(v);
}

void prim(int s, int n){
	int i, u, v;
	// 초기화
	for (u = 0; u < n; u++) {
		dist[u] = INF;
		selected[u] = FALSE;
	}
	// 시작정점
	dist[s] = 0;

	for (i = 0; i < n; i++) {
		u = get_min_vertex(n);
		selected[u] = TRUE;
		if (dist[u] == INF) return;
		printf("(%d, cost : %d)\n", u, dist[u]);
		for (v = 0; v < n; v++)
			if (weight[u][v] != INF)
				if (!selected[v] && weight[u][v] < dist[v])
					dist[v] = weight[u][v];
	}
}


int main(void) {
	printf("------------- kruskal algorithm -----------\n");
	kruskal(7);
	printf("------------- prim algorithm --------------\n");
	prim(0, MAX_VERTICES_PRIM);
	return 0;
}

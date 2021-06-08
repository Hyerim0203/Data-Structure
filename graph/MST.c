// ����Ʈ��
// ��� �������� ����Ǿ� �־�� �ϰ�, ����Ŭ�� �������� �ʴ�
// �ּ� ���� ������ ��� �������� �����ϴ� Ʈ��
// �� n���� ��尡 �ִٸ� n-1���� ������ ����
// MST�� ��Ʈ��ũ�� �ִ� ��� �������� ���� ���� ���� ������ ������� �����ϴ� ��

// kruskal_mst -> greedy method
// �� �ܰ迡�� ����Ŭ�� �̷��� �ʴ� �ּ� ��� ������ ���������ν� �������� �ش信 ����

#include <stdio.h>
#define MAX_VERTICES 100
#define INF 1000

// ������ ��� Ÿ�� ����
// �Ϲ�Ʈ������ heap�� ������ �迭�� �����ߴ� �Ϳ� �޸� MST������ ������ �迭�� ����
// Ʈ���� ��� ������ 1���� ����������, �׷����� ��� ������ 0���� ����
typedef struct {
	int key;
	int u; // ����1
	int v; // ����2
}element;

typedef struct {
	element heap[MAX_VERTICES];
	int heap_size;
}HeapType;

// ����Ʈ�������� �����Լ�
void insert_min_heap(HeapType* h, element edge) {
	int i;
	i = ++(h->heap_size);
	
	while ((i != 1)&&(edge.key<h->heap[i/2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = edge;
}

// ����Ʈ�������� �����Լ�
element delete_min_heap(HeapType* h) {
	int parent, child;
	element item, temp;
	item = h->heap[1];
	temp = h->heap[(h->heap_size)--]; // ���� �׷����� �� ������ ���
	parent = 1; 
	child = 2;
	while (child <= h->heap_size) {
		if ((child < h->heap_size) && ((h->heap[child]).key > h->heap[child + 1].key))
			child++;
		if (temp.key <= h->heap[child].key) break;
		//�� �ܰ� �Ʒ��� �̵�
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
int parent[MAX_VERTICES]; // �� ����� �θ� ���
int num[MAX_VERTICES];    // �� ������ ũ��

// �ʱ�ȭ
void set_init(int n) {
	int i;
	for (i = 0; i < n; i++) {
		parent[i] = -1;
		num[i] = 1;
	}
}


// vertex�� ���ϴ� ���� ��ȯ
int set_find(int vertex) {
	int p, s, i = 1;
	for (i = vertex; (p = parent[i]) >= 0; i = p); // ��Ʈ������ �ݺ�
	s=i; // ������ ��ǥ ����
	for (i = vertex; (p = parent[i]) >= 0; i = p)
		parent[i] = s; // ������ ��� ���ҵ��� �θ� s�� ���� -> ���̰� 1�� Ʈ��
	return s;
}

// �� ���� ���Ұ� ���� ������ ����
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

// kruskal�� �ּ� ��� ���� Ʈ�� ���α׷�
void kruskal(int n) {
	int edge_accepted = 0; // ������� ���õ� ������ ��
	HeapType h;
	int uset, vset; // ���� u�� ���� v�� ���� ��ȣ
	element e;      // ���� ���
	init(&h);
	set_init(n);    // ���� �ʱ�ȭ
	insert_all_edges(&h); // ������ �������� ����
	while (edge_accepted < (n - 1)) {
		e = delete_min_heap(&h); // �ּ� �������� ����
		uset = set_find(e.u);
		vset = set_find(e.v);
		if (uset != vset) { // ���� ���� ������ �ٸ���
			printf("(%d, %d) %d \n", e.u, e.v, e.key);
			edge_accepted++;
			set_union(uset, vset); // �ΰ��� ������ ��ģ��
		}
	}
}

// Prim Algorithm
// ���������������� ����Ͽ� ���� Ʈ�� ������ �ܰ������� Ȯ���س���
// krukal Algorithm�� ���� �����̶�� Prim Algorithm�� ���� ����
// ������ ���� �߿��� ���� �������� ����� ������ �����Ͽ� �߰�
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
int dist[MAX_VERTICES_PRIM]; // �� �������� ���µ��� �ּ� ����� �����ϴ� �迭

// ���� ���� ���� ��� �� �ּ� ����� ������ ��ȯ
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
	// �ʱ�ȭ
	for (u = 0; u < n; u++) {
		dist[u] = INF;
		selected[u] = FALSE;
	}
	// ��������
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

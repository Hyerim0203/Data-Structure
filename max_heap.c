#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200

// 히프의 정의
typedef struct {
	int key;
}element;

typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
}HeapType;

// 히프트리에서의 삽입 함수
void insert_max_heap(HeapType* h, element item) {
	int i;
	i = ++(h->heap_size);

	// 트리를 거슬러 올라가면서 부모 노드와 비교
	while ((i != 1) && (item.key > h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;
}

// 히프트리에서의 삭제 함수
element delete_max_heap(HeapType* h) {
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// 현재 노드의 자식 노드 중 더 큰 자식 노드를 찾는다.
		// 마지막 노드가 아니고 우측 노드가 더 크다면
		if ((child < h->heap_size) && (h->heap[child]).key < h->heap[child + 1].key)
			child++;
		// 만약 마지막 노드라면 무조건 같기 때문에 break
		if (temp.key >= h->heap[child].key) break;
		// 한 단계 아래로 이동
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}

	h->heap[parent] = temp;
	return item;
}

HeapType* create() {
	return (HeapType*)malloc(sizeof(HeapType));
}

void init(HeapType* h) {
	h->heap_size = 0;
}

int main(void) {
	element e;
	HeapType* h = create();
	init(h);
	e.key = 5; insert_max_heap(h, e);
	e.key = 6; insert_max_heap(h, e);
	e.key = 15; insert_max_heap(h, e);
	e.key = 1; insert_max_heap(h, e);
	printf("입력 : 5, 6, 15, 1\n");
	printf("출력 : ");
	for (int i=0; i < 4; i++) {
		printf("%d, ", delete_max_heap(h).key);
	}

	return 0;
}






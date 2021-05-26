#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200

// ������ ����
typedef struct {
	int key;
}element;

typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
}HeapType;

// ����Ʈ�������� ���� �Լ�
void insert_max_heap(HeapType* h, element item) {
	int i;
	i = ++(h->heap_size);

	// Ʈ���� �Ž��� �ö󰡸鼭 �θ� ���� ��
	while ((i != 1) && (item.key > h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;
}

// ����Ʈ�������� ���� �Լ�
element delete_max_heap(HeapType* h) {
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// ���� ����� �ڽ� ��� �� �� ū �ڽ� ��带 ã�´�.
		// ������ ��尡 �ƴϰ� ���� ��尡 �� ũ�ٸ�
		if ((child < h->heap_size) && (h->heap[child]).key < h->heap[child + 1].key)
			child++;
		// ���� ������ ����� ������ ���� ������ break
		if (temp.key >= h->heap[child].key) break;
		// �� �ܰ� �Ʒ��� �̵�
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
	printf("�Է� : 5, 6, 15, 1\n");
	printf("��� : ");
	for (int i=0; i < 4; i++) {
		printf("%d, ", delete_max_heap(h).key);
	}

	return 0;
}






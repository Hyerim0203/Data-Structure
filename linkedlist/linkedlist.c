#include <stdio.h>
#include <stdlib.h>
void error(char* message) {
	fprintf(stderr, "%s", message);
	exit(1);
}

typedef int element;

// linkedlist 구조체 선언
typedef struct ListNode {
	element data;
	struct ListNode*link;
} ListNode;

// 삽입연산
void insert_node(ListNode** phead, ListNode* p, ListNode* new_node) {
	// phead : linkedlist의 head pointer
	// p : 선행 node
	// new node : 삽입될node
	if (*phead == NULL) { // 공백리스트라면
		new_node->link = NULL;
		*phead = new_node;
	}
	else if (p == NULL) { // 첫번째 노드로 삽입한다면
		new_node->link = *phead;
		*phead = new_node;
	}
	else {                // p node 다음에 삽입
		new_node->link = p->link;
		p->link = new_node;
	}
}

// 삭제연산
void remove_node(ListNode** phead, ListNode* p, ListNode* removed) {
	if (p == NULL)
		*phead = removed->link;
	else
		p->link = removed->link;
	free(removed);
}

// display
void display(ListNode* head) {
	ListNode* p = head;
	while (p != NULL) {
		printf("%d->", p->data);
		p = p->link;
	}
	printf("\n");
}

// 탐색(특정한 데이터 값을 찾는 연산)
ListNode* search(ListNode* head, int x) {
	ListNode* p = head;
	while (p != NULL) {
		if (p->data == x) return p;
		p = p->link;
	}
	return p; // 탐색실패일 경우 NULL 반환
}

// 합병 연산 코드
ListNode* concat(ListNode* head1, ListNode* head2) {
	ListNode* p;
	if (head1 == NULL) return head2;
	else if (head2 == NULL) return head1;
	else {
		p = head1;
		while (p->link != NULL) {
			p = p->link;
		}
		p->link = head2;
		return head1;
	}
}

ListNode* reverse(ListNode* head) {
	ListNode* r;
	ListNode* p = head; // 역순으로 만들 리스트
	ListNode* q = NULL; // 역순으로 만들 노드
	while (p != NULL) {
		r = q;          // 바꿀 link 값을 저장해놓음
		q = p;          // 역순으로 만들 노드 복사
		q->link = r;    // 저장해놓은 link값 할당
		p = p->link;
	}
	return q;           // 역순으로 된 리스트의 헤드 포인터
}

// List
typedef struct {
	ListNode* head; // 헤드 포인터
	int length;     // 노드의 개수
} ListType;

void init(ListType* list) {
	list->length = 0;
	list->head = NULL;
}

// 비어있는지를 반환
int is_empty(ListType* list) {
	return (list->head == NULL);
}

// 리스트의 항목의 개수를 반환
int get_length(ListType* list) {
	return list->length;
}

// 리스트 안에서 pos 위치의 노드를 반환
ListNode* get_node_at(ListType* list, int pos)
{
	int i;
	ListNode* p = list->head;
	if (pos < 0 || pos>=list->length) return NULL;
	for (i = 0; i < pos; i++) 
		p = p->link;
	return p;
}

// 리스트 안에서 pos위치의 데이터를 반환
element get_entry(ListType* list, int pos)
{
	ListNode* p;
	if (pos < 0 || pos >= list->length) error("위치 오류");
	p = get_node_at(list, pos);
	return p->data;
}

// 주어진 위치에 데이터를 삽입
void add(ListType* list, int pos, element data) {
	ListNode* p;
	if ((pos >= 0) && (pos <= list->length)) { // < 가 아닌 <= 임에 유의!
		ListNode* node = (ListNode*)malloc(sizeof(ListNode));
		if (node == NULL) error("메모리 할당에러");
		node->data = data;
		p = get_node_at(list, pos-1); // 전 노드를 찾아야 하기 때문에 pos-1
		insert_node(&(list->head), p, node);
		list->length++;
	}
}

// 주어진 위치의 데이터를 삭제
void delete(ListType* list, int pos) {
	ListNode* p;
	if (pos >= 0 && pos < list->length) {
		p = get_node_at(list, pos-1);
		remove_node(&(list->head), p, (p != NULL) ? p->link : NULL);
		list->length--;
	}
}

int main(void) {
	ListNode* head = NULL;
	ListType list1;
	ListNode* tmp1;
	ListNode* tmp2 = NULL;
	int i;
	init(&list1);
	for (i = 0; i < 10; i++) {
		tmp1 = (ListNode*)malloc(sizeof(ListNode)); // 추가할 노드
		tmp1->data = i + 1;						    // 데이터 삽입
		insert_node(&(head),tmp2,tmp1);       // 노드 추가
		tmp2 = tmp1;
	}
	display(head);
	printf("\n");
	while (head != NULL)
	{
		remove_node(&(head), NULL, head);
		display(head);
	}

	for (i = 0; i < 10; i++) {
		add(&list1, i, 10 - i);
	}
	display(list1.head);
	return 0;
}

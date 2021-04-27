#include <stdio.h>
#include <stdlib.h>
void error(char* message) {
	fprintf(stderr, "%s", message);
	exit(1);
}

typedef int element;

// linkedlist ����ü ����
typedef struct ListNode {
	element data;
	struct ListNode*link;
} ListNode;

// ���Կ���
void insert_node(ListNode** phead, ListNode* p, ListNode* new_node) {
	// phead : linkedlist�� head pointer
	// p : ���� node
	// new node : ���Ե�node
	if (*phead == NULL) { // ���鸮��Ʈ���
		new_node->link = NULL;
		*phead = new_node;
	}
	else if (p == NULL) { // ù��° ���� �����Ѵٸ�
		new_node->link = *phead;
		*phead = new_node;
	}
	else {                // p node ������ ����
		new_node->link = p->link;
		p->link = new_node;
	}
}

// ��������
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

// Ž��(Ư���� ������ ���� ã�� ����)
ListNode* search(ListNode* head, int x) {
	ListNode* p = head;
	while (p != NULL) {
		if (p->data == x) return p;
		p = p->link;
	}
	return p; // Ž�������� ��� NULL ��ȯ
}

// �պ� ���� �ڵ�
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
	ListNode* p = head; // �������� ���� ����Ʈ
	ListNode* q = NULL; // �������� ���� ���
	while (p != NULL) {
		r = q;          // �ٲ� link ���� �����س���
		q = p;          // �������� ���� ��� ����
		q->link = r;    // �����س��� link�� �Ҵ�
		p = p->link;
	}
	return q;           // �������� �� ����Ʈ�� ��� ������
}

// List
typedef struct {
	ListNode* head; // ��� ������
	int length;     // ����� ����
} ListType;

void init(ListType* list) {
	list->length = 0;
	list->head = NULL;
}

// ����ִ����� ��ȯ
int is_empty(ListType* list) {
	return (list->head == NULL);
}

// ����Ʈ�� �׸��� ������ ��ȯ
int get_length(ListType* list) {
	return list->length;
}

// ����Ʈ �ȿ��� pos ��ġ�� ��带 ��ȯ
ListNode* get_node_at(ListType* list, int pos)
{
	int i;
	ListNode* p = list->head;
	if (pos < 0 || pos>=list->length) return NULL;
	for (i = 0; i < pos; i++) 
		p = p->link;
	return p;
}

// ����Ʈ �ȿ��� pos��ġ�� �����͸� ��ȯ
element get_entry(ListType* list, int pos)
{
	ListNode* p;
	if (pos < 0 || pos >= list->length) error("��ġ ����");
	p = get_node_at(list, pos);
	return p->data;
}

// �־��� ��ġ�� �����͸� ����
void add(ListType* list, int pos, element data) {
	ListNode* p;
	if ((pos >= 0) && (pos <= list->length)) { // < �� �ƴ� <= �ӿ� ����!
		ListNode* node = (ListNode*)malloc(sizeof(ListNode));
		if (node == NULL) error("�޸� �Ҵ翡��");
		node->data = data;
		p = get_node_at(list, pos-1); // �� ��带 ã�ƾ� �ϱ� ������ pos-1
		insert_node(&(list->head), p, node);
		list->length++;
	}
}

// �־��� ��ġ�� �����͸� ����
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
		tmp1 = (ListNode*)malloc(sizeof(ListNode)); // �߰��� ���
		tmp1->data = i + 1;						    // ������ ����
		insert_node(&(head),tmp2,tmp1);       // ��� �߰�
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
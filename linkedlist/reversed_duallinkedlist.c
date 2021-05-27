#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct {
	element data;
	struct DListNode* llink;
	struct DListNode* rlink;
}DListNode;

// �ʱ�ȭ
void init(DListNode* phead) {
	phead->llink = phead;
	phead->rlink = phead;
}

// ���ο� �����͸� ��� before�� �����ʿ� ����
void dinsert(DListNode* before, element item) {
	DListNode* new_node = (DListNode*)malloc(sizeof(DListNode));
	DListNode* p;
	new_node->data = item;
	new_node->llink = before;
	new_node->rlink = before->rlink;
	p = before->rlink;
	p->llink = new_node;
	before->rlink = new_node;
}

void ddelete(DListNode* head, DListNode* removed) {
	DListNode* p;
	if (removed == head) return;
	p = removed->llink;
	p->rlink = removed->rlink;
	p=removed->rlink;
	p->llink = removed->llink;
	free(removed);
}

void display(DListNode* head) {
	DListNode* p = head->rlink;
	while (p != head) {
		printf("%d ", p->data);
		p = p->rlink;
	} ;
}

void reverse_display(DListNode*head) {
	DListNode* p = head->llink;
	while (p != head) {
		printf("%d ", p->data);
		p = p->llink;
	}
}

int main(void) {
	DListNode* head = (DListNode*)malloc(sizeof(DListNode));
	DListNode* p;
	int num, item;
	init(head);

	printf("�������� ������ �Է��Ͻÿ� : ");
	scanf("%d", &num);
	printf("\n");

	for (int i = 0; i < num;  i++) {
		printf("��� #%d�� �����͸� �Է��Ͻÿ�: ",i+1);
		scanf("%d", &item);
		p = head;
		for (int j = 0; j < i; j++)
			p = p->rlink;
		dinsert(p, item);
	}
	printf("\n");

	printf("�����͸� �������� ���: ");
	reverse_display(head);
	return 0;
}


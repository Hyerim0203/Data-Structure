#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct {
	element data;
	struct ListNode *link;
}ListNode;

void insert(ListNode** phead, ListNode* p, ListNode* new_node) {
	if (*phead == NULL) {
		new_node->link = NULL;
		*phead = new_node;
	}
	else if (p == NULL) {
		new_node->link = *phead;
		*phead = new_node;
	}
	else {
		new_node->link = p->link;
		p->link = new_node;
	}
}

void remove_node(ListNode** phead, ListNode* p, ListNode* removed) {
	if (p == NULL)
		*phead = (*phead)->link;
	else
		p->link = removed->link;
	free(removed);
}
f
void display(ListNode *head) {
	ListNode* p = head;
	while (p != NULL) {
		printf("%d->", p->data);
		p = p->link;
	}
	printf("\n");
}

element search_max(ListNode* head) {
	element max = head->data;
	ListNode* p = head->link;
	while (p != NULL) {
		if (max < p->data)
			max = p->data;
		p = p->link;
	}
	return max;
}

ListNode* create() {
	return (ListNode*)malloc(sizeof(ListNode));
}

int main(void) {
	ListNode* head = create();
	head = NULL;
	ListNode l1, l2, l3, l4, l5;
	l1.data = 15; l1.link = NULL;
	l2.data = 13; l2.link = NULL;
	l3.data = 29; l3.link = NULL;
	l4.data = 16; l4.link = NULL;
	l5.data = 24; l5.link = NULL;
	insert(&head, NULL, &l1);
	insert(&head, &l1, &l2);
	insert(&head, &l2, &l3);
	insert(&head, &l3, &l4);
	insert(&head, &l4, &l5);

	printf("ÃÖ´ñ°ª : %d", search_max(head));

	return 0;
}
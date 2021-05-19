#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct {
	int data;
	struct TreeNode* left, * right;
}TreeNode;

// 전위순회
void preorder(TreeNode* tree) {
	if (tree){
		printf("%d ", tree->data);
		preorder(tree->left);
		preorder(tree->right);
	}
}

// 중위순회
void inorder(TreeNode* tree) {
	if (tree){
		inorder(tree->left);
		printf("%d ", tree->data);
		inorder(tree->right);
	}
}

// 후위순회
void postorder(TreeNode* tree) {
	if (tree){
		postorder(tree->left);
		postorder(tree->right);
		printf("%d ", tree->data);
	}
}

typedef TreeNode* element;
#define MAX_QUEUE_SIZE 100

typedef struct {
	element data[MAX_QUEUE_SIZE];
	int rear, front;
}QueueType;

void initialize(QueueType* q) {
	q->rear = 0;
	q->front = 0;
}

int is_empty(QueueType* q) {
	return(q->front == q->rear);
}

int is_full(QueueType* q) {
	return(q->rear == (q->front + 1) % MAX_QUEUE_SIZE);
}

void enqueue(QueueType* q, element input) {
	if (!is_full(q)) {
		q->front = (q->front + 1) % MAX_QUEUE_SIZE;
		q->data[q->front] = input;
	}
}

element dequeue(QueueType* q) {
	if (!is_empty(q)) {
		q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
		return(q->data[q->rear]);
	}
}

// 레벨 순회 알고리즘
void level_order(TreeNode* root) {
	QueueType q;
	initialize(&q);
	enqueue(&q, root);
	while (!is_empty(&q)) {
		root = dequeue(&q);
		printf("%d ", root->data);
		if (root->left)
			enqueue(&q, root->left);
		if (root->right)
			enqueue(&q, root->right);
	}
}

int main(void) {
	TreeNode n1 = { 2, NULL, NULL };
	TreeNode n2 = { 1, NULL, NULL };
	TreeNode n3 = { 4, NULL, NULL };
	TreeNode n4 = { 5, NULL, NULL };
	TreeNode n5 = { 3, &n1, &n2 };
	TreeNode n6 = { 9, &n3, &n4 };
	TreeNode n7 = { 8, &n5, &n6 };
	TreeNode* root = &n7;
	printf("전위순회\n");
	preorder(root);
	printf("\n");
	printf("중위순회\n");
	inorder(root);
	printf("\n");
	printf("후위순회\n");
	postorder(root);
	printf("\n");
	printf("레벨순회\n");
	level_order(root);
	return(0);
}


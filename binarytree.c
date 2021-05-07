#include <stdio.h>
#include <math.h>
#define MAX_TREE_SIZE 7

void edge_display(int floor_block, int h) {
	int i;
	//��Ʈ ��� ����
	int node_num = pow(2, (h + 1) / 2) - pow(2, (h - 1) / 2);
	int print_block = (node_num * 3);
	int blank_block = (floor_block-print_block)/2;
	for (i = 0; i < blank_block; i++)
		printf(" ");
	for (i = 0; i < node_num; i++) {
		printf("/");
		printf(" ");
		printf("\\");
		printf(" ");
	}
	for (i = 0; i < blank_block-1; i++)
		printf(" ");
	printf("\n");
}

void node_display(int* tree, int floor_block, int h) {
	int i;
	// �ش� ���� ����� ù��° ���
	int index = pow(2,(h - 1) / 2) - 1;
	// �ش� ���� ��� ����
	int node_num = pow(2, (h+1) / 2) - pow(2, (h-1)/2);
	int node_block = node_num + node_num -1 + (node_num)/2;
	for (i = 0; i < (floor_block - node_block) / 2; i++)
		printf(" ");
	for (i = index; i < index + node_num; i++){
		if (i%2==0)
			printf(" ");
		printf("%d ", tree[i]);
		}
	for (i = 0; i < (floor_block - node_block) / 2 -1 ; i++)
		printf(" ");
	printf("\n");
}

void display(int* tree) {
	// Ʈ���� ����
	int height = log2(MAX_TREE_SIZE + 1);
	// ����ϴ� �� ����(edge�� ����)
	int full_height = height + (height - 1);
	// �� ���� �� ����
	int floor_block = 2 * full_height - 1;
	
	// ���
	for (int h = 1; h <= full_height; h++) {
		if (h % 2 == 0)
			edge_display(floor_block, h);
		else if(h % 2 == 1)
			node_display(tree, floor_block, h);

	}
}

int main(void) {
	int tree[MAX_TREE_SIZE];

	for (int i = 0; i < MAX_TREE_SIZE; i++) {
		printf("���Ҹ� �Է��ϼ���");
		scanf("%d", &tree[i]);
	}
	

	display(tree);
	return(0);
}
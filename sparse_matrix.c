#include <stdio.h>
#define MAX_TERMS 10

typedef struct {
	int row;
	int col;
	int value;
} element;

typedef struct SparseMatrix {
	element data[MAX_TERMS];
	int rows;  // ���� ����
 	int cols;  // ���� ����
	int terms; // ���� ����(0�� �ƴ� ���� ����)
} SparseMatrix;

// ������ ���� �Լ�
// c = a+b
SparseMatrix sparse_matrix_add2(SparseMatrix a, SparseMatrix b) {
	SparseMatrix c;
	int ca = 0, cb = 0, cc = 0; // �� �迭�� �׸��� ����Ű�� �ε���
	// �迭 a�� �迭 b�� ũ�Ⱑ ���� ���� Ȯ��
	if (a.rows != b.rows || a.cols != b.cols) {
		fprintf(stderr, "������ ũ�⿡��\n");
		//exit(1);
	}
	// �迭 a�� �迭 b�� ũ�Ⱑ ���ٸ� c�� ũ�� ����
	c.rows = a.rows;
	c.cols = a.cols;
	c.terms = 0;

	while (ca < a.terms && cb < b.terms) {
		// �� �׸��� �������� ��ȣ�� ���
		int inda = a.data[ca].row * a.cols + a.data[ca].col;
		int indb = b.data[cb].row * b.cols + b.data[cb].col;
		if (inda < indb) {
			// a�迭 �׸��� �տ� ������
			c.data[cc++] = a.data[ca++]; // a�� ������ �״�� ����

		}
		else if (inda == indb) {
			// a�� b�� ���� ��ġ�̰� ���� ���� 0�� �ƴ϶��
			if (a.data[ca].value + b.data[cb].value != 0) {
				c.data[cc].row = a.data[ca].row;
				c.data[cc].col = a.data[ca].col;
				c.data[cc++].value = a.data[ca++].value +
					b.data[cb++].value;
			}
			else {
				ca++; cb++;
			}
		}
		else // b �迭 �׸��� �տ� ����
			c.data[cc++] = b.data[cb++];
	}
	// �迭 a�� b�� ���� �ִ� �׵��� �迭 c�� �ű��.
	for (; ca < a.terms;)
		c.data[cc++] = a.data[ca++];
	for (; cb < b.terms;)
		c.data[cc++] = b.data[cb++];
	c.terms = cc;
	return c;
}

int main(void){
	int cc = 0, size = 0;
	char* element_temp = NULL;
	SparseMatrix A, B, C; // �������� ����
	printf("���ũ�⸦ �Է��Ͻÿ�:");
	scanf("%d", &size);
	A.rows = size; A.cols = size; B.rows = size; B.cols = size;
	element_temp = (char*)malloc(sizeof(char) * (size+1));
	
	printf("���A�� ��Ұ����� �Է��Ͻÿ�:");
	scanf("%d", &(A.terms));
	for (int i = 0; i < A.terms; i++) {
		printf("��� A�� ��Ұ��� �Է��Ͻÿ�:");
		scanf("%s", element_temp); // ���ڿ��� �Է¹���
		// ���ڿ��� �Է¹��� ��Ұ��� ���������� ����
		A.data[i].row = element_temp[0]-48;
		A.data[i].col = element_temp[1]-48;
		A.data[i].value = element_temp[2]-48;
	}

	printf("���B�� ��Ұ����� �Է��Ͻÿ�:");
	scanf("%d", &(B.terms));
	for (int i = 0; i < B.terms; i++) {
		printf("��� B�� ��Ұ��� �Է��Ͻÿ�:");
		scanf("%s", element_temp);
		B.data[i].row = element_temp[0]-48;
		B.data[i].col = element_temp[1]-48;
		B.data[i].value = element_temp[2]-48;
	}

	C = sparse_matrix_add2(A, B);
	printf("��� c�� ���� ������ �����ϴ�.\n");
	for (int i = 0; i < C.cols * C.rows; i++) {
		// �� �迭�� �׸��� ����Ű�� ���Ҹ� ��� ���� ����
		int r = i / C.cols;
		int c = i % C.cols;
;		if (C.data[cc].row == r && C.data[cc].col == c) {
			printf("%d ", C.data[cc].value);
			cc++;
			// ���̹ٲ�� �ٶ��
			if (i % C.cols == C.cols-1) printf("\n"); 
		}
		else {
			printf("%d ", 0);
			// ���̹ٲ�� �ٶ��
			if (i % C.cols == C.cols - 1) printf("\n");
		}
	}
	return 0;
}
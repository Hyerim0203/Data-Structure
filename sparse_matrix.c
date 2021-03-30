#include <stdio.h>
#define MAX_TERMS 10

typedef struct {
	int row;
	int col;
	int value;
} element;

typedef struct SparseMatrix {
	element data[MAX_TERMS];
	int rows;  // 행의 개수
 	int cols;  // 열의 개수
	int terms; // 항의 개수(0이 아닌 값의 개수)
} SparseMatrix;

// 희소행렬 덧셈 함수
// c = a+b
SparseMatrix sparse_matrix_add2(SparseMatrix a, SparseMatrix b) {
	SparseMatrix c;
	int ca = 0, cb = 0, cc = 0; // 각 배열의 항목을 가리키는 인덱스
	// 배열 a와 배열 b의 크기가 같은 지를 확인
	if (a.rows != b.rows || a.cols != b.cols) {
		fprintf(stderr, "희소행렬 크기에러\n");
		//exit(1);
	}
	// 배열 a와 배열 b의 크기가 같다면 c의 크기 정의
	c.rows = a.rows;
	c.cols = a.cols;
	c.terms = 0;

	while (ca < a.terms && cb < b.terms) {
		// 각 항목의 순차적인 번호를 계산
		int inda = a.data[ca].row * a.cols + a.data[ca].col;
		int indb = b.data[cb].row * b.cols + b.data[cb].col;
		if (inda < indb) {
			// a배열 항목이 앞에 있으면
			c.data[cc++] = a.data[ca++]; // a의 데이터 그대로 저장

		}
		else if (inda == indb) {
			// a와 b가 같은 위치이고 더한 값이 0이 아니라면
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
		else // b 배열 항목이 앞에 있음
			c.data[cc++] = b.data[cb++];
	}
	// 배열 a와 b에 남아 있는 항들을 배열 c로 옮긴다.
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
	SparseMatrix A, B, C; // 희소행렬을 정의
	printf("행렬크기를 입력하시오:");
	scanf("%d", &size);
	A.rows = size; A.cols = size; B.rows = size; B.cols = size;
	element_temp = (char*)malloc(sizeof(char) * (size+1));
	
	printf("행렬A의 희소값수를 입력하시오:");
	scanf("%d", &(A.terms));
	for (int i = 0; i < A.terms; i++) {
		printf("행렬 A의 희소값을 입력하시오:");
		scanf("%s", element_temp); // 문자열로 입력받음
		// 문자열로 입력받은 희소값은 정수형으로 변경
		A.data[i].row = element_temp[0]-48;
		A.data[i].col = element_temp[1]-48;
		A.data[i].value = element_temp[2]-48;
	}

	printf("행렬B의 희소값수를 입력하시오:");
	scanf("%d", &(B.terms));
	for (int i = 0; i < B.terms; i++) {
		printf("행렬 B의 희소값을 입력하시오:");
		scanf("%s", element_temp);
		B.data[i].row = element_temp[0]-48;
		B.data[i].col = element_temp[1]-48;
		B.data[i].value = element_temp[2]-48;
	}

	C = sparse_matrix_add2(A, B);
	printf("행렬 c의 값은 다음과 같습니다.\n");
	for (int i = 0; i < C.cols * C.rows; i++) {
		// 각 배열의 항목을 가리키는 원소를 행과 열로 변경
		int r = i / C.cols;
		int c = i % C.cols;
;		if (C.data[cc].row == r && C.data[cc].col == c) {
			printf("%d ", C.data[cc].value);
			cc++;
			// 행이바뀌면 줄띄움
			if (i % C.cols == C.cols-1) printf("\n"); 
		}
		else {
			printf("%d ", 0);
			// 행이바뀌면 줄띄움
			if (i % C.cols == C.cols - 1) printf("\n");
		}
	}
	return 0;
}
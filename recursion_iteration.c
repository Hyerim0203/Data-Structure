#include <stdio.h>

// ���丮�� ��ȯ
int factorial(int n) {
	if (n == 1) return (1);
	else return (n * factorial(n - 1));
}

// ���丮�� �ݺ�
int factorial_iter(int n) {
	int k, v = 1;
	for (k = n; k > 0; k--)
		v *= k;
	return(v);
}

// �ŵ����� ��ȯ-�ð����⵵ : O(log2(n))
double power(double x, int n) {
	if (n == 0) return(1);
	else if (n % 2 == 0) return(power(x * x, n / 2));
	else  return(x*power(x * x, (n - 1) / 2));
}


// �ŵ����� �ݺ�-�ð����⵵ : O(n)
double slow_power(double x, int n) {
	int i;
	double r = 1.0;
	for (i = 0; i < n; i++)
		r *= x;
	return(r);
}

// �Ǻ���ġ ��ȯ - ���� ���� �ߺ��ؼ� ���Ǳ� ������ ��ȿ����
int fib(int n) {
	if (n == 0) return(0);
	if (n == 1)return(1);
	return(fib(n - 2) + fib(n - 1));
}

// �Ǻ���ġ �ݺ�
int fib_iter(int n) {
	if (n < 2) return (n);
	else {
		int i, tmp, current = 1, last = 0;
		for (i = 2; i <= n; i++) {
			tmp = current;   // i-1��° �� 
			current += last; // i��° �� ���
			last = tmp;      // i+1������ i-2��° �� ����
		}
		return(current);
	}
}

void hanoi_tower(int n, char from, char tmp, char to) {
	if (n == 1) 
		printf("%c���� %c�� ������ �ű��.\n", from, tmp);
	else {
		hanoi_tower(n - 1, from, to, tmp);
		printf("%c���� %c�� ������ �ű��.\n", from, tmp);
		hanoi_tower(n - 1, tmp, from, to);
	}
}

int main(void) {
	int n;
	printf("���ڸ� �Է����ּ���");
	scanf("%d", &n);
	printf("��ȯ�� �̿��� %d ���丮�� : %d\n", n, factorial(n));
	printf("�ݺ��� �̿��� %d ���丮�� : %d\n", n, factorial_iter(n));
	printf("��ȯ�� �̿��� %d�� 6�ŵ����� : %f\n", n, power(n, 6));
	printf("�ݺ��� �̿��� %d�� 6 �ŵ����� : %f\n", n, slow_power(n, 6));
	printf("��ȯ�� �̿��� �Ǻ���ġ ������ %d��° �� : %d\n", n, fib(n));
	printf("�ݺ��� �̿��� �Ǻ���ġ ������ %d��° �� : %d\n", n, fib(n));
	printf("�ϳ���ž\n");
	hanoi_tower(n, 'A', 'B', 'C');

	return 0;
}


#include <stdio.h>

// 팩토리얼 순환
int factorial(int n) {
	if (n == 1) return (1);
	else return (n * factorial(n - 1));
}

// 팩토리얼 반복
int factorial_iter(int n) {
	int k, v = 1;
	for (k = n; k > 0; k--)
		v *= k;
	return(v);
}

// 거듭제곱 순환-시간복잡도 : O(log2(n))
double power(double x, int n) {
	if (n == 0) return(1);
	else if (n % 2 == 0) return(power(x * x, n / 2));
	else  return(x*power(x * x, (n - 1) / 2));
}


// 거듭제곱 반복-시간복잡도 : O(n)
double slow_power(double x, int n) {
	int i;
	double r = 1.0;
	for (i = 0; i < n; i++)
		r *= x;
	return(r);
}

// 피보나치 순환 - 같은 항이 중복해서 계산되기 때문에 비효율적
int fib(int n) {
	if (n == 0) return(0);
	if (n == 1)return(1);
	return(fib(n - 2) + fib(n - 1));
}

// 피보나치 반복
int fib_iter(int n) {
	if (n < 2) return (n);
	else {
		int i, tmp, current = 1, last = 0;
		for (i = 2; i <= n; i++) {
			tmp = current;   // i-1번째 값 
			current += last; // i번째 값 계산
			last = tmp;      // i+1에서의 i-2번째 값 저장
		}
		return(current);
	}
}

void hanoi_tower(int n, char from, char tmp, char to) {
	if (n == 1) 
		printf("%c에서 %c로 원판을 옮긴다.\n", from, tmp);
	else {
		hanoi_tower(n - 1, from, to, tmp);
		printf("%c에서 %c로 원판을 옮긴다.\n", from, tmp);
		hanoi_tower(n - 1, tmp, from, to);
	}
}

int main(void) {
	int n;
	printf("숫자를 입력해주세요");
	scanf("%d", &n);
	printf("순환을 이용한 %d 팩토리얼 : %d\n", n, factorial(n));
	printf("반복을 이용한 %d 팩토리얼 : %d\n", n, factorial_iter(n));
	printf("순환을 이용한 %d의 6거듭제곱 : %f\n", n, power(n, 6));
	printf("반복을 이용한 %d의 6 거듭제곱 : %f\n", n, slow_power(n, 6));
	printf("순환을 이용한 피보나치 수열의 %d번째 수 : %d\n", n, fib(n));
	printf("반복을 이용한 피보나치 수열의 %d번째 수 : %d\n", n, fib(n));
	printf("하노이탑\n");
	hanoi_tower(n, 'A', 'B', 'C');

	return 0;
}


#include <stdio.h>
int BinomialCoefficient_iter(int n, int k)
{
	float result = 1;
	for (int i = 0 ; i < k; i++)
	{
		result *= (n - i);
		result /= (k - i);
	}
	return result;
}

int BinomialCoefficient_recursion(int n, int k)
{
	if (k == 0 || k == n) return(1);
	else return (BinomialCoefficient_recursion(n - 1, k - 1) + BinomialCoefficient_recursion(n - 1, k));
}

int main(void)
{
	int a, b;
	a = BinomialCoefficient_iter(10, 3);
	b = BinomialCoefficient_recursion(10, 3);
	printf("%d,%d", a, b);
}
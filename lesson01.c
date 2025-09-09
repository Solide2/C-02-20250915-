#include <stdio.h>

int main() {
	int id;
	int product;
	int in[101];
	int out[101];
	int a;

	scanf_s("%d", &product);

	for (int i = 0; i < product; i++)
	{
		scanf_s("%d", &in[i]);
	}

	for (int i = 0; i < product; i++)
	{
		scanf_s("%d", &out[i]);
	}

	scanf_s("%d", &id);

	a = id - 1;

	printf("%d\n", in[a] - out[a]);
	for (int i = 0; i < product; i++)
	{
		printf("%d", in[i] - out[i]);
		printf(" ");
	}
}

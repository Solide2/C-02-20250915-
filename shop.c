#include <stdio.h>

int main() {
	int id;
	int product;
	int in[101];
	int out[101];

	scanf_s("%d", &product);

	for  (int i = 0; i < product; i++)
	{
		scanf_s("%d", &in[i]);
	}

	for (int i = 0; i < product; i++)
	{
		scanf_s("%d", &out[i]);
	}

	scanf_s("%d", &id);

	printf("%d\n", in[id] - out[id]);
	for (int i = 0; i < product; i++)
	{
		printf("%d", in[i] - out[i]);
		printf(" ");
	}
}
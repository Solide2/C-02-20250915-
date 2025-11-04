#include <stdio.h>

int main() {
	int id;
	int a;//id 입력
	int product;
	int in[101];//입고
	int inall = 0; //총 입고 수량
	int out[101];//출고
	int outall[101];//남은 수량
	

	int sellall = 0;//총 판매량
	float sellpercent = 0;//판매율

	printf("상품 종류 :");

	scanf_s("%d", &product);

	printf("입고 수량 :");

	for (int i = 0; i < product; i++)
	{
		scanf_s("%d", &in[i]);
	}

	printf("판매 수량 :");
	for (int i = 0; i < product; i++)
	{
		scanf_s("%d", &out[i]);
	}

	for (int i = 0; i < product; i++)
	{
		outall[i] = in[i] - out[i];
		inall += in[i];
		sellall += out[i];
	}

	printf("ID 입력 :");
	scanf_s("%d", &id);
	a = id - 1;

	printf("ID에 해당하는 제품의 재고 수량 :");
	printf("%d\n", outall[a]);

	printf("재고 수량: ");
	for (int i = 0; i < product; i++)
	{
		printf("%d", outall[i]);
		printf(" ");
	}

	sellpercent = (sellall / (float)inall) * 100;

	printf("\n총 판매량 %d (판매율 %.2f)\n", sellall, sellpercent);


	for (int i = 0; i < product; i++)
	{
		if (outall[i] <= 2)
		{
			printf("상품 ID %d: 재고 부족 (%d)\n", i, outall[i]);
		}
	}
	int sold[101];

	for (int i = 0; i < product; i++) {
		sold[i] = in[i] - outall[i];
	}

	int maxID = 0, minID = 0;
	int maxSales = sold[0], minSales = sold[0];

	for (int i = 1; i < product; i++) {
		if (sold[i] > maxSales) {
			maxSales = sold[i];
			maxID = i;
		}
		if (sold[i] < minSales) {
			minSales = sold[i];
			minID = i;
		}
	}
	printf("\n가장 많이 판매된 상품 : ID %d, 판매량 %d\n", maxID + 1, maxSales);
	printf("가장 적게 판매된 상품 : ID %d, 판매량 %d\n", minID + 1, minSales);
}

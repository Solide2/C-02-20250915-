#include <stdio.h>

int main() {
	int id;
	int a;//id �Է�
	int product;
	int in[101];//�԰�
	int inall = 0; //�� �԰� ����
	int out[101];//���
	int outall[101];//���� ����
	
	int sellall = 0;//�� �Ǹŷ�
	float sellpercent = 0;//�Ǹ���

	printf("��ǰ ���� :");

	scanf_s("%d", &product);

	printf("�԰� ���� :");

	for (int i = 0; i < product; i++)
	{
		scanf_s("%d", &in[i]);
	}

	printf("�Ǹ� ���� :");
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

	printf("ID �Է� :");
	scanf_s("%d", &id);
	a = id - 1;
	
	printf("ID�� �ش��ϴ� ��ǰ�� ��� ���� :");
	printf("%d\n", outall[a]);

	printf("��� ����: ");
	for (int i = 0; i < product; i++)
	{
		printf("%d", outall[i]);
		printf(" ");
	}

	sellpercent = (sellall / (float)inall)*100;

	printf("\n�� �Ǹŷ� %d (�Ǹ��� %.2f)\n", sellall, sellpercent);


	for (int i = 0; i < product; i++)
	{
		if (outall[i] <= 2)
			{
			printf("��ǰ ID %d: ��� ���� (%d)\n", i, outall[i]);
			}
	}
	
}
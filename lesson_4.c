#include <stdio.h>

#define MAX_QUANTITY 101
int stock[MAX_QUANTITY] = { 0 };

int Mainmenu;

int main() {
	int menu = MainMenu();
	if (menu == 1){//�԰�
		InStockMenu(stock);
	}

	else if (menu == 2) {//�Ǹ�
		SellMenu(stock);
	}

	else if (menu == 3) {//��ǰ��Ȳ
		StorageMenu(stock);
	}

	else if (menu == 4) {//����
		printf("���α׷� ����");
	}

	else {
		printf("�߸��� �Է�");
	}
}
int MainMenu() {
	int menu;
	printf("[���θ��������α׷�]\n");
	printf("���ϴ¸޴��������ϼ���.(1.�԰�, 2.�Ǹ�, 3.��ǰ��Ȳ, 4.����)\n");
	scanf_s("%d", &menu);
	return menu;
}
int SellMenu() {

}
int StorageMenu() {

}

int InStockMenu() {
	int menu;
	printf("1.��ü ��ǰ �԰� ���� ,2. ���� ��ǰ �Է�");

	scanf_s("%d", &menu);

	printf("�԰� ���� :");

	for (int i = 0; i < product; i++)
	{
		scanf_s("%d", &in[i]);
	}for (int i = 0; i < product; i++)
	{
		scanf_s("%d", &in[i]);
	}
}
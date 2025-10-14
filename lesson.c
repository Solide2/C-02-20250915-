#include <stdio.h>

#define MAX_QUANTITY 101
int stock[MAX_QUANTITY] = { 0 }; //��� �迭

int MainMenu(void);
void InStockMenu(int stock[]);
void SellMenu(int stock[]);
void StorageMenu(int stock[]);

int main() {
	int menu = MainMenu();
	if (menu == 1) {//�԰�
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

// -------------------------------
// ���� �޴�
// -------------------------------

int MainMenu(void) {
	int menu;
	printf("[���θ��������α׷�]\n");
	printf("���ϴ¸޴��������ϼ���.(1.�԰�, 2.�Ǹ�, 3.��ǰ��Ȳ, 4.����)\n");
	scanf_s("%d", &menu);
	return menu;
}

// -------------------------------
// �԰� �޴�
// -------------------------------

void InStockMenu(int stock[]) {
	int menu;
	int productCount;
	printf("[�԰� �޴�]\n");
	printf("1.��ü ��ǰ �԰� ���� ,2. ���� ��ǰ �Է�\n");

	scanf_s("%d", &menu);

	if (menu == 1) {
		printf("��ü ��ǰ ���� �Է�: ");
		scanf_s("%d", &productCount);

		for (int i = 0; i < productCount; i++) {
			printf("%d�� ��ǰ �԰� ����: ", i + 1);
			scanf_s("%d", &stock[i]);
		}
	}

	else if (menu == 2) {
		int idx, qty;

		printf("�԰��� ��ǰ ��ȣ: ");
		scanf_s("%d", &idx);
		printf("�԰� ����: ");
		scanf_s("%d", &qty);
		stock[idx] += qty;
		printf("%d�� ��ǰ�� %d�� �԰�\n", idx, qty);
	}
	else {
		printf("�߸��� �Է�");
		InStockMenu(stock);
	}
}



// -------------------------------
// �Ǹ� �޴�
// -------------------------------
void SellMenu() {

	int menu;
	int productCount;
	int idx, qty;

	printf("[�Ǹ� �޴�]\n");
	printf("1. ��ü ��ǰ �԰� ���� �Է�, 2. ���� ��ǰ �԰� �Է�\n");
	scanf_s("%d", &menu);

	if (menu == 1) {
		printf("��ü ��ǰ �Ǹ� ���� �Է�: ");
		scanf_s("%d", &productCount);

		for (int i = 0; i < productCount; i++) {
			printf("%d�� ��ǰ �Ǹ� ����: ", i + 1);
			scanf_s("%d", &stock[i]);
		}

		printf("\n�԰� �Ϸ�!\n");
	}
	else if (menu == 2) {
		printf("�Ǹ��� ��ǰ ��ȣ: ");
		scanf_s("%d", &idx);
		printf("�Ǹ� ����: ");
		scanf_s("%d", &qty);

		if (stock[idx] >= qty) {
			stock[idx] -= qty;
			printf("%d�� ��ǰ %d�� �Ǹ�\n", idx, qty);
		}
		else {
			printf("��� ����\n");
		}
		
	}
	else {
		printf("�߸��� �Է�\n");
		SellMenu(stock);
	}
}


// -------------------------------
// ��ǰ ��Ȳ
// -------------------------------
void StorageMenu(int stock[]) {

}
#include <stdio.h>

#define MAX_QUANTITY 101
int stock[MAX_QUANTITY] = { 0 };

int Mainmenu;

int main() {
	int menu = MainMenu();
	if (menu == 1){//입고
		InStockMenu(stock);
	}

	else if (menu == 2) {//판매
		SellMenu(stock);
	}

	else if (menu == 3) {//상품현황
		StorageMenu(stock);
	}

	else if (menu == 4) {//종료
		printf("프로그램 종료");
	}

	else {
		printf("잘못된 입력");
	}
}
int MainMenu() {
	int menu;
	printf("[쇼핑몰관리프로그램]\n");
	printf("원하는메뉴를선택하세요.(1.입고, 2.판매, 3.상품현황, 4.종료)\n");
	scanf_s("%d", &menu);
	return menu;
}
int SellMenu() {

}
int StorageMenu() {

}

int InStockMenu() {
	int menu;
	printf("1.전체 상품 입고 수량 ,2. 개별 상품 입력");

	scanf_s("%d", &menu);

	printf("입고 수량 :");

	for (int i = 0; i < product; i++)
	{
		scanf_s("%d", &in[i]);
	}for (int i = 0; i < product; i++)
	{
		scanf_s("%d", &in[i]);
	}
}
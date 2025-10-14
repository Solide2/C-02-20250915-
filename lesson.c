#include <stdio.h>

#define MAX_QUANTITY 101
int stock[MAX_QUANTITY] = { 0 }; //재고 배열

int MainMenu(void);
void InStockMenu(int stock[]);
void SellMenu(int stock[]);
void StorageMenu(int stock[]);

int main() {
	int menu = MainMenu();
	if (menu == 1) {//입고
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

// -------------------------------
// 메인 메뉴
// -------------------------------

int MainMenu(void) {
	int menu;
	printf("[쇼핑몰관리프로그램]\n");
	printf("원하는메뉴를선택하세요.(1.입고, 2.판매, 3.상품현황, 4.종료)\n");
	scanf_s("%d", &menu);
	return menu;
}

// -------------------------------
// 입고 메뉴
// -------------------------------

void InStockMenu(int stock[]) {
	int menu;
	int productCount;
	printf("[입고 메뉴]\n");
	printf("1.전체 상품 입고 수량 ,2. 개별 상품 입력\n");

	scanf_s("%d", &menu);

	if (menu == 1) {
		printf("전체 상품 개수 입력: ");
		scanf_s("%d", &productCount);

		for (int i = 0; i < productCount; i++) {
			printf("%d번 상품 입고 수량: ", i + 1);
			scanf_s("%d", &stock[i]);
		}
	}

	else if (menu == 2) {
		int idx, qty;

		printf("입고할 상품 번호: ");
		scanf_s("%d", &idx);
		printf("입고 수량: ");
		scanf_s("%d", &qty);
		stock[idx] += qty;
		printf("%d번 상품에 %d개 입고\n", idx, qty);
	}
	else {
		printf("잘못된 입력");
		InStockMenu(stock);
	}
}



// -------------------------------
// 판매 메뉴
// -------------------------------
void SellMenu() {

	int menu;
	int productCount;
	int idx, qty;

	printf("[판매 메뉴]\n");
	printf("1. 전체 상품 입고 수량 입력, 2. 개별 상품 입고 입력\n");
	scanf_s("%d", &menu);

	if (menu == 1) {
		printf("전체 상품 판매 개수 입력: ");
		scanf_s("%d", &productCount);

		for (int i = 0; i < productCount; i++) {
			printf("%d번 상품 판매 수량: ", i + 1);
			scanf_s("%d", &stock[i]);
		}

		printf("\n입고 완료!\n");
	}
	else if (menu == 2) {
		printf("판매할 상품 번호: ");
		scanf_s("%d", &idx);
		printf("판매 수량: ");
		scanf_s("%d", &qty);

		if (stock[idx] >= qty) {
			stock[idx] -= qty;
			printf("%d번 상품 %d개 판매\n", idx, qty);
		}
		else {
			printf("재고 부족\n");
		}
		
	}
	else {
		printf("잘못된 입력\n");
		SellMenu(stock);
	}
}


// -------------------------------
// 상품 현황
// -------------------------------
void StorageMenu(int stock[]) {

}
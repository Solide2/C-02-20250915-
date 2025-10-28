#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 5
#define FILENAME "products.txt"

typedef struct {
    int id;
    char name[50];
    int price;
    int stock;      // 재고수량
    int sold;       // 판매수량
} Product;

Product products[MAX_PRODUCTS];
int productCount = 0;

// 함수 선언
void loadProducts();
void saveProducts();
void addOrUpdateProduct();
void sellProduct();
void showProduct();
void showAllProducts();
void menu();

// ---------------------------
// 메인 함수
// ---------------------------
int main() {
    loadProducts(); // 실행 시 파일에서 데이터 불러오기
    menu();
    return 0;
}

// ---------------------------
// 메뉴 출력 및 실행
// ---------------------------
void menu() {
    int choice;
    while (1) {
        printf("\n===== 쇼핑몰 재고 관리 시스템 =====\n");
        printf("1. 입고\n");
        printf("2. 판매\n");
        printf("3. 개별상품현황\n");
        printf("4. 전체상품현황\n");
        printf("5. 저장하기\n");
        printf("6. 종료하기\n");
        printf("메뉴 선택: ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1: addOrUpdateProduct(); break;
        case 2: sellProduct(); break;
        case 3: showProduct(); break;
        case 4: showAllProducts(); break;
        case 5: saveProducts(); break;
        case 6:
            saveProducts();
            printf("프로그램을 종료합니다.\n");
            return;
        default:
            printf("잘못된 입력입니다.\n");
        }
    }
}

// ---------------------------
// 상품 정보 불러오기
// ---------------------------
void loadProducts() {
    FILE* file = NULL;
    fopen_s(&file, FILENAME, "r");
    if (file == NULL) {
        printf("[알림] 저장된 상품 정보가 없습니다.\n");
        return;
    }

    productCount = 0;
    while (fscanf_s(file, "%d %49s %d %d %d",
        &products[productCount].id,
        products[productCount].name, (unsigned)_countof(products[productCount].name),
        &products[productCount].price,
        &products[productCount].stock,
        &products[productCount].sold) == 5) {
        productCount++;
        if (productCount >= MAX_PRODUCTS) break;
    }

    fclose(file);
    printf("[불러오기 완료] %d개의 상품 정보를 불러왔습니다.\n", productCount);
}

// ---------------------------
// 상품 정보 저장하기
// ---------------------------
void saveProducts() {
    FILE* file = NULL;
    fopen_s(&file, FILENAME, "w");
    if (file == NULL) {
        printf("파일 저장 실패!\n");
        return;
    }

    for (int i = 0; i < productCount; i++) {
        fprintf(file, "%d %s %d %d %d\n",
            products[i].id,
            products[i].name,
            products[i].price,
            products[i].stock,
            products[i].sold);
    }

    fclose(file);
    printf("[저장 완료] 상품 정보가 '%s'에 저장되었습니다.\n", FILENAME);
}

// ---------------------------
// 상품 추가 또는 업데이트 (입고)
// ---------------------------
void addOrUpdateProduct() {
    if (productCount >= MAX_PRODUCTS) {
        printf("[오류] 상품 개수가 5개를 초과할 수 없습니다.\n");
        return;
    }

    int id, found = 0;
    printf("상품 ID 입력: ");
    scanf_s("%d", &id);

    for (int i = 0; i < productCount; i++) {
        if (products[i].id == id) {
            int addStock;
            printf("기존 상품입니다. 입고 수량 추가 입력: ");
            scanf_s("%d", &addStock);
            products[i].stock += addStock;
            printf("입고 완료. 현재 재고: %d\n", products[i].stock);
            found = 1;
            break;
        }
    }

    if (!found) {
        Product newP;
        newP.id = id;
        printf("상품명 입력: ");
        scanf_s("%49s", newP.name, (unsigned)_countof(newP.name));
        printf("상품 가격 입력: ");
        scanf_s("%d", &newP.price);
        printf("입고 수량 입력: ");
        scanf_s("%d", &newP.stock);
        newP.sold = 0;

        products[productCount++] = newP;
        printf("새 상품 등록 완료!\n");
    }
}

// ---------------------------
// 상품 판매 처리
// ---------------------------
void sellProduct() {
    int id, qty;
    printf("판매할 상품 ID 입력: ");
    scanf_s("%d", &id);

    for (int i = 0; i < productCount; i++) {
        if (products[i].id == id) {
            printf("판매 수량 입력: ");
            scanf_s("%d", &qty);
            if (qty > products[i].stock) {
                printf("[오류] 재고가 부족합니다. 현재 재고: %d\n", products[i].stock);
                return;
            }
            products[i].stock -= qty;
            products[i].sold += qty;
            printf("판매 완료! 남은 재고: %d\n", products[i].stock);
            return;
        }
    }

    printf("[오류] 해당 상품 ID를 찾을 수 없습니다.\n");
}

// ---------------------------
// 개별 상품 현황 보기
// ---------------------------
void showProduct() {
    int id;
    printf("조회할 상품 ID 입력: ");
    scanf_s("%d", &id);

    for (int i = 0; i < productCount; i++) {
        if (products[i].id == id) {
            printf("\n[상품 정보]\n");
            printf("ID: %d\n", products[i].id);
            printf("상품명: %s\n", products[i].name);
            printf("가격: %d\n", products[i].price);
            printf("재고: %d\n", products[i].stock);
            printf("판매수량: %d\n", products[i].sold);
            printf("총판매금액: %d\n", products[i].sold * products[i].price);
            return;
        }
    }

    printf("[오류] 해당 상품을 찾을 수 없습니다.\n");
}

// ---------------------------
// 전체 상품 현황 보기
// ---------------------------
void showAllProducts() {
    if (productCount == 0) {
        printf("[알림] 등록된 상품이 없습니다.\n");
        return;
    }

    printf("\n=== 전체 상품 현황 ===\n");
    printf("ID\t상품명\t가격\t재고\t판매량\t총판매금액\n");
    for (int i = 0; i < productCount; i++) {
        printf("%d\t%s\t%d\t%d\t%d\t%d\n",
            products[i].id,
            products[i].name,
            products[i].price,
            products[i].stock,
            products[i].sold,
            products[i].sold * products[i].price);
    }
}

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define PRODUCT 5

typedef struct {
    int ID;
    char name[101];
    int in;         // 입고 수량
    int out;        // 판매 수량
    int remain;     // 남은 수량
    int cost;       // 상품 가격
} Product;

Product items[PRODUCT];   // 상품 리스트

int inall = 0;            // 총 입고량
int sellall = 0;          // 총 판매량

// 함수 선언
int MainMenu();
void InMenu();
void OutMenu();
void oneStatus();
void allStatus();
int ProductID();
void setProductName(int id);
void clearInputBuffer(void);
void saveData();
void loadData();

// Main
int main() {
    int select;
    while (1) {
        select = MainMenu();
        switch (select) {
        case 1: InMenu(); break;
        case 2: OutMenu(); break;
        case 3: oneStatus(); break;
        case 4: allStatus(); break;
        case 5: saveData(); break;
        case 6: loadData(); break;
        case 7: printf("프로그램을 종료합니다.\n"); return 0;
        default: printf("잘못된 선택입니다.\n"); break;
        }
    }
}

void clearInputBuffer(void) {
    while (getchar() != '\n');
}

void setProductName(int id) {
    printf("상품명 입력 : ");
    scanf("%100s", items[id].name);
    clearInputBuffer();
}

int ProductID() {
    int id;
    printf("상품 ID (1 ~ %d) 입력 : ", PRODUCT);

    if (scanf("%d", &id) != 1) {
        printf("숫자를 입력하세요!\n");
        clearInputBuffer();
        return -1;
    }

    if (id <= 0 || id > PRODUCT) {
        printf("잘못된 입력입니다. (1~%d 사이 숫자를 입력하세요)\n", PRODUCT);
        return -1;
    }
    clearInputBuffer();
    return id - 1;
}

int MainMenu() {
    int select;
    printf("\n[쇼핑몰 관리 프로그램]\n");
    printf("1. 입고\n2. 판매\n3. 개별 현황\n4. 전체 현황\n");
    printf("5. 저장하기\n6. 불러오기\n7. 종료\n");
    printf("원하는 메뉴 선택: ");
    scanf("%d", &select);
    clearInputBuffer();
    return select;
}

void InMenu() {
    printf("\n[입고 메뉴]\n");
    int id = ProductID();
    if (id == -1) return;

    if (strlen(items[id].name) == 0) {
        printf("새로운 상품 → 상품명 등록\n");
        setProductName(id);
        items[id].ID = id + 1;
    }

    int qty;
    printf("입고 수량: ");
    scanf("%d", &qty);
    clearInputBuffer();

    if (qty <= 0) {
        printf("0 이하 수량 불가\n");
        return;
    }

    int cost;
    printf("판매 가격: ");
    scanf("%d", &cost);
    clearInputBuffer();

    if (cost <= 0) {
        printf("0 이하 가격 불가\n");
        return;
    }

    items[id].cost = cost;
    items[id].in += qty;
    items[id].remain += qty;
    inall += qty;

    printf("상품 [%s] %d개 입고 완료.\n", items[id].name, qty);
}

void OutMenu() {
    printf("\n[판매 메뉴]\n");
    int id = ProductID();
    if (id == -1) return;

    if (strlen(items[id].name) == 0) {
        printf("등록되지 않은 상품입니다.\n");
        return;
    }

    int qty;
    printf("판매 수량 : ");
    scanf("%d", &qty);
    clearInputBuffer();

    if (qty > items[id].remain) {
        printf("재고 부족! 현재 재고: %d\n", items[id].remain);
        return;
    }

    items[id].out += qty;
    items[id].remain -= qty;
    sellall += qty;
}

void oneStatus() {
    printf("\n[개별 현황]\n");
    int id = ProductID();
    if (id == -1) return;

    printf("상품 ID: %d\n", items[id].ID);
    printf("상품명: %s\n", (strlen(items[id].name) > 0) ? items[id].name : "등록 안됨");
    printf("가격: %d\n", items[id].cost);
    printf("입고: %d | 판매: %d | 재고: %d\n",
        items[id].in, items[id].out, items[id].remain);
}

void allStatus() {
    printf("\n[전체 현황]\n");

    float rate = 0;
    if (inall > 0) rate = (sellall / (float)inall) * 100;

    printf("총 판매량: %d | 판매율: %.2f%%\n", sellall, rate);

    int maxID = -1, minID = -1;
    int maxSales = -1, minSales = 999999;

    for (int i = 0; i < PRODUCT; i++) {
        if (strlen(items[i].name) == 0) continue;

        int sold = items[i].in - items[i].remain;

        if (sold > maxSales) { maxSales = sold; maxID = i; }
        if (sold < minSales) { minSales = sold; minID = i; }

        if (items[i].remain <= 2)
            printf("재고 부족 → ID %d %s (%d개)\n",
                i + 1, items[i].name, items[i].remain);
    }

    if (maxID == -1)
        printf("등록된 상품 없음\n");
    else {
        printf("\n베스트셀러: ID %d %s (%d개)\n",
            maxID + 1, items[maxID].name, maxSales);
        printf("최소 판매: ID %d %s (%d개)\n",
            minID + 1, items[minID].name, minSales);
    }
}

void saveData() {
    FILE* fp = fopen("shopping_data.txt", "w");
    if (!fp) {
        printf("저장 실패\n");
        return;
    }

    for (int i = 0; i < PRODUCT; i++) {
        if (strlen(items[i].name) == 0) continue;

        fprintf(fp, "%d %s %d %d %d %d\n",
            items[i].ID, items[i].name,
            items[i].in, items[i].out,
            items[i].remain, items[i].cost);
    }

    fclose(fp);
    printf("저장 완료\n");
}

void loadData() {
    FILE* fp = fopen("shopping_data.txt", "r");
    if (!fp) {
        printf("불러오기 실패\n");
        return;
    }

    for (int i = 0; i < PRODUCT; i++) {
        if (fscanf(fp, "%d %s %d %d %d %d",
            &items[i].ID, items[i].name,
            &items[i].in, &items[i].out,
            &items[i].remain, &items[i].cost) != 6) break;
    }

    fclose(fp);
    printf("불러오기 완료\n");
}

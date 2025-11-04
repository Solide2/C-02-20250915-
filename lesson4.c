#include <stdio.h>
#define PRODUCT 5


int product;          // 상품 종류 수
int in[PRODUCT];      // 입고 수량
int out[PRODUCT];     // 판매 수량
int outall[PRODUCT];  // 남은 수량
int inall = 0;        // 총 입고량
int sellall = 0;      // 총 판매량
char name[PRODUCT][101];

// 함수
int MainMenu();
void InMenu();
void OutMenu();
void ProductStatus();
void ProductName();

int main() {
    int select;

    while (1) {
        select = MainMenu();

        switch (select) {
        case 1:
            InMenu();
            break;
        case 2:
            OutMenu();
            break;
        case 3:
            ProductStatus();
            break;

        case 4:
            ProductName();
            break;

        case 5:
            printf("프로그램을 종료합니다.\n");
            return 0;
        default:
            printf("잘못된 선택입니다.\n");
            break;
        }
    }
}

// 메인 메뉴
int MainMenu() {
    int select;
    printf("\n[쇼핑몰 관리 프로그램]\n");
    printf("1. 입고\n");
    printf("2. 판매\n");
    printf("3. 상품 현황\n");
    printf("4. 상품명 입력\n");
    printf("5. 종료\n");
    printf("원하는 메뉴 선택: ");
    scanf_s("%d", &select);
    return select;
}

// 입고
void InMenu() {
    int select;
    printf("[입고 메뉴]\n");
    printf("전체 상품 입고수량 입력 1, 개별 상품 입력 2\n");
    printf("원하는 메뉴 선택 :");
    scanf_s("%d", &select);
    if (select == 1)
    {
        printf("전체 상품 입고 수량 입력 :");
        for (int i = 0; i < PRODUCT; i++) {
            scanf_s("%d", &in[i]);
            outall[i] += in[i];
            inall += in[i];
        }
    }

    else if (select == 2) {
        for (int i = 0; i < PRODUCT; i++) {
            printf("%d번 상품 입고 수량 입력: ", i + 1);
            scanf_s("%d", &in[i]);
            outall[i] += in[i];
            inall += in[i];
        }
    }

    else
    {
        printf("잘못된 입력\n");
    }

}

// 판매
void OutMenu() {
    int select;
    printf("[판매 메뉴]\n");
    printf("전체 상품 입고수량 입력 1, 개별 상품 입력 2\n");
    printf("원하는 메뉴 선택 :");
    scanf_s("%d", &select);
    if (select == 1) {
        printf("전체 상품 판매 수량 입력 :");
        for (int i = 0; i < PRODUCT; i++) {
            scanf_s("%d", &out[i]);
            if (out[i] > outall[i]) {
                printf("재고 부족 현재 재고: %d\n", outall[i]);
                out[i] = 0;
            }
            else {
                outall[i] -= out[i];
                sellall += out[i];
            }
        }
    }
    else if (select == 2) {
        for (int i = 0; i < PRODUCT; i++) {
            printf("%d번 상품 판매 수량 입력: ", i + 1);
            scanf_s("%d", &out[i]);
            if (out[i] > outall[i]) {
                printf("재고 부족 현재 재고: %d\n", outall[i]);
                out[i] = 0;
            }
            else {
                outall[i] -= out[i];
                sellall += out[i];
            }
        }
    }

    else {
        printf("잘못된 입력\n");
    }
    printf("판매 처리가 완료되었습니다.\n");
}


// 상품 현황
void ProductStatus() {
    float sellpercent = 0;
    if (inall > 0)
        sellpercent = (sellall / (float)inall) * 100;

    printf("\n[상품 현황]\n");
    printf("재고 수량 :");
    for (int i = 0; i < PRODUCT; i++)
    {
        printf("%d ", outall[i]);
    }
    printf("\n");
    for (int i = 0; i < PRODUCT; i++) {
        if (outall[i] <= 2)
            printf("상품 ID %d %s: 재고 부족 (%d)\n", i + 1, name[i], outall[i]);
    }

    printf("총 판매량: %d\n", sellall);
    printf("판매율: %.2f%%\n", sellpercent);

    int sold[PRODUCT];

    for (int i = 0; i < PRODUCT; i++) {
        sold[i] = in[i] - outall[i];
    }

    int maxID = 0, minID = 0;
    int maxSales = sold[0], minSales = sold[0];

    for (int i = 1; i < PRODUCT; i++) {
        if (sold[i] > maxSales) {
            maxSales = sold[i];
            maxID = i;
        }
        if (sold[i] < minSales) {
            minSales = sold[i];
            minID = i;
        }
    }
    printf("\n가장 많이 판매된 상품 : ID %d, 상품명:%s,  판매량 %d\n", maxID + 1, name[maxID], maxSales);
    printf("가장 적게 판매된 상품 : ID %d, 상품명:%s, 판매량 %d\n", minID + 1, name[minID], minSales);
}

void ProductName() {
    printf("\n[상품명 입력 메뉴]\n");
    for (int i = 0; i < PRODUCT; i++)
    {
        printf("ID %d 상품명 : ", i+1);
        scanf_s("%s", name[i],101);
    }
    printf("상품명 입력이 완료되었습니다.\n");
}

#include <stdio.h>
#include <string.h>
#define PRODUCT 5

int in[PRODUCT];      // 입고 수량
int out[PRODUCT];     // 판매 수량
int outall[PRODUCT];  // 남은 수량
int inall = 0;        // 총 입고량
int sellall = 0;      // 총 판매량
char name[PRODUCT][101]; // 상품명
int productcost[PRODUCT];      //상품 가격


// 함수
int MainMenu();
void InMenu();
void OutMenu();
void oneStatus();
void allStatus();
int ProductID();
void setProductName(int id);
void clearInputBuffer(void);

//메뉴 터널
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
            oneStatus();
            break;
        case 4:
            allStatus();
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
//입력값 지우기
void clearInputBuffer(void) {
    while (getchar() != '\n');
}

//상품 name
void setProductName(int id) {
    printf("상품명 입력 : ");
    scanf_s("%100s", name[id], 101);
    clearInputBuffer();
}

//상품 ID 
int ProductID() {
    int id;
    printf("상품 ID (1 ~ %d) 입력 : ", PRODUCT);

    if (scanf_s("%d", &id) != 1) {
        printf("숫자를 입력하세요!\n");
        clearInputBuffer();
        return -1;
    }

    if (id <= 0 || id > PRODUCT) {
        printf("잘못된 입력입니다. (1~%d 사이 숫자를 입력하세요)\n", PRODUCT);
        return -1;
    }

    return id;
}

//선택 메뉴
int MainMenu() {
    int select;
    printf("\n[쇼핑몰 관리 프로그램]\n");
    printf("1. 입고\n");
    printf("2. 판매\n");
    printf("3. 개별 현황\n");
    printf("4. 전체 현황\n");
    printf("5. 종료\n");
    printf("원하는 메뉴 선택: ");
    scanf_s("%d", &select);
    clearInputBuffer();
    return select;
}

//입고
void InMenu() {
    printf("\n[입고 메뉴]\n");
    int id = ProductID();
    if (id == -1) return;

    if (strlen(name[id]) == 0) {
        printf("상품이 없어 생성\n");
        setProductName(id);
    }

    int qty;
    printf("입고 수량 입력: ");
    scanf_s("%d", &qty);
    clearInputBuffer();

    if (qty <= 0) {
        printf("0 이하의 수량은 입력할 수 없습니다.\n");
        return;
    }
    
    int cost;
    printf("판매 가격 입력: ");
    scanf_s("%d", &cost);
    clearInputBuffer();
    if (cost <= 0) {
        printf("0 이하의 판매 가격은 입력할 수 없습니다.\n");
        return;
    }
    productcost[id] += cost;
    in[id] += qty;
    outall[id] += qty;
    inall += qty;

    printf("상품 [%s] %d개 입고 완료.\n", name[id], qty);
}


//판매
void OutMenu() {
    printf("\n[판매 메뉴]\n");
    int id = ProductID();
    if (id == -1) return;
    //상품ID : (입력)상품ID << 없으면 오류메시지 출력
    if (strlen(name[id]) == 0) {
        printf("상품명이 등록되지 않았습니다.\n");
        return;
    }
    //판매량: (입력)판매수량 입력
    int qty;
    printf("판매 수량 입력: ");
    scanf_s("%d",&qty);
    clearInputBuffer();

    if (qty <= 0) {
        printf("0 이하의 수량은 입력할 수 없습니다.\n");
        return;
    }

    if (qty > outall[id]) {
        printf("재고 부족 현재 재고: %d\n", outall[id]);
        return;
    }
    out[id] += qty;
    outall[id] -= qty;
    sellall += qty;
}


//개별 현황
void oneStatus() {
    //상품 ID를 입력받아 상품정보(상품명, 가격,…)를 출력한다. 
    printf("\n[개별 현황 메뉴]\n");
    int id = ProductID();
    if (id == -1) return;

    printf("\n상품 ID: %d\n", id + 1);
    printf("상품명: %s\n", (strlen(name[id]) > 0) ? name[id] : "등록 안됨");
    printf("상품 가격: %d\n", productcost[id]);
    printf("입고 수량: %d\n", in[id]);
    printf("판매 수량: %d\n", out[id]);
    printf("남은 재고: %d\n", outall[id]);
}


//전체 현황
void allStatus() {
    // 전체현황 메뉴 : 앞서 개발한 상품현황(판매율…)을 출력한다.
    float sellpercent = 0;
    if (inall > 0)
        sellpercent = (sellall / (float)inall) * 100;

    printf("\n[상품 현황]\n");
    printf("재고 수량 :");
    for (int i = 0; i < PRODUCT; i++)
    {
        if (strlen(name[i]) == 0)
            continue;
        printf("%d ", outall[i]);
    }

    printf("\n");
    for (int i = 0; i < PRODUCT; i++) {
        if (strlen(name[i]) == 0)
            continue;
        if (outall[i] <= 2)
            printf("상품 ID %d %s: 재고 부족 (%d)\n", i + 1, name[i], outall[i]);
    }

    printf("총 판매량: %d\n", sellall);
    printf("판매율: %.2f%%\n", sellpercent);

    int sold[PRODUCT];

    for (int i = 0; i < PRODUCT; i++) {
        sold[i] = in[i] - outall[i];
    }

    int maxID = -1, minID = -1;
    int maxSales = 0, minSales = 0;

    for (int i = 0; i < PRODUCT; i++) {
        if (strlen(name[i]) == 0) {
            continue;
        }

        if (maxID == -1) {
            maxID = minID = i;
            maxSales = minSales = sold[i];
            continue;
        }

        if (sold[i] > maxSales) {
            maxSales = sold[i];
            maxID = i;
        }

        if (sold[i] < minSales) {
            minSales = sold[i];
            minID = i;
        }
    }
    if (maxID == -1) {
        printf("등록된 상품이 없습니다.\n");
    }
    else if (maxSales == 0){
        printf("판매된 상품이 없음\n");
    }
    else
    {
        printf("\n가장 많이 판매된 상품 : ID %d, 상품명:%s,  판매량 %d\n", maxID + 1, name[maxID], maxSales);
        printf("가장 적게 판매된 상품 : ID %d, 상품명:%s, 판매량 %d\n", minID + 1, name[minID], minSales);
    }
}

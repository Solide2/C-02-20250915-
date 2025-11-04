#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define PRODUCT 5


int in[PRODUCT];                  // 입고 수량
int out[PRODUCT];                 // 판매 수량
int outall[PRODUCT];              // 남은 수량
int inall = 0;                    // 총 입고량
int sellall = 0;                  // 총 판매량
char name[PRODUCT][101];          // 상품명
int productcost[PRODUCT];         //상품 가격
int ID[PRODUCT];                  //상품 ID
int index;                        //인덱스

// 함수
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
            saveData();
            break;
        case 6:
            loadData();
            break;
        case 7:
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

//상품 이름
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
    index = id - 1;
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
    printf("5. 저장하기\n");
    printf("6. 불러오기\n");
    printf("7. 종료\n");
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

    if (strlen(name[index]) == 0) {
        printf("상품이 없어 생성\n");
        setProductName(index);
        ID[index] = id;
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
    productcost[index] += cost;
    in[index] += qty;
    outall[index] += qty;
    inall += qty;

    printf("상품 [%s] %d개 입고 완료.\n", name[index], qty);
}


//판매
void OutMenu() {
    printf("\n[판매 메뉴]\n");
    int id = ProductID();
    if (id == -1) return;
    
    //상품ID : (입력)상품ID << 없으면 오류메시지 출력
    if (strlen(name[index]) == 0) {
        printf("상품명이 등록되지 않았습니다.\n");
        return;
    }
    //판매량: (입력)판매수량 입력
    int qty;
    printf("판매 수량 입력: ");
    scanf_s("%d",&qty);
    clearInputBuffer();

    if (strlen(name[index]) == 0) {
        printf("상품명이 등록되지 않았습니다.\n");
        return;
    }

    if (qty > outall[index]) {
        printf("재고 부족 현재 재고: %d\n", outall[index]);
        return;
    }

    out[index] += qty;
    outall[index] -= qty;
    sellall += qty;
}


//개별 현황
void oneStatus() {
    //상품 ID를 입력받아 상품정보(상품명, 가격,…)를 출력한다. 
    printf("\n[개별 현황 메뉴]\n");
    int id = ProductID();
    if (id == -1) return;


    printf("\n상품 ID: %d\n", id);
    printf("상품명: %s\n", (strlen(name[index]) > 0) ? name[index] : "등록 안됨");
    printf("상품 가격: %d\n", productcost[index]);
    printf("입고 수량: %d\n", in[index]);
    printf("판매 수량: %d\n", out[index]);
    printf("남은 재고: %d\n", outall[index]);
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

//저장
void saveData() {
    FILE* fp;
    fp = fopen("shopping_data.txt", "w");
    if (fp == NULL) {
        printf("파일 저장 실패\n");
        return;
    }
    for (int i = 0; i < PRODUCT; i++)
    {
        if (strlen(name[i]) == 0)
            continue;
        for (int j = 0; j < strlen(name[i]); j++) {
            if (name[i][j] == ' ')
                name[i][j] = '_';
        }

        fprintf(fp, "%d %s %d %d %d %d\n",ID[i] ,name[i], in[i], out[i], outall[i], productcost[i]);
    }
    fclose(fp);
    printf("\n저장 완료\n");
}

//불러오기
void loadData() {
    FILE* fp;
    fp = fopen("shopping_data.txt", "r");
    if (fp == NULL) {
        printf("파일 열기 실패\n");
        return;
    }

    for (int i = 0; i < PRODUCT; i++) {
        if (fscanf(fp, "%d %s %d %d %d %d",&ID[i], name[i], &in[i], &out[i], &outall[i], &productcost[i]) != 6) {
            break;
        }
        // 이름에서 '_'를 공백으로 바꾸기
        for (int j = 0; j < strlen(name[i]); j++) { 
            if (name[i][j] == '_') 
                name[i][j] = ' '; 
        }
    }
    fclose(fp);
    printf("\n불러오기 완료\n");

}

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
    int stock;      // ������
    int sold;       // �Ǹż���
} Product;

Product products[MAX_PRODUCTS];
int productCount = 0;

// �Լ� ����
void loadProducts();
void saveProducts();
void addOrUpdateProduct();
void sellProduct();
void showProduct();
void showAllProducts();
void menu();

// ---------------------------
// ���� �Լ�
// ---------------------------
int main() {
    loadProducts(); // ���� �� ���Ͽ��� ������ �ҷ�����
    menu();
    return 0;
}

// ---------------------------
// �޴� ��� �� ����
// ---------------------------
void menu() {
    int choice;
    while (1) {
        printf("\n===== ���θ� ��� ���� �ý��� =====\n");
        printf("1. �԰�\n");
        printf("2. �Ǹ�\n");
        printf("3. ������ǰ��Ȳ\n");
        printf("4. ��ü��ǰ��Ȳ\n");
        printf("5. �����ϱ�\n");
        printf("6. �����ϱ�\n");
        printf("�޴� ����: ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1: addOrUpdateProduct(); break;
        case 2: sellProduct(); break;
        case 3: showProduct(); break;
        case 4: showAllProducts(); break;
        case 5: saveProducts(); break;
        case 6:
            saveProducts();
            printf("���α׷��� �����մϴ�.\n");
            return;
        default:
            printf("�߸��� �Է��Դϴ�.\n");
        }
    }
}

// ---------------------------
// ��ǰ ���� �ҷ�����
// ---------------------------
void loadProducts() {
    FILE* file = NULL;
    fopen_s(&file, FILENAME, "r");
    if (file == NULL) {
        printf("[�˸�] ����� ��ǰ ������ �����ϴ�.\n");
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
    printf("[�ҷ����� �Ϸ�] %d���� ��ǰ ������ �ҷ��Խ��ϴ�.\n", productCount);
}

// ---------------------------
// ��ǰ ���� �����ϱ�
// ---------------------------
void saveProducts() {
    FILE* file = NULL;
    fopen_s(&file, FILENAME, "w");
    if (file == NULL) {
        printf("���� ���� ����!\n");
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
    printf("[���� �Ϸ�] ��ǰ ������ '%s'�� ����Ǿ����ϴ�.\n", FILENAME);
}

// ---------------------------
// ��ǰ �߰� �Ǵ� ������Ʈ (�԰�)
// ---------------------------
void addOrUpdateProduct() {
    if (productCount >= MAX_PRODUCTS) {
        printf("[����] ��ǰ ������ 5���� �ʰ��� �� �����ϴ�.\n");
        return;
    }

    int id, found = 0;
    printf("��ǰ ID �Է�: ");
    scanf_s("%d", &id);

    for (int i = 0; i < productCount; i++) {
        if (products[i].id == id) {
            int addStock;
            printf("���� ��ǰ�Դϴ�. �԰� ���� �߰� �Է�: ");
            scanf_s("%d", &addStock);
            products[i].stock += addStock;
            printf("�԰� �Ϸ�. ���� ���: %d\n", products[i].stock);
            found = 1;
            break;
        }
    }

    if (!found) {
        Product newP;
        newP.id = id;
        printf("��ǰ�� �Է�: ");
        scanf_s("%49s", newP.name, (unsigned)_countof(newP.name));
        printf("��ǰ ���� �Է�: ");
        scanf_s("%d", &newP.price);
        printf("�԰� ���� �Է�: ");
        scanf_s("%d", &newP.stock);
        newP.sold = 0;

        products[productCount++] = newP;
        printf("�� ��ǰ ��� �Ϸ�!\n");
    }
}

// ---------------------------
// ��ǰ �Ǹ� ó��
// ---------------------------
void sellProduct() {
    int id, qty;
    printf("�Ǹ��� ��ǰ ID �Է�: ");
    scanf_s("%d", &id);

    for (int i = 0; i < productCount; i++) {
        if (products[i].id == id) {
            printf("�Ǹ� ���� �Է�: ");
            scanf_s("%d", &qty);
            if (qty > products[i].stock) {
                printf("[����] ��� �����մϴ�. ���� ���: %d\n", products[i].stock);
                return;
            }
            products[i].stock -= qty;
            products[i].sold += qty;
            printf("�Ǹ� �Ϸ�! ���� ���: %d\n", products[i].stock);
            return;
        }
    }

    printf("[����] �ش� ��ǰ ID�� ã�� �� �����ϴ�.\n");
}

// ---------------------------
// ���� ��ǰ ��Ȳ ����
// ---------------------------
void showProduct() {
    int id;
    printf("��ȸ�� ��ǰ ID �Է�: ");
    scanf_s("%d", &id);

    for (int i = 0; i < productCount; i++) {
        if (products[i].id == id) {
            printf("\n[��ǰ ����]\n");
            printf("ID: %d\n", products[i].id);
            printf("��ǰ��: %s\n", products[i].name);
            printf("����: %d\n", products[i].price);
            printf("���: %d\n", products[i].stock);
            printf("�Ǹż���: %d\n", products[i].sold);
            printf("���Ǹűݾ�: %d\n", products[i].sold * products[i].price);
            return;
        }
    }

    printf("[����] �ش� ��ǰ�� ã�� �� �����ϴ�.\n");
}

// ---------------------------
// ��ü ��ǰ ��Ȳ ����
// ---------------------------
void showAllProducts() {
    if (productCount == 0) {
        printf("[�˸�] ��ϵ� ��ǰ�� �����ϴ�.\n");
        return;
    }

    printf("\n=== ��ü ��ǰ ��Ȳ ===\n");
    printf("ID\t��ǰ��\t����\t���\t�Ǹŷ�\t���Ǹűݾ�\n");
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

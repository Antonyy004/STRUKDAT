#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10 

struct Node {
    int data;
    struct Node* next;
};

struct Stack {
    struct Node* top;
    int count;
};

void createStack(struct Stack *stack) {
    stack->top = NULL;
    stack->count = 0;
}

int push(struct Stack *stack, int data) {
    if (isFull(stack)) { 
        return 0;
    }
    struct Node* newPtr = (struct Node*)malloc(sizeof(struct Node));  
    if (newPtr == NULL) {
        printf("Gagal mengalokasikan memori.\n");
        return 0;
    }
    newPtr->data = data;
    newPtr->next = stack->top;
    stack->top = newPtr;
    stack->count++;
    return 1;
}

int pop(struct Stack *stack, int *dataOut) {
    if (isEmpty(stack)) { 
        return 0;
    }
    struct Node* dltPtr = stack->top;
    *dataOut = stack->top->data;
    stack->top = stack->top->next;
    stack->count--;
    free(dltPtr); 
    return 1;
}

int stackTop(struct Stack *stack, int *dataOut) {
    if (isEmpty(stack)) {  
        return 0;
    }
    *dataOut = stack->top->data;
    return 1;
}

int isEmpty(struct Stack *stack) {
    return stack->top == NULL;
}

int isFull(struct Stack *stack) {
    return stack->count >= MAX_SIZE;
}

int stackCount(struct Stack *stack) {
    return stack->count;
}

void destroyStack(struct Stack *stack) {
    while (stack->top != NULL) {
        struct Node* temp = stack->top;
        stack->top = stack->top->next;
        free(temp);
    }
    stack->count = 0;
}

void displayStack(struct Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack kosong.\n");
    } else {
        struct Node* current = stack->top;
        printf("Isi stack (dari atas ke bawah): ");
        while (current != NULL) {
            printf("%d ", current->data);
            current = current->next;
        }
        printf("\n");
    }
}

void clearScreen() {
        system("cls");  
}

int main() {
    struct Stack stack;
    createStack(&stack);
    int choice;
    int value;

    do {
        clearScreen();
        printf("\nMenu:\n");
        printf("1. Push (Tambah elemen)\n");
        printf("2. Pop (Hapus elemen teratas)\n");
        printf("3. Top (Lihat elemen teratas)\n");
        printf("4. Count (Jumlah elemen dalam stack)\n");
        printf("5. Display Stack (Lihat seluruh elemen dalam stack)\n");
        printf("6. Destroy (Hapus semua elemen dalam stack)\n");
        printf("7. Keluar\n");
        printf("Pilih operasi: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Masukkan nilai untuk push: ");
                scanf("%d", &value);
                if (push(&stack, value)) {
                    printf("Elemen %d ditambahkan ke stack.\n", value);
                } else {
                    printf("Stack penuh, tidak bisa menambah elemen.\n");
                }
                break;

            case 2:
                if (pop(&stack, &value)) {
                    printf("Elemen %d dihapus dari stack.\n", value);
                } else {
                    printf("Stack kosong, tidak ada elemen untuk dihapus.\n");
                }
                break;

            case 3:
                if (stackTop(&stack, &value)) {
                    printf("Elemen teratas: %d\n", value);
                } else {
                    printf("Stack kosong.\n");
                }
                break;

            case 4:
                printf("Jumlah elemen dalam stack: %d\n", stackCount(&stack));
                break;

            case 5:
                displayStack(&stack);
                break;

            case 6:
                destroyStack(&stack);
                printf("Semua elemen dihapus dari stack.\n");
                break;

            case 7:
                printf("Keluar dari program.\n");
                break;

            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
        printf("Tekan enter untuk melanjutkan...");
        getchar();
        getchar();
    } while (choice != 7);

    return 0;
}

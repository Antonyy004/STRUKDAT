#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};
typedef struct node node;

void tambahAwal(node **head);
void tambahData(node **head);
void tambahAkhir(node **head);
void tranverse(node *head);
void hapusData(node **head);
void hapusAwal(node **head);
void hapusAkhir(node **head);
int hitungJumlah(node *head);
int hitungPenjumlahan(node *head);
int cariData(node *head, int data);

int main() {
    node *head = NULL;
    char pilih;

    do {
        system("cls");
        printf("Masukkan pilihan\n");
        printf("1. Tambah data di awal\n");
        printf("2. Tambah data di tengah list\n");
        printf("3. Tambah data di akhir list\n");
        printf("4. Cetak isi list\n");
        printf("5. Hapus data di tengah list\n");
        printf("6. Hapus data di awal list\n");
        printf("7. Hapus data di akhir list\n");
        printf("8. Hitung jumlah elemen dalam list\n");
        printf("9. Hitung penjumlahan elemen dalam list\n");
        printf("0. Cari data dalam list\n");
        printf("MASUKKAN PILIHAN (tekan q untuk keluar) : ");
        fflush(stdin);
        scanf("%c", &pilih);

        if (pilih == '1')
            tambahAwal(&head);
        else if (pilih == '2')
            tambahData(&head);
        else if (pilih == '3')
            tambahAkhir(&head);
        else if (pilih == '4') {
            tranverse(head);
            getchar();
        }
        else if (pilih == '5')
            hapusData(&head);
        else if (pilih == '6')
            hapusAwal(&head);
        else if (pilih == '7')
            hapusAkhir(&head);
        else if (pilih == '8') {
            int jumlah = hitungJumlah(head);
            printf("\nJumlah elemen dalam circular linked list: %d", jumlah);
            getchar();
        }
        else if (pilih == '9') {
            int total = hitungPenjumlahan(head);
            printf("\nPenjumlahan elemen dalam circular linked list: %d", total);
            getchar();
        }
        else if (pilih == '0') {
            int data;
            system("cls");
            printf("Masukkan data yang ingin dicari: ");
            fflush(stdin);
            scanf("%d", &data);
            int posisi = cariData(head, data);
            if (posisi != -1) {
                printf("\nData %d ditemukan di posisi %d", data, posisi);
            } else {
                printf("\nData %d tidak ditemukan dalam circular linked list", data);
            }
            getchar();
        }

    } while (pilih != 'q');

    return 0;
}

void tambahAwal(node **head) {
    int bil;
    node *pNew;
    system("cls");
    fflush(stdin);
    printf("Masukkan bilangan : ");
    scanf("%d", &bil);
    pNew = (node *)malloc(sizeof(node));
    if (pNew != NULL) {
        pNew->data = bil;
        if (*head == NULL) { // If the list is empty
            pNew->next = pNew; // Point to itself
            *head = pNew;
        } else {
            node *temp = *head;
            while (temp->next != *head) { // Find the last node
                temp = temp->next;
            }
            temp->next = pNew; // Link last node to new node
            pNew->next = *head; // Point new node to head
            *head = pNew; // Update head
        }
    } else {
        printf("Alokasi memori gagal");
        getchar();
    }
}

void tambahData(node **head) {
    int pos, bil;
    node *pNew, *pCur;
    system("cls");
    tranverse(*head);
    printf("\nPosisi penyisipan setelah data bernilai : ");
    fflush(stdin);
    scanf("%d", &pos);
    printf("\nBilangan : ");
    fflush(stdin);
    scanf("%d", &bil);
    
    pCur = *head;
    if (pCur == NULL) {
        printf("List kosong. Tambahkan data terlebih dahulu.\n");
        getchar();
        return;
    }

    do {
        if (pCur->data == pos) {
            break;
        }
        pCur = pCur->next;
    } while (pCur != *head);

    pNew = (node *)malloc(sizeof(node));
    if (pCur == *head && pCur->data != pos) {
        printf("\nNode tidak ditemukan");
        getchar();
        return;
    } else if (pNew == NULL) {
        printf("\nAlokasi memori gagal");
        getchar();
        return;
    } else {
        pNew->data = bil;
        pNew->next = pCur->next;
        pCur->next = pNew;
    }
}

void tranverse(node *head) {
    node *pWalker;
    system("cls");
    if (head == NULL) {
        printf("Linked list kosong.\n");
        return;
    }
    pWalker = head;
    do {
        printf("%d\t", pWalker->data);
        pWalker = pWalker->next;
    } while (pWalker != head);
    printf(" -> ... (back to head)\n");
}

void tambahAkhir(node **head) {
    int bil;
    node *pNew, *pCur;
    system("cls");
    tranverse(*head);
    printf("\nBilangan yang ditambahkan di akhir list: ");
    fflush(stdin);
    scanf("%d", &bil);
    pCur = *head;
    
    pNew = (node *)malloc(sizeof(node));
    if (pNew == NULL) {
        printf("\nAlokasi memori gagal");
        getchar();
        return;
    }
    
    pNew->data = bil;
    
    if (pCur == NULL) { // If the list is empty
        pNew->next = pNew; // Point to itself
        *head = pNew;
    } else {
        while (pCur->next != *head) { // Find the last node
            pCur = pCur->next;
        }
        pCur->next = pNew; // Link last node to new node
        pNew->next = *head; // Point new node to head
    }
}

void hapusData(node **head) {
    int pos;
    node *pCur, *pTemp;
    system("cls");
    tranverse(*head);
    printf("\nData yang akan dihapus pada circular linked list : ");
    fflush(stdin);
    scanf("%d", &pos);
    
    pCur = *head;
    if (pCur != NULL && pCur->data == pos) {
        hapusAwal(head);
        return;
    }

    while (pCur->next != *head && pCur->next != NULL && pCur->next->data != pos) {
        pCur = pCur->next;
    }
    
    if (pCur->next == *head) {
        printf("\nNode tidak ditemukan");
        getchar();
    } else {
        pTemp = pCur->next;
        pCur->next = pTemp->next;
        free(pTemp);
    }
}

void hapusAwal(node **head) {
    if (*head == NULL) {
        printf("\nCircular linked list kosong.");
        getchar();
        return;
    }
    node *temp = *head;
    
    if (temp->next == *head) { // Only one node in the list
        free(temp);
        *head = NULL;
        printf("\nNode pertama telah dihapus.");
        getchar();
        return;
    }

    node *last = *head;
    while (last->next != *head) {
        last = last->next;
    }

    *head = (*head)->next; // Move head to next node
    last->next = *head; // Last node points to new head
    free(temp);
    printf("\nNode pertama telah dihapus.");
    getchar();
}

void hapusAkhir(node **head) {
    if (*head == NULL) {
        printf("\nCircular linked list kosong.");
        getchar();
        return;
    }
    if ((*head)->next == *head) {
        free(*head);
        *head = NULL;
        printf("\nNode terakhir telah dihapus.");
        getchar();
        return;
    }
    
    node *pCur = *head;
    while (pCur->next->next != *head) {
        pCur = pCur->next;
    }
    
    free(pCur->next);
    pCur->next = *head; // Point last node to head
    printf("\nNode terakhir telah dihapus.");
    getchar();
}

int hitungJumlah(node *head) {
    int count = 0;
    node *pWalker = head;
    if (pWalker == NULL) {
        return count;
    }
    do {
        count++;
        pWalker = pWalker->next;
    } while (pWalker != head);
    return count;
}

int hitungPenjumlahan(node *head) {
    int total = 0;
    node *pWalker = head;
    if (pWalker == NULL) {
        return total;
    }
    do {
        total += pWalker->data;
        pWalker = pWalker->next;
    } while (pWalker != head);
    return total;
}

int cariData(node *head, int target) {
    node *pCur = head;
    int posisi = 1;
    if (pCur == NULL) {
        return -1; // List is empty
    }
    do {
        if (pCur->data == target) {
            return posisi;
        }
        pCur = pCur->next;
        posisi++;
    } while (pCur != head);
    
    return -1; // Data not found
}

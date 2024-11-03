#include <stdio.h>
#include <conio.h>
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
    node *head;
    char pilih;
    head = NULL;

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
            getch();
        }
        else if (pilih == '5')
            hapusData(&head);
        else if (pilih == '6')
            hapusAwal(&head);
        else if (pilih == '7')
            hapusAkhir(&head);
        else if (pilih == '8') {
            int jumlah = hitungJumlah(head);
            printf("\nJumlah elemen dalam linked list: %d", jumlah);
            getch();
        }
        else if (pilih == '9') {
            int total = hitungPenjumlahan(head);
            printf("\nPenjumlahan elemen dalam linked list: %d", total);
            getch();
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
                printf("\nData %d tidak ditemukan dalam linked list", data);
            }
            getch();
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
    fflush(stdin);
    scanf("%d", &bil);
    pNew = (node *)malloc(sizeof(node));
    if (pNew != NULL) {
        pNew->data = bil;
        pNew->next = *head;
        *head = pNew;
    }
    else {
        printf("Alokasi memori gagal");
        getch();
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
    while (pCur != NULL && pCur->data != pos) {
        pCur = pCur->next;
    }
    pNew = (node *)malloc(sizeof(node));
    if (pCur == NULL) {
        printf("\nNode tidak ditemukan");
        getch();
    }
    else if (pNew == NULL) {
        printf("\nAlokasi memori gagal");
        getch();
    }
    else {
        pNew->data = bil;
        pNew->next = pCur->next;
        pCur->next = pNew;
    }
}

void tranverse(node *head) {
    node *pWalker;
    system("cls");
    pWalker = head;
    while (pWalker != NULL) {
        printf("%d\t", pWalker->data);
        pWalker = pWalker->next;
        printf(" -> ");
    }
    printf("NULL");
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
    if (pCur == NULL) {
        // Jika linked list kosong, tambahkan node di awal
        tambahAwal(head);
        return;
    }
    while (pCur->next != NULL) {
        pCur = pCur->next;
    }
    pNew = (node *)malloc(sizeof(node));
    if (pNew == NULL) {
        printf("\nAlokasi memori gagal");
        getch();
    }
    else {
        pNew->data = bil;
        pNew->next = NULL;
        pCur->next = pNew;
    }
}

void hapusData(node **head) {
    int pos;
    node *pCur, *pTemp;
    system("cls");
    tranverse(*head);
    printf("\nData yang akan dihapus pada linked list : ");
    fflush(stdin);
    scanf("%d", &pos);
    pCur = *head;
    if (pCur != NULL && pCur->data == pos) {
        hapusAwal(head);
        return;
    }
    while (pCur != NULL && pCur->next != NULL && pCur->next->data != pos) {
        pCur = pCur->next;
    }
    if (pCur == NULL || pCur->next == NULL) {
        printf("\nNode tidak ditemukan");
        getch();
    } else {
        pTemp = pCur->next;
        pCur->next = pTemp->next;
        free(pTemp);
    }
}

void hapusAwal(node **head) {
    if (*head == NULL) {
        printf("\nLinked list kosong.");
        getch();
        return;
    }
    node *temp = *head;
    *head = (*head)->next;
    free(temp);
    printf("\nNode pertama telah dihapus.");
    getch();
}

void hapusAkhir(node **head) {
    if (*head == NULL) {
        printf("\nLinked list kosong.");
        getch();
        return;
    }
    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        printf("\nNode terakhir telah dihapus.");
        getch();
        return;
    }
    node *pCur = *head;
    while (pCur->next->next != NULL) {
        pCur = pCur->next;
    }
    free(pCur->next);
    pCur->next = NULL;
    printf("\nNode terakhir telah dihapus.");
    getch();
}

int hitungJumlah(node *head) {
    int count = 0;
    node *pWalker = head;
    while (pWalker != NULL) {
        count++;
        pWalker = pWalker->next;
    }
    return count;
}

int hitungPenjumlahan(node *head) {
    int total = 0;
    node *pWalker = head;
    while (pWalker != NULL) {
        total += pWalker->data;
        pWalker = pWalker->next;
    }
    return total;
}

int cariData(node *head, int target) {
    node *pCur = head;
    int posisi = 1;
    while (pCur != NULL && pCur->data != target) {
        pCur = pCur->next;
        posisi++;
    }
    if (pCur != NULL) {
        return posisi;
    } else {
        return -1;
    }
}

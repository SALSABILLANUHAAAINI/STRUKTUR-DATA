#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

//========================================================
//membuat struct
struct node {
    int data;
    struct node *right;
    struct node *left;
};

typedef struct node node;

//node *createNode(void);
void tambahAwal(node **head);
void tambahData(node **head);
void tambahAkhir(node **head);
void hapusAwal(node **head);
void hapusTengah(node **head);
void hapusAkhir(node **head);
void cariData(node *head);//sigle pointer : karena hanya 1 perintah
void jumlahData(node *head);
void totalJumlahData(node *head);
void tranverse(node *head);//mengunjungi semua node yang ada pada list dari head sampai node terakhir

//========================================================
//Tampilan Terminal
int main()
{
    node *head;
    char pilih;
    head = NULL;

    do {
        system("cls"); //membersihkan terminal sebelum opera running selanjutnya
        printf("Masukkan pilihan:\n");
        printf("1. Tambah data di awal\n");
        printf("2. Tambah data di tengah list\n");
        printf("3. Tambah data di akhir\n");
        printf("4. Hapus data di awal\n");
        printf("5. Hapus data di tengah\n");
        printf("6. Hapus data di akhir\n");
        printf("7. Cari data dalam list\n");
        printf("8. Jumlah data di list\n");
        printf("9. Total penjumlahan data di list\n");
        printf("0. Cetak isi list\n");
        printf("MASUKKAN PILIHAN (tekan E untuk keluar): ");
        fflush(stdin);
        scanf("%c", &pilih);

        if (pilih == '1')
            tambahAwal(&head);
        else if (pilih == '2')
            tambahData(&head);
        else if (pilih == '3')
            tambahAkhir(&head);
        else if (pilih == '4')
            hapusAwal(&head);
        else if (pilih == '5')
            hapusTengah(&head);
        else if (pilih == '6')
            hapusAkhir(&head);
        else if (pilih == '7')
            cariData(head);
        else if (pilih == '8')
            jumlahData(head);
        else if (pilih == '9')
            totalJumlahData(head);
        else if (pilih == '0') {
            tranverse(head);
            getch();
        }
    } while (pilih != 'E');
    
    return 0;
}

//========================================================
//TambahDataDiawal
void tambahAwal(node **head){
    int bil;
    node *pNew;

    system("cls");
    fflush(stdin);
    printf("Masukkan bilangan untuk node pertama: ");
    fflush(stdin);
    scanf("%d", &bil);
    pNew = (node *)malloc(sizeof(node));

  if (pNew != NULL){
  	  pNew->data = bil;
      pNew->left = NULL;
      //add before first logical node or to an empty list
	  pNew -> right= *head;
      *head = pNew;
      if (*head != NULL)
      (*head) -> left = pNew;
      
    } else {
        printf("Alokasi memori gagal");
        getch();
    }
    
    *head = pNew;
}

//========================================================
//TambahDataTengah
void tambahData(node **head){
    int pos, bil;
    node *pNew, *pCur;

    system("cls");
    tranverse(*head); // Asumsi fungsi tranverse sudah didefinisikan
    printf("\nposisi penyisipan setelah data bernilai : ");
    fflush(stdin);
    scanf("%d", &pos);
    printf("\nmasukan bilangan yang ingin dimasukan : ");
    fflush(stdin);
    scanf("%d", &bil);

    // Mencari posisi untuk penyisipan
    pCur = *head;
    while (pCur != NULL && pCur->data != pos) {
        pCur = pCur->right;
    }

    if (pCur == NULL) { // Jika data posisi tidak ditemukan
        printf("\n node tidak ditemukan");
        getch();
        return;
    }

    // Alokasi memori untuk node baru
    pNew = (node *)malloc(sizeof(node));
    if (pNew == NULL) { // Jika alokasi gagal
        printf("\n alokasi memori gagal");
        getch();
        return;
    }

    // Inisialisasi node baru
    pNew->data = bil;
    pNew->left = pCur;
    pNew->right = pCur->right;

    // Update koneksi
    if (pCur->right != NULL) {
        pCur->right->left = pNew;
    }
    pCur->right = pNew;
}

//========================================================
//TambahDataAkhir
void tambahAkhir(node **head) {
    int bil;
    node *pNew, *pCur;

    system("cls");
    printf("Masukkan bilangan untuk node terakhir: ");
    scanf("%d", &bil);

    pNew = (node *)malloc(sizeof(node));
    if (pNew == NULL) {
        printf("Alokasi memori gagal\n");
        getch();
        return;
    }

    pNew->data = bil;
    pNew->right = NULL;
    pNew->left = NULL;

    if (*head == NULL) {
        *head = pNew;
    } else {
        pCur = *head;
        while (pCur->right != NULL) {
            pCur = pCur->right;
        }
        pCur->right = pNew;
        pNew->left = pCur;
    }
}

//========================================================
//HapusAwal
void hapusAwal(node **head) {
    node *pCur;
    if (*head == NULL) {
        printf("List kosong!\n");
        getch();
        return;
    }
    pCur = *head;
    *head = (*head)->right;
      (*head)->left = NULL;
    free(pCur);
    printf("\nData di awal dihapus.\n");
    getch();
}

//========================================================
//HapusTengah
void hapusTengah(node **head){
    int bil;
    node *pCur;

    system("cls");
    tranverse(*head);
    printf("\nMasukan bilangan yang ingin dihapus: ");
    scanf("%d", &bil);

    pCur = *head;
    while (pCur != NULL && pCur->data != bil) {
        pCur = pCur->right;
    }

    if (pCur == NULL) {
        printf("Data tidak ditemukan");
        getch();
    } else {
        if (pCur->right != NULL) {
            pCur->right->left = pCur->left;
        }
        if (pCur->left != NULL) {
            pCur->left->right = pCur->right;
        } else {
            *head = pCur->right;
        }
        free(pCur);
        printf("Data dengan nilai %d berhasil dihapus.\n", bil);
        getch();
    }
}
//========================================================
//HapusAkhir
void hapusAkhir( node **head) {
     node *pCur;

    // Cek apakah list kosong
    if (*head == NULL) {
        printf("List kosong!\n");
        return;
    }

    pCur = *head;

    // Menemukan node terakhir
    while (pCur->right != NULL) {
        pCur = pCur->right;
    }

    // Jika ada lebih dari satu node
    if (pCur->left != NULL) {
        pCur->left->right = NULL;
    } else {
        // Jika hanya satu node, hapus head
        *head = NULL;
    }

    free(pCur);
    printf("Data di akhir dihapus.\n");
    getch();
}

    

//========================================================
//Caridata
void cariData(node *head) {
    int bil, found = 0;
    node *pCur;

    system("cls");
    printf("Masukkan data yang dicari: ");
    fflush(stdin);
    scanf("%d", &bil);

    // Memeriksa apakah list kosong
    if (head == NULL) {
        printf("List kosong!\n");
        getch();
        return; 
    }

    pCur = head; 
    while (pCur != NULL) { // Selama pCur tidak NULL
        if (pCur->data == bil) { // Jika data ditemukan
            printf("Data %d ditemukan.\n", bil);
            found = 1;
            break; // Keluar dari loop
        }
        pCur = pCur->right; // Pindah ke node berikutnya
    }

    if (!found) {
        printf("Data tidak ditemukan.\n");
    }
    getch();
}

//========================================================
//JumlahData
void jumlahData(node *head) {
    int count = 0;
    node *pCur;
    

    if (head == NULL) {
        printf("List kosong!\n");
        getch();
        return; 
    }

    pCur = head; 

    while (pCur != NULL) {
        count++;
        pCur = pCur->right;
    }

    printf("Jumlah data di list: %d\n", count);
    getch();
}

//========================================================
//TotalData
void totalJumlahData(node *head) {
    int sum = 0;
    node *pCur;
    
     // Memeriksa apakah list kosong
    if (head == NULL) {
        printf("List kosong!\n");
        getch();
        return; // Kembali setelah menampilkan pesan
    }

    pCur = head;
    

    while (pCur != NULL) {
        sum += pCur->data;
        pCur = pCur->right;
    }

    printf("Total penjumlahan data di list: %d\n", sum);
    getch();
}

//========================================================
///mengunjungi semua node yang ada pada list dari head sampai node terakhir
void tranverse(node *head){
   //traverse a linked list
	node *pWalker;

   system("cls");
	pWalker = head;
	while (pWalker != NULL){
   	printf("%d", pWalker->data);
   	pWalker = pWalker->right;
      printf("<->");
	}
   printf("NULL");
}

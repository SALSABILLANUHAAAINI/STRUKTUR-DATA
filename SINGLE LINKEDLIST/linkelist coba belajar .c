#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

//========================================================

struct node {
    int data;
    struct node *next;
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
    printf("Masukkan bilangan: ");
    fflush(stdin);
    scanf("%d", &bil);
    pNew = (node *)malloc(sizeof(node));

  if (pNew != NULL){
  	  pNew->data = bil;
      pNew->next = NULL;
      //add before first logical node or to an empty list
	  pNew -> next = *head;
      *head = pNew;
  
    } else {
        printf("Alokasi memori gagal");
        getch();
    }
}

//========================================================
//TambahDataTengah
void tambahData(node **head){
  int pos, bil;
  node *pNew, *pCur;

  system("cls");
  tranverse(*head);
  printf("\nposisi penyisipan setelah data bernilai : ");
  fflush(stdin);
  scanf("%d", &pos);
  printf("\nbilangan : ");
  fflush(stdin);
  scanf("%d", &bil);

  pCur = *head;// analisis pCur dengan data awal
  while (pCur != NULL && pCur -> data != pos) {
    pCur = pCur -> next;
  }

  pNew = (node *)malloc(sizeof(node));

  if (pCur == NULL){// jika pcur (data sebelumnya tidak ada
     printf("\n node tidak ditemukan");
     getch();
  }
  else if (pNew == NULL){//jika data yang kita masukan kosong
     printf("\n alokasi memeori gagal");
     getch();
  }
  else{
     pNew->data = bil;
     pNew->next = NULL;
     pNew -> next = pCur -> next;
     pCur -> next = pNew;
  }
}

//========================================================
//TambahDataAkhir
void tambahAkhir(node **head) {
    int bil;
    node *pNew, *pCur;

    system("cls");
    printf("Masukkan bilangan: ");
    fflush(stdin);
    scanf("%d", &bil);

    pNew = (node *)malloc(sizeof(node));

    if (pNew == NULL) {
        printf("Alokasi memori gagal\n");
        getch();
        
    }

    pNew->data = bil;
    pNew->next = NULL;

    if (*head == NULL) {
        *head = pNew;
    } else {
        pCur = *head;//jalan pCur mulai dari head
        while (pCur->next != NULL) {
            pCur = pCur->next;
        }
        pCur->next = pNew;
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
    *head = (*head)->next;
    free(pCur);
    printf("\nData di awal dihapus.\n");
    getch();
}

//========================================================
//HapusTengah
void hapusTengah(node **head){
   int  bil;
   node *pcur, *ppre;

   system("cls");
   tranverse(*head);  
   printf("\nbilangan :  ");
   fflush(stdin);
   scanf("%d", &bil);  


   pcur = *head;
   ppre = NULL;

   while (pcur != NULL && pcur->data != bil)
   {
         ppre=pcur;
         pcur = pcur->next;    
   }
   
   if (pcur == NULL )
   {
      printf("\ndata tidak ditemukan");
      getch();
      return;
   }
   
   if (ppre == NULL)
   {
      *head = pcur->next;
   }else
   {
      ppre -> next = pcur-> next;
   }
   free(pcur);
   printf("\ndata berhasil dihapus");
   getch();
}


//========================================================
//HapusAkhir
void hapusAkhir(node **head) {
    node *pCur, *pPrev;

    if (*head == NULL) {
        printf("List kosong!\n");
        getch();
    }

    pCur = *head;
    pPrev = NULL;

    if (pCur->next == NULL) {
        free(pCur);
        *head = NULL;
    } else {
        while (pCur->next != NULL) {
            pPrev = pCur;
            pCur = pCur->next;
        }
        free(pCur);
        pPrev->next = NULL;
    }
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
        return; // Kembali setelah menampilkan pesan
    }

    pCur = head; 
    while (pCur != NULL) { // Selama pCur tidak NULL
        if (pCur->data == bil) { // Jika data ditemukan
            printf("Data %d ditemukan.\n", bil);
            found = 1;
            break; // Keluar dari loop
        }
        pCur = pCur->next; // Pindah ke node berikutnya
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
    
     // Memeriksa apakah list kosong
    if (head == NULL) {
        printf("List kosong!\n");
        getch();
        return; // Kembali setelah menampilkan pesan
    }

    pCur = head; 

    while (pCur != NULL) {
        count++;
        pCur = pCur->next;
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
        pCur = pCur->next;
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
   	printf("%d\t", pWalker -> data);
   	pWalker = pWalker -> next;
      printf(" -> ");
	}
   printf("NULL");
}

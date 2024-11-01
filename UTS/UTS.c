#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MAHASISWA 20

typedef struct Mahasiswa {
    char nama[50];
    char jenis_kelamin; 
    struct Mahasiswa* next;
} Mahasiswa;

// Deklarasi fungsi
void tambahMahasiswa(char nama[], char jenis_kelamin);
void tampilkanMahasiswa();
void keluarMahasiswa();
void cekCINDY(char nama[], char jenis_kelamin);
void pisahkanLingkaran();
void tambahMahasiswaKeLingkaran(Mahasiswa** pListTarget, char nama[], char jenis_kelamin);
void tampilkanLingkaran(Mahasiswa* pListTarget);
void tampilkanBergandengan();
void tampilMenu();


//aray of stuct untuk membatasi 
Mahasiswa* pList = NULL;   // Pointer utama ke circular linked list
int jumlahMahasiswa = 0; // menentukan jumlah mahasiswa

int main() {
    int pilihan;
    char nama[50];
    char jenis_kelamin;

    do {
        tampilMenu();
        scanf("%d", &pilihan);

        if (pilihan == 1) {
            if (jumlahMahasiswa >= MAX_MAHASISWA) {
                printf("Maaf, jumlah mahasiswa sudah mencapai maksimum (%d). Keluarkan mahasiswa untuk menambah mahasiswa baru.\n", MAX_MAHASISWA);
                continue;
            }
            printf("Masukkan nama: ");
            scanf("%49s", nama);
            printf("Masukkan jenis kelamin (L/P): ");
            scanf(" %c", &jenis_kelamin);
            tambahMahasiswa(nama, jenis_kelamin);
        } else if (pilihan == 2) {
            keluarMahasiswa();
        } else if (pilihan == 3) {
            printf("Masukkan nama CINDY: ");
            scanf("%49s", nama);
            cekCINDY(nama, 'P'); 
        } else if (pilihan == 4) {
            pisahkanLingkaran();
        } else if (pilihan == 5) {
            tampilkanBergandengan();
        } else if (pilihan == 6) {
            printf("Keluar program.\n");
        } else {
            printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 6);

    return 0;
}

// Fungsi untuk menampilkan menu utama
void tampilMenu() {
    printf("\n================== Menu =======================\n");
    printf("\nGunakan huruf besar untuk mengisi inputan ini\n");
    printf("1. Tambah Mahasiswa\n");
    printf("2. Mahasiswa Keluar\n");
    printf("3. memasukan cindy\n");
    printf("4. Pisahkan Lingkaran\n");
    printf("5. Tampilkan Status Bergandengan\n");
    printf("6. Keluar\n");
    printf("masukan pilihan menu sesuai nomor: ");
}

// Fungsi untuk menambahkan mahasiswa ke lingkaran satu persatu
void tambahMahasiswa(char nama[], char jenis_kelamin) {
    Mahasiswa* baru = (Mahasiswa*)malloc(sizeof(Mahasiswa));
    strcpy(baru->nama, nama);
    baru->jenis_kelamin = jenis_kelamin;

    if (pList == NULL) {
        pList = baru;
        baru->next = pList; // Membentuk lingkaran
    } else {
        Mahasiswa* pCur = pList;
        while (pCur->next != pList) {
            pCur = pCur->next;
        }
        pCur->next = baru;
        baru->next = pList; // Menyambungkan kembali ke awal
    }

    jumlahMahasiswa++;
    printf("%s berhasil ditambahkan ke lingkaran.\n", nama);
}

// Fungsi opsi jika mahasiswa ingin keluar dari lingakaran
void keluarMahasiswa() {
    if (pList == NULL) {
        printf("Lingkaran kosong.\n");
        return;
    }

    char nama[50];
    printf("Masukkan nama mahasiswa yang keluar: ");
    scanf("%49s", nama);

    Mahasiswa *pCur = pList, *prev = NULL;
    do {
        if (strcmp(pCur->nama, nama) == 0) {
            // Jika hanya ada satu mahasiswa
            if (pCur == pList && pCur->next == pList) {
                free(pCur);
                pList = NULL;
                jumlahMahasiswa--;
                printf("%s telah keluar, lingkaran kosong sekarang.\n", nama);
                return;
            }

            // Jika mahasiswa pertama yang keluar
            if (pCur == pList) {
                while (pCur->next != pList) {
                    pCur = pCur->next;
                }
                pCur->next = pList->next;
                Mahasiswa* hapus = pList;
                pList = pList->next; 
                free(hapus);
            } else {
                prev->next = pCur->next;
                free(pCur);
            }

            jumlahMahasiswa--;//cek jumlah mahasiswa
            printf("%s telah keluar dari lingkaran.\n", nama);
            return;//berhenti
        }
        prev = pCur;
        pCur = pCur->next;
    } while (pCur != pList);

    printf("Mahasiswa dengan nama %s tidak ditemukan.\n", nama);//jika yng diimputkan tdk ada
}

// Fungsi untuk mengecek apakah CINDY bisa bergabung
void cekCINDY(char nama[], char jenis_kelamin) {
    if (jenis_kelamin == 'P') {
        Mahasiswa* pCur = pList;
        if (pCur != NULL) {
            do {
                if (pCur->jenis_kelamin == 'L') {//jika ada laki laki cindy tidak akan bergabung
                    printf("CINDY tidak mau bergandengan dengan teman lelaki. Tidak bisa bergabung.\n");
                    return;
                }
                pCur = pCur->next;
            } while (pCur != pList);
        }
        // Jika tidak ada laki-laki cindy masuk dalam lingkaran
        tambahMahasiswa(nama, jenis_kelamin);
        printf("%s berhasil bergabung ke lingkaran.\n", nama);
    } else {
        printf("CINDY hanya mau bergandengan dengan perempuan.\n");
    }
}

// Fungsi untuk memisahkan lingkaran menjadi dua wahasiswa/i
void pisahkanLingkaran() {
    if (pList == NULL) {
        printf("Lingkaran kosong.\n");
        return;
    }

    Mahasiswa *pListLaki = NULL, *pListPerempuan = NULL;

    Mahasiswa* pCur = pList;
    do {
        if (pCur->jenis_kelamin == 'L') {
            // menambah ke lingkaran laki-laki
            tambahMahasiswaKeLingkaran(&pListLaki, pCur->nama, pCur->jenis_kelamin);
        } else {
            // menambah ke lingkaran perempuan
            tambahMahasiswaKeLingkaran(&pListPerempuan, pCur->nama, pCur->jenis_kelamin);
        }
        pCur = pCur->next;
    } while (pCur != pList);

    printf("Lingkaran telah dipisahkan berdasarkan jenis kelamin.\n");
    
    // Tampilkan lingkaran laki-laki
    printf("Lingkaran Laki-laki:\n");
    tampilkanLingkaran(pListLaki);

    // Tampilkan lingkaran perempuan
    printf("Lingkaran Perempuan:\n");
    tampilkanLingkaran(pListPerempuan);
}

// Fungsi untuk menampilkan lingkaran
void tampilkanLingkaran(Mahasiswa* pListTarget) {
    if (pListTarget == NULL) {
        printf("Lingkaran kosong.\n");
        return;
    }

    Mahasiswa* pWalker = pListTarget;
    do {
        printf("%s -> ", pWalker->nama);
        pWalker = pWalker->next;
    } while (pWalker != pListTarget);
    printf("%s (kembali ke awal)\n", pListTarget->nama);
}

// Fungsi untuk menambahkan mahasiswa ke lingkaran kecil
void tambahMahasiswaKeLingkaran(Mahasiswa** pListTarget, char nama[], char jenis_kelamin) {
    Mahasiswa* baru = (Mahasiswa*)malloc(sizeof(Mahasiswa));
    strcpy(baru->nama, nama);
    baru->jenis_kelamin = jenis_kelamin;

    if (*pListTarget == NULL) {
        *pListTarget = baru;
        baru->next = *pListTarget; // Membentuk lingkaran
    } else {
        Mahasiswa* pCur = *pListTarget;
        while (pCur->next != *pListTarget) {
            pCur = pCur->next;
        }
        pCur->next = baru;
        baru->next = *pListTarget; // Menyambungkan kembali
    }
}

// Fungsi untuk menampilkan status bergandengan
void tampilkanBergandengan() {
    if (pList == NULL) {
        printf("Lingkaran kosong.\n");
        return;
    }

    Mahasiswa* pWalker = pList;
    printf("Status Bergandengan:\n");
    do {
        printf("%s -> ", pWalker->nama);
        pWalker = pWalker->next;
    } while (pWalker != pList);
    printf("%s (kembali ke awal)\n", pList->nama);
}


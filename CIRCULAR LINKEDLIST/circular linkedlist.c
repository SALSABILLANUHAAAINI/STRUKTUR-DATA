#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Mahasiswa {
    char nama[50];
    char jenis_kelamin; // 'L' untuk laki-laki, 'P' untuk perempuan
    struct Mahasiswa* next;
} Mahasiswa;

Mahasiswa* pList = NULL;  // Pointer utama ke circular linked list

// Fungsi untuk menambahkan mahasiswa ke pList (circular linked list)
void tambahMahasiswa(char nama[], char jenis_kelamin) {
    Mahasiswa* baru = (Mahasiswa*)malloc(sizeof(Mahasiswa));
    strcpy(baru->nama, nama);
    baru->jenis_kelamin = jenis_kelamin;
    baru->next = NULL;

    if (pList == NULL) {
        pList = baru;
        pList->next = pList; // Membentuk lingkaran
    } else {
        Mahasiswa* pCur = pList;
        while (pCur->next != pList) {
            pCur = pCur->next;
        }
        pCur->next = baru;
        baru->next = pList;
    }
}

// Fungsi untuk mengecek apakah Cyndi bisa bergabung
void cekCyndi(char nama[], char jenis_kelamin) {
    // Cyndi hanya mau bergandengan jika tidak ada mahasiswa laki-laki
    if (jenis_kelamin == 'P') {
        // Cek apakah ada mahasiswa laki-laki di dalam pList
        Mahasiswa* pCur = pList;
        if (pCur != NULL) {
            do {
                if (pCur->jenis_kelamin == 'L') {
                    printf("Cyndi tidak mau bergandengan dengan teman lelaki. Tidak bisa bergabung.\n");
                    return;
                }
                pCur = pCur->next;
            } while (pCur != pList);
        }
        // Jika tidak ada laki-laki, tambahkan Cyndi
        tambahMahasiswa(nama, jenis_kelamin);
        printf("%s berhasil bergabung ke lingkaran.\n", nama);
    } else {
        printf("Cyndi hanya mau bergandengan dengan perempuan.\n");
    }
}

// Fungsi untuk menampilkan mahasiswa yang sedang bernyanyi dan yang menunggu giliran
void tampilkanStatusBernyanyi() {
    if (pList == NULL) {
        printf("Lingkaran kosong.\n");
        return;
    }

    Mahasiswa* pCur = pList;
    int pertama = 1; // Flag untuk menunjukkan mahasiswa pertama (yang sedang menyanyi)

    do {
        if (pertama) {
            // Mahasiswa pertama sedang bernyanyi
            printf("%s (Jenis kelamin: %c) sedang bernyanyi.\n", pCur->nama, pCur->jenis_kelamin);
            pertama = 0; // Setelah mahasiswa pertama, flag dimatikan
        } else {
            // Mahasiswa lainnya menunggu giliran
            printf("%s (Jenis kelamin: %c) sedang menunggu giliran.\n", pCur->nama, pCur->jenis_kelamin);
        }
        pCur = pCur->next;
    } while (pCur != pList);
}

// Fungsi untuk memindah urutan bernyanyi dan menghapus elemen pList saat ini
void pindahUrutanBernyanyi() {
    if (pList == NULL) {
        printf("Lingkaran kosong.\n");
        return;
    }

    Mahasiswa* pCur = pList;

    // Jika hanya ada satu elemen dalam lingkaran
    if (pList->next == pList) {
        free(pList);
        pList = NULL;
        printf("Mahasiswa terakhir telah dihapus. Lingkaran kosong.\n");
        return;
    }

    // Jika lebih dari satu elemen, cari elemen sebelum pList
    while (pCur->next != pList) {
        pCur = pCur->next;
    }

    // Simpan pointer ke elemen yang akan dihapus
    Mahasiswa* hapus = pList;
    pCur->next = pList->next; // Hubungkan elemen sebelumnya ke elemen setelah pList
    pList = pList->next; // Pindahkan pList ke elemen berikutnya
    free(hapus); // Hapus elemen lama

    printf("Urutan bernyanyi telah dipindahkan. Elemen pertama dihapus.\n");
}

int pilihan;

void tampilMenu() {
    printf("\n===== Menu =====\n");
    printf("1. Tambah Mahasiswa ke Lingkaran\n");
    printf("2. Cek Cyndi\n");
    printf("3. Tampilkan Status Bernyanyi\n");
    printf("4. Pindah Urutan Bernyanyi\n");
    printf("5. Keluar\n");
    printf("Pilih: ");
    scanf("%d", &pilihan);
}

// Menu utama
int main() {
    char nama[50];
    char jenis_kelamin;

    do {
        tampilMenu();

        if (pilihan == 1) {
            printf("Masukkan nama: ");
            scanf("%s", nama);
            printf("Masukkan jenis kelamin (L/P): ");
            scanf(" %c", &jenis_kelamin);
            tambahMahasiswa(nama, jenis_kelamin);
        } 
        else if (pilihan == 2) {
            printf("Masukkan nama Cyndi: ");
            scanf("%s", nama);
            cekCyndi(nama, 'P'); // Cyndi adalah perempuan
        } 
        else if (pilihan == 3) {
            tampilkanStatusBernyanyi();
        } 
        else if (pilihan == 4) {
            pindahUrutanBernyanyi();
        } 
        else if (pilihan == 5) {
            printf("Keluar program.\n");
        } 
        else {
            printf("Pilihan tidak valid.\n");
        }

    } while (pilihan != 5);

    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> // Untuk menggunakan tipe data bool

// Mendefinisikan enum untuk tujuan perjalanan
typedef enum {
    MEDAN_SIANTAR,
    MEDAN_BALIGE,
    MEDAN_TARUTUNG,
    JUMLAH_TUJUAN // Digunakan untuk menghitung jumlah tujuan
} TujuanPerjalanan;

// Struct untuk menyimpan data tiket penumpang
typedef struct {
    int nomorTiket;
    char namaPenumpang[50];
    TujuanPerjalanan tujuan;
    int nomorKursi;
    long hargaTiket;
    bool isBooked; // Menandakan apakah tiket sudah dibooking
} TiketPenumpang;

// Array untuk menyimpan maksimal 100 data tiket
#define MAX_TIKET 100
TiketPenumpang daftarTiket[MAX_TIKET];
int jumlahTiketTerisi = 0; // Menghitung jumlah tiket yang sudah terisi

// Fungsi untuk mendapatkan nama tujuan dari enum
const char* getNamaTujuan(TujuanPerjalanan tujuan) {
    switch (tujuan) {
        case MEDAN_SIANTAR: return "Medan - Siantar";
        case MEDAN_BALIGE: return "Medan - Balige";
        case MEDAN_TARUTUNG: return "Medan - Tarutung";
        default: return "Tidak Diketahui";
    }
}

// Fungsi untuk mendapatkan harga tiket berdasarkan tujuan
long getHargaTujuan(TujuanPerjalanan tujuan) {
    switch (tujuan) {
        case MEDAN_SIANTAR: return 60000;
        case MEDAN_BALIGE: return 140000;
        case MEDAN_TARUTUNG: return 250000;
        default: return 0;
    }
}

// Fungsi untuk menampilkan menu utama
void tampilkanMenu() {
    printf("\n--- Sistem Ticketing Travel KBT ---\n");
    printf("1. Pesan Tiket\n");
    printf("2. Lihat Daftar Tiket\n");
    printf("3. Cari Tiket\n");
    printf("4. Batalkan Tiket\n");
    printf("5. Tampilkan Jumlah Tiket Terjual\n");
    printf("6. Keluar\n");
    printf("Pilih menu: ");
}

// Fungsi untuk pesan tiket
void pesanTiket() {
    if (jumlahTiketTerisi >= MAX_TIKET) {
        printf("Maaf, kapasitas tiket sudah penuh.\n");
        return;
    }

    TiketPenumpang newTiket;
    newTiket.nomorTiket = jumlahTiketTerisi + 1; // Nomor tiket otomatis
    printf("\n--- Pesan Tiket Baru ---\n");
    printf("Nomor Tiket: %d\n", newTiket.nomorTiket);

    printf("Masukkan Nama Penumpang: ");
    scanf(" %49[^\n]", newTiket.namaPenumpang);

    printf("Pilih Tujuan Perjalanan:\n");
    printf("  1. Medan - Siantar (Rp 60.000)\n");
    printf("  2. Medan - Balige (Rp 140.000)\n");
    printf("  3. Medan - Tarutung (Rp 250.000)\n");
    printf("Pilihan Tujuan (1-3): ");
    int pilihanTujuan;
    scanf("%d", &pilihanTujuan);

    switch (pilihanTujuan) {
        case 1: newTiket.tujuan = MEDAN_SIANTAR; break;
        case 2: newTiket.tujuan = MEDAN_BALIGE; break;
        case 3: newTiket.tujuan = MEDAN_TARUTUNG; break;
        default:
            printf("Pilihan tujuan tidak valid. Pembatalan pemesanan.\n");
            return;
    }
    newTiket.hargaTiket = getHargaTujuan(newTiket.tujuan);

    printf("Masukkan Nomor Kursi (1-100): ");
    scanf("%d", &newTiket.nomorKursi);
    // TODO: Tambahkan validasi nomor kursi agar tidak duplikat dan sesuai rentang

    newTiket.isBooked = true;
    daftarTiket[jumlahTiketTerisi] = newTiket;
    jumlahTiketTerisi++;

    printf("\n--- Bukti Tiket ---\n");
    printf("Nomor Tiket      : %d\n", newTiket.nomorTiket);
    printf("Nama Penumpang   : %s\n", newTiket.namaPenumpang);
    printf("Tujuan Perjalanan: %s\n", getNamaTujuan(newTiket.tujuan));
    printf("Nomor Kursi      : %d\n", newTiket.nomorKursi);
    printf("Harga Tiket      : Rp %ld\n", newTiket.hargaTiket);
    printf("Pemesanan tiket berhasil!\n");
}

// Fungsi untuk melihat daftar tiket
void lihatDaftarTiket() {
    printf("\n--- Daftar Tiket Penumpang ---\n");
    if (jumlahTiketTerisi == 0) {
        printf("Belum ada tiket yang dipesan.\n");
        return;
    }

    printf("-----------------------------------------------------------------------------------\n");
    printf("| No. Tiket | Nama Penumpang        | Tujuan Perjalanan | No. Kursi | Harga Tiket   |\n");
    printf("-----------------------------------------------------------------------------------\n");
    for (int i = 0; i < jumlahTiketTerisi; i++) {
        if (daftarTiket[i].isBooked) {
            printf("| %-9d | %-21s | %-17s | %-9d | Rp %-10ld |\n",
                   daftarTiket[i].nomorTiket,
                   daftarTiket[i].namaPenumpang,
                   getNamaTujuan(daftarTiket[i].tujuan),
                   daftarTiket[i].nomorKursi,
                   daftarTiket[i].hargaTiket);
        }
    }
    printf("-----------------------------------------------------------------------------------\n");
}

// Fungsi untuk mencari tiket
void cariTiket() {
    printf("\n--- Cari Tiket ---\n");
    if (jumlahTiketTerisi == 0) {
        printf("Belum ada tiket yang dipesan untuk dicari.\n");
        return;
    }

    int nomorTiketCari;
    printf("Masukkan Nomor Tiket yang ingin dicari: ");
    scanf("%d", &nomorTiketCari);

    bool ditemukan = false;
    for (int i = 0; i < jumlahTiketTerisi; i++) {
        if (daftarTiket[i].isBooked && daftarTiket[i].nomorTiket == nomorTiketCari) {
            printf("\n--- Detail Tiket Ditemukan ---\n");
            printf("Nomor Tiket      : %d\n", daftarTiket[i].nomorTiket);
            printf("Nama Penumpang   : %s\n", daftarTiket[i].namaPenumpang);
            printf("Tujuan Perjalanan: %s\n", getNamaTujuan(daftarTiket[i].tujuan));
            printf("Nomor Kursi      : %d\n", daftarTiket[i].nomorKursi);
            printf("Harga Tiket      : Rp %ld\n", daftarTiket[i].hargaTiket);
            ditemukan = true;
            break;
        }
    }

    if (!ditemukan) {
        printf("Tiket dengan nomor %d tidak ditemukan atau sudah dibatalkan.\n", nomorTiketCari);
    }
}

// Fungsi untuk batalkan tiket
void batalkanTiket() {
    printf("\n--- Batalkan Tiket ---\n");
    if (jumlahTiketTerisi == 0) {
        printf("Belum ada tiket yang dipesan untuk dibatalkan.\n");
        return;
    }

    int nomorTiketBatal;
    printf("Masukkan Nomor Tiket yang ingin dibatalkan: ");
    scanf("%d", &nomorTiketBatal);

    bool dibatalkan = false;
    for (int i = 0; i < jumlahTiketTerisi; i++) {
        if (daftarTiket[i].isBooked && daftarTiket[i].nomorTiket == nomorTiketBatal) {
            daftarTiket[i].isBooked = false; // Menandai tiket tidak aktif
            printf("Tiket dengan nomor %d berhasil dibatalkan.\n", nomorTiketBatal);
            dibatalkan = true;
            break;
        }
    }

    if (!dibatalkan) {
        printf("Tiket dengan nomor %d tidak ditemukan atau sudah dibatalkan sebelumnya.\n", nomorTiketBatal);
    }
}

// Fungsi untuk menampilkan jumlah tiket yang terjual
void tampilkanJumlahTiketTerjual() {
    int terjualAktif = 0;
    for (int i = 0; i < jumlahTiketTerisi; i++) {
        if (daftarTiket[i].isBooked) {
            terjualAktif++;
        }
    }
    printf("\n--- Informasi Tiket Terjual ---\n");
    printf("Jumlah total tiket yang pernah dipesan: %d\n", jumlahTiketTerisi);
    printf("Jumlah tiket yang saat ini aktif/terjual: %d\n", terjualAktif);
}

int main() {
    int pilihan;
    // Loop do-while agar program terus berjalan sampai user memilih keluar
    do {
        tampilkanMenu();
        scanf("%d", &pilihan);

        // Membersihkan buffer input setelah scanf untuk menghindari masalah dengan fgets/scanf berikutnya
        // pada input string jika ada newline yang tersisa
        while (getchar() != '\n'); 

        switch (pilihan) {
            case 1:
                pesanTiket();
                break;
            case 2:
                lihatDaftarTiket();
                break;
            case 3:
                cariTiket();
                break;
            case 4:
                batalkanTiket();
                break;
            case 5:
                tampilkanJumlahTiketTerjual();
                break;
            case 6:
                printf("Terima kasih telah menggunakan Sistem Ticketing Travel KBT. Sampai jumpa!\n");
                break;
            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
        printf("\n"); // Baris kosong untuk keterbacaan
    } while (pilihan != 6);

    return 0;
}
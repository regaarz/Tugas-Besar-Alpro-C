#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Kamar
{
    int kamarID;
    char type_kamar[20];
    double harga_kamar;
    int ketersediaan;
    char fasilitas[150];
};

struct Reservasi
{
    char name[50];
    char IDTamu[20];
    int kamarID;
    char telepon[20];
    int waktu_menginap;
    double bayar;
};

struct Kamar kamarHotel[] = {
    {1, "Standard", 80.0, 1, "Kasur, Kamar mandi, Water heater, sofa, TV, AC, meja, lemari, wifi, breakfast"},
    {2, "Premium", 120.0, 1, "Kasur, Kamar mandi, Water heater, sofa, TV, AC, meja, lemari, wifi, breakfast, mini bar"},
    {3, "Luxury", 200.0, 1, "Kasur, Kamar mandi, Water heater, sofa, TV, AC, meja, lemari, wifi, breakfast, mini bar, Kolam renang pribadi"}};

void Keterangankamar()
{
    printf("\nKamar Yang Tersedia:\n");
    printf("No. Kamar | Tipe Kamar | Harga Per Malam | Fasilitas\n");
    for (int i = 0; i < sizeof(kamarHotel) / sizeof(kamarHotel[0]); i++)
    {
        if (kamarHotel[i].ketersediaan)
        {
            printf("%8d  | %-11s|      $%.2f     | %s\n", kamarHotel[i].kamarID, kamarHotel[i].type_kamar, kamarHotel[i].harga_kamar, kamarHotel[i].fasilitas);
        }
    }
}

int reservasiKamar(struct Reservasi *reservation)
{
    printf("\nMasukkan Nama Anda \t\t: ");
    scanf("%s", reservation->name);
    printf("Masukkan Nomor Identitas Anda   : ");
    scanf("%s", &reservation->IDTamu);
    printf("Masukkan Nomor Kamar \t\t: ");
    scanf("%d", &reservation->kamarID);

    if (reservation->kamarID < 1 || reservation->kamarID > 3 || !kamarHotel[reservation->kamarID - 1].ketersediaan)
    {
        printf("Kamar tidak tersedia atau nomor kamar tidak valid.\n");
        return 0; // Pemesanan gagal
    }
    else
    {
        printf("Masukkan Nomer Telepon \t\t: ");
        scanf("%s", reservation->telepon);
        printf("Masukkan Jumlah Malam Menginap  : ");
        scanf("%d", &reservation->waktu_menginap);

        reservation->bayar = kamarHotel[reservation->kamarID - 1].harga_kamar * reservation->waktu_menginap;

        kamarHotel[reservation->kamarID - 1].ketersediaan = 0;

        return 1;
    }
}

void bayar(struct Reservasi *reservation)
{
    // Melakukan bayar
    double payment;
    char pesanan;
    char pembayaran[20];
    printf("\nTotal Harga \t\t\t: $%.2f\n", reservation->bayar);
    printf("Buat Pesanan (y/n) : ");
    getchar();
    scanf("%c", &pesanan);
    if (pesanan == 'y')
    {
        printf("Pembayaran melalui cash/transfer : ");
        scanf("%s", &pembayaran);

        if (strcmp(pembayaran, "cash") == 0)
        {
            printf("Silahkan Lakukan Pembayaran di resepsionis \n");
            printf("Reservasi Anda Telah Kami Simpan\n");
        }

        else if (strcmp(pembayaran, "transfer") == 0)
        {
            printf("Masukkan Jumlah bayar: $");
            scanf("%lf", &payment);
            if (payment < reservation->bayar)
            {
                printf("bayar tidak mencukupi. Pembatalan pemesanan.\n");
                kamarHotel[reservation->kamarID - 1].ketersediaan = 1;
            }
            else
            {
                printf("\nPembayaran berhasil! Terima kasih atas pemesanan Anda.\n");
            }
        }
    }
    else
    {
        printf("Terimakasih telah mengunjungi menu reservasi kami\n");
    }
}

int main()
{
    int keluar;
    do
    {
        int i;
        // Fitur menu utama
        printf("=========================================================\n");
        printf("***************** WELCOME TO ZODIAC.HOTEL ***************\n");
        printf("=========================================================\n");

        printf("1. Informasi Kamar\n2. Reservasi Kamar\n3. Manajemen Hotel\n4. Keluar\n");
        printf("\nPilih Menu : ");
        scanf("%d", &i);
        system("cls");

        switch (i)
        {
        case 1:
            // Fitur menampilkan informasi kamar
            Keterangankamar();
            break;
        // Fitur reservasi kamar
        case 2:
            printf("============================================================\n");
            printf("----------------------- RESERVASI --------------------------\n");
            printf("============================================================\n");

            struct Reservasi reservation;
            if (reservasiKamar(&reservation))
            {
                bayar(&reservation);
            }
            break;

        default:
            printf("Operasi tidak ditemukan.\n");
            break;
        }
        printf("1. Kembali ke menu utama\n2. Keluar \n");
        scanf("%d", &keluar);
        system("cls");
        if (keluar == 2)
        {
            printf("Terimakasih Telah Mengunjungi Aplikasi Zodiak Hotel \n");
            printf("Semoga Hari Anda Menyenangkan  \n");
        }
    } while (keluar == 1);

    return 0;
}

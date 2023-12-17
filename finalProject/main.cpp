#include "relasi.h"

int main()
{
    // Deklarasi variabel Ld, Lm, Lr
    listDosen Ld;
    listMhs Lm;
    listRelasi Lr;

    // Membuat list kosong Ld,Lm,Lr
    createListDosen(Ld);
    createListMhs(Lm);
    createListRelasi(Lr);

    int option = 1337; // deklarasi variabel
    // Selama option tidak '0', lakukan loop
    while (option!=0) {
        menu(); // menampilkan menu
        cout << "Input: ";
        cin >> option;

        if (option==1) { // Menambah data mahasiswa
            // Meminta berapa jumlah data yang akan dimasukkan
            cout << "Berapa jumlah data yang akan dimasukkan? ";
            int jum;
            cin >> jum;

            for (int i = 1; i <= jum;i++){
                // Menggunakan insertFirst untuk memasukkan elemen ke list
                cout << "Data ke-" << i << endl;
                insertFirstMhs(Lm, createElmtMhs());
            }
        } else if (option==2) { // Menambah data dosen
            // Meminta berapa jumlah data yang akan dimasukkan
            cout << "Berapa jumlah data yang akan dimasukkan? ";
            int jum;
            cin >> jum;

            for (int i = 1; i <= jum;i++){
                // Menggunakan insertLast untuk memasukkan elemen ke list
                cout << "Data ke-" << i << endl;
                insertLastDosen(Ld, createElmtDosen());
            }
        } else if (option==3) { // Mencari data mahasiswa
            int subOpt1 = -1;
            while (subOpt1 != 0){
                cout << "Mencari data mahasiswa berdasarkan: " << endl;
                cout << "1. Nama" << endl << "2. NIM" << endl;
                cout << "Tekan 0 untuk keluar dari menu ini" << endl;
                cout << "Input: " << endl;
                cin >> subOpt1;

                if (subOpt1 == 1){ // Berdasarkan nama
                    cout << "Masukkan Nama Mahasiswa: ";
                    string nama;
                    cin >> nama;
                    adrMhs p = searchMhsByNama(Lm, nama);
                    if (p != NULL){
                        cout << "Nama: ";
                        cout << p->info.namaMhs << endl;
                        cout << "NIM: ";
                        cout << p->info.NIM << endl;
                        cout << "Dosen Pembimbing 1: ";
                        cout << p->info.dospem1 << endl;
                        cout << "NIP Dosen: ";
                        cout << p->info.NIP1 << endl;
                        cout << "Dosen Pembimbing 2: ";
                        cout << p->info.dospem2 << endl;
                        cout << "NIP Dosen: ";
                        cout << p->info.NIP2 << endl;
                        cout << endl;
                    }

                } else if (subOpt1 == 2) { // Berdasarkan NIM
                    cout << "Masukkan NIM Mahasiswa: ";
                    string NIM;
                    cin >> NIM;
                    adrMhs p = searchMhsByNIM(Lm, NIM);
                    if (p != NULL){
                        cout << "Nama: ";
                        cout << p->info.namaMhs << endl;
                        cout << "NIM: ";
                        cout << p->info.NIM << endl;
                        cout << "Dosen Pembimbing 1: ";
                        cout << p->info.dospem1 << endl;
                        cout << "NIP Dosen: ";
                        cout << p->info.NIP1 << endl;
                        cout << "Dosen Pembimbing 2: ";
                        cout << p->info.dospem2 << endl;
                        cout << "NIP Dosen: ";
                        cout << p->info.NIP2 << endl;
                        cout << endl;
                    } else {
                        cout << "Data tidak ditemukan" << endl;
                    }
                } else if (subOpt1 < 0 || subOpt1 > 2){
                    cout << "Input tidak valid, coba lagi" << endl;
                }
            }
        } else if (option==4) { // Menambah relasi dospem dengan mahasiswa atau sebaliknya
            // Meminta NIM mahasiswa dan mencari NIP dosen
            string NIM, NIP;

            cout << "Masukkan NIM mahasiswa: ";
            cin >> NIM;
            cout << "Masukkan NIP dosen: ";
            cin >> NIP;

            // Menambahkan relasi
            addRelasi(Lr, Ld, Lm, NIP, NIM);
        } else if (option==5) { // Mencari mahasiswa yang dibimbing oleh dosen tertentu

        } else if (option==6) { // Menghapus dosen beserta relasinya

        } else if (option==7) { // Menghapus data dosen yang membimbing mahasiswa tertentu

        } else if (option==8) { // Menampilkan seluruh mahasiswa beserta dospem 1 dan 2

        } else if (option==9) { // Menampilkan dospem dengan jumlah bimbingan terbanyak

        } else if (option==10) { // Menampilkan mahasiswa yang hanya memiliki 1 dospem

        } else if (option < 0 || option > 10){ // Jika option tidak valid) {
            cout << "Input tidak valid, coba lagi" << endl;
        }
    }
    cout << "Cheerio!" << endl;
    return 0;
}

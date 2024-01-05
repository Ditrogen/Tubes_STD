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
    dummy(Ld, Lm);

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
                        p=Lm.first;
                        // nama orang bisa sama jadi di loop
                        while (p!=NULL) {
                            if (p->info.namaMhs==nama) {
                                cout << "Nama: " << p->info.namaMhs << endl;
                                cout << "NIM: " << p->info.NIM << endl;
                                cout << "Dosen Pembimbing 1: " << p->info.dospem1 << endl;
                                cout << "NIP Dosen: " << p->info.NIP1 << endl;
                                cout << "Dosen Pembimbing 2: " << p->info.dospem2 << endl;
                                cout << "NIP Dosen: " << p->info.NIP2 << endl;
                                cout << endl;
                            }
                            p=p->next;
                        }
                    } else {
                        cout << "Data tidak ditemukan" << endl;
                    }
                } else if (subOpt1 == 2) { // Berdasarkan NIM
                    cout << "Masukkan NIM Mahasiswa: ";
                    string NIM;
                    cin >> NIM;
                    adrMhs p = searchMhsByNIM(Lm, NIM);
                    if (p != NULL){
                        cout << "Nama: " << p->info.namaMhs << endl;
                        cout << "NIM: " << p->info.NIM << endl;
                        cout << "Dosen Pembimbing 1: " << p->info.dospem1 << endl;
                        cout << "NIP Dosen: " << p->info.NIP1 << endl;
                        cout << "Dosen Pembimbing 2: " << p->info.dospem2 << endl;
                        cout << "NIP Dosen: " << p->info.NIP2 << endl;
                        cout << endl;
                    } else {
                        cout << "Data tidak ditemukan" << endl;
                    }
                } else if (subOpt1 < 0 || subOpt1 > 2){
                    cout << "Input tidak valid, coba lagi" << endl;
                }
            }
        } else if (option==4) { // Menambah relasi dospem dengan mahasiswa atau sebaliknya
            // Meminta NIM mahasiswa dan NIP dosen
            string NIM, NIP;

            cout << "Masukkan NIM mahasiswa: ";
            cin >> NIM;
            cout << "Masukkan NIP dosen: ";
            cin >> NIP;

            // Menambahkan relasi
            addRelasi(Lr, Ld, Lm, NIP, NIM);
        } else if (option==5) { // Mencari mahasiswa yang dibimbing oleh dosen tertentu
            // Menerima input NIP Dosen dan mencarinya
            cout << "Masukkan NIP Dosen: ";
            string NIP;
            cin >> NIP;
            adrDosen p = searchDosenByNIP(Ld, NIP);

            // Klo ketemu, lakukan pencarian mahasiswa bimbingannya
            if (p != NULL){
                adrRelasi r = Lr.first;
                cout << "Dosen " << p->info.namaDosen << " Membimbing:" << endl;
                int jum = 0;
                while (r != NULL){ // Menelusuri list relasi
                    // Klo elemennya sama dengan p, print nama dan nim mahasiswanya
                    if (r->nextDosen == p){
                        cout << "Nama: " << r->nextMhs->info.namaMhs << endl;
                        cout << "NIM: " << r->nextMhs->info.NIM << endl;
                        cout << endl;
                        jum++;
                    }
                    r = r->next;
                }

                // Klo dosennya gk berelasi sama mahasiwa
                if (jum == 0){
                    cout << "Dosen tidak membimbing mahasiswa siapapun" << endl;
                }
            } else {
                cout << "Dosen tidak ditemukan" << endl;
            }
        } else if (option==6) { // Menghapus dosen beserta relasinya
            // Menerima NIP Dosen dan mencarinya
            string NIP;
            cout << "Masukkan NIP Dosen: ";
            cin >> NIP;
            deleteAllDosenByNIPDosen(Lr, Ld, Lm, NIP);
        } else if (option==7) { // Menghapus data dosen yang membimbing mahasiswa tertentu
            string NIP, NIM;
            cout << "Masukkan NIP Dosen: ";
            cin >> NIP;
            cout << "Masukkan NIM Mahasiswa: ";
            cin >> NIM;
            deleteRelasiByNIPDosenDanNIMMhs(Lr, Ld, Lm, NIP, NIM);
        } else if (option==8) { // Menampilkan seluruh mahasiswa beserta dospem 1 dan 2
            showAllMhs(Lm);
            showAllDosen(Ld);
        } else if (option==9) { // Menampilkan dospem dengan jumlah bimbingan terbanyak
            if (Ld.first != NULL){
                showHighestDospemCount(Ld);
            } else {
                cout << "List dosen tidak ada" << endl;
            }
        } else if (option==10) { // Menampilkan mahasiswa yang hanya memiliki 1 dospem
            if (Ld.first != NULL){
                showSingleDospemCount(Lr);
            } else {
                cout << "List relasi tidak ada" << endl;
            }
        } else if (option < 0 || option > 10){ // Jika option tidak valid) {
            cout << "Input tidak valid, coba lagi" << endl;
        }
    }
    cout << "Cheerio!" << endl;
    return 0;
}


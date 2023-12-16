#include "relasi.h"

int main()
{
    int input;
    string instring;
    string instring2;
    adrDosen inDosen;
    adrMhs inMhs;
    adrRelasi inRel;
    int i = -1;
    listDosen Ld;
    listMhs Lm;
    listRelasi Lr;
    createListDosen(Ld);
    createListMhs(Lm);
    createListRelasi(Lr);
    while (i!=0) {
        menu();
        cout << "Input :";
        cin >> i;
        cout << endl;
        if (i==1) {
            inMhs=createElmtMhs();
            insertLastMhs(Lm, inMhs);
        } else if (i==2) {
            inDosen=createElmtDosen();
            insertFirstDosen(Ld, inDosen);
        } else if (i==3) {
            cout << "Masukkan kode Dosen : ";
            cin >> instring;
            cout << endl;
            inDosen=searchDosen(Ld, instring);
            if (inDosen==NULL) {
                cout << "Tidak ada dosen yang memiliki Kode Dosen tersebut" << endl;
            } else {
                cout << "Nama : " << inDosen->info.namaDosen << endl;
                cout << "Kode Dosen : " << inDosen->info.kodeDosen << endl;
                cout << "NIP : " << inDosen->info.NIP << endl;
            }
        } else if (i==4) {
            cout << "Cari mahasiswa berdasarkan?" << endl;
            cout << "1. Dosen Pembimbing" << endl;
            cout << "2. NIM" << endl;
            cout << "Input : ";
            cin >> input;
            cout << endl;
            if (input==1) {
                cout << "Masukkan kode Dosen : ";
                cin >> instring;
                cout << endl;
                searchRelasiByDosen(Lr, Ld, Lm, instring);
            } else if (input==2) {
                cout << "Masukkan NIM Mahasiswa: ";
                cin >> instring;
                cout << endl;
                inMhs=searchMhs(Lm, instring);
                if (inMhs!=NULL) {
                    cout << "Nama : " << inMhs->info.namaMhs << endl;
                    cout << "NIM : " << inMhs->info.NIM << endl;
                    cout << "Judul Skripsi : " << inMhs->info.judulSkripsi << endl;
                    cout << "Dosen Pembimbing 1 : " << inMhs->info.dospem1 << endl;
                    cout << "Dosen Pembimbing 2 : " <<inMhs->info.dospem2 << endl;
                } else {
                    cout << "Tidak ada mahasiswa yang memiliki NIM tersebut" << endl;
                }
            } else {
                cout << "Input tidak valid" << endl;
            }

        } else if (i==5) {
            cout << "Input NIM Mahasiswa dan Kode Dosen yang ingin di Assign" << endl;
            cout << "NIM : ";
            cin >> instring;
            cout << endl;
            cout << "Kode Dosen : ";
            cin >> instring2;
            cout << endl;
            addRelasi(Lr, Ld, Lm, instring2, instring);
        } else if (i==6) {
            cout << "Input NIM Mahasiswa dari Dosen yang ingin di UnAssign serta Kode Dosennya" << endl;
            cout << "NIM : ";
            cin >> instring;
            cout << endl;
            cout << "Kode Dosen : ";
            cin >> instring2;
            cout << endl;
            deleteRelasiByDosen(Lr, Ld, Lm, instring2, instring);
        } else if (i==7) {
            cout << "Input Kode Dosen" << endl;
            cout << "Kode Dosen : ";
            cin >> instring;
            cout << endl;
            inDosen=searchDosen(Ld, instring);
            if (inDosen==NULL) {
                cout << "Tidak ada Dosen dengan Kode Dosen tersebut" << endl;
            } else {
                deleteRelasiDosen(Lr, Ld, Lm, inDosen);
            }
            if (Ld.first==inDosen&&inDosen!=NULL) {
                deleteFirstDosen(Ld, inDosen);
            } else if (Ld.last==inDosen&&inDosen!=NULL) {
                deleteLastDosen(Ld, inDosen);
            } else if (inDosen!=NULL){
                adrDosen prev = Ld.first;
                while (prev->next!=inDosen) {
                    prev=prev->next;
                }
                deleteAfterDosen(Ld, prev, inDosen);
            }
        } else if (i==8) {
            cout << "Input NIM Mahasiswa" << endl;
            cout << "NIM : ";
            cin >> instring;
            cout << endl;
            inMhs=searchMhs(Lm, instring);
            if (inMhs==NULL) {
                cout << "Tidak ada Mahasiswa dengan NIM tersebut" << endl;
            } else {
                deleteRelasiMhs(Lr, Ld, Lm, inMhs);
            }
            if (Lm.first==inMhs&&inMhs!=NULL) {
                deleteFirstMhs(Lm, inMhs);
            } else if (Lm.last==inMhs&&inMhs!=NULL) {
                deleteLastMhs(Lm, inMhs);
            } else if (inMhs!=NULL){
                adrMhs prev = Lm.first;
                while (prev->next!=inMhs) {
                    prev=prev->next;
                }
                deleteAfterMhs(Lm, prev, inMhs);
            }
        } else if (i==9) {
            cout << "Masukkan angka bedasarkan pilihan berikut" << endl;
            cout << "1. Tampilkan semua Mahasiswa" << endl;
            cout << "2. Tampilkan Mahasiswa yang memiliki pembimbing tunggal" << endl;
            cout << "Input : ";
            cin >> input;
            cout << endl;
            if (input==1) {
                printMhs(Lm);
            } else if (input==2) {
                inMhs=Lm.first;
                while (inMhs!=NULL) {
                    if (inMhs->info.dospem2=="#") {
                        cout << "Nama : " << inMhs->info.namaMhs << endl;
                        cout << "NIM : " << inMhs->info.NIM << endl;
                    }
                    inMhs=inMhs->next;
                }
            } else {
                cout << "Input tidak valid" << endl;
            }
        } else if (i==10) {
            cout << "Masukkan angka bedasarkan pilihan berikut" << endl;
            cout << "1. Tampil semua Info Dosen Pembimbing" << endl;
            cout << "2. Tampil Dosen yang memiliki jumlah bimbingan terbanyak" << endl;
            cout << "Input : ";
            cin >> input;
            cout << endl;
            if (input==1) {
                printDosen(Ld);
            } else if (input==2) {
                maxDosen(Lr, Ld, Lm);
            } else {
                cout << "Input tidak valid" << endl;
            }
        } else {
            cout << "Input tidak valid" << endl;
        }
    }
    return 0;
}

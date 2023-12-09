#include "relasi.h"

void menu() {
    cout << "============================" << endl;
    cout << "Halaman Depan Final Project" << endl;
    cout << endl;
    cout << "Silahkan pilih opsi berikut: " << endl;
    cout << "1. Tambah Info Dosen Pembimbing" << endl;
    cout << "2. Tambah Info Mahasiswa" << endl;
    cout << "3. Mencari Dosen Pembimbing" << endl;
    cout << "4. Mencari Mahasiswa" << endl;
    cout << "5. Assign Dosen Pembimbing ke Mahasiswa" << endl;
    cout << "6. UnAssign Dosen Pembimbing ke Mahasiswa" << endl;
    cout << "7. Menghapus Info Dosen" << endl;
    cout << "8. Menghapus Info Mahasiswa" << endl;
    cout << "9. Menampilkan Info Mahasiswa dengan Dosen Pembimbing" << endl;
    cout << "10. Menampilkan Info Dosen Pembimbing" << endl;
    cout << "Tekan 0 untuk Keluar Program" << endl;
    cout << "============================" << endl;
}

void createListDosen(listDosen &Ld) {
    Ld.first=NULL;
    Ld.last=NULL;
}

void createListMhs(listMhs &Lm) {
    Lm.first=NULL;
    Lm.last=NULL;
}

void createListRelasi(listRelasi &Lr) {
    Lr.first=NULL;
}

adrDosen createElmtDosen() {
    adrDosen p = new ElmDosen;
    p->next=NULL;
    p->prev=NULL;
    cin >> p->info.namaDosen;
    cin >> p->info.kodeDosen;
    cin >> p->info.NIP;
    p->info.jumPembimbing1=0;
    p->info.jumPembimbing2=0;
    return p;
}

adrMhs createElmtMhs() {
    adrMhs p = new ElmMhs;
    p->next=NULL;
    p->prev=NULL;
    cin >> p->info.namaMhs;
    cin >> p->info.NIM;
    cin >> p->info.judulSkripsi;
    return p;
}

adrMhs createElmtRelasi() {
    adrRelasi p = new ElmRelasi;
    p->next=NULL;
    p->nextDosen=NULL;
    p->nextMhs=NULL;
}

void insertLastDosen(listDosen &Ld, adrDosen p) {
    if (Ld.first==NULL && Ld.last==NULL) {
        Ld.first=p;
        Ld.last=p;
    } else {
        Ld.last->next=p;
        p->prev=Ld.last;
        Ld.last=p;
    }
}

void deleteLastDosen(listDosen &Ld, adrDosen &p) {
    if (Ld.first==NULL && Ld.last==NULL) {
        p=NULL;
    } else if (Ld.first->next==NULL) {
        p=Ld.first;
        Ld.first=NULL;
        Ld.last=NULL;
    } else {
        p=Ld.last;
        Ld.last=p->prev;
        Ld.last->next=NULL;
        p->prev=NULL;
    }
}

void deleteAfterDosen(listDosen &Ld, adrDosen prev, adrDosen &p) {
    if (prev==NULL || prev->next==NULL) {
        p=NULL;
    } else {
        p=prev->next;
        if (p->next==NULL) {
            Ld.last=p->prev;
            Ld.last->next=NULL;
            p->prev=NULL;
        } else {
            prev->next=p->next;
            (p->next)->prev=prev;
            p->next=NULL;
            p->prev=NULL;
        }
    }
}

void deleteFirstDosen(listDosen &Ld, adrDosen &p) {
    if (Ld.first==NULL && Ld.last==NULL) {
        p=NULL;
    } else if (Ld.first->next==NULL) {
        p=Ld.first;
        Ld.first=NULL;
        Ld.last=NULL;
    } else {
        p=Ld.first;
        Ld.first=p->next;
        p->next=NULL;
        Ld.first->prev=NULL;
    }
}

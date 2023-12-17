#include "dosen.h"

void createListDosen(listDosen &Ld) {
    Ld.first=NULL;
    Ld.last=NULL;
}

adrDosen createElmtDosen() {
    adrDosen p = new ElmDosen;
    p->next=NULL;
    p->prev=NULL;
    p->info.countDospem1 = 0;
    p->info.countDospem2 = 0;
    cout << "Masukkan Nama Dosen: ";
    cin >> p->info.namaDosen;
    cout << "Masukkan Kode Dosen: ";
    cin >> p->info.kodeDosen;
    cout << "Masukkan NIP Dosen: ";
    cin >> p->info.NIP;
    return p;
}

void insertFirstDosen(listDosen &Ld, adrDosen p) {
    if (Ld.first==NULL && Ld.last==NULL) {
        Ld.first=p;
        Ld.last=p;
    } else {
        p->next=Ld.first;
        Ld.first->prev=p;
        Ld.first=p;
    }
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

adrDosen searchDosenByKode(listDosen Ld, string kodeDosen){
    adrDosen p = Ld.first;
    while (p != NULL && p->info.kodeDosen != kodeDosen){
        p = p->next;
    }
    return p;
}
adrDosen searchDosenByNIP(listDosen Ld, string NIP){
    adrDosen p = Ld.first;
    while (p != NULL && p->info.NIP != NIP){
        p = p->next;
    }
    return p;
}

void showAllDosen(listDosen Ld){
    adrDosen p = Ld.first;
    cout << "======================= List Dosen =======================" << endl;
    cout << endl;
    while (p != NULL){
        cout << "Nama: ";
        cout << p->info.namaDosen << endl;
        cout << "Kode Dosen: ";
        cout << p->info.kodeDosen << endl;
        cout << "NIP: ";
        cout << p->info.NIP << endl;
        cout << "Jumlah Bimbingan Pertama: ";
        cout << p->info.countDospem1 << endl;
        cout << "Jumlah Bimbingan Kedua: ";
        cout << p->info.countDospem2 << endl;
        cout << endl;
        p = p->next;
    }
    cout << "=========================================================" << endl;
}

#include "mahasiswa.h"

void createListMhs(listMhs &Lm) {
    Lm.first=NULL;
    Lm.last=NULL;
}

adrMhs createElmtMhs() {
    adrMhs p = new ElmMhs;
    p->next=NULL;
    p->prev=NULL;
    cout << "Masukkan nama Mahasiswa: ";
    cin >> p->info.namaMhs;
    cout << "Masukkan NIM Mahasiswa: ";
    cin >> p->info.NIM;
    p->info.dospem1="-";
    p->info.dospem2="-";
    p->info.NIP1="-";
    p->info.NIP2="-";
    return p;
}
void insertLastMhs(listMhs &Lm, adrMhs p){
    if (Lm.first==NULL && Lm.last==NULL) {
        Lm.first=p;
        Lm.last=p;
    } else {
        Lm.last->next=p;
        p->prev=Lm.last;
        Lm.last=p;
    }
}
void insertFirstMhs(listMhs &Lm, adrMhs p){
    if (Lm.first==NULL && Lm.last==NULL) {
        Lm.first=p;
        Lm.last=p;
    } else {
        p->next=Lm.first;
        Lm.first->prev=p;
        Lm.first=p;
    }
}
void deleteLastMhs(listMhs &Lm, adrMhs &p){
    if (Lm.first==NULL && Lm.last==NULL) {
        p=NULL;
    } else if (Lm.first->next==NULL) {
        p=Lm.first;
        Lm.first=NULL;
        Lm.last=NULL;
    } else {
        p=Lm.last;
        Lm.last=p->prev;
        Lm.last->next=NULL;
        p->prev=NULL;
    }
}
void deleteAfterMhs(listMhs &Lm, adrMhs prev, adrMhs &p){
    if (prev==NULL || prev->next==NULL) {
        p=NULL;
    } else {
        p=prev->next;
        if (p->next==NULL) {
            Lm.last=p->prev;
            Lm.last->next=NULL;
            p->prev=NULL;
        } else {
            prev->next=p->next;
            (p->next)->prev=prev;
            p->next=NULL;
            p->prev=NULL;
        }
    }
}
void deleteFirstMhs(listMhs &Lm, adrMhs &p){
    if (Lm.first==NULL && Lm.last==NULL) {
        p=NULL;
    } else if (Lm.first->next==NULL) {
        p=Lm.first;
        Lm.first=NULL;
        Lm.last=NULL;
    } else {
        p=Lm.first;
        Lm.first=p->next;
        p->next=NULL;
        Lm.first->prev=NULL;
    }
}
adrMhs searchMhsByNIM(listMhs Lm, string NIM){
    adrMhs p = Lm.first;
    while (p != NULL && p->info.NIM != NIM){
        p = p->next;
    }
    return p;
}
adrMhs searchMhsByNama(listMhs Lm, string nama){
    adrMhs p = Lm.first;
    while (p != NULL && p->info.namaMhs != nama){
        p = p->next;
    }
    return p;
}
void showAllMhs(listMhs Lm){
    adrMhs p = Lm.first;
    cout << "===================== List Mahasiswa =====================" << endl;
    cout << endl;
    while (p != NULL){
        cout << "Nama: ";
        cout << p->info.namaMhs << endl;
        cout << "NIM: " ;
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
        p = p->next;
    }
    cout << "=========================================================" << endl;
}

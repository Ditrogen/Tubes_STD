#include "mahasiswa.h"

void createListMhs(listMhs &Lm) {
    Lm.first=NULL;
    Lm.last=NULL;
}

adrMhs createElmtMhs() {
    adrMhs p = new ElmMhs;
    p->next=NULL;
    p->prev=NULL;
    cout << "Nama : ";
    cin >> p->info.namaMhs;
    cout << endl;
    cout << "NIM : ";
    cin >> p->info.NIM;
    cout << endl;
    cout << "Judul Skripsi : ";
    cin >> p->info.judulSkripsi;
    cout << endl;
    p->info.dospem1="#";
    p->info.dospem2="#";
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
adrMhs searchMhs(listMhs Lm, string NIM){
    adrMhs p = Lm.first;
    while (p != NULL && p->info.NIM != NIM){
        p = p->next;
    }
    return p;
}

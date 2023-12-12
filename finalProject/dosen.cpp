#include "dosen.h"

void createListDosen(listDosen &Ld) {
    Ld.first=NULL;
    Ld.last=NULL;
}

adrDosen createElmtDosen() {
    adrDosen p = new ElmDosen;
    p->next=NULL;
    p->prev=NULL;
    cin >> p->info.namaDosen;
    cin >> p->info.kodeDosen;
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

adrDosen searchDosen(listDosen Ld, string kodeDosen){
    adrDosen p = Ld.first;
    while (p != NULL && p->info.kodeDosen != kodeDosen){
        p = p->next;
    }
    return p;
}

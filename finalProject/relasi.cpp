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

void createListRelasi(listRelasi &Lr) {
    Lr.first=NULL;
}

adrMhs createElmtRelasi() {
    adrRelasi p = new ElmRelasi;
    p->next=NULL;
    p->nextDosen=NULL;
    p->nextMhs=NULL;
    return p;
}

void insertLastRelasi(listRelasi &Lr, adrRelasi p) {
    if (Lr.first==NULL && Lr.last==NULL) {
        Lr.first=p;
        Lr.last=p;
    } else {
        Lr.last->next=p;
        p->prev=Lr.last;
        Lr.last=p;
    }
}
void inserFirstRelasi(listRelasi &Lr, adrRelasi p){
    if (Lr.first==NULL && Lr.last==NULL) {
            Lr.first=p;
            Lr.last=p;
        } else {
            p->next=Lr.first;
            Lr.first->prev=p;
            Lr.first=p;
        }
}
void deleteLastRelasi(listRelasi &Lr, adrRelasi &p){
    if (Lr.first==NULL && Lr.last==NULL) {
        p=NULL;
    } else if (Lr.first->next==NULL) {
        p=Lr.first;
        Lr.first=NULL;
        Lr.last=NULL;
    } else {
        p=Lr.last;
        Lr.last=p->prev;
        Lr.last->next=NULL;
        p->prev=NULL;
    }
}
void deleteAfterRelasi(listRelasi &Lr, adrRelasi prev, adrRelasi &p){
    if (prev==NULL || prev->next==NULL) {
        p=NULL;
    } else {
        p=prev->next;
        if (p->next==NULL) {
            Lr.last=p->prev;
            Lr.last->next=NULL;
            p->prev=NULL;
        } else {
            prev->next=p->next;
            (p->next)->prev=prev;
            p->next=NULL;
            p->prev=NULL;
        }
    }
}
void deleteFirstRelasi(listRelasi &Lr, adrRelasi &p){
    if (Lr.first==NULL && Lr.last==NULL) {
        p=NULL;
    } else if (Lr.first->next==NULL) {
        p=Lr.first;
        Lr.first=NULL;
        Lr.last=NULL;
    } else {
        p=Lr.first;
        Lr.first=p->next;
        p->next=NULL;
        Lr.first->prev=NULL;
    }
}

void searchRelasiByDosen(listRelasi Lr, listDosen Ld, listMhs Lm, string kodeDosen){
    adrRelasi r = Lr.first;
    adrDosen d = searchDosen(Ld,kodeDosen);
    if (d != NULL){
        while (r != NULL){
            if (r->nextDosen->info.kodeDosen==kodeDosen){
                cout << r->nextMhs->info.namaMhs << r->nextMhs->info.NIM << r->nextMhs->info.judulSkripsi << endl;
            }
            r = r->next;
        }
        cout << endl;
    } else {
        cout << "Dosen tidak ditemukan" << endl;
    }
}

void addRelasi(listRelasi &Lr, listDosen Ld, listMhs Lm, string kodeDosen, string NIM){
    adrDosen d = searchDosen(Ld, kodeDosen);
    adrMhs m = searchMhs(Lm, NIM);

    adrRelasi r = createElmtRelasi();
    r->nextDosen = d;
    r->nextMhs = m;
    inserFirstRelasi(Lr, r);
}

void deleteRelasiByDosen(listRelasi &Lr, listDosen Ld, listMhs Lm, string kodeDosen, string NIM){
    adrDosen d = searchDosen(Ld, kodeDosen);
    adrMhs m = searchMhs(Lm, NIM);
    adrRelasi r = Lr.first;

    while (r != NULL && (r->nextDosen != d || r->nextMhs != m)){
        r = r->next;
    }
    if (r != NULL){
        // Ngehapus data di infotypeMhs
        if (r->nextMhs->info.dospem1 == kodeDosen){
            r->nextMhs->info.dospem1 = "#";
        }
        if (r->nextMhs->info.dospem2 == kodeDosen){
            r->nextMhs->info.dospem2 = "#";
        }

        // NULL-in relasi
        r->nextDosen = NULL;
        r->nextMhs = NULL;

        // Ngehapus elemen relasinya
        if (r==Lr.first) {
            deleteFirstRelasi(Lr, r);
        } else if ( r->next==NULL ){
            deleteLastRelasi(Lr, r);
        } else {
            adrRelasi prev = Lr.first;
            while (prev->next!=r) {
                prev=prev->next;
            }
            deleteAfterRelasi(Lr, prev, r);
        }
    } else {
        cout << "Input tidak Valid" << endl;
    }
}

int jumMhsByDosen(listRelasi &Lr, listDosen Ld, listMhs Lm, string kodeDosen) {
    adrRelasi r = Lr.first;
    int j = 0;
    while (r!=NULL) {
        if (r->nextDosen->info.kodeDosen==kodeDosen) {
            j=j+1;
        }
    }
    return j;
}

int jumDosenByMhs(listRelasi &Lr, listDosen Ld, listMhs Lm, string NIM) {
    adrRelasi r = Lr.first;
    int j = 0;
    while (r!=NULL) {
        if (r->nextMhs->info.NIM==NIM) {
            j=j+1;
        }
    }
    return j;
}

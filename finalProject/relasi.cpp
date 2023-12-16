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

adrRelasi createElmtRelasi() {
    adrRelasi p = new ElmRelasi;
    p->next=NULL;
    p->nextDosen=NULL;
    p->nextMhs=NULL;
    return p;
}

void insertLastRelasi(listRelasi &Lr, adrRelasi p) {
    if (Lr.first==NULL) {
        Lr.first=p;
    } else {
        adrRelasi last = Lr.first;
        while (last->next!=NULL) {
            last=last->next;
        }
        last->next=p;
    }
}
void inserFirstRelasi(listRelasi &Lr, adrRelasi p){
    if (Lr.first==NULL) {
            Lr.first=p;
        } else {
            p->next=Lr.first;
            Lr.first=p;
        }
}
void deleteLastRelasi(listRelasi &Lr, adrRelasi &p){
    if (Lr.first==NULL) {
        p=NULL;
    } else if (Lr.first->next==NULL) {
        p=Lr.first;
        Lr.first=NULL;
    } else {
        adrRelasi last = Lr.first;
        while (last->next!=NULL) {
            last=last->next;
        }
        p=last;
        last->next=NULL;
    }
}
void deleteAfterRelasi(listRelasi &Lr, adrRelasi prev, adrRelasi &p){
    if (prev==NULL || prev->next==NULL) {
        p=NULL;
    } else {
        p=prev->next;
        if (p->next==NULL) {
            deleteLastRelasi(Lr, p);
        } else {
            prev->next=p->next;
            p->next=NULL;
        }
    }
}
void deleteFirstRelasi(listRelasi &Lr, adrRelasi &p){
    if (Lr.first==NULL) {
        p=NULL;
    } else if (Lr.first->next==NULL) {
        p=Lr.first;
        Lr.first=NULL;
    } else {
        p=Lr.first;
        Lr.first=p->next;
        p->next=NULL;
    }
}

void searchRelasiByDosen(listRelasi Lr, listDosen Ld, listMhs Lm, string kodeDosen){
    adrRelasi r = Lr.first;
    adrDosen d = searchDosen(Ld,kodeDosen);
    if (d != NULL){
        cout << "======================================" << endl;
        cout << "Mahasiswa yang dibimbing oleh Dosen " << d->info.namaDosen << endl;
        while (r != NULL){
            if (r->nextDosen->info.kodeDosen==kodeDosen){
                cout << r->nextMhs->info.namaMhs << r->nextMhs->info.NIM << r->nextMhs->info.judulSkripsi << endl;
            }
            r = r->next;
        }
        cout << "======================================" << endl;
        cout << endl;
    } else {
        cout << "Dosen tidak ditemukan" << endl;
    }
}

void addRelasi(listRelasi &Lr, listDosen &Ld, listMhs &Lm, string kodeDosen, string NIM){
    adrDosen d = searchDosen(Ld, kodeDosen);
    adrMhs m = searchMhs(Lm, NIM);
    if (d!=NULL && m!=NULL) {
        adrRelasi r = Lr.first;
        int jumP1 = 0;
        int jumP2 = 0;
        while (r!=NULL) {
            if (r->nextMhs->info.dospem1==kodeDosen) {
                jumP1=jumP1+1;
            }
            r=r->next;
        }
        r = Lr.first;
        while (r!=NULL) {
            if (r->nextMhs->info.dospem2==kodeDosen) {
                jumP2=jumP2+1;
            }
            r=r->next;
        }
         if (jumDosenByMhs(Lr, Ld, Lm, NIM)==0) {
            if (jumP1<3) {
                r->nextMhs->info.dospem1=kodeDosen;
                r = createElmtRelasi();
                r->nextDosen = d;
                r->nextMhs = m;
                inserFirstRelasi(Lr, r);
            } else {
                cout << "Dosen Pembimbing sibuk" << endl;
            }
        } else if (jumDosenByMhs(Lr, Ld, Lm, NIM)==1) {
            if (jumP1<5) {
                r->nextMhs->info.dospem2=kodeDosen;
                r = createElmtRelasi();
                r->nextDosen = d;
                r->nextMhs = m;
                inserFirstRelasi(Lr, r);
            } else {
                cout << "Dosen Pembimbing sibuk" << endl;
            }
        } else {
            cout << "Dosen Pembimbing Mahasiswa sudah 2" << endl;
        }
    } else {
        cout << "Kode Dosen atau NIM tidak sesuai" << endl;
    }
}

void deleteRelasiByDosen(listRelasi &Lr, listDosen &Ld, listMhs &Lm, string kodeDosen, string NIM){
    adrDosen d = searchDosen(Ld, kodeDosen);
    adrMhs m = searchMhs(Lm, NIM);
    adrRelasi r = Lr.first;

    while (r != NULL && (r->nextDosen != d || r->nextMhs != m)){
        r = r->next;
    }
    if (r != NULL){
        // Ngehapus data di infotypeMhs
        if (r->nextMhs->info.dospem1 == kodeDosen){
            // jika dospem1 di delete otomatis dospem2 jadi dospem 1
            r->nextMhs->info.dospem1 = r->nextMhs->info.dospem2;
            r->nextMhs->info.dospem2 = "#";
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


int jumMhsByDosen(listRelasi Lr, listDosen Ld, listMhs Lm, string kodeDosen) {
    adrRelasi r = Lr.first;
    int j = 0;
    while (r!=NULL) {
        if (r->nextDosen->info.kodeDosen==kodeDosen) {
            j=j+1;
        }
    }
    return j;
}

int jumDosenByMhs(listRelasi Lr, listDosen Ld, listMhs Lm, string NIM) {
    adrRelasi r = Lr.first;
    int j = 0;
    while (r!=NULL) {
        if (r->nextMhs->info.NIM==NIM) {
            j=j+1;
        }
    }
    return j;
}

void printMhs(listMhs Lm) {
    adrMhs m = Lm.first;
    if (Lm.first==NULL) {
        cout << "Tidak ada data" << endl;
    }
    while (m!=NULL) {
        cout << "Nama : " << m->info.namaMhs << endl;
        cout << "NIM : " << m->info.NIM << endl;
        cout << "Judul Skripsi : " << m->info.judulSkripsi << endl;
        cout << "Dosen Pembimbing 1 : " << m->info.dospem1 << endl;
        cout << "Dosen Pembimbing 2 : " << m->info.dospem2 << endl;
        m=m->next;
    }
}

void printDosen(listDosen Ld) {
    adrDosen d = Ld.first;
    if (Ld.first==NULL) {
        cout << "Tidak ada data" << endl;
    }
    while (d!=NULL) {
        cout << "Nama : " << d->info.namaDosen << endl;
        cout << "Kode Dosen : " << d->info.kodeDosen << endl;
        cout << "NIP : " << d->info.NIP << endl;
        d=d->next;
    }
}

void maxDosen(listRelasi Lr, listDosen Ld, listMhs Lm) {
    int max = jumMhsByDosen(Lr, Ld, Lm, Ld.first->info.kodeDosen);
    adrDosen d = Ld.first;
    while (d!=NULL) {
        if (jumMhsByDosen(Lr, Ld, Lm, d->info.kodeDosen)>max ) {
            max=jumMhsByDosen(Lr, Ld, Lm, d->info.kodeDosen);
        }
        d=d->next;
    }
    d=Ld.first;
    cout << "Dosen yang memiliki mahasiswa bimbingan terbanyak dengan jumlah " << max << endl;
    while (d!=NULL) {
        if (jumMhsByDosen(Lr, Ld, Lm, d->info.kodeDosen)==max) {
            cout << "Nama : " << d->info.namaDosen << endl;
            cout << "Kode Dosen : " << d->info.kodeDosen << endl;
            cout << "NIP : " << d->info.NIP << endl;
        }
        d=d->next;
    }
}

void deleteRelasiMhs(listRelasi &Lr, listDosen &Ld, listMhs &Lm, adrMhs &m) {
    adrRelasi r = Lr.first;
    adrRelasi prev;
    while (r!=NULL) {
        if (r->nextMhs==m) {
            r->nextMhs->info.dospem1="#";
            r->nextMhs->info.dospem2="#";
            r->nextMhs=NULL;
            r->nextDosen=NULL;
            if (r==Lr.first) {
                deleteFirstRelasi(Lr, r);
            } else if ( r->next==NULL ){
                deleteLastRelasi(Lr, r);
            } else {
                prev = Lr.first;
                while (prev->next!=r) {
                    prev=prev->next;
                }
                deleteAfterRelasi(Lr, prev, r);
            }
        }
        r=r->next;
    }
}
void deleteRelasiDosen(listRelasi &Lr, listDosen &Ld, listMhs &Lm, adrDosen &d) {
    adrRelasi r = Lr.first;
    adrRelasi prev;
    while (r!=NULL) {
        if (r->nextDosen==d) {
            if (r->nextMhs->info.dospem1 == d->info.kodeDosen){
            // jika dospem1 di delete otomatis dospem2 jadi dospem 1
            r->nextMhs->info.dospem1 = r->nextMhs->info.dospem2;
            r->nextMhs->info.dospem2 = "#";
            }
            if (r->nextMhs->info.dospem2 == d->info.kodeDosen){
                r->nextMhs->info.dospem2 = "#";
            }
            r->nextMhs=NULL;
            r->nextDosen=NULL;
            if (r==Lr.first) {
                deleteFirstRelasi(Lr, r);
            } else if ( r->next==NULL ){
                deleteLastRelasi(Lr, r);
            } else {
                prev = Lr.first;
                while (prev->next!=r) {
                    prev=prev->next;
                }
                deleteAfterRelasi(Lr, prev, r);
            }
        }
        r=r->next;
    }
}

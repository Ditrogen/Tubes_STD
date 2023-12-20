#include "relasi.h"

void menu() {
    cout << "=========================================================" << endl;
    cout << "Halaman Depan Final Project" << endl;
    cout << endl;
    cout << "Silahkan pilih opsi berikut: " << endl;
    cout << "1. Menambah data mahasiswa" << endl;
    cout << "2. Menambah data dosen" << endl;
    cout << "3. Mencari data mahasiswa" << endl;
    cout << "4. Menambah relasi dospem dengan mahasiswa" << endl;
    cout << "5. Mencari mahasiswa yang dibimbing oleh dosen tertentu" << endl;
    cout << "6. Menghapus dosen beserta relasinya" << endl;
    cout << "7. Menghapus data dosen yang membimbing mahasiswa tertentu" << endl;
    cout << "8. Menampilkan seluruh mahasiswa beserta dospem 1 dan 2" << endl;
    cout << "9. Menampilkan dospem dengan jumlah bimbingan terbanyak" << endl;
    cout << "10. Menampilkan mahasiswa yang hanya memiliki 1 dospem" << endl;
    cout << "Tekan 0 untuk Keluar Program" << endl;
    cout << "=========================================================" << endl;
}

void createListRelasi(listRelasi &Lr) {
    Lr.first=NULL;
}

adrRelasi createElmtRelasi() {
    adrRelasi p = new ElmRelasi;
    p->next=NULL;
    p->nextDosen =NULL;
    p->nextMhs=NULL;
    return p;
}

void insertLastRelasi(listRelasi &Lr, adrRelasi p) {
    if (Lr.first==NULL) {
        Lr.first=p;
    } else {
        adrRelasi r = Lr.first;
        while (r->next != NULL){
            r = r->next;
        }
        r->next = p;
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
        adrRelasi r = Lr.first;
        while (r->next->next != NULL){
            r = r->next;
        }
        p = r->next;
        r->next = NULL;
    }
}
void deleteAfterRelasi(listRelasi &Lr, adrRelasi prev, adrRelasi &p){
    if (prev==NULL || prev->next==NULL) {
        p=NULL;
    } else {
        p=prev->next;
        if (p->next==NULL) {
            prev->next = NULL;
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
    adrDosen d = searchDosenByKode(Ld,kodeDosen);
    if (d != NULL){
        cout << "======================================" << endl;
        cout << "Mahasiswa yang dibimbing oleh Dosen " << d->info.namaDosen << endl;
        while (r != NULL){
            if (r->nextDosen->info.kodeDosen==kodeDosen){
                cout << r->nextMhs->info.namaMhs << r->nextMhs->info.NIM << endl;
            }
            r = r->next;
        }
        cout << "======================================" << endl;
        cout << endl;
    } else {
        cout << "Dosen tidak ditemukan" << endl;
    }
}

void addRelasi(listRelasi &Lr, listDosen Ld, listMhs Lm, string NIP, string NIM){
    // mencari dosen dan mahasiswa
    adrDosen d = searchDosenByNIP(Ld, NIP);
    adrMhs m = searchMhsByNIM(Lm, NIM);

    // Cek jika dosen dan mahasiswa ketemu
    if (d != NULL && m !=  NULL){
        // Jika ketemu, cek dospem yang kosong
        if (m->info.dospem1 == "-"){
            // cek apakah dosen memiliki slot untuk dospem1
            if (d->info.countDospem1 < NMAX1){
                adrRelasi r = createElmtRelasi();
                r->nextDosen = d;
                r->nextDosen->info.countDospem1++;
                r->nextMhs = m;
                r->nextMhs->info.dospem1 = r->nextDosen->info.kodeDosen;
                r->nextMhs->info.NIP1 = r->nextDosen->info.NIP;
                inserFirstRelasi(Lr, r);
            } else {
                cout << "Batas Dosen Sebagai Pembimbing Pertama Tercapai" << endl;
            }
        } else if (m->info.dospem2 == "-" && m->info.NIP1 != d->info.NIP) {
            // cek apakah dosen memiliki slot untuk dospem2
            if (d->info.countDospem2 < NMAX2){
                adrRelasi r = createElmtRelasi();
                r->nextDosen = d;
                r->nextDosen->info.countDospem2++;
                r->nextMhs = m;
                r->nextMhs->info.dospem2 = r->nextDosen->info.kodeDosen;
                r->nextMhs->info.NIP2 = r->nextDosen->info.NIP;
                inserFirstRelasi(Lr, r);
            } else {
                cout << "Batas Dosen Sebagai Pembimbing Kedua Tercapai" << endl;
            }
        } else {
            // Error handling, berisikan tempat
            if (m->info.NIP1 == d->info.NIP || m->info.NIP2 == d->info.NIP){
                cout << "Tidak bisa menambahkan dosen yang sudah menjadi pembimbing" << endl;
            } else if (m->info.dospem1 != "-" && m->info.dospem2 == "-"){
                cout << "Mahasiswa Sudah Memiliki Dosen Pembimbing Pertama" << endl;
            } else {
                cout << "Mahasiswa Sudah Memiliki Dua Dosen Pembimbing" << endl;
            }
        }
    } else {
        if (d == NULL) {
            cout << "Dosen tidak ditemukan" << endl;
        } else if (m == NULL){
            cout << "Mahasiswa tidak ditemukan" << endl;
        } else {
            cout << "Dosen dan mahasiswa tidak ditemukan" << endl;
        }
    }


}

void deleteRelasiByDosen(listRelasi &Lr, listDosen Ld, listMhs Lm, string kodeDosen, string NIM){
    adrDosen d = searchDosenByKode(Ld, kodeDosen);
    adrMhs m = searchMhsByNIM(Lm, NIM);
    adrRelasi r = Lr.first;

    // mencari dosen dan mahasiswa
    while (r != NULL && (r->nextDosen != d || r->nextMhs != m)){
        r = r->next;
    }

    // Jika tidak null, lakukan penghapusan
    if (r != NULL){
        // Ngehapus data di infotypeMhs
        if (r->nextMhs->info.dospem1 == kodeDosen){
            r->nextMhs->info.dospem1 = "#";
            r->nextDosen->info.countDospem1--;
        }
        if (r->nextMhs->info.dospem2 == kodeDosen){
            r->nextMhs->info.dospem2 = "#";
            r->nextDosen->info.countDospem2--;
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
void showAllRelasi(listRelasi Lr){
    adrRelasi p = Lr.first;
    while (p != NULL){
        cout << p->nextDosen->info.countDospem1 << " " << p->nextMhs->info.dospem1 << endl;
        p = p->next;
    }
    cout << endl;
}

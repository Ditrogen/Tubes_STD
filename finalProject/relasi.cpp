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

void addRelasi(listRelasi &Lr, listDosen Ld, listMhs Lm, string NIP, string NIM){
    // mencari dosen dan mahasiswa
    adrDosen d = searchDosenByNIP(Ld, NIP);
    adrMhs m = searchMhsByNIM(Lm, NIM);

    // Cek jika dosen dan mahasiswa ketemu
    if (d != NULL && m !=  NULL){
        // Jika ketemu, cek dospem yang kosong
        if (m->info.dospem1 == "-" && m->info.dospem2 != d->info.kodeDosen){
            // cek apakah dosen memiliki slot untuk dospem1
            if (d->info.countDospem1 < NMAX1){
                adrRelasi r = createElmtRelasi();
                r->nextDosen = d;
                r->nextDosen->info.countDospem1=r->nextDosen->info.countDospem1+1;
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
            // Error handling
            if (m->info.NIP1 == d->info.NIP || m->info.NIP2 == d->info.NIP){
                cout << "Tidak bisa menambahkan dosen yang sudah menjadi pembimbing" << endl;
            } else if (m->info.dospem1 != "-" && m->info.dospem2 == "-"){
                cout << "Mahasiswa Sudah Memiliki Dosen Pembimbing Pertama" << endl;
            } else {
                cout << "Mahasiswa Sudah Memiliki Dua Dosen Pembimbing" << endl;
            }
        }
    } else {
        if (d == NULL && m != NULL) {
            cout << "Dosen tidak ditemukan" << endl;
        } else if (m == NULL && d != NULL){
            cout << "Mahasiswa tidak ditemukan" << endl;
        } else {
            cout << "Dosen dan mahasiswa tidak ditemukan" << endl;
        }
    }
}

void deleteRelasiByNIPDosenDanNIMMhs(listRelasi &Lr, listDosen &Ld, listMhs &Lm, string NIP, string NIM){
    adrDosen d = searchDosenByNIP(Ld, NIP);
    adrMhs m = searchMhsByNIM(Lm, NIM);
    adrRelasi r = Lr.first;

    // mencari dosen dan mahasiswa
    while (r != NULL && (r->nextDosen != d || r->nextMhs != m)){
        r = r->next;
    }

    // Jika tidak null, lakukan penghapusan
    if (r != NULL){
        // Ngehapus data di infotypeMhs
        if (r->nextMhs->info.NIP1 == NIP){
            // jika ada dospem2, dospem2 berubah jadi dospem1nya
            if (r->nextMhs->info.NIP2 != "-"){
                // Ngecek klo jumlah dospem1 dosen kedua masih bisa nambah, klo ngak, tetep jadi dospem2
                adrDosen d2 = searchDosenByNIP(Ld, r->nextMhs->info.NIP2);
                if (d2->info.countDospem1 < NMAX1){
                    r->nextMhs->info.dospem1 = r->nextMhs->info.dospem2;
                    r->nextMhs->info.dospem2 = "-";
                    r->nextMhs->info.NIP1 = r->nextMhs->info.NIP2;
                    r->nextMhs->info.NIP2 = "-";
                    r->nextDosen->info.countDospem1--;
                    d2->info.countDospem1++;
                    d2->info.countDospem2--;
                } else {
                    r->nextMhs->info.dospem1 = "-";
                    r->nextMhs->info.NIP1 = "-";
                    r->nextDosen->info.countDospem1--;
                }
            } else {
                r->nextMhs->info.dospem1 = r->nextMhs->info.dospem2;
                r->nextMhs->info.NIP1 = r->nextMhs->info.NIP2;
                r->nextDosen->info.countDospem1--;
            }
        }
        if (r->nextMhs->info.NIP2 == NIP){
            r->nextMhs->info.dospem2 = "-";
            r->nextMhs->info.NIP2 = "-";
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

void deleteAllDosenByNIPDosen(listRelasi &Lr, listDosen &Ld, listMhs &Lm, string NIP){
    adrDosen d = searchDosenByNIP(Ld, NIP);
    if (d != NULL){
        if (Lr.first != NULL){
            adrRelasi r = Lr.first;
            adrRelasi q;
            adrRelasi prev;
            while (r != NULL){
                if (r->nextDosen == d) {
                    if (r->nextMhs->info.NIP1 == NIP){
                    // jika ada dospem2, dospem2 berubah jadi dospem1nya
                    if (r->nextMhs->info.NIP2 != "-"){
                        // Ngecek klo jumlah dospem1 dosen kedua masih bisa nambah, klo ngak, tetep jadi dospem2
                        adrDosen d2 = searchDosenByNIP(Ld, r->nextMhs->info.NIP2);
                        if (d2->info.countDospem1 < NMAX1){
                            r->nextMhs->info.dospem1 = r->nextMhs->info.dospem2;
                            r->nextMhs->info.dospem2 = "-";
                            r->nextMhs->info.NIP1 = r->nextMhs->info.NIP2;
                            r->nextMhs->info.NIP2 = "-";
                            r->nextDosen->info.countDospem1--;
                            d2->info.countDospem1++;
                            d2->info.countDospem2--;
                        } else {
                            r->nextMhs->info.dospem1 = "-";
                            r->nextMhs->info.NIP1 = "-";
                            r->nextDosen->info.countDospem1--;
                        }
                    } else {
                        r->nextMhs->info.dospem1 = r->nextMhs->info.dospem2;
                        r->nextMhs->info.NIP1 = r->nextMhs->info.NIP2;
                        r->nextDosen->info.countDospem1--;
                    }
                }
                if (r->nextMhs->info.NIP2 == NIP){
                    r->nextMhs->info.dospem2 = "-";
                    r->nextMhs->info.NIP2 = "-";
                    r->nextDosen->info.countDospem2--;
                }

                    r->nextDosen = NULL;
                    r->nextMhs = NULL;

                    if (r==Lr.first) {
                        deleteFirstRelasi(Lr, r);
                        r = Lr.first;
                    } else if ( r->next==NULL ){
                        deleteLastRelasi(Lr, r);
                    } else {
                        prev = Lr.first;
                        while (prev->next!=r) {
                            prev=prev->next;
                        }
                        deleteAfterRelasi(Lr, prev, r);
                        r = prev;
                    }
                } else {
                    r = r->next;
                }
            }
        }
        if (d==Ld.first) {
            deleteFirstDosen(Ld, d);
        } else if (d==Ld.last) {
            deleteLastDosen(Ld, d);
        } else {
            adrDosen prev = Ld.first;
            while (prev->next!=d) {
                prev=prev->next;
            }
            deleteAfterDosen(Ld, prev, d);
        }
    } else {
        cout << "Dosen tidak ditemukan" << endl;
    }
}

void showAllRelasi(listRelasi Lr){
    adrRelasi p = Lr.first;
    while (p != NULL){
        cout << p->nextDosen->info.namaDosen << "=" << p->nextMhs->info.namaMhs << " -> ";
        p = p->next;
    }
    cout << endl;
}
void showHighestDospemCount(listDosen Ld){
    adrDosen p = Ld.first;
    int maxCount = 0;
    int current;

    // Nyari nilai maxnya
    while (p != NULL){
        current = p->info.countDospem1 + p->info.countDospem2;
        if (current > maxCount){
            maxCount = current;
        }
        p = p->next;
    }

    // Menampilkan semua dosen yang memiliki jumlah bimbingan yg sama dengan max
    p = Ld.first;
    cout << "Dosen yang memiliki jumlah bimbingan terbanyak: " << endl;
    while (p != NULL){
        current = p->info.countDospem1 + p->info.countDospem2;
        if (current == maxCount){
            cout << "Nama Dosen: " << p->info.namaDosen << endl;
            cout << "NIP: " << p->info.NIP << endl;
            cout << "Jumlah bimbingan total: " << current << endl;
            cout << endl;
        }
        p = p->next;
    }
    cout << endl;
}

void showSingleDospemCount(listRelasi Lr){
    adrRelasi r = Lr.first;
    int i=0;
    while (r != NULL) {
        if (r->nextMhs->info.NIP1 == "-" || r->nextMhs->info.NIP2 == "-"){
            cout << "Nama Mahasiswa: " << r->nextMhs->info.namaMhs << endl;
            cout << "NIM Mahasiswa: " << r->nextMhs->info.NIM << endl;
            cout << endl;
            i=i+1;
        }
        r = r->next;
    }
    if (i==0) {
        cout << "Tidak ada mahasiswa yang memiliki 1 dosen pembimbing" << endl;
    }
}

void dummy(listDosen &Ld, listMhs &Lm) {
    adrMhs m = new ElmMhs;

    // dummy mhs 1
    m->next=NULL;
    m->prev=NULL;
    m->info.namaMhs="Azizah Salma";
    m->info.NIM="1301220021";
    m->info.dospem1="-";
    m->info.dospem2="-";
    m->info.NIP1="-";
    m->info.NIP2="-";
    insertFirstMhs(Lm, m);

    // dummy mhs2
    adrMhs m2 = new ElmMhs;
    m2->next=NULL;
    m2->prev=NULL;
    m2->info.namaMhs="Yohanes Januarico";
    m2->info.NIM="1301223430";
    m2->info.dospem1="-";
    m2->info.dospem2="-";
    m2->info.NIP1="-";
    m2->info.NIP2="-";
    insertFirstMhs(Lm, m2);

    // dummy mhs3
    adrMhs m3 = new ElmMhs;
    m3->next=NULL;
    m3->prev=NULL;
    m3->info.namaMhs="Putri Rohayu";
    m3->info.NIM="1301221111";
    m3->info.dospem1="-";
    m3->info.dospem2="-";
    m3->info.NIP1="-";
    m3->info.NIP2="-";
    insertFirstMhs(Lm, m3);

    // dummy dosen 1
    adrDosen d = new ElmDosen;
    d->next=NULL;
    d->prev=NULL;
    d->info.namaDosen="Pakarima";
    d->info.NIP="12345";
    d->info.kodeDosen="PPK";
    d->info.countDospem1=0;
    d->info.countDospem2=0;
    insertLastDosen(Ld, d);

    // dummy dosen 2
    adrDosen d2 = new ElmDosen;
    d2->next=NULL;
    d2->prev=NULL;
    d2->info.namaDosen="Lakana";
    d2->info.NIP="67898";
    d2->info.kodeDosen="LKA";
    d2->info.countDospem1=0;
    d2->info.countDospem2=0;
    insertLastDosen(Ld, d2);

}


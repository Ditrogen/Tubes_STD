#ifndef RELASI_H_INCLUDED
#define RELASI_H_INCLUDED

#include "dosen.h"
#include "mahasiswa.h"

typedef struct ElmRelasi *adrRelasi;

struct ElmRelasi {
    adrRelasi next;
    adrDosen nextDosen;
    adrMhs nextMhs;
};

struct listRelasi {
    adrRelasi first;
};

void createListRelasi(listRelasi &Lr);
adrRelasi createElmtRelasi();
void inserFirstRelasi(listRelasi &Lr, adrRelasi p);
void deleteLastRelasi(listRelasi &Lr, adrRelasi &p);
void deleteAfterRelasi(listRelasi &Lr, adrRelasi prev, adrRelasi &p);
void deleteFirstRelasi(listRelasi &Lr, adrRelasi &p);
void addRelasi(listRelasi &Lr, listDosen Ld, listMhs Lm, string kodeDosen, string NIM);
void deleteRelasiByNIPDosenDanNIMMhs(listRelasi &Lr, listDosen &Ld, listMhs &Lm, string NIP, string NIM);
void deleteAllDosenByNIPDosen(listRelasi &Lr, listDosen &Ld, listMhs &Lm, string NIP);
void dummy(listDosen &Ld, listMhs &Lm);
void menu();

void showAllRelasi(listRelasi Lr);
void showHighestDospemCount(listDosen Ld);
void showSingleDospemCount(listRelasi Lr);
#endif // RELASI_H_INCLUDED


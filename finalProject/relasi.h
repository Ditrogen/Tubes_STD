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
void insertLastRelasi(listRelasi &Lr, adrRelasi p);
void inserFirstRelasi(listRelasi &Lr, adrRelasi p);
void deleteLastRelasi(listRelasi &Lr, adrRelasi &p);
void deleteAfterRelasi(listRelasi &Lr, adrRelasi prev, adrRelasi &p);
void deleteFirstRelasi(listRelasi &Lr, adrRelasi &p);
adrRelasi searchRelasi(listRelasi Lr, adrRelasi p);
void searchRelasiByDosen(listRelasi Lr, listDosen Ld, listMhs Lm, string kodeDosen);
void addRelasi(listRelasi &Lr, listDosen &Ld, listMhs &Lm, string kodeDosen, string NIM);
void deleteRelasiByDosen(listRelasi &Lr, listDosen &Ld, listMhs &Lm, string kodeDosen, string NIM);
int jumMhsByDosen(listRelasi Lr, listDosen Ld, listMhs Lm, string kodeDosen);
int jumDosenByMhs(listRelasi Lr, listDosen Ld, listMhs Lm, string NIM);
void printMhs(listMhs Lm);
void printDosen(listDosen Ld);
void maxDosen(listRelasi Lr, listDosen Ld, listMhs Lm);
void deleteRelasiMhs(listRelasi &Lr, listDosen &Ld, listMhs &Lm, adrMhs &m);
void deleteRelasiDosen(listRelasi &Lr, listDosen &Ld, listMhs &Lm, adrDosen &d);
void menu();

void showAllRelasi(listRelasi Lr);
#endif // RELASI_H_INCLUDED

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
adrMhs createElmtRelasi();
void insertLastRelasi(listRelasi &Lr, adrRelasi p);
void deleteLastRelasi(listRelasi &Lr, adrRelasi &p);
void deleteAfterRelasi(listRelasi &Lr, adrRelasi prev, adrRelasi &p);
void deleteFirstRelasi(listRelasi &Lr, adrRelasi &p);

#endif // RELASI_H_INCLUDED

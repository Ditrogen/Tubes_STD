#ifndef MAHASISWA_H_INCLUDED
#define MAHASISWA_H_INCLUDED

#include <iostream>
using namespace std;

struct infomahasiswa {
    string namaMhs, NIM, judulSkripsi;
    string dospem1, dospem2;
};

typedef struct infomahasiswa infotypeMhs;
typedef struct ElmMhs* adrMhs;

struct ElmMhs {
    infotypeMhs info;
    adrMhs next, prev;
};

struct listMhs {
    adrMhs first, last;
};

void createListMhs(listMhs &Lm);
adrMhs createElmtMhs();
void insertLastMhs(listMhs &Lm, adrMhs p);
void insertFirstMhs(listMhs &Lm, adrMhs p);
void deleteLastMhs(listMhs &Lm, adrMhs &p);
void deleteAfterMhs(listMhs &Lm, adrMhs prev, adrMhs &p);
void deleteFirstMhs(listMhs &Lm, adrMhs &p);
adrMhs searchMhs(listMhs Lm, string NIM);



#endif // MAHASISWA_H_INCLUDED

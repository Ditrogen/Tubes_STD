#ifndef DOSEN_H_INCLUDED
#define DOSEN_H_INCLUDED

#include <iostream>
using namespace std;

typedef struct infodosen infotypeDosen;
typedef struct ElmDosen *adrDosen;

struct infodosen {
    string namaDosen;
    string kodeDosen;
    string NIP;
    int jumPembimbing1;
    int jumPembimbing2;
};

struct ElmDosen {
    infotypeDosen info;
    adrDosen next;
    adrDosen prev;
};

struct listDosen {
    adrDosen first;
    adrDosen last;
};

adrDosen createElmtDosen();
void createListDosen(listDosen &Ld);
void insertLastDosen(listDosen &Ld, adrDosen p);
void deleteLastDosen(listDosen &Ld, adrDosen &p);
void deleteAfterDosen(listDosen &Ld, adrDosen prev, adrDosen &p);
void deleteFirstDosen(listDosen &Ld, adrDosen &p);


#endif // DOSEN_H_INCLUDED

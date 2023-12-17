#ifndef DOSEN_H_INCLUDED
#define DOSEN_H_INCLUDED

#include <iostream>
using namespace std;

typedef struct infodosen infotypeDosen;
typedef struct ElmDosen *adrDosen;

const int NMAX1 = 3;
const int NMAX2 = 5;

struct infodosen {
    string namaDosen;
    string kodeDosen;
    string NIP;
    int countDospem1, countDospem2;
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
void insertFirstDosen(listDosen &Ld, adrDosen p);
void deleteLastDosen(listDosen &Ld, adrDosen &p);
void deleteAfterDosen(listDosen &Ld, adrDosen prev, adrDosen &p);
void deleteFirstDosen(listDosen &Ld, adrDosen &p);
adrDosen searchDosenByKode(listDosen Ld, string kodeDosen);
adrDosen searchDosenByNIP(listDosen Ld, string NIP);
void showAllDosen(listDosen Ld);


#endif // DOSEN_H_INCLUDED

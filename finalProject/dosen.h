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


#endif // DOSEN_H_INCLUDED

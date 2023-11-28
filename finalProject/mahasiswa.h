#ifndef MAHASISWA_H_INCLUDED
#define MAHASISWA_H_INCLUDED

struct infomahasiswa {
    string namaMhs, NIM, judulSkripsi;
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



#endif // MAHASISWA_H_INCLUDED

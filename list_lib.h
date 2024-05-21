#ifndef LIST_LIB_H_INCLUDED
#define LIST_LIB_H_INCLUDED

#include <stdbool.h>
#include <stdlib.h>
#include "types.h"


typedef struct T_cell{
    struct T_cell *suiv;
    struct T_cell *prec;
    Tunite *pdata;
}T_cellule;

typedef T_cellule *T_liste;

void initListe(T_liste *l);
bool listeVide(T_liste l);

T_liste getptrFirstCell(T_liste l);
T_liste getptrLastCell(T_liste l);
T_liste getptrNextCell(T_liste l);
T_liste getptrPrevCell(T_liste l);

void afficheListePtrUnit(T_liste l);

Tunite* getPtrData(T_liste l);
Tunite getData(T_liste l);
void swapPtrData(T_liste source, T_liste destination);

int getNbreCell(T_liste l);
int getSizeBytes(T_liste l);

#endif // LIST_LIB_H_INCLUDED

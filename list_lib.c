#include "list_lib.h"

//Ces fonctions proviennent d'un TP précédent, nous les avions déjà faites.

void initListe(T_liste *l){
    *l=NULL;
}
bool listeVide( T_liste l){
    return (l==NULL);
}
void afficheListePtrUnit(T_liste l){
    T_liste courant = l;

    if(listeVide(l))
    {
        printf("\nliste vide !");
        return;
    }
    printf("\nLISTE:\n");

    while (courant!=NULL){
        printf("\n%p",getPtrData(courant));
        courant = getptrNextCell(courant);
    }
}

T_liste getptrFirstCell(T_liste l){
    return l;
}
T_liste getptrLastCell(T_liste l){
        if (l==NULL)
        {
            return NULL;
        }
        T_liste tmp=l;
        while(tmp->suiv!=NULL)
        {
            tmp=tmp->suiv;
        }
    return tmp;
}
T_liste getptrNextCell(T_liste l){
    if (l->suiv==NULL)
    {
        return NULL;
    }
    return l->suiv;
}
T_liste getptrPrevCell(T_liste l){
    if (l->prec==NULL)
    {
        return NULL;
    }
    return l->prec;
}

Tunite* getPtrData(T_liste l){
    return l->pdata;
}
Tunite getData(T_liste l){
    return *(getPtrData(l));
}

int getNbreCell(T_liste l){ //Tested - Works
    int i=1;
    if (listeVide(l))
    {
        return 0;
    }
    T_liste tmp=l;
    while(getptrNextCell(tmp)!=NULL)
    {
        tmp=getptrNextCell(tmp);
        i++;
    }
    return i;
}
int getSizeBytes(T_liste l){ //Tested - Works
    return (sizeof(struct T_cell)*getNbreCell(l));
}


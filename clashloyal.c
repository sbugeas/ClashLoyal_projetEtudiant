#include "SDL.h"
#include "types.h"
#include "list_lib.h"
#include "clashloyal.h"
#include <stdio.h>
#include <stdlib.h>


int calcDistance(Tunite *fstUnit, Tunite *scdUnit){
    int fstUnitPosX = fstUnit->posX;
    int fstUnitPosY = fstUnit->posY;

    int scdUnitPosX = scdUnit->posX;
    int scdUnitPosY = scdUnit->posY;

    int diffX = abs(scdUnitPosX - fstUnitPosX);
    int diffY = abs(fstUnitPosY - scdUnitPosY);

    return max(diffX,diffY);

}

//////////////////FOURNIE////////////////////////
TplateauJeu AlloueTab2D(int largeur, int hauteur){
    TplateauJeu jeu;
    jeu = (Tunite***)malloc(sizeof(Tunite**)*largeur);
    for (int i=0;i<largeur;i++){
        jeu[i] = (Tunite**)malloc(sizeof(Tunite*)*hauteur);
    }
    return jeu;  //tab2D contenant des pointeurs
}
/////////////////////////////////////////////////

void initPlateauAvecNULL(TplateauJeu jeu,int largeur, int hauteur){
    for (int i=0;i<largeur;i++){
        for (int j=0;j<hauteur;j++){
            jeu[i][j] = NULL;
        }
    }
}

//////////////////FOURNIE////////////////////////
void affichePlateauConsole(TplateauJeu jeu, int largeur, int hauteur){
    //pour un affichage sur la console, en relation avec enum TuniteDuJeu
    const char* InitialeUnite[6]={"T", "R", "A", "C", "D", "G"};

    printf("\n");
    for (int j=0;j<hauteur;j++){
        for (int i=0;i<largeur;i++){
                // A ne pas donner aux etudiants
            if (jeu[i][j] != NULL){
                    printf("%s",InitialeUnite[jeu[i][j]->nom]);
            }
            else printf(" ");  //cad pas d'unité sur cette case
        }
        printf("\n");
    }
}
/////////////////////////////////////////////////


void PositionnePlayerOnPlateau(TListePlayer player, TplateauJeu jeu){
    if(player == NULL)
    {
        return;
    }

    TListePlayer curUnit = player;
    while(curUnit != NULL)
    {
        //On récupère position
        int posX = GetUnitPosX(curUnit);
        int posY = GetUnitPosY(curUnit);
        //Vérifie qu'il n'y a pas déjà une unité dans cette case
        if(jeu[posX][posY] == NULL) //Pointeur sur T_Unite nul
        {
            jeu[posX][posY] = curUnit->pdata;
        }
        curUnit = curUnit->suiv;
    }
}

/////////////// COLLEGUE /////////////////////////
Tunite *creeTourRoi(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = tourRoi;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = sol;
    nouv->pointsDeVie = 800;
    nouv->vitesseAttaque = 1.2;
    nouv->degats = 120;
    nouv->portee = 4;
    nouv->vitessedeplacement = 0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    nouv->coutEnElixir = 0;
    return nouv;
}
Tunite *creeTour(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = tour;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = sol;
    nouv->pointsDeVie = 500;
    nouv->vitesseAttaque = 1.0;
    nouv->degats = 100;
    nouv->portee = 3;
    nouv->vitessedeplacement = 0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    nouv->coutEnElixir = 0;
    return nouv;
}
Tunite *creeArcher(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = archer;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = sol;
    nouv->pointsDeVie = 80;
    nouv->vitesseAttaque = 0.7;
    nouv->degats = 120;
    nouv->portee = 3;
    nouv->vitessedeplacement = 1.0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    nouv->coutEnElixir = 2;
    return nouv;
}
Tunite *creeChevalier(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = chevalier;
    nouv->cibleAttaquable = sol;
    nouv->maposition = sol;
    nouv->pointsDeVie = 400;
    nouv->vitesseAttaque = 1.5;
    nouv->degats = 250;
    nouv->portee = 1;
    nouv->vitessedeplacement = 2.0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    nouv->coutEnElixir = 4;
    return nouv;
}
Tunite *creeDragon(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = dragon;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = air;
    nouv->pointsDeVie = 200;
    nouv->vitesseAttaque = 1.1;
    nouv->degats = 70;
    nouv->portee = 2;
    nouv->vitessedeplacement = 2.0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    nouv->coutEnElixir = 3;
    return nouv;
}
Tunite *creeGargouille(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = gargouille;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = air;
    nouv->pointsDeVie = 80;
    nouv->vitesseAttaque = 0.6;
    nouv->degats = 90;
    nouv->portee = 1;
    nouv->vitessedeplacement = 3.0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    nouv->coutEnElixir = 1;
    return nouv;
}
/////////////////////////////////////////////////

TuniteDuJeu GetUnitName(TListePlayer curUnit){
    return curUnit->pdata->nom;
}
int GetUnitPosX(TListePlayer curUnit){
    return curUnit->pdata->posX;
}
int GetUnitPosY(TListePlayer curUnit){
    return curUnit->pdata->posY;
}
int GetUnitHP(TListePlayer curUnit){
    return curUnit->pdata->pointsDeVie;
}
float GetUnitMoveSpeed(TListePlayer curUnit){
    return curUnit->pdata->vitessedeplacement;
}
float GetUnitAttackSpeed(TListePlayer curUnit){
    return curUnit->pdata->vitesseAttaque;
}
int GetUnitDamage(TListePlayer curUnit){
    return curUnit->pdata->degats;
}
int GetUnitRange(TListePlayer curUnit){
    return curUnit->pdata->portee;
}
int ThisUnitCanAttack(TListePlayer curUnit){
    return curUnit->pdata->peutAttaquer;
}
Tcible GetUnitType(TListePlayer curUnit){
    return curUnit->pdata->maposition;
}
Tcible GetUnitTargetType(TListePlayer curUnit){
    return curUnit->pdata->cibleAttaquable;
}

/////////////// COLLEGUE /////////////////////////
bool tourRoiDetruite(TListePlayer player){
    if(listeVide(player))
    {
        return true;
    }
    else
    {
        //On récupère adresse dernière cellule
        TListePlayer ptrLastCell = getptrLastCell(player);
        if(GetUnitName(ptrLastCell)== tourRoi)
        {
            return false;
        }
        else return true;
    }
}
/////////////// COLLEGUE /////////////////////////

void AjouterUnite(TListePlayer *player, Tunite *nouvelleUnite){

    //On ajoute AU DEBUT

    if(nouvelleUnite == NULL)
    {
        return;
    }

    //Allocation mémoire pour nvlle cellule + valeur data(unité)
    T_cellule *p_new_cell = (T_cellule*)malloc(sizeof(T_cellule));
    p_new_cell->pdata = (Tunite*)malloc(sizeof(Tunite));

    TListePlayer tmp_p = *player;

    //Affectation valeur paramètre
    p_new_cell->pdata = nouvelleUnite;

    if(listeVide(*player))
    {
        p_new_cell->suiv = NULL;
        p_new_cell->prec = NULL;

        *player = p_new_cell;
    }
    else //Modifier pour ajout en début de liste
    {
        p_new_cell->suiv = tmp_p;
        p_new_cell->prec = NULL;
        tmp_p->prec = p_new_cell;

        *player = p_new_cell;

    }
}
void supprimerUnite(TListePlayer *player, Tunite *destroyedUnit) {

    if (listeVide(*player)) {
        return;
    }

    TListePlayer tmp = *player;

    while (tmp != NULL) {
        if (getPtrData(tmp) == destroyedUnit) {

            // Si en début de liste
            if (getptrPrevCell(tmp) == NULL) {

                *player = getptrNextCell(tmp);

                if (*player != NULL) {
                    (*player)->prec = NULL;
                }

            }
            // Si en fin de liste
            else if (getptrNextCell(tmp) == NULL) {
                tmp->prec->suiv = NULL;
            }
            // Si au milieu
            else {
                tmp->prec->suiv = getptrNextCell(tmp);
                tmp->suiv->prec = getptrPrevCell(tmp);
            }

            free(tmp);
            tmp = NULL;

            return;
        }
        tmp = getptrNextCell(tmp);
    }

    return;
}

/////////////// COLLEGUE /////////////////////////
void giveElixir(int *elixirEnStockduJoueur){

    if(*elixirEnStockduJoueur < MAXELIXIR)
    {
        int randNum = (rand() % 3) +1; //donne donner 1 à 3

        if((*elixirEnStockduJoueur + randNum) > MAXELIXIR)
        {
            *elixirEnStockduJoueur = MAXELIXIR;
        }
        else *elixirEnStockduJoueur = *elixirEnStockduJoueur + randNum;
    }
}
Tunite *AcheteUnite(int *elixirEnStockduJoueur, TListePlayer player, TplateauJeu jeu) {
    int randNum = rand() % 2; // give 0 or 1
    Tunite *unitToAdd = NULL;
    Tpoint spawnPos;

    // If we pass the 50/50, choose a random unit based on elixir quantity
    if ((*elixirEnStockduJoueur > 0) && (randNum == 1))
    {
        //Renvoie {-1,-1} si pas d'emplacement vide, sinon les coords d'apparition (du plateau de jeu)
        spawnPos = GiveSpawnPos(player, jeu);

        if(spawnPos.posX != -1)
        {
            int maxInd;

            if(*elixirEnStockduJoueur >= 4){
                maxInd = 3;
            }
            else if(*elixirEnStockduJoueur == 3){
                maxInd = 2;
            }
            else if(*elixirEnStockduJoueur == 2){
                maxInd = 1;
            }
            else if(*elixirEnStockduJoueur == 1){
                maxInd = 0;
            }

            //0 -> maxInd
            int uniteChoice = rand() % (maxInd + 1);

            if(uniteChoice == 0){
                unitToAdd = creeGargouille(spawnPos.posX, spawnPos.posY);
            }else if(uniteChoice == 1){
                unitToAdd = creeArcher(spawnPos.posX, spawnPos.posY);
            }else if(uniteChoice == 2){
                unitToAdd = creeDragon(spawnPos.posX, spawnPos.posY);
            }else if(uniteChoice == 3){
                unitToAdd = creeChevalier(spawnPos.posX, spawnPos.posY);
            }

            (*elixirEnStockduJoueur)-= unitToAdd->coutEnElixir;


        }
    }

     // Return the selected unit
    return unitToAdd;
}
/////////////// COLLEGUE /////////////////////////

Tpoint GiveKingPos(TListePlayer player){
    int posX = -1;
    int posY = -1;
    TListePlayer tmp = player;

     while(getptrNextCell(tmp) != NULL)
    {
        tmp = getptrNextCell(tmp);
    }

    if(GetUnitName(tmp) == tourRoi)
    {
        posX = GetUnitPosX(tmp);
        posY = GetUnitPosY(tmp);
        Tpoint res = {posX,posY};

        return res;
    }
}
Tpoint GiveSpawnPos(TListePlayer player, TplateauJeu jeu){
    Tpoint res = {-1,-1};
    //Récupération position tour du roi ( {5,1} OU {5,17} )
    Tpoint kingPos = GiveKingPos(player);

    int i = 1;
    bool posIsOk = false;


    while((i<=5) && posIsOk != true)
    {
        if(jeu[kingPos.posX + i][kingPos.posY] == NULL)
        {
            res.posX = kingPos.posX + i;
            res.posY = kingPos.posY;
            posIsOk = true;
        }
        else if(jeu[kingPos.posX - i][kingPos.posY] == NULL)
        {
            res.posX = kingPos.posX - i;
            res.posY = kingPos.posY;
            posIsOk = true;
        }
        i++;
    }

    //Si res = {-1,-1} -> Pas de spawn car pas d'emplacement vide
    return res;
}


void Attack(TListePlayer *player1,TListePlayer *player2){
    //On autorise l'attaque (toutes les unités)
    allowAttackUnits(player1);
    allowAttackUnits(player2);

    TListePlayer tmp_2 = *player2;

    //Attaque unite player1 sur unités player2
    while(tmp_2 != NULL)
    {
        Tunite *curUnit = getPtrData(tmp_2);
        *player1 = combat(*player1, curUnit);
        tmp_2 = getptrNextCell(tmp_2);
    }
    ClearDeadUnitsFromList(player2);

    TListePlayer tmp_1 = *player1;
    //Attaque unite player2 sur unités player1
    while(tmp_1 != NULL)
    {
        Tunite *curUnit = getPtrData(tmp_1);
        *player2 = combat(*player2, curUnit);
        tmp_1 = getptrNextCell(tmp_1);
    }
    ClearDeadUnitsFromList(player1);
}
TListePlayer combat(TListePlayer player, Tunite *uneUniteDeLautreJoueur){
    TListePlayer unitAtRange;
    initListe(&unitAtRange);

    //Savoir qui est a portee de uneUniteDeLautreJoueur (dans player)
    unitAtRange = quiEstAPortee(player,uneUniteDeLautreJoueur);
    //Tri de la liste unitAtRange (vitesse d'attaque)
    trierListeJoueurs(&unitAtRange);

    //Attaque des unités de unitAtRange sur uneUniteDeLautreJoueur
    while((unitAtRange != NULL) && (uneUniteDeLautreJoueur != NULL))
    {
        //Si l'unité peut attaquer et si la cible a encore des PV
        if((ThisUnitCanAttack(unitAtRange) == 1) && (uneUniteDeLautreJoueur->pointsDeVie > 0))
        {
            //Attaque de l'unité courante sur unité cible
            AttackUnit(getPtrData(unitAtRange), uneUniteDeLautreJoueur);
        }
        unitAtRange = getptrNextCell(unitAtRange);
    }

    return player;
}
TListePlayer quiEstAPortee(TListePlayer player, Tunite *uneUniteDeLautreJoueur){
    TListePlayer tmp = player;
    TListePlayer res;
    initListe(&res);

    while(tmp != NULL)
    {
        Tunite *curUnit = getPtrData(tmp);
        int unit_range = GetUnitRange(tmp);
        int distanceOfUnit = calcDistance(curUnit, uneUniteDeLautreJoueur);

        if(distanceOfUnit <= unit_range)
        {
            AjouterUnite(&res, curUnit);
        }

        tmp = getptrNextCell(tmp);
    }

    return res;
}
void AttackUnit(Tunite *currentUnit, Tunite *targetUnit){
    targetUnit->pointsDeVie -= currentUnit->degats;
    currentUnit->peutAttaquer = 0;
}
void ClearDeadUnitsFromList(TListePlayer *player){
    TListePlayer tmp = *player;

    while(tmp != NULL)
    {
        if(GetUnitHP(tmp) <= 0)
        {
            supprimerUnite(player, getPtrData(tmp));
        }
        tmp = getptrNextCell(tmp);
    }
}
void allowAttackUnits(TListePlayer *player){
    TListePlayer tmp = *player;

    while(tmp != NULL)
    {
        Tunite *curUnit = getPtrData(tmp);
        curUnit->peutAttaquer = 1;
        tmp=getptrNextCell(tmp);
    }
}

/////////////// COLLEGUE /////////////////////////
void trierListeJoueurs(TListePlayer *ListeJoueur) {

    //0 ou 1 elmt -> Pas besoin de trier
    if (listeVide(*ListeJoueur) || getptrNextCell(*ListeJoueur) == NULL) {
        return;
    }

    TListePlayer ListeTriee = NULL;
    TListePlayer curr = *ListeJoueur;

    while (curr != NULL) {
        TListePlayer next = getptrNextCell(curr);

        //Ajout au début de la liste triée
        if (listeVide(ListeTriee) || GetUnitAttackSpeed(curr) <= GetUnitAttackSpeed(ListeTriee)) {
            curr->suiv = ListeTriee;
            ListeTriee = curr;
        }
        //On cherche où insérer dans la liste triée
        else {
            TListePlayer tmp = ListeTriee;
            while (getptrNextCell(tmp) != NULL && GetUnitAttackSpeed(getptrNextCell(tmp)) < GetUnitAttackSpeed(curr)) {
                tmp = getptrNextCell(tmp);
            }
            curr->suiv = getptrNextCell(tmp);
            tmp->suiv = curr;
        }
        curr = next;

    }
    *ListeJoueur = ListeTriee;
}
void MoveUnit(TListePlayer player, TListePlayer player2, TplateauJeu jeu){

    TListePlayer tmp = player;
    TListePlayer tmp2 = player2;

    while(tmp != NULL)
    {
        int curX = GetUnitPosX(tmp);
        int curY = GetUnitPosY(tmp);
        int moveDistance = GetUnitMoveSpeed(tmp);

        // Vérification des cases en partant de la distance maximale jusqu'à 1
        for (int i = moveDistance; i >= 1; i--) {
            int newX = curX; // La même colonne que la position actuelle
            int newY = curY - i;
            if(curX > 5){
                newX = curX - 1;
            } else if(curX < 5){
                newX = curX + 1;
            }
            if (newX >= 0 && newX < LARGEURJEU && newY >= 0 && newY < HAUTEURJEU && jeu[newX][newY] == NULL) {
                // Si la case est libre, effectuer le déplacement et sortir de la boucle
                jeu[curX][curY] = NULL;
                jeu[newX][newY] = tmp->pdata;
                tmp->pdata->posX = newX;
                tmp->pdata->posY = newY;
                break;
            }
        }
        tmp = getptrNextCell(tmp);
    }
// même processus pour joueur 2
    while(tmp2 != NULL)
    {
        int curX2 = GetUnitPosX(tmp2);
        int curY2 = GetUnitPosY(tmp2);
        int moveDistance2 = GetUnitMoveSpeed(tmp2);

        for (int i = moveDistance2; i >= 1; i--) {
            int newX2 = curX2; // La même colonne que la position actuelle
            int newY2 = curY2 + i;
            if(curX2 > 5){
                newX2 = curX2 - 1;
            } else if(curX2 < 5){
                newX2 = curX2 + 1;
            }
            if (newX2 >= 0 && newX2 < LARGEURJEU && newY2 >= 0 && newY2 < HAUTEURJEU && jeu[newX2][newY2] == NULL) {
                // Si la case est libre, effectuer le déplacement et sortir de la boucle
                jeu[curX2][curY2] = NULL;
                jeu[newX2][newY2] = tmp2->pdata;
                tmp2->pdata->posX = newX2;
                tmp2->pdata->posY = newY2;
                break;
            }
        }
        tmp2 = getptrNextCell(tmp2);
    }
}
/////////////// COLLEGUE /////////////////////////


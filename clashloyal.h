#ifndef CLASHLOYAL_H_INCLUDED
#define CLASHLOYAL_H_INCLUDED

#include "types.h"
#include "list_lib.h"
#include "mathsLib.h"

#include <stdio.h>

#define LARGEURJEU 11
#define HAUTEURJEU 19

#define MAXELIXIR 10
#define MAXUNITS 10

typedef T_liste TListePlayer;
typedef Tunite* ** TplateauJeu;

//GESTION PLATEAU DE JEU
TplateauJeu AlloueTab2D(int largeur, int hauteur);
void initPlateauAvecNULL(TplateauJeu jeu,int largeur, int hauteur);
void affichePlateauConsole(TplateauJeu jeu, int largeur, int hauteur);
void PositionnePlayerOnPlateau(TListePlayer player, TplateauJeu jeu);


//CREATION UNITES
Tunite *creeTour(int posx, int posy);
Tunite *creeTourRoi(int posx, int posy);
Tunite *creeArcher(int posx, int posy);
Tunite *creeChevalier(int posx, int posy);
Tunite *creeGargouille(int posx, int posy);
Tunite *creeDragon(int posx, int posy);


/////////////////// UTILES //////////////////////
TuniteDuJeu GetUnitName(TListePlayer curUnit);
int GetUnitPosX(TListePlayer curUnit);
int GetUnitPosY(TListePlayer curUnit);
int GetUnitHP(TListePlayer curUnit);
float GetUnitMoveSpeed(TListePlayer curUnit);
float GetUnitAttackSpeed(TListePlayer curUnit);
int GetUnitDamage(TListePlayer curUnit);
int GetUnitRange(TListePlayer curUnit);
int ThisUnitCanAttack(TListePlayer curUnit); //1 si l'unité peut attaquer, 0 si l'unité a déjà attaqué
Tcible GetUnitType(TListePlayer curUnit);
Tcible GetUnitTargetType(TListePlayer curUnit);

int calcDistance(Tunite *fstUnit, Tunite *scdUnit);

void AjouterUnite(TListePlayer *player, Tunite *nouvelleUnite);
void supprimerUnite(TListePlayer *player, Tunite *UniteDetruite);

bool tourRoiDetruite(TListePlayer player);
/////////////////////////////////////////////////


//ACHAT + NAISSANCE UNITES
void giveElixir(int *elixirEnStockduJoueur);
Tunite *AcheteUnite(int *elixirEnStockduJoueur, TListePlayer player,TplateauJeu jeu);
//Quelque chose interessant pour rendre le jeu plus "juste" serait de faire un if pour comparer qui a le plus d'unit�s entre
//les deux joueurs et donner 1 elixir en plus à celui qui en a le moins
Tpoint GiveKingPos(TListePlayer player);
Tpoint GiveSpawnPos(TListePlayer player, TplateauJeu jeu);


//DEPLACEMENT
void MoveUnit(TListePlayer player, TListePlayer player2, TplateauJeu jeu);


//COMBAT
TListePlayer quiEstAPortee(TListePlayer player, Tunite *uneUniteDeLautreJoueur);
TListePlayer combat(TListePlayer player, Tunite *uneUniteDeLautreJoueur);
void AttackUnit(Tunite *currentUnit, Tunite *targetUnit);
void Attack(TListePlayer *player1,TListePlayer *player2);
void allowAttackUnits(TListePlayer *player);
void ClearDeadUnitsFromList(TListePlayer *player);

void trierListeJoueurs(TListePlayer *ListeJoueur);

//SAUVEGARDES
void sauvegarderPartieBinaire(const char *nomFichier, TplateauJeu plateau, T_liste listeUnitesPlayer1, T_liste listeUnitesPlayer2);
void chargerPartieBinaire(const char *nomFichier, TplateauJeu plateau, T_liste *listeUnitesPlayer1, T_liste *listeUnitesPlayer2);
void sauvegarderListeBinaire(T_liste liste, FILE *fichier);
T_liste chargerListeBinaire(FILE *fichier);

void sauvegarderPartieSequentielle(const char *nomFichier, TplateauJeu plateau, T_liste listeUnitesPlayer1, T_liste listeUnitesPlayer2);

#endif // CLASHLOYAL_H_INCLUDED

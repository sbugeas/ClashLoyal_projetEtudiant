//"surcouche partielle" de la SDL pour les affichages li�s au jeu2048

// ENIEREMENT FOURNIE

#include "clashloyal.h"
#ifndef MASDL_H_INCLUDED
#define MASDL_H_INCLUDED

void message(char *myTitle, char *myMessage);

//void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination );
//void clear_surface(SDL_Surface *psurf);

void prepare_sprite( int x, int y, SDL_Surface* source, SDL_Surface* destination );
void efface_fenetre(SDL_Surface *psurf);
void maj_fenetre(SDL_Window *pWindow);

void prepareAllSpriteDuJeu(TplateauJeu jeu, int largeur, int hauteur, SDL_Surface **TabSprite, SDL_Surface* destination );


#endif // MASDL_H_INCLUDED

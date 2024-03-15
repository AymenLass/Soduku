#ifndef SDL_H_INCLUDED
#define SDL_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include "main.h"
void         initialisationSDL(void);
void         impressionEcran(SDL_Renderer* renderer,
                             int          grilleSudoku[9][9][10]);
SDL_Window* creationEcran(int hauteur, int largeur);
SDL_Surface* chargementBitmap(char *nomImage);
int afficherSolution(int grille[9][9][10], SDL_Renderer *renderer) ;
void afficherGrilleVierge(SDL_Renderer *renderer) ;
void afficherGrilleVierge2(SDL_Renderer *renderer) ;

#endif // SDL_H_INCLUDED
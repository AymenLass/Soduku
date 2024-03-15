#ifndef GESTIONEVENEMENTS_H_INCLUDED
#define GESTIONEVENEMENTS_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include "main.h"
#include "fonctionsSDL.h"
#include ".\Sudoku_Console\fonctionsDeBase.h"
#include ".\Sudoku_Console\resolveur.h"
void attenteEcranPrincipal(SDL_Renderer* renderer,
                           bool        *finDuProgramme);
void attenteEcranChoix(SDL_Renderer *renderer, bool *finDuProgramme) ;
void attenteEcranJouer(SDL_Renderer *renderer,
                       SDL_Texture *grilleTexture,
                       int grilleSudoku[9][9][10],
                       bool *finDuProgramme) ;
void attenteEcranResolveur(SDL_Renderer *renderer,
                           SDL_Texture *grille,
                           bool *finDuProgramme) ;
void saisirChiffre(SDL_Renderer *renderer,
                   int          positionX,
                   int          positionY,
                   bool        *finDuProgramme,
                   int         *caseChiffre);

#endif // GESTIONEVENEMENTS_H_INCLUDED
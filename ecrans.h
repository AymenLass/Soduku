#ifndef ECRANS_H_INCLUDED
#define ECRANS_H_INCLUDED
#include "main.h"
#include <SDL_render.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <stdbool.h>
#include "fonctionsSDL.h"
#include "gestionEvenements.h"
#include "C:\Users\user\Desktop\libraries\projects\Sudoku_Console\generateur.h"
void ecranPrincipal(SDL_Renderer* renderer, bool *finDuProgramme);

void ecranJouer(SDL_Renderer *renderer, bool *finDuProgramme, int niveau) ;

void ecranResolveur(SDL_Renderer *renderer, bool *finDuProgramme) ;
void ecranChoixDifficulte(SDL_Renderer *renderer, bool *finDuProgramme)  ;

void ecranPerdu(SDL_Renderer *renderer, bool *finDuProgramme) ;

#endif // ECRANS_H_INCLUDED
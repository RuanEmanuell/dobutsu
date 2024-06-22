#ifndef TEXTURAS_H
#define TEXTURAS_H

#include "raylib.h"

#define NUM_FRAMES 8
#define NUM_FRAMES_DEATH 19
#define NUM_FRAMES_ROLL 6

void CarregarTexturas(Texture2D texturas[NUM_FRAMES], const char* basePath, const char* prefixo);
void CarregarTexturasMorte(Texture2D texturas[NUM_FRAMES_DEATH], const char* basePath, const char* prefixo);
void CarregarTexturasRoll(Texture2D texturas[NUM_FRAMES_ROLL], const char* basePath, const char* prefixo);



extern Texture2D paradoDir[NUM_FRAMES];
extern Texture2D paradoEsq[NUM_FRAMES];
extern Texture2D correrDir[NUM_FRAMES];
extern Texture2D correrEsq[NUM_FRAMES];
extern Texture2D ataqueDir[NUM_FRAMES];
extern Texture2D ataqueEsq[NUM_FRAMES];
extern Texture2D rollDir[NUM_FRAMES_ROLL];
extern Texture2D rollEsq[NUM_FRAMES_ROLL];
extern Texture2D morteDir[NUM_FRAMES_DEATH];
extern Texture2D morteEsq[NUM_FRAMES_DEATH];

#endif // TEXTURAS_H

#include "texturas.h"

Texture2D paradoDir[NUM_FRAMES];
Texture2D paradoEsq[NUM_FRAMES];
Texture2D correrDir[NUM_FRAMES];
Texture2D correrEsq[NUM_FRAMES];
Texture2D ataqueDir[NUM_FRAMES];
Texture2D ataqueEsq[NUM_FRAMES];
Texture2D morteDir[NUM_FRAMES_DEATH];
Texture2D morteEsq[NUM_FRAMES_DEATH];
Texture2D rollDir[NUM_FRAMES_ROLL];
Texture2D rollEsq[NUM_FRAMES_ROLL];

void CarregarTexturas(Texture2D texturas[NUM_FRAMES], const char* basePath, const char* prefixo)
{
    for (int i = 0; i < NUM_FRAMES; i++)
    {
        char fileName[64];
        sprintf(fileName, "%s/%s%d.png", basePath, prefixo, i + 1);
        texturas[i] = LoadTexture(fileName);
    }
}

void CarregarTexturasMorte(Texture2D texturas[NUM_FRAMES_DEATH], const char* basePath, const char* prefixo)
{
    for (int i = 0; i < NUM_FRAMES_DEATH; i++)
    {
        char fileName[64];
        sprintf(fileName, "%s/%s%d.png", basePath, prefixo, i + 1);
        texturas[i] = LoadTexture(fileName);
    }
}

void CarregarTexturasRoll(Texture2D texturas[NUM_FRAMES_ROLL], const char* basePath, const char* prefixo)
{
    for (int i = 0; i < NUM_FRAMES_ROLL; i++)
    {
        char fileName[64];
        sprintf(fileName, "%s/%s%d.png", basePath, prefixo, i + 1);
        texturas[i] = LoadTexture(fileName);
    }
}

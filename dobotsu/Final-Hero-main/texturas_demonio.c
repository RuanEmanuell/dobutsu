#include "texturas_demonio.h"

// Definição das texturas
Texture2D demonioIdleDir[NUM_FRAMES_IDLE];
Texture2D demonioIdleEsq[NUM_FRAMES_IDLE];
Texture2D demonioWalkDir[NUM_FRAMES_WALK];
Texture2D demonioWalkEsq[NUM_FRAMES_WALK];
Texture2D demonioAttackDir[NUM_FRAMES_ATTACK];
Texture2D demonioAttackEsq[NUM_FRAMES_ATTACK];
Texture2D demonioDeathDir[NUM_FRAMES_DEATH_DEMON];
Texture2D demonioDeathEsq[NUM_FRAMES_DEATH_DEMON];


void CarregarTexturasDemonio(Texture2D texturas[], const char* basePath, const char* prefixo, int numFrames)
{
    for (int i = 0; i < numFrames; i++)
    {
        char fileName[256];
        sprintf(fileName, "%s/%s%d.png", basePath, prefixo, i + 1);
        texturas[i] = LoadTexture(fileName);
    }
}


void CarregarTexturasMorteDemonio(Texture2D texturas[NUM_FRAMES_DEATH_DEMON], const char* basePath, const char* prefixo)
{
    for (int i = 0; i < NUM_FRAMES_DEATH_DEMON; i++)
    {
        char fileName[256];
        sprintf(fileName, "%s/%s%d.png", basePath, prefixo, i + 1);
        texturas[i] = LoadTexture(fileName);
    }
}


void UnloadTexturasDemonio(Texture2D* texturas, int num_frames)
{
    for (int i = 0; i < num_frames; i++)
    {
        UnloadTexture(texturas[i]);
    }
}

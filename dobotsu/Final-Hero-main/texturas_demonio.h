#ifndef TEXTURAS_DEMONIO_H
#define TEXTURAS_DEMONIO_H

#include "raylib.h"

#define NUM_FRAMES_IDLE 6
#define NUM_FRAMES_WALK 12
#define NUM_FRAMES_ATTACK 15
#define NUM_FRAMES_DEATH_DEMON 22


extern Texture2D demonioIdleDir[NUM_FRAMES_IDLE];
extern Texture2D demonioIdleEsq[NUM_FRAMES_IDLE];
extern Texture2D demonioWalkDir[NUM_FRAMES_WALK];
extern Texture2D demonioWalkEsq[NUM_FRAMES_WALK];
extern Texture2D demonioAttackDir[NUM_FRAMES_ATTACK];
extern Texture2D demonioAttackEsq[NUM_FRAMES_ATTACK];
extern Texture2D demonioDeathDir[NUM_FRAMES_DEATH_DEMON];
extern Texture2D demonioDeathEsq[NUM_FRAMES_DEATH_DEMON];


void CarregarTexturasDemonio(Texture2D texturas[], const char* basePath, const char* prefixo, int numFrames);
void CarregarTexturasMorteDemonio(Texture2D texturas[NUM_FRAMES_DEATH_DEMON], const char* basePath, const char* prefixo);
void UnloadTexturasDemonio(Texture2D* texturas, int num_frames);

#endif // TEXTURAS_DEMONIO_H

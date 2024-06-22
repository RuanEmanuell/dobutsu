#include "raylib.h"
#include "texturas.h"
#include "texturas_demonio.h"
#include <math.h>
#include <stdbool.h>

// Definições básicas
#define LARGURA_TELA 1400
#define ALTURA_TELA 800
#define ESCALA_PERSONAGEM 3.0f
#define VELOCIDADE_HEROI 400.0f
#define VELOCIDADE_DEMONIO 120.0f
#define TEMPO_FRAME_MORTE 0.2f

#define VIDA_MAX_HEROI 1000
#define VIDA_MAX_DEMONIO 3000
#define DANO_HEROI 30
#define DANO_DEMONIO 10

typedef enum { PARADO, CORRENDO, ATACANDO, MORTO, MORRENDO } EstadoHeroi;
typedef enum { PARADO_DEMONIO, ANDANDO, ATACANDO_DEMONIO, MORTO_DEMONIO, MORRENDO_DEMONIO } EstadoDemonio;

int main(void)
{
    InitWindow(LARGURA_TELA, ALTURA_TELA, "FINAL HERO");

//Texturas heroi
    CarregarTexturas(paradoDir, "assets/hero/parado/parado_dir", "parado_dir_");
    CarregarTexturas(paradoEsq, "assets/hero/parado/parado_esq", "parado_esq_");
    CarregarTexturas(correrDir, "assets/hero/correr/correr_dir", "correr_dir_");
    CarregarTexturas(correrEsq, "assets/hero/correr/correr_esq", "correr_esq_");
    CarregarTexturas(ataqueDir, "assets/hero/ataque/ataque_dir", "atk_dir_");
    CarregarTexturas(ataqueEsq, "assets/hero/ataque/ataque_esq", "atk_esq_");
    CarregarTexturasRoll(rollDir, "assets/hero/rolar/rolar_dir", "roll_dir_");
    CarregarTexturasRoll(rollEsq, "assets/hero/rolar/rolar_esq", "roll_esq_");
    CarregarTexturasMorte(morteDir, "assets/hero/morte/morte_dir", "death_dir_");
    CarregarTexturasMorte(morteEsq, "assets/hero/morte/morte_esq", "death_esq_");

// Inimigo
    CarregarTexturasDemonio(demonioIdleDir, "assets/demon/parado/parado_dir", "demon_idle_right_", NUM_FRAMES_IDLE);
    CarregarTexturasDemonio(demonioIdleEsq, "assets/demon/parado/parado_esq", "demon_idle_left_", NUM_FRAMES_IDLE);
    CarregarTexturasDemonio(demonioWalkDir, "assets/demon/andando/andando_dir", "demon_walk_dir_", NUM_FRAMES_WALK);
    CarregarTexturasDemonio(demonioWalkEsq, "assets/demon/andando/andando_esq", "demon_walk_esq_", NUM_FRAMES_WALK);
    CarregarTexturasDemonio(demonioAttackDir, "assets/demon/ataque/ataque_dir", "demon_cleave_dir_", NUM_FRAMES_ATTACK);
    CarregarTexturasDemonio(demonioAttackEsq, "assets/demon/ataque/ataque_esq", "demon_cleave_esq_", NUM_FRAMES_ATTACK);
    CarregarTexturasDemonio(demonioDeathDir, "assets/demon/morte/morte_demon_dir", "demon_death_dir_", NUM_FRAMES_ATTACK);
    CarregarTexturasDemonio(demonioDeathEsq, "assets/demon/morte/morte_demon_esq", "demon_death_esq_", NUM_FRAMES_ATTACK);


    // Cenário
    Texture2D cenario = LoadTexture("assets/cenario/cen1.png");

    Vector2 posicaoHeroi = { 0.0f, (float)(ALTURA_TELA - paradoDir[0].height * ESCALA_PERSONAGEM) };
    Vector2 posicaoDemonio = { (float)(LARGURA_TELA - demonioIdleDir[0].width * ESCALA_PERSONAGEM), (float)(ALTURA_TELA - demonioIdleDir[0].height * ESCALA_PERSONAGEM) };

    int frameAtual = 0;
    float tempoFrame = 0.1f;
    float temporizador = 0.0f;
    int frameAtualDemonio = 0;
    float tempoFrameDemonio = 0.08f;
    float temporizadorDemonio = 0.0f;


    bool olhandoDireita = true;
    EstadoHeroi estado = PARADO;

    bool demonioOlhandoDireita = false;
    EstadoDemonio estadoDemonio = PARADO_DEMONIO;

    int vidaHeroi = VIDA_MAX_HEROI;
    int vidaDemonio = VIDA_MAX_DEMONIO;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        temporizador += GetFrameTime();
        if (temporizador >= tempoFrame)
        {
            frameAtual = (frameAtual + 1) % NUM_FRAMES;
            temporizador = 0.0f;

            if (estado == ATACANDO && frameAtual == 0)
            {
                estado = PARADO;
            }
        }

        if (estado != ATACANDO && estado != MORTO && estado != MORRENDO)
        {
            estado = PARADO;
        }

        // Movimentação do herói
        if (IsKeyDown(KEY_RIGHT) && estado != MORTO && estado != MORRENDO)
        {
            posicaoHeroi.x += VELOCIDADE_HEROI * GetFrameTime();
            olhandoDireita = true;
            estado = CORRENDO;
        }
        else if (IsKeyDown(KEY_LEFT) && estado != MORTO && estado != MORRENDO)
        {
            posicaoHeroi.x -= VELOCIDADE_HEROI * GetFrameTime();
            olhandoDireita = false;
            estado = CORRENDO;
        }


        // Ataque do herói
        float tempoFrameAtaqueHeroi = 0.05f; // Ajuste para maior velocidade de ataque
        temporizador += GetFrameTime();
        if (IsKeyPressed(KEY_A) && estado != ATACANDO && estado != MORTO && estado != MORRENDO)
        {
            estado = ATACANDO;
            frameAtual = 0; // Reinicia a animação de ataque
            temporizador = 0.0f;
        }
        if (estado == ATACANDO && temporizador >= tempoFrameAtaqueHeroi)
        {
            frameAtual = (frameAtual + 1) % NUM_FRAMES;
            temporizador = 0.0f;

            if (frameAtual == 0)
            {
                estado = PARADO;
            }
        }

        // Lógica do demônio
        temporizadorDemonio += GetFrameTime();
        if (temporizadorDemonio >= tempoFrameDemonio)
        {
            frameAtualDemonio++;
            temporizadorDemonio = 0.0f;

            if (estadoDemonio == ATACANDO_DEMONIO && frameAtualDemonio >= NUM_FRAMES_ATTACK)
            {
                frameAtualDemonio = 0;
                estadoDemonio = PARADO_DEMONIO;
            }
            else if (estadoDemonio == ANDANDO && frameAtualDemonio >= NUM_FRAMES_WALK)
            {
                frameAtualDemonio = 0;
            }
            else if (estadoDemonio == MORRENDO_DEMONIO && frameAtualDemonio >= NUM_FRAMES_DEATH_DEMON)
            {
                estadoDemonio = MORTO_DEMONIO;
                frameAtualDemonio = NUM_FRAMES_DEATH_DEMON - 1;
            }
            else if (estadoDemonio != ATACANDO_DEMONIO && estadoDemonio != ANDANDO && estadoDemonio != MORRENDO_DEMONIO)
            {
                frameAtualDemonio = frameAtualDemonio % NUM_FRAMES_IDLE;
            }
        }


        float distanciaX = posicaoHeroi.x - posicaoDemonio.x;
        float distanciaAbsoluta = fabs(distanciaX);
        if (estadoDemonio != ATACANDO_DEMONIO && estadoDemonio != MORRENDO_DEMONIO && estadoDemonio != MORTO_DEMONIO)
        {


            if (distanciaAbsoluta < 150.0f) // Distância do demônio do herói
            {
                estadoDemonio = ATACANDO_DEMONIO;
                frameAtualDemonio = 0;
            }
            else
            {
                estadoDemonio = ANDANDO;
                if (distanciaAbsoluta > 100.0f) // Distância que o ataque atinge
                {
                    if (distanciaX > 0)
                    {
                        posicaoDemonio.x += VELOCIDADE_DEMONIO * GetFrameTime();
                        demonioOlhandoDireita = true;
                    }
                    else
                    {
                        posicaoDemonio.x -= VELOCIDADE_DEMONIO * GetFrameTime();
                        demonioOlhandoDireita = false;
                    }
                }
                else
                {
                    estadoDemonio = PARADO_DEMONIO;
                }
            }
        }


        // Verifica colisões e aplica dano
        if (estado == ATACANDO && distanciaAbsoluta < 200.0f && frameAtual == (NUM_FRAMES / 2))
        {
            vidaDemonio -= DANO_HEROI;
            if (vidaDemonio < 0) vidaDemonio = 0;
        }

        if (estadoDemonio == ATACANDO_DEMONIO && distanciaAbsoluta < 400.0f && frameAtualDemonio == (NUM_FRAMES_ATTACK / 2))
        {
            vidaHeroi -= DANO_DEMONIO;
            if (vidaHeroi < 0) vidaHeroi = 0;
        }

        if (vidaHeroi <= 0 && estado != MORTO && estado != MORRENDO)
        {
            estado = MORRENDO;
            frameAtual = 0;
            temporizador = 0.0f;
        }

        if (vidaDemonio <= 0 && estadoDemonio != MORTO_DEMONIO && estadoDemonio != MORRENDO_DEMONIO)
        {
            estadoDemonio = MORRENDO_DEMONIO;
            frameAtualDemonio = 0;
            temporizadorDemonio = 0.0f;
        }

        // Desenha na tela
        BeginDrawing();
        ClearBackground(RAYWHITE);

        Rectangle source = { 0.0f, 0.0f, (float)cenario.width, (float)cenario.height };
        Rectangle dest = { 0.0f, 0.0f, (float)LARGURA_TELA, (float)ALTURA_TELA };
        Vector2 origin = { 0.0f, 0.0f };
        DrawTexturePro(cenario, source, dest, origin, 0.0f, WHITE);

        // Desenha barras de vida
        DrawRectangle(50, 50, 300, 25, GRAY);
        DrawRectangle(50, 50, (int)(300 * ((float)vidaHeroi / VIDA_MAX_HEROI)), 25, GREEN);
        DrawRectangle(LARGURA_TELA - 350, 50, 300, 25, GRAY);
        DrawRectangle(LARGURA_TELA - 350, 50, (int)(300 * ((float)vidaDemonio / VIDA_MAX_DEMONIO)), 25, RED);

        if (estado == MORTO)
        {
            DrawText("GAME OVER", LARGURA_TELA / 2 - 270, ALTURA_TELA / 2 - 100, 100, RED);
            DrawText("Deseja tentar novamente? (S/N)", LARGURA_TELA / 2 - 220, ALTURA_TELA / 2, 30, WHITE);

            if (IsKeyPressed(KEY_S))
            {
                // Reiniciar o jogo
                vidaHeroi = VIDA_MAX_HEROI;
                vidaDemonio = VIDA_MAX_DEMONIO;
                posicaoHeroi = (Vector2)
                {
                    0.0f, (float)(ALTURA_TELA - paradoDir[0].height * ESCALA_PERSONAGEM)
                };
                posicaoDemonio = (Vector2)
                {
                    (float)(LARGURA_TELA - demonioIdleDir[0].width * ESCALA_PERSONAGEM), (float)(ALTURA_TELA - demonioIdleDir[0].height * ESCALA_PERSONAGEM)
                };
                estado = PARADO;
                estadoDemonio = PARADO_DEMONIO;
                tempoFrame = 0.1f;
            }
            else if (IsKeyPressed(KEY_N))
            {
                break;
            }
        }
        else
        {
            switch (estado)
            {
            case PARADO:
                if (olhandoDireita)
                {
                    DrawTextureEx(paradoDir[frameAtual], posicaoHeroi, 0.0f, ESCALA_PERSONAGEM, WHITE);
                }
                else
                {
                    DrawTextureEx(paradoEsq[frameAtual], posicaoHeroi, 0.0f, ESCALA_PERSONAGEM, WHITE);
                }
                break;
            case CORRENDO:
                if (olhandoDireita)
                {
                    DrawTextureEx(correrDir[frameAtual], posicaoHeroi, 0.0f, ESCALA_PERSONAGEM, WHITE);
                }
                else
                {
                    DrawTextureEx(correrEsq[frameAtual], posicaoHeroi, 0.0f, ESCALA_PERSONAGEM, WHITE);
                }
                break;
            case ATACANDO:
                if (olhandoDireita)
                {
                    DrawTextureEx(ataqueDir[frameAtual], posicaoHeroi, 0.0f, ESCALA_PERSONAGEM, WHITE);
                }
                else
                {
                    DrawTextureEx(ataqueEsq[frameAtual], posicaoHeroi, 0.0f, ESCALA_PERSONAGEM, WHITE);
                }
                break;
            case MORRENDO:
                if (olhandoDireita)
                {
                    DrawTextureEx(morteDir[frameAtual], posicaoHeroi, 0.0f, ESCALA_PERSONAGEM, WHITE);
                }
                else
                {
                    DrawTextureEx(morteEsq[frameAtual], posicaoHeroi, 0.0f, ESCALA_PERSONAGEM, WHITE);
                }
                temporizador += GetFrameTime();
                tempoFrame = 0.5f;
                if (temporizador >= tempoFrame)
                {
                    frameAtual++;
                    temporizador = 0.0f;

                    if (frameAtual >= NUM_FRAMES_DEATH)
                    {
                        frameAtual = NUM_FRAMES_DEATH - 1;
                        estado = MORTO;
                    }

                }
                break;
            }

            if (estadoDemonio == MORTO_DEMONIO)
            {
                DrawText("VITÓRIA!", LARGURA_TELA / 2 - 220, ALTURA_TELA / 2 - 100, 100, RED);
                DrawText("Deseja jogar novamente? (S/N)", LARGURA_TELA / 2 - 220, ALTURA_TELA / 2, 30, WHITE);

                if (IsKeyPressed(KEY_S))
                {
                    // Reiniciar o jogo
                    vidaHeroi = VIDA_MAX_HEROI;
                    vidaDemonio = VIDA_MAX_DEMONIO;
                    posicaoHeroi = (Vector2)
                    {
                        0.0f, (float)(ALTURA_TELA - paradoDir[0].height * ESCALA_PERSONAGEM)
                    };
                    posicaoDemonio = (Vector2)
                    {
                        (float)(LARGURA_TELA - demonioIdleDir[0].width * ESCALA_PERSONAGEM), (float)(ALTURA_TELA - demonioIdleDir[0].height * ESCALA_PERSONAGEM)
                    };
                    estado = PARADO;
                    estadoDemonio = PARADO_DEMONIO;
                    tempoFrameDemonio = 0.1f;
                }
                else if (IsKeyPressed(KEY_N))
                {
                    break;
                }
            }
            else
            {
                switch (estadoDemonio)
                {
                case PARADO_DEMONIO:
                    if (demonioOlhandoDireita)
                    {
                        DrawTextureEx(demonioIdleDir[frameAtualDemonio], posicaoDemonio, 0.0f, ESCALA_PERSONAGEM, WHITE);
                    }
                    else
                    {
                        DrawTextureEx(demonioIdleEsq[frameAtualDemonio], posicaoDemonio, 0.0f, ESCALA_PERSONAGEM, WHITE);
                    }
                    break;
                case ANDANDO:
                    if (demonioOlhandoDireita)
                    {
                        DrawTextureEx(demonioWalkDir[frameAtualDemonio], posicaoDemonio, 0.0f, ESCALA_PERSONAGEM, WHITE);
                    }
                    else
                    {
                        DrawTextureEx(demonioWalkEsq[frameAtualDemonio], posicaoDemonio, 0.0f, ESCALA_PERSONAGEM, WHITE);
                    }
                    break;
                case ATACANDO_DEMONIO:
                    if (demonioOlhandoDireita)
                    {
                        DrawTextureEx(demonioAttackDir[frameAtualDemonio], posicaoDemonio, 0.0f, ESCALA_PERSONAGEM, WHITE);
                    }
                    else
                    {
                        DrawTextureEx(demonioAttackEsq[frameAtualDemonio], posicaoDemonio, 0.0f, ESCALA_PERSONAGEM, WHITE);
                    }
                    break;
                case MORRENDO_DEMONIO:
                    if (demonioOlhandoDireita)
                    {
                        DrawTextureEx(demonioDeathDir[frameAtualDemonio], posicaoDemonio, 0.0f, ESCALA_PERSONAGEM, WHITE);
                    }
                    else
                    {
                        DrawTextureEx(demonioDeathEsq[frameAtualDemonio], posicaoDemonio, 0.0f, ESCALA_PERSONAGEM, WHITE);
                    }
                    temporizadorDemonio += GetFrameTime();
                    tempoFrameDemonio = 0.2f;
                    if (temporizadorDemonio >= tempoFrameDemonio)
                    {
                        frameAtualDemonio++;
                        temporizadorDemonio = 0.0f;

                        if (frameAtualDemonio >= NUM_FRAMES_DEATH_DEMON)
                        {
                            frameAtualDemonio = NUM_FRAMES_DEATH_DEMON - 1;
                            estadoDemonio = MORTO_DEMONIO;
                        }
                    }
                    break;
                }
            }


        }

        EndDrawing();
    }

    for (int i = 0; i < NUM_FRAMES; i++)
    {
        UnloadTexture(paradoDir[i]);
        UnloadTexture(paradoEsq[i]);
        UnloadTexture(correrDir[i]);
        UnloadTexture(correrEsq[i]);
        UnloadTexture(ataqueDir[i]);
        UnloadTexture(ataqueEsq[i]);
    }

    for (int i = 0; i < NUM_FRAMES_IDLE; i++)
    {
        UnloadTexture(demonioIdleDir[i]);
        UnloadTexture(demonioIdleEsq[i]);
    }
    for (int i = 0; i < NUM_FRAMES_WALK; i++)
    {
        UnloadTexture(demonioWalkDir[i]);
        UnloadTexture(demonioWalkEsq[i]);
    }
    for (int i = 0; i < NUM_FRAMES_ATTACK; i++)
    {
        UnloadTexture(demonioAttackDir[i]);
        UnloadTexture(demonioAttackEsq[i]);
    }

    for (int i = 0; i < NUM_FRAMES_DEATH; i++)
    {
        UnloadTexture(morteDir[i]);
        UnloadTexture(morteEsq[i]);
    }

    for (int i = 0; i < NUM_FRAMES_DEATH_DEMON; i++)
    {
        UnloadTexture(demonioDeathDir[i]);
        UnloadTexture(demonioDeathEsq[i]);
    }
    UnloadTexture(cenario);

    CloseWindow();

    return 0;
}

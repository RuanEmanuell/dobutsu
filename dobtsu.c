#include "raylib.h"

#define MAX_GIF_FRAMES 9

typedef enum { SCREEN_TITLE, SCREEN_GAMEPLAY, SCREEN_ENDING } GameScreen;


int main(void)
{
    
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    //FRAMES DO FUNDO
    Texture2D gifFrames[MAX_GIF_FRAMES];
    for (int i = 0; i < MAX_GIF_FRAMES; i++) {
        char fileName[50];
        sprintf(fileName, "resources/%d.png", i + 1);
        gifFrames[i] = LoadTexture(fileName);
    }
    int currentGifFrame = 0;
    int gifFrameCounter = 0;
    int gifFrameSpeed = 20;

    //BOLA
    Vector2 ballPosition = { screenWidth/2, screenHeight/2 };
    float ballRadius = 20.0f;
    int ballSpeedX = 6;
    int ballSpeedY = -4;

    //AZUL
    Rectangle player = { 10, screenHeight/2 - 50, 25, 100 };
    float playerSpeed = 8.0f;
    int playerScore = 0;

    //VERDE
    Rectangle enemy = { screenWidth - 10 - 25, screenHeight/2 - 50, 25, 100 };
    float enemySpeed = 8.0f;
    int enemyVisionRange = screenWidth/2;
    int enemyScore = 0;

    Font fntTitle = LoadFontEx("resources/pixantiqua.ttf", 12, 0, 0);
    SetTextureFilter(fntTitle.texture, TEXTURE_FILTER_POINT);

    Sound fxStart = LoadSound("resources/start.wav");
    Sound fxPong = LoadSound("resources/pong.wav");

    Music ambient = LoadMusicStream("resources/qt-plimp.xm");
    PlayMusicStream(ambient);

    bool pause = false;
    bool finishGame = false;
    int framesCounter = 0;
    GameScreen currentScreen = SCREEN_TITLE; // 0-INICIO, 1-GAMEPLAY, 2-FIM

    SetTargetFPS(60); 

   //LOOP PRINCIPAL
    while (!WindowShouldClose() && !finishGame) // Detectar botão de fechar janela ou tecla ESC
    {
      

        switch (currentScreen)
        {
            case SCREEN_TITLE:
            {
                framesCounter++;

                if (IsKeyPressed(KEY_ENTER))
                {
                    currentScreen = SCREEN_GAMEPLAY;
                }
            } break;
            case SCREEN_GAMEPLAY:
            {
                if (!pause)
                {
                    ballPosition.x += ballSpeedX;
                    ballPosition.y += ballSpeedY;

                    if (((ballPosition.x + ballRadius) > screenWidth) || ((ballPosition.x - ballRadius) < 0))
                    {
                        PlaySound(fxPong);
                        ballSpeedX *= -1;
                    }

                    if (((ballPosition.y + ballRadius) > screenHeight) || ((ballPosition.y - ballRadius) < 0))
                    {
                        PlaySound(fxPong);
                        ballSpeedY *= -1;
                    }

                    if ((ballPosition.x - ballRadius) <= 0) enemyScore += 1000;
                    else if ((ballPosition.x + ballRadius) > GetScreenWidth()) playerScore += 1000;

                    if (IsKeyDown(KEY_UP)) player.y -= playerSpeed;
                    else if (IsKeyDown(KEY_DOWN)) player.y += playerSpeed;

                    if (player.y <= 0) player.y = 0;
                    else if ((player.y + player.height) >= screenHeight) player.y = screenHeight - player.height;

                    if (CheckCollisionCircleRec(ballPosition, ballRadius, player))
                    {
                        PlaySound(fxPong);
                        ballSpeedX *= -1;
                    }

                    if (IsKeyDown(KEY_W)) enemy.y -= enemySpeed;
                    else if (IsKeyDown(KEY_S)) enemy.y += enemySpeed;

                    if (enemy.y <= 0) enemy.y = 0;
                    else if ((enemy.y + enemy.height) >= screenHeight) enemy.y = screenHeight - enemy.height;

                    if (CheckCollisionCircleRec(ballPosition, ballRadius, enemy))
                    {
                        PlaySound(fxPong);
                        ballSpeedX *= -1;
                    }
                }
                    
                //PAUSA O JOGO COM P
                if (IsKeyPressed(KEY_P)) pause = !pause;

                if (IsKeyPressed(KEY_ENTER)) currentScreen = SCREEN_ENDING;
            } break;
            case SCREEN_ENDING:
            {
                //FIM DO JOGO COM ENTER
                if (IsKeyPressed(KEY_ENTER))
                {
                    finishGame = true;
                }
            } break;
            default: break;
        }

        gifFrameCounter++;
        
        if (gifFrameCounter >= gifFrameSpeed) {
            gifFrameCounter = 0;
            currentGifFrame++;
            if (currentGifFrame >= MAX_GIF_FRAMES) currentGifFrame = 0;
        }

        BeginDrawing();

            ClearBackground(RAYWHITE);

            //FUNDO
            DrawTexture(gifFrames[currentGifFrame], 0, 0, WHITE);

            switch (currentScreen)
            {
                case SCREEN_TITLE:
                {
                    DrawTextEx(fntTitle, "DOBUTSU", (Vector2){ 200, 100 }, fntTitle.baseSize*6, 4, WHITE);

                    if ((framesCounter/30)%2) DrawText("PRESSIONE ENTER para COMEÇAR", 200, 300, 30, WHITE);

                } break;
                
                case SCREEN_GAMEPLAY:
                {
                    DrawCircleV(ballPosition, ballRadius, RED);

                    DrawRectangleRec(player, BLUE);

                    DrawRectangleRec(enemy, DARKGREEN);

                    DrawLine(enemyVisionRange, 0, enemyVisionRange, screenHeight, GRAY);

                    DrawText(TextFormat("%04i", playerScore), 100, 10, 30, BLUE);
                    DrawText(TextFormat("%04i", enemyScore), screenWidth - 200, 10, 30, DARKGREEN);

                    if (pause)
                    {
                        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.8f));
                        DrawText("JOGO PAUSADO", 320, 200, 30, WHITE);
                    }
                } break;
                
                case SCREEN_ENDING:
                {
                    
                    
                    if (enemyScore > playerScore){
                      DrawRectangle(0, 0, screenWidth, screenHeight, GREEN);
                      DrawText("FIM DE JOGO", 10, 10, 30,WHITE);
                      DrawText(TextFormat("Jogador VERDE ganha com %d pontos!", enemyScore), screenWidth / 2 - MeasureText(TextFormat("Jogador VERDE ganha com %d pontos!", enemyScore), 20) / 2, screenHeight / 2, 20, WHITE);
                    } 
                    else if (playerScore > enemyScore){
                     DrawRectangle(0, 0, screenWidth, screenHeight, BLUE);
                     DrawText("FIM DE JOGO", 10, 10, 30,WHITE);
                     DrawText(TextFormat("Jogador AZUL ganha com %d pontos!", playerScore), screenWidth / 2 - MeasureText(TextFormat("Jogador AZUL ganha com %d pontos!", playerScore), 20) / 2, screenHeight / 2, 20, WHITE);
                   }
                   else{
                    DrawRectangle(0, 0, screenWidth, screenHeight, PURPLE);
                    DrawText("FIM DE JOGO", 10, 10, 30,WHITE);
                    const char* empateMsg = "Houve um EMPATE! Jogue novamente!";
                      DrawText(empateMsg, screenWidth / 2 - MeasureText(empateMsg, 20) / 2, screenHeight / 2, 20, WHITE);
                   }
                    
                } break;
                default: break;
            }

        EndDrawing();
    }

    for (int i = 0; i < MAX_GIF_FRAMES; i++) {
        UnloadTexture(gifFrames[i]);
    }
    UnloadFont(fntTitle);

    CloseWindow(); //FECHA O JOGO

    return 0;
}

#include "raylib.h"

int main() {
  int screenWidth = 1920;
  int screenHeight = 1080;
  InitWindow(screenWidth, screenHeight, "Raylib basic window");
  Texture2D arvore = LoadTexture("arvore.png");    
  Texture2D shiba = LoadTexture("dog.png");
  Vector2 position = { 320.0f, 300.0f };
  Rectangle frameRec = { 0.0f, 0.0f, (float)shiba.width/8.01, (float)shiba.height };
  int currentFrame = 0;

  int framesCounter = 0;
  int framesSpeed = 10;  
  SetTargetFPS(40);
  
  while (!WindowShouldClose()) {
    BeginDrawing();
    
    ClearBackground(RAYWHITE);
    framesCounter++;

    DrawTexture(arvore, 0,0, WHITE);
    DrawText("DOBOTSU ", 330, 200, 20, WHITE);
    
    if (framesCounter >= (40/framesSpeed))
    {
            framesCounter = 0;
            currentFrame++;

            if (currentFrame > 8) currentFrame = 0;

            frameRec.x = (float)currentFrame*(float)shiba.width/8.01;
    }
    
    frameRec.x++;

    DrawTextureRec(shiba, frameRec, position, WHITE);
    
    EndDrawing();
  }
  CloseWindow();
  return 0;
}

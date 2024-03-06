#include "raylib.h"

int main() {
  int screenWidth = 1920;
  int screenHeight = 1080;
  InitWindow(screenWidth, screenHeight, "Raylib basic window");
  Texture2D shiba = LoadTexture("dog.png");
  Vector2 position = { 166.0f, 265.0f };
  Rectangle frameRec = { 0.0f, 0.0f, (float)shiba.width/5, (float)shiba.height };
  int currentFrame = 0;

  int framesCounter = 0;
  int framesSpeed = 8;  
  SetTargetFPS(30);
  
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    framesCounter++;

    if (framesCounter >= (30/framesSpeed))
    {
            framesCounter = 0;
            currentFrame++;

            if (currentFrame > 5) currentFrame = 0;

            frameRec.x = (float)currentFrame*(float)shiba.width/5;
    }
    
    frameRec.x++;

    DrawTextureRec(shiba, frameRec, position, WHITE);
    DrawText("Teste ", 20, 20, 20, BLACK);
    EndDrawing();
  }
  CloseWindow();
  return 0;
}

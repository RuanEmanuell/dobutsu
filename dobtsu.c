#include "raylib.h"

int main() {
  int currentScreen = 0;
  int screenWidth = 480;
  int screenHeight = 720;
  InitWindow(screenWidth, screenHeight, "Raylib basic window");
  Texture2D fundo_inicial = LoadTexture("fundo_inicial.png");    
  Texture2D gelo = LoadTexture("gelo.png");  
  Rectangle button = {150, 300, 200, 50};
  Color buttonColor = RED;
  int colorIndex = 0;
  Vector2 position = { 0.0f, 0.0f };
  Rectangle frameRec = { 0.0f, 0.0f, (float)screenWidth, (float)screenHeight};
  int currentFrame = 0;
  

  int framesCounter = 0;
  int framesSpeed = 10;  
  SetTargetFPS(20);
  
  while (!WindowShouldClose()) {
    BeginDrawing();
    
    ClearBackground(RAYWHITE);
    framesCounter++;
    
    switch(currentScreen){
        case 0:
    //Screen do shiba, animação **corrigir frames 
        if (framesCounter >= (50/framesSpeed))
    {
            framesCounter = 0;
            currentFrame++;

            if (currentFrame > 100) currentFrame = 0;

            frameRec.x = (float)currentFrame * (float)(screenWidth);
    }
        DrawTextureRec(fundo_inicial, frameRec, position, WHITE);
        break;
        default:
    //Screen do penguin
           DrawTexture(gelo, 0,0, WHITE);
        break;
    }
    
    if(IsKeyPressed (KEY_ENTER)){
        if(currentScreen < 1){
            currentScreen++;
        }else{
            currentScreen = 0;
        }
    }
    
    Vector2 mousePoint = GetMousePosition();
    bool IsMouseOverButton = CheckCollisionPointRec(mousePoint, button);
    
    if(IsMouseOverButton){
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            if(colorIndex < 1){
                colorIndex++;
            }else{
                colorIndex = 0;
            }
            if(colorIndex == 0){
              buttonColor=RED;   
            }else{
              buttonColor=GREEN;
            }
        }
    }
    
    DrawRectangleRec(button, buttonColor);
    DrawText("NOVO JOGO", button.x + 10, button.y + 10, 20, BLACK);
   
    
    EndDrawing();
  }
  CloseWindow();
  return 0;
}

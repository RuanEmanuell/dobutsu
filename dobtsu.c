#include "raylib.h"

int main() {
  int currentScreen = 0;
  int screenWidth = 480;
  int screenHeight = 720;
  InitWindow(screenWidth, screenHeight, "Raylib basic window");
  Texture2D arvore = LoadTexture("arvore.png");    
  Texture2D gelo = LoadTexture("gelo.png");    
  Texture2D shiba = LoadTexture("dog.png");
  Rectangle button = {100, 100, 200, 50};
  Color buttonColor = RED;
  int colorIndex = 0;
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
    
    switch(currentScreen){
        case 0:
           DrawTexture(arvore, 0,0, WHITE);
        break;
        default:
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

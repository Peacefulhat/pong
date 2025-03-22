#define PONG_IMP
#include"pong.h"

int main(){
  Player left={5,5,{0,0}};
  Player right={P2LOC,5,{0,0}};
  Ball ball ={WIDTH/2,HEIGHT/2,7,false,10.f};
  SetTargetFPS(60);
  InitWindow(WIDTH,HEIGHT,TITLE);
  while(!WindowShouldClose()){
    BeginDrawing();
    ClearBackground(RAYWHITE);
    left_player_move(&left);
    right_player_move(&right);
    ball_move(&ball,left, right);
    EndDrawing();
  }
  
  CloseWindow();
  
  PP(left);
  PP(right);

  return 0;		     
}

#define PONG_IMP
#include"pong.h"

int main(){

  SetTargetFPS(60);
  InitWindow(WIDTH,HEIGHT,TITLE);
  
  vec2 paddle_left={5,5};
  vec2 paddle_right={P2LOC,5};
  vec2 ball_vel={2,2};
  Ball ball ={{WIDTH/2,HEIGHT/2},ball_vel,6};
  real dt=GetFrameTime(); 

  while(!WindowShouldClose()){
    dt=GetFrameTime();
    BeginDrawing();
    ClearBackground(RAYWHITE);
  
    switch(options){
    case 0:
      home_screen();
      break;
    case 1:
      draw_components(&paddle_left,&paddle_right,&ball,ball_vel);
      left_paddle_move(&paddle_left);
      right_paddle_move(&paddle_right);
      ball_wall_collision(&ball, dt*1.2);
      paddle_ball_collision(&ball, paddle_left, paddle_right, dt);
      break;
    case 2:
      // settings not implemented yet
      settings();
      break;
      
    case 3:
      quit_screen();
      break;
      
    default:
      
    }
    
    EndDrawing();
}
  
  CloseWindow();
  return 0;		     
}

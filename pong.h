#ifndef PONG_H
#define PONG_H
//Goal to this to write chaotic pong.:)
#include<stdio.h>
#include<raylib.h>
#include<stdbool.h>
#include<math.h>


#define HEIGHT 400
#define WIDTH 400
#define TITLE "Chaotic Pong"
#define SPEED 5
#define RWIDTH 20
#define RHEIGHT 65
#define COLOR_RECT RED
#define COLOR_BALL RED
#define P2LOC (WIDTH-RWIDTH)-5

typedef struct {
  int x, y;
}velocity;

typedef struct {
  int x, y;
  velocity v;
}Player;

typedef struct {
  int x,y;
  int radius;
  bool wall_col;
  velocity v;
}Ball;

#define PP(p) printf("{x: %d, y: %d}\n",p.x,p.y);
void left_player_move(Player *left);
void right_player_move(Player *right);
void ball_move(Ball *ball, Player left, Player right);


#endif// PONG_H


#ifdef PONG_IMP

 void left_player_move(Player *left) {
   
    if (left->y <= SPEED) {
      left->y = SPEED;
    }
    if (left->y >= HEIGHT - RHEIGHT-SPEED) {
      left->y = HEIGHT - RHEIGHT-SPEED;
    }

    if (IsKeyDown(KEY_UP)) {
        left->y -= SPEED;
    }
    if (IsKeyDown(KEY_DOWN)) {
        left->y += SPEED;
    }
     DrawRectangle(left->x, left->y, RWIDTH, RHEIGHT, COLOR_RECT);
}


 void right_player_move(Player *right) {
   
    if (right->y <=SPEED) {
        right->y = SPEED;
    }
    if (right->y >= HEIGHT - RHEIGHT - SPEED) {
        right->y = HEIGHT - RHEIGHT - SPEED; 
    }

    if (IsKeyDown(KEY_W)) {
        right->y -= SPEED;
    }
    if (IsKeyDown(KEY_S)) {
        right->y += SPEED;
    }
     DrawRectangle(right->x, right->y, RWIDTH, RHEIGHT, COLOR_RECT);
}


void ball_move(Ball* ball, Player left, Player right){
  DrawCircle(ball->x, ball->y, ball->radius, COLOR_BALL);
}

#endif

#ifndef PONG_H
#define PONG_H

//Goal to this to write chaotic pong.:)
// not completed yet Goal is described above
#include<stdio.h>
#include<raylib.h>
#include<stdbool.h>
#include<math.h>
#include<unistd.h>
#define PMATH_IMP
#include"pmath.h"
#include<stdlib.h>

#define MARGIN 5
#define HEIGHT 665
#define WIDTH 800
#define TITLE "Pong"
#define SPEED 10
#define RWIDTH 20
#define RHEIGHT 130
#define COLOR_RECT RED
#define COLOR_BALL RED
#define P2LOC (WIDTH-RWIDTH) - 5
#define BALL_VEL_SCALE 100
#define SCORE_REGION 65

typedef struct{
    unsigned int p1,p2;
    bool state;
}pair;

typedef struct {
    vec2 pos;
    vec2 vel;
    int radius;
}Ball;

int options = 0;
int rounds=10;
pair score={0,0,false};

#define PP(p) printf("{x: %f, y: %f}\n",p.x,p.y);
void draw_components(vec2 *left , vec2*right,Ball *b,vec2 ini);
void left_paddle_move(vec2 *left);
void right_paddle_move(vec2 *right);
void ball_wall_collision(Ball *b,real dt);
void paddle_ball_collision(Ball*b, vec2 paddle_left,vec2 paddle_right ,real dt);
void get_score(Ball *b);
void reset(Ball*b, vec2 *left, vec2*right,vec2 ini);
void home_screen();
void quit_screen();
void settings();

#endif// PONG_H


#ifdef PONG_IMP

void settings(){
}

void get_score(Ball *b) {
    if (b->pos.x < b->radius) { 
        score.p2 += 1;
        score.state = true;
    }
    if (b->pos.x > WIDTH-b->radius) {  
        score.p1 += 1;
        score.state = true;
    }
}


void reset(Ball*b, vec2 *left, vec2*right,vec2 ini){
    PMA_ASSERT(b!=NULL);
    PMA_ASSERT(left!=NULL);
    PMA_ASSERT(right!=NULL);
    
    b->pos.x=WIDTH/2;
    b->pos.y=HEIGHT/2;
    left->x=MARGIN;
    left->y=MARGIN;
    right->x=P2LOC;
    right->y=MARGIN;
    b->vel.x=ini.x;
    b->vel.y=ini.x;
    
    return ;
}

void quit_screen(){
    
    for(int i=0;i<120;i++){ 
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("GOODBYE!", 80, 100, 100, RED);
        DrawText("Thanks For Playing", 100, 250, 30, RED);
        EndDrawing();
    }
    exit(0);
}


void home_screen(){
    
    const vec2 title={150,100};
    const vec2 line={145,160};
    const Rectangle play={250,230,200,50};
    const Rectangle settings ={250,300,300,50};
    const vec2 b_offset={25,5};
    const Rectangle quit ={250,370,200,50};
    
    DrawText("HELLO,PONG",(int)title.x,(int)title.y,70,BLACK);
    DrawText("==================",(int)line.x,(int)line.y,50,RED);
    
    //play
    DrawRectangleLinesEx(play, 3, BLACK);
    DrawText("PLAY", play.x+(int)b_offset.x,play.y+(int)b_offset.y, 50, DARKBLUE);
    
    // settings
    DrawRectangleLinesEx(settings, 3, BLACK);
    DrawText("SETTINGS", settings.x+(int)b_offset.x,settings.y+(int)b_offset.y, 50, DARKBLUE);
    
    //quit
    DrawRectangleLinesEx(quit, 3, BLACK);
    DrawText("QUIT", quit.x+(int)b_offset.x,quit.y+(int)b_offset.y, 50, DARKBLUE);
    
    Vector2 mouse=GetMousePosition();
    if((mouse.x>play.x && mouse.x<play.x+200) &&
    (mouse.y>play.y&&mouse.y<play.y+50)){
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            options=1;
        }
    }
    
    if((mouse.x>settings.x && mouse.x<settings.x+200) &&
    (mouse.y>settings.y&&mouse.y<settings.y+50)){
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            options=2;
        }
    }
    if((mouse.x>quit.x && mouse.x<quit.x+200) &&
    (mouse.y>quit.y&&mouse.y<quit.y+50)){
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            options=3;
        }
    }  
}

void draw_components(vec2 *left , vec2*right,Ball *b, vec2 iniv){
    PMA_ASSERT(left!=NULL);
    PMA_ASSERT(right!=NULL);
    PMA_ASSERT(b!=NULL);
    
    
    // middle line
    DrawRectangle(WIDTH / 2, 0, 3, HEIGHT, COLOR_RECT);
    
    // paddles
    DrawRectangle(left->x, left->y, RWIDTH, RHEIGHT, COLOR_RECT);
    DrawRectangle(right->x, right->y, RWIDTH, RHEIGHT, COLOR_RECT);
    
    
    // Score region

    DrawRectangle(0, 0, WIDTH, SCORE_REGION, RAYWHITE);
    DrawRectangle(0, SCORE_REGION - 5, WIDTH,5, RED);
    
    // back button
    Rectangle back={MARGIN,20, 30, 30};
    DrawRectangleLinesEx(back, 3, BLACK);
    DrawText("<-",back.x+5,back.y+5, 25, BLACK);
    
    // home logic
    /*Vector2 mouse=GetMousePosition();
    if((mouse.x>back.x && mouse.x<back.x+5) &&
    (mouse.y>back.y&&mouse.y<back.y+5)){
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            options=0;
        }
    }*/

    Vector2 mouse = GetMousePosition();
    if (CheckCollisionPointRec(mouse, back) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        options = 0;
    }
    
    DrawText("SCORE", WIDTH / 2 - 110, 10, 30, RED);
    char score_text[20]; 
    sprintf(score_text, "%d : %d", score.p1, score.p2);
    
    DrawText(score_text, WIDTH / 2, 10, 30, RED);
    get_score(b);
    
    if(score.state==true){
        reset(b,left,right, iniv);
        score.state=false;
    }
}


void left_paddle_move(vec2 *left) {
    PMA_ASSERT(left!=NULL);
    if (left->y <= SCORE_REGION + SPEED) {
        left->y = SCORE_REGION + SPEED;
    }
    if (left->y >= HEIGHT - RHEIGHT - SPEED) {
        left->y = HEIGHT - RHEIGHT - SPEED;
    }

    if (IsKeyDown(KEY_UP)) {
        left->y -= SPEED;
    }
    if (IsKeyDown(KEY_DOWN)) {
        left->y += SPEED;
    }
    
    DrawRectangle(left->x, left->y, RWIDTH, RHEIGHT, COLOR_RECT);
}

void right_paddle_move(vec2 *right) {
    PMA_ASSERT(right!=NULL);
    
    if (right->y <= SCORE_REGION + SPEED) {
        right->y = SCORE_REGION + SPEED;
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

void ball_wall_collision(Ball *b, real dt) {
    PMA_ASSERT(b != NULL);
    vec_scaled_add2d(&b->pos, b->pos, b->vel, dt*BALL_VEL_SCALE);
    // x wall collision
    if (b->pos.x > WIDTH - b->radius || b->pos.x < b->radius) {
        b->vel.x = -b->vel.x;
    }

    // y wall collision
    if (b->pos.y > HEIGHT - b->radius) {
        b->vel.y = -b->vel.y;
    }
    if (b->pos.y < SCORE_REGION + b->radius) {  
        b->vel.y = -b->vel.y;
    }

    DrawCircle(b->pos.x, b->pos.y, b->radius, COLOR_BALL);
}


void paddle_ball_collision(Ball *b, vec2 left, vec2 right, real dt) {
    PMA_ASSERT(b != NULL);
    // left paddle right edge
    if ((b->pos.x - b->radius) <= (left.x + RWIDTH) &&
    (b->pos.y >= left.y) && (b->pos.y <= left.y + RHEIGHT)) {
        b->vel.x = -b->vel.x;
    }
    
    // right paddle left edge
    if ((b->pos.x + b->radius) >= right.x &&
    (b->pos.y >= right.y) && (b->pos.y <= right.y + RHEIGHT)) {
        b->vel.x = -b->vel.x;
    }
}


#endif

#ifndef PMATH_H
#define PMATH_H
#include<stdio.h>
#include<assert.h>
#include<string.h>
#include<math.h>

#define PMA_ASSERT assert
#define real_sqrt sqrtf

typedef float real;

typedef struct{
  real x,y;
}vec2;


// vector 2d 
void vec_init2d(vec2 *vec,real x, real y);
void vec_invert2d(vec2*vec);
real vec_mag2d(vec2 vec);
void vec_normalize2d(vec2 *vec);
void vec_scaler_mul2d(vec2* vec,real value);
void vec_sum2d(vec2*dst, vec2 a ,vec2 b);
void vec_scaled_add2d(vec2 *dst ,vec2 a, vec2 b, real scale);
void vec_sub2d(vec2*dst ,vec2 a, vec2 b);
real dot_product2d(vec2 a, vec2 b);
#define VEC_PRINT2D(vec) printf("{x:%f, y:%f}\n",vec->x,vec->y)

#endif // PMATH_H



#ifdef PMATH_IMP

void vec_init2d(vec2 *vec,real x, real y){
  
  PMA_ASSERT(vec!=NULL);
  vec->x=x;
  vec->y=y;

}

void vec_invert2d(vec2*vec){
  
  PMA_ASSERT(vec!=NULL);
  vec->x=-vec->x;
  vec->y=-vec->y;

}


real vec_mag2d(vec2 vec){
    return real_sqrt(vec.x*vec.x+vec.y*vec.y);
}


void vec_normalize2d(vec2 *vec){
  
  PMA_ASSERT(vec!=NULL);
  real mag=vec_mag2d(*vec);
  PMA_ASSERT(mag>0);
  
  vec->x*=(real)1/mag;
  vec->y*=(real)1/mag;
}

void vec_scaler_mul2d(vec2* vec,real value){
  PMA_ASSERT(vec!=NULL);
  vec->x*=value;
  vec->y*=value;
}

void vec_sum2d(vec2*dst, vec2 a ,vec2 b){
  
  PMA_ASSERT(dst!=NULL);
  dst->x=a.x+b.x;
  dst->y=a.y+b.y;
}

void vec_sub2d(vec2*dst, vec2 a ,vec2 b){
  
  PMA_ASSERT(dst!=NULL);
  dst->x=a.x-b.x;
  dst->x=a.y-b.y;
}

void vec_scaled_add2d(vec2 *dst,vec2 a, vec2 b, real scale){
  
  PMA_ASSERT(dst!=NULL);
  vec_scaler_mul2d(&b,scale);
  dst->x=a.x+b.x;
  dst->y=a.y+b.y;
}

real dot_product2d(vec2 a, vec2 b){
  
  return(a.x*b.x)+(a.y*b.y);
}

real cross_product2d(vec2 a, vec2 b){
  return (a.x*b.y)-(a.y*b.x);
}

#endif//PMATH_IMP

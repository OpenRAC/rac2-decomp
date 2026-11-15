#include "include_asm.h"
#include "common.h"
typedef int Vector128 __attribute__((mode(TI)));
typedef struct { Vector128 rows[3]; } Triangle;
extern float func_002A7878(float,float);
extern int func_002A7820(int,int);
extern void func_00282D30(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
extern void func_00283098(void *,void *,void *);
extern char *func_002C6DD8(void *,void *,int,float);
extern float D_L16_001B15F0 __attribute__((sda));
extern float D_L16_001B15F4[] __attribute__((sda));
extern int D_L16_001B15E8 __attribute__((sda));
extern int D_L16_001B15EC[] __attribute__((sda));
extern int D_L16_001B15E0 __attribute__((sda));
extern int D_L16_001B15E4[] __attribute__((sda));
extern Triangle D_L16_001B1600;
extern char D_L16_001A8F20[] __attribute__((sda));
/* Spawns one sparkle at a random spot inside a triangle on the object. */
void func_L16_0040C5F0(char *object)
{
    float weights[4];
    Vector128 point[1],temporary[1];
    Triangle triangle;
    int lifetime;
    float amount,reciprocal;
    char *effect;
    char *translation, *matrix;
    amount=-(RandomFloatRange(D_L16_001B15F0,D_L16_001B15F4[0])*0.0002777777845f);
    lifetime=RandomIntRange(D_L16_001B15E8,D_L16_001B15EC[0]);
    {
        float *weight=weights;
        int i;
        for(i=2;i>=0;i--) *weight++=RandomFloatRange(0.0f,1.0f);
    }
    matrix=object+0xc0;
    translation=object+0x10;
    reciprocal=1.0f/(weights[0]+weights[1]+weights[2]);
    {
        float *weight=weights;
        int i;
        for(i=2;i>=0;i--,weight++) *weight *= reciprocal;
    }
    triangle.rows[0]=D_L16_001B1600.rows[0];
    triangle.rows[1]=D_L16_001B1600.rows[1];
    triangle.rows[2]=D_L16_001B1600.rows[2];
    FastVecScale(point,&triangle.rows[0],weights[0]);
    FastVecScale(temporary,&triangle.rows[1],weights[1]);
    FastVecAdd(point,point,temporary);
    FastVecScale(temporary,&triangle.rows[2],weights[2]);
    FastVecAdd(point,point,temporary);
    matrix_mul_vec3(point,point,matrix);
    FastVecAdd(point,point,translation);
    effect=SpawnTrailParticle_002C6DD8(point,D_L16_001A8F20,lifetime,amount);
    if(effect!=0) {
        *(int *)(effect+4)=D_L16_001B15E0;
        *(int *)(effect+12)=D_L16_001B15E4[0];
    }
}

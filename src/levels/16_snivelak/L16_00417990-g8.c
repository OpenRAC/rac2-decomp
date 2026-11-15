#include "common.h"
typedef int Vector128 __attribute__((mode(TI)));
extern void func_00282D30(void *,void *,float);
extern char *func_L00_0033E220(void *,void *,unsigned int,int,int,int,int,int,float,float);
extern void *func_002A9640(void *,unsigned int,int);
extern void func_002A7750(unsigned char *,int,int);
extern void func_L00_0032A258(void *,void *,void *,void *,int,int,int,int,int,int,int);
/* Mixed arguments preserve the EE ABI order within each register bank. */
extern void func_L00_002EC248(void *,void *,float,void *,float,int,int,float,float,float);
extern void func_L00_00324F18(char *,char *,float,float,float);
extern void func_002ABBB8(void *,void *,void *,float,float,int,int,int,float,int,float,float,float,float,int,int,int,int,int);
extern void func_002B9180(void *);
extern char *func_L00_00326620(char *,int,int);
extern int func_00282948(int *);
extern int func_002A7820(int,int);
extern char D_L16_001B1BF0[] SDATA(D_L16_001B1BF0);
extern char D_L16_001B1BE8[] SDATA(D_L16_001B1BE8);
extern char D_L16_001B1BE0[] SDATA(D_L16_001B1BE0);
extern int D_L16_001B1C10 __attribute__((sda));
void func_L16_00417990(char *object)
{
    Vector128 position[1],velocity[1],zero[1];
    int *state=*(int **)(object+0x68);
    *(Vector128 *)position=0;
    *(Vector128 *)velocity=0;
    ((float *)position)[0]=13.0f;
    ((float *)position)[2]=15.0f;
    ((float *)velocity)[0]=0.1666666716f;
    ((float *)velocity)[2]=0.1166666746f;
    switch(*(unsigned char *)(object+0x20)) {
    case 0:
        func_002A7750((unsigned char *)object,1,-1);
        break;
    case 1:
        FastVecScale(position,position,*(float *)(object+0x2c));
        state[1]=(int)func_L00_0033E220(position,object,0x28202080u,-1,1,2,0,0x60,*(float *)(object+0x2c)*3780000.0f,0.75f);
        if(func_002A9640(object,0x4010000u,0)!=0 && state[0]==0) func_002A7750((unsigned char *)object,2,-1);
        *(unsigned char *)(object+0xa8)=0xff;
        break;
    case 2:
        func_L00_0032A258(object,D_L16_001B1BF0,D_L16_001B1BE8,D_L16_001B1BE0,0xffff,0,D_L16_001B1C10,0,0xffff,0xff,0);
        func_L00_002EC248(object,position,0.2f,velocity,0.1166666746f,40,1,1.0f,5.0f,1.0f);
        *(Vector128 *)zero=0;
        func_L00_00324F18(object,(char *)position,13.0f,0.0f,14.0f);
        SpawnExplosionEffects(object,zero,position,0.0f,0.0f,10,3,5,0.0f,-1,1.0f,9.0f,0.75f,0.0f,0,0,-1,0,0x810001);
        if(state[1]!=0) func_002B9180((void *)state[1]);
        func_L00_00326620(object,0x10f2,0);
        *(int *)(object+0x98)=0;
        object[0x31]=0;
        *(unsigned short *)(object+0x34)|=1;
        state[2]=100;
        func_002A7750((unsigned char *)object,3,-1);
        break;
    case 3:
        if(state[2]>80) {
            FastVecScale(velocity,velocity,0.5f);
            func_L00_002EC248(object,position,0.0f,velocity,0.05000000447f,4,1,1.0f,5.0f,1.0f);
        }
        if(func_00282948(state+2)!=0) {
            FastVecScale(velocity,velocity,0.3333333433f);
            ((float *)velocity)[2]*=0.3333333433f;
            func_L00_002EC248(object,position,0.0f,velocity,0.05000000447f,func_002A7820(3,6),1,0.5f,15.0f,1.0f);
            func_L00_002EC248(object,position,0.0f,velocity,0.05000000447f,func_002A7820(3,6),0,0.5f,15.0f,1.0f);
            state[2]=func_002A7820(30,80);
        }
        break;
    }
}

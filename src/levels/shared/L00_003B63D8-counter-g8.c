#include "common.h"
typedef unsigned int TI128 __attribute__((mode(TI)));
typedef union {TI128 q;float v[4];} Vector;

/* Measured camera prefix: its position precedes the three-row basis. */
typedef struct {
    float position[4];
    u8 reserved10[0x220];
    float basis[3][4];
} CameraBasisPrefix;
typedef struct NODE NODE;
typedef void (*DrawCallback_r002E6CF0)(void *);
extern unsigned int D_00138324[];
extern int D_L00_001A8F00 MACRO_ADDR;
extern int mode_gp SDATA(D_L00_001A8F00);
extern int D_L00_001B1BE8 MACRO_ADDR;
extern float D_L00_001B18E0;
extern CameraBasisPrefix D_L00_001B8DC0;
extern float D_L00_001AFA44 __attribute__((sda));
extern int D_L00_001AFA4C __attribute__((sda));
extern void func_002A7750(unsigned char *,unsigned char,int),func_0029F338(void *);
extern int func_002B49E0(int,int,int,int,unsigned char *),func_002B4B70(int,int);
extern int func_L00_003B6858(void *);
extern void func_L00_003B69D8(void *),func_L00_003B75C8(void *),func_L00_003B72B0(void *),func_L00_003B77A8(void *);
extern void func_L00_003B7908(void *),func_L00_002E6CF0(DrawCallback_r002E6CF0,void *),func_L00_003B6A90(NODE *);
extern float func_002AA2E8(float *,float,float);
extern void func_002833F0(float *,float *),func_00283698(void *,void *),func_00282CF0(void *,void *,void *),func_00283098(void *,void *,void *);
extern void func_L00_003B7190(float *,float *),func_L00_003B7260(float,float,float,float *,float *),func_00282CC0(void *,void *,void *),func_00282F20(void *,void *,float);
extern void func_L00_003B74A8(unsigned char *,void *);
extern int func_002A8C28(void *,float *,float,int,float,float,int,int,int);
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define U(p,o) (*(unsigned short *)((char *)(p)+(o)))
void func_L00_003B63D8(unsigned char *object)
{
    Vector point;
    /* 00283698 reads three source rows and writes all four destination rows. */
    float inverse[4][4];
    Vector velocity,spawn,offset;
    char *context=*(char **)(object+0x68);
    int mode;
    switch(object[0x20]) { case 0: {
        if(!D_L00_001A8F00) {func_002B49E0(7,1,(int)object,2,0);return;}
        if(D_L00_001A8F00==7 && func_L00_003B6858(object)) {
            point.q=0;point.v[1]=1.5707964f;
            func_002833F0(D_L00_001B8DC0.basis,point.v);
            func_002A7750(object,1,-1);return;
        }
        { unsigned timer=U(object,0x96),old=timer++;
          U(object,0x96)=timer; if(old<6)return; }
        func_0029F338(object);return;
    break; } case 1: {
        D_L00_001B1BE8=1;
        func_L00_003B69D8(object);
        func_L00_003B75C8(object);
        func_L00_003B72B0(object);
        func_L00_003B77A8(object);
        func_L00_002E6CF0(func_L00_003B7908,object);
        if(I(context,0x60) && I(context,0x64)++>=91) {
            func_002AA2E8(&D_L00_001B18E0,1.0f,0.06666667f);
            mode=mode_gp;
            if(D_L00_001B18E0>=1.0f) {
                func_L00_003B6A90((NODE *)object);
                func_L00_003B6858(object);
                I(context,0x64)=0; I(context,0x60)=0;
                mode=D_L00_001A8F00;
            }
        } else {
            func_002AA2E8(&D_L00_001B18E0,0.0f,0.06666667f);
            mode=D_L00_001A8F00;
        }
        if(mode!=7) {
            func_L00_003B6A90((NODE *)object);
            func_0029F338(object);return;
        } else {
            if(!(D_00138324[0]&0x10))return;
            func_002B4B70(1,0);return;
        }
    break; } case 2: {
        func_00283698(inverse,D_L00_001B8DC0.basis);
        func_00282CF0(&point,object+0x10,D_L00_001B8DC0.position);
        func_00283098(&point,&point,inverse);
        func_00283098(&velocity,context,inverse);
        func_L00_003B7190(point.v+1,point.v+2);
        func_L00_003B7260(point.v[1],point.v[2],D_L00_001AFA44*0.00027777778f,velocity.v+1,velocity.v+2);
        velocity.v[0]=0.0f;
        func_00282CC0(&point,&point,&velocity);
        func_00283098(object+0x10,&point,D_L00_001B8DC0.basis);
        func_00282CC0(object+0x10,object+0x10,D_L00_001B8DC0.position);
        func_00283098(context,&velocity,D_L00_001B8DC0.basis);
        if(point.v[1]*point.v[1]+point.v[2]*point.v[2]<0.09f) {func_0029F338(object);return;} else {
            func_L00_003B74A8(object,object+0x10);
            func_00282F20(&offset,D_L00_001B8DC0.basis,-0.1f);
            func_00282CC0(&spawn,object+0x10,&offset);
            func_002A8C28(*(void **)(object+0xB8),spawn.v,0.1f,0x10000,1.0f,1.0f,0,1,0);
            func_00282CF0(&spawn,object+0x10,&offset);
            func_002A8C28(*(void **)(object+0xB8),spawn.v,0.1f,0x10000,1.0f,1.0f,0,1,0);
            func_00282CF0(&spawn,object+0x10,&offset);
            func_002A8C28(*(void **)(object+0xB8),spawn.v,0.1f,0x10000,1.0f,1.0f,0,1,0);
            if(D_L00_001A8F00==7) {int limit=D_L00_001AFA4C; unsigned timer=U(object,0x96),old=timer++;
              U(object,0x96)=timer; if((int)old<=limit)return;}
        }
    }
    break; default: return; }
    func_0029F338(object);
}

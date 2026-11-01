#include "include_asm.h"

#include "common.h"
typedef int HeroQ __attribute__((mode(TI)));
typedef union { unsigned char b[0x2600]; signed char c[0x2600]; short h[0x1300]; unsigned short uh[0x1300]; int i[0x980]; unsigned int u[0x980]; float f[0x980]; char *ptr[0x980]; HeroQ q[0x260]; } Hero;
extern unsigned char D_00189E20[];
#define H ((Hero *)D_00189E20)
typedef int Vector128 __attribute__((mode(TI)));
typedef struct { int a,b,c,d; } __attribute__((aligned(16))) Quad16;
typedef struct { Quad16 vector; int owner,flags; unsigned char enabled,kind; unsigned short id; float distance; int active; } CollisionRequest;
typedef struct { Vector128 position,offset; CollisionRequest request; Vector128 direction; } MarkerWorkspace;
extern float func_002A7940(void);
extern void func_002A7750(unsigned char *,int,int);
extern void func_00282F20(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
extern int func_00277258(void *,int,void *,float);
extern void func_002A8C00(char *,int,int,float,Quad16 *);
extern void func_PAL_L00_002B3000(void);
extern void func_00282D60(void *,void *,float);
extern float func_00283B98(float,float);
extern float func_002A78D8(float,float);
extern void func_L00_002E6CF0(void (*)(void *),void *);
extern void func_L13_0041FBE0(void *);
extern float func_002AA2E8(float *,float,float);
extern int D_001A79F0;
extern char *D_L13_001BFD18 NOT_SDA;
extern Quad16 D_L13_001A8F20 MACRO_ADDR;
extern float D_L13_001B1A30 __attribute__((sda));
extern float D_L13_001B1A34 __attribute__((sda));
extern float D_L13_001B1A38 __attribute__((sda));

void func_PAL_L13_00424870(char *object)
{
    MarkerWorkspace local;
    float *state=*(float **)(object+0x68);
    float value;
    int i;
    switch (*(unsigned char *)(object+0x20)) { case 1: goto active; case 0: break; case 2: default: goto common; }

        state[0]=1.0f;
        state[8]=func_002A7940();
        state[2]=0.5f;
        state[1]=0.0f;
        state[0]=1.0f;
        for(i=3;i>=0;i--) state[i+4]=1.0f;
        *(unsigned char *)(object+0x30)=0xff;
        func_002A7750((unsigned char *)object,1,-1);
        object[0x31]=0;
        *(unsigned short *)(object+0x34)|=1;
    goto common;
active:
    if (D_001A79F0==16) {

        qcopy(&local.position,&H->q[8]);
        func_00282F20(&local.offset,H->ptr[2212]+0xe0,0.75f);
        func_00282CC0(&local.position,&local.position,&local.offset);
        if (func_00277258(&local.position,0,H->ptr[2212],0.5f)!=0 && D_L13_001BFD18!=0 && D_L13_001BFD18==object) {
            func_002A8C00((char *)&local.request,(int)object,1,100.0f,&D_L13_001A8F20);
            local.request.id=*(unsigned short *)(object+0xaa);
            func_PAL_L00_002B3000();
        }
        if (H->ptr[207]!=0 && H->ptr[207]==object && H->i[208]!=0) {
            ((float *)&local.direction)[0]=0.0f;
            ((float *)&local.direction)[1]=1.0f;
            ((float *)&local.direction)[2]=0.0f;
            ((float *)&local.direction)[3]=1.0f;
            func_00282F20(&local.direction,&local.direction,10.0f);
            func_002A8C00((char *)&local.request,(int)object,1,10.0f,(Quad16 *)&local.direction);
            local.request.id=*(unsigned short *)(object+0xaa);
            func_PAL_L00_002B3000();
        }
    }
common:
    if (state[0]!=0.0f) {
        func_00282D60(&local.position,object,0.0009765625f);
        state[8]=func_00283B98(state[8],D_L13_001B1A30*0.0003490659f);
        state[3]+=(D_L13_001B1A34+func_002A78D8(0.25f,0.5f))*0.020000001f;
        if (state[3]>1.0f) state[3]-=1.0f;
        for(i=1;i<=2;i++) {
            value=state[i]+D_L13_001B1A38*0.020000001f;
            state[i]=value;
            if(value>1.0f) state[i]=value-1.0f;
        }
        func_L00_002E6CF0(func_L13_0041FBE0,object);
        func_002AA2E8(state,1.0f,0.010000001f);
    }
}

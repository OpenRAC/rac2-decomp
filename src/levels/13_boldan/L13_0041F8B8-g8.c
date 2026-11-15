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
extern void func_L00_002B30E8(void);
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
/* Updates a floating marker the player can target. It spins, glows, and reacts when the player aims at it or touches it. */
void func_L13_0041F8B8(char *moby)
{
    MarkerWorkspace work;
    float *vars=*(float **)(moby+0x68);
    float value;
    int i;
    switch (*(unsigned char *)(moby+0x20)) { case 1: goto active; case 0: break; case 2: default: goto common; }

        vars[0]=1.0f;
        vars[8]=RandomAngle();
        vars[2]=0.5f;
        vars[1]=0.0f;
        vars[0]=1.0f;
        for(i=3;i>=0;i--) vars[i+4]=1.0f;
        *(unsigned char *)(moby+0x30)=0xff;
        SetMobyState((unsigned char *)moby,1,-1);
        moby[0x31]=0;
        *(unsigned short *)(moby+0x34)|=1;
    goto common;
active:
    if (gCurrentMapIndex==16) {

        qcopy(&work.position,&H->q[8]);
        vec_scale_to_length(&work.offset,H->ptr[2212]+0xe0,0.75f);
        FastVecAdd(&work.position,&work.position,&work.offset);
        if (TestPointAgainstCollision(&work.position,0,H->ptr[2212],0.5f)!=0 && D_L13_001BFD18!=0 && D_L13_001BFD18==moby) {
            make_hit_descriptor((char *)&work.request,(int)moby,1,100.0f,&D_L13_001A8F20);
            work.request.id=*(unsigned short *)(moby+0xaa);
            RecordHeroPlayCounters();
        }
        if (H->ptr[207]!=0 && H->ptr[207]==moby && H->i[208]!=0) {
            ((float *)&work.direction)[0]=0.0f;
            ((float *)&work.direction)[1]=1.0f;
            ((float *)&work.direction)[2]=0.0f;
            ((float *)&work.direction)[3]=1.0f;
            vec_scale_to_length(&work.direction,&work.direction,10.0f);
            make_hit_descriptor((char *)&work.request,(int)moby,1,10.0f,(Quad16 *)&work.direction);
            work.request.id=*(unsigned short *)(moby+0xaa);
            RecordHeroPlayCounters();
        }
    }
common:
    if (vars[0]!=0.0f) {
        scale_vector(&work.position,moby,0.0009765625f);
        vars[8]=FastAddRotations(vars[8],D_L13_001B1A30*0.0002908882452f);
        vars[3]+=(D_L13_001B1A34+RandomSignedFloatRange(0.25f,0.5f))*0.016666668f;
        if (vars[3]>1.0f) vars[3]-=1.0f;
        for(i=1;i<=2;i++) {
            value=vars[i]+D_L13_001B1A38*0.016666668f;
            vars[i]=value;
            if(value>1.0f) vars[i]=value-1.0f;
        }
        AddDrawCallbackToList1(DrawPulsingGlowStrip,moby);
        ApproachValue(vars,1.0f,0.008333333768f);
    }
}

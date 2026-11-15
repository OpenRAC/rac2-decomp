#include "include_asm.h"
#include "names.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;

extern int D_L02_001B03DC __attribute__((sda));
extern float D_L02_001B03D4 __attribute__((sda)),D_L02_001B03D8 __attribute__((sda));
extern float D_L02_001B03C8 __attribute__((sda)),D_L02_001B03CC __attribute__((sda)),D_L02_001B03D0 __attribute__((sda));
/* Six-word parameter record, verified in retail and read through +0x14. */
typedef struct { void *colours; void *sizes; void *lifetimes; int kind; int count; float acceleration; } EffectParameters24;
extern EffectParameters24 D_L02_001B03B0 __attribute__((sda));
extern char D_L02_001BA500[];
extern int func_002A77E0(int);
extern void func_00282C88(Quad *),func_00282CC0(void *,void *,void *),func_00282CF0(void *,void *,void *),func_00282F20(void *,void *,float),func_002ACB48(float *,float);
extern float func_002A7878(float,float);
extern void *func_L02_003449D8(void *,void *,void *,void *,int);
/* Sometimes spawns a small puff effect near the object, drifting upward. */
void func_L02_003D7040(char *object) {
    Vector velocity,origin,direction;
    float speed;
    int variant;
    if (RandomIntBelow(D_L02_001B03DC)) return;
    velocity.q=0;
    ClearVector128(&origin.q);
    FastVecAdd(&origin,&origin,object+0x10);
    origin.f[3]=0.0f;
    origin.f[2]+=D_L02_001B03D4;
    FastVecSub(&direction,gCameraPosition_L02,&origin);
    direction.f[2]=0.0f;
    vec_scale_to_length(&direction,&direction,D_L02_001B03D8);
    FastVecAdd(&origin,&origin,&direction);
    AddRandomOffsetToVector(origin.f,D_L02_001B03C8);
    speed=RandomFloatRange(D_L02_001B03CC,D_L02_001B03D0);
    velocity.f[2]=speed*0.0166666675f;
    variant=RandomIntBelow(2);
    SpawnEnemyRecord(&origin,&velocity,&D_L02_001B03B0,(void *)variant,1);
}

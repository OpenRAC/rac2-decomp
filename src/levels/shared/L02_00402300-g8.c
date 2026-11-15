#include "include_asm.h"
#include "names.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;

extern float D_L02_001B17B8 __attribute__((sda)),D_L02_001B17BC __attribute__((sda));
extern float D_L02_001B17AC __attribute__((sda)),D_L02_001B17B0 __attribute__((sda));
extern float D_L02_001B17B4 __attribute__((sda)),D_L02_001B17A0 __attribute__((sda));
extern float D_L02_001B17A4 __attribute__((sda)),D_L02_001B17A8 __attribute__((sda));
/* Two adjacent four-word parameter records, verified in retail data.
   The effect allocator reads the colour and lifetime at offsets 0 and 12. */
typedef struct { unsigned int colour, field04, field08; unsigned short lifetime, reserved; } EffectParameters16;
extern EffectParameters16 D_L02_001B1790 __attribute__((sda)),D_L02_001B1780 __attribute__((sda));
extern char D_L02_001BA500[];
extern void func_00282CF0(void *,void *,void *),func_00282F20(void *,void *,float),func_00282CC0(void *,void *,void *),func_002ACB48(float *,float);
extern float func_002A7878(float,float);
extern int func_002A77E0(int);
extern void *func_L00_0033C0D0(void *,void *,void *,void *,int);
/* The child consumes five GPR inputs and deliberately returns a pointer. */
/* Spawns two small puffs near the object, each drifting slowly upward. */
void func_L02_00402300(char *object) {
    Vector velocity,origin,direction;
    int variant;
    velocity.q=0;
    origin.q=*(Quad *)(object+0x10);
    origin.f[2]+=D_L02_001B17B8;
    FastVecSub(&direction,gCameraPosition_L02,&origin);
    direction.f[2]=0.0f;
    vec_scale_to_length(&direction,&direction,D_L02_001B17BC);
    FastVecAdd(&origin,&origin,&direction);
    velocity.f[2]=RandomFloatRange(D_L02_001B17AC,D_L02_001B17B0)*0.0166666675f;
    variant=RandomIntBelow(2);
    SpawnObjectRelativeParticle(object,&origin,&velocity,&D_L02_001B1790,variant);
    origin.q=*(Quad *)(object+0x10);
    origin.f[2]+=D_L02_001B17B4;
    AddRandomOffsetToVector(origin.f,D_L02_001B17A0);
    velocity.f[2]=RandomFloatRange(D_L02_001B17A4,D_L02_001B17A8)*0.0166666675f;
    variant=RandomIntBelow(2);
    SpawnObjectRelativeParticle(object,&origin,&velocity,&D_L02_001B1780,variant);
}

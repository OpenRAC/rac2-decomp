#include "include_asm.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
extern float D_L02_001B17B8 __attribute__((sda)),D_L02_001B17BC __attribute__((sda));
extern float D_L02_001B17AC __attribute__((sda)),D_L02_001B17B0 __attribute__((sda));
extern float D_L02_001B17B4 __attribute__((sda)),D_L02_001B17A0 __attribute__((sda));
extern float D_L02_001B17A4 __attribute__((sda)),D_L02_001B17A8 __attribute__((sda));
typedef struct { unsigned int colour, field04, field08; unsigned short lifetime, reserved; } EffectParameters16;
extern EffectParameters16 D_L02_001B1790 __attribute__((sda)),D_L02_001B1780 __attribute__((sda));
extern char D_L02_001BA500[];
extern void func_00282CF0(void *,void *,void *),func_00282F20(void *,void *,float),func_00282CC0(void *,void *,void *),func_002ACB48(float *,float);
extern float func_002A7878(float,float);
extern int func_002A77E0(int);
extern void *func_L00_0033C0D0(void *,void *,void *,void *,int);

/* The child consumes five GPR inputs and deliberately returns a pointer. */
void func_PAL_L02_00406D40(char *object) {
    Vector velocity,origin,direction;
    int variant;
    velocity.q=0;
    origin.q=*(Quad *)(object+0x10);
    origin.f[2]+=D_L02_001B17B8;
    func_00282CF0(&direction,D_L02_001BA500,&origin);
    direction.f[2]=0.0f;
    func_00282F20(&direction,&direction,D_L02_001B17BC);
    func_00282CC0(&origin,&origin,&direction);
    velocity.f[2]=func_002A7878(D_L02_001B17AC,D_L02_001B17B0)*0.020000001f;
    variant=func_002A77E0(2);
    func_L00_0033C0D0(object,&origin,&velocity,&D_L02_001B1790,variant);
    origin.q=*(Quad *)(object+0x10);
    origin.f[2]+=D_L02_001B17B4;
    func_002ACB48(origin.f,D_L02_001B17A0);
    velocity.f[2]=func_002A7878(D_L02_001B17A4,D_L02_001B17A8)*0.020000001f;
    variant=func_002A77E0(2);
    func_L00_0033C0D0(object,&origin,&velocity,&D_L02_001B1780,variant);
}

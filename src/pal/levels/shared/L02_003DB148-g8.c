#include "include_asm.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
extern int D_L02_001B03DC __attribute__((sda));
extern float D_L02_001B03D4 __attribute__((sda)),D_L02_001B03D8 __attribute__((sda));
extern float D_L02_001B03C8 __attribute__((sda)),D_L02_001B03CC __attribute__((sda)),D_L02_001B03D0 __attribute__((sda));
typedef struct { void *colours; void *sizes; void *lifetimes; int kind; int count; float acceleration; } EffectParameters24;
extern EffectParameters24 D_L02_001B03B0 __attribute__((sda));
extern char D_L02_001BA500[];
extern int func_002A77E0(int);
extern void func_00282C88(Quad *),func_00282CC0(void *,void *,void *),func_00282CF0(void *,void *,void *),func_00282F20(void *,void *,float),func_002ACB48(float *,float);
extern float func_002A7878(float,float);
extern void *func_L02_003449D8(void *,void *,void *,void *,int);

void func_PAL_L02_003DB148(char *object) {
    Vector velocity,origin,direction;
    float speed;
    int variant;
    if (func_002A77E0(D_L02_001B03DC)) return;
    velocity.q=0;
    func_00282C88(&origin.q);
    func_00282CC0(&origin,&origin,object+0x10);
    origin.f[3]=0.0f;
    origin.f[2]+=D_L02_001B03D4;
    func_00282CF0(&direction,D_L02_001BA500,&origin);
    direction.f[2]=0.0f;
    func_00282F20(&direction,&direction,D_L02_001B03D8);
    func_00282CC0(&origin,&origin,&direction);
    func_002ACB48(origin.f,D_L02_001B03C8);
    speed=func_002A7878(D_L02_001B03CC,D_L02_001B03D0);
    velocity.f[2]=speed*0.020000001f;
    variant=func_002A77E0(2);
    func_L02_003449D8(&origin,&velocity,&D_L02_001B03B0,(void *)variant,1);
}

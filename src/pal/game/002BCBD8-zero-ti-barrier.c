#include "include_asm.h"

typedef int Quad __attribute__((mode(TI)));
typedef struct {
    unsigned char b0, b1, b2, b3;
    int color;
    unsigned char seed, alpha;
    unsigned short size;
    float life;
    union { Quad q; float f[4]; } position;
    float payload[8];
} Particle;
extern Particle *func_002B9030(int);
extern int func_00283CF0(float);
extern int func_001163B0(void);
extern float func_00283CE0(int);
extern unsigned char *D_001F257C;

/* The effect-record initialiser of func_L00_0033E888, without the rotation argument. */
Particle *func_PAL_002BD790(float life,Quad *position,Quad *velocity,int color,int value,int size,int extra,int texture,int flags,int weight)
{
    Particle *p;
    if(!size) return 0;
    p=func_002B9030(0xF);
    if(p) {
        float *out;
        p->position.q=*position;
        p->position.f[3]=func_00283CE0(weight);
        p->color=color;
        p->alpha=func_00283CF0(4.0f)-96;
        if(flags!=-1) p->b3=flags; else p->b3=0x48;
        p->b1=0;
        p->life=life;
        p->seed=func_001163B0();
        if(texture==-1) p->b2=*D_001F257C; else p->b2=texture;
        out=p->payload;
        p->size=size;
        *(short *)((char*)out+0x18)=size;
        out[7]=life;
        *(int *)(out+4)=color;
        *(int *)(out+5)=value;
        *(short *)((char*)out+0x1a)=extra;
        *(Quad *)out=*velocity;
        out[3]=0.00584f;
    }
    return p;
}

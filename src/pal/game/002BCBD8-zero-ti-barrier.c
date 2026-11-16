#include "include_asm.h"
#include "names.h"

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
extern Particle *part_alloc(int);
extern int FloatToInt(float);
extern int func_001163B0(void);
extern float IntToFloat(int);
extern unsigned char *g_part_tex_spark;

/* The effect-record initialiser of func_L00_0033E888, without the rotation argument. */
/* Spawns a spark particle with a velocity, colour and size; PAL's version of the initialiser, without a rotation argument. */
Particle *part_spawn_spark_pal(float life,Quad *position,Quad *velocity,int color,int value,int size,int extra,int texture,int flags,int weight)
{
    Particle *p;
    if(!size) return 0;
    p=part_alloc(0xF);
    if(p) {
        float *out;
        p->position.q=*position;
        p->position.f[3]=IntToFloat(weight);
        p->color=color;
        p->alpha=FloatToInt(4.0f)-96;
        if(flags!=-1) p->b3=flags; else p->b3=0x48;
        p->b1=0;
        p->life=life;
        p->seed=func_001163B0();
        if(texture==-1) p->b2=*g_part_tex_spark; else p->b2=texture;
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

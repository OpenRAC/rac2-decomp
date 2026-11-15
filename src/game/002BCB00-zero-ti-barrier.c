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
extern unsigned char *D_001F257C;

/* The effect-record initialiser of func_L00_0033E888, without the rotation argument. */
/* Creates a spark particle at a point that flies off with the given velocity. */
Particle *part_spawn_spark(float life,Quad *position,Quad *velocity,int color,int endColor,int lifeFrames,int extra,int texture,int flags,int weight)
{
    Particle *particle;
    if(!lifeFrames) return 0;
    particle=part_alloc(0xF);
    if(particle) {
        float *motion;
        particle->position.q=*position;
        particle->position.f[3]=IntToFloat(weight);
        particle->color=color;
        particle->alpha=FloatToInt(4.0f)-96;
        if(flags!=-1) particle->b3=flags; else particle->b3=0x48;
        particle->b1=0;
        particle->life=life;
        particle->seed=func_001163B0();
        if(texture==-1) particle->b2=*D_001F257C; else particle->b2=texture;
        motion=particle->payload;
        particle->size=lifeFrames;
        *(short *)((char*)motion+0x18)=lifeFrames;
        motion[7]=life;
        *(int *)(motion+4)=color;
        *(int *)(motion+5)=endColor;
        *(short *)((char*)motion+0x1a)=extra;
        *(Quad *)motion=*velocity;
        motion[3]=0.004055556f;
    }
    return particle;
}

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
extern unsigned char *g_spinning_particle_bytes;

/* Spawns a spinning particle at position with the given velocity, colour and size. */
Particle *part_spawn_spinning_particle_pal(float life,float rotation,Quad *position,Quad *velocity,int color,int value,int size,int extra,int texture,int flags,int weight)
{
    Particle *particle;
    if(!size) return 0;
    particle=part_alloc(0x5b);
    if(particle) {
        float *out;
        particle->position.q=*position;
        particle->position.f[3]=IntToFloat(weight);
        particle->color=color;
        particle->alpha=FloatToInt(4.0f)-96;
        if(flags!=-1) particle->b3=flags; else particle->b3=0x48;
        particle->b1=0;
        particle->life=life;
        particle->seed=func_001163B0();
        if(texture==-1) particle->b2=*g_spinning_particle_bytes; else particle->b2=g_spinning_particle_bytes[texture];
        out=particle->payload;
        particle->size=size;
        *(short *)((char*)out+0x18)=size;
        out[7]=life;
        *(int *)(out+4)=color;
        *(int *)(out+5)=value;
        *(short *)((char*)out+0x1a)=extra;
        *(Quad *)out=*velocity;
        out[3]=rotation*0.00040000002f;
    }
    return particle;
}

#include "names.h"
/* func_L00_0033E888: initializes an allocated effect record and its payload. */
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

/* Creates a spinning particle with a position, speed, color, size and life. It does nothing if the size is zero. */
Particle *part_spawn_spinning_particle(float life,float rotation,Quad *position,Quad *velocity,int color,int value,int size,int extra,int texture,int flags,int weight)
{
    Particle *p;
    if(!size) return 0;
    p=part_alloc(0x5b);
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
        if(texture==-1) p->b2=*g_spinning_particle_bytes; else p->b2=g_spinning_particle_bytes[texture];
        out=p->payload;
        p->size=size;
        *(short *)((char*)out+0x18)=size;
        out[7]=life;
        *(int *)(out+4)=color;
        *(int *)(out+5)=value;
        *(short *)((char*)out+0x1a)=extra;
        *(Quad *)out=*velocity;
        out[3]=rotation*0.00027777778f;
    }
    return p;
}

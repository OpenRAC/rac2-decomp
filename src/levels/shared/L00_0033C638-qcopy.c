#include "names.h"
/* func_L00_0033C638: initializes an allocated effect record and its payload. */
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
extern int math_random_int_below(int);
extern int moby_get_private_value_0(unsigned char *);
extern unsigned char *D_L00_001FEA78;

/* Creates a particle with its start position, color, size, life and direction. It can also remember the object that owns it. */
Particle *part_spawn_owned_particle(float life,float secondLife,Quad *position,int size,int color,int mode,int flag,float *vector,int id)
{
    Particle *p=part_alloc(0x4e);
    if(p) {
        float *out=p->payload;
        p->position.q=*position;
        p->color=color;
        p->b3=0x48;
        p->alpha=FloatToInt(4.0f)+32;
        p->b1=0;
        p->b2=*D_L00_001FEA78;
        p->size=size;
        p->life=life*210000.0f;
        if(mode==0) p->seed=0;
        else if(mode==1) p->seed=32;
        else p->seed=math_random_int_below(255);
        out[0]=p->life;
        *(short *)((char*)out+8)=size;
        *((unsigned char*)out+10)=flag;
        out[1]=secondLife*210000.0f;
        *((unsigned char*)out+11)=color>>24;
        *(int *)(out+6)=id;
        out[7]=0;
        if(id) {
            char *owner=(char *)moby_get_private_value_0((unsigned char *)id);
            if(owner) out[7]=*(float *)(owner+0x10);
        }
        { float *dst=out+3; dst[0]=vector[0];dst[1]=vector[1];dst[2]=vector[2]; }
    }
    return p;
}

#include "include_asm.h"

#include "common.h"
extern int func_002A77E0(int);
extern int func_00283CF0(float);
extern unsigned char *func_PAL_002BE9A8(void *,float,float,float,int,void *,float,unsigned int,int);
struct SparkPayloadPrefix {
    unsigned char reserved00[4];
    unsigned int mode;
    unsigned char reserved08[2];
    unsigned char alpha;
    unsigned char lifetime;
};

void func_PAL_L12_0042EC00(unsigned char *object,int positive)
{
    float velocity[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    int rotation;
    unsigned char *first,*particle;
    velocity[0]=0.0f;
    velocity[2]=positive?0.5f:-0.5f;
    velocity[1]=0.0f;
    velocity[3]=1.0f;
    rotation=func_002A77E0(16);
    if(func_002A77E0(2))
        rotation=-rotation;
    qcopy(position,object+0x10);
    position[2]-=0.25f;
    first=func_PAL_002BE9A8(position,0.1f,1.0f,0.9f,rotation,velocity,420000.0f,0xDF204080u,0);
    if(first) {
        unsigned char *state;
        *(unsigned short *)(first+0xA)=8;
        state=first+0x20;
        first[9]=func_00283CF0(4.0f)+0x70;
        *(int *)(state+4)=2;
        state[0xA]=0xDF;
        state[0xB]=first[0xA];
    }
    {
        unsigned char *second=func_PAL_002BE9A8(position,0.1f,1.0f,0.9f,rotation,velocity,420000.0f,0xDF204080u,0);
        if(second) {
            unsigned char *state=second+0x20;
            /* The retail second allocation updates the first header. */
            *(unsigned short *)(first+0xA)=8;
            first[9]=func_00283CF0(4.0f)+0x70;
            *(int *)(state+4)=2;
            state[0xA]=0xDF;
            state[0xB]=first[0xA];
        }
    }
    particle=func_PAL_002BE9A8(position,0.05f,1.0f,0.97f,16,velocity,210000.0f,0xDFFFFFFFu,0);
    if(particle) {
        struct SparkPayloadPrefix *state=(struct SparkPayloadPrefix *)(particle+0x20);
        int brightness=func_00283CF0(4.0f);
        *(unsigned short *)(particle+0xA)=4;
        particle[9]=brightness+0x70;
        particle[8]=func_002A77E0(255);
        state->mode=2;
        state->alpha=0xDF;
        state->lifetime=first[0xA];
    }
}

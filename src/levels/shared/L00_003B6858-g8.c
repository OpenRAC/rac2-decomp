#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef struct { char *objects[2]; char pad08[8]; Quad positions[2]; Quad velocity[2]; char pad50[0x18]; int seed; } PairState;
extern Quad D_L00_001AFA70[2] SDATA(D_L00_001AFA70);
extern Quad D_L00_001AFA50[2] SDATA(D_L00_001AFA50);
extern float D_L00_001AFAA0[2] __attribute__((sda));
extern float D_L00_001AFA90[2] SDATA(D_L00_001AFA90);
extern int D_L00_001AFA98[2] SDATA(D_L00_001AFA98);
extern int math_random_int_below(int);
extern char *CreateMoby(int);
extern void moby_init_child_from_parent(char *,int);
extern void moby_set_light_color(char *,int);

int InitializePairedObjects(char *object)
{
    int i=0;
    Quad *source,*position;
    int *material;
    float *scale,*rate;

    PairState *state=*(PairState **)(object+0x68);
    char **slot;
    Quad *out,*velocity;
    slot=state->objects;
    velocity=state->velocity;
    state->seed=math_random_int_below(255);
    material=D_L00_001AFA98;
    scale=D_L00_001AFA90;
    rate=D_L00_001AFAA0;
    position=D_L00_001AFA50;
    source=D_L00_001AFA70;
    out=state->positions;
    do {
        *slot=CreateMoby(i?MOBY_CLASS_SHEEP:MOBY_CLASS_DARK_SHEEP);
        moby_init_child_from_parent(*slot,0);
        *(unsigned short *)(*slot+0x34)|=0x4100;
        (*slot)[0xbc]=i;
        *(Quad *)(*slot+0xf0)=*source;
        *out=*position;
        *velocity=0;
        ((float *)velocity)[1]=*rate*(1.0f/60.0f);
        *(float *)(*slot+0x2c)=*(float *)(*(char **)(*slot+0x24)+0x24)* *scale;
        moby_set_light_color(*slot,*material);
        slot++;rate++;position++;out++;source++;velocity++;scale++;material++;i++;
    }while(i<2);
    if(state->objects[0]) {
        if(state->objects[1]) return 1;
    }
    return 0;
}

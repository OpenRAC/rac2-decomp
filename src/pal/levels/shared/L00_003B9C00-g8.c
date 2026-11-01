#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef struct { char *objects[2]; char pad08[8]; Quad positions[2]; Quad velocity[2]; char pad50[0x18]; int seed; } PairState;
extern Quad D_L00_001AFA70[2] SDATA(D_L00_001AFA70);
extern Quad D_L00_001AFA50[2] SDATA(D_L00_001AFA50);
extern float D_L00_001AFAA0[2] __attribute__((sda));
extern float D_L00_001AFA90[2] SDATA(D_L00_001AFA90);
extern int D_L00_001AFA98[2] SDATA(D_L00_001AFA98);
extern int func_002A77E0(int);
extern char *func_0029EFD0(int);
extern void func_002B37E8(char *,int);
extern void func_002AEC18(char *,int);

int func_PAL_L00_003BA320(char *object)
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
    state->seed=func_002A77E0(255);
    material=D_L00_001AFA98;
    scale=D_L00_001AFA90;
    rate=D_L00_001AFAA0;
    position=D_L00_001AFA50;
    source=D_L00_001AFA70;
    out=state->positions;
    do {
        *slot=func_0029EFD0(i?0xe7d:0xeb0);
        func_002B37E8(*slot,0);
        *(unsigned short *)(*slot+0x34)|=0x4100;
        (*slot)[0xbc]=i;
        *(Quad *)(*slot+0xf0)=*source;
        *out=*position;
        *velocity=0;
        ((float *)velocity)[1]=*rate*(0.020000001f);
        *(float *)(*slot+0x2c)=*(float *)(*(char **)(*slot+0x24)+0x24)* *scale;
        func_002AEC18(*slot,*material);
        slot++;rate++;position++;out++;source++;velocity++;scale++;material++;i++;
    }while(i<2);
    if(state->objects[0]) {
        if(state->objects[1]) return 1;
    }
    return 0;
}

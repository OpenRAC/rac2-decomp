#include "common.h"
extern char *D_L03_001B2A1C;
typedef struct { char pad[0x30]; float pos[4]; char pad2[0x30]; float rot[4]; } Record;
extern Record *D_L03_001B2B0C;
extern int D_L03_001B0140 __attribute__((sda));
extern float D_L03_001B0144 __attribute__((sda)), D_L03_001B0148 __attribute__((sda));
typedef struct { char pad[0x3d4]; float f; char pad2[0x10]; char b0,b1; } AimState;
extern AimState D_L03_001B9840;
typedef struct { int index; int indices[3]; int handles[8]; int current; } SelectState;
extern int func_321988(void *, int);
extern void func_L03_003C7AA0(void *, void *);
extern void func_2EEF78(void *);
extern float func_2EF190(void *, void *);
extern float func_2EF670(float, float);
extern float func_2F0000(float, float);
/* Picks which camera anchor to use and outputs its position and a rotation that looks at the target. */
void func_L03_003C6E50(char *obj, float *pos, float *rot)
{
    float target[4];
    int i;
    SelectState *state = *(SelectState **)(obj+0x68);
    char *source = D_L03_001B2A1C + state->index * 0x100;

    if (state->current == -1 || !func_321988(source+0x10, state->handles[state->current])) {
        for(i=0;i<3;i++) {
            if(i == state->current) continue;
            if(state->handles[i] == -1) continue;
            if(func_321988(source+0x10, state->handles[i])) {
                state->current=i;
                break;
            }
        }
    }
    D_L03_001B0140 = state->current;
    { Record *base = D_L03_001B2B0C; int index = state->indices[state->current];
    qcopy(pos,base[index].pos);
    qcopy(rot,base[index].rot); }
    CopyMobyPositionAndHeight(source,target);
    func_2EEF78(rot);
    rot[1]=func_2F0000(-func_2EF670(func_2EF190(pos,target),target[2]-pos[2]),D_L03_001B0144*0.017453294f);
    rot[2]=func_2EF670(target[0]-pos[0],target[1]-pos[1]);
    D_L03_001B9840.f=D_L03_001B0148;
    D_L03_001B9840.b1=1;
    D_L03_001B9840.b0=0;
}

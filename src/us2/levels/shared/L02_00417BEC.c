#include "include_asm.h"
#include "common.h"

/* func_US2_L02_00417BEC, the USA v2.00 copy of func_L02_004164A8: the same C, with the released child's
   save records cleared. */

typedef struct { u8 *child; float speed,turn,height; } CaptureState;
typedef struct { u8 pad[0x464]; u8 active[0]; } SaveTable;
extern int func_00312B58(void *);
extern int func_002B3868(void *);
extern void func_002A7470(void *, int, int, int);
extern void func_002A7750(void *, int, int);
extern float func_00283B98(float,float);
extern SaveTable D_L02_0021E880, D_L02_0021F4F0;
extern u8 D_0019B4A8[];
extern int D_001A79F0 MACRO_ADDR;

/* Advance the captured child's rising and settling states. */
void func_US2_L02_00417BEC(u8 *object)
{
    CaptureState *state=*(CaptureState **)(object+0x68);
    if (state->child && func_00312B58(state->child)) {
        int save=D_001A79F0<<10;
        unsigned short index;
        D_L02_0021E880.active[*(short *)(state->child+0xB2)]=0;
        D_L02_0021F4F0.active[*(short *)(state->child+0xB2)]=0;
        index=*(unsigned short *)(state->child+0xB2);
        {
            u8 *entry=&D_0019B4A8[((short)index>>1)+save];
            unsigned flags=*entry;
            unsigned value=flags&0xF8;
            if (index&1) value=flags&0x8F;
            *entry=value;
        }
        state->child=0;
        state->speed=0;
    }
    switch (object[0x20]) {
    case 0:
        state->child=0;
        state->speed=0;
        func_002A7750(object,1,-1);
        if(object[0x43]) func_002A7470(object,0,0,7);
        return;
    case 2:
        if (func_002B3868(object)) {
            if(object[0x43]!=1) func_002A7470(object,1,0,7);
            *(float *)(object+0x48)=1;
        }
        if (!state->child) {
            func_002A7750(object,4,-1);
            return;
        }
        *(float *)(state->child+0x18)+=state->speed;
        *(float *)(state->child+0xF8)=func_00283B98(*(float *)(state->child+0xF8),state->turn);
        if (!(object[0x60]&2)) return;
        func_002A7750(object,3,-1);
        return;
    case 3:
        if (func_002B3868(object)) *(float *)(object+0x48)=0;
        if (!state->child) {
            func_002A7750(object,4,-1);
            return;
        }
        {
            u8 *data=*(u8 **)(state->child+0x68);
            *(float *)(state->child+0x18)+=state->speed;
            *(float *)(state->child+0xF8)=func_00283B98(*(float *)(state->child+0xF8),state->turn);
            *(int *)(data+0xAC)=2;
            if (!(*(float *)(state->child+0x18)>*(float *)(object+0x18)+0.2f)) return;
            *(int *)(data+0xAC)=8;
        }
        func_002A7750(object,4,-1);
        return;
    case 4:
        if (func_002B3868(object)) {
            if(object[0x43]!=2) func_002A7470(object,2,0,7);
            *(float *)(object+0x48)=1;
        }
        if (!(object[0x60]&2)) return;
        if (state->child) state->height=*(float *)(state->child+0x18);
        func_002A7750(object,1,-1);
        if(object[0x43]) func_002A7470(object,0,0,7);
        return;
    case 1:
        if (!state->child) return;
        if (*(float *)(state->child+0x18)==state->height)
            *(int *)(*(u8 **)(state->child+0x68)+0xAC)=2;
        else
            state->height=*(float *)(state->child+0x18);
        return;
    }
}

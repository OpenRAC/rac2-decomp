#include "include_asm.h"
#include "names.h"

/* func_PAL_L02_0041B204, the PAL copy of func_L02_004164A8: the same C, where the func_002A7470
   argument 7 becomes 6 and a child taken by func_00312B58 also has its flag bytes and its nibble
   in D_0019B4A8 cleared. */

typedef unsigned char u8;

typedef struct { u8 *child; float speed,turn,height; } CaptureState;
extern int moby_is_state_six(void *);
extern int flag_set_first_pending(void *);
extern void anim_start_blended(void *, int, int, int);
extern void moby_set_state(void *, int, int);
extern float FastAddRotations(float,float);

extern struct { char pad[0x464]; u8 flags[0]; } D_L02_0021E880;
extern struct { char pad[0x464]; u8 flags[0]; } D_L02_0021F4F0;
extern int g_current_map_index __attribute__((sda));
extern u8 D_0019B4A8[];

void func_PAL_L02_0041B204(u8 *object)
{
    CaptureState *state=*(CaptureState **)(object+0x68);
    if (state->child && moby_is_state_six(state->child)) {
        unsigned short id;
        u8 *bits;
        D_L02_0021E880.flags[*(short *)(state->child+0xB2)]=0;
        D_L02_0021F4F0.flags[*(short *)(state->child+0xB2)]=0;
        id=*(unsigned short *)(state->child+0xB2);
        bits=&D_0019B4A8[((short)id>>1)+(g_current_map_index<<10)];
        {
            u8 value=*bits;
            u8 low=value&0xF8;
            u8 high=value&0x8F;
            value=!(id&1)?low:high;
            *bits=value;
        }
        state->child=0;
        state->speed=0;
    }
    switch (object[0x20]) {
    case 0:
        state->child=0;
        state->speed=0;
        moby_set_state(object,1,-1);
        if(object[0x43]) anim_start_blended(object,0,0,6);
        return;
    case 2:
        if (flag_set_first_pending(object)) {
            if(object[0x43]!=1) anim_start_blended(object,1,0,6);
            *(float *)(object+0x48)=1;
        }
        if (!state->child) {
            moby_set_state(object,4,-1);
            return;
        }
        *(float *)(state->child+0x18)+=state->speed;
        *(float *)(state->child+0xF8)=FastAddRotations(*(float *)(state->child+0xF8),state->turn);
        if (!(object[0x60]&2)) return;
        moby_set_state(object,3,-1);
        return;
    case 3:
        if (flag_set_first_pending(object)) *(float *)(object+0x48)=0;
        if (!state->child) {
            moby_set_state(object,4,-1);
            return;
        }
        {
            u8 *data=*(u8 **)(state->child+0x68);
            *(float *)(state->child+0x18)+=state->speed;
            *(float *)(state->child+0xF8)=FastAddRotations(*(float *)(state->child+0xF8),state->turn);
            *(int *)(data+0xAC)=2;
            if (!(*(float *)(state->child+0x18)>*(float *)(object+0x18)+0.2f)) return;
            *(int *)(data+0xAC)=8;
        }
        moby_set_state(object,4,-1);
        return;
    case 4:
        if (flag_set_first_pending(object)) {
            if(object[0x43]!=2) anim_start_blended(object,2,0,6);
            *(float *)(object+0x48)=1;
        }
        if (!(object[0x60]&2)) return;
        if (state->child) state->height=*(float *)(state->child+0x18);
        moby_set_state(object,1,-1);
        if(object[0x43]) anim_start_blended(object,0,0,6);
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

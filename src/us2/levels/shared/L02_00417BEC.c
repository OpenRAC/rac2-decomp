#include "include_asm.h"
#include "common.h"

/* func_US2_L02_00417BEC, the USA v2.00 copy of func_L02_004164A8: the same C, with the released child's
   save records cleared. */

typedef struct { u8 *child; float speed,turn,height; } CaptureState;
typedef struct { u8 pad[0x464]; u8 active[0]; } SaveTable;
extern int moby_is_state_six(void *);
extern int flag_set_first_pending(void *);
extern void anim_start_blended(void *, int, int, int);
extern void moby_set_state(void *, int, int);
extern float FastAddRotations(float,float);
extern SaveTable g_level_active_flags, g_cell_flags;
extern u8 g_moby_nibble_table[];
extern int g_current_map_index MACRO_ADDR;

/* Advance the captured child's rising and settling states. */
void func_US2_L02_00417BEC(u8 *object)
{
    CaptureState *state=*(CaptureState **)(object+0x68);
    if (state->child && moby_is_state_six(state->child)) {
        int save=g_current_map_index<<10;
        unsigned short index;
        g_level_active_flags.active[*(short *)(state->child+0xB2)]=0;
        g_cell_flags.active[*(short *)(state->child+0xB2)]=0;
        index=*(unsigned short *)(state->child+0xB2);
        {
            u8 *entry=&g_moby_nibble_table[((short)index>>1)+save];
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
        moby_set_state(object,1,-1);
        if(object[0x43]) anim_start_blended(object,0,0,7);
        return;
    case 2:
        if (flag_set_first_pending(object)) {
            if(object[0x43]!=1) anim_start_blended(object,1,0,7);
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
            if(object[0x43]!=2) anim_start_blended(object,2,0,7);
            *(float *)(object+0x48)=1;
        }
        if (!(object[0x60]&2)) return;
        if (state->child) state->height=*(float *)(state->child+0x18);
        moby_set_state(object,1,-1);
        if(object[0x43]) anim_start_blended(object,0,0,7);
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

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
void capture_lift_update_us2(u8 *moby)
{
    CaptureState *capture=*(CaptureState **)(moby+0x68);
    if (capture->child && moby_is_state_six(capture->child)) {
        int map_offset=g_current_map_index<<10;
        unsigned short save_index;
        g_level_active_flags.active[*(short *)(capture->child+0xB2)]=0;
        g_cell_flags.active[*(short *)(capture->child+0xB2)]=0;
        save_index=*(unsigned short *)(capture->child+0xB2);
        {
            u8 *entry=&g_moby_nibble_table[((short)save_index>>1)+map_offset];
            unsigned flags=*entry;
            unsigned value=flags&0xF8;
            if (save_index&1) value=flags&0x8F;
            *entry=value;
        }
        capture->child=0;
        capture->speed=0;
    }
    switch (moby[0x20]) {
    case 0:
        capture->child=0;
        capture->speed=0;
        moby_set_state(moby,1,-1);
        if(moby[0x43]) anim_start_blended(moby,0,0,7);
        return;
    case 2:
        if (flag_set_first_pending(moby)) {
            if(moby[0x43]!=1) anim_start_blended(moby,1,0,7);
            *(float *)(moby+0x48)=1;
        }
        if (!capture->child) {
            moby_set_state(moby,4,-1);
            return;
        }
        *(float *)(capture->child+0x18)+=capture->speed;
        *(float *)(capture->child+0xF8)=FastAddRotations(*(float *)(capture->child+0xF8),capture->turn);
        if (!(moby[0x60]&2)) return;
        moby_set_state(moby,3,-1);
        return;
    case 3:
        if (flag_set_first_pending(moby)) *(float *)(moby+0x48)=0;
        if (!capture->child) {
            moby_set_state(moby,4,-1);
            return;
        }
        {
            u8 *child_vars=*(u8 **)(capture->child+0x68);
            *(float *)(capture->child+0x18)+=capture->speed;
            *(float *)(capture->child+0xF8)=FastAddRotations(*(float *)(capture->child+0xF8),capture->turn);
            *(int *)(child_vars+0xAC)=2;
            if (!(*(float *)(capture->child+0x18)>*(float *)(moby+0x18)+0.2f)) return;
            *(int *)(child_vars+0xAC)=8;
        }
        moby_set_state(moby,4,-1);
        return;
    case 4:
        if (flag_set_first_pending(moby)) {
            if(moby[0x43]!=2) anim_start_blended(moby,2,0,7);
            *(float *)(moby+0x48)=1;
        }
        if (!(moby[0x60]&2)) return;
        if (capture->child) capture->height=*(float *)(capture->child+0x18);
        moby_set_state(moby,1,-1);
        if(moby[0x43]) anim_start_blended(moby,0,0,7);
        return;
    case 1:
        if (!capture->child) return;
        if (*(float *)(capture->child+0x18)==capture->height)
            *(int *)(*(u8 **)(capture->child+0x68)+0xAC)=2;
        else
            capture->height=*(float *)(capture->child+0x18);
        return;
    }
}

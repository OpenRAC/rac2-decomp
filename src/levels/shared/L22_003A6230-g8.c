#include "common.h"
typedef struct { u8 pad[0x1874]; int clock; u8 pad2[0x229c-0x1878]; int mode; } Resident;
extern Resident g_hero_state;
typedef struct { u8 pad[0x6c]; short time; u8 pad2[4]; short mode; } Animation;
extern Animation D_001A63A8_4;
extern int ref_L22_003A6230_00 __attribute__((sda));
extern int D_L22_001B1C48;
extern void anim_start_free_slot_in_range(void *,int,int), anim_start_slot(void *,int);
extern int math_fast_float_d(void *),math_random_int_below(int);
extern float vec_fast_helper_c(void *,void *);
extern void snd_resume_music_stream(void);
/* Chooses which animation the object should play next, based on its health, the player's state and a few level flags. */
void anim_choose_next(u8 *obj) {
    u8 *ctl = *(u8 **)(obj + 0x68);
    float healthRatio = *(float *)(ctl + 0x20) / *(short *)(ctl + 0x24);
    float seconds = g_hero_state.clock * 0.00083333335f;
    if (ref_L22_003A6230_00) return;
    if (D_L22_001B1C48 && !(*(int *)(ctl + 0x4E0) & 0x1000000)) {
        *(int *)(ctl + 0x4E0) |= 0x1000000;
        anim_start_free_slot_in_range(obj,0,2);
    }
    if (*(int *)(ctl + 0x344) && !(*(int *)(ctl + 0x4E0) & 0x800000))
        anim_start_slot(obj,23);
    if (g_hero_state.clock == 0)
        anim_start_free_slot_in_range(obj,20,22);
    if (healthRatio < 0.25f && !(*(int *)(ctl + 0x4E0) & 0x80))
        anim_start_slot(obj,7);
    if (healthRatio > 0.02f && seconds > 0.04f) {
        if (math_fast_float_d(ctl + 0x4E4) && obj[0x31] &&
            vec_fast_helper_c(obj + 0x10, (u8 *)&g_hero_state + 0x80) < 1600.0f)
            anim_start_free_slot_in_range(obj,3,6);
        if (g_hero_state.mode == 7 &&
            !*(int *)((u8 *)&g_hero_state + 0x1B8) && math_random_int_below(2) == 0)
            anim_start_free_slot_in_range(obj,8,12);
    }
    if (D_001A63A8_4.mode == 3 && D_001A63A8_4.time < 6000)
        snd_resume_music_stream();
}

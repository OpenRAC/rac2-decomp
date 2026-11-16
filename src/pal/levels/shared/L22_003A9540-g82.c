#include "include_asm.h"

#include "common.h"
typedef struct { u8 pad[0x1874]; int clock; u8 pad2[0x229c-0x1878]; int mode; } Resident;
extern Resident g_hero_state;
typedef struct { u8 pad[0x6c]; short time; u8 pad2[4]; short mode; } Animation;
extern Animation D_001A63A8_4;
extern int ref_L22_003A6230_00 __attribute__((sda));
extern int g_frame_l22_counter;
extern void anim_start_free_slot_in_range_pal(void *,int,int), anim_start_slot_pal(void *,int);
extern int math_fast_float_d(void *),math_random_int_below(int);
extern float vec_fast_helper_c(void *,void *);
extern s32 snd_resume_music_stream(void);

/* Chooses which animation the object should play next, based on its health, the player's state and a few level flags. (PAL: 50 Hz timings) */
void anim_choose_next_pal(u8 *obj) {
    u8 *vars = *(u8 **)(obj + 0x68);
    float ratio = *(float *)(vars + 0x20) / *(short *)(vars + 0x24);
    float time = g_hero_state.clock * 0.00083333335f;
    if (ref_L22_003A6230_00) return;
    if (g_frame_l22_counter && !(*(int *)(vars + 0x4E0) & 0x1000000)) {
        *(int *)(vars + 0x4E0) |= 0x1000000;
        anim_start_free_slot_in_range_pal(obj,0,2);
    }
    if (*(int *)(vars + 0x344) && !(*(int *)(vars + 0x4E0) & 0x800000))
        anim_start_slot_pal(obj,23);
    if (g_hero_state.clock == 0)
        anim_start_free_slot_in_range_pal(obj,20,22);
    if (ratio < 0.25f && !(*(int *)(vars + 0x4E0) & 0x80))
        anim_start_slot_pal(obj,7);
    if (ratio > 0.02f && time > 0.04f) {
        if (math_fast_float_d(vars + 0x4E4) && obj[0x31] &&
            vec_fast_helper_c(obj + 0x10, (u8 *)&g_hero_state + 0x80) < 1600.0f)
            anim_start_free_slot_in_range_pal(obj,3,6);
        if (g_hero_state.mode == 7 &&
            !*(int *)((u8 *)&g_hero_state + 0x1B8) && math_random_int_below(2) == 0)
            anim_start_free_slot_in_range_pal(obj,8,12);
    }
    if (D_001A63A8_4.mode == 3 && D_001A63A8_4.time < 6000)
        snd_resume_music_stream();
}

#include "include_asm.h"



#include "common.h"
extern float FastAddRotations(float, float);
extern int g_color_effect_freed_flag;
extern s32 snd_is_voice_playing_for_owner(void *, s32);
extern s32 PlayMobySound(s32, s32, void *);
extern void *part_find_owned_effect_slot(void *, s32, s32);
extern float moby_update_aim_target_strength_pal(void *, void *);
extern void func_PAL_002AC290(void *, void *);
extern void func_PAL_002AC3C0(void *, void *);
extern void moby_set_state(void *, int, int);
extern u8 *part_spawn_ground_effect(void *, int, float, float, unsigned int, int, int, void *, int, float);
extern int snd_is_voice_playing_for_owner(void *,int),PlayMobySound(int,int,void *);
extern int g_color_effect_freed_flag;
extern float FastAddRotations(float, float);
extern s32 snd_is_voice_playing_for_owner(void *, s32);
extern s32 PlayMobySound(s32, s32, void *);
extern void *part_find_owned_effect_slot(void *, s32, s32);
extern float moby_update_aim_target_strength_pal(void *, void *);
extern void func_PAL_002AC290(void *, void *);
extern void func_PAL_002AC3C0(void *, void *);

void func_PAL_L18_0043F330(u8 *obj) {
    u8 *state;
    u8 *p;
    float f;

    if (g_color_effect_freed_flag != 0) return;
    state = *(u8 **)(obj + 0x68);
    switch (*(u8 *)(obj + 0x20)) {
    case 0:
        *(short *)(state + 0x24) = 0x12;
        *(float *)(state + 0x20) = 18.0f;
        moby_set_state(obj, 1, -1);
        return;
    case 1:
        if (snd_is_voice_playing_for_owner(obj, *(s32 *)(state + 0x68)) == 0) {
            *(s32 *)(state + 0x68) = PlayMobySound(0, 4, obj);
        }
        p = state + 0x50;
        *(float *)(obj + 0xF8) = FastAddRotations(*(float *)(obj + 0xF8),
                                               *(float *)(state + 0x64) * 0.0003490659f);
        f = moby_update_aim_target_strength_pal(obj, part_find_owned_effect_slot(obj, 0x230000, 0));
        if (f > 0.0f) {
            *(u8 *)(state + 0x57) = 0xFF;
            *(u8 *)(state + 0x58) = 0x40;
            *(u8 *)(state + 0x59) = 0;
            func_PAL_002AC290(obj, p);
            *(float *)(state + 0x20) = *(float *)(state + 0x20) - f;
        }
        func_PAL_002AC3C0(obj, p);
        *(u8 *)(obj + 0xA8) = 0xFF;
        return;
    }
}





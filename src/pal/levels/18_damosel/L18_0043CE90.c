#include "include_asm.h"



#include "common.h"
extern float FastAddRotations(float, float);
extern int g_color_effect_freed_flag;
extern s32 snd_is_voice_playing_for_owner(void *, s32);
extern s32 PlayMobySound(s32, s32, void *);
extern void *part_find_owned_effect_slot(void *, s32, s32);
extern float moby_update_aim_target_strength_pal(void *, void *);
extern void gfx_start_color_fade_pal(void *, void *);
extern void gfx_update_color_fade_pal(void *, void *);
extern void moby_set_state(void *, int, int);
extern u8 *part_spawn_ground_effect(void *, int, float, float, unsigned int, int, int, void *, int, float);
extern int snd_is_voice_playing_for_owner(void *,int),PlayMobySound(int,int,void *);
extern int g_color_effect_freed_flag;
extern float FastAddRotations(float, float);
extern s32 snd_is_voice_playing_for_owner(void *, s32);
extern s32 PlayMobySound(s32, s32, void *);
extern void *part_find_owned_effect_slot(void *, s32, s32);
extern float moby_update_aim_target_strength_pal(void *, void *);
extern void gfx_start_color_fade_pal(void *, void *);
extern void gfx_update_color_fade_pal(void *, void *);

/* Spinning target: plays its hum, turns, takes damage from hits with a flash and spins on until it is destroyed (PAL: 50 Hz speeds). */
void spinning_target_update_pal(u8 *obj) {
    u8 *state;
    u8 *hit_flash;
    float damage;

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
        hit_flash = state + 0x50;
        *(float *)(obj + 0xF8) = FastAddRotations(*(float *)(obj + 0xF8),
                                               *(float *)(state + 0x64) * 0.0003490659f);
        damage = moby_update_aim_target_strength_pal(obj, part_find_owned_effect_slot(obj, 0x230000, 0));
        if (damage > 0.0f) {
            *(u8 *)(state + 0x57) = 0xFF;
            *(u8 *)(state + 0x58) = 0x40;
            *(u8 *)(state + 0x59) = 0;
            gfx_start_color_fade_pal(obj, hit_flash);
            *(float *)(state + 0x20) = *(float *)(state + 0x20) - damage;
        }
        gfx_update_color_fade_pal(obj, hit_flash);
        *(u8 *)(obj + 0xA8) = 0xFF;
        return;
    }
}





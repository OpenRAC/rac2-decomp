#include "common.h"

typedef int EffectQuad __attribute__((mode(TI)));
extern void route_set_node_enabled_flag(u32, u8 *, s32);
extern void effect_init_moby_state(void *);
extern void func_L03_0038B408(void *);
extern void moby_set_state(u8 *, s32, s32);
extern int flag_set_first_pending(u8 *);
extern int math_fast_float_d(void *);
extern void math_refresh_random_vector_table(void);
extern void rope_update_strand_points(u8 *);
typedef void (*EffectDrawCallback)(void *);
extern void gfx_add_draw_callback_third(EffectDrawCallback, void *);

extern void ref_L03_0038A6D8_00(void *);
extern int flag_is_third_pending_set(u8 *);
extern void FastVecAdd(void *, void *, void *);
extern u8 *SpawnExplosion(void *,int,int,int,int,int,int,int,float,float,int,int,int,void *);
extern unsigned short g_timed_effect_id;
extern unsigned char g_sound_state[];
/* Only the accessed prefix is described. Indexing still uses the measured
 * 0x70-byte stride, not sizeof this partial view. */
typedef struct {
    u8 reserved00[0x74];
    u8 active;
    u8 reserved75[0x13];
    u8 *owner;
} SoundSlotPrefix;
extern void snd_stop_voice(int);
extern int PlayMobySound(int, int, char *);
extern void moby_mark_spawned(void *);

/* Updates a moby (class 2832) that cycles through three timed states, draws its effect, and blows up with a sound when destroyed. */
void timed_state_effect_update(unsigned char *object) {
    unsigned char *state = *(unsigned char **)(object + 0x68);
    union { EffectQuad quad; float values[4]; } position;
    int handle;
    switch (object[0x20]) {
    case 0:
        qcopy(state, object + 0x10);
        if (*(int *)(state + 0x10) != -1 && *(int *)(state + 0x14))
            route_set_node_enabled_flag(*(int *)(state + 0x10), object + 0x10, 0);
        effect_init_moby_state(object);
        if ((*(unsigned long long *)(state + 0x38) & 0x1100000000ULL) == 0x1100000000ULL)
            func_L03_0038B408(object);
        moby_set_state(object, 1, -1);
        break;
    case 1:
        if (flag_set_first_pending(object))
            qcopy(object + 0x10, state);
        if (math_fast_float_d(state + 0x24)) {
            *(int *)(state + 0x24) = *(int *)(state + 0x18);
            moby_set_state(object, 2, -1);
        }
        break;
    case 2:
        if (math_fast_float_d(state + 0x24)) {
            *(int *)(state + 0x24) = *(int *)(state + 0x1C);
            moby_set_state(object, 3, -1);
        }
        break;
    case 3:
        if (math_fast_float_d(state + 0x24)) {
            *(int *)(state + 0x24) = *(int *)(state + 0x20);
            moby_set_state(object, 1, -1);
        }
        break;
    }
    if (!(*(int *)(state + 0x3C) & 0x20)) {
        if (!(*(int *)(state + 0x3C) & 0x40))
            math_refresh_random_vector_table();
        rope_update_strand_points(object);
        gfx_add_draw_callback_third(ref_L03_0038A6D8_00, object);
    }
    if (flag_is_third_pending_set(object)) {
        position.quad = 0;
        position.values[2] = 1.0f;
        FastVecAdd(&position, &position, object + 0x10);
        SpawnExplosion(&position,0,0,0,0,0x14,0x2D,1,1.0f,20.0f,1,0,0,0);
        if (*(int *)(state + 0x10) != -1 && *(int *)(state + 0x14))
            route_set_node_enabled_flag(*(int *)(state + 0x10), object + 0x10, 1);
        g_timed_effect_id = 0xFFFF;
        handle = *(int *)(state + 0xD8);
        if (handle != -1) {
            if (((SoundSlotPrefix *)(g_sound_state + handle * 0x70))->owner == object && ((SoundSlotPrefix *)(g_sound_state + handle * 0x70))->active)
                snd_stop_voice(handle);
        }
        *(int *)(state + 0xD8) = -1;
        PlayMobySound(1, 0, (char *)object);
        moby_mark_spawned(object);
    } else {
        if (((SoundSlotPrefix *)(g_sound_state + *(int *)(state + 0xD8) * 0x70))->owner != object || !((SoundSlotPrefix *)(g_sound_state + *(int *)(state + 0xD8) * 0x70))->active)
            *(int *)(state + 0xD8) = PlayMobySound(0, 4, (char *)object);
    }
}

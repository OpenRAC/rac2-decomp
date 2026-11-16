#include "common.h"

typedef int Vector128 __attribute__((mode(TI)));

extern u8 *g_moby_l11_table;
extern u8 g_sound_state[];
extern Vector128 g_identity_l11_matrix __attribute__((sda));
extern s32 g_pulsing_platform_linked_counter __attribute__((sda));
extern f32 FastAddRotations(f32, f32);
extern f32 math_fast_sin_or_cos_a(f32);
extern void vec_scale_to_length(void *, void *, f32);
extern void FastVecAdd(void *, void *, void *);
extern void mat_combine_and_store(void *, void *, void *, void *);
extern s32 PlayMobySound(s32, s32, u8 *);
extern void snd_stop_voice(s32);

/* Waits for its trigger object to become active, then bobs the object out and back in a smooth wave with a sound, and repeats. */
void pulsing_platform_linked_update(u8 *moby_arg) {
    f32 offset[4] __attribute__((aligned(16)));
    u8 *moby_table = g_moby_l11_table;
    u8 *entity = moby_arg;
    u8 *state = *(u8 **)(entity + 0x68);
    u8 *target = moby_table + *(s32 *)(state + 0x68) * 256;
    switch (*(u8 *)(entity + 0x20)) {
    case 0:
        *(u32 *)(state + 0x5C) |= 4;
        *(u8 *)(entity + 0x20) = 1;
        *(f32 *)(state + 0x6C) = 3.1415927410125732f;
        *(s32 *)(state + 0x70) = 0;
        g_pulsing_platform_linked_counter = 0;
        qcopy(state + 0x80, entity + 0x10);
        /* fall through */
    case 1: {
        u8 *sound_slot;
        if (*(s32 *)(state + 0x60) && *(u8 *)(target + 0x20) == 2) {
            sound_slot = (u8 *)(*(s32 *)(state + 0x74) * 0x70 + (s32)g_sound_state);
            if (*(u8 **)(sound_slot + 0x88) == entity) {
                if (!*(u8 *)(sound_slot + 0x74))
                    *(s32 *)(state + 0x74) = PlayMobySound(0, 4, entity);
            } else {
                *(s32 *)(state + 0x74) = PlayMobySound(0, 4, entity);
            }
            *(u8 *)(entity + 0x20) = 2;
            *(f32 *)(state + 0x6C) = 3.1415927410125732f;
            *(s32 *)(state + 0x70) = 0;
        }
        break;
    }
    case 2: {
        u8 *sound_slot;
        *(f32 *)(state + 0x70) += 0.05235988646745682f;
        *(f32 *)(state + 0x6C) = FastAddRotations(*(f32 *)(state + 0x6C), 0.05235988646745682f);
        if (*(f32 *)(state + 0x70) >= 3.1415927410125732f) {
            if (*(s32 *)(state + 0x74) != -1) {
                sound_slot = (u8 *)(*(s32 *)(state + 0x74) * 0x70 + (s32)g_sound_state);
                if (*(u8 **)(sound_slot + 0x88) == entity && *(u8 *)(sound_slot + 0x74))
                    snd_stop_voice(*(s32 *)(state + 0x74));
            }
            *(s32 *)(state + 0x74) = -1;
            *(u8 *)(entity + 0x20) = 3;
        } else {
            vec_scale_to_length(offset, entity + 0xD0, -(math_fast_sin_or_cos_a(*(f32 *)(state + 0x6C)) + 1.0f) * 4.0f);
            FastVecAdd(entity + 0x10, offset, state + 0x80);
        }
        break;
    }
    case 3: {
        u8 *sound_slot;
        if (*(u8 *)(target + 0x20) != 2) {
            sound_slot = (u8 *)(*(s32 *)(state + 0x74) * 0x70 + (s32)g_sound_state);
            if (*(u8 **)(sound_slot + 0x88) == entity) {
                if (!*(u8 *)(sound_slot + 0x74))
                    *(s32 *)(state + 0x74) = PlayMobySound(0, 4, entity);
            } else {
                *(s32 *)(state + 0x74) = PlayMobySound(0, 4, entity);
            }
            *(u8 *)(entity + 0x20) = 4;
        }
        break;
    }
    case 4: {
        u8 *sound_slot;
        *(f32 *)(state + 0x70) += 0.05235988646745682f;
        *(f32 *)(state + 0x6C) = FastAddRotations(*(f32 *)(state + 0x6C), 0.05235988646745682f);
        if (*(f32 *)(state + 0x70) >= 6.2831854820251465f) {
            if (*(s32 *)(state + 0x74) != -1) {
                sound_slot = (u8 *)(*(s32 *)(state + 0x74) * 0x70 + (s32)g_sound_state);
                if (*(u8 **)(sound_slot + 0x88) == entity && *(u8 *)(sound_slot + 0x74))
                    snd_stop_voice(*(s32 *)(state + 0x74));
            }
            *(s32 *)(state + 0x74) = -1;
            *(u8 *)(entity + 0x20) = 1;
            *(f32 *)(state + 0x6C) = 3.1415927410125732f;
            *(s32 *)(state + 0x70) = 0;
            qcopy(entity + 0x10, state + 0x80);
        } else {
            vec_scale_to_length(offset, entity + 0xD0, -(math_fast_sin_or_cos_a(*(f32 *)(state + 0x6C)) + 1.0f) * 4.0f);
            FastVecAdd(entity + 0x10, offset, state + 0x80);
        }
        break;
    }
    }
    mat_combine_and_store(state + 0x20, &g_identity_l11_matrix, entity + 0xF0, entity + 0xF0);
}

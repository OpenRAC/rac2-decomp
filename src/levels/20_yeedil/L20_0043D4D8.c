#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
typedef struct PoolRecord64 PoolRecord64;
extern Vector g_hero_position;
extern unsigned char g_sound_state[];
extern void moby_set_state(unsigned char *, unsigned char, int);
extern unsigned char *CreateMoby(int);
extern void moby_init_child_from_parent(void *, void *);
extern int flag_set_first_pending(unsigned char *);
extern int math_fast_float_d(int *);
extern float FastAddRotations(float, float);
extern int PlayMobySound(int, int, char *);
extern void snd_stop_voice(int);
extern int hero_is_current_selected_id(int);
extern PoolRecord64 *cam_alloc_override_slot(int);
extern void cam_end_override(unsigned char *);
extern void object_fill_settings_block(char *);
extern void FastVecSub(void *, const void *, const void *);
extern void mat_combine_and_store(void *, const void *, const void *, const void *);
extern void glow_flicker_update(void *, float *, int);
extern void moby_mark_spawned(void *);
extern void FastVecScale(void *, const void *, float);
extern void FastVecAdd(void *, const void *, const void *);
extern void func_002A0F48(void *);
extern Vector g_camera_l20_position;

/* Updates moby class 4464: a rotating object that turns for a set time, plays a sound while turning, and keeps a copy of itself and any riders moving with it. */
void rotating_object_update(unsigned char *moby) {
    Vector oldPosition, oldRotation, delta, offset;
    unsigned char *state = *(unsigned char **)(moby + 0x68);
    unsigned char *child;
    unsigned char *slot;
    int index;
    oldPosition.q = *(Quadword *)(moby + 0x10);
    oldRotation.q = *(Quadword *)(moby + 0xF0);
    switch (moby[0x20]) {
    case 0: {
        float speed = *(float *)(state + 0x74) * 0.017453294f;
        float range = 6.2831854820251465f;
        float one = 1.0f;
        unsigned int saved_value;
        *(int *)(state + 0x5C) |= 1;
        *(float *)(state + 0x70) = range;
        *(float *)(state + 0x74) = speed;
        saved_value = moby[0xBC];
        *(int *)(state + 0x60) = 0;
        *(int *)(state + 0x68) = 0;
        *(int *)(state + 0x80) = 0;
        *(unsigned int *)(state + 0x7C) = saved_value;
        *(float *)(state + 0x64) = one;
        *(float *)(state + 0x6C) = one;
        moby_set_state(moby, 1, -1);
        break;
    }
    case 1:
        if ((unsigned)moby[0xBC] != *(unsigned int *)(state + 0x7C)) {
            if (!*(unsigned char **)(state + 0x88)) {
                if (!(*(unsigned char **)(state + 0x88) = CreateMoby(*(short *)(moby + 0xAA))))
                    goto clone_failed;
            }
            {
                moby_init_child_from_parent(*(unsigned char **)(state + 0x88), 0);
                *(unsigned short *)(*(unsigned char **)(state + 0x88) + 0x34) |= 2;
                *(int *)(*(unsigned char **)(state + 0x88) + 0x98) = 0;
                (*(unsigned char **)(state + 0x88))[0x23] = 0;
            }
clone_failed:
            {
                float sign = -1.0f;
                if (g_hero_position.f[1] <= *(float *)(moby + 0x14)) sign = 1.0f;
                *(float *)(state + 0x64) = sign;
            }
            moby_set_state(moby, 2, -1);
        }
        break;
    case 2:
        if (flag_set_first_pending(moby)) *(int *)(state + 0x78) = (int)(*(float *)(state + 0x70) / *(float *)(state + 0x74));
        if (!math_fast_float_d((int *)(state + 0x78))) {
            *(float *)(moby + 0xF8) = FastAddRotations(*(float *)(moby + 0xF8), *(float *)(state + 0x74));
            slot = *(int *)(state + 0x90) * 0x70 + g_sound_state;
            if (*(unsigned char **)(slot + 0x88) != moby || !slot[0x74])
                *(int *)(state + 0x90) = PlayMobySound(1, 4, (char *)moby);
        } else {
            moby[0xBC] = *(unsigned char *)(state + 0x7C);
            moby_set_state(moby, 1, -1);
            index = *(int *)(state + 0x90);
            if (index != -1) {
                unsigned char *stoppedSlot = index * 0x70 + g_sound_state;
                if (*(unsigned char **)(stoppedSlot + 0x88) == moby && stoppedSlot[0x74])
                    snd_stop_voice(index);
            }
            *(int *)(state + 0x90) = -1;
        }
        break;
    }
    if (hero_is_current_selected_id((int)moby) && !*(int *)(state + 0x80)) {
        *(PoolRecord64 **)(state + 0x84) = cam_alloc_override_slot(5);
        *(int *)(state + 0x80) = 1;
        object_fill_settings_block((char *)moby);
    } else if (!hero_is_current_selected_id((int)moby) && *(int *)(state + 0x80)) {
        cam_end_override(*(unsigned char **)(state + 0x84));
        *(int *)(state + 0x80) = 0;
    }
    FastVecSub(&delta, moby + 0x10, &oldPosition);
    mat_combine_and_store(state + 0x20, &delta, &oldRotation, moby + 0xF0);
    child = *(unsigned char **)(state + 0x88);
    if (child) {
        glow_flicker_update(child, (float *)(state + 0x8C), moby[0x20] == 2);
        child = *(unsigned char **)(state + 0x88);
        if (!child[0x23]) {
            moby_mark_spawned(child);
            *(unsigned char **)(state + 0x88) = 0;
        } else {
            *(Quadword *)(child + 0xF0) = *(Quadword *)(moby + 0xF0);
            FastVecSub(&offset, &g_camera_l20_position, moby + 0x10);
            FastVecScale(&offset, &offset, 0.01f);
            FastVecAdd(*(unsigned char **)(state + 0x88) + 0x10, &offset, moby + 0x10);
            func_002A0F48(*(unsigned char **)(state + 0x88));
        }
    }
}

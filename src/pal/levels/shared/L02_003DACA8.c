#include "include_asm.h"

#include "common.h"
extern void moby_set_state(void *, int, int);
extern unsigned char g_sound_state[];
extern int D_L02_001B3FD8 __attribute__((sda));
extern void platform_init(void *);
extern void part_spawn_puff_at_moby(void *);
extern void moby_push_nearby_sideways(void *);
extern void moby_update_attached_transforms(void *, void *);
extern void multiply_matrix3x3(void *, void *, void *);
extern void copy_matrix_rotation(void *, void *);
extern void mat_get_euler_angles(float *, float *);
extern int PlayMobySound(int, int, char *);
extern int snd_is_voice_playing_for_owner(int, int);
extern void snd_stop_voice(int);
extern int math_fast_float_d(void *);

/* The level's own sound-emitter update: the kind byte at +0x20 of the object picks the
   work, the shared emitter table at D_00188660 holds the listeners. */
void func_PAL_L02_003DACA8(char *a0)
{
    char *s1 = a0;
    char *s2;
    unsigned char buf[0x40];

    s2 = *(char **)(s1 + 0x68);
    platform_init(a0);

    switch (*(unsigned char *)(s1 + 0x20)) {
    case 2:
        if (*(int *)(s2 + 0xBC) == 0)
            return;
        moby_set_state(s1, 3, -1);
        *(int *)(s2 + 0xB4) = D_L02_001B3FD8;
        break;
    case 1:
        moby_push_nearby_sideways(s1);
        if (*(unsigned char *)(s1 + 0x31) != 0)
            part_spawn_puff_at_moby(s1);
        if (*(int *)(s2 + 0xBC) != 0)
            return;
        moby_set_state(s1, 4, -1);
        *(int *)(s2 + 0xB4) = D_L02_001B3FD8;
        break;
    case 3:
        multiply_matrix3x3(s1 + 0xC0, s2 + 0x80, s1 + 0xC0);
        if (*(int *)(s2 + 0xB4) == D_L02_001B3FD8)
            PlayMobySound(1, 0, s1);
        copy_matrix_rotation(buf, s1 + 0xC0);
        mat_get_euler_angles((float *)buf, s1 + 0xF0);
        moby_update_attached_transforms(s1, s2 + 0x30);
        moby_push_nearby_sideways(s1);
        math_fast_float_d(s2 + 0xB4);
        if (*(int *)(s2 + 0xB4) == 0)
            moby_set_state(s1, 1, -1);
        if (snd_is_voice_playing_for_owner((int)s1, *(short *)(s2 + 0xC0)) != 0)
            return;
        *(short *)(s2 + 0xC0) = PlayMobySound(0, 4, s1);
        break;
    case 4:
        multiply_matrix3x3(s1 + 0xC0, s2 + 0x80, s1 + 0xC0);
        copy_matrix_rotation(buf, s1 + 0xC0);
        mat_get_euler_angles((float *)buf, s1 + 0xF0);
        moby_update_attached_transforms(s1, s2 + 0x30);
        moby_push_nearby_sideways(s1);
        math_fast_float_d(s2 + 0xB4);
        if (*(int *)(s2 + 0xB4) != 0)
            return;
        if (*(short *)(s2 + 0xC0) != -1) {
            unsigned char *e = g_sound_state + *(short *)(s2 + 0xC0) * 0x70;

            if (*(int *)(e + 0x88) == (int)s1 && *(unsigned char *)(e + 0x74) != 0)
                snd_stop_voice(*(short *)(s2 + 0xC0));
        }
        *(short *)(s2 + 0xC0) = -1;
        moby_set_state(s1, 2, -1);
        break;
    }
}


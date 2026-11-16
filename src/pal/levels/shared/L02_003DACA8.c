#include "include_asm.h"

#include "common.h"
extern void moby_set_state(void *, int, int);
extern unsigned char g_sound_state[];
extern int g_snd_emitter_cooldown __attribute__((sda));
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
void snd_emitter_update_pal(char *moby)
{
    char *moby_ref = moby;
    char *vars;
    unsigned char matrix_buf[0x40];

    vars = *(char **)(moby_ref + 0x68);
    platform_init(moby);

    switch (*(unsigned char *)(moby_ref + 0x20)) {
    case 2:
        if (*(int *)(vars + 0xBC) == 0)
            return;
        moby_set_state(moby_ref, 3, -1);
        *(int *)(vars + 0xB4) = g_snd_emitter_cooldown;
        break;
    case 1:
        moby_push_nearby_sideways(moby_ref);
        if (*(unsigned char *)(moby_ref + 0x31) != 0)
            part_spawn_puff_at_moby(moby_ref);
        if (*(int *)(vars + 0xBC) != 0)
            return;
        moby_set_state(moby_ref, 4, -1);
        *(int *)(vars + 0xB4) = g_snd_emitter_cooldown;
        break;
    case 3:
        multiply_matrix3x3(moby_ref + 0xC0, vars + 0x80, moby_ref + 0xC0);
        if (*(int *)(vars + 0xB4) == g_snd_emitter_cooldown)
            PlayMobySound(1, 0, moby_ref);
        copy_matrix_rotation(matrix_buf, moby_ref + 0xC0);
        mat_get_euler_angles((float *)matrix_buf, moby_ref + 0xF0);
        moby_update_attached_transforms(moby_ref, vars + 0x30);
        moby_push_nearby_sideways(moby_ref);
        math_fast_float_d(vars + 0xB4);
        if (*(int *)(vars + 0xB4) == 0)
            moby_set_state(moby_ref, 1, -1);
        if (snd_is_voice_playing_for_owner((int)moby_ref, *(short *)(vars + 0xC0)) != 0)
            return;
        *(short *)(vars + 0xC0) = PlayMobySound(0, 4, moby_ref);
        break;
    case 4:
        multiply_matrix3x3(moby_ref + 0xC0, vars + 0x80, moby_ref + 0xC0);
        copy_matrix_rotation(matrix_buf, moby_ref + 0xC0);
        mat_get_euler_angles((float *)matrix_buf, moby_ref + 0xF0);
        moby_update_attached_transforms(moby_ref, vars + 0x30);
        moby_push_nearby_sideways(moby_ref);
        math_fast_float_d(vars + 0xB4);
        if (*(int *)(vars + 0xB4) != 0)
            return;
        if (*(short *)(vars + 0xC0) != -1) {
            unsigned char *voice = g_sound_state + *(short *)(vars + 0xC0) * 0x70;

            if (*(int *)(voice + 0x88) == (int)moby_ref && *(unsigned char *)(voice + 0x74) != 0)
                snd_stop_voice(*(short *)(vars + 0xC0));
        }
        *(short *)(vars + 0xC0) = -1;
        moby_set_state(moby_ref, 2, -1);
        break;
    }
}


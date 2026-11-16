#include "include_asm.h"
#include "names.h"


extern float g_spark_burst_threshold __attribute__((sda));
extern float g_level_float_param __attribute__((sda));
extern void *part_find_owned_effect_slot(char *, int, int);
extern void part_l01_spawn_ring_of_sparks(char *, int, float, float, float, float);
extern int PlayMobySound(int, int, char *);

/* When hit, bursts into a spray of pieces and removes itself. */
void burst_on_hit_update_pal(char *moby)
{
    char *hit;
    int ring_count;

    if (*(unsigned char *)(moby + 0x20) == 0) {
        *(unsigned char *)(moby + 0x20) = 1;
        *(unsigned short *)(moby + 0x34) |= 0x800;
    }

    hit = (char *)part_find_owned_effect_slot(moby, 0x4010000, 0);
    if (hit != 0 && *(short *)(*(char **)(hit + 0x20) + 0xAA) != 0xFE5) {
        ring_count = 3;
        if (g_spark_burst_threshold < 0.8999999761581421f && g_level_float_param < 0.8999999761581421f)
            ring_count = 0xE;

        part_l01_spawn_ring_of_sparks(moby, ring_count, 0.0f, 3.263000011444092f, 1.9739999771118164f,
                          0.14000002f);
        PlayMobySound(0, 0, moby);
        moby_mark_spawned(moby);
    } else {
        *(unsigned char *)(moby + 0xA8) = 0xFF;
    }
}




#include "common.h"
extern int cam_moby_update(char *);
extern void moby_set_state(char *, int, int);
extern void moby_mark_spawned(char *);
extern void flying_fragment_update(unsigned char *);

/* A fragment flying through the air; it fades out and is removed. */
void flying_fragment_update_pal(unsigned char *moby)
{
    switch (moby[0x20]) {
    case 0:
        if (cam_moby_update((char *)moby) != 0) {
            moby_set_state((char *)moby, 1, -1);
            *(unsigned short *)(moby + 0x34) |= 0x2800;
        }
        break;
    case 1:
        cam_moby_update((char *)moby);
        if (moby[0x23] < 2) {
            moby_mark_spawned((char *)moby);
        } else {
            moby[0x23] -= 2;
        }
        break;
    }
}

typedef unsigned int NotakQuad __attribute__((mode(TI)));
extern char g_sound_state[];
extern char g_hero_position[];
/* Keep this absolute address as one assembler macro under -G0. */
extern char g_effect_vector[] __attribute__((sda));
extern int func_0035CBA0(char *, int, int);
extern void moby_set_byte_on_group(int, int);
extern int func_003A0948(int, int, char *);
extern void FastVecAdd(void *, void *, void *);
extern void *SpawnExplosion_pal(void *, int, int, int, int, int, int, int,
                                   float, float, int, int, int, int);
extern void part_spawn_masked_debris_pal(char *, int, void *, int, float, float, float, float);
extern void part_spawn_scaled_bolts_pal(char *, int, float);
extern void func_00350388(char *);
extern int math_random_int_range(int, int);
extern float vec_distance_xy(void *, void *);
extern int math_fast_float_d(void *);
extern void snd_stop_voice(int);
extern void part_emit_facing_pal(char *);

/* func_PAL_L06_00461504, the PAL copy of func_L06_0045C3E8: the same C, where the three
   countdowns written to state take the 50 Hz scale. */
void particle_l06_emitter_update_pal(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    char *hit;
    float pos[4];
    *(unsigned char *)(moby + 0x23) = 0x80;
    if (!vars) {
        return;
    }
    hit = (char *)func_0035CBA0(moby, 0x4010000, 0);
    if (hit && *(short *)(*(char **)(hit + 0x20) + 0xAA) != 0xFE5) {
        if (*(unsigned char *)(moby + 0x20) == 1) {
            moby_set_byte_on_group(*(unsigned char *)(moby + 0x21), 0);
        }
        func_003A0948(1, 0, moby);
        *(NotakQuad *)pos = 0;
        pos[2] = 1.0f;
        FastVecAdd(pos, pos, moby + 0x10);
        SpawnExplosion_pal(pos, 1, 25, 20, 20, 20, 45, 1, 1.25f, 20.0f, 1, 1, 0, 0);
        part_spawn_masked_debris_pal(moby, 0x7F, g_effect_vector, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
        part_spawn_scaled_bolts_pal(moby, 1, 0.0f);
        func_00350388(moby);
    }
    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        *(unsigned char *)(moby + 0x23) = 0x80;
        *(int *)vars = ((s32)(math_random_int_range(40, 250)) * 5 + 2) / 6;
        moby[0x20] = 2;
        *(int *)(vars + 8) = -1;
        break;
    case 1:
        if (vec_distance_xy(moby + 0x10, g_hero_position) < 32.0f) {
            part_emit_facing_pal(moby);
        }
        if (math_fast_float_d(vars + 4)) {
            *(int *)vars = ((s32)(math_random_int_range(200, 250)) * 5 + 2) / 6;
            if (*(int *)(vars + 8) != -1) {
                char *snd = g_sound_state + *(int *)(vars + 8) * 0x70;
                if (*(char **)(snd + 0x88) == moby && *(unsigned char *)(snd + 0x74)) {
                    snd_stop_voice(*(int *)(vars + 8));
                }
            }
            *(int *)(vars + 8) = -1;
            moby[0x20] = 2;
            moby_set_byte_on_group(*(unsigned char *)(moby + 0x21), 0);
        }
        break;
    case 2:
        if (math_fast_float_d(vars) && *(unsigned char *)(moby + 0xBC) == 0) {
            char *snd;
            *(int *)(vars + 4) = ((s32)(math_random_int_range(200, 250)) * 5 + 2) / 6;
            snd = g_sound_state + *(int *)(vars + 8) * 0x70;
            if (*(char **)(snd + 0x88) != moby || !*(unsigned char *)(snd + 0x74)) {
                *(int *)(vars + 8) = func_003A0948(0, 4, moby);
            }
            moby[0x20] = 1;
            moby_set_byte_on_group(*(unsigned char *)(moby + 0x21), 1);
        }
        break;
    }
    *(unsigned char *)(moby + 0xA8) = 0xFF;
}




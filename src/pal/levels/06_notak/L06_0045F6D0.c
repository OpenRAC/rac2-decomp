#include "include_asm.h"
#include "names.h"


extern float D_L06_001B234C __attribute__((sda));
extern float D_001B2350 __attribute__((sda));
extern int part_find_owned_effect_slot(char *, int, int);
extern void part_l01_spawn_ring_of_sparks(char *, int, float, float, float, float);
extern int PlayMobySound(int, int, char *);

void func_PAL_L06_00460E58(char *a0)
{
    char *p;
    int n;

    if (*(unsigned char *)(a0 + 0x20) == 0) {
        *(unsigned char *)(a0 + 0x20) = 1;
        *(unsigned short *)(a0 + 0x34) |= 0x800;
    }

    p = (char *)part_find_owned_effect_slot(a0, 0x4010000, 0);
    if (p != 0 && *(short *)(*(char **)(p + 0x20) + 0xAA) != 0xFE5) {
        n = 3;
        if (D_L06_001B234C < 0.8999999761581421f && D_001B2350 < 0.8999999761581421f)
            n = 0xE;

        part_l01_spawn_ring_of_sparks(a0, n, 0.0f, 3.263000011444092f, 1.9739999771118164f,
                          0.14000002f);
        PlayMobySound(0, 0, a0);
        moby_mark_spawned(a0);
    } else {
        *(unsigned char *)(a0 + 0xA8) = 0xFF;
    }
}




#include "common.h"
extern int cam_moby_update(char *);
extern void moby_set_state(char *, int, int);
extern void moby_mark_spawned(char *);
extern void flying_fragment_update(unsigned char *);

void func_PAL_L06_00461470(unsigned char *a0)
{
    switch (a0[0x20]) {
    case 0:
        if (cam_moby_update((char *)a0) != 0) {
            moby_set_state((char *)a0, 1, -1);
            *(unsigned short *)(a0 + 0x34) |= 0x2800;
        }
        break;
    case 1:
        cam_moby_update((char *)a0);
        if (a0[0x23] < 2) {
            moby_mark_spawned((char *)a0);
        } else {
            a0[0x23] -= 2;
        }
        break;
    }
}

typedef unsigned int NotakQuad __attribute__((mode(TI)));
extern char g_sound_state[];
extern char g_hero_position[];
/* Keep this absolute address as one assembler macro under -G0. */
extern char D_L06_001A8F20[] __attribute__((sda));
extern int func_0035CBA0(char *, int, int);
extern void moby_set_byte_on_group(int, int);
extern int func_003A0948(int, int, char *);
extern void FastVecAdd(void *, void *, void *);
extern void *func_PAL_L00_003FB330(void *, int, int, int, int, int, int, int,
                                   float, float, int, int, int, int);
extern void func_PAL_002B15D8(char *, int, void *, int, float, float, float, float);
extern void func_PAL_L00_003281C0(char *, int, float);
extern void func_00350388(char *);
extern int math_random_int_range(int, int);
extern float vec_distance_xy(void *, void *);
extern int math_fast_float_d(void *);
extern void snd_stop_voice(int);
extern void func_PAL_L06_00461850(char *);

/* func_PAL_L06_00461504, the PAL copy of func_L06_0045C3E8: the same C, where the three
   countdowns written to state take the 50 Hz scale. */
void func_PAL_L06_00461504(char *a0)
{
    char *state = *(char **)(a0 + 0x68);
    char *hit;
    float pos[4];
    *(unsigned char *)(a0 + 0x23) = 0x80;
    if (!state) {
        return;
    }
    hit = (char *)func_0035CBA0(a0, 0x4010000, 0);
    if (hit && *(short *)(*(char **)(hit + 0x20) + 0xAA) != 0xFE5) {
        if (*(unsigned char *)(a0 + 0x20) == 1) {
            moby_set_byte_on_group(*(unsigned char *)(a0 + 0x21), 0);
        }
        func_003A0948(1, 0, a0);
        *(NotakQuad *)pos = 0;
        pos[2] = 1.0f;
        FastVecAdd(pos, pos, a0 + 0x10);
        func_PAL_L00_003FB330(pos, 1, 25, 20, 20, 20, 45, 1, 1.25f, 20.0f, 1, 1, 0, 0);
        func_PAL_002B15D8(a0, 0x7F, D_L06_001A8F20, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
        func_PAL_L00_003281C0(a0, 1, 0.0f);
        func_00350388(a0);
    }
    switch (*(unsigned char *)(a0 + 0x20)) {
    case 0:
        *(unsigned char *)(a0 + 0x23) = 0x80;
        *(int *)state = ((s32)(math_random_int_range(40, 250)) * 5 + 2) / 6;
        a0[0x20] = 2;
        *(int *)(state + 8) = -1;
        break;
    case 1:
        if (vec_distance_xy(a0 + 0x10, g_hero_position) < 32.0f) {
            func_PAL_L06_00461850(a0);
        }
        if (math_fast_float_d(state + 4)) {
            *(int *)state = ((s32)(math_random_int_range(200, 250)) * 5 + 2) / 6;
            if (*(int *)(state + 8) != -1) {
                char *snd = g_sound_state + *(int *)(state + 8) * 0x70;
                if (*(char **)(snd + 0x88) == a0 && *(unsigned char *)(snd + 0x74)) {
                    snd_stop_voice(*(int *)(state + 8));
                }
            }
            *(int *)(state + 8) = -1;
            a0[0x20] = 2;
            moby_set_byte_on_group(*(unsigned char *)(a0 + 0x21), 0);
        }
        break;
    case 2:
        if (math_fast_float_d(state) && *(unsigned char *)(a0 + 0xBC) == 0) {
            char *snd;
            *(int *)(state + 4) = ((s32)(math_random_int_range(200, 250)) * 5 + 2) / 6;
            snd = g_sound_state + *(int *)(state + 8) * 0x70;
            if (*(char **)(snd + 0x88) != a0 || !*(unsigned char *)(snd + 0x74)) {
                *(int *)(state + 8) = func_003A0948(0, 4, a0);
            }
            a0[0x20] = 1;
            moby_set_byte_on_group(*(unsigned char *)(a0 + 0x21), 1);
        }
        break;
    }
    *(unsigned char *)(a0 + 0xA8) = 0xFF;
}




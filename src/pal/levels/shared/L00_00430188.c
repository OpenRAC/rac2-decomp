#include "include_asm.h"

#include "common.h"
extern char g_sound_state[];
extern char g_camera_l00_position[];
extern char *D_L00_001B19EC __attribute__((section(".sdata")));
extern float fast_vec_dist(char *, char *);
extern int math_fast_float_d(int *);
extern int snd_start_from_table_entry(int, int, char *, int);
extern int math_random_int_below(int);
extern void snd_stop_voice(int);

void func_PAL_L00_00430188(char *self) {
    int *sub = *(int **)(self + 8);
    unsigned int flags;
    float distance;
    if (sub[0] < 0) return;
    distance = fast_vec_dist(g_camera_l00_position, self + 0x40);
    if (distance < *(float *)(self + 0xc)) {
        char *slot;
        flags = 0;
        if (*(u8 *)(D_L00_001B19EC + sub[0] * 32 + 0x18)) flags |= 4;
        slot = g_sound_state + sub[4] * 0x70;
        if (*(char **)(slot + 0x8c) == self && *(u8 *)(slot + 0x74)) return;
        if (math_fast_float_d(sub + 3)) {
            sub[4] = snd_start_from_table_entry(sub[0], flags, self, 0x400);
            if (sub[2] > 0) sub[3] = (int)((sub[1] + math_random_int_below(sub[2] - sub[1])) * 5e+01f);
        }
    } else if (*(float *)(self + 0xc) + 1.0f < distance) {
        char *slot;
        int index = sub[4];
        if (index != -1) {
            slot = g_sound_state + index * 0x70;
            if (*(char **)(slot + 0x8c) == self && *(u8 *)(slot + 0x74)) snd_stop_voice(index);
        }
        sub[4] = -1;
    }
}



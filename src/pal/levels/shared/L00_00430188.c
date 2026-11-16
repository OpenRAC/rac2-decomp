#include "include_asm.h"

#include "common.h"
extern char g_sound_state[];
extern char g_camera_l00_position[];
extern char *g_slot_table __attribute__((section(".sdata")));
extern float fast_vec_dist(char *, char *);
extern int math_fast_float_d(int *);
extern int snd_start_from_table_entry(int, int, char *, int);
extern int math_random_int_below(int);
extern void snd_stop_voice(int);

/* Starts the emitter's sound when the listener comes within its radius and stops it once the listener is one unit past it (PAL: 50 Hz timings). */
void snd_update_emitter_proximity_pal(char *emitter) {
    int *state = *(int **)(emitter + 8);
    unsigned int flags;
    float distance;
    if (state[0] < 0) return;
    distance = fast_vec_dist(g_camera_l00_position, emitter + 0x40);
    if (distance < *(float *)(emitter + 0xc)) {
        char *slot;
        flags = 0;
        if (*(u8 *)(g_slot_table + state[0] * 32 + 0x18)) flags |= 4;
        slot = g_sound_state + state[4] * 0x70;
        if (*(char **)(slot + 0x8c) == emitter && *(u8 *)(slot + 0x74)) return;
        if (math_fast_float_d(state + 3)) {
            state[4] = snd_start_from_table_entry(state[0], flags, emitter, 0x400);
            if (state[2] > 0) state[3] = (int)((state[1] + math_random_int_below(state[2] - state[1])) * 5e+01f);
        }
    } else if (*(float *)(emitter + 0xc) + 1.0f < distance) {
        char *slot;
        int index = state[4];
        if (index != -1) {
            slot = g_sound_state + index * 0x70;
            if (*(char **)(slot + 0x8c) == emitter && *(u8 *)(slot + 0x74)) snd_stop_voice(index);
        }
        state[4] = -1;
    }
}



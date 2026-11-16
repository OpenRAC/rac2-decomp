#include "common.h"

/* 989snd's vsync callback, permcb.cpp in the NTSC split.
   rac1-decomp src/core/permcb.c: func_0012F308. The three counters sit at
   0x001A7200/0x001A7208/0x001A7210; retail reaches the last one $gp-relative
   because its store lands in the jr delay slot (0x001A7210 = $gp - 0x7DE0).
   0x10000800 is T1_COUNT. */
extern long g_timer_base_count NOT_SDA;
extern long g_vsync_count NOT_SDA;
extern long g_timer_total_count MACRO_ADDR;

/* Runs every vertical sync and updates the timer counters. */
int timer_update_vsync_counters(void) {
    g_vsync_count++;
    g_timer_total_count = g_timer_base_count + (unsigned int)((int)T1_COUNT);
    return 0;
}

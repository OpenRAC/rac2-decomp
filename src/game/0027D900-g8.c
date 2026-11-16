#include "common.h"

/* Adapted from rac1-decomp src/game/draw.c (GPL-3.0). */
extern int g_screen_offset_x[] __attribute__((sda));
extern int g_screen_offset_y[] __attribute__((sda));
extern int g_gs_clip_x_value[] __attribute__((sda));
extern int g_gs_clip_y_value[] __attribute__((sda));
extern int g_cutscene_active_flag, g_cutscene_letterbox_progress;
extern unsigned char g_language_settings[] __attribute__((sda));
typedef union { int *words; char *bytes; int address; } PacketCursor;
extern PacketCursor ref_0027D900_01;
extern char ref_0027D900_02[], ref_0027D900_03[];
/* Slides black bars in at the top and bottom of the screen, or back out again. */
void DrawLetterboxBars(void) {
    int h;

    if (g_cutscene_active_flag != 0) {
        if (g_cutscene_letterbox_progress < 52) {
            g_cutscene_letterbox_progress++;
        }
    } else {
        if (g_cutscene_letterbox_progress == 0) {
            return;
        }
        g_cutscene_letterbox_progress--;
    }
    h = g_cutscene_letterbox_progress;
    if (h == 0 || g_language_settings[1]) {
        return;
    }
    h <<= 4;
    ref_0027D900_01.words[0] = 0x10000007;
    ref_0027D900_01.words[1] = 0;
    ref_0027D900_01.words[2] = 0;
    ref_0027D900_01.words[3] = 0x50000007;
    {
        int *base = ref_0027D900_01.words;
        ref_0027D900_01.words = base + 4;
        qcopy(ref_0027D900_01.words, ref_0027D900_02);
        *(short *)(base + 4) = 0x8001;
    }
    {
        int *base = ref_0027D900_01.words;
        long *p;
        ref_0027D900_01.words = base + 4;
        p = (long *)ref_0027D900_01.words;
        p[0] = 0x104;
        p[1] = 0x80000000;
    }
    {
        int *base = ref_0027D900_01.words;
        ref_0027D900_01.words = base + 4;
        qcopy(ref_0027D900_01.words, ref_0027D900_03);
        *(short *)(base + 4) = 0x8008;
    }
    {
        int *base = ref_0027D900_01.words;
        long *p;
        ref_0027D900_01.words = base + 4;
        p = (long *)ref_0027D900_01.words;
        p[0] = g_screen_offset_x[0] | ((long)g_screen_offset_y[0] << 16) | ((long)0xFFFFF3 << 32);
        p[1] = g_screen_offset_x[0] | ((long)(g_screen_offset_y[0] + h) << 16) | ((long)0xFFFFF3 << 32);
        p[2] = g_gs_clip_x_value[0] | ((long)g_screen_offset_y[0] << 16) | ((long)0xFFFFF3 << 32);
        p[3] = g_gs_clip_x_value[0] | ((long)(g_screen_offset_y[0] + h) << 16) | ((long)0xFFFFF3 << 32);
        p[4] = g_gs_clip_x_value[0] | ((long)g_gs_clip_y_value[0] << 16) | ((long)0xFFFFF3 << 32);
        p[5] = g_gs_clip_x_value[0] | ((long)(g_gs_clip_y_value[0] - h) << 16) | ((long)0xFFFFF3 << 32);
        p[6] = g_screen_offset_x[0] | ((long)g_gs_clip_y_value[0] << 16) | ((long)0xFFFFF3 << 32);
        p[7] = g_screen_offset_x[0] | ((long)(g_gs_clip_y_value[0] - h) << 16) | ((long)0xFFFFF3 << 32);
    }
    ref_0027D900_01.words = (int *)((char *)ref_0027D900_01.words + 0x40);
}

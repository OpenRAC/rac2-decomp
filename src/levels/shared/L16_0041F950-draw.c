#include "include_asm.h"
#include "names.h"

extern void VU1_addGSregister(int, int);
extern void gfx_draw_colored_rectangle(int, int, int, int, unsigned long);
extern struct { char pad[0x150]; short x, y; } g_screen_adjust_offsets;
extern void gfx_draw_billboard_quad_jitter(void *, int, float, float, float, float, float, int);

/* Draws the on-screen fade and the glow effect for a timed object as its countdown runs. */
void gfx_draw_timed_fade_glow(char *object) {
    char *state = *(char **)(object + 0x68);
    if (*(short *)(state + 2) - *(short *)state < 2 && *(short *)(state + 4)) {
        if (*(int *)(state + 0x1C)) {
            VU1_addGSregister(0x42, 0x48);
            gfx_draw_colored_rectangle(0, g_screen_adjust_offsets.y, 0, g_screen_adjust_offsets.x, (unsigned long)(int)0x80808080);
        }
    }
    if (*(int *)(state + 0x18)) {
        if (*(short *)(state + 2) - *(short *)state < 10) {
            float progress = (*(short *)(state + 2) - *(short *)state) * 0.1f;
            gfx_draw_billboard_quad_jitter(object + 0x10, 0x3C, *(float *)(state + 8) + (*(float *)(state + 12) - *(float *)(state + 8)) * progress, 0.5f, 0.0f, 0.0f, 0.0f, 0);
        } else if ((unsigned short)(*(unsigned short *)state - 0x2E) < 4) {
            float progress = (*(short *)state - 0x2D) * 0.1f;
            gfx_draw_billboard_quad_jitter(object + 0x10, 0x3C, *(float *)(state + 8) + (*(float *)(state + 12) - *(float *)(state + 8)) * progress, 0.5f, 0.0f, 0.0f, 0.0f, 0);
        }
    }
}

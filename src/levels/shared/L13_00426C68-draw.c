#include "include_asm.h"
#include "names.h"

extern void VU1_addGSregister(int, int);
extern void gfx_draw_colored_rectangle(int, int, int, int, unsigned long);
extern struct { char pad[0x150]; short x, y; } g_screen_adjust_offsets;
extern void gfx_draw_jittered_billboard_quad_copy(void *, int, float, float, float, float, float, int);

/* Draws the screen flash and blends a sound effect while the object's countdown nears its end. */
void gfx_draw_screen_flash_sound(char *obj) {
    char *st = *(char **)(obj + 0x68);
    if (*(short *)(st + 2) - *(short *)st < 2 && *(short *)(st + 4)) {
        if (*(int *)(st + 0x1C)) {
            VU1_addGSregister(0x42, 0x48);
            gfx_draw_colored_rectangle(0, g_screen_adjust_offsets.y, 0, g_screen_adjust_offsets.x, (unsigned long)(int)0x80808080);
        }
    }
    if (*(int *)(st + 0x18)) {
        if (*(short *)(st + 2) - *(short *)st < 10) {
            float t = (*(short *)(st + 2) - *(short *)st) * 0.1f;
            gfx_draw_jittered_billboard_quad_copy(obj + 0x10, 0x3C, *(float *)(st + 8) + (*(float *)(st + 12) - *(float *)(st + 8)) * t, 0.5f, 0.0f, 0.0f, 0.0f, 0);
        } else if ((unsigned short)(*(unsigned short *)st - 0x2E) < 4) {
            float t = (*(short *)st - 0x2D) * 0.1f;
            gfx_draw_jittered_billboard_quad_copy(obj + 0x10, 0x3C, *(float *)(st + 8) + (*(float *)(st + 12) - *(float *)(st + 8)) * t, 0.5f, 0.0f, 0.0f, 0.0f, 0);
        }
    }
}

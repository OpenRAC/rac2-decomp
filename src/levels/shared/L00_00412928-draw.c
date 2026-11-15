#include "include_asm.h"
#include "names.h"

extern void VU1_addGSregister(int, int);
extern void gfx_draw_colored_rectangle(int, int, int, int, unsigned long);
extern struct { char pad[0x150]; short x, y; } g_screen_adjust_offsets;
extern void ref_L00_004143D0_00(void *, int, float, float, float, float, float, int);

/* Flashes the screen at the start of the effect and draws a growing glow at the object while it builds up. */
void screen_flash_and_glow_update(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    if (*(short *)(vars + 2) - *(short *)vars < 2 && *(short *)(vars + 4)) {
        if (*(int *)(vars + 0x1C)) {
            VU1_addGSregister(0x42, 0x48);
            gfx_draw_colored_rectangle(0, g_screen_adjust_offsets.y, 0, g_screen_adjust_offsets.x, (unsigned long)(int)0x80808080);
        }
    }
    if (*(int *)(vars + 0x18)) {
        if (*(short *)(vars + 2) - *(short *)vars < 10) {
            float blend = (*(short *)(vars + 2) - *(short *)vars) * 0.1f;
            ref_L00_004143D0_00(moby + 0x10, 0x3C, *(float *)(vars + 8) + (*(float *)(vars + 12) - *(float *)(vars + 8)) * blend, 0.5f, 0.0f, 0.0f, 0.0f, 0);
        } else if ((unsigned short)(*(unsigned short *)vars - 0x2E) < 4) {
            float blend = (*(short *)vars - 0x2D) * 0.1f;
            ref_L00_004143D0_00(moby + 0x10, 0x3C, *(float *)(vars + 8) + (*(float *)(vars + 12) - *(float *)(vars + 8)) * blend, 0.5f, 0.0f, 0.0f, 0.0f, 0);
        }
    }
}

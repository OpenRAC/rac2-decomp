#include "common.h"
extern int g_enemy_freeze_flag;
extern int g_pulse_last_value[] NOT_SDA __attribute__((sda));
extern int g_arena_progress_level[] NOT_SDA __attribute__((sda));
extern void moby_set_state(void *, int, int);
extern void gfx_add_draw_callback_first(void *, void *);
extern void gfx_draw_spinning_glow_sprites(char *);
/* Fades the object in and out by pulsing its colour value up and down, and counts its frames. It asks for a refresh whenever the level counter changes. */
void UpdateJobaPulseController(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    unsigned short frame_count;
    int fade;
    int old, current;

    if (g_enemy_freeze_flag != 0)
        return;
    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        *(unsigned char *)(moby + 0x30) = 0xFF;
        moby_set_state(moby, 1, -1);
        *(int *)(vars + 0x0) = 0x1000000;
        *(int *)(vars + 0x8) = 1;
        *(int *)(vars + 0x4) = 1;
        break;
    case 1:
        if (*(unsigned short *)(moby + 0x96) >= 0x2D) {
            *(unsigned short *)(moby + 0x96) = 0;
            *(int *)(vars + 0x4) = -*(int *)(vars + 0x4);
        }
        fade = *(int *)(vars + 0x8) + *(int *)(vars + 0x4);
        old = g_pulse_last_value[0];
        current = g_arena_progress_level[0];
        *(int *)(vars + 0x0) = fade << 24;
        *(int *)(vars + 0x8) = fade;
        if (old != current) {
            g_pulse_last_value[0] = current;
            gfx_add_draw_callback_first(gfx_draw_spinning_glow_sprites, moby);
        }
        break;
    }
    frame_count = *(unsigned short *)(moby + 0x96);
    if (frame_count <= 0xFFFE)
        *(unsigned short *)(moby + 0x96) = frame_count + 1;
}

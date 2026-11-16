#include "include_asm.h"


#include "common.h"
extern float g_beam_phases[] __attribute__((sda));
extern int g_beam_slot_key[] __attribute__((sda));
extern int g_beam_slot_state[] __attribute__((sda));
extern char g_slot_pane_points[];
extern void VU1_addGSregister(int, u64);
extern int level_is_resident_flag_clear(void);
extern void DrawGlowBillboardPair(int, int);
extern void DrawRibbonStrips(int, int, void *, int, int, int, int);
extern int math_random_int_range(int, int);
extern void gfx_append_vectors_to_packet(int, int, u64, int, u64);

/* The spawner's per-frame draw callback: each live slot past state 1 scrolls its phase
   (wrapping at -8) and has its two 0x140-byte strips drawn. */
void beam_slots_draw_pal(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    int i;

    VU1_addGSregister(0x47, 0x51001);
    for (i = 0; i < 3; i++) {
        float *phase = &g_beam_phases[i];
        int j, k, x, y;
        char *p;

        if (!g_beam_slot_key[i] || g_beam_slot_state[i] < 2) continue;
        j = i * 2;
        k = j + 1;
        if (level_is_resident_flag_clear()) {
            *phase -= 0.24000001f;
            if (*phase <= -8.0f) *phase += 8.0f;
        }
        p = g_slot_pane_points + k * 0x140;
        DrawGlowBillboardPair(g_beam_slot_key[i], i);
        y = *(int *)(vars + 4) + 63;
        x = *(int *)vars + 63;
        DrawRibbonStrips(y, x, g_slot_pane_points + j * 0x140, 128, 64, i, -1);
        DrawRibbonStrips(y, x, p, 48, 16, i, math_random_int_range(1, 20));
    }
    gfx_append_vectors_to_packet(2, 0x47, 0x5340B, 0x42, 0x8000000044ULL);
}


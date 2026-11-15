#include "common.h"

/* Incomplete sda arrays at -G0: the status table's address is rebuilt on each pass. */
extern float D_L08_001B3A20[] __attribute__((sda));
extern int g_beam_slot_key[] __attribute__((sda));
extern int g_beam_slot_state[] __attribute__((sda));
extern char D_L08_002604A0[];
extern void VU1_addGSregister(int, u64);
extern int level_is_resident_flag_clear(void);
extern void DrawGlowBillboardPair(int, int);
extern void DrawRibbonStrips(int, int, void *, int, int, int, int);
extern int math_random_int_range(int, int);
extern void gfx_append_vectors_to_packet(int, int, u64, int, u64);

/* The spawner's per-frame draw callback: each live slot past state 1 scrolls its phase
   (wrapping at -8) and has its two 0x140-byte strips drawn. */
void beam_slots_draw(char *spawner) {
    char *vars = *(char **)(spawner + 0x68);
    int i;

    VU1_addGSregister(0x47, 0x51001);
    for (i = 0; i < 3; i++) {
        float *phase = &D_L08_001B3A20[i];
        int firstStrip, secondStrip, x, y;
        char *strip2;

        if (!g_beam_slot_key[i] || g_beam_slot_state[i] < 2) continue;
        firstStrip = i * 2;
        secondStrip = firstStrip + 1;
        if (level_is_resident_flag_clear()) {
            *phase -= 0.2f;
            if (*phase <= -8.0f) *phase += 8.0f;
        }
        strip2 = D_L08_002604A0 + secondStrip * 0x140;
        DrawGlowBillboardPair(g_beam_slot_key[i], i);
        y = *(int *)(vars + 4) + 63;
        x = *(int *)vars + 63;
        DrawRibbonStrips(y, x, D_L08_002604A0 + firstStrip * 0x140, 128, 64, i, -1);
        DrawRibbonStrips(y, x, strip2, 48, 16, i, math_random_int_range(1, 20));
    }
    gfx_append_vectors_to_packet(2, 0x47, 0x5340B, 0x42, 0x8000000044ULL);
}

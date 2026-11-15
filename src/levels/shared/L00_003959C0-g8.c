#include "common.h"

extern f32 IntToFloat(int);
extern s32 FloatToInt(f32);
extern void gfx_l00_draw_ribbon_with_halo(void *, int, int, int, f32, f32, f32);
extern void gfx_l00_draw_billboard_flare(void *);

extern s16 D_L00_001B2778[] __attribute__((sda));
extern s16 D_L00_001B2790[] __attribute__((sda));
extern f32 D_L00_001B27DC[] __attribute__((sda));
extern char D_L00_00239EF0[];
extern f32 D_L00_001AF260 __attribute__((sda));
extern f32 D_L00_001AF264 __attribute__((sda));

/* Updates ten 0x50-byte records using the paired halfword tables. */
void UpdateScaledRecords(char *object) {
    s16 *values = D_L00_001B2790;
    s16 *enabled = D_L00_001B2778;
    char *record = D_L00_00239EF0;
    char *savedObject = object;
    int remaining = 9;

    do {
        if (*enabled != 0) {
            int scaled = FloatToInt(IntToFloat(*values) * D_L00_001B27DC[0]);

            gfx_l00_draw_ribbon_with_halo(record, scaled, scaled, 5, D_L00_001AF260, D_L00_001AF264, 0.2f);
        }
        record += 0x50;
        values++;
        enabled++;
    } while (--remaining >= 0);
    gfx_l00_draw_billboard_flare(savedObject);
}

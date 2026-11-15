#include "include_asm.h"
#include "names.h"
typedef struct {
    unsigned char pad0[0x84];
    int f84;
    int f88;
    char *f8c;
    unsigned char pad1[0x15C - 0x90];
    int f15c;
    int f160;
    unsigned char *f164;
    unsigned char pad2[0x1A0 - 0x168];
    int f1a0;
    unsigned char pad3[0x1B0 - 0x1A4];
    float f1b0;
    unsigned char pad3b[4];
    int f1b8;
    unsigned char pad4[0x2D0 - 0x1BC];
    float f2d0;
} L04_004044B8_Record;
extern int IsPointInCuboid(void *, int);
extern void anim_start_blended(char *, int, int, int);
extern int g_is_pal_video __attribute__((sda));
extern int g_race_time_ticks;

/* Updates the record's flag from the two point tests, prints the message when the
   record has one and its counter runs, then advances the counter and the value. */
void func_PAL_L04_00408930(void *a0, L04_004044B8_Record *s0)
{
    char *s1 = (char *)a0 + 0x10;
    int v;

    if (IsPointInCuboid(s1, s0->f88)) {
        s0->f15c = 1;
    }
    if (!IsPointInCuboid(s1, s0->f84)) {
        return;
    }
    if (s0->f15c == 0) {
        return;
    }
    v = s0->f160;
    if (s0->f8c && v > 0) {
        anim_start_blended(s0->f8c, 9, 0, 0xA);
        v = s0->f160;
    }
    if (v < 4) {
        float f1 = (float)s0->f1b8;
        float f2;
        float f0;

        if (g_is_pal_video != 0) {
            f2 = f1 * 0.02f;
        } else {
            f2 = f1 * 0.016666667f;
        }
        f0 = s0->f2d0 + s0->f1b0 - f2;
        s0->f2d0 = f0;
        if (f0 < 0.0f) {
            s0->f2d0 = 0.0f;
        }
        s0->f1b8 = 0;
        s0->f15c = 0;
        s0->f160 = s0->f160 + 1;
        if (s0->f160 != 3) {
            return;
        }
        if (*(unsigned char *)(s0->f164 + 0x20) == 2) {
            s0->f1a0 = g_race_time_ticks;
        }
    }
}

#include "common.h"
extern int D_001B0960 __attribute__((sda));
extern int D_001A8CFC[] __attribute__((sda));
extern float D_001B23A4[] __attribute__((sda));
extern int D_001B2840[] __attribute__((sda));
extern char D_001B0978[];
extern int func_00336D50(int, int);
extern void func_00300A00(int, int, float, float, float, float, float);
extern void func_002ED578(int, int *, int *, int *);
extern int func_00115DA8(char *, char *, ...);
extern int func_00283CF0(float);
extern void func_0027F5B8(int, int, unsigned long, char *, int);

/* The display mode word beside the HUD scale. */
extern int D_001B23A0[] __attribute__((sda));

/* A HUD coordinate scaled for the display and rounded to a whole pixel. The display-mode
   test has no effect on the result, but it is real: its load and compare go at flow2,
   after allocation, which leaves the saved but unused register (as func_L11_004456A0). */
static __inline__ int hud_coord(float value, float scale, float half, int active)
{
    float scaled = scale * value + half;
    int result = (int)scaled;

    if (result != 0 && D_001B23A0[0] == active)
        scaled = 1.0f;
    return result;
}

/* Draws the HUD timer: two labels from the text table, then the time split into three
   fields, formatted and drawn centred, scaled by the HUD scale. */
int func_0032F3D0(void)
{
    char text[64];
    int field0, field1, field2;
    int labelId, labelY, one, tableOffset;
    float half;
    float ox, sc, z, labelBaseY;

    if (D_001B0960 == 0)
        return 1;
    labelBaseY = 380.0f;
    half = 0.5f;
    one = 1;
    tableOffset = 0x8710;
    labelId = FindTableEntryById(D_001A8CFC[0] + tableOffset, 0xC1);
    labelY = hud_coord(labelBaseY, D_001B23A4[0], half, one);
    ox = -0.5f;
    sc = 1.0f;
    DrawScaledObjectTwoAxes(labelId, 0x60442D00, 454.0f, (float)labelY, ox, sc, z = 0.0f);
    labelId = FindTableEntryById(D_001A8CFC[0] + tableOffset, 0xC2);
    labelY = hud_coord(labelBaseY, D_001B23A4[0], half, one);
    DrawScaledObjectTwoAxes(labelId, 0x55F0C070, 454.0f, (float)labelY, ox, sc, z);
    SplitTimeIntoParts(D_001B2840[0], &field0, &field1, &field2);
    Sprintf(text, D_001B0978, field0, field1, field2);
    DrawTextMediumFont(FloatToInt(405.0f), hud_coord(372.0f, D_001B23A4[0], half, one),
                  0x80808080UL, text, 128);
    return 1;
}

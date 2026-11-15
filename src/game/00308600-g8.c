#include "include_asm.h"
#include "names.h"

extern int ref_L00_0030CAA0_00 __attribute__((sda));
extern int ref_L00_0030CAA0_01 __attribute__((sda));
extern int ref_L00_0030CAA0_02 __attribute__((sda));

extern int g_current_map_index;

/* Picks the beam's glow colour. Level 20 in mode 2 has its own colour, every other case uses the normal one. */
int beam_get_glow_color(void) {
    return g_current_map_index == 20 && ref_L00_0030CAA0_00 == 2
        ? ref_L00_0030CAA0_01 : ref_L00_0030CAA0_02;
}

extern void DrawBeamAndArcTwoPassQuads(void *, int, int, int, float, float, float);
extern void beam_draw_anchor_glow(void *);

/* The globals below are read through $gp (small data) or absolutely, and each of
   them sits at another address in every program, so the names carry no level. */
extern float ref_L00_0030BA38_00 __attribute__((sda));
extern float ref_L00_0030BA38_01 __attribute__((sda));
extern int ref_L00_0030BA38_02 __attribute__((sda));
extern int ref_L00_0030BA38_03 __attribute__((sda));
extern float ref_L00_0030BA38_04 __attribute__((sda));
extern float ref_L00_0030BA38_05 __attribute__((sda));
extern float ref_L00_0030BA38_06 __attribute__((sda));
extern int ref_L00_0030BA38_07 __attribute__((sda));
extern int ref_L00_0030BA38_08 __attribute__((sda));
extern float ref_L00_0030BA38_09 __attribute__((sda));
extern float ref_L00_0030BA38_10 __attribute__((sda));
extern float ref_L00_0030BA38_11 __attribute__((sda));
extern char ref_L00_0030BA38_12[];
extern char ref_L00_0030BA38_13[];
extern short ref_L00_0030BA38_14;
extern short ref_L00_0030BA38_15;
extern short ref_L00_0030BA38_16;
extern short ref_L00_0030BA38_17;

/* Draws the beam: scrolls its texture, draws its two main ribbons and four small ones, then the glow at its end. */
void beam_draw_ribbons(void *object) {
    void *unit = *(void **)((char *)object + 0x68);
    float value = ref_L00_0030BA38_00 - ref_L00_0030BA38_01;

    ref_L00_0030BA38_00 = value;
    if (value <= -8.0f) {
        ref_L00_0030BA38_00 = value + 8.0f;
    }
    {
        char *first = ref_L00_0030BA38_12;

        DrawBeamAndArcTwoPassQuads(first, ref_L00_0030BA38_02, ref_L00_0030BA38_03,
            *(short *)((char *)unit + 0x3E), ref_L00_0030BA38_04,
            ref_L00_0030BA38_05, ref_L00_0030BA38_06);
        DrawBeamAndArcTwoPassQuads(first + 0x140, ref_L00_0030BA38_07, ref_L00_0030BA38_08,
            *(short *)((char *)unit + 0x3E), ref_L00_0030BA38_09,
            ref_L00_0030BA38_10, ref_L00_0030BA38_11);
    }
    {
        char *second = ref_L00_0030BA38_13;

        DrawBeamAndArcTwoPassQuads(second, ref_L00_0030BA38_14, ref_L00_0030BA38_14, 5,
            ref_L00_0030BA38_09, ref_L00_0030BA38_10, 0.2f);
        DrawBeamAndArcTwoPassQuads(second + 0x50, ref_L00_0030BA38_15, ref_L00_0030BA38_15, 5,
            ref_L00_0030BA38_09, ref_L00_0030BA38_10, 0.2f);
        DrawBeamAndArcTwoPassQuads(second + 0xA0, ref_L00_0030BA38_16, ref_L00_0030BA38_16, 5,
            ref_L00_0030BA38_09, ref_L00_0030BA38_10, 0.2f);
        DrawBeamAndArcTwoPassQuads(second + 0xF0, ref_L00_0030BA38_17, ref_L00_0030BA38_17, 5,
            ref_L00_0030BA38_09, ref_L00_0030BA38_10, 0.2f);
    }
    beam_draw_anchor_glow(object);
}

#include "names.h"
/* Walk a two-step fade of one resident float and drop the enable flag once it is finished.
   The float's address is a per-program value, so each of the four uses is a ref_ name whose
   value the build reads from the retail bytes; the word is read with the assembler macro
   form (an incomplete sda array in a -G8 unit), never through $gp. */
extern int g_fade_effect_active __attribute__((sda));
extern int g_fade_effect_phase __attribute__((sda));
extern float g_fade_effect_blend __attribute__((sda));
extern float ref_L00_002A7958_00[] __attribute__((sda));
extern float ref_L00_002A7958_01[] __attribute__((sda));
extern float ref_L00_002A7958_02[] __attribute__((sda));
extern float ref_L00_002A7958_03[] __attribute__((sda));

extern float func_0031D8A0(float *dst, float value, float scale);

/* Fades an effect value up to full, waits one frame, then fades it back down to zero and switches the effect off. */
void gfx_fade_screen_effect(void)
{
    float target;

    if (g_fade_effect_active == 0)
        return;
    if (g_fade_effect_phase == 0) {
        target = 1.0f;
        func_0031D8A0(ref_L00_002A7958_00, target, g_fade_effect_blend);
        if (ref_L00_002A7958_01[0] == target)
            g_fade_effect_phase = 1;
        return;
    }
    if (g_fade_effect_phase == 1) {
        g_fade_effect_phase = 2;
        return;
    }
    if (g_fade_effect_phase == 2) {
        target = 0.0f;
        func_0031D8A0(ref_L00_002A7958_02, target, g_fade_effect_blend);
        if (ref_L00_002A7958_03[0] == target)
            g_fade_effect_active = 0;
    }
}

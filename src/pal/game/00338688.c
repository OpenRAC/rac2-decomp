#include "include_asm.h"
#include "names.h"

/* func_PAL_00338688, the PAL copy of func_003369A8. */
extern void object_alloc_float4_arrays(void *);
extern unsigned char g_font_glyphs_small[];

/* Sets up the text widget defaults: font glyphs, scale 1 and a width limit (PAL version). */
void hud_init_widget_defaults_pal(char *self)
{
    object_alloc_float4_arrays(self);
    *(char **)(self + 0x34) = (char *)g_font_glyphs_small;
    *(long long *)(self + 0x38) = 1;
    *(int *)(self + 0x40) = 0;
    **(float **)(self + 4) = 1.0f;
    (*(float **)(self + 4))[1] = 1.0f;
    *(int *)(self + 0x44) = 1;
    *(int *)(self + 0x48) = 0;
    *(int *)(self + 0x4C) = 0x200;
    *(float *)(self + 0x50) = 0.7f;
}

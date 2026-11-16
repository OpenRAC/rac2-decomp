#include "include_asm.h"
#include "names.h"

/* func_US2_003377B0, the v2.00 relative of func_003369A8: the same C, with the fields 0x48-0x54 added. */

extern void object_alloc_float4_arrays(void *);
extern unsigned char g_font_glyphs_small[];

/* Sets a text widget's fields to their defaults (v2.00 copy, with the extra fields 0x48-0x54). */
void hud_init_widget_defaults_us2(char *widget)
{
    object_alloc_float4_arrays(widget);
    *(char **)(widget + 0x34) = (char *)g_font_glyphs_small;
    *(long long *)(widget + 0x38) = 1;
    *(int *)(widget + 0x40) = 0;
    **(float **)(widget + 4) = 1.0f;
    (*(float **)(widget + 4))[1] = 1.0f;
    *(int *)(widget + 0x44) = 1;
    *(int *)(widget + 0x48) = 0;
    *(int *)(widget + 0x4C) = 0x200;
    *(float *)(widget + 0x50) = 0.7f;
    *(int *)(widget + 0x54) = 1;
}

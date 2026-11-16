#include "include_asm.h"
#include "names.h"

/* Returns the text scale for a text panel mode: 0.7, 0.8 or 1.0 (PAL only). */
float text_panel_mode_scale_pal(void *object, int mode)
{
    switch (mode) {
    case 0:
        return 0.7f;
    case 1:
        return 0.8f;
    case 2:
    default:
        return 1.0f;
    }
}

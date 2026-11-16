#include "include_asm.h"
#include "names.h"

/* Returns the text scale for a panel mode: 0.7, 0.8 or 1.0 (new in v2.00). */
float text_panel_get_scale_us2(void *object, int index)
{
    switch (index) {
    case 0:
        return 0.7f;
    case 1:
        return 0.8f;
    case 2:
    default:
        return 1.0f;
    }
}



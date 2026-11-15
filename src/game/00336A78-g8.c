#include "include_asm.h"
#include "names.h"

extern int g_item_level_colors __attribute__((sda));

/* Returns one of four colour values from a table, or 0 if the index is too big. */
int ui_get_item_color(unsigned int index) {
    if (index >= 4u) return 0;
    return ((int *)&g_item_level_colors)[index];
}

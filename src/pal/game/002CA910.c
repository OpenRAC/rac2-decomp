#include "include_asm.h"
#include "names.h"

extern char *g_resident_data_base[] __attribute__((sda));
extern void popup_set_box_value(void *, int);
extern char *g_resident_data_base[] __attribute__((sda));
extern void popup_set_box_value(void *, int);

/* Turns off the resident subsystem object at +0x3CF50 (PAL). */
int menu_disable_subsystem_pal(void) {
    if (g_resident_data_base[0] != 0)
        popup_set_box_value(g_resident_data_base[0] + 0x3CF50, 0);
    return 0;
}

/* Turns on the resident subsystem object at +0x3CF50 (PAL). */
int menu_enable_subsystem_pal(void) {
    if (g_resident_data_base[0] != 0)
        popup_set_box_value(g_resident_data_base[0] + 0x3CF50, 1);
    return 0;
}


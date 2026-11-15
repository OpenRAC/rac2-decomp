#include "include_asm.h"
#include "names.h"

extern char *D_001A8CFC[] __attribute__((sda));
extern char *D_001A8CFC[] __attribute__((sda));
extern char *D_001A8CFC[] __attribute__((sda));
extern void *tab_menu_get_selected_value(void *);

int func_PAL_002D5E90(char *object) {
    if (D_001A8CFC[0] != 0)
        *(void **)(object + 0x34) = tab_menu_get_selected_value(D_001A8CFC[0] + 0x3C210);
    return 0;
}


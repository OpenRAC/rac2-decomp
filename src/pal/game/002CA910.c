#include "include_asm.h"
#include "names.h"

extern char *D_001A8CFC[] __attribute__((sda));
extern void popup_set_box_value(void *, int);
extern char *D_001A8CFC[] __attribute__((sda));
extern void popup_set_box_value(void *, int);

int func_PAL_002CA910(void) {
    if (D_001A8CFC[0] != 0)
        popup_set_box_value(D_001A8CFC[0] + 0x3CF50, 0);
    return 0;
}

int func_PAL_002CA948(void) {
    if (D_001A8CFC[0] != 0)
        popup_set_box_value(D_001A8CFC[0] + 0x3CF50, 1);
    return 0;
}


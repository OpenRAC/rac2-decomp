#include "include_asm.h"
#include "names.h"

extern int D_L00_001A904C_2 __attribute__((sda));
extern void menu_get_sub_object_value(int);

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void func_US2_L00_0030E930(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        menu_get_sub_object_value(value + 0x3C7E8);
}


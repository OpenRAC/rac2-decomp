#include "include_asm.h"
#include "names.h"

extern int D_L00_001A904C_2 __attribute__((sda));
extern void mission_screen_draw_parts(int);

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void module_l00_call_handler_7_us2(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        mission_screen_draw_parts(value + 0x3B418);
}

extern int D_L00_001A904C_1 __attribute__((sda));
extern int list_screen_layout(int, int);

/* Reads a bound global word; when it is non-zero it calls a helper with that value plus a fixed base offset as the first argument and the function's own argument as the second, otherwise returns 0. */
int module_l00_call_handler_with_arg_8_us2(int a0)
{
    int v = D_L00_001A904C_1;

    if (v != 0) {
        return list_screen_layout(v + 0x3AF80, a0);
    }
    return 0;
}

extern void list_screen_draw(int);

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void module_l00_call_handler_8_us2(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        list_screen_draw(value + 0x3AF80);
}

extern void map_screen_draw(int);

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void module_l00_call_handler_9_us2(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        map_screen_draw(value + 0x3B6F8);
}


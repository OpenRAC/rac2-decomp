#include "include_asm.h"
#include "names.h"

extern int D_L00_001A904C_1 __attribute__((sda));
extern int simple_page_update(int, int);

/* Reads a bound global word; when it is non-zero it calls a helper with that value plus a fixed base offset as the first argument and the function's own argument as the second, otherwise returns 0. */
int func_US2_L00_0030E960(int a0)
{
    int v = D_L00_001A904C_1;

    if (v != 0) {
        return simple_page_update(v + 0x3C7E8, a0);
    }
    return 0;
}

extern int D_L00_001A904C_2 __attribute__((sda));
extern void two_toggle_b_draw(int);

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void func_US2_L00_0030E9A0(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        two_toggle_b_draw(value + 0x3D1D8);
}

extern int menu_handle_page_input_c(int, int);

/* Reads a bound global word; when it is non-zero it calls a helper with that value plus a fixed base offset as the first argument and the function's own argument as the second, otherwise returns 0. */
int func_US2_L00_0030E9D0(int a0)
{
    int v = D_L00_001A904C_1;

    if (v != 0) {
        return menu_handle_page_input_c(v + 0x3D1D8, a0);
    }
    return 0;
}


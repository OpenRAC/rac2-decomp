#include "include_asm.h"
#include "names.h"

extern char *g_resident_data_base[] __attribute__((sda));
extern void hud_update_subobject_primary(void *);

void level_run_update_us2(void) {
    if (g_resident_data_base[0] != 0)
        hud_update_subobject_primary(g_resident_data_base[0] + 0x36F28);
}

extern int D_L00_001A904C_6 __attribute__((sda));
extern void text_draw_framed_box(int *p, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10);

/* Loads a 32-bit global pointer from a fixed data address; if non-null, tail-forwards it (offset by 0x36F28) plus ten incoming arguments to an overlay-local callee. */
void level_forward_draw_args_us2(int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9)
{
    int value = D_L00_001A904C_6;

    if (value != 0)
        text_draw_framed_box((int *)(value + 0x36F28), a0, a1, a2, a3, a4, a5, a6, a7, a8, a9);
}








extern void hud_update_subsystems_us2(void *);

void func_US2_0029CF10(void) {
    if (g_resident_data_base[0] != 0)
        hud_update_subsystems_us2(g_resident_data_base[0] + 0x36F28);
}


extern void hud_item_bolt_draw_us2(void *);

void func_US2_0029CF40(void) {
    if (g_resident_data_base[0] != 0)
        hud_item_bolt_draw_us2(g_resident_data_base[0] + 0x36F28);
}


extern void func_US2_00349C00(void *);

void func_US2_0029CF70(void) {
    if (g_resident_data_base[0] != 0)
        func_US2_00349C00(g_resident_data_base[0] + 0x39160);
}



extern void func_US2_00348628(void *);

void func_US2_0029CFE0(void) {
    if (g_resident_data_base[0] != 0)
        func_US2_00348628(g_resident_data_base[0] + 0x39620);
}


extern void func_US2_00347550(void *);

void func_US2_0029D010(void) {
    if (g_resident_data_base[0] != 0)
        func_US2_00347550(g_resident_data_base[0] + 0x39AF0);
}




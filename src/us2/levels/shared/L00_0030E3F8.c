#include "include_asm.h"
#include "names.h"

extern char *g_resident_data_base[] __attribute__((sda));
extern void hud_update_subsystems_us2(void *);

void func_US2_L00_0030E3F8(void) {
    if (g_resident_data_base[0] != 0)
        hud_update_subsystems_us2(g_resident_data_base[0] + 0x36F28);
}


extern void hud_item_bolt_draw_us2(void *);

void func_US2_L00_0030E428(void) {
    if (g_resident_data_base[0] != 0)
        hud_item_bolt_draw_us2(g_resident_data_base[0] + 0x36F28);
}


extern void func_US2_00349C00(void *);

void func_US2_L00_0030E458(void) {
    if (g_resident_data_base[0] != 0)
        func_US2_00349C00(g_resident_data_base[0] + 0x39160);
}



extern void func_US2_00348628(void *);

void func_US2_L00_0030E4C8(void) {
    if (g_resident_data_base[0] != 0)
        func_US2_00348628(g_resident_data_base[0] + 0x39620);
}


extern void func_US2_00347550(void *);

void func_US2_L00_0030E4F8(void) {
    if (g_resident_data_base[0] != 0)
        func_US2_00347550(g_resident_data_base[0] + 0x39AF0);
}



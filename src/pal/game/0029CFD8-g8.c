#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern int simple_page_update(void *, int);

int func_PAL_0029CFD8(int value) {
    if (g_resident_data_base != 0)
        return simple_page_update(g_resident_data_base + 0x3C898, value);
    return 0;
}

extern void two_toggle_b_draw(void *);

void func_PAL_0029D018(void) {
    if (g_resident_data_base != 0)
        two_toggle_b_draw(g_resident_data_base + 0x3D288);
}

extern int two_toggle_b_update(void *, int);

int func_PAL_0029D048(int value) {
    if (g_resident_data_base != 0)
        return two_toggle_b_update(g_resident_data_base + 0x3D288, value);
    return 0;
}

extern int UpdateFourOptionMenuInput(void *, int);

int func_PAL_0029D088(int value) {
    if (g_resident_data_base != 0)
        return UpdateFourOptionMenuInput(g_resident_data_base + 0x3D568, value);
    return 0;
}

extern void four_option_menu_draw(void *);

void func_PAL_0029D0C8(void) {
    if (g_resident_data_base != 0)
        four_option_menu_draw(g_resident_data_base + 0x3D568);
}

extern int two_toggle_a_update(void *, int);

int func_PAL_0029D0F8(int value) {
    if (g_resident_data_base != 0)
        return two_toggle_a_update(g_resident_data_base + 0x3D848, value);
    return 0;
}

extern void two_toggle_a_draw(void *);

void func_PAL_0029D138(void) {
    if (g_resident_data_base != 0)
        two_toggle_a_draw(g_resident_data_base + 0x3D848);
}

extern int single_toggle_a_update(void *, int);

int func_PAL_0029D168(int value) {
    if (g_resident_data_base != 0)
        return single_toggle_a_update(g_resident_data_base + 0x3DE98, value);
    return 0;
}

extern void single_toggle_a_draw(void *);

void func_PAL_0029D1A8(void) {
    if (g_resident_data_base != 0)
        single_toggle_a_draw(g_resident_data_base + 0x3DE98);
}

extern int screen_adjust_menu_update(void *, int);

int func_PAL_0029D1D8(int value) {
    if (g_resident_data_base != 0)
        return screen_adjust_menu_update(g_resident_data_base + 0x3E178, value);
    return 0;
}

extern void onoff_menu_draw_with_help(void *);

void func_PAL_0029D218(void) {
    if (g_resident_data_base != 0)
        onoff_menu_draw_with_help(g_resident_data_base + 0x3E178);
}

extern int onoff_menu_update(void *, int);

int func_PAL_0029D248(int value) {
    if (g_resident_data_base != 0)
        return onoff_menu_update(g_resident_data_base + 0x3E458, value);
    return 0;
}

extern void onoff_menu_draw(void *);

void func_PAL_0029D288(void) {
    if (g_resident_data_base != 0)
        onoff_menu_draw(g_resident_data_base + 0x3E458);
}

extern int list_page_update(void *, int);

int func_PAL_0029D2B8(int value) {
    if (g_resident_data_base != 0)
        return list_page_update(g_resident_data_base + 0x3F4A0, value);
    return 0;
}

extern void list_page_draw(void *);

void func_PAL_0029D2F8(void) {
    if (g_resident_data_base != 0)
        list_page_draw(g_resident_data_base + 0x3F4A0);
}

extern int audio_menu_update(void *, int);

int func_PAL_0029D328(int value) {
    if (g_resident_data_base != 0)
        return audio_menu_update(g_resident_data_base + 0x3DB28, value);
    return 0;
}

extern void audio_menu_draw(void *);

void func_PAL_0029D368(void) {
    if (g_resident_data_base != 0)
        audio_menu_draw(g_resident_data_base + 0x3DB28);
}

extern int single_toggle_c_update(void *, int);

int func_PAL_0029D398(int value) {
    if (g_resident_data_base != 0)
        return single_toggle_c_update(g_resident_data_base + 0x3EC00, value);
    return 0;
}

extern void single_toggle_c_draw(void *);

void func_PAL_0029D3D8(void) {
    if (g_resident_data_base != 0)
        single_toggle_c_draw(g_resident_data_base + 0x3EC00);
}

#include "include_asm.h"
#include "names.h"

extern int ref_L00_0030CDA0_00;

/* Sets a stored level choice to -1, meaning nothing is selected. */
void func_0029BCC8(void)
{
    ref_L00_0030CDA0_00 = -1;
}

/* func_0029BCD8 is in 0029BCC8-g8.c. */

extern char *D_001A8CFC;
extern void hud_update_subobject_alt(void *);

/* Draws the first on-screen menu panel, if the menu system exists. */
void func_0029BE88(void) {
    if (D_001A8CFC != 0)
        hud_update_subobject_alt(D_001A8CFC + 0x36F28);
}

extern int D_001A9A50 __attribute__((sda));
extern int D_001A9A54 __attribute__((sda));
extern int g_notice_owner;
extern void circle_menu_draw(void *);

/* Draws a menu panel, but only when the menu system exists and the game is in the right state. */
void func_0029BEB8(void) {
    if (D_001A9A50 != 0 && g_notice_owner == 0 && D_001A9A54 != 0 && D_001A8CFC != 0)
        circle_menu_draw(D_001A8CFC + 0x3F138);
}

/* func_0029BF08 is in 0029BCC8-g8.c. */

/* Does nothing. */
void func_0029C0D0(void) {
}

extern void hud_update_subsystems(void *);

/* Draws a menu panel, if the menu system exists. */
void func_0029C0D8(void) {
    if (D_001A8CFC != 0)
        hud_update_subsystems(D_001A8CFC + 0x36F28);
}

extern void hud_item_bolt_draw(void *);

/* Draws a menu panel, if the menu system exists. */
void func_0029C108(void) {
    if (D_001A8CFC != 0)
        hud_item_bolt_draw(D_001A8CFC + 0x36F28);
}

extern void list_menu_draw_centered_rows(void *);

/* Draws a menu panel, if the menu system exists. */
void func_0029C138(void) {
    if (D_001A8CFC != 0)
        list_menu_draw_centered_rows(D_001A8CFC + 0x39140);
}

extern int UpdateMenuChoiceListWidgets(void *, int);

/* Passes a value to a menu panel and returns its answer; returns 0 if the menu system does not exist. */
int func_0029C168(int value) {
    if (D_001A8CFC != 0)
        return UpdateMenuChoiceListWidgets(D_001A8CFC + 0x39140, value);
    return 0;
}

extern void item_grid_menu_draw(void *);

/* Draws a menu panel, if the menu system exists. */
void func_0029C1A8(void) {
    if (D_001A8CFC != 0)
        item_grid_menu_draw(D_001A8CFC + 0x39590);
}

extern void menu_screen_large_draw_parts(void *);

/* Draws a menu panel, if the menu system exists. */
void func_0029C1D8(void) {
    if (D_001A8CFC != 0)
        menu_screen_large_draw_parts(D_001A8CFC + 0x39A98);
}

extern int UpdateItemGridMenu(void *, int);

/* Passes a value to a menu panel and returns its answer; returns 0 if the menu system does not exist. */
int func_0029C208(int value) {
    if (D_001A8CFC != 0)
        return UpdateItemGridMenu(D_001A8CFC + 0x39590, value);
    return 0;
}

extern int selection_menu_update_layout(void *, int, int);

/* Passes a value to a menu panel and returns its answer; returns 0 if the menu system does not exist. */
int func_0029C248(int first, int second)
{
    if (D_001A8CFC != 0)
        return selection_menu_update_layout(D_001A8CFC + 0x39A98, first, second);
    return 0;
}

extern int mission_screen_place_parts(void *, int);

/* Passes a value to a menu panel and returns its answer; returns 0 if the menu system does not exist. */
int func_0029C290(int value) {
    if (D_001A8CFC != 0)
        return mission_screen_place_parts(D_001A8CFC + 0x3B1F0, value);
    return 0;
}

extern void mission_screen_draw_parts(void *);

/* Draws a menu panel, if the menu system exists. */
void func_0029C2D0(void) {
    if (D_001A8CFC != 0)
        mission_screen_draw_parts(D_001A8CFC + 0x3B1F0);
}

extern int list_screen_layout(void *, int);

/* Passes a value to a menu panel and returns its answer; returns 0 if the menu system does not exist. */
int func_0029C300(int value) {
    if (D_001A8CFC != 0)
        return list_screen_layout(D_001A8CFC + 0x3ADE8, value);
    return 0;
}

extern void list_screen_draw(void *);

/* Draws a menu panel, if the menu system exists. */
void func_0029C340(void) {
    if (D_001A8CFC != 0)
        list_screen_draw(D_001A8CFC + 0x3ADE8);
}

extern void map_screen_draw(void *);

/* Draws a menu panel, if the menu system exists. */
void func_0029C370(void) {
    if (D_001A8CFC != 0)
        map_screen_draw(D_001A8CFC + 0x3B490);
}

extern int map_screen_update_layout(void *, int);

/* Passes a value to a menu panel and returns its answer; returns 0 if the menu system does not exist. */
int func_0029C3A0(int value) {
    if (D_001A8CFC != 0)
        return map_screen_update_layout(D_001A8CFC + 0x3B490, value);
    return 0;
}

extern void radial_menu_destroy(void *);

/* Draws a menu panel, if the menu system exists. */
void func_0029C3E0(void) {
    if (D_001A8CFC != 0)
        radial_menu_destroy(D_001A8CFC + 0x3B7C0);
}

extern int info_panel_update(void *, int);

/* Passes a value to a menu panel and returns its answer; returns 0 if the menu system does not exist. */
int func_0029C410(int value) {
    if (D_001A8CFC != 0)
        return info_panel_update(D_001A8CFC + 0x3B7C0, value);
    return 0;
}

extern void menu_screen_draw_parts(void *);

/* Draws a menu panel, if the menu system exists. */
void func_0029C450(void) {
    if (D_001A8CFC != 0)
        menu_screen_draw_parts(D_001A8CFC + 0x39F38);
}

extern int grid_menu_update(void *, int);

/* Passes a value to a menu panel and returns its answer; returns 0 if the menu system does not exist. */
int func_0029C480(int value) {
    if (D_001A8CFC != 0)
        return grid_menu_update(D_001A8CFC + 0x39F38, value);
    return 0;
}

extern void tab_menu_draw(void *);

/* Draws a menu panel, if the menu system exists. */
void func_0029C4C0(void) {
    if (D_001A8CFC != 0)
        tab_menu_draw(D_001A8CFC + 0x3BE08);
}

extern int tab_menu_update(void *, int);

/* Passes a value to a menu panel and returns its answer; returns 0 if the menu system does not exist. */
int func_0029C4F0(int value) {
    if (D_001A8CFC != 0)
        return tab_menu_update(D_001A8CFC + 0x3BE08, value);
    return 0;
}

/* Same as the other 3BE08 panel draw: draws the menu panel if the menu system exists. */
void func_0029C530(void) {
    if (D_001A8CFC != 0)
        tab_menu_draw(D_001A8CFC + 0x3BE08);
}

/* Same as the other 3BE08 panel update: updates the menu panel and returns its answer. */
int func_0029C560(int value) {
    if (D_001A8CFC != 0)
        return tab_menu_update(D_001A8CFC + 0x3BE08, value);
    return 0;
}

extern void item_menu_draw(void *);

/* Draws a menu panel, if the menu system exists. */
void func_0029C5A0(void) {
    if (D_001A8CFC != 0)
        item_menu_draw(D_001A8CFC + 0x3C108);
}

extern int item_menu_update(void *, int);

/* Passes a value to a menu panel and returns its answer; returns 0 if the menu system does not exist. */
int func_0029C5D0(int value) {
    if (D_001A8CFC != 0)
        return item_menu_update(D_001A8CFC + 0x3C108, value);
    return 0;
}

extern void menu_draw_frame(void *);

/* Draws a menu panel, if the menu system exists. */
void func_0029C610(void) {
    if (D_001A8CFC != 0)
        menu_draw_frame(D_001A8CFC + 0x3C440);
}

extern int simple_page_update(void *, int);

/* Passes a value to a menu panel and returns its answer; returns 0 if the menu system does not exist. */
int func_0029C640(int value) {
    if (D_001A8CFC != 0)
        return simple_page_update(D_001A8CFC + 0x3C440, value);
    return 0;
}

extern void two_toggle_b_draw(void *);

/* Draws a menu panel, if the menu system exists. */
void func_0029C680(void) {
    if (D_001A8CFC != 0)
        two_toggle_b_draw(D_001A8CFC + 0x3CDB0);
}

extern int two_toggle_b_update(void *, int);

/* Passes a value to a menu panel and returns its answer; returns 0 if the menu system does not exist. */
int func_0029C6B0(int value) {
    if (D_001A8CFC != 0)
        return two_toggle_b_update(D_001A8CFC + 0x3CDB0, value);
    return 0;
}

extern int UpdateFourOptionMenuInput(void *, int);

/* Passes a value to a menu panel and returns its answer; returns 0 if the menu system does not exist. */
int func_0029C6F0(int value) {
    if (D_001A8CFC != 0)
        return UpdateFourOptionMenuInput(D_001A8CFC + 0x3D060, value);
    return 0;
}

extern void four_option_menu_draw(void *);

/* Draws a menu panel, if the menu system exists. */
void func_0029C730(void) {
    if (D_001A8CFC != 0)
        four_option_menu_draw(D_001A8CFC + 0x3D060);
}

extern int two_toggle_a_update(void *, int);

/* Passes a value to a menu panel and returns its answer; returns 0 if the menu system does not exist. */
int func_0029C760(int value) {
    if (D_001A8CFC != 0)
        return two_toggle_a_update(D_001A8CFC + 0x3D310, value);
    return 0;
}

extern void two_toggle_a_draw(void *);

/* Draws a menu panel, if the menu system exists. */
void func_0029C7A0(void) {
    if (D_001A8CFC != 0)
        two_toggle_a_draw(D_001A8CFC + 0x3D310);
}

extern int single_toggle_a_update(void *, int);

/* Passes a value to a menu panel and returns its answer; returns 0 if the menu system does not exist. */
int func_0029C7D0(int value) {
    if (D_001A8CFC != 0)
        return single_toggle_a_update(D_001A8CFC + 0x3D900, value);
    return 0;
}

extern void single_toggle_a_draw(void *);

/* Draws a menu panel, if the menu system exists. */
void func_0029C810(void) {
    if (D_001A8CFC != 0)
        single_toggle_a_draw(D_001A8CFC + 0x3D900);
}

extern int screen_adjust_menu_update(void *, int);

/* Passes a value to a menu panel and returns its answer; returns 0 if the menu system does not exist. */
int func_0029C840(int value) {
    if (D_001A8CFC != 0)
        return screen_adjust_menu_update(D_001A8CFC + 0x3DBB0, value);
    return 0;
}

extern void onoff_menu_draw_with_help(void *);

/* Draws a menu panel, if the menu system exists. */
void func_0029C880(void) {
    if (D_001A8CFC != 0)
        onoff_menu_draw_with_help(D_001A8CFC + 0x3DBB0);
}

extern int onoff_menu_update(void *, int);

/* Passes a value to a menu panel and returns its answer; returns 0 if the menu system does not exist. */
int func_0029C8B0(int value) {
    if (D_001A8CFC != 0)
        return onoff_menu_update(D_001A8CFC + 0x3DE60, value);
    return 0;
}

extern void onoff_menu_draw(void *);

/* Draws a menu panel, if the menu system exists. */
void func_0029C8F0(void) {
    if (D_001A8CFC != 0)
        onoff_menu_draw(D_001A8CFC + 0x3DE60);
}

extern int list_page_update(void *, int);

/* Passes a value to a menu panel and returns its answer; returns 0 if the menu system does not exist. */
int func_0029C920(int value) {
    if (D_001A8CFC != 0)
        return list_page_update(D_001A8CFC + 0x3EDB8, value);
    return 0;
}

extern void list_page_draw(void *);

/* Draws a menu panel, if the menu system exists. */
void func_0029C960(void) {
    if (D_001A8CFC != 0)
        list_page_draw(D_001A8CFC + 0x3EDB8);
}

extern int audio_menu_update(void *, int);

/* Passes a value to a menu panel and returns its answer; returns 0 if the menu system does not exist. */
int func_0029C990(int value) {
    if (D_001A8CFC != 0)
        return audio_menu_update(D_001A8CFC + 0x3D5C0, value);
    return 0;
}

extern void audio_menu_draw(void *);

/* Draws a menu panel, if the menu system exists. */
void func_0029C9D0(void) {
    if (D_001A8CFC != 0)
        audio_menu_draw(D_001A8CFC + 0x3D5C0);
}

extern int single_toggle_c_update(void *, int);

/* Passes a value to a menu panel and returns its answer; returns 0 if the menu system does not exist. */
int func_0029CA00(int value) {
    if (D_001A8CFC != 0)
        return single_toggle_c_update(D_001A8CFC + 0x3E5A8, value);
    return 0;
}

extern void single_toggle_c_draw(void *);

/* Draws a menu panel, if the menu system exists. */
void func_0029CA40(void) {
    if (D_001A8CFC != 0)
        single_toggle_c_draw(D_001A8CFC + 0x3E5A8);
}

extern int list_menu_update(void *, int);

/* Passes a value to a menu panel and returns its answer; returns 0 if the menu system does not exist. */
int func_0029CA70(int value) {
    if (D_001A8CFC != 0)
        return list_menu_update(D_001A8CFC + 0x3E1D8, value);
    return 0;
}

extern void menu_draw_if_active(void *);

/* Draws a menu panel, if the menu system exists. */
void func_0029CAB0(void) {
    if (D_001A8CFC != 0)
        menu_draw_if_active(D_001A8CFC + 0x3E1D8);
}

extern int list_menu_set_selection(void *, int);

/* Passes a value to a menu panel and returns its answer; returns 0 if the menu system does not exist. */
int func_0029CAE0(int value) {
    if (D_001A8CFC != 0)
        return list_menu_set_selection(D_001A8CFC + 0x3E430, value);
    return 0;
}

extern void small_list_menu_draw_rows(void *);

/* Draws a menu panel, if the menu system exists. */
void func_0029CB20(void) {
    if (D_001A8CFC != 0)
        small_list_menu_draw_rows(D_001A8CFC + 0x3E430);
}


extern void UpdateBoltCounter(void);

/* Updates the bolt counter, if the menu system exists. */
void func_0029CB58(void) {
    if (D_001A8CFC != 0)
        UpdateBoltCounter();
}

extern void DrawBoltCounterDeltas(void);

/* Draws the bolt gain and loss numbers, if the menu system exists. */
void func_0029CB80(void) {
    if (D_001A8CFC != 0)
        DrawBoltCounterDeltas();
}

extern void menu_set_screen_field_2bc(void *, int);

/* Gives a value to a menu panel, if the menu system exists. */
void func_0029CBA8(int value) {
    if (D_001A8CFC != 0)
        menu_set_screen_field_2bc(D_001A8CFC + 0x376C8, value);
}

extern int func_0033FB98(void *, int);

/* Passes a value to a menu panel and returns its answer; returns 0 if the menu system does not exist. */
int func_0029CBE0(int value) {
    if (D_001A8CFC != 0)
        return func_0033FB98(D_001A8CFC + 0x3A388, value);
    return 0;
}

extern void radial_menu_draw(void *);

/* Draws a menu panel, if the menu system exists. */
void func_0029CC20(void) {
    if (D_001A8CFC != 0)
        radial_menu_draw(D_001A8CFC + 0x3A388);
}

extern void msg_box_init_localized(void *, int, int, int);
/* Passes three values to the first menu panel, if the menu system exists. */
void func_0029CC50(int first, int second, int third) { if (D_001A8CFC != 0) msg_box_init_localized(D_001A8CFC + 0x36F28, first, second, third); }

extern void msg_box_init_short(void *, int, int);

/* Passes two values to the first menu panel, if the menu system exists. */
void func_0029CC98(int first, int second) {
    if (D_001A8CFC != 0)
        msg_box_init_short(D_001A8CFC + 0x36F28, first, second);
}

extern void msg_box_init_long(void *, int, int);

/* Passes two other values to the first menu panel, if the menu system exists. */
void func_0029CCD8(int first, int second) {
    if (D_001A8CFC != 0)
        msg_box_init_long(D_001A8CFC + 0x36F28, first, second);
}

/* Does nothing. */
void func_0029CD18(void) {
}

extern int g_is_pal_video[] __attribute__((sda));
extern void gfx_set_scale_mode_values(int);

/* Tells the menu code whether a stored game flag is set. */
void func_0029CD20(void) {
    gfx_set_scale_mode_values(g_is_pal_video[0] != 0);
}

/* func_0029CD48 is in 0029CD48.c. */

/* If the menu system exists and the game is not paused, turns something on and runs a follow-up setup step. */
void func_0029CE38(void)
{
    extern int g_notice_owner;
    extern void hud_update_record_timers(int);
    extern void level_run_callbacks(void);
    if (D_001A8CFC != 0) {
        if (g_notice_owner == 0) {
            hud_update_record_timers(1);
            level_run_callbacks();
        }
    }
}




extern void menu_draw_with_prompts(void *);

/* Draws a menu panel, if the menu system exists. */
void func_0029CED8(void) {
    if (D_001A8CFC != 0)
        menu_draw_with_prompts(D_001A8CFC + 0x3CAA8);
}

extern int popup_update_position(void *, int);

/* Passes a value to a menu panel and returns its answer; returns 0 if the menu system does not exist. */
int func_0029CF08(int value) {
    if (D_001A8CFC != 0)
        return popup_update_position(D_001A8CFC + 0x3CAA8, value);
    return 0;
}

/* Original assembly: RAC1 game/render/miscproc.c, func_0020C210. */
ASM_FUNC("asm/game", func_0029CF58);

/* Original assembly: RAC1 game/render/miscproc.c, func_0020C230. */
ASM_FUNC("asm/game", func_0029CF78);

/* Original assembly: $at as a working register and trapping addi/add/sub; the compiler cannot emit them. */
ASM_FUNC("asm/game", func_0029CFB0);

ASM_FUNC("asm/game", func_0029D050);

/* Original assembly: $at as a working register and trapping addi/add; the compiler cannot emit them. */
ASM_FUNC("asm/game", func_0029D0E0);

/* Original assembly: lqc2/qmtc2/qmfc2 VU0 ops, $at as a working register and trapping addi/add. */
ASM_FUNC("asm/game", func_0029D258);

/* Original assembly: lqc2/qmtc2/qmfc2 VU0 ops, $at as a working register and trapping addi/add. */
ASM_FUNC("asm/game", func_0029D398);

ASM_FUNC("asm/game", func_0029D4D0);

ASM_FUNC("asm/game", func_0029D7A0);

/* Original assembly: RAC1 game/render/miscproc.c, func_0020C758 (live-in $v1, unconditional `teq` traps; one more nop before the final return). */
ASM_FUNC("asm/game", func_0029D7C0);


extern void *D_0026CA90[];
extern unsigned char D_001A7BC8[];
extern unsigned char g_item_owned_flags[];
extern unsigned char D_001A7B30[];
extern unsigned char D_001395B8[];
extern unsigned int D_00139768[];
extern unsigned char D_0019B278[];
extern int D_001C51D0[];
extern int save_test_flag_bit_2(int, int);

typedef struct { int first, second, third, fourth; } ProgressBand;
extern ProgressBand D_00139A28[];

/* Progress-condition dispatcher. The retail dispatch reads the code-address table it
   already has at D_0026CA90 (twelve entries, one per condition) and jumps through it;
   `cases` only keeps the labels alive. The bodies are laid out in the retail's order,
   which puts the ninth condition's bit test before the eighth one's table lookup. */
/* Checks one kind of progress condition (a flag, a counter, a bit, or a callback) and returns whether it is true. */
int func_0029D9D0(short kind, int arg)
{
    static void *cases[12] = {&&L0, &&L1, &&L2, &&L3, &&L4, &&L5, &&L6, &&L7, &&L9, &&L8, &&L10, &&L11};
    int kindIndex = kind;

    if ((unsigned)kindIndex >= 12)
        goto L11;
    goto *D_0026CA90[kindIndex];
L0:
    return 1;
L1:
    return D_001A7BC8[arg] != 0;
L2:
    return g_item_owned_flags[arg] != 0;
L3:
    return D_001A7B30[arg] != 0;
L4:
    if (arg < 0x72)
        return D_00139A28[arg].fourth != 0;
    goto L11;
L5:
    if (arg < 0x72)
        return D_00139A28[arg].fourth >= 2;
    goto L11;
L6:
    return D_001395B8[arg] != 0;
L7:
    return ((int (*)(void))arg)() != 0;
L9: {
    unsigned int mask = 1u << (arg & 0x1F);
    return (D_00139768[(unsigned)arg >> 2] & mask) != 0;
}
L8:
    return D_0019B278[(arg & 0xFFFF) + (arg >> 16) * 4] != 0;
L10:
    return save_test_flag_bit_2(D_001C51D0[0], arg);
L11:
    return 0;
}



/* func_0029DC90 is in 0029DC90.c. */

extern int D_001397C4[];
extern unsigned char D_001395D5[];

/* Returns 1 when a progress counter is negative and its flag is set, otherwise 0. */
int func_0029DCD0(void) {
    if (D_001397C4[0] < 0) {
        if (D_001395D5[0] != 0)
            return 1;
    }
    return 0;
}

/* func_0029DD30 is in 0029DD30.c. */

/* func_0029DDC0 is in 0029DDC0.c. */

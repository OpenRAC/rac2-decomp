#include "include_asm.h"
#include "names.h"

extern char *g_resident_data_base[] __attribute__((sda));
extern int g_mission_select_enabled __attribute__((sda));
extern char g_mission_menu_field __attribute__((sda));
extern char g_mission_circle_menu __attribute__((sda));
extern char g_mission_menu_items[];
extern int stub_empty_25(void), stub_empty_25(void);
extern void func_US2_0029CA88(void), func_US2_0029C700(void);
extern void menu_set_field_144(void *, int);
extern void circle_menu_init_entries_us2(void *,void *,void *);
extern void circle_menu_set_radius_us2(void *,float);
extern void circle_menu_set_selection_us2(void *,int);
extern int stub_empty_24(void), stub_empty_24(void);

extern int ref_US2_0029C818_00(void), ref_US2_0029C818_00(void);
extern int ref_US2_0029C818_01(void), ref_US2_0029C818_01(void);

void func_US2_0029C818(void) {
 int enabled;
 if (g_resident_data_base[0] != 0) {
  enabled=0;
  if(ref_US2_0029C818_00()) enabled=ref_US2_0029C818_01()!=0;
  if(g_mission_select_enabled != enabled) {
   func_US2_0029CA88();
   g_mission_select_enabled=enabled;
   if(enabled==1) {
    menu_set_field_144(g_resident_data_base[0]+0x3CD48,(int)&g_mission_menu_field);
    circle_menu_init_entries_us2(g_resident_data_base[0]+0x3F7B0,&g_mission_circle_menu,g_mission_menu_items);
    circle_menu_set_radius_us2(g_resident_data_base[0]+0x3F7B0,36.0f);
    circle_menu_set_selection_us2(g_resident_data_base[0]+0x3F7B0,-1);
    func_US2_0029C700();
   }
  }
 }
}

extern int ref_L00_0030CDB0_00[] __attribute__((sda));
extern int g_current_game_mode[] __attribute__((sda));
extern int func_US2_0029C8F0(void);
extern unsigned int menu_get_saved_state(void);
extern void level_run_update_us2(void);
typedef int (*Fn)(void);
typedef struct { void *cb; int pad; } Slot;
typedef struct {
    char pad0[0x79D8];
    void *cb1;
    char pad1[0x7368 - 0x7354];
    void *cb2;
    char pad2[0x7370 - 0x736C];
    Slot slot[4];
    Slot slot2[2];
} Sub;

void func_US2_0029CA98(void)
{
    int i;
    int result;
    Sub *sub;
    Fn fn;
    char *g;

    if (ref_L00_0030CDB0_00[0] != 0)
        return;

    if (g_resident_data_base[0] == 0)
        goto states;
    func_US2_0029C8F0();
    fn = (Fn)((Sub *)(g_resident_data_base[0] + 0x38000))->cb2;
    if (fn != 0) {
        if (fn() != 0)
            return;
    }
    result = 0;
    for (i = 0; i < 4; i++) {
        sub = (Sub *)(g_resident_data_base[0] + 0x38000);
        if (sub->slot[i].cb != 0)
            result |= ((Fn *)(g_resident_data_base[0] + 0x3F9F8))[i * 2]();
    }
    if (result != 0)
        return;
    for (i = 0; i < 2; i++) {
        sub = (Sub *)(g_resident_data_base[0] + 0x38000);
        if (sub->slot2[i].cb != 0)
            result |= ((Fn *)(g_resident_data_base[0] + 0x3FA18))[i * 2]();
    }
    if (result != 0)
        return;
states:
    if (g_current_game_mode[0] != 0 && g_current_game_mode[0] != 5) {
        if (g_current_game_mode[0] == 4) {
            if (menu_get_saved_state() != 7)
                return;
        }
    }
    g = g_resident_data_base[0];
    if (g != 0) {
        char *b = g + 0x38000;
        g = (char *)((Sub *)b)->cb1;
        ((Fn)g)();
        level_run_update_us2();
    }
}

/* func_US2_0029CCB8, the v2.00 copy of func_0029BEB8: the same C with one more test and the menu's new offset. */
extern int g_mission_menu_depth __attribute__((sda));
extern short g_menu_command_flag[];
extern int g_notice_owner;
extern void circle_menu_draw_us2(void *);

void func_US2_0029CCB8(void) {
    if (g_mission_menu_depth != 0 && g_menu_command_flag[0] == 0 && g_notice_owner == 0 && g_mission_select_enabled != 0 && g_resident_data_base[0] != 0)
        circle_menu_draw_us2(g_resident_data_base[0] + 0x3F7B0);
}

/* func_US2_0029CD18, the v2.00 copy of func_0029BF08: the callback tables at their new offsets,
   a menu test before them and the camera scale moved out to func_US2_0029CC48. */
extern int g_current_map_index[] __attribute__((sda));
extern void hud_update_letterbox_bars(void);
extern void func_US2_0029CC48(void);
extern int menu_get_mode(void);
extern int ref_US2_0029CD18_00(int);

typedef unsigned int (*CbCd)(void);
typedef struct { void *cb; int pad; } SlotCd;
typedef struct {
    char pad0[0x79D4];
    void *cb1;
    char pad1[0x79F4 - 0x79D8];
    void *cb2;
    char pad2[0x79FC - 0x79F8];
    SlotCd slot[4];
    SlotCd slot2[2];
} SubCd;

/* The same table seen from its other end: the callback pointer is the second word. */
typedef struct { int pad; void *fn; } FnCd;

void func_US2_0029CD18(void)
{
    int result;
    int i;
    CbCd fn;
    SubCd *sub;
    char *g;

    if (ref_L00_0030CDB0_00[0] != 0)
        return;

    if (g_resident_data_base[0] == 0)
        goto states;

    if (g_current_game_mode[0] == 4) {
        if (menu_get_mode() == 8)
            return;
    }

    hud_update_letterbox_bars();
    result = 0;
    func_US2_0029CCB8();

    fn = (CbCd)((SubCd *)(g_resident_data_base[0] + 0x38000))->cb2;
    if (fn != 0)
        result = fn() != 0;

    for (i = 0; i < 4; i++) {
        sub = (SubCd *)(g_resident_data_base[0] + 0x38000);
        if (sub->slot[i].cb != 0)
            result |= ((CbCd)((FnCd *)(g_resident_data_base[0] + 0x3F9F8))[i].fn)();
    }

    for (i = 0; i < 2; i++) {
        sub = (SubCd *)(g_resident_data_base[0] + 0x38000);
        if (sub->slot2[i].cb != 0)
            result |= ((CbCd)((FnCd *)(g_resident_data_base[0] + 0x3FA18))[i].fn)();
    }

    if (result != 0) {
        if (g_current_map_index[0] == 8 || g_current_map_index[0] == 0x13) {
            if (ref_US2_0029CD18_00(2))
                func_US2_0029CC48();
        }
    }

    if (result != 0)
        return;

states:
    if (g_current_game_mode[0] != 0 && g_current_game_mode[0] != 5) {
        if (g_current_game_mode[0] == 4) {
            if (menu_get_saved_state() != 7)
                return;
        }
    }

    g = g_resident_data_base[0];
    if (g != 0) {
        char *b = g + 0x38000;
        g = (char *)((SubCd *)b)->cb1;
        ((CbCd)g)();
        func_US2_0029CC48();
    }
}

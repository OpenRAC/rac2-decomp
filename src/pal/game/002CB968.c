#include "include_asm.h"


#include "common.h"
extern char g_pause_menu_state[];
extern short D_001A63AC;
extern int D_001C51D0;
extern int g_weapon_table[];
extern unsigned char g_item_slot_to_record[];
extern int request_end_slot(int, int);
extern int request_begin_slot(int, int, int, int, void *);
extern void func_PAL_002B8898(int);
extern void LoadClassIntoFreeCacheSlot(int);
typedef struct {
    char pad00[0x1C];
    int mode;
    char pad20[0x04];
    volatile int count;
    char pad28[0x08];
    int field30;
    char pad34[0x0C];
    int field40;
    char pad44[0xB0];
    int fieldF4;
} GameState_1F2840;

void func_PAL_002CBC18(void)
{
    int n = ((GameState_1F2840 *)g_pause_menu_state)->count;

    if (n != 0)
        ((GameState_1F2840 *)g_pause_menu_state)->count = n - 1;
    if (((GameState_1F2840 *)g_pause_menu_state)->count != 0)
        return;
    if (D_001A63AC != 0)
        return;
    if (((GameState_1F2840 *)g_pause_menu_state)->mode == 2) {
        request_end_slot(0, D_001C51D0);
    } else if (((GameState_1F2840 *)g_pause_menu_state)->mode == 3) {
        request_begin_slot(1, 1, 0, ((GameState_1F2840 *)g_pause_menu_state)->fieldF4, 0);
    } else if (((GameState_1F2840 *)g_pause_menu_state)->mode == 4) {
        request_begin_slot(1, 1, 0, ((GameState_1F2840 *)g_pause_menu_state)->fieldF4, 0);
    } else if (((GameState_1F2840 *)g_pause_menu_state)->mode == 6) {
        request_begin_slot(1, 1, 0, ((GameState_1F2840 *)g_pause_menu_state)->fieldF4, 0);
    } else if (((GameState_1F2840 *)g_pause_menu_state)->mode == 5) {
        request_begin_slot(2, 1, ((GameState_1F2840 *)g_pause_menu_state)->fieldF4, 0, 0);
    } else {
        request_end_slot(0, 0);
    }
    if (((GameState_1F2840 *)g_pause_menu_state)->field40 != 0 &&
        ((GameState_1F2840 *)g_pause_menu_state)->field30 != ((GameState_1F2840 *)g_pause_menu_state)->field40) {
        int id;
        int *rec;
        func_PAL_002B8898(1);
        id = ((GameState_1F2840 *)g_pause_menu_state)->field40;
        rec = (int *)((char *)g_weapon_table + g_item_slot_to_record[id] * 0xE0);
        LoadClassIntoFreeCacheSlot(rec[5]);
        func_PAL_002B8898(1);
    }
    func_PAL_002B8898(1);
}



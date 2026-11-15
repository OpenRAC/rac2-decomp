#include "include_asm.h"
#include "names.h"

extern int g_current_game_mode;
extern int g_hud_state __attribute__((section(".sdata")));
extern char g_hud_elements[];
extern void hud_finish_element_setup(char *);

/* The subtitle counters are small data reached through $gp in retail, so this unit is -G8. */
extern int D_L00_001A9070[2] __attribute__((sda));

typedef struct {
    int active;
    int timer;
    int halfWidth;
    int halfHeight;
    int x;
    int y;
    int boxHalfWidth;
    int boxHalfHeight;
    int entryIndex;
    int unk24;
    int pad28[8];
    int unk48;
} SubtitleState;

typedef struct { int unk00; int unk04; int id; int unk0C; } TextEntry;

extern SubtitleState g_subtitle_state;
extern TextEntry *g_subtitle_entries;
extern unsigned short D_001A7B94;
extern int g_screen_height;
extern int g_is_pal_video;
extern void func_2E5E58(int, int, int);
extern void func_2802E0(unsigned short *, int, int, int, int, int, int, int, int);
extern void func_280200(unsigned short *, long long, int, int);
extern int func_1157AC(int);

/* Seeds the subtitle renderer's state from the current text entry and its font metrics. */
void subtitle_init_state(void)
{
    unsigned short metrics[12];
    int textId;
    int screenHeight;

    g_subtitle_state.active = 1;
    g_subtitle_state.timer = 0;
    if (D_001A7B94 != 0)
        func_2E5E58(0, 1, 0);
    textId = g_subtitle_entries[g_subtitle_state.entryIndex].unk00;
    func_2802E0(metrics, 0xF0, 0x1E0, 0x2C, 0x1D4, 0x100, 0x168, 0x10, 7);
    func_280200(metrics, 0x80FFA888LL, textId, -1);
    g_subtitle_state.halfWidth = ((short)metrics[6] >> 1) + 10;
    g_subtitle_state.halfHeight = ((short)metrics[7] >> 1) + 5;
    g_subtitle_state.x = 0x100;
    g_subtitle_state.y = D_L00_001A9070[g_is_pal_video];
    g_subtitle_state.boxHalfWidth = 8;
    g_subtitle_state.boxHalfHeight = 8;
    g_subtitle_state.unk48 = 0;
    if (textId != 0)
        g_subtitle_state.unk48 = func_1157AC(textId) * 7;
    screenHeight = g_screen_height;
    g_subtitle_state.y = screenHeight - 0x3C;
    if (screenHeight - 0xC < g_subtitle_state.y + g_subtitle_state.halfHeight) {
        int boxBottom = g_subtitle_state.halfHeight + 0xC;
        g_subtitle_state.y = screenHeight - boxBottom;
    }
}

extern char *ref_L00_0028B338_00 __attribute__((sda));
extern int D_001A8D44 __attribute__((sda));
extern char *D_001B1B5C;
extern char *D_001B1B60;
extern int D_001B1B64;
extern int D_001B1B6C;
extern char *D_001B18D8;
extern char *D_001B18DC;
extern int D_001B18E0;
extern int D_001B18E4;

/* Switches between two saved sets of buffer pointers when the requested index differs from the current one. */
void select_moby_context(int requested)
{
    int state = D_001A8D44;
    if (requested != state) {
        char *first;
        char *second;
        int third, fourth, active_fourth;
        char *active_first = ref_L00_0028B338_00;
        requested = state ^ 1;
        first = *(char *volatile *)&D_001B18D8;
        *(char *volatile *)&D_001B18D8 = active_first;
        active_first = *(char *volatile *)&D_001B1B60;
        second = *(char *volatile *)&D_001B18DC;
        *(char *volatile *)&D_001B18DC = active_first;
        active_first = (char *)*(volatile int *)&D_001B1B64;
        third = *(volatile int *)&D_001B18E0;
        active_fourth = *(volatile int *)&D_001B1B6C;
        fourth = *(volatile int *)&D_001B18E4;
        *(volatile int *)&D_001A8D44 = requested;
        *(char *volatile *)&D_001B1B5C = first;
        *(char *volatile *)&D_001B1B60 = second;
        *(volatile int *)&D_001B1B64 = third;
        *(volatile int *)&D_001B18E0 = (int)active_first;
        *(volatile int *)&D_001B1B6C = fourth;
        *(volatile int *)&D_001B18E4 = active_fourth;
    }
}

/* Sets up a HUD slot with a new item and its parameters. Returns the slot serial number, unchanged if nothing differs. */
int hud_set_slot_contents(int slot, int id, int callback, int value1, int value2, int value3, int value4)
{
    int index = slot & 15;
    char *slotData = g_hud_elements + index * 0x90;
    int flags = slot & 0xfff0;
    int refresh;
    int serial;
    if (g_current_game_mode == 5 && index != 2 && index != 0) return 0;
    if (*(int *)(slotData + 0x2c) == value3 && *(int *)(slotData + 0x28) == value4 &&
        *(int *)(slotData + 0x20) == id && *(int *)(slotData + 0x24) == flags &&
        *(int *)(slotData + 0x30) == callback && *(int *)(slotData + 0x34) == value1 &&
        *(int *)(slotData + 0x38) == value2) return *(int *)(slotData + 0x64);
    serial = g_hud_state;
    *(int *)(slotData + 0x2c) = value3;
    refresh = flags & *(int *)(slotData + 4);
    *(int *)(slotData + 0x64) = serial;
    refresh &= 0x20;
    serial++;
    *(int *)(slotData + 0x28) = value4;
    *(int *)(slotData + 0x20) = id;
    *(int *)(slotData + 0x30) = callback;
    *(int *)(slotData + 0x34) = value1;
    *(int *)(slotData + 0x38) = value2;
    g_hud_state = serial;
    *(int *)(slotData + 0x68) = 1;
    *(int *)(slotData + 0x24) = flags;
    *(int *)(slotData + 0x7c) = 0;
    *(int *)(slotData + 0x70) = 0;
    if (refresh) hud_finish_element_setup(slotData);
    return *(int *)(slotData + 0x64);
}

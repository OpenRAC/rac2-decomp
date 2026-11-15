#include "include_asm.h"
#include "names.h"

/* func_US2_002CAC28, the v2.00 copy of func_002C9CF8: the same C, plus a flag at 0x1F4. The flag is
   cleared unless func_US2_002B5B30() is 4 and func_002857B0() is 8, it skips func_00132AF8,
   func_002B72E8 and func_00132028 while set, and it is cleared again at the end. */

extern char g_pause_menu_state[];

extern int g_current_game_mode __attribute__((sda));
extern int D_001A7A08 __attribute__((sda));
extern char D_00259918[];
extern char D_00259AF8[];
extern char D_00259AA8[];
extern int g_current_map_index __attribute__((sda));
extern int D_0025B5F8;
extern int func_US2_002B5B30(void);
extern int menu_get_mode(void);
extern void snd_send_cmd22(int);
extern void music_Pause(int);
extern int snd_Pump(void);
extern void func_US2_002CBED0(void);
extern void map_set_current_and_refresh(int);
extern int menu_update_entry_states(void);
extern void func_US2_002DFE60(void);

typedef struct {
    char pad[0x38];
    char *next;
    char *previous;
} Links_2C9CF8;

typedef struct {
    int f0, pad4, f8;
    char padC[0x10];
    int f1C, f20;
    char pad24[0xB7];
    char byteDB;
    char padDC[0xC];
    int fE8;
    char padEC[0x18];
    unsigned int f104;
    int f108;
    char pad10C[0x14];
    int f120;
    char pad124[0x20];
    int f144, f148, f14C, f150;
    char pad154[0x6C];
    int f1C0, f1C4, f1C8;
    char pad1CC[0x28];
    int f1F4;
} State_2C9CF8;

void func_US2_002CAC28(int mode)
{
    if (func_US2_002B5B30() != 4 || menu_get_mode() != 8)
        ((State_2C9CF8 *)g_pause_menu_state)->f1F4 = 0;
    if (!((State_2C9CF8 *)g_pause_menu_state)->f1F4) {
        snd_send_cmd22(0x5D);
        music_Pause(0);
    }
    ((State_2C9CF8 *)g_pause_menu_state)->byteDB = 0;
    if (!((State_2C9CF8 *)g_pause_menu_state)->f1F4)
        snd_Pump();
    ((State_2C9CF8 *)g_pause_menu_state)->f0 = 1;
    if (!g_current_game_mode) func_US2_002CBED0();
    ((State_2C9CF8 *)g_pause_menu_state)->f144 = 0;
    ((State_2C9CF8 *)g_pause_menu_state)->f148 = 0;
    ((State_2C9CF8 *)g_pause_menu_state)->fE8 = (D_001A7A08 & 0xFFFF0000) || ((State_2C9CF8 *)g_pause_menu_state)->f108 ? 1 : 0;
    ((Links_2C9CF8 *)D_00259918)->next = ((State_2C9CF8 *)g_pause_menu_state)->fE8 ? D_00259AF8 : D_00259AA8;
    ((Links_2C9CF8 *)D_00259AA8)->previous = ((State_2C9CF8 *)g_pause_menu_state)->fE8 ? D_00259AF8 : D_00259918;
    ((State_2C9CF8 *)g_pause_menu_state)->f8 = ((State_2C9CF8 *)g_pause_menu_state)->f104 ? (int)((State_2C9CF8 *)g_pause_menu_state)->f104 : mode;
    ((State_2C9CF8 *)g_pause_menu_state)->f1C = 0;
    ((State_2C9CF8 *)g_pause_menu_state)->f20 = 0;
    ((State_2C9CF8 *)g_pause_menu_state)->f120 = 0;
    ((State_2C9CF8 *)g_pause_menu_state)->f1C0 = 0;
    ((State_2C9CF8 *)g_pause_menu_state)->f1C4 = 0;
    ((State_2C9CF8 *)g_pause_menu_state)->f1C8 = 0;
    if (mode != 6) {
        map_set_current_and_refresh(g_current_map_index);
        menu_update_entry_states();
        D_0025B5F8 = 0;
        func_US2_002DFE60();
    }
    ((State_2C9CF8 *)g_pause_menu_state)->f1F4 = 0;
    ((State_2C9CF8 *)g_pause_menu_state)->f150 = 0;
    ((State_2C9CF8 *)g_pause_menu_state)->f14C = 1;
}

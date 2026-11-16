#include "common.h"

/* func_PAL_0029C8A0, the PAL copy of func_0029BF08: the same C, where the callback tables move
   up by 0x738 and the camera scale moves. */
extern int ref_L00_0030CFE0_00[] __attribute__((sda));
extern int g_current_game_mode[] __attribute__((sda));
extern char *g_resident_data_base[] __attribute__((sda));
extern unsigned int menu_get_saved_state(void);
extern unsigned int menu_get_mode(void);
extern void hud_update_letterbox_bars(void);
extern void func_0029BEB8(void);
extern void func_0029BE88(void);
extern void UpdateViewContext(void);

typedef unsigned int (*Cb)(void);

typedef struct { void *cb; int pad; } SlotBf;
typedef struct {
    char pad0[0x7A84];
    void *cb1;
    char pad1[0x7AA4 - 0x7A88];
    void *cb2;
    char pad2[0x7AAC - 0x7AA8];
    SlotBf slot[4];
    SlotBf slot2[2];
} SubBf;

/* The same table seen from its other end: the callback pointer is the second word. */
typedef struct { int pad; void *fn; } FnBf;

typedef struct { char pad[0xB0]; float scale; } CamBf;

/* The camera object: its projection scale is at +0xB0. */
extern CamBf ref_L00_0030CFE0_01;

void level_run_callbacks_and_draw_pal(void)
{
    int result;
    int i;
    Cb fn;
    SubBf *sub;
    char *g;
    float saved;

    if (ref_L00_0030CFE0_00[0] != 0)
        return;

    if (g_resident_data_base[0] == 0)
        goto states;

    if (g_current_game_mode[0] == 4) {
        if (menu_get_mode() == 8)
            return;
    }

    hud_update_letterbox_bars();
    result = 0;
    func_0029BEB8();

    fn = (Cb)((SubBf *)(g_resident_data_base[0] + 0x38000))->cb2;
    if (fn != 0)
        result = fn() != 0;

    for (i = 0; i < 4; i++) {
        sub = (SubBf *)(g_resident_data_base[0] + 0x38000);
        if (sub->slot[i].cb != 0)
            result |= ((Cb)((FnBf *)(g_resident_data_base[0] + 0x3FAA8))[i].fn)();
    }

    for (i = 0; i < 2; i++) {
        sub = (SubBf *)(g_resident_data_base[0] + 0x38000);
        if (sub->slot2[i].cb != 0)
            result |= ((Cb)((FnBf *)(g_resident_data_base[0] + 0x3FAC8))[i].fn)();
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
        g = (char *)((SubBf *)b)->cb1;
        ((Cb)g)();
        saved = ref_L00_0030CFE0_01.scale;
        ref_L00_0030CFE0_01.scale = 0.62f;
        UpdateViewContext();
        func_0029BE88();
        ref_L00_0030CFE0_01.scale = saved;
        UpdateViewContext();
    }
}

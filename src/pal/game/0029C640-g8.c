#include "include_asm.h"
#include "names.h"

extern int ref_L00_0030CDB0_00[] __attribute__((sda));
extern int g_current_game_mode[] __attribute__((sda));
extern char *g_resident_data_base[] __attribute__((sda));
extern int func_PAL_0029C498(void);
extern unsigned int level_get_word_a(void);
extern void module_l00_call_handler_pal(void);
typedef int (*Fn)(void);
typedef struct { void *cb; int pad; } Slot;
typedef struct {
    char pad0[0x7A88];
    void *cb1;
    char pad1[0x7368 - 0x7354];
    void *cb2;
    char pad2[0x7370 - 0x736C];
    Slot slot[4];
    Slot slot2[2];
} Sub;

void func_PAL_0029C640(void)
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
    func_PAL_0029C498();
    fn = (Fn)((Sub *)(g_resident_data_base[0] + 0x38000))->cb2;
    if (fn != 0) {
        if (fn() != 0)
            return;
    }
    result = 0;
    for (i = 0; i < 4; i++) {
        sub = (Sub *)(g_resident_data_base[0] + 0x38000);
        if (sub->slot[i].cb != 0)
            result |= ((Fn *)(g_resident_data_base[0] + 0x3FAA8))[i * 2]();
    }
    if (result != 0)
        return;
    for (i = 0; i < 2; i++) {
        sub = (Sub *)(g_resident_data_base[0] + 0x38000);
        if (sub->slot2[i].cb != 0)
            result |= ((Fn *)(g_resident_data_base[0] + 0x3FAC8))[i * 2]();
    }
    if (result != 0)
        return;
states:
    if (g_current_game_mode[0] != 0 && g_current_game_mode[0] != 5) {
        if (g_current_game_mode[0] == 4) {
            if (level_get_word_a() != 7)
                return;
        }
    }
    g = g_resident_data_base[0];
    if (g != 0) {
        char *b = g + 0x38000;
        g = (char *)((Sub *)b)->cb1;
        ((Fn)g)();
        module_l00_call_handler_pal();
    }
}

#include "include_asm.h"
#include "names.h"
typedef struct {
    char reserved00[0x14];
    char *source;
    int value;
    char reserved1c[0x118];
    int fallback;
} CallbackState;
extern CallbackState g_pause_menu_state;
extern int D_00138344;
typedef struct {
    char pad0[0x44];
    int f44;
    char pad48[8];
    int f50;
    int f54;
    int f58;
} State_0025E2B8_002CD720;
extern State_0025E2B8_002CD720 D_0025E2B8;
extern char *D_0025E284;
extern int D_0025E464;
extern short D_001A63AC;
extern char *D_001A8CFC[] __attribute__((sda));
extern int menu_get_setting_value(void);
extern int func_0029C480(int);
extern char *D_001A8CFC[] __attribute__((sda));

/* The same flag dispatch as func_002CD660 between two reads of func_00336EF0, then, when
   D_001A8CFC[0] is set, clears bit 2 of the word at D_0025E284 + 0x10 if the two reads agree,
   D_001A63AC is clear and the state at D_0025E2B8 matches one of its two modes, and sets it
   otherwise. The unit is built with -frac2-gcse-unsplit-edges (config/cflags.txt): the high
   half of D_0025E2B8 is computed once before the compare, as in retail. */
int func_PAL_002CE6C0(void) {
    int result = 0;
    int result1;
    int result2;
    int flags;
    int value;

    result1 = menu_get_setting_value();
    flags = D_00138344;
    if (flags & 0x10) {
        value = *(int *)(g_pause_menu_state.source + 0xE0);
        if (value != 0)
            g_pause_menu_state.value = value;
        else if (g_pause_menu_state.fallback == 0) {
            result = -1;
            goto after_first;
        }
        result = 0;
    } else if (flags & 0x900) {
        result = 1;
    } else {
        func_0029C480(flags);
    }
after_first:
    if (D_001A8CFC[0] == 0)
        return result;
    result2 = menu_get_setting_value();
    if (result1 == result2 && D_001A63AC == 0 &&
        ((D_0025E2B8.f50 == result1 && D_0025E2B8.f44 == 2) ||
         (D_0025E2B8.f54 == result1 && D_0025E2B8.f44 == 4)))
        *(int *)(D_0025E284 + 0x10) &= ~4;
    else
        *(int *)(D_0025E284 + 0x10) |= 4;
    if (result2 != result1)
        D_0025E464 = -0x22C;
    D_0025E2B8.f58 = menu_get_setting_value();
    return result;
}

extern void *grid_menu_get_selected_text_id(void *);

int func_PAL_002CE818(char *object) {
    if (D_001A8CFC[0] != 0)
        *(void **)(object + 0x34) = grid_menu_get_selected_text_id(D_001A8CFC[0] + 0x3A0B0);
    return 0;
}

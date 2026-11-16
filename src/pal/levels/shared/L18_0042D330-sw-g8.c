#include "common.h"

/* func_PAL_L18_0042D330, the PAL copy of func_L18_004286D0: the same C, with the halfword control
   scaled to 50 Hz. */
extern void STUB_printf(void *);

extern int g_enemy_timer_reset_value __attribute__((sda));

extern u8 g_str_debug_stub[];

void func_PAL_L18_0042D330(u8 *a0) {
    u8 *state = *(u8 **)(a0 + 0x68);
    switch (*(s16 *)(a0 + 0xAA)) {
        case 0xEC0:
            *(u16 *)(state + 0x392) = (g_enemy_timer_reset_value * 5 + 2) / 6;
            break;
        case 0xED4:
            break;
        case 0xEE1:
            break;
        default:
            STUB_printf(g_str_debug_stub);
            break;
    }
}

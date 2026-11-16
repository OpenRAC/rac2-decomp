#include "common.h"

/* func_PAL_L18_0042D330, the PAL copy of func_L18_004286D0: the same C, with the halfword control
   scaled to 50 Hz. */
extern void STUB_printf(void *);

extern int g_enemy_timer_reset_value __attribute__((sda));

extern u8 g_str_debug_stub[];

/* Resets the enemy timer for its kind: the first kind gets the timer reset value, the others do nothing (PAL: 50 Hz scale). */
void enemy_reset_timer_by_kind_pal(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    switch (*(s16 *)(moby + 0xAA)) {
        case 0xEC0: /* moby class 3776 */
            *(u16 *)(vars + 0x392) = (g_enemy_timer_reset_value * 5 + 2) / 6;
            break;
        case 0xED4: /* moby class 3796 */
            break;
        case MOBY_CLASS_RECEIVER_BOT:
            break;
        default:
            STUB_printf(g_str_debug_stub);
            break;
    }
}

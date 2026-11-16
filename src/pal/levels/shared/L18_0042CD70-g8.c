#include "names.h"
/* func_PAL_L18_0042CD70, the PAL copy of func_L18_00428138: the same C, with 50 Hz rate constants and the 5/6 scale on D_L18_001B1240. */
#include "common.h"
extern int g_hero_frozen_flag;
typedef struct { u8 pad[0x1E0]; s16 guard; u8 pad2[0x20B2]; int mode; } Player;
extern Player g_player_l18_state;
extern float g_shot_range_receiver __attribute__((sda));
extern float g_shot_range_default __attribute__((sda));
extern float g_enemy_notice_distance __attribute__((sda));
extern int g_enemy_timer_reset_value __attribute__((sda));
extern u8 g_enemy_notice_data[];
extern float func_00308AD0(void *, void *);
extern void func_003476C8(void *, float, float, float, float);
extern void moby_start_or_forward_anim_pal(void *, int, int, float);
extern void func_00335668(void *, int, int);
extern void func_002C27F0(void *, int);
/* Checks whether the player is close enough for the enemy to notice. If so, it starts the alert move and returns 1 (PAL: 50 Hz rates). */
int enemy_try_notice_player_pal(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    float range;
    if (g_hero_frozen_flag || g_player_l18_state.guard || g_player_l18_state.mode == 0x6F) return 0;
    range = g_shot_range_receiver;
    switch (*(s16 *)(moby + 0xAA)) {
    case 0xEC0: /* moby class 3776 */
        if (func_00308AD0(moby + 0x10, vars + 0x220) < g_enemy_notice_distance && !*(s16 *)(vars + 0x396) && !g_hero_frozen_flag && g_player_l18_state.mode != 0x6F) {
            func_003476C8(moby, *(float *)(vars + 0x3CC) * 0.00040000002f, *(float *)(vars + 0x3C8) * 0.020000001f, *(float *)(vars + 0x3DC) * 6.981318e-06f, *(float *)(vars + 0x3D8) * 0.0003490659f);
            *(u16 *)(vars + 0x392) = (g_enemy_timer_reset_value * 5 + 2) / 6;
            moby_start_or_forward_anim_pal(moby, 10, 0, 10.0f);
            func_00335668(moby, 6, -1);
            return 1;
        }
        return 0;
    case 0xED4: /* moby class 3796 */
        range = g_shot_range_default;
    case MOBY_CLASS_RECEIVER_BOT:
        if (func_00308AD0(moby + 0x10, vars + 0x220) < range && !*(s16 *)(vars + 0x396) && !g_hero_frozen_flag && g_player_l18_state.mode != 0x6F) {
            moby_start_or_forward_anim_pal(moby, 10, 0, 10.0f);
            func_00335668(moby, 6, -1);
            return 1;
        }
        return 0;
    default:
        func_002C27F0(g_enemy_notice_data, *(s16 *)(moby + 0xAA));
        return 0;
    }
}

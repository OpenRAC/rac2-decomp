#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef short s16;
typedef int s32;
extern u8 g_beam_target_vec[];
extern u8 *g_moby_l18_table[] __attribute__((sda));
extern s32 g_max_l18_group_index[] __attribute__((sda));
extern s32 g_current_map_index __attribute__((sda));
extern u8 g_moby_group_flags[];
extern s32 IsPointInCuboid(u8 *, s32);
extern s32 CollLine(void *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4);
extern u8 *g_moby_l18_table[] __attribute__((sda));
extern s32 g_max_l18_group_index[] __attribute__((sda));
extern u8 g_data_block_base[];

s32 extermibot_is_cooldown_finished_pal(s32 a0) {
    u8 *v1 = (u8 *)*(s32 *)(a0 + 0x68);
    s32 r = 0;
    if (*(s16 *)(v1 + 0x7FC) != 0) {
        if (*(s16 *)(v1 + 0x804) < 0x7E) goto done;
    }
    r = 1;
done:
    return r;
}


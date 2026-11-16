#include "include_asm.h"

#include "common.h"
extern u16 *g_moby_l12_group_lists[];
extern u8 *g_moby_list_start MACRO_ADDR;
typedef unsigned int u128 __attribute__((mode(TI)));
extern f32 mat_fast_helper_a(f32, f32);
extern f32 math_random_float_range(f32, f32);
extern void anim_start_blended_pal(void *, s32, s32, s32);
extern void func_002A0F48(void *);

/* Finds an idle launch object in the given group and starts it moving from a position toward a target. Returns 1 when one was started. */
s32 space_tourist_launch_pal(s32 group_id, void *start_pos, void *target_pos)
{
    f32 start_vec[4] __attribute__((aligned(16))), target_vec[4] __attribute__((aligned(16)));
    f32 *start_ptr = start_vec, *target_ptr = target_vec;
    u16 *group_list;
    s32 result = 0;
    group_list = g_moby_l12_group_lists[group_id];
    *(u128 *)start_vec = *(u128 *)start_pos;
    *(u128 *)target_vec = *(u128 *)target_pos;
    if (!group_list) return 0;
    do {
        u16 entry = *group_list;
        u8 *moby = g_moby_list_start + ((entry & 0x7FFF) << 8);
        if (*(s16 *)(moby + 0xAA) == MOBY_CLASS_SPACE_TOURIST && moby[0x20] == 1) {
            u8 *vars = *(u8 **)(moby + 0x68);
            result = 1;
            *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) & 0xFFBE) | 0x1000;
            *(s32 *)(moby + 0x98) = *(s32 *)(*(u8 **)(moby + 0x24) + 0x10);
            qcopy(moby + 0x10, start_ptr);
            qcopy(vars + 0x740, target_ptr);
            *(f32 *)(moby + 0xF8) = mat_fast_helper_a(target_ptr[0] - *(f32 *)(moby + 0x10), target_ptr[1] - *(f32 *)(moby + 0x14));
            *(s32 *)(moby + 0xF0) = 0;
            *(s32 *)(moby + 0xF4) = 0;
            anim_start_blended_pal(moby, 2, 0, 2);
            moby[0x20] = 2;
            *(f32 *)(vars + 0x7AC) = math_random_float_range(5.5f, 6.5f) * 0.020000001f;
            *(s32 *)(vars + 0x794) = 0;
            *(s32 *)(vars + 0x798) = 0;
            func_002A0F48(moby);
            break;
        }
    } while ((s16)*group_list++ >= 0);
    return result;
}

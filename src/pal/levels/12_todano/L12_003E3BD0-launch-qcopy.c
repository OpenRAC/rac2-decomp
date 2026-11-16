#include "include_asm.h"

#include "common.h"
extern u16 *g_moby_l12_group_lists[];
extern u8 *g_moby_list_start MACRO_ADDR;
typedef unsigned int u128 __attribute__((mode(TI)));
extern f32 mat_fast_helper_a(f32, f32);
extern f32 math_random_float_range(f32, f32);
extern void func_PAL_002A7E68(void *, s32, s32, s32);
extern void func_002A0F48(void *);

s32 func_PAL_L12_003E4AC8(s32 id, void *pos, void *target)
{
    f32 p[4] __attribute__((aligned(16))), t[4] __attribute__((aligned(16)));
    f32 *pp = p, *tp = t;
    u16 *list;
    s32 result = 0;
    list = g_moby_l12_group_lists[id];
    *(u128 *)p = *(u128 *)pos;
    *(u128 *)t = *(u128 *)target;
    if (!list) return 0;
    do {
        u16 packed = *list;
        u8 *object = g_moby_list_start + ((packed & 0x7FFF) << 8);
        if (*(s16 *)(object + 0xAA) == 0xBB8 && object[0x20] == 1) {
            u8 *state = *(u8 **)(object + 0x68);
            result = 1;
            *(u16 *)(object + 0x34) = (*(u16 *)(object + 0x34) & 0xFFBE) | 0x1000;
            *(s32 *)(object + 0x98) = *(s32 *)(*(u8 **)(object + 0x24) + 0x10);
            qcopy(object + 0x10, pp);
            qcopy(state + 0x740, tp);
            *(f32 *)(object + 0xF8) = mat_fast_helper_a(tp[0] - *(f32 *)(object + 0x10), tp[1] - *(f32 *)(object + 0x14));
            *(s32 *)(object + 0xF0) = 0;
            *(s32 *)(object + 0xF4) = 0;
            func_PAL_002A7E68(object, 2, 0, 2);
            object[0x20] = 2;
            *(f32 *)(state + 0x7AC) = math_random_float_range(5.5f, 6.5f) * 0.020000001f;
            *(s32 *)(state + 0x794) = 0;
            *(s32 *)(state + 0x798) = 0;
            func_002A0F48(object);
            break;
        }
    } while ((s16)*list++ >= 0);
    return result;
}

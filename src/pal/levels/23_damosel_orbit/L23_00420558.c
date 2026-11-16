#include "include_asm.h"
#include "names.h"

typedef signed int s32;
typedef unsigned long long u64;
extern s32 mothership_is_value_not_in_slots(s32 arg0);
extern s32 math_get_mask_bit(u64, s32);
extern void module_l00_call_handler(void);
extern s32 g_effect_pool_total __attribute__((sda));
extern s32 g_effect_pool_counts[3] __attribute__((sda));
extern s32 g_effect_pools[3][60];
extern s32 g_effect_pool_total __attribute__((sda));
extern s32 g_effect_pool_counts[3] __attribute__((sda));
extern s32 g_effect_pool_limits[4];
extern s32 g_effect_pools[3][60];

/* Calls the measured shared helper and reports success. */
s32 mothership_call_helper_return_true_pal(void) {
    module_l00_call_handler();
    return 1;
}


#include "include_asm.h"

#include "common.h"
typedef unsigned char BatchA_A18_u8;
typedef int BatchA_A18_s32;
extern BatchA_A18_u8 g_screen_mode_flag;
extern BatchA_A18_s32 ref_L18_002E4090_00(BatchA_A18_s32 a0, BatchA_A18_s32 a1);
extern BatchA_A18_s32 point_in_path_xy(BatchA_A18_s32 a0, BatchA_A18_s32 a1, BatchA_A18_s32 a2);
extern BatchA_A18_s32 g_path_pointer_table[];
extern BatchA_A18_s32 g_path_pointer_table[];
extern BatchA_A18_s32 protopet_is_in_either_active_state(BatchA_A18_u8 *s);
extern BatchA_A18_s32 math_random_int_below(BatchA_A18_s32 a0);
extern u8 *protopet_count_group(BatchA_A18_s32 a0, BatchA_A18_u8 *a1);
extern BatchA_A18_s32 path_measure_moby_against_entry(BatchA_A18_u8 *a0, BatchA_A18_s32 a1, float f12);
extern BatchA_A18_s32 path_apply_entry_to_moby(BatchA_A18_u8 *a0, BatchA_A18_s32 a1,
                                        BatchA_A18_s32 a2, BatchA_A18_s32 a3);
extern BatchA_A18_s32 path_get_entry_id(void *a0);

/* runs the 0x1E gate and, when it clears, the record query into a local buffer;
   answers whether the query found anything */
BatchA_A18_s32 protopet_find_for_group_pal(BatchA_A18_u8 *a0) {
    BatchA_A18_u8 buf[16];
    BatchA_A18_s32 p;

    if (math_random_int_below(0x19) == 0) {
        p = *(BatchA_A18_s32 *)(a0 + 0x68);
        return protopet_count_group(*(BatchA_A18_s32 *)((char *)p + 0x25C), buf) != 0;
    }
    return 0;
}


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
extern void func_00335388(BatchA_A18_u8 *a0, BatchA_A18_s32 a1, BatchA_A18_s32 a2,
                          BatchA_A18_s32 a3);
extern void func_002EC9C8(BatchA_A18_u8 *a0, BatchA_A18_s32 a1);
extern BatchA_A18_s32 path_measure_moby_against_entry(BatchA_A18_u8 *a0, BatchA_A18_s32 a1, float f12);
extern BatchA_A18_s32 path_apply_entry_to_moby(BatchA_A18_u8 *a0, BatchA_A18_s32 a1,
                                        BatchA_A18_s32 a2, BatchA_A18_s32 a3);
extern BatchA_A18_s32 path_get_entry_id(void *a0);

/* Starts an animation on the object, or passes the request on when it is in another mode (PAL). */
void moby_start_or_forward_anim_pal(BatchA_A18_u8 *moby, BatchA_A18_s32 anim_or_arg, BatchA_A18_s32 arg2, float speed) {
    if (moby[0xBC] == 0) {
        if (moby[0x43] != anim_or_arg) {
            func_00335388(moby, anim_or_arg, arg2, (BatchA_A18_s32)speed);
        }
    } else {
        func_002EC9C8((BatchA_A18_u8 *)anim_or_arg, arg2);
    }
}

extern void moby_set_controller_speed_limits(BatchA_A18_u8 *, float, float, float, float);
extern int math_fast_float_d(void *a0);
extern int math_fast_float_d(void *a0);

/* the object's scale angles are re-submitted in degrees, then the matrix is rebuilt */
void moby_rebuild_scale_matrix_pal(BatchA_A18_u8 *moby) {
    BatchA_A18_u8 *vars = *(BatchA_A18_u8 **)(moby + 0x68);
    if (moby[0x21] != 0xFF) {
        if (*(BatchA_A18_u8 *)(vars + 0x39F) != 0) {
            moby_set_controller_speed_limits(moby, 0.00040000002f * *(float *)(vars + 0x3C4),
                          0.020000001f * *(float *)(vars + 0x3C0),
                          6.981318e-06f * *(float *)(vars + 0x3D4),
                          0.0003490659f * *(float *)(vars + 0x3D0));
            math_fast_float_d(*(void **)(vars + 0x388));
        }
    }
    *(BatchA_A18_u8 *)(vars + 0x39F) = 0;
}


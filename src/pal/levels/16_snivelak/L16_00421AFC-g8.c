#include "include_asm.h"
#include "names.h"

typedef float f32;
extern f32 g_level_l16_float_param __attribute__((sda));
extern f32 func_002E73F8(f32);
extern f32 g_spark_dir_speed_min __attribute__((sda));
extern f32 g_float_data_unused_a __attribute__((nosda));
extern f32 g_float_data_unused_b __attribute__((nosda));
extern f32 g_float_data_unused_c __attribute__((nosda));
extern f32 g_spark_first_scale __attribute__((sda));
extern f32 g_float_data_unused_d __attribute__((nosda));
extern f32 func_00313F38(f32, f32);
extern f32 g_subobject_spin_param __attribute__((sda));
extern f32 g_subobject_angle_scale __attribute__((sda));
extern void math_update_wrapped_angle_offset(char *, char *, char *, f32, f32, f32);
extern f32 g_quad_packet_value_first __attribute__((sda));
extern f32 g_quad_packet_value_second __attribute__((sda));
extern f32 g_quad_packet_value_third __attribute__((sda));
extern f32 g_quad_packet_value_fourth __attribute__((sda));

/* submits the sub-object at 0x68 with the level's angle scale */
void func_PAL_L16_00421D18(char *arg0) {
    char *p = arg0;
    char *st = *(char **)(p + 0x68);

    math_update_wrapped_angle_offset(p, st + 4, st, g_subobject_spin_param, g_subobject_angle_scale * 0.0003490659f, -1.0f);
}

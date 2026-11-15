#include "include_asm.h"

#include "common.h"
extern void moby_set_state(void *, int, int);
extern int g_active_yeti_count __attribute__((sda));
extern int g_frame_l19_counter;
extern int FloatToInt(float);
extern int math_random_int_below(int);
extern float coll_probe_ground_height_below(void *, int, float);
extern float math_random_signed_float_range(float, float);
extern void moby_set_controller_speed_limits(void *, float, float, float, float);
extern void func_PAL_002A7E68(void *, int, int, int);
extern int func_PAL_002B1A50(void *, void *, int);
extern void group_mark_entities(void *);
extern int weapon_select_aim_target(void *, int, float, float, void *, int);

int func_PAL_L19_00421568(char *obj)
{
    char *data = *(char **)(obj + 0x68);
    if (*(u8 *)(obj + 0x20) == 0) {
        g_active_yeti_count = 0;
        *(u8 *)(data + 0x48) = FloatToInt(15.0f);
        *(u8 *)(data + 0x4A) = FloatToInt(14.4f);
        *(u8 *)(data + 0x29) = 1;
        if (math_random_int_below(2)) *(u16 *)(obj + 0x34)|=0x8000;
        *(float *)(obj + 0x2C)*=1.45f;
        *(float *)(obj + 0x18) = coll_probe_ground_height_below(obj + 0x10, 0, 0.5f);
        *(u16 *)(obj + 0x34) = (*(u16 *)(obj + 0x34)|1)&0xEFFF;
        *(u8 *)(obj + 0x31) = 0;
        *(int *)(obj + 0x98) = 0;
        *(int *)(data + 0x268) = 0;
        *(float *)(data + 0x270) = math_random_signed_float_range(5.0f, 25.0f)*0.0174532942474f;
        qcopy(data + 0x210, obj + 0x10);
        *(u8 *)(data + 0x150) = 25;
        *(int *)(data + 0x188) = 3;
        *(u8 *)(data + 0x156) = 9;
        *(u8 *)(data + 0x151) = 14;
        *(float *)(data + 0x17C) = 0.15f;
        *(float *)(data + 0x30) = 1.5f;
        *(float *)(data + 0x170) = 0.5f;
        *(float *)(data + 0x174) = 0.5f;
        *(u8 *)(data + 0x1B7) = 1;
        *(u8 *)(data + 0x2E) = 1;
        if (*(short *)(data + 0x24) == 0) {
            *(short *)(data + 0x24) = 1;
            *(float *)(data + 0x20) = 1.0f;
        }
        *(float *)(data + 0x84) = 0.5f;
        *(float *)(data + 0x54) = 0.8f;
        *(float *)(data + 0x50) = 1.0f;
        *(float *)(data + 0x58) = 0.75f;
        *(float *)(data + 0x5C) = 0.75f;
        *(float *)(data + 0x60) = 1.57079648972f;
        *(float *)(data + 0x80) = 0.52359885f;
        moby_set_controller_speed_limits(obj, 0.0048f, 0.120000005f, 0.010053098f, 1.0053098f);
        moby_set_state(obj, 1, 0);
        if (*(u8 *)(obj + 0x43) != 12) func_PAL_002A7E68(obj, 12, 0, 0);
    }
    if (*(u8 *)(data + 0x2E) == 2) {
        g_active_yeti_count--;
        return 1;
    }
    if (func_PAL_002B1A50(obj, data + 0x140, 0)) group_mark_entities(obj);
    if (g_frame_l19_counter >= 6) {
        *(int *)(data + 0x278) = weapon_select_aim_target(obj, *(int *)(data + 0x228), *(float *)(data + 0x22C), 10.0f, data + 0x210, 0);
        *(int *)(data + 0x27C) = weapon_select_aim_target(obj, *(int *)(data + 0x220), *(float *)(data + 0x224), 10.0f, data + 0x210, 0);
    }
    return 0;
}

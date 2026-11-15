#include "include_asm.h"

#include "common.h"
extern char *D_L05_001B1EC4, *D_L05_001B251C;
typedef struct {
    char pad[0x7C];
    int timer, flag;
} DriverState;
extern DriverState D_L05_00221D10;
extern char D_L05_002B8770[];
extern float D_L05_001B1A84 __attribute__((sda));
extern float D_L05_001B1A7C __attribute__((sda));
extern float D_L05_001B1A80 __attribute__((sda));
extern float D_L05_001B1BF8 __attribute__((sda));
extern float D_L05_001B1BFC __attribute__((sda));
extern float D_L05_001B1A98 __attribute__((sda));
extern float direction[] SDATA(D_L05_001B1C00);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern float math_step_spring_damper_clamped(float, float, float, float, float, void *);
extern float IntToFloat(int);
extern float math_cosine_blend(float, float, float);
extern float math_wrap_angle_to_pi(float);
extern float FastAddRotations(float, float);
extern float math_fabs(float);
extern void math_build_axis_angle_quat(void *, void *, float);
extern void vec_rotate_by_quaternion(void *, void *, void *);
extern int math_fast_float_d(void *);
extern void slot_copy_records_to_free(void *);
extern void func_PAL_L05_0044B738(void *, void *);
extern void ship_update_aim_point(void *, void *);
extern void moby_sync_equipment_parts(void *);
extern void func_PAL_L05_00449FF0(void *, void *);
extern void func_PAL_L05_0044A970(void *);
extern void gfx_add_draw_callback_first(void *, void *);
extern void gfx_add_draw_callback_third(void *, void *);
extern void func_PAL_L05_0044AED0(void);
extern void ship_draw_aim_crosshair(void);
#define F(p, o) (*(float *)((char *)(p) + (o)))
#define P(p, o) (*(char **)((char *)(p) + (o)))
#define I(p, o) (*(int *)((char *)(p) + (o)))
#define H(p, o) (*(short *)((char *)(p) + (o)))

/* Updates the driven moby position and rebuilds its basis, including bank and roll. */
void func_PAL_L05_00449A28(char *obj)
{
    char old[16] __attribute__((aligned(16)));
    char a[16] __attribute__((aligned(16)));
    char b[16] __attribute__((aligned(16)));
    char c[16] __attribute__((aligned(16)));
    char d[16] __attribute__((aligned(16)));
    char e[16] __attribute__((aligned(16)));
    char rotation[16] __attribute__((aligned(16)));
    char *input = P(obj, 0x70) + 0x50;
    char *moby = D_L05_001B251C +
        (I(P(D_L05_001B1EC4 + H(obj, 0x84) * 32, 0x1C), 0x20) << 8);
    char *state = P(moby, 0x68);
    float t, angle;
    float forward;

    qcopy(old, moby + 0x10);
    forward = D_L05_001B1A7C;
    F(moby, 0x2C) = F(P(moby, 0x24), 0x24) * D_L05_001B1A84;
    FastVecScale(a, obj, forward);
    FastVecAdd(moby + 0x10, obj + 0x30, a);
    FastVecScale(b, obj + 0x20, D_L05_001B1A80);
    FastVecAdd(moby + 0x10, moby + 0x10, b);
    t = -F(input, 0x68) / (F(input, 0x78) * 0.017453294f);
    if (t > 1.0f) t = 1.0f;
    else if (t < -1.0f) t = -1.0f;
    FastVecScale(c, obj + 0x10, F(state, 0x250) * t);
    FastVecAdd(moby + 0x10, moby + 0x10, c);
    t = F(input, 0x64) / (F(input, 0x74) * 0.017453294f);
    if (t < 0.0f) {
        t *= F(state, 0x24C);
        if (t < -1.0f) t = -1.0f;
    } else if (t > 1.0f) {
        t = 1.0f;
    }
    F(state, 0xC) = math_step_spring_damper_clamped(F(state, 0xC), t, D_L05_001B1BF8,
                                  D_L05_001B1BFC, 0.0f, state + 0x10);
    FastVecScale(b, obj + 0x20, F(state, 0x254) * F(state, 0xC));
    FastVecAdd(moby + 0x10, moby + 0x10, b);
    if (D_L05_00221D10.flag) {
        if (!math_fast_float_d(&D_L05_00221D10.timer)) {
            slot_copy_records_to_free(D_L05_002B8770);
        } else {
            D_L05_00221D10.flag = 0;
            D_L05_00221D10.timer = 6;
        }
    }
    func_PAL_L05_0044B738(obj, old);
    ship_update_aim_point(obj, moby);
    FastVecSub(d, state + 0x20, obj + 0x30);
    vec_scale_to_length(d, d, D_L05_001B1A98);
    FastVecAdd(e, obj + 0x30, d);
    FastVecSub(moby + 0xC0, e, moby + 0x10);
    vec_scale_to_length(moby + 0xC0, moby + 0xC0, 1.0f);
    FastVecCross(moby + 0xD0, moby + 0xC0, obj + 0x20);
    vec_scale_to_length(moby + 0xD0, moby + 0xD0, 1.0f);
    FastVecCross(moby + 0xE0, moby + 0xD0, moby + 0xC0);
    I(moby, 0xCC) = 0;
    I(moby, 0xDC) = 0;
    I(moby, 0xEC) = 0;
    angle = (-F(input, 0x68) / (F(input, 0x78) * 0.017453294f)) *
            0.017453294f * F(state, 0x258);
    {
        char *turn = P(obj, 0x70) + 0xD4;
        if (H(turn, 4)) {
            float wave = IntToFloat(H(turn, 6));
            wave = math_cosine_blend(1.0f, 0.0f, wave * F(turn, 8));
            wave = math_wrap_angle_to_pi(wave * 12.566371f);
            if (H(turn, 4) == -1) wave = -wave;
            angle = FastAddRotations(angle, wave);
        }
    }
    if (math_fabs(angle) > 0.00001f) {
        math_build_axis_angle_quat(rotation, moby + 0xC0, angle);
        vec_rotate_by_quaternion(moby + 0xD0, moby + 0xD0, rotation);
        vec_rotate_by_quaternion(moby + 0xE0, moby + 0xE0, rotation);
    }
    FastVecScale(rotation, direction, 0.05f);
    matrix_mul_vec3(rotation, rotation, moby + 0xC0);
    FastVecAdd(moby + 0x10, moby + 0x10, rotation);
    moby_sync_equipment_parts(moby);
    func_PAL_L05_00449FF0(moby, obj);
    func_PAL_L05_0044A970(moby);
    gfx_add_draw_callback_first(func_PAL_L05_0044AED0, moby);
    gfx_add_draw_callback_third(ship_draw_aim_crosshair, moby);
}

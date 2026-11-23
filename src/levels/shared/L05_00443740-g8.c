#include "common.h"

extern char *g_path_l05_entry_table, *g_feltzin_target_mobys;
typedef struct {
    char pad[0x7C];
    int timer, flag;
} DriverState;
extern DriverState g_feltzin_challenge_state;
extern char g_ship_l05_rumble_waves[];
extern float g_ship_moby_scale_factor __attribute__((sda));
extern float g_ship_forward_offset __attribute__((sda));
extern float g_ship_lift_offset_scale __attribute__((sda));
extern float g_ship_lean_spring_stiffness __attribute__((sda));
extern float g_ship_lean_spring_damping __attribute__((sda));
extern float g_cam_look_d_spring_length __attribute__((sda));
/* The direction has an unknown complete extent; only its GP address is needed. */
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
extern int actuator_play_waves(void *);
extern void ResolveLinkedMobyMovementCollisions(void *, void *);
extern void ship_update_aim_point(void *, void *);
extern void moby_sync_equipment_parts(void *);
extern void UpdateShipWeapons(void *, void *);
extern void ship_update_target_lock(void *);
extern void gfx_add_draw_callback_first(void *, void *);
extern void gfx_add_draw_callback_third(void *, void *);
extern void ship_draw_lock_on_reticle(void);
extern void ship_draw_aim_crosshair(void);

#define F(p, o) (*(float *)((char *)(p) + (o)))
#define P(p, o) (*(char **)((char *)(p) + (o)))
#define I(p, o) (*(int *)((char *)(p) + (o)))
#define H(p, o) (*(short *)((char *)(p) + (o)))

/* Updates the driven moby position and rebuilds its basis, including bank and roll. */
void UpdateDrivenMobyTransform(char *obj)
{
    char old_pos[16] __attribute__((aligned(16)));
    char forward_offset[16] __attribute__((aligned(16)));
    char lift_offset[16] __attribute__((aligned(16)));
    char side_offset[16] __attribute__((aligned(16)));
    char spring_offset[16] __attribute__((aligned(16)));
    char smoothed_pos[16] __attribute__((aligned(16)));
    char rotation[16] __attribute__((aligned(16)));
    char *input = P(obj, 0x70) + 0x50;
    char *moby = g_feltzin_target_mobys +
        (I(P(g_path_l05_entry_table + H(obj, 0x84) * 32, 0x1C), 0x20) << 8);
    char *state = P(moby, 0x68);
    float lean_fraction, angle;
    float forward;

    qcopy(old_pos, moby + 0x10);
    forward = g_ship_forward_offset;
    F(moby, 0x2C) = F(P(moby, 0x24), 0x24) * g_ship_moby_scale_factor;
    FastVecScale(forward_offset, obj, forward);
    FastVecAdd(moby + 0x10, obj + 0x30, forward_offset);
    FastVecScale(lift_offset, obj + 0x20, g_ship_lift_offset_scale);
    FastVecAdd(moby + 0x10, moby + 0x10, lift_offset);
    lean_fraction = -F(input, 0x68) / (F(input, 0x78) * 0.017453294f);
    if (lean_fraction > 1.0f) lean_fraction = 1.0f;
    else if (lean_fraction < -1.0f) lean_fraction = -1.0f;
    FastVecScale(side_offset, obj + 0x10, F(state, 0x250) * lean_fraction);
    FastVecAdd(moby + 0x10, moby + 0x10, side_offset);
    lean_fraction = F(input, 0x64) / (F(input, 0x74) * 0.017453294f);
    if (lean_fraction < 0.0f) {
        lean_fraction *= F(state, 0x24C);
        if (lean_fraction < -1.0f) lean_fraction = -1.0f;
    } else if (lean_fraction > 1.0f) {
        lean_fraction = 1.0f;
    }
    F(state, 0xC) = math_step_spring_damper_clamped(F(state, 0xC), lean_fraction, g_ship_lean_spring_stiffness,
                                  g_ship_lean_spring_damping, 0.0f, state + 0x10);
    FastVecScale(lift_offset, obj + 0x20, F(state, 0x254) * F(state, 0xC));
    FastVecAdd(moby + 0x10, moby + 0x10, lift_offset);
    if (g_feltzin_challenge_state.flag) {
        if (!math_fast_float_d(&g_feltzin_challenge_state.timer)) {
            actuator_play_waves(g_ship_l05_rumble_waves);
        } else {
            g_feltzin_challenge_state.flag = 0;
            g_feltzin_challenge_state.timer = 7;
        }
    }
    ResolveLinkedMobyMovementCollisions(obj, old_pos);
    ship_update_aim_point(obj, moby);
    FastVecSub(spring_offset, state + 0x20, obj + 0x30);
    vec_scale_to_length(spring_offset, spring_offset, g_cam_look_d_spring_length);
    FastVecAdd(smoothed_pos, obj + 0x30, spring_offset);
    FastVecSub(moby + 0xC0, smoothed_pos, moby + 0x10);
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
    UpdateShipWeapons(moby, obj);
    ship_update_target_lock(moby);
    gfx_add_draw_callback_first(ship_draw_lock_on_reticle, moby);
    gfx_add_draw_callback_third(ship_draw_aim_crosshair, moby);
}

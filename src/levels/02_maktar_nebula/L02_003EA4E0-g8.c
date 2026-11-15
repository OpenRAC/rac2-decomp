#include "names.h"
/* func_L02_003EA4E0: a Maktar platform's state handler (activation, swing, travel, release and
   the scrolling surface), a nine-state switch. The activation timer is read into one local that
   is incremented and stored while a copy keeps the old value for the test: retail's
   daddu copy / addiu. The usual `timer = field++` gives an andi 0xFFFF instead.
   -O2 -G8 -ffunction-sections (config/cflags.txt). */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern int D_L02_001B0D50 __attribute__((sda));
extern int D_L02_001B0D54 __attribute__((sda));
extern float D_L02_001B0D58 __attribute__((sda));
extern float D_L02_001B0D5C __attribute__((sda));
extern int g_frame_l02_counter;
/* Prefix view of the shared owner flag; the whole object remains unqualified. */
typedef struct { unsigned char pad[3]; unsigned char active; } OwnerFlagView;
extern OwnerFlagView D_001395B8 __attribute__((nosda));
extern char g_sound_state[], D_00189F10[];
extern void swing_platform_init_group(void *);
extern int flag_is_third_pending_set(void *);
extern int MemcardSave(int, int);
extern int PlayMobySound(int, int, void *);
extern void group_set_moby_states_from_mode(void *);
extern float math_fabs(float);
extern int swing_platform_is_leading(void *);
extern void moby_set_state(void *, int, int);
extern int flag_set_first_pending(void *);
extern void euler_rotation_basis(void *, void *);
extern void matrix_from_basis_rows(void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern float math_step_value_toward_target(void *, void *, float, float, float, float);
extern void FastVecAdd(void *, void *, void *);
extern void lerp_vector(void *, void *, void *, float);
extern float FastAddRotations(float, float);
extern int group_are_mobys_settled(void *);
extern void snd_stop_voice(int);
extern void group_reset_moby_hit_points(void *);
extern float ApproachValue(float *, float, float);
extern void vec_scale_to_length(void *, void *, float);
extern int group_update_effect_mobys(void *, void *);
extern float FastVecDot(void *, void *);
extern void gfx_add_draw_callback_first(void (*)(char *), void *);
extern void gfx_draw_energy_sheet(char *);
typedef union { int i[0x20]; float f[0x20]; } PlatState;

/* Updates the platform's activation, swing, travel and scrolling surface. */
void swing_platform_update(char *actor) {
    char *state = *(char **)(actor + 0x68);
    float angles[4], rotation[12], inverse[16], offset[4];
    float speed, distance, target;
    switch (*(unsigned char *)(actor + 0x20)) {
    case 0:
    swing_platform_init_group(actor);
    return;
    case 2:
    if (D_L02_001B0D50 == 0) {
        unsigned int timer, next;
        if (!flag_is_third_pending_set(actor)) return;
        next = *(unsigned short *)(actor + 0x96);
        timer = next;
        next++;
        *(unsigned short *)(actor + 0x96) = next;
        if (timer < 6) return;
    }
    if (*(int *)(state + 4)) { D_001395B8.active = 1; MemcardSave(0, -1); }
    *(int *)(state + 0x2C) = PlayMobySound(0, 4, actor);
    group_set_moby_states_from_mode(actor);
    return;
    case 3:
    if (!(math_fabs((float)g_frame_l02_counter - **(float **)(state + 0x28)) > 10.0f)) return;
    if (swing_platform_is_leading(actor)) {
        **(float **)(state + 0x28) = (float)g_frame_l02_counter;
        moby_set_state(actor, 4, -1);
        *(unsigned short *)(actor + 0x34) = (*(unsigned short *)(actor + 0x34) & 0xFFBE) | 0x1000;
        *(int *)(actor + 0x98) = *(int *)(*(char **)(actor + 0x24) + 0x10);
        *(float *)(state + 0xC) = 0;
    }
    return;
    case 4:
    speed = 0.016666668f;
    if (flag_set_first_pending(actor)) speed = 60.0f;
    qzero(angles);
    angles[2] = *(float *)(state + 0x3C);
    euler_rotation_basis(rotation, angles);
    matrix_from_basis_rows(inverse, rotation);
    FastVecSub(offset, actor + 0x10, state + 0x30);
    matrix_mul_vec3(offset, offset, inverse);
    distance = math_fabs(offset[1]);
    if (distance <= math_fabs(*(float *)(state + 0xC))) {
        offset[1] = 0;
        moby_set_state(actor, 5, -1);
    } else math_step_value_toward_target(offset + 1, state + 0xC, 0.0f, speed, speed, 1.0f);
    matrix_mul_vec3(offset, offset, rotation);
    FastVecAdd(actor + 0x10, state + 0x30, offset);
    return;
    case 5:
    if (flag_set_first_pending(actor)) {
        qcopy(state + 0x40, actor + 0x10);
        *(float *)(state + 0x10) = 0;
        *(float *)(state + 0xC) = 0;
    }
    distance = math_fabs(*(float *)(state + 0x10) - 1.0f);
    if (distance < math_fabs(*(float *)(state + 0xC))) {
        *(float *)(state + 0x10) = 1.0f;
        moby_set_state(actor, 6, -1);
    } else math_step_value_toward_target(state + 0x10, state + 0xC, 1.0f, 0.0027777778f, 0.0027777778f, 0.16666667f);
    lerp_vector(actor + 0x10, state + 0x40, state + 0x30, *(float *)(state + 0x10));
    *(float *)(actor + 0xF8) = FastAddRotations(*(float *)(state + 0x3C), (1.0f - *(float *)(state + 0x10)) * 1.5707965f);
    *(float *)(actor + 0xF0) = (1.0f - *(float *)(state + 0x10)) * 3.1415927f;
    return;
    case 7:
    if (group_are_mobys_settled(actor)) {
        int index = *(int *)(state + 0x2C);
        if (index != -1) {
            char *slot = g_sound_state + index * 0x70;
            if (*(char **)(slot + 0x88) == actor && *(unsigned char *)(slot + 0x74)) snd_stop_voice(index);
        }
        *(int *)(state + 0x2C) = -1;
        group_reset_moby_hit_points(actor);
        moby_set_state(actor, 8, -1);
    }
    return;
    case 8:
    target = (float)D_L02_001B0D54 * 0.06666667f;
    ApproachValue(&D_L02_001B0D58, target, 0.0044444446f);
    vec_scale_to_length(angles, actor + 0xD0, D_L02_001B0D58);
    if (group_update_effect_mobys(actor, angles)) {
        if (D_L02_001B0D58 == target) {
            if (FastVecDot(D_00189F10, angles) < -0.001f) {
                if (++((PlatState *)state)->i[8] > 30) D_L02_001B0D54 = -D_L02_001B0D54;
            } else ((PlatState *)state)->i[8] = 0;
        } else ((PlatState *)state)->i[8] = 0;
    }
    ((PlatState *)state)->f[5] = FastAddRotations(((PlatState *)state)->f[5], D_L02_001B0D5C * 0.00029088825f);
    ((PlatState *)state)->f[6] += D_L02_001B0D58 * 0.5f;
    if (((PlatState *)state)->f[6] > 1.0f) ((PlatState *)state)->f[6] -= 1.0f;
    else if (((PlatState *)state)->f[6] < -1.0f) ((PlatState *)state)->f[6] += 1.0f;
    ApproachValue(&((PlatState *)state)->f[7], 1.0f, 0.016666668f);
    gfx_add_draw_callback_first(gfx_draw_energy_sheet, actor);
    case 1:
    case 6:
        return;
    }
}

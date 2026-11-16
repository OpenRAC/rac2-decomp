#include "include_asm.h"

#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union {
    struct { float origin[4]; float difference[4]; } aim;
    struct { float angles[4]; float original[4]; } rotation;
} JointScratch;
typedef struct {
    char pad0[0x10];
    float position[4];
    unsigned char state;
    char pad21[0x21];
    unsigned char animation;
    unsigned char next_animation;
    char pad44[0x1C];
    unsigned char flags;
    char pad61[7];
    struct TurretState *vars;
    char pad6C[0x50];
    unsigned char emitted;
    char padBD[3];
    float matrix[12];
    float rotation[4];
} TurretObject;
typedef struct TurretState {
    char pad0[0x20];
    float elapsed;
    short duration;
    char pad26[0xE];
    unsigned char damage;
    char pad35[0x14B];
    float left_joint[16];
    float right_joint[16];
    char pad200[0x40];
    char *target;
    int proxy_index;
    float yaw;
    float yaw_speed;
    unsigned int colour;
    unsigned int old_colour;
    unsigned int target_colour;
    float colour_fraction;
    char pad260[0x26];
    short fire_timer;
} TurretState;
extern TurretObject *g_moby_l02_pool __attribute__((sda));
extern int g_frame_l02_counter __attribute__((sda));
extern float g_zero_l02_vector[4] __attribute__((sda));
extern float vec_distance_xy(void *, void *);
extern float mat_fast_helper_a(float, float);
extern float FastDiffRots(float, float);
extern void moby_transform_joint_point(char *, int, char *);
extern void func_PAL_002A0F68(char *);
extern void func_002A0F48(char *);
extern void func_002A10E8(char *);
extern unsigned int math_lerp_int_fraction(unsigned int, unsigned int, float);
extern float math_fast_sin_or_cos_b(float);
extern float math_approach_target_with_direction_mode(float *, float *, int, float, float, float, float);
extern void euler_rotation_basis(void *, void *);
extern void mat_get_euler_angles(float *, float *);
extern void moby_transform_joint_to_world(char *, int, char *);
extern void FastVecSub(void *, void *, void *);
extern float fast_subtract_rotations(float, float);
extern float math_fast_float_g(float);
extern void mat_build_rotation_from_angles(void *, float *);
extern float vec_step_toward_target_limited(void *, void *, float);
extern int FastDecTimer(short *);
extern void anim_start_blended_pal(char *, int, int, int);
extern int FloatToInt(float);
extern float moby_get_anim_value(char *);
extern void vec_scale_to_length(void *, void *, float);
extern unsigned char *projectile_l02_spawn_pal(unsigned char *, int, unsigned char *, float);
#define OBJ (D_L02_001B359C[self->vars->proxy_index])
#define PROXY ((unsigned char *)&OBJ)

/* Update the attached object's colour, aim joints and muzzle emissions. */
void twin_muzzle_turret_update_pal(TurretObject *self)
{
    float target[4];
    float owner_matrix[16];
    JointScratch work;
    float angles[4];
    float orientation[4];
    float first_muzzle[16];
    float second_muzzle[16];
    TurretState *state = self->vars;
    TurretObject *object;
    float distance, yaw, difference, fraction, limit, phase;
    unsigned int colour;
    int mode;

    *(Quadword *)target = 0;
    {
        char *target_object = state->target;
        if (target_object) qcopy(target, target_object + 0x10);
    }
    distance = vec_distance_xy(self->position, target);
    yaw = mat_fast_helper_a(target[0] - self->position[0], target[1] - self->position[1]);
    difference = FastDiffRots(*(float *)(PROXY + 0xF8), yaw);
    moby_transform_joint_point((char *)self, 0, (char *)owner_matrix);
    qcopy_nc(PROXY + 0x10, owner_matrix + 12);
    func_PAL_002A0F68((char *)PROXY);
    func_002A0F48((char *)PROXY);
    func_002A10E8((char *)PROXY);
    if ((state->colour & 0xFFFFFF) != (state->target_colour & 0xFFFFFF)) {
        state->colour = math_lerp_int_fraction(state->old_colour,
                state->target_colour, state->colour_fraction);
        state->colour_fraction += 0.1f;
        if (state->colour_fraction > 1.0f) state->colour_fraction = 1.0f;
    } else {
        state->old_colour = state->target_colour;
        state->colour_fraction = 0;
    }
    phase = math_fast_sin_or_cos_b((float)(g_frame_l02_counter % 120) * 0.052359883f - 3.1415927f);
    colour = (state->colour & 0xFFFFFF)
            | ((int)(phase * phase * (float)*((unsigned char *)&state->target_colour + 3)) << 24);
    state->colour = colour;
    *(unsigned int *)(PROXY + 0x78) = colour;
    if (self->state != 9 && self->state != 10 && self->state != 11 && self->state != 7) {
        fraction = state->elapsed / (float)state->duration;
        limit = (fraction * -330.0f + 360.0f) * 6.981318e-06f;
        math_approach_target_with_direction_mode(&state->yaw, &state->yaw_speed, 0,
                yaw, limit, limit, (fraction * -225.0f + 240.0f) * 0.0003490659f);
        *(Quadword *)work.rotation.original = 0;
        work.rotation.original[2] = state->yaw;
        *(Quadword *)work.rotation.angles = *(Quadword *)work.rotation.original;
        euler_rotation_basis(PROXY + 0xC0, &work);
        object = (TurretObject *)PROXY;
        mat_get_euler_angles(object->matrix, object->rotation);
    }
    mode = self->state;
    if (mode == 5 || (mode == 6 && state->elapsed < (float)state->duration * 0.2f)) {
        moby_transform_joint_to_world((char *)PROXY, 2, (char *)work.aim.origin);
        FastVecSub(work.aim.difference, state->target + 0x10, work.aim.origin);
        limit = vec_distance_xy(state->target + 0x10, work.aim.origin);
        *(Quadword *)angles = 0;
        angles[1] = mat_fast_helper_a(work.aim.difference[2], limit) + -1.5707964f;
        if (angles[1] > 1.5707965f) angles[1] = 1.5707965f;
        else if (angles[1] < -1.5707965f) angles[1] = -1.5707965f;
        if (difference < 0.17453295f) {
            angles[2] = mat_fast_helper_a(work.aim.difference[0], work.aim.difference[1]);
            angles[2] = fast_subtract_rotations(angles[2], *(float *)(PROXY + 0xF8));
            angles[2] = math_fast_float_g(angles[2]);
        }
        if (!(angles[2] > 0.9599312f)) {
            if (angles[2] < -0.13962635f) angles[2] = -0.13962635f;
        } else angles[2] = 0.9599312f;
        mat_build_rotation_from_angles(orientation, angles);
        vec_step_toward_target_limited(state->left_joint, orientation, 0.01f);
        moby_transform_joint_to_world((char *)PROXY, 3, (char *)work.aim.origin);
        FastVecSub(work.aim.difference, state->target + 0x10, work.aim.origin);
        limit = vec_distance_xy(state->target + 0x10, work.aim.origin);
        angles[1] = mat_fast_helper_a(work.aim.difference[2], limit) + -1.5707964f;
        if (angles[1] > 1.5707965f) angles[1] = 1.5707965f;
        else if (angles[1] < -1.5707965f) angles[1] = -1.5707965f;
        if (difference < 0.17453295f) {
            angles[2] = mat_fast_helper_a(work.aim.difference[0], work.aim.difference[1]);
            angles[2] = fast_subtract_rotations(angles[2], *(float *)(PROXY + 0xF8));
            angles[2] = math_fast_float_g(angles[2]);
        }
        if (!(angles[2] > 0.13962635f)) {
            if (angles[2] < -0.9599312f) angles[2] = -0.9599312f;
        } else angles[2] = 0.13962635f;
        mat_build_rotation_from_angles(orientation, angles);
        vec_step_toward_target_limited(state->right_joint, orientation, 0.01f);
        if (FastDecTimer(&state->fire_timer) && distance < 45.0f
                && distance > 0.0f && difference < 3.141593f) {
            if (OBJ.next_animation != 5) anim_start_blended_pal((char *)&OBJ, 5, 0, 2);
            PROXY[0xBC] = 0;
            if (self->state == 5)
                state->fire_timer = ((s32)(FloatToInt((state->elapsed / (float)state->duration) * 40.0f + 20.0f)) * 5 + 2) / 6;
            else state->fire_timer = 50;
        }
    } else {
        vec_step_toward_target_limited(state->left_joint, g_zero_l02_vector, 0.01f);
        vec_step_toward_target_limited(state->right_joint, g_zero_l02_vector, 0.01f);
    }
    switch (PROXY[0x42]) {
    case 0:
        state->target_colour = 0x40FF00EA;
        if (self->state != 5 || !(distance > 45.0f) || !(distance < 0.0f) || !(difference > 3.141593f)) return;
        if (OBJ.next_animation != 1) anim_start_blended_pal((char *)&OBJ, 1, 0, 8);
        return;
    case 1: case 2: case 3: case 4:
        if (!(distance < 45.0f) || !(distance > 0.0f) || !(difference < 3.141593f)) return;
        if (OBJ.next_animation) anim_start_blended_pal((char *)&OBJ, 0, 0, 8);
        return;
    case 5:
        state->target_colour = 0x80FF00EA;
        phase = moby_get_anim_value((char *)PROXY);
        if (!OBJ.emitted && phase > 3.0f && phase < 6.0f) {
            moby_transform_joint_to_world((char *)&OBJ, 0, (char *)work.aim.origin);
            moby_transform_joint_point((char *)PROXY, 0, (char *)first_muzzle);
            FastVecSub(angles, state->target + 0x10, work.aim.origin);
            vec_scale_to_length(angles, angles, 1.0f);
            first_muzzle[2] = angles[2];
            vec_scale_to_length(first_muzzle, first_muzzle, 1.0f);
            projectile_l02_spawn_pal((unsigned char *)work.aim.origin, (int)self, (unsigned char *)first_muzzle,
                    (float)state->damage);
            moby_transform_joint_to_world((char *)PROXY, 1, (char *)work.aim.difference);
            moby_transform_joint_point((char *)PROXY, 1, (char *)second_muzzle);
            FastVecSub(angles, state->target + 0x10, work.aim.difference);
            vec_scale_to_length(angles, angles, 1.0f);
            second_muzzle[2] = angles[2];
            vec_scale_to_length(second_muzzle, second_muzzle, 1.0f);
            projectile_l02_spawn_pal((unsigned char *)work.aim.difference, (int)self, (unsigned char *)second_muzzle,
                    (float)state->damage);
            PROXY[0xBC] = 1;
        }
        if ((OBJ.flags & 2) && OBJ.next_animation) anim_start_blended_pal((char *)&OBJ, 0, 0, 2);
        return;
    case 10:
        state->target_colour = 0x30FF00EA;
        return;
    case 12: case 13:
        state->target_colour = 0xFF000000;
        if (self->state != 11) {
            state->target_colour = 0x8000FFFF;
            state->yaw += state->yaw_speed;
            state->yaw_speed *= 0.97f;
            state->yaw = math_fast_float_g(state->yaw);
            *(Quadword *)work.rotation.original = 0;
            work.rotation.original[2] = state->yaw;
            *(Quadword *)work.rotation.angles = *(Quadword *)work.rotation.original;
            euler_rotation_basis(PROXY + 0xC0, &work);
            object = (TurretObject *)PROXY;
            mat_get_euler_angles(object->matrix, object->rotation);
            return;
        }
        /* State 11 falls through and fails the state 7 guard. */
    case 7:
        if (self->state != 7) return;
        state->target_colour = 0x80806060;
        state->yaw += state->yaw_speed;
        state->yaw_speed *= 0.97f;
        state->yaw = math_fast_float_g(state->yaw);
        *(Quadword *)work.rotation.original = 0;
        work.rotation.original[2] = state->yaw;
        *(Quadword *)work.rotation.angles = *(Quadword *)work.rotation.original;
        euler_rotation_basis(PROXY + 0xC0, &work);
        object = (TurretObject *)PROXY;
        mat_get_euler_angles(object->matrix, object->rotation);
        return;
    }
}

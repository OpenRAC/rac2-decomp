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
    unsigned char nextAnimation;
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
    float leftJoint[16];
    float rightJoint[16];
    char pad200[0x40];
    char *target;
    int proxyIndex;
    float yaw;
    float yawSpeed;
    unsigned int colour;
    unsigned int oldColour;
    unsigned int targetColour;
    float colourFraction;
    char pad260[0x26];
    short fireTimer;
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
extern void func_PAL_002A7E68(char *, int, int, int);
extern int FloatToInt(float);
extern float moby_get_anim_value(char *);
extern void vec_scale_to_length(void *, void *, float);
extern unsigned char *func_PAL_L02_00426700(unsigned char *, int, unsigned char *, float);
#define OBJ (D_L02_001B359C[self->vars->proxyIndex])
#define PROXY ((unsigned char *)&OBJ)

/* Update the attached object's colour, aim joints and muzzle emissions. */
void func_PAL_L02_003DDFD0(TurretObject *self)
{
    float target[4];
    float ownerMatrix[16];
    JointScratch work;
    float angles[4];
    float orientation[4];
    float firstMuzzle[16];
    float secondMuzzle[16];
    TurretState *state = self->vars;
    TurretObject *object;
    float distance, yaw, difference, fraction, limit, phase;
    unsigned int colour;
    int mode;

    *(Quadword *)target = 0;
    {
        char *targetObject = state->target;
        if (targetObject) qcopy(target, targetObject + 0x10);
    }
    distance = vec_distance_xy(self->position, target);
    yaw = mat_fast_helper_a(target[0] - self->position[0], target[1] - self->position[1]);
    difference = FastDiffRots(*(float *)(PROXY + 0xF8), yaw);
    moby_transform_joint_point((char *)self, 0, (char *)ownerMatrix);
    qcopy_nc(PROXY + 0x10, ownerMatrix + 12);
    func_PAL_002A0F68((char *)PROXY);
    func_002A0F48((char *)PROXY);
    func_002A10E8((char *)PROXY);
    if ((state->colour & 0xFFFFFF) != (state->targetColour & 0xFFFFFF)) {
        state->colour = math_lerp_int_fraction(state->oldColour,
                state->targetColour, state->colourFraction);
        state->colourFraction += 0.1f;
        if (state->colourFraction > 1.0f) state->colourFraction = 1.0f;
    } else {
        state->oldColour = state->targetColour;
        state->colourFraction = 0;
    }
    phase = math_fast_sin_or_cos_b((float)(g_frame_l02_counter % 120) * 0.052359883f - 3.1415927f);
    colour = (state->colour & 0xFFFFFF)
            | ((int)(phase * phase * (float)*((unsigned char *)&state->targetColour + 3)) << 24);
    state->colour = colour;
    *(unsigned int *)(PROXY + 0x78) = colour;
    if (self->state != 9 && self->state != 10 && self->state != 11 && self->state != 7) {
        fraction = state->elapsed / (float)state->duration;
        limit = (fraction * -330.0f + 360.0f) * 6.981318e-06f;
        math_approach_target_with_direction_mode(&state->yaw, &state->yawSpeed, 0,
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
        vec_step_toward_target_limited(state->leftJoint, orientation, 0.01f);
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
        vec_step_toward_target_limited(state->rightJoint, orientation, 0.01f);
        if (FastDecTimer(&state->fireTimer) && distance < 45.0f
                && distance > 0.0f && difference < 3.141593f) {
            if (OBJ.nextAnimation != 5) func_PAL_002A7E68((char *)&OBJ, 5, 0, 2);
            PROXY[0xBC] = 0;
            if (self->state == 5)
                state->fireTimer = ((s32)(FloatToInt((state->elapsed / (float)state->duration) * 40.0f + 20.0f)) * 5 + 2) / 6;
            else state->fireTimer = 50;
        }
    } else {
        vec_step_toward_target_limited(state->leftJoint, g_zero_l02_vector, 0.01f);
        vec_step_toward_target_limited(state->rightJoint, g_zero_l02_vector, 0.01f);
    }
    switch (PROXY[0x42]) {
    case 0:
        state->targetColour = 0x40FF00EA;
        if (self->state != 5 || !(distance > 45.0f) || !(distance < 0.0f) || !(difference > 3.141593f)) return;
        if (OBJ.nextAnimation != 1) func_PAL_002A7E68((char *)&OBJ, 1, 0, 8);
        return;
    case 1: case 2: case 3: case 4:
        if (!(distance < 45.0f) || !(distance > 0.0f) || !(difference < 3.141593f)) return;
        if (OBJ.nextAnimation) func_PAL_002A7E68((char *)&OBJ, 0, 0, 8);
        return;
    case 5:
        state->targetColour = 0x80FF00EA;
        phase = moby_get_anim_value((char *)PROXY);
        if (!OBJ.emitted && phase > 3.0f && phase < 6.0f) {
            moby_transform_joint_to_world((char *)&OBJ, 0, (char *)work.aim.origin);
            moby_transform_joint_point((char *)PROXY, 0, (char *)firstMuzzle);
            FastVecSub(angles, state->target + 0x10, work.aim.origin);
            vec_scale_to_length(angles, angles, 1.0f);
            firstMuzzle[2] = angles[2];
            vec_scale_to_length(firstMuzzle, firstMuzzle, 1.0f);
            func_PAL_L02_00426700((unsigned char *)work.aim.origin, (int)self, (unsigned char *)firstMuzzle,
                    (float)state->damage);
            moby_transform_joint_to_world((char *)PROXY, 1, (char *)work.aim.difference);
            moby_transform_joint_point((char *)PROXY, 1, (char *)secondMuzzle);
            FastVecSub(angles, state->target + 0x10, work.aim.difference);
            vec_scale_to_length(angles, angles, 1.0f);
            secondMuzzle[2] = angles[2];
            vec_scale_to_length(secondMuzzle, secondMuzzle, 1.0f);
            func_PAL_L02_00426700((unsigned char *)work.aim.difference, (int)self, (unsigned char *)secondMuzzle,
                    (float)state->damage);
            PROXY[0xBC] = 1;
        }
        if ((OBJ.flags & 2) && OBJ.nextAnimation) func_PAL_002A7E68((char *)&OBJ, 0, 0, 2);
        return;
    case 10:
        state->targetColour = 0x30FF00EA;
        return;
    case 12: case 13:
        state->targetColour = 0xFF000000;
        if (self->state != 11) {
            state->targetColour = 0x8000FFFF;
            state->yaw += state->yawSpeed;
            state->yawSpeed *= 0.97f;
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
        state->targetColour = 0x80806060;
        state->yaw += state->yawSpeed;
        state->yawSpeed *= 0.97f;
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

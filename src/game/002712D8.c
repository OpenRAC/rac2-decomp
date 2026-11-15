#include "common.h"
typedef struct {float v[4];} Vec;
typedef struct {Vec basis[3]; Vec pos;} Camera;
typedef struct {float yaw,pitch,dist; int frames_left; float inv_frames; int frames; char pad[8]; Vec fwd,up,rot,pos,saved_rot;} CamBlendOrbit;
extern unsigned char D_001B5490[];
extern char D_00189E20[];
extern Vec D_00189EA0[], D_001B5340[], D_001B5570[], D_0018A0E0[];
extern float func_002A7C00(float,float,float);
extern void func_00282DD8(void*,void*,void*);
extern void func_00270B58(float*,void*,void*,void*,void*,void*);
extern void func_00282F20(void*,void*,float);
extern float func_00283BE0(float,float), func_00283B98(float,float);
extern void func_002ACEC0(void*,void*,void*,float);
extern void func_00282D30(void*,void*,float), func_00282CF0(void*,void*,void*);
extern float func_00282DB0(void*,void*), func_00282DF0(void*), func_002831B0(float), func_00282C48(float);
extern void func_002AB668(void*,void*,float), func_002ACDE8(void*,void*,void*);
extern int func_00282948(void*);
extern void func_00283958(void*,void*), func_002AB600(void*,void*), func_00282CC0(void*,void*,void*);
/* Adapted from RAC1 advance_alternate_camera_transition, GPL-3.0. */
/* Moves the camera around an orbit toward its goal each frame; returns 1 when the move is finished. */
int func_002712D8(Camera *cam, CamBlendOrbit *orbit) {
    Vec ang;
    Vec fwd;
    Vec side;
    Vec up;
    Vec target;
    Vec pos;
    Vec diff;
    Vec proj;
    Vec axes[3];
    Vec r0;
    Vec r1;
    Vec r2;
    Vec tempRot;
    float step;
    float dyaw;
    float dpitch;
    float yaw;
    float turn;
    float sign;
    float pitchSign;
    float d;
    char *hero;

    if (orbit->frames_left <= 0) {
        return 1;
    }
    step = 1.0f / CosineBlend(1.0f, (float)orbit->frames, (float)orbit->frames_left * orbit->inv_frames);
    if (D_001B5490[2] == 2) {
        qcopy(&target, gHeroPosition);
        qcopy(&fwd, &orbit->fwd);
        qcopy(&up, &orbit->up);
        FastVecCross(&side, &fwd, &up);
        ComputeAimAngles(ang.v, &cam->pos, &target, &fwd, &side, &up);
    } else {
        qcopy(&target, &cam->pos);
        hero = gHeroState;
        vec_scale_to_length(&fwd, *(char **)(hero + 0x2290) + 0xC0, 1.0f);
        vec_scale_to_length(&up, *(char **)(hero + 0x2290) + 0xE0, 1.0f);
        ang.v[2] = 0.0f;
        ang.v[1] = 0.0f;
        ang.v[0] = 3.1415927f;
    }
    dyaw = fast_subtract_rotations(ang.v[0], orbit->yaw);
    orbit->yaw = FastAddRotations(orbit->yaw, dyaw * step);
    dpitch = fast_subtract_rotations(ang.v[1], orbit->pitch);
    orbit->pitch = FastAddRotations(orbit->pitch, dpitch * step);
    orbit->dist = orbit->dist + (ang.v[2] - orbit->dist) * step;
    vec_scale_to_length(&pos, &fwd, orbit->dist);
    ApplyAxisRotationToQuaternion(&pos, &pos, &up, orbit->yaw);
    FastVecCross(&side, &pos, &up);
    vec_scale_to_length(&side, &side, 1.0f);
    ApplyAxisRotationToQuaternion(&pos, &pos, &side, orbit->pitch);
    FastVecAdd(&orbit->pos, &target, &pos);
    qcopy(gCameraState_001B5340, &orbit->pos);
    quaternion_to_rotation_basis(&orbit->rot, axes);
    d = FastVecDot(&axes[2], cam);
    FastVecScale(&proj, &axes[2], d);
    FastVecSub(&diff, cam, &proj);
    yaw = 1.57079637f - FastAngleHelper(FastVecDot(&axes[0], &diff) / FastVecLength(&diff));
    sign = -1.0f;
    if (FastVecDot(&diff, &axes[1]) >= 0.0f) {
        sign = 1.0f;
    }
    yaw = yaw * sign;
    if (FloatAbs(dyaw) > 1.5707965f
        && ((dyaw >= 0.0f && sign < 0.0f) || (dyaw < 0.0f && sign >= 0.0f))) {
        if (yaw < 0.0f) {
            yaw += 6.283186f;
        } else {
            yaw -= 6.283186f;
        }
    }
    turn = yaw * step;
    if (FloatAbs(turn) < 1e-5f) {
        qcopy(&r0, &axes[0]);
        qcopy(&r1, &axes[1]);
    } else {
        BuildAxisAngleQuaternion(&r2, &axes[2], turn);
        RotateVectorByQuaternion(&r0, &axes[0], &r2);
        RotateVectorByQuaternion(&r1, &axes[1], &r2);
    }
    if (FloatAbs(yaw) < 1e-5f) {
        qcopy(&r2, &axes[0]);
    } else {
        BuildAxisAngleQuaternion(&tempRot, &axes[2], yaw);
        RotateVectorByQuaternion(&r2, &axes[0], &tempRot);
    }
    yaw = 1.57079637f - FastAngleHelper(FastVecDot(&r2, cam));
    d = FastVecDot(&r2, &cam->basis[2]);
    pitchSign = -1.0f;
    if (d >= 0.0f) {
        pitchSign = 1.0f;
    }
    yaw *= pitchSign;
    ApplyAxisRotationToQuaternion(&r0, &r0, &r1, yaw * step);
    vec_scale_to_length(&D_001B5570[0], &r0, 1.0f);
    FastVecCross(&D_001B5570[1], &D_001B5570[0], D_0018A0E0);
    vec_scale_to_length(&D_001B5570[1], &D_001B5570[1], -1.0f);
    FastVecCross(&D_001B5570[2], &D_001B5570[1], &D_001B5570[0]);
    TransformMatrixViaCopy(&orbit->saved_rot, D_001B5570);
    TransformMatrixViaCopy(&orbit->rot, D_001B5570);
    FastFloatHelperD(&orbit->frames_left);
    return 0;
}

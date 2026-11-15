#include "common.h"
extern void func_0029FCC0(void *,int,void *),func_0029FC20(void *,int,void *);
extern float func_00282E48(void *,void *),func_00282E80(void *,void *),func_00282E20(void *);
extern float func_00283248(float,float),func_00283BE0(float,float),func_002A7878(float,float);
extern float func_00283CE0(int),func_002ABB18(float),func_00283198(float);
extern void func_00282D30(void *,void *,float),func_00282F20(void *,void *,float);
extern void func_00282CC0(void *,void *,void *),func_00282CF0(void *,void *,void *);
extern void func_002ACB48(void *,float),func_002A7470(void *,int,int,int);
extern void func_002AEC48(void *,void *,int,float,float);
extern void *func_L09_003AE8C8(void *,void *,void *,int,int,float,float,float,float);
extern char D_00189F30[] MACRO_ADDR;
extern int D_L09_001B2388 MACRO_ADDR;
extern int D_L09_001B2388_gp SDATA(D_L09_001B2388);
extern float D_L09_001B0BD4 __attribute__((sda));
extern float D_L09_001B0C30 __attribute__((sda));
extern float D_L09_001B0C2C __attribute__((sda));
extern float D_L09_001B0C34 __attribute__((sda));
extern float D_L09_001B0C24 __attribute__((sda));
extern u8 D_L09_001B0BDC __attribute__((sda));
extern int D_L09_001B0BD8 __attribute__((sda));
extern u16 D_L09_001B0BE0 __attribute__((sda));
extern float D_L09_001B0BE8 __attribute__((sda));
extern u16 D_L09_001B0BE4 __attribute__((sda));
extern float D_L09_001B0BEC __attribute__((sda));
extern float D_L09_001B0C38 __attribute__((sda));
extern float D_L09_001B0C3C __attribute__((sda));

typedef union { u8 pad[0x318]; struct { u8 pad0[0x298]; float yaw; u8 pad1[0x314 - 0x29C]; float pitch; } aim; } AimState;

/* Tracks a shot direction in active states and drives the two aim channels.
 * The joint transform is a complete 64-byte matrix, not one vector.
 */
/* Turns the enemy to face the hero while it is active, and sways it gently while it is idle. */
void func_L09_003EA360(u8 *object)
{
    struct { float point[4], direction[4], joint[16]; } frame;
    u8 *state = *(u8 **)(object + 0x68);
    float blend = 1.0f, distance, angle;
    if ((unsigned)(object[0x20] - 3) < 3) {
        TransformMobyJointToWorld(object, 0, frame.point);
        distance = fast_vec_dist(frame.point, state + 0x140) - 1.0f;
        distance /= D_L09_001B0BD4 * 0.016666668f;
        distance *= RandomFloatRange(D_L09_001B0C2C, D_L09_001B0C30);
        FastVecScale(frame.direction, D_00189F30, distance);
        AddRandomOffsetToVector(frame.direction, D_L09_001B0C34);
        frame.direction[2] = 0.0f;
        FastVecAdd(frame.direction, frame.direction, state + 0x140);
        FastVecSub(frame.point, frame.direction, frame.point);
        *(float *)(state + 0x298) = fast_subtract_rotations(
            FastMatrixHelperA(frame.point[0], frame.point[1]), *(float *)(object + 0xF8));
        TransformMobyJointToWorld(object, 1, frame.point);
        FastVecSub(frame.point, frame.direction, frame.point);
        angle = fast_subtract_rotations(-FastMatrixHelperA(vec_length_xy(frame.point), frame.point[2]),
                              *(float *)(object + 0xF4));
        if (angle > 0.349065899848938f) angle = 0.349065899848938f;
        else if (angle < -0.349065899848938f) angle = -0.349065899848938f;
        *(float *)(state + 0x314) = angle;
    }
    if (object[0x20] == 4) {
        if ((*(u64 *)(state + 0x368) & 0xFFFF00FFULL) == 0) {
            if (object[0x42] != 1 && object[0x43] != 1)
                StartAnimationBlended(object, 1, 0, 0);
            distance = *(float *)(state + 0x384);
            if (distance < 1.0f) distance = D_L09_001B0C24;
            TransformMobyJointToWorld(object, 2, frame.point);
            TransformMobyJointPoint(object, 2, frame.joint);
            vec_scale_to_length(frame.direction, frame.joint, D_L09_001B0BD4 * 0.016666668f);
            SpawnProjectileMoby_L09(frame.point, object, frame.direction, 1, 1,
                              (float)state[0x34], distance, 1.0f, 1.0f);
            state[0x369]++;
            state[0x368] = D_L09_001B0BDC;
            if (D_L09_001B0BD8 < state[0x369]) {
                state[0x369] = 0;
                *(u16 *)(state + 0x36A) = D_L09_001B0BE0;
                if (vec_distance_xy(object + 0x10, state + 0x140) < D_L09_001B0BE8)
                    *(u16 *)(state + 0x36A) = D_L09_001B0BE4;
                if (object[0x43] != 0) StartAnimationBlended(object, 0, 0, 0);
            }
        }
        blend = IntToFloat(*(u16 *)(object + 0x96)) / D_L09_001B0BEC;
        if (blend > 1.0f) blend = 1.0f;
        else if (blend < 0.0f) blend = 0.0f;
    } else if (object[0x20] < 3) {
        if (object[0x43] != 0) StartAnimationBlended(object, 0, 0, 0);
        blend = 0.1f;
        ((AimState *)state)->aim.pitch = FastSinOrCosB(WrapAngleToPi(
            IntToFloat(D_L09_001B2388_gp) * 0.016666668f)) * 0.2617994248867035f;
        ((AimState *)state)->aim.yaw = FastSinOrCosB(WrapAngleToPi(
            IntToFloat(D_L09_001B2388) * 0.014285714365541935f)) * 0.349065899848938f;
    }
    UpdateEasedNode(object, state + 0x230, 0, D_L09_001B0C38 * blend, D_L09_001B0C3C);
    UpdateEasedNode(object, state + 0x2B0, 1, D_L09_001B0C38 * blend, D_L09_001B0C3C);
}

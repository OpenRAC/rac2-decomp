#include "names.h"
extern void FastVecAdd(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern float mat_fast_helper_a(float, float);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern float moby_get_anim_value(void *);
extern void moby_transform_joint_to_world(void *, int, void *);
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern void vec_random_direction(void *, float, float);
extern float coll_probe_ground_height_below(void *, int, float);
extern int moby_step_at_own_position_factor(void *, float);
extern char *SpawnSpinningSparkParticle(void *, int, float, float, void *, float, int, int, float);
extern int moby_l01_turn_toward_target(void *, void *);
extern float D_L04_002AF630[];

/* Moves the object along its animation toward a target point and turns it to face that point. On two key frames it also sprays a burst of sparks. */
void object_move_along_anim_sparks(char *moby, float *targetPos)
{
    float step[4], pos[4], vel[4], random[4], spawn[4];
    float frame, frameStart, brightness;
    int frameIndex, i, sparkKind;
    unsigned short lifetime;
    char *particle, *particleData;

    if ((unsigned char)moby[0x42] != (unsigned char)moby[0x43]) {
        moby_l01_turn_toward_target(moby, targetPos);
        return;
    }
    frame = moby_get_anim_value(moby);
    frameIndex = FloatToInt(frame);
    {
        int nextIndex = frameIndex + 1;
        frameStart = IntToFloat(frameIndex);
        frame -= frameStart;
        FastVecScale(step, moby + 0xc0,
                      D_L04_002AF630[frameIndex] + (D_L04_002AF630[nextIndex] - D_L04_002AF630[frameIndex]) * frame);
    }
    FastVecAdd(moby + 0x10, step, moby + 0x10);
    moby_step_at_own_position_factor(moby, mat_fast_helper_a(targetPos[0] - *(float *)(moby + 0x10), targetPos[1] - *(float *)(moby + 0x14)));
    *(float *)(moby + 0x18) = coll_probe_ground_height_below(moby + 0x10, 0, 0.5f);
    if (frameIndex != 5 && frameIndex != 15) {
        return;
    }
    if (frameIndex == 5) {
        moby_transform_joint_to_world(moby, 3, pos);
    } else {
        moby_transform_joint_to_world(moby, 2, pos);
    }
    FastVecScale(vel, moby + 0xc0, 0.5f);
    FastVecAdd(pos, pos, vel);
    pos[2] -= 0.2f;
    lifetime = 60;
    for (i = 9; i >= 0; i--) {
        vec_random_direction(random, 0.005000000353902578f, 0.050000004f);
        sparkKind = FloatToInt(math_random_signed_float_range(1.0f, 3.0f));
        brightness = math_random_float_range(0.3f, 1.0f) * 210000.0f;
        spawn[0] = pos[0] + math_random_signed_float_range(0.0f, 0.3f);
        spawn[1] = pos[1] + math_random_signed_float_range(0.0f, 0.3f);
        spawn[2] = pos[2] + math_random_signed_float_range(0.0f, 0.3f);
        particle = SpawnSpinningSparkParticle(spawn, sparkKind, 0.0f, 1.0f, random, 1.01f, 0x406080, 0, brightness);
        if (particle) {
            *(unsigned short *)(particle + 0xa) = lifetime;
            particleData = particle + 0x20;
            particle[3] = 0x44;
            particle[9] = FloatToInt(4.0f) + 0x40;
            *(float *)(particleData + 0x1c) = IntToFloat(5);
            *(int *)(particleData + 4) = 3;
            particleData[0xa] = 0x20;
            particleData[0xb] = particle[0xa];
        }
    }
}

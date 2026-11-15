#include "names.h"
/* A unit of its own for -frac2-keep-block-order (config/cflags.txt): retail keeps the
   frame-15 joint call behind the frame-5 one, reached by a jump. */

extern int moby_l01_turn_toward_target(char *, float *);
extern float moby_get_anim_value(char *);
extern int FloatToInt(float);
extern float IntToFloat(int);
extern float D_L11_002B6C10[];
extern void FastVecScale(char *, char *, float);
extern void FastVecAdd(char *, char *, char *);
extern float mat_fast_helper_a(float, float);
extern int moby_step_at_own_position_factor(char *, float);
extern void moby_transform_joint_to_world(char *, int, float *);
extern void vec_random_direction(float *, float, float);
extern float math_random_signed_float_range(float, float);
extern float math_random_float_range(float, float);
extern char *SpawnSpinningSparkParticle(float *, float, float, float, int, float *, float, int, int);

/* Steps along the vector at +0xC0, weighted by the walk table at the animation frame, and
   turns toward the target; on frames 5 and 15 it scatters ten dust particles at a joint
   (3, then 2). A state change hands over to the shared handler instead. */
void joba_fighter_walk_dust(char *obj, float *target)
{
    float offset[4], origin[4], half[4], velocity[4], pos[4];
    float frame, t, scale;
    int index, i, type, next;
    short lifetime;
    char *particle, *data;

    if (*(unsigned char *)(obj + 0x42) != *(unsigned char *)(obj + 0x43)) {
        moby_l01_turn_toward_target(obj, target);
        return;
    }
    frame = moby_get_anim_value(obj);
    index = FloatToInt(frame);
    next = index + 1;
    t = IntToFloat(index);
    FastVecScale((char *)offset, obj + 0xC0, D_L11_002B6C10[index] + (D_L11_002B6C10[next] - D_L11_002B6C10[index]) * (frame - t));
    FastVecAdd(obj + 0x10, (char *)offset, obj + 0x10);
    moby_step_at_own_position_factor(obj, mat_fast_helper_a(target[0] - *(float *)(obj + 0x10), target[1] - *(float *)(obj + 0x14)));
    if (index == 5 || index == 15) {
        if (index == 5) {
            moby_transform_joint_to_world(obj, 3, origin);
        } else {
            moby_transform_joint_to_world(obj, 2, origin);
        }
        FastVecScale((char *)half, obj + 0xC0, 0.5f);
        FastVecAdd((char *)origin, (char *)origin, (char *)half);
        origin[2] -= 0.2f;
        lifetime = 60;
        for (i = 9; i >= 0; i--) {
            vec_random_direction(velocity, 0.005000000353902578f, 0.050000004f);
            type = FloatToInt(math_random_signed_float_range(1.0f, 3.0f));
            scale = math_random_float_range(0.3f, 1.0f) * 210000.0f;
            pos[0] = origin[0] + math_random_signed_float_range(0, 0.3f);
            pos[1] = origin[1] + math_random_signed_float_range(0, 0.3f);
            pos[2] = origin[2] + math_random_signed_float_range(0, 0.3f);
            particle = SpawnSpinningSparkParticle(pos, 0, 1.0f, 1.01f, type, velocity, scale, 0x406080, 0);
            if (particle != 0) {
                *(short *)(particle + 0xA) = lifetime;
                particle[3] = 0x44;
                data = particle + 0x20;
                particle[9] = FloatToInt(4.0f) + 0x40;
                *(float *)(data + 0x1C) = IntToFloat(5);
                *(int *)(data + 4) = 3;
                data[0xA] = 0x20;
                data[0xB] = particle[0xA];
            }
        }
    }
}

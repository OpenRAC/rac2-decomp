#include "include_asm.h"
#include "names.h"

extern int moby_l01_turn_toward_target_pal(char *, float *);
extern float moby_get_anim_value(char *);
extern int FloatToInt(float);
extern float IntToFloat(int);
extern float g_walk_dust_scale_curve[];
extern void FastVecScale(char *, char *, float);
extern void FastVecAdd(char *, char *, char *);
extern float mat_fast_helper_a(float, float);
extern int moby_step_at_own_position_factor_pal(char *, float);
extern void moby_transform_joint_to_world(char *, int, float *);
extern void vec_random_direction(float *, float, float);
extern float math_random_signed_float_range(float, float);
extern float math_random_float_range(float, float);
extern char *part_spawn_spinning_spark_pal(float *, float, float, float, int, float *, float, int, int);

/* Steps along the vector at +0xC0, weighted by the walk table at the animation frame, and
   turns toward the target; on frames 5 and 15 it scatters ten dust particles at a joint
   (3, then 2). A state change hands over to the shared handler instead. */
void joba_walk_and_scatter_dust_pal(char *moby, float *target)
{
    float offset[4], origin[4], half[4], velocity[4], pos[4];
    float frame, frame_int, scale;
    int index, i, type, next;
    short lifetime;
    char *particle, *vars;

    if (*(unsigned char *)(moby + 0x42) != *(unsigned char *)(moby + 0x43)) {
        moby_l01_turn_toward_target_pal(moby, target);
        return;
    }
    frame = moby_get_anim_value(moby);
    index = FloatToInt(frame);
    next = index + 1;
    frame_int = IntToFloat(index);
    FastVecScale((char *)offset, moby + 0xC0, g_walk_dust_scale_curve[index] + (g_walk_dust_scale_curve[next] - g_walk_dust_scale_curve[index]) * (frame - frame_int));
    FastVecAdd(moby + 0x10, (char *)offset, moby + 0x10);
    moby_step_at_own_position_factor_pal(moby, mat_fast_helper_a(target[0] - *(float *)(moby + 0x10), target[1] - *(float *)(moby + 0x14)));
    if (index == 5 || index == 15) {
        if (index == 5) {
            moby_transform_joint_to_world(moby, 3, origin);
        } else {
            moby_transform_joint_to_world(moby, 2, origin);
        }
        FastVecScale((char *)half, moby + 0xC0, 0.5f);
        FastVecAdd((char *)origin, (char *)origin, (char *)half);
        origin[2] -= 0.2f;
        lifetime = 50;
        for (i = 9; i >= 0; i--) {
            vec_random_direction(velocity, 0.0060000005f, 0.060000002f);
            type = FloatToInt(math_random_signed_float_range(1.0f, 3.0f));
            scale = math_random_float_range(0.3f, 1.0f) * 210000.0f;
            pos[0] = origin[0] + math_random_signed_float_range(0, 0.3f);
            pos[1] = origin[1] + math_random_signed_float_range(0, 0.3f);
            pos[2] = origin[2] + math_random_signed_float_range(0, 0.3f);
            particle = part_spawn_spinning_spark_pal(pos, 0, 1.0f, 1.01f, type, velocity, scale, 0x406080, 0);
            if (particle != 0) {
                *(short *)(particle + 0xA) = lifetime;
                particle[3] = 0x44;
                vars = particle + 0x20;
                particle[9] = FloatToInt(4.0f) + 0x40;
                *(float *)(vars + 0x1C) = IntToFloat(4);
                *(int *)(vars + 4) = 3;
                vars[0xA] = 0x20;
                vars[0xB] = particle[0xA];
            }
        }
    }
}

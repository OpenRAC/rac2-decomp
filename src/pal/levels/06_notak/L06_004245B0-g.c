#include "include_asm.h"
#include "names.h"

extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(float *, float *, float *);
extern float FastVecLength(float *);
extern void vec_scale_to_length(float *, float *, float);
extern void FastVecScale(void *, void *, float);
extern int PlayMobySound(int, int, void *);
extern float math_ease_out_quad(float);
extern int moby_move_and_collide(void *, void *, int, float, float, float);
extern float MobySpringTurn(void *, float, float, float, float, void *);
extern char g_effect_target_records[];

/* Steps the follower's weight toward its goal and blends the state vectors; returns 1 on arrival. */
int actor_move_toward_goal_pal(char *object, float accel, float max_speed, float turn_yaw, float damping)
{
    char *record;
    float distance;
    float speed_now;
    char *state = *(char **)(object + 0x68);
    int done = 0;
    float top_speed = max_speed * 0.020000001f;
    float stop_ratio;
    char *velocity_vec;
    float to_goal[4];
    float accel_step = accel * 0.00040000002f;

    FastVecSub(to_goal, (float *)(state + 0x220), (float *)(object + 0x10));
    distance = FastVecLength(to_goal);
    speed_now = FastVecLength((float *)(state + 0x230));
    record = g_effect_target_records + *(int *)(state + 0x254) * 0x70;
    stop_ratio = speed_now / accel_step;
    if (*(char **)(record + 0x88) != object || *(unsigned char *)(record + 0x74) == 0)
        *(int *)(state + 0x254) = PlayMobySound(0, 4, object);
    if (distance < speed_now * stop_ratio) {
        speed_now -= accel_step;
        done = 1;
    } else {
        speed_now += accel_step * math_ease_out_quad((top_speed - speed_now) / top_speed);
    }
    vec_scale_to_length(to_goal, to_goal, speed_now);
    velocity_vec = state + 0x230;
    FastVecScale(velocity_vec, velocity_vec, damping);
    FastVecScale(to_goal, to_goal, 1.0f - damping);
    FastVecAdd(velocity_vec, velocity_vec, to_goal);
    moby_move_and_collide(object, velocity_vec, 0, 0.0f, 1.5f, 0.0f);
    MobySpringTurn(object, turn_yaw, 0.0008377582f, 0.0025132746f, 0.04188791f, state + 0x25C);
    return done;
}

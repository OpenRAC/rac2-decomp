#include "names.h"
typedef struct {
    float x, y, z, w;
} Vec9E60;
extern struct { char pad[128]; Vec9E60 position; } g_hero_state;
typedef struct {
    char pad[0x10];
    Vec9E60 position;
    unsigned char mode;
    char pad21[0x47];
    void *state;
} Object9E60;
extern void FastVecSub(char *, void *, char *);
extern void vec_fast_divide_helper(char *, char *, float);
extern float FastDiffRots(float, float);
extern float math_ease_out_quad(float);
extern float FastVecLength(char *);
extern float math_approach_target_with_direction_mode(char *, float, float, float, float, char *, int);
extern void math_approach_target_with_braking(float *, float, float, float, float);
extern float func_002EAB28(float, float);
extern float func_002EB478(float, float);
extern void vec_scale_to_length(char *, char *, float);
extern void FastVecAdd(char *, char *,char *);
/* Moves the object toward a target point at a speed that depends on how far it must turn. Returns 0 when its path point changed, otherwise 1. */
int path_move_moby_turn_speed(Object9E60 *obj, void *buf, float distance)
{
    char *object = (char *)obj;
    struct State {
        char pad0[0x64];
        float field64, field68, field6C, field70, field74, field78;
        int pad7C;
        float field80;
        char pad84[0x6C];
        float velocity[4];
        int pad100;
        float field104;
        char pad108[16];
        short current, previous;
    };
    struct State *state = *(struct State **)(object + 0x68);
    float toTarget[4];
    float speed;
    float scale;
    int result = 1;
    float angle;
    char *pos;
    if (state->current != -1) {
        scale = 1.0f;
        FastVecSub((char *)toTarget, buf, (char *)&obj->position);
        pos = (char *)&obj->position;
        vec_fast_divide_helper((char *)toTarget, (char *)toTarget, state->field78);
        angle = func_002EAB28(toTarget[0], toTarget[1]);
        if (*(unsigned char *)(object + 0x20) < 4) {
            math_approach_target_with_direction_mode(object + 0xF8, angle, state->field64, state->field68, state->field6C, (char *)&state->field104, 0);
            scale = FastDiffRots(angle, *(float *)(object + 0xF8)) / state->field80;
            if (scale > 1.0f) scale = 1.0f;
            else if (scale < 0.0f) scale = 0.0f;
            scale = math_ease_out_quad(1.0f - scale);
        } else {
            float y = obj->position.y;
            float x = obj->position.x;
            angle = func_002EAB28(g_hero_state.position.x - x, g_hero_state.position.y - y);
            math_approach_target_with_direction_mode(object + 0xF8, func_002EB478(angle, 1.5707964897155762f), state->field64, state->field68, state->field6C, (char *)&state->field104, 0);
        }
        speed = FastVecLength((char *)state->velocity);
        math_approach_target_with_braking(&speed, distance, state->field70, state->field74, state->field78);
        speed *= scale;
        vec_scale_to_length((char *)state->velocity, (char *)toTarget, speed);
        FastVecAdd(pos, pos, (char *)state->velocity);
        if (state->current != state->previous) result = 0;
    }
    return result;
}

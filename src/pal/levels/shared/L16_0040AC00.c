#include "include_asm.h"

#include "common.h"
typedef int Vector128 __attribute__((mode(TI)));
extern char *CreateMoby(int);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern int math_fast_helper_a(void *, float);
extern float fast_vec_dist(void *, void *);
extern float FastVecDot(void *, void *);
extern float math_fast_angle_helper(float);
extern void part_l16_spawn_explosion_burst_pal(char *, char *);
extern char g_scalar_transition_state[];
typedef struct SpawnState {
    short life;
    short timer;
    short delay;
    short pad06;
    float outer, inner, fade, size;
    int flags, control, kind, red, green, blue, enabled, extra;
} SpawnState;
typedef struct SpawnObject {
    char pad00[0x10];
    float position[4];
    char status;
    char pad21[0xf];
    unsigned char alpha;
    char pad31;
    short color;
    char pad34[0x34];
    SpawnState *state;
    char pad6c[0x54];
    float forward[4], right[4], up[4];
} SpawnObject;
extern void cam_compute_view_direction(char *a0, void *a1, int a2);

/* func_L00_0040BA30 is defined in L00_0040BA30-g8.c. */

/* func_L00_0040C7D8 is defined in L00_0040C7D8-g8.c. */

/* func_L00_0040CCA0 is in L00_0040CCA0.c. */

/* func_L00_0040D058 is defined in L00_0040D058-ribbon.c. */

/* Spawns a flash effect facing the camera, sets its colors and timers, and starts the explosion burst when on screen (PAL timings). */
char *part_create_flash_pal(float size, char *position, int trigger, int kind, int red, int green, int blue, int enabled, int flags, int extra, int control)
{
    Vector128 direction[1], up[1], sphere[1], difference[1];
    char *object = CreateMoby(0xEC1);
    SpawnState *state;
    SpawnObject *moby;
    char *camera;
    float angle;
    if (object != 0) {
        moby = (SpawnObject *)object;
        state = moby->state;
        *(unsigned char *)(object + 0x30) = 0xff;
        *(short *)(object + 0x32) = 0xff;
        object[0x20] = 0;
        qcopy(object + 0x10, position);
        *(float *)(object + 0x1c) = 1.0f;
        camera = g_scalar_transition_state + 0x140;
        FastVecSub(direction, camera, object + 0x10);
        vec_scale_to_length(direction, direction, 1.0f);
        cam_compute_view_direction(object + 0x10, (char *)up, 1);
        qcopy(object + 0xc0, direction);
        FastVecCross(object + 0xd0, object + 0xc0, up);
        vec_scale_to_length(object + 0xd0, object + 0xd0, 1.0f);
        FastVecCross(object + 0xe0, object + 0xd0, object + 0xc0);
        moby->forward[3] = moby->right[3] = moby->up[3] = 0.0f;
        /* Both countdowns start together. */
        state->timer = state->life = 50;
        state->outer = size + size;
        state->inner = size*4.0f;
        state->kind = kind;
        state->red = red;
        state->green = green;
        state->blue = blue;
        state->enabled = enabled;
        state->extra = extra;
        state->control = control;
        state->flags = flags;
        state->size = size;
        qcopy(sphere, object + 0x10);
        ((float *)sphere)[3] = size*3.0f;
        if (math_fast_helper_a(sphere, 128.0f) == 1) {
            state->delay = 8;
            state->fade = 0.125f;
            if (fast_vec_dist(position, camera) < 48.0f && trigger != 0) {
                char *manager = camera - 0x140;
                *(int *)(manager + 0x16c) = 0;
                *(volatile float *)(manager + 0x160) = 0.075f;
                *(volatile int *)(manager + 0x168) = 33;
            }
            if (state->flags != 0) {
                FastVecSub(difference, object + 0x10, g_scalar_transition_state + 0x140);
                vec_scale_to_length(difference, difference, 1.0f);
                angle = math_fast_angle_helper(FastVecDot(difference, g_scalar_transition_state + 0x370));
                if (1.5707963705f - angle < 0.4537856579f)
                    state->flags = 1;
                else
                    state->flags = 0;
            }
        } else {
            state->delay = 0;
            state->flags = 0;
        }
        part_l16_spawn_explosion_burst_pal(object, (char *)up);
    }
    return object;
}

/* func_PAL_L16_0040B0C8 is defined in L16_0040B0C8-g8.c. */

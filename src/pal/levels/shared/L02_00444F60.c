#include "include_asm.h"



#include "common.h"
typedef int Vector128 __attribute__((mode(TI)));
extern char *CreateMoby(int);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void cam_compute_view_direction(char *, char *, int);
extern void FastVecCross(void *, void *, void *);
extern int math_fast_helper_a(void *, float);
extern float fast_vec_dist(void *, void *);
extern float FastVecDot(void *, void *);
extern float math_fast_angle_helper(float);
extern void func_PAL_L00_00419448(char *, char *, char *);
extern int moby_transform_point_by_attachment(char *, char *, char *, char *);
extern char g_scalar_transition_state[];
typedef struct SpawnState {
    short life;
    short timer;
    short delay;
    short pad06;
    float outer, inner, fade, size;
    int flags, control, kind, red, green, blue, enabled, extra;
} SpawnState;
typedef struct ParentedSpawnState {
    short life;
    short timer;
    short delay;
    short pad06;
    float outer, inner, fade, size;
    int flags, control, kind, red, green, blue, enabled, extra, extra2;
    char *parent;
} ParentedSpawnState;
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
extern Vector128 g_hero_l00_position;

char *func_PAL_L02_00445660(float size, char *position, int trigger, int kind, int red, int green,
                        int blue, int enabled, int flags, int extra, int control, int extra2,
                        char *parent)
{
    Vector128 direction[1], up[1], attachment[1], sphere[1], difference[1];
    char *object = CreateMoby(0x139c);
    ParentedSpawnState *state;
    SpawnObject *m;
    if (object != 0) {
        m = (SpawnObject *)object;
        *(unsigned char *)(object + 0x30) = 0xff;
        object[0x20] = 0;
        *(short *)(object + 0x32) = 0xff;
        state = (ParentedSpawnState *)m->state;
        qcopy(object + 0x10, position);
        *(float *)(object + 0x1c) = 1.0f;
        FastVecSub(direction, g_scalar_transition_state + 0x140, object + 0x10);
        vec_scale_to_length(direction, direction, 1.0f);
        cam_compute_view_direction(object + 0x10, (char *)up, 1);
        qcopy(object + 0xc0, direction);
        FastVecCross(object + 0xd0, object + 0xc0, up);
        vec_scale_to_length(object + 0xd0, object + 0xd0, 1.0f);
        FastVecCross(object + 0xe0, object + 0xd0, object + 0xc0);
        m->forward[3] = m->right[3] = m->up[3] = 0.0f;
        state->size = size;
        state->kind = kind;
        state->red = red;
        state->green = green;
        state->blue = blue;
        state->enabled = enabled;
        state->extra = extra;
        state->extra2 = extra2;
        /* Both countdowns start together. */
        state->timer = state->life = 50;
        state->outer = size + size;
        state->inner = size*4.0f;
        state->control = control;
        state->flags = flags;
        state->parent = parent;
        qzero_nc(attachment);
        if (parent)
            moby_transform_point_by_attachment(object, parent, object + 0x10, (char *)attachment);
        qcopy(sphere, object + 0x10);
        ((float *)sphere)[3] = size*3.0f;
        if (math_fast_helper_a(sphere, 128.0f) == 1) {
            state->delay = 8;
            state->fade = 0.125f;
            if (fast_vec_dist(position, g_scalar_transition_state + 0x140) < 48.0f && trigger != 0) {
                char *manager = g_scalar_transition_state;
                *(int *)(manager + 0x16c) = 0;
                *(int *)(manager + 0x168) = 17;
                *(float *)(manager + 0x160) = 0.075f;
            }
            if (state->flags != 0) {
                FastVecSub(difference, object + 0x10, g_scalar_transition_state + 0x140);
                vec_scale_to_length(difference, difference, 1.0f);
                if (1.5707964f - math_fast_angle_helper(FastVecDot(difference, g_scalar_transition_state + 0x370)) < 0.45378566f)
                    state->flags = 1;
                else
                    state->flags = 0;
            }
        } else {
            state->delay = 0;
            state->flags = 0;
        }
        func_PAL_L00_00419448(object, (char *)up, (char *)attachment);
    }
    return object;
}


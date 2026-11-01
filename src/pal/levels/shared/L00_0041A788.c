#include "include_asm.h"

#include "common.h"
typedef int Vector128 __attribute__((mode(TI)));
extern char *func_0029EFD0(int);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern int func_00283DB8(void *, float);
extern float func_00282E48(void *, void *);
extern float func_00282DB0(void *, void *);
extern float func_002831B0(float);
extern void func_PAL_L00_0041AE28(char *, char *);
extern char D_L00_001B8C80[];
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
extern void func_002AFFD8(char *a0, void *a1, int a2);

/* func_L00_0040BA30 is defined in L00_0040BA30-g8.c. */

/* func_L00_0040C7D8 is defined in L00_0040C7D8-g8.c. */

/* func_L00_0040CCA0 is in L00_0040CCA0.c. */

/* func_L00_0040D058 is defined in L00_0040D058-ribbon.c. */

char *func_PAL_L00_0041A788(float size, char *position, int trigger, int kind, int red, int green, int blue, int enabled, int flags, int extra, int control)
{
    Vector128 direction[1], up[1], sphere[1], difference[1];
    char *object = func_0029EFD0(0x139D);
    SpawnState *state;
    SpawnObject *m;
    char *camera;
    float angle;
    if (object != 0) {
        m = (SpawnObject *)object;
        state = m->state;
        *(unsigned char *)(object + 0x30) = 0xff;
        *(short *)(object + 0x32) = 0xff;
        object[0x20] = 0;
        qcopy(object + 0x10, position);
        *(float *)(object + 0x1c) = 1.0f;
        camera = D_L00_001B8C80 + 0x140;
        func_00282CF0(direction, camera, object + 0x10);
        func_00282F20(direction, direction, 1.0f);
        func_002AFFD8(object + 0x10, (char *)up, 1);
        qcopy(object + 0xc0, direction);
        func_00282DD8(object + 0xd0, object + 0xc0, up);
        func_00282F20(object + 0xd0, object + 0xd0, 1.0f);
        func_00282DD8(object + 0xe0, object + 0xd0, object + 0xc0);
        m->forward[3] = m->right[3] = m->up[3] = 0.0f;
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
        if (func_00283DB8(sphere, 128.0f) == 1) {
            state->delay = 8;
            state->fade = 0.125f;
            if (func_00282E48(position, camera) < 48.0f && trigger != 0) {
                char *manager = camera - 0x140;
                *(int *)(manager + 0x16c) = 0;
                *(volatile float *)(manager + 0x160) = 0.075f;
                *(volatile int *)(manager + 0x168) = 33;
            }
            if (state->flags != 0) {
                func_00282CF0(difference, object + 0x10, D_L00_001B8C80 + 0x140);
                func_00282F20(difference, difference, 1.0f);
                angle = func_002831B0(func_00282DB0(difference, D_L00_001B8C80 + 0x370));
                if (1.5707963705f - angle < 0.4537856579f)
                    state->flags = 1;
                else
                    state->flags = 0;
            }
        } else {
            state->delay = 0;
            state->flags = 0;
        }
        func_PAL_L00_0041AE28(object, (char *)up);
    }
    return object;
}


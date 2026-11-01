#include "include_asm.h"


INCLUDE_ASM("asm/pal/levels", func_PAL_L02_00445550);

#include "common.h"
typedef int Vector128 __attribute__((mode(TI)));
extern char *func_0029EFD0(int);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_002AFFD8(char *, char *, int);
extern void func_00282DD8(void *, void *, void *);
extern int func_00283DB8(void *, float);
extern float func_00282E48(void *, void *);
extern float func_00282DB0(void *, void *);
extern float func_002831B0(float);
extern void func_PAL_L00_00419448(char *, char *, char *);
extern int func_002AD330(char *, char *, char *, char *);
extern char D_L00_001B8C80[];
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
extern Vector128 D_L00_001BF220;

char *func_PAL_L02_00445660(float size, char *position, int trigger, int kind, int red, int green,
                        int blue, int enabled, int flags, int extra, int control, int extra2,
                        char *parent)
{
    Vector128 direction[1], up[1], attachment[1], sphere[1], difference[1];
    char *object = func_0029EFD0(0x139c);
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
        func_00282CF0(direction, D_L00_001B8C80 + 0x140, object + 0x10);
        func_00282F20(direction, direction, 1.0f);
        func_002AFFD8(object + 0x10, (char *)up, 1);
        qcopy(object + 0xc0, direction);
        func_00282DD8(object + 0xd0, object + 0xc0, up);
        func_00282F20(object + 0xd0, object + 0xd0, 1.0f);
        func_00282DD8(object + 0xe0, object + 0xd0, object + 0xc0);
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
            func_002AD330(object, parent, object + 0x10, (char *)attachment);
        qcopy(sphere, object + 0x10);
        ((float *)sphere)[3] = size*3.0f;
        if (func_00283DB8(sphere, 128.0f) == 1) {
            state->delay = 8;
            state->fade = 0.125f;
            if (func_00282E48(position, D_L00_001B8C80 + 0x140) < 48.0f && trigger != 0) {
                char *manager = D_L00_001B8C80;
                *(int *)(manager + 0x16c) = 0;
                *(int *)(manager + 0x168) = 17;
                *(float *)(manager + 0x160) = 0.075f;
            }
            if (state->flags != 0) {
                func_00282CF0(difference, object + 0x10, D_L00_001B8C80 + 0x140);
                func_00282F20(difference, difference, 1.0f);
                if (1.5707964f - func_002831B0(func_00282DB0(difference, D_L00_001B8C80 + 0x370)) < 0.45378566f)
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


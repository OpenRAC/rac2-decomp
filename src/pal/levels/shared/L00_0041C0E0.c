#include "include_asm.h"

#include "common.h"
typedef int Vector128 __attribute__((mode(TI)));
extern char *func_0029EFD0(int);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_002AFFD8(char *, char *, int);
extern void func_00282DD8(void *, void *, void *);
extern char D_L00_001B8C80[];
typedef struct SpawnState {
    short life;
    short timer;
    short delay;
    short pad06;
    float outer, inner, fade, size;
    int flags, control, kind, red, green, blue, enabled, extra;
} SpawnState;
typedef struct AttachedSpawnState {
    int life;
    int kind;
    char *parent;
} AttachedSpawnState;
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

char *func_PAL_L00_0041C0E0(Vector128 *position, int kind, char *parent)
{
    Vector128 direction[1], up[1];
    char *object = func_0029EFD0(0x139E);
    if (object != 0) {
        SpawnObject *m = (SpawnObject *)object;
        AttachedSpawnState *state = (AttachedSpawnState *)m->state;
        char *first = object + 0x10;
        char *second;
        char *third;
        *(unsigned char *)(object + 0x30) = 0xff;
        *(short *)(object + 0x32) = 0xff;
        object[0x20] = 0;
        qcopy(first, position);
        *(float *)(object + 0x1c) = 1.0f;
        second = object + 0xc0;
        func_00282CF0(direction, D_L00_001B8C80 + 0x140, first);
        func_00282F20(direction, direction, 1.0f);
        func_002AFFD8(first, (char *)up, 1);
        qcopy(second, direction);
        third = object + 0xd0;
        func_00282DD8(third, second, up);
        func_00282F20(third, third, 1.0f);
        func_00282DD8(object + 0xe0, third, second);
        m->forward[3] = m->right[3] = m->up[3] = 0.0f;
        state->life = 50;
        state->kind = kind;
        state->parent = parent;
    }
    return object;
}



extern float func_00283248(float, float);
extern float func_002A78D8(float, float);
extern int func_00283CF0(float);
extern float func_00283B98(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern unsigned char *func_PAL_L00_00342480(void *, void *, int);
extern char D_L00_001A8F20[] __attribute__((sda));
typedef struct { char pad[0x140]; float x, y; } CameraHead;
extern void func_L00_00417218(char *);

/* Spawns 25 particles around the object, each drifting away from the camera at a random angle. */
void func_PAL_L00_0041C390(char *object)
{
    float spawn[8];
    float heading, angle, speed;
    float spread = 0.0f;
    int i;

    for (i = 24; i >= 0; i--) {
        heading = func_00283248(((CameraHead *)D_L00_001B8C80)->x - *(float *)(object + 0x10),
                                ((CameraHead *)D_L00_001B8C80)->y - *(float *)(object + 0x14));
        speed = func_002A78D8(1.0f, 2.0f);
        func_00283CF0(speed);
        spawn[0] = *(float *)(object + 0x10) + func_002A78D8(-0.25f, 0.25f);
        spawn[1] = *(float *)(object + 0x14) + func_002A78D8(-0.25f, 0.25f);
        spawn[2] = *(float *)(object + 0x18) + func_002A78D8(-0.25f, 0.25f);
        spread = 0.0f;
        angle = func_00283B98(heading, func_002A78D8(spread, -1.5707965f));
        speed = 4.0f;
        spawn[4] = func_00283180(angle) * 0.020000001f * speed;
        spawn[5] = func_00283198(angle) * 0.020000001f * speed;
        spawn[6] = 0.09f;
        func_PAL_L00_00342480(spawn, D_L00_001A8F20, 250);
    }
}






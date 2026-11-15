#include "include_asm.h"

#include "common.h"
typedef int Vector128 __attribute__((mode(TI)));
extern char *CreateMoby(int);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void cam_compute_view_direction(char *, char *, int);
extern void FastVecCross(void *, void *, void *);
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
    char *object = CreateMoby(0x139E);
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
        FastVecSub(direction, D_L00_001B8C80 + 0x140, first);
        vec_scale_to_length(direction, direction, 1.0f);
        cam_compute_view_direction(first, (char *)up, 1);
        qcopy(second, direction);
        third = object + 0xd0;
        FastVecCross(third, second, up);
        vec_scale_to_length(third, third, 1.0f);
        FastVecCross(object + 0xe0, third, second);
        m->forward[3] = m->right[3] = m->up[3] = 0.0f;
        state->life = 50;
        state->kind = kind;
        state->parent = parent;
    }
    return object;
}



extern float mat_fast_helper_a(float, float);
extern float math_random_signed_float_range(float, float);
extern int FloatToInt(float);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern unsigned char *func_PAL_L00_00342480(void *, void *, int);
extern char D_L00_001A8F20[] __attribute__((sda));
typedef struct { char pad[0x140]; float x, y; } CameraHead;
extern void part_spawn_drifting_particles(char *);

/* Spawns 25 particles around the object, each drifting away from the camera at a random angle. */
void func_PAL_L00_0041C390(char *object)
{
    float spawn[8];
    float heading, angle, speed;
    float spread = 0.0f;
    int i;

    for (i = 24; i >= 0; i--) {
        heading = mat_fast_helper_a(((CameraHead *)D_L00_001B8C80)->x - *(float *)(object + 0x10),
                                ((CameraHead *)D_L00_001B8C80)->y - *(float *)(object + 0x14));
        speed = math_random_signed_float_range(1.0f, 2.0f);
        FloatToInt(speed);
        spawn[0] = *(float *)(object + 0x10) + math_random_signed_float_range(-0.25f, 0.25f);
        spawn[1] = *(float *)(object + 0x14) + math_random_signed_float_range(-0.25f, 0.25f);
        spawn[2] = *(float *)(object + 0x18) + math_random_signed_float_range(-0.25f, 0.25f);
        spread = 0.0f;
        angle = FastAddRotations(heading, math_random_signed_float_range(spread, -1.5707965f));
        speed = 4.0f;
        spawn[4] = math_fast_sin_or_cos_a(angle) * 0.020000001f * speed;
        spawn[5] = math_fast_sin_or_cos_b(angle) * 0.020000001f * speed;
        spawn[6] = 0.09f;
        func_PAL_L00_00342480(spawn, D_L00_001A8F20, 250);
    }
}






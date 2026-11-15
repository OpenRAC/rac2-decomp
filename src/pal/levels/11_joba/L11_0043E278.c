#include "include_asm.h"

#include "common.h"
struct RotorPath {
    int count;
    char pad04[12];
    float points[0][4];
};
struct RotorState {
      char pad00[0x35];
      u8 f35;
      char pad36[0x1A];
      float aim[4];
      int f60;
      char pad64[0x9C];
      float points[13][4];
      float oldPoints[13][4];
      char pad2A0[0x10];
      int choices[4][4];
      char pad2F0[0x30];
      int pathIndex;
      struct RotorPath *path;
      char pad328[8];
      int records[10];
      int linked;
      char pad35C[0xC];
      int projectileClass;
      char pad36C[4];
      s16 pathPoint;
      char pad372[2];
      s16 projectileIndex;
      s16 projectileDelay;
      s16 ropeCount;
      u16 toggle;
      char pad37C[4];
      u8 disabled[10];
};
struct RotorAxis {
    float x, y, z;
    int w;
};
struct RotorObject {
      char pad00[0x10];
      float pos[4];
      u8 mode;
      char pad21[0x13];
      u16 flags;
      char pad36[0x32];
      struct RotorState *state;
      char pad6C[0x4C];
      int fB8;
      char padBC[4];
      struct RotorAxis basis[3];
};
extern struct RotorPath *D_L11_001FF580[];
extern int g_moby_l11_table __attribute__((sda));
extern void FastVecSub(void *, const void *, const void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
#define ROTOR_RECORD(index) ((struct RotorObject *)(D_L11_001B359C + ((index) << 8)))
#define LISTED_RECORD(obj, i) ROTOR_RECORD((obj)->state->records[i])
extern int FastDecTimer(short *);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void moby_transform_joint_point(void *, int, void *);
extern char *moby_find_active_in_group(int);
extern void joba_shot_init(char *, void *, int, int, void *, void *, int, float, float);
extern void vec_random_direction(float *, float, float);
extern struct RotorPath *D_L11_001FF580[];
extern void vec_random_direction(float *out, float a, float b);

/* Emits a projectile from the next enabled record, with a fifteen-frame delay. */
void func_PAL_L11_0043E278(struct RotorObject *obj)
{
    float pos[4];
    float matrix[4][4];
    float offset[4];
    float velocity[4];
    float jitter[4];
    float toTarget[4];
    struct RotorState *state = obj->state;
    char *projectile;

    if (state->projectileIndex == -1)
        return;

    while (state->disabled[state->projectileIndex])
        ++state->projectileIndex;
    if (state->projectileIndex >= 10) {
        state->projectileIndex = -1;
        return;
    }
    if (!FastDecTimer(&state->projectileDelay))
        return;

    moby_transform_joint_to_world(LISTED_RECORD(obj, state->projectileIndex), 0, pos);
    moby_transform_joint_point(LISTED_RECORD(obj, state->projectileIndex), 0, matrix);
    vec_scale_to_length(offset, matrix[2], -0.3f);
    FastVecAdd(pos, pos, offset);

    vec_random_direction(jitter, 0.020000001f, 0.060000002f);
    jitter[2] = -0.10000001f;
    qcopy_nc(velocity, jitter);
    FastVecSub(toTarget, state->aim, pos);
    vec_scale_to_length(toTarget, toTarget, 0.40000004f);
    FastVecAdd(velocity, velocity, toTarget);

    projectile = moby_find_active_in_group(state->projectileClass);
    if (projectile)
        joba_shot_init(projectile, LISTED_RECORD(obj, state->projectileIndex), obj->fB8,
                          state->f60, pos, velocity, 120, 0.004f, state->f35);
    ++state->projectileIndex;
    state->projectileDelay = 12;
}


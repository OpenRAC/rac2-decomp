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
extern int D_L11_001B359C __attribute__((sda));
extern void func_00282CF0(void *, const void *, const void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
#define ROTOR_RECORD(index) ((struct RotorObject *)(D_L11_001B359C + ((index) << 8)))
#define LISTED_RECORD(obj, i) ROTOR_RECORD((obj)->state->records[i])
extern int func_00282978(short *);
extern void func_0029FCC0(void *, int, void *);
extern void func_0029FC20(void *, int, void *);
extern char *func_L07_003F6B88(int);
extern void func_L11_00458A98(char *, void *, int, int, void *, void *, int, float, float);
extern void func_002A7A00(float *, float, float);
extern struct RotorPath *D_L11_001FF580[];
extern void func_002A7A00(float *out, float a, float b);

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
    if (!func_00282978(&state->projectileDelay))
        return;

    func_0029FCC0(LISTED_RECORD(obj, state->projectileIndex), 0, pos);
    func_0029FC20(LISTED_RECORD(obj, state->projectileIndex), 0, matrix);
    func_00282F20(offset, matrix[2], -0.3f);
    func_00282CC0(pos, pos, offset);

    func_002A7A00(jitter, 0.020000001f, 0.060000002f);
    jitter[2] = -0.10000001f;
    qcopy_nc(velocity, jitter);
    func_00282CF0(toTarget, state->aim, pos);
    func_00282F20(toTarget, toTarget, 0.40000004f);
    func_00282CC0(velocity, velocity, toTarget);

    projectile = func_L07_003F6B88(state->projectileClass);
    if (projectile)
        func_L11_00458A98(projectile, LISTED_RECORD(obj, state->projectileIndex), obj->fB8,
                          state->f60, pos, velocity, 120, 0.004f, state->f35);
    ++state->projectileIndex;
    state->projectileDelay = 12;
}


/* Nonmatching: 332/328 bytes.
 * Profile: -O2 -G8 -ffunction-sections.
 * Placement checks: US: 0/1; US2: 0/1; PAL: 0/1.
 * 332/328 bytes. The complete prefix and count-up copy loop agree until an additional NOP at +0x10c shifts the back edge and epilogue. The reviewed qcopy emits two words but is counted as one instruction by post-DBR loop padding (MATCHING-BLOCKERS section30). The subtraction scratch now reserves the full16 bytes written by the callee.
 * Reopen with an independently qualified loop-padding/compiler profile or meaningful loop source change. Indexed helpers and the grouped TI/barrier profile retain this extra NOP; no dummy padding is added.
 */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern void *func_0029EFD0(int);
extern void func_002B37E8(void *, void *);
extern void func_00282CF0(float *, void *, void *);
extern float func_00282E20(float *);
extern float func_00283248(float, float);
extern float func_002A7878(float, float);
extern float D_L20_001B1F98 __attribute__((sda));


/* Spawns a projectile next to its owner and points it at the hero. It also sets the speed, the delay before it moves, its lifetime and its damage. */
char *func_L20_0043F318(char *owner, char *spawnPos, int lifetime, int side, int counterPtr, float damage) {
    char *obj = (char *)CreateMoby(0x119D /* moby class 4509 */);
    char *state;
    float v[4] __attribute__((aligned(16)));
    float randomValue;
    float timer;
    int i;

    if (obj == 0) {
        goto out;
    }
    InitChildObjectFromParent(obj, owner);
    qcopy(obj + 0x10, spawnPos);
    FastVecSub(v, (void *)(obj + 0x10), owner + 0x10);
    state = *(char **)(obj + 0x68);
    *(float *)(state + 0x40) = vec_length_xy(v);
    *(float *)(state + 0x44) = FastMatrixHelperA(v[0], v[1]);
    *(float *)(state + 0x5C) = *(float *)(owner + 0x18);
    randomValue = RandomFloatRange(1.0f, 4.0f);
    *(float *)(state + 0x4C) = *(float *)(state + 0x5C) + randomValue;
    randomValue = RandomFloatRange(0.0f, 1.0f);
    timer = D_L20_001B1F98 + randomValue;
    *(int *)(state + 0x64) = lifetime;
    *(int *)(state + 0x68) = side;
    *(int *)(state + 0x6C) = counterPtr;
    *(float *)(state + 0x70) = damage;
    *(float *)(state + 0x48) = timer;
    for (i = 0; i < 3; i++) {
        qcopy(state + 0x10 + i * 0x10, spawnPos);
    }
out:
    return obj;
}

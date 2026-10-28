/* Nonmatching reconstruction, 2026-10-28. No C coverage credit.
 * Five bounded US checks, 0/28 placements. Best narrow profile:
 * -O2 -G0 -ffunction-sections -frac2-zero-ti-por
 * -frac2-gcse-unsplit-edges gives 628 / 636 bytes, frame0x70 vs0x80.
 * First qcopy body620B; unsplit edges620B; separate later global view628B;
 * pure TI snapshots612B; scoped hero plus broad -fno-gcse632B, rejected.
 * Remaining: saved global high-half lifetime, one absent saved register,
 * linked-list selection scheduling, and collision snapshot address allocation.
 * Reopen with independent hero/global-lifetime evidence.
 *
 * Contracts: 002AD0B0 is signed-int pointer query (actual source definition),
 * 002761F8 returns int and reads its first two complete vectors; last optional
 * 40-byte packet is null here. 00282F20 reads/writes16B, normalizes XYZ and
 * preserves W. 00282CC0/00282D30/00283028 have void returns, two16B input
 * vectors for add/reflect, one16B input for scale. Actual reflect has either
 * full vector load/store or cop2 full store and preserves initialized W.
 * Random is whole-zero initialized before XYZ writes; work is a full copy;
 * normal is fully written before add; random is overwritten by full qcopy
 * before ray use. All caller vector inputs must provide16B as retail reads.
 * Global allocation extents remain incomplete. No volatility/aliases/pins.
 */

#include "common.h"
typedef int ShardQuad __attribute__((mode(TI)));
typedef union { ShardQuad q; float f[4]; } ShardVector;
extern unsigned char D_00189E20[];
extern unsigned char *D_001B1B68;
extern unsigned char D_001BAFA0[];
extern float func_002A7878(float, float);
extern int func_002AD0B0(void *);
extern void func_00282F20(void *, const void *, float);
extern void func_00282CC0(void *, const void *, const void *);
extern void func_00283028(void *, const void *, const void *);
extern void func_00282D30(void *, const void *, float);
extern int func_002761F8(const void *, const void *, int, void *, const void *);

void func_003159D0(float *position, unsigned char *object, float *velocity)
{
    ShardVector work, random, normal;
    unsigned char *state = *(unsigned char **)(object + 0x68);
    unsigned char *hero;
    unsigned char *it;
    unsigned char *oldest;
    unsigned char *excluded;
    int count, time;
    random.q = 0;
    random.f[0] = func_002A7878(-1.0f, 1.0f);
    random.f[1] = func_002A7878(-1.0f, 1.0f);
    random.f[2] = func_002A7878(-1.0f, 1.0f);
    work.q = random.q;
    object[0x20] = 0;
    *(float *)(object + 0x2C) *= 1.5384615659713745f;
    func_00282F20(&work, &work, func_002A7878(0.00016666666488163173f, 0.0016666668234393f));
    func_00282CC0(state, &work, velocity);
    hero = D_00189E20;
    if (*(void **)(hero + 0x33C) && func_002AD0B0(*(void **)(hero + 0x33C)))
        func_00282CC0(state, state, hero + 0x110);
    *(short *)(state + 0x34) = 120;
    count = 0;
    oldest = 0;
    time = 0;
    for (it = D_001B1B68; it; it = *(unsigned char **)(it + 0x28)) {
        if (it[0x20] == 0xFE || it[0x20] == 0xFD) continue;
        if (*(short *)(it + 0xAA) != *(short *)(object + 0xAA) || it == object) continue;
        if (!oldest || *(int *)(*(unsigned char **)(it + 0x68) + 0x5C) < time) {
            time = *(int *)(*(unsigned char **)(it + 0x68) + 0x5C);
            oldest = it;
        }
        count++;
    }
    if (count >= 9) *(int *)(*(unsigned char **)(oldest + 0x68) + 0x5C) = -1;
    qcopy(object + 0x10, position);
    excluded = *(unsigned char **)(D_00189E20 + 0x2290);
    qcopy(&random, excluded + 0x10);
    random.f[2] = position[2];
    if (func_002761F8(&random, position, 0, excluded, 0)) {
        unsigned char *hit = D_001BAFA0;
        qcopy(object + 0x10, hit);
        func_00282F20(&normal, hit + 0x20, 0.0026944444980472326f);
        func_00282CC0(object + 0x10, object + 0x10, &normal);
        func_00283028(state, state, hit + 0x20);
        func_00282D30(state, state, 0.6f);
    }
}

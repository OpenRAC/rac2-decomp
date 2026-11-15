#include "common.h"
typedef int QuadWord __attribute__((mode(TI)));
extern void *func_0029EFD0(int);
extern float func_002A7878(float, float);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282F20(char *, char *, float);
typedef struct { float v[4]; void *owner; int flags; unsigned char mode, enabled; unsigned short kind; float radius; int active; } SweepProbe;
extern float func_00282E20(void *);
extern float func_00283248(float, float);
extern void func_00282F70(void *, void *, float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern char D_L04_001BFAE0[];
extern char D_L04_001BFB00[];
extern char D_L04_001A8F20[] __attribute__((sda));
extern void func_00283028(void *, void *, void *);
extern float func_00282DF0(void *);
extern int func_002A7820(int, int);
extern void func_L04_00358AE8(void *, void *, unsigned int, int, float);
extern void func_L04_00358868(void *, unsigned int, int, int, float);
extern unsigned char *func_L04_0035F3E0(void *, void *, int, float);
extern void func_L04_003F9C60(void *, int);
extern void func_0029F338(void *);
extern float func_002A7AA8(float, float, float, float, float);

/* Spawns a shot moby at pos heading along velocity. If the sweep from the owner to pos is
 * blocked, it bursts into sparks and is deleted at once; otherwise it gets 17 trail particles.
 * The owner is kept as an int: a pointer parameter would let the start-vector load
 * be scheduled above the probe stores. */
/* Creates a homing shot at a position with a velocity, and builds its trail of followers. If the shot would start inside a wall it bursts into sparks at once and returns 0. */
unsigned char *func_L04_003F9320(int owner, float *pos, float *velocity, int life)
{
    float originBuf[4], directionBuf[4];
    float *origin = originBuf, *direction = directionBuf;
    SweepProbe probe;
    float start[4], scratch[4], random[4];
    unsigned char *shot, *vars, *particle;
    int i, trailIndex;
    unsigned short kind;
    float fade, alpha, numerator, denominator;
    *(QuadWord *)origin = *(QuadWord *)pos;
    *(QuadWord *)direction = *(QuadWord *)velocity;
    shot = CreateMoby(0xABC /* moby class 2748 */);
    if (shot) {
        vars = *(unsigned char **)(shot + 0x68);
        *(void **)(vars + 0x18) = (void *)owner;
        shot[0x30] = 0x7F;
        *(short *)(shot + 0x32) = 0x7F;
        shot[0x31] = 1;
        *(long *)(shot + 0x38) = *(long *)(owner + 0x38);
        *(float *)(shot + 0xF0) = 0;
        *(float *)(shot + 0xF4) = -FastMatrixHelperA(vec_length_xy(direction), direction[2]);
        *(float *)(shot + 0xF8) = FastMatrixHelperA(direction[0], direction[1]);
        qcopy((shot + 0x10), origin);
        qcopy(vars, direction);
        *(int *)(vars + 0x10) = life;
        *(int *)(vars + 0x14) = life;
        probe.owner = *(void **)(vars + 0x18);
        probe.flags = 0x30000;
        probe.radius = 13.0f;
        probe.active = 1;
        *(QuadWord *)probe.v = *(QuadWord *)vars;
        FastVectorNormalizeHelper(&probe, &probe, 1.0f);
        probe.v[2] = 1;
        probe.v[3] = 5627.9248046875f;
        probe.mode = 1;
        probe.enabled = 1;
        kind = *(unsigned short *)(shot + 0xAA);
        *(QuadWord *)start = *(QuadWord *)(owner + 0x10);
        probe.kind = kind;
        start[2] = origin[2];
        if (CollLine(start, origin, 0, (void *)owner, &probe)) {
            qcopy((shot + 0x10), D_L04_001BFAE0);
            for (i = 4; i >= 0; i--) {
                *(QuadWord *)random = 0;
                random[0] = RandomFloatRange(-1, 1);
                random[1] = RandomFloatRange(-1, 1);
                random[2] = RandomFloatRange(-1, 1);
                *(QuadWord *)scratch = *(QuadWord *)random;
                FastVectorNormalize(random, vars, D_L04_001BFB00);
                vec_scale_to_length((char *)scratch, (char *)scratch, FastVecLength(random) * 0.5f);
                FastVecAdd(random, random, scratch);
                vec_scale_to_length((char *)random, (char *)random, RandomFloatRange(0.050000004f, 0.10000001f));
                SpawnVelocityParticle(shot + 0x10, random, 0x7F2F4F6F, RandomIntRange(10, 15), 15000);
            }
            DestroyMobyEffectsWithBurst(shot, 0);
            MarkMobySpawned(shot);
            return 0;
        }
        SpawnJointFollowParticle(shot, 0x2F4F7F7F, *(int *)(vars + 0x10), -1, 100000);
        for (trailIndex = 0; trailIndex < 17; trailIndex++) {
            particle = SpawnRandomEffectRecord(shot + 0x10, D_L04_001A8F20, 1, 0);
            if (particle) {
                *(float *)(particle + 0xC) = RandomFloatRange(15000, 25000);
                numerator = IntToFloat(trailIndex);
                denominator = IntToFloat(16);
                fade = cubic_hermite_scalar(-1.5f, 0, 1, 0, numerator / denominator);
                *(float *)(particle + 0xC) += (8000.0f - *(float *)(particle + 0xC)) * fade;
                alpha = fade * -64.0f + 128.0f;
                *(unsigned int *)(particle + 4) = (FloatToInt(alpha) << 24) | 0xFFFFFF;
                *(void **)(vars + 0x1C + trailIndex * 4) = particle;
            } else *(void **)(vars + 0x1C + trailIndex * 4) = 0;
        }
    }
    return shot;
}

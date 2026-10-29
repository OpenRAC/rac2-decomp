/* Retained paired-particle burst, 2026-10-28: best680/720B,0/27US.
 * Two bounded trials: default680/frameE0; no-rerun-loop-opt664/frameD0.
 * Retail preserves an otherwise unused ANDI V0,V0,1 after the raw RNG call;
 * truthful ordinary C retains the RNG side effect but drops the dead mask.
 * Do not manufacture an argument/dependency, false return type or volatile
 * local merely to preserve it. Other gaps are FP invariant hoists/allocation.
 * Actual002C2210 matched definition returns Particle*, consumes position16B
 * but vectorXYZ only12B, writes its own positionW, and has sevenGPR+threeFP.
 * Its allocated record is64B; byte9 set here is inside its real header.
 * Scratch matrix48B (three rows), vectors16B each. Source snapshot copy is a
 * real retail transfer even though the copied value is not later consumed.
 */
#include "common.h"
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern int func_002A77E0(int);
extern int func_001163B0(void);
extern int func_00283CF0(float);
extern void func_002833F0(void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern u8 *func_002C2210(float, float, float, void *, int, int, int, int, float *, int);

/* The real particle constructor returns its allocated pointer; it consumes
 * all16 position bytes, three velocity floats, and writes position W itself.
 * Three-row rotation output is48B, with complete aligned scratch vectors. */
void func_L00_003BD510(float *position, void *direction, int count, int color)
{
    float velocity[4] __attribute__((aligned(16)));
    float snapshot[4] __attribute__((aligned(16)));
    float rotation[4] __attribute__((aligned(16)));
    float matrix[12] __attribute__((aligned(16)));
    float scale;
    int sign, coin;
    u8 *particle;
    if (count <= 0)
        return;
    do {
        scale = func_002A7878(1.75f, 2.0f);
        sign = func_002A77E0(2);
        if (sign == 0)
            sign = -1;
        rotation[3] = 0;
        rotation[1] = func_002A7878(-1.5707963705062866f, 1.5707963705062866f);
        rotation[0] = func_002A7878(-1.5707963705062866f, 1.5707963705062866f);
        rotation[2] = func_002A7878(-1.5707963705062866f, 1.5707963705062866f);
        func_002833F0(matrix, rotation);
        func_00283098(velocity, direction, matrix);
        func_00282F20(velocity, velocity, 0.05f);
        velocity[2] += 0.05f;
        qcopy(snapshot, position);
        position[0] += func_002A78D8(0.0f, 0.15f);
        position[1] += func_002A78D8(0.0f, 0.15f);
        position[2] += func_002A78D8(0.0f, 0.15f);
        coin = func_001163B0() & 1;
        (void)coin;
        particle = func_002C2210(scale * 0.1f, scale, 0.002f, position, 60, color | 0x4F000000, 0, sign, velocity, 1);
        if (particle)
            particle[9] = func_00283CF0(4.0f) + 0x70;
        particle = func_002C2210(scale * 0.07f, scale * 0.7f, 0.002f, position, 60, 0x7FFFFFFF, 1, -sign, velocity, 1);
        if (particle)
            particle[9] = func_00283CF0(4.0f) + 0x70;
    } while (--count);
}

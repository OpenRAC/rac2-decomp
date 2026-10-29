/* Retained spark-burst reconstruction, 2026-10-28.
 * Six bounded trials: 600 -> 612/620 bytes, 0/27 US placements.
 * Best profile: -O2 -G0 -ffunction-sections -frac2-zero-ti-por -frac2-qcopy.
 * Ordinary qcopy gives600; grouped TI copy gives612. Moving selector reset to
 * loop tail gives628 and truthful MOVN but retains a loop-carried selector.
 * Narrow fno-cse-follow-jumps gives600; fno-rerun-cse-after-loop gives600;
 * broad fno-gcse gives612 (no improvement, not retained as a required flag).
 * Retail caches a separate invariant one and copies it into the selector;
 * ordinary C lowers the local boolean to SLTIU. Copy address also differs.
 * RNG order is the actual order: tilt, angle, speed, raw RNG, transform, life.
 * Each input velocity/position read by00308600 is16B; +134 returns created
 * object pointer. The constructor source/RAC1 correspondence and full RAC2
 * callee disassembly were audited. No fake void prototype or short vector.
 */
#include "common.h"

typedef s32 Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_00282FB8(void *, void *, float);
extern float func_002A7878(float, float);
extern float func_002A7940(void);
extern int func_002A7820(int, int);
extern int func_001163B0(void);
extern void func_002AF000(void *, float, float, float);
extern void *func_00308600(void *, void *, int, int, int);
extern Vector D_L00_001B8DC0;

/* Camera-biased falling-spark burst. All three vectors are complete 16-byte
 * objects. The random vector is cleared before XYZ writes and full transfer.
 * Related RAC1 donor: moby_ground_collision.c spawn_explosion, GPL-3.0;
 * reconstructed from RAC2 bytes with verified canonical helper interfaces. */
void func_L00_003E5340(u8 *object, void *position)
{
    Vector delta, velocity, random;
    float distance, angle, tilt;
    int count = 8;
    int selected;
    func_00282CF0(&delta, &D_L00_001B8DC0, position);
    distance = func_00282DF0(&delta);
    random.q = 0;
    random.f[0] = func_002A7878(-1.0f, 1.0f);
    random.f[1] = func_002A7878(-1.0f, 1.0f);
    random.f[2] = func_002A7878(-1.0f, 1.0f);
    delta.f[2] += distance * 0.5f;
    velocity.q = random.q;
    func_00282F20(&velocity, &velocity, distance * 0.0033333336468786f);
    distance += distance;
    func_00282F20(&delta, &delta, distance * 0.01666666753590107f);
    func_00282CC0(&velocity, &velocity, &delta);
    func_00282FB8(&velocity, &velocity, 0.1666666716337204f);
    func_00308600(position, &velocity, func_002A7820(60, 90), 0, 0);
    do {
        tilt = func_002A7878(0.2617994248867035f, 1.3089970350265503f);
        angle = func_002A7940();
        func_002AF000(&random, func_002A7878(8.0f, 12.0f) * 0.01666666753590107f, angle, tilt);
        random.f[2] += 0.05000000447034836f;
        selected = 1;
        if (func_001163B0() % 3 != 0)
            selected = 0;
        func_00283098(&random, &random, object + 0xC0);
        func_00308600(position, &random, func_002A7820(60, 90), selected, 0);
    } while (--count >= 0);
}

/* Nonmatching reconstruction, 2026-10-28. No C coverage credit.
 * US: 0/2 places; compiled / retail 624 / 624 bytes.
 * Best profile: -O2 -G0 -ffunction-sections -frac2-zero-ti-por.
 * Ten bounded trials: first qcopy body 620B; TI copy and separate counter
 * scopes 624B; naming the velocity pointer before the burst loop corrected
 * its initialization order. Only the three smoke preheader initializers
 * at +0x140..+0x148 remain permuted: counter before color low-half / -1,
 * versus retail color / -1 / counter. No wrong instructions or registers.
 * -fno-strength-reduce is identical; disabling sched1 gives 620B with broader
 * changes. Short counter and separated color assignment are worse (616/620).
 * No broad scheduling flag retained. Reopen with independent loop-source evidence.
 *
 * Both particle constructors return a real pointer, including the ignored
 * first result. 00358AE8 reads 16B each at a0 position and a1 velocity;
 * 002BDCE8 reads 16B each at a0 position and a2 parameters. The latter takes
 * a1 signed direction, a3 color, t0 integer, and f12..f15 four floats.
 * Both local vectors are fully initialized: whole zero then XYZ writes,
 * whole TI copy, full vector normalization; smoke parameters whole zero
 * then Z/W overwrite. No local padding or unstored fourth component is read.
 * 002B9180 has one observed actor input; its raw-only void-return
 * hypothesis remains provisional, since no common result does not prove
 * void. Complete read/write extents were checked independently.
 * TI assignment is required for the observed load from SP+0x10 to schedule
 * into the following random call; approved qcopy instead ties it to S0.
 */

#include "common.h"
typedef int BurstQuad __attribute__((mode(TI)));
typedef union { BurstQuad q; float f[4]; } BurstVector;
extern void func_002B9180(void *);
extern float func_002A7878(float, float);
extern int func_002A7820(int, int), func_002A77E0(int);
extern void func_00282F20(void *, const void *, float);
extern unsigned char *func_L04_00358AE8(void *, void *, int, int, float);
/* Integer arguments occupy a0..t0; the four floats occupy f12..f15.
 * The constructor reads a full vector from each pointer and returns the particle. */
extern unsigned char *func_002BDCE8(void *, float, float, float, float, int, void *, unsigned int, int);

void func_L04_003F9C60(unsigned char *object, int burst)
{
    BurstVector work, direction;
    int clear = 16;
    unsigned char **slot = (unsigned char **)(*(unsigned char **)(object + 0x68) + 0x1C);
    unsigned char *particle;
    unsigned char *state;
    unsigned int color;
    int sign;
    do {
        clear--;
        if (*slot) func_002B9180(*slot);
        *slot = 0;
        slot++;
    } while (clear >= 0);
    if (burst) {
        BurstVector *velocity = &direction;
        for (clear = 4; clear >= 0; clear--) {
            direction.q = 0;
            direction.f[0] = func_002A7878(-1.0f, 1.0f);
            direction.f[1] = func_002A7878(-1.0f, 1.0f);
            direction.f[2] = func_002A7878(-1.0f, 1.0f);
            work.q = direction.q;
            func_00282F20(velocity, &work, func_002A7878(0.05000000447034836f, 0.10000000894069672f));
            func_L04_00358AE8(object + 0x10, velocity, 0x7F2F4F6F, func_002A7820(10, 15), 35000.0f);
        }
    }
    {
    const unsigned int baseColor = 0x606060;
    const int negativeSign = -1;
    int i;
    i = 2;
    do {
        color = (func_002A7820(32, 128) << 24) | baseColor;
        sign = 1;
        if (func_002A77E0(2)) sign = negativeSign;
        work.q = 0;
        work.f[2] = 1.0f;
        work.f[3] = 1.0f;
        work.f[2] = func_002A7878(0.01f, 0.025f);
        particle = func_002BDCE8(object + 0x10, 0.2f, 1.0f, 1.02f, 140000.0f, sign, &work, color, 0);
        state = particle + 0x20;
        if (particle) {
            *(short *)(particle + 0xA) = func_002A7820(50, 80);
            state[0xA] = (int)color >> 24;
            *(int *)(state + 4) = 2;
            state[0xB] = particle[0xA];
            if (func_002A77E0(2)) particle[3] = 0x44;
        }
        i--;
    } while (i >= 0);
    }
}

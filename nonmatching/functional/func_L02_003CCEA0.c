/* functional: high. Near-miss draft within a few instructions of retail: differences are register allocation, scheduling and instruction shape. */
/* GPT-6.1 Sol high, 2026-10-29: 328/328 bytes, 0/2 USA v1.01 places.
 * Default -O2 -G0 -ffunction-sections. Four instruction words differ at
 * +0xC4, +0xC8, +0xD0 and +0xD8: cc1 uses an annulled branch with the
 * in-range yaw store in its delay slot; retail forms the vector
 * argument there and stores the clamped yaw in the following jal delay slot.
 * Ordinary, call-argument-comma and full-expression-comma forms compile
 * identically; -frac2-gcse-unsplit-edges is also unchanged. Separate stores
 * in the three arms shrink to 324 bytes and do not recover the retail tail.
 * Corrected the older reconstruction: the transform call always takes the
 * result vector for BOTH vector arguments; yaw is always stored and the
 * horizontal-length helper is always called. Pitch uses its float return,
 * not result.x. qcopy recovers the frame and opening register allocation.
 * Reopen with a new hypothesis for the yaw-store/call-argument lifetime.
 * All required declarations are below; the source marker is restored.
 */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern void func_00282CF0(float *, const float *, const float *);

extern void func_002AFDD8(unsigned char *, unsigned char *, unsigned char *, int);

extern float func_00283248(float, float);

extern float func_00282E20(char *);

/* The zero vector the boot keeps for the shared helper. */
extern float D_00189F00[];

void func_L02_003CCEA0(char *a0) {
    char *s0 = a0;
    char *s1 = *(char **)(s0 + 0x68);
    TI128 v[2];
    float f;

    qcopy(&v[1], s0 + 0x10);
    *(float *)((char *)&v[1] + 8) += 1.0f;
    if (*(unsigned char *)(s0 + 0x20) == 0xB) {
        func_00282CF0((float *)&v[0], (float *)(s1 + 0x360), (float *)&v[1]);
    } else {
        func_00282CF0((float *)&v[0], D_00189F00, (float *)&v[1]);
    }
    func_002AFDD8((unsigned char *)s0, (unsigned char *)&v[0],
                 (unsigned char *)&v[0], 0);
    f = func_00283248(*(float *)&v[0], *(float *)((char *)&v[0] + 4));
    if (f > 0.7853982448577881f)
        f = 0.7853982448577881f;
    else if (f < -0.7853982448577881f)
        f = -0.7853982448577881f;
    *(float *)(s1 + 0x278) = f;
    f = func_00282E20((char *)&v[0]);
    f = -func_00283248(f, *(float *)((char *)&v[0] + 8));
    if (f > 0.523598849773407f)
        f = 0.523598849773407f;
    else if (f < -0.523598849773407f)
        f = -0.523598849773407f;
    *(float *)(s1 + 0x2F4) = f;
}

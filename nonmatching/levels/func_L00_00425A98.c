/* func_L00_00425A98 - retained C reconstruction, not an exact match.
 * Profile: -O2 -G8 -ffunction-sections.
 * Measured in src/levels/shared/L00_00425A98-g8.c: 556/568 bytes.
 * US: 0/27 local places; PAL: ABSENT; US2: 0/27 local places.
 * No strict linked build was run because no local placement matched.
 * Shared hero/camera address lifetimes and conditional output scheduling differ. Ordered NaN guards and the complete fallback are retained. Reopen with actual field views or allocator evidence.
 */

#include "common.h"

extern char D_L00_001B8E20[];
extern char D_00189E20[];
extern float D_L00_001B14E0 __attribute__((sda));
extern float D_L00_001B14E4 __attribute__((sda));
extern float D_L00_001B1508 __attribute__((sda));
extern float D_L00_001B150C __attribute__((sda));
extern float func_00282DB0(void *, void *);
extern float func_00282C48(float);
extern void func_L00_00424A08(int, float, float);

void func_L00_00425A98(char *object, float *first, float *second)
{
    char *state = *(char **)(object + 0x70);
    char *control = state + 0x240;
    char *movement = state + 0x160;
    char *camera = D_L00_001B8E20;
    float weight;
    float target;
    float candidate;
    if (*(short *)(control + 6)) goto fallback;
    if (*(short *)(control + 4) && *(float *)(camera + 0xA4) == 0.0f) {
        if (func_00282DB0(*(char **)(D_00189E20 + 0x2290) + 0xC0, object) <= -0.3f)
            goto active;
    }
    if (!(func_00282C48(*(float *)(camera + 0xA4)) > 0.0001f)) goto fallback;
    if (!(func_00282DB0(camera + 0x80, object) <= -0.3f)) goto fallback;
active:
    *(short *)(control + 4) = 120;
    weight = *(float *)(camera + 0xA4) * 14.2857f;
    if (weight > 1.0f) weight = 1.0f;
    target = *(unsigned char *)(D_00189E20 + 0x22B4) == 1 ? 4.0f : *(float *)(control + 0xC);
    candidate = *(float *)(movement + 0x58);
    candidate += (target - candidate) * weight;
    if (candidate > *(float *)(control + 8)) *(float *)(control + 8) = candidate;
    func_L00_00424A08(0, *(float *)(control + 8), 0.003f);
    *first = D_L00_001B14E0 + (D_L00_001B1508 - D_L00_001B14E0) * weight;
    *second = D_L00_001B14E4 + (D_L00_001B150C - D_L00_001B14E4) * weight;
    return;
fallback:
    if (*(short *)(control + 4)) {
        *(short *)(control + 4) = 0;
        *(float *)(control + 8) = *(float *)(movement + 0x58);
    }
    if (*(int *)(D_00189E20 + 0x2294) == 0x84) {
        *first = 0.04f;
        *second = 0.2f;
    } else {
        *first = D_L00_001B14E0;
        *second = D_L00_001B14E4;
    }
}
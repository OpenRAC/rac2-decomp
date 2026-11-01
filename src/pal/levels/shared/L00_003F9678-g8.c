#include "include_asm.h"

#include "common.h"
extern unsigned char D_00189E20[];
typedef int HitWord128 __attribute__((mode(TI)));
typedef union { HitWord128 word; float values[4]; } HitVector;
typedef struct {
    char prefix[4];
    unsigned char enabled;
    char middle[0x74 - 5];
    float scale;
    char suffix[0xE0 - 0x78];
} HitTuning;
typedef struct {
    HitVector direction;
    void *owner;
    int flags;
    unsigned char enabled, kind;
    unsigned short classId;
    float scale;
    int active;
    char suffix[12];
} HitRequest;
extern unsigned char D_00139568[];
extern HitTuning D_L00_00262570[] __attribute__((nosda));
extern int D_L00_001ADB2C;
extern char *D_L00_001C3280[] __attribute__((nosda));
extern void *func_PAL_L00_003FB330(void *, float, float, int, int, int, int, int, int, int, int, int, int, int);
extern void func_00282F20(void *, void *, float);
extern int func_00277F48(void *, int, void *, void *, float);
extern int func_PAL_00335DD0(char *, int, int);
extern int func_002A7820(int, int);
extern int func_002A77E0(int);
extern float func_002A78D8(float, float);
extern char *func_002C2210(void *, int, float, float, unsigned int, int, int, void *, float, int);

/* Apply the configured area hit, or emit eight pairs of particles around the impact.
 * The hit request and particle vectors share one scratch area. Integer and FP
 * arguments retain the measured order within their independent EE register banks. */
void func_PAL_L00_003F97D0(char *object, HitVector *source)
{
    char *state = *(char **)(object + 0x68);
    struct {
        HitVector position;
        union { HitRequest request; struct { HitVector zero, jitter; } particles; } u;
    } scratch;
    int count, i;
    int particle;

    qcopy(&scratch.position, source);
    if (D_L00_00262570[D_00139568[0x17]].enabled) {
        func_PAL_L00_003FB330(object + 0x10, 1.0f, 20.0f, 1, 0x28, 0x14, 0x1E, 0x28, 0x32, 1,
                      1, 1, 0, D_L00_001ADB2C);
        scratch.u.request.flags = 0x810000;
        scratch.u.request.active = 1;
        scratch.u.request.owner = object;
        scratch.u.request.scale = D_L00_00262570[D_00139568[0x17]].scale;
        qcopy(&scratch.u.request.direction, state);
        func_00282F20(&scratch.u.request.direction, &scratch.u.request.direction, 1.0f);
        scratch.u.request.direction.values[3] = 5627.9248046875f;
        scratch.u.request.enabled = 3;
        scratch.u.request.kind = 2;
        scratch.u.request.classId = *(unsigned short *)(object + 0xAA);
        count = func_00277F48(&scratch.position, 1, *(char **)(D_00189E20 + 0x2290), &scratch.u.request, 2.0f);
        for (i = 0; i < count; i++)
            func_PAL_00335DD0(D_L00_001C3280[i], 0x42, *(int *)(object + 0xB8));
    } else {
        int negative;
        HitVector *jitter, *zero;
        scratch.u.particles.zero.word = 0;
        negative = -1;
        jitter = &scratch.u.particles.jitter;
        zero = &scratch.u.particles.zero;
        particle = 7;
        do {
            int lifetime = func_002A7820(6, 16);
            int sign = func_002A77E0(2) ? negative : 1;
            scratch.u.particles.jitter.values[0] = scratch.position.values[0] + func_002A78D8(0.0f, 0.5f);
            scratch.u.particles.jitter.values[1] = scratch.position.values[1] + func_002A78D8(0.0f, 0.5f);
            scratch.u.particles.jitter.values[2] = scratch.position.values[2] + func_002A78D8(0.0f, 0.5f);
            func_002C2210(jitter, lifetime, 10.0f, 0.1f, 0x4010FF10, 2, sign, zero, 0.0f, 1);
            func_002C2210(jitter, lifetime, 2.0f, 0.1f, (int)0xC0FFFFFF, 2, sign, zero, 0.0f, 1);
        } while (--particle >= 0);
    }
}

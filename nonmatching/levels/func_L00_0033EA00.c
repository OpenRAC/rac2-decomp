/* Nonmatching C reconstruction.
 * Profile: -O2 -G8 -ffunction-sections -frac2-qcopy -frac2-zero-ti-por.
 * Compiled 576 bytes; retail 584 bytes.
 * Carrying checks: 0/27 in us and us2; PAL ABSENT. No strict linked qualification.
 * Retail snapshots sixteen bytes of position at +0x98 to caller sp+0x10, with no identified later consumer. The complete inspected emitter reads only its ninth GPR argument at caller sp+0. That unexplained dead snapshot is omitted under the strict source policy. Reopen only after proving a real snapshot consumer or aggregate ABI reason; do not add an unused local or padding.
 */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef struct {
    unsigned char b0, b1, b2, b3;
    int color;
    unsigned char seed, alpha;
    unsigned short size;
    float life;
    union { Quad q; float f[4]; } position;
    float payload[8];
} Particle;
typedef union { Quad q; float f[4]; } EffectQuad;
extern Particle *func_002BCB00(float, Quad *, Quad *, int, int, int, int, int, int, int);
extern int func_00282978(short *);
extern void func_002B9180(void *);
extern float func_00283CE0(int);
extern int func_L00_0031C998(int, int, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00300190(void *, void *);
extern float func_002A7878(float, float);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282D30(void *, void *, float);
extern int func_002A7820(int, int);
extern int func_00283CF0(float);
extern int D_L00_001B19C8 __attribute__((sda));

void func_L00_0033EA00(unsigned char *particle)
{
    EffectQuad randomVector __attribute__((aligned(16)));
    EffectQuad velocity __attribute__((aligned(16)));
    char *data = (char *)particle + 0x20;
    float *position = (float *)(particle + 0x10);
    float remaining;
    float magnitude;
    int count;
    int weight;
    if (func_00282978((short *)(particle + 0xA))) {
        func_002B9180(particle);
        return;
    }
    remaining = func_00283CE0(*(short *)(particle + 0xA));
    *(int *)(particle + 4) = func_L00_0031C998(*(int *)(data + 0x14), *(int *)(data + 0x10),
                          remaining / func_00283CE0(*(short *)(data + 0x18)));
    func_00282CC0(position, position, data);
    *(float *)(data + 8) -= *(float *)(data + 0xC);
    if (position[3] != 0.0f) {
        if (position[3] == 2.0f)
            func_00300190(position, position);
        position[3] = 2.0f;
    }
    if (*(short *)(data + 0x1A) && (D_L00_001B19C8 & 1)) {
        randomVector.q = 0;
        randomVector.f[0] = func_002A7878(-1.0f, 1.0f);
        randomVector.f[1] = func_002A7878(-1.0f, 1.0f);
        randomVector.f[2] = func_002A7878(-1.0f, 1.0f);
        qcopy(&velocity, &randomVector);
        magnitude = func_00282DF0(data);
        func_00282F20(&velocity, &velocity, magnitude * func_002A7878(0.15f, 0.25f));
        func_00282CC0(&velocity, &velocity, data);
        func_00282D30(&velocity, &velocity, func_002A7878(0.75f, 0.95f));
        count = func_002A7820(15, 30);
        weight = func_00283CF0(position[3]);
        func_002BCB00(*(float *)(particle + 0xC), (Quad *)position, &velocity.q,
                       *(int *)(particle + 4), *(int *)(data + 0x14), count, 0,
                       particle[2], particle[3], weight);
    } else {
        func_00282D30(data, data, 0.9599999785423279f);
    }
}

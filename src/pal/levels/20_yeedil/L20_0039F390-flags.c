#include "include_asm.h"

#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
extern int func_002A77E0(int);
extern unsigned char *func_002C65A0(void *, void *, int, int, int, int, int, float, float, float, int);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern void func_00282CF0(void *, const void *, const void *);
extern void func_00282D30(void *, const void *, float);
extern void func_00282CC0(void *, const void *, const void *);
extern Vector D_L20_001A8F20 __attribute__((sda));
extern unsigned char *D_L20_001FFC14;
extern unsigned char *D_L20_001FFBF4;
extern int D_L20_001B2AC8[] __attribute__((sda));

void func_PAL_L20_0039F518(unsigned char *object) {
    Vector delta, position, jitter;
    unsigned char *state = *(unsigned char **)(object + 0x68);
    unsigned char *particle;
    int shade = func_002A77E0(255);
    int count;
    float size;
    particle = func_002C65A0(object + 0x10, &D_L20_001A8F20, 2, 0x202080, shade, 64, 16,
                            420000.0f, 420000.0f, 0.0f, 0);
    if (particle) {
        particle[2] = *D_L20_001FFC14;
    }
    particle = func_002C65A0(object + 0x10, &D_L20_001A8F20, 2, 0x202080, (shade + 128) % 255, 64, 16,
                            420000.0f, 420000.0f, 0.0f, 0);
    if (particle) {
        particle[2] = *D_L20_001FFC14;
    }
    func_00282CF0(&delta, object + 0x10, state);
    func_00282D30(&delta, &delta, 0.1f);
    qcopy(&position, state);
    count = 4;
    do {
        --count;
        shade = func_002A77E0(255);
        size = func_002A7878(0.1f, 0.3f);
        jitter.f[0] = position.f[0] + func_002A78D8(0.0f, 0.05f);
        jitter.f[1] = position.f[1] + func_002A78D8(0.0f, 0.05f);
        jitter.f[2] = position.f[2] + func_002A78D8(0.0f, 0.05f);
        func_002C65A0(&jitter, &D_L20_001A8F20, 12, 0x808080, shade, 32, 0,
                      size * 210000.0f, size * 42000.0f, 0.0f, 0);
        func_00282CC0(&position, &position, &delta);
    } while (count >= 0);
    if (D_L20_001B2AC8[0] % 10 == 0) {
        particle = func_002C65A0(object + 0x10, &D_L20_001A8F20, 25, 0x202080, 0, 32, 0,
                                2100.0f, 420000.0f, 0.0f, 0);
        if (particle) {
            particle[2] = *D_L20_001FFBF4;
        }
    }
}

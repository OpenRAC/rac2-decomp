/* func_PAL_L00_00343940, the PAL copy of func_L00_00341410: the same C, where scale func_002A7820(minimum, maximum). */
/* func_PAL_L00_00343940 in its own unit (flags in config/cflags.txt: -O2 -G0 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier). */

typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
typedef struct {
    unsigned char unknown_00[0x10];
    Vector position;
    unsigned char unknown_20[0xA0];
    float matrix[16];
} ParticleOwner;
extern unsigned char *func_002B9030(int);
extern int func_00283CF0(float);
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern unsigned char *D_L00_001FEAF8;
extern void func_00282C88(Quadword *);
extern void func_00283098(void *, const void *, const void *);
extern void func_00282CC0(void *, const void *, const void *);
extern void func_002FE8D8(void *, void *);
extern void func_00282D30(void *, const void *, float);

unsigned char *func_PAL_L00_00343940(ParticleOwner *owner, Quadword *position,
                              int flags, int minimum, int maximum, float scale) {
    union { Quadword q; float f[4]; } direction;
    unsigned char *particle = func_002B9030(0x6E);
    unsigned char *motion;
    Vector *origin;
    int shade;
    if (particle) {
        motion = particle + 0x20;
        particle[9] = func_00283CF0(4.0f) + 0x40;
        particle[3] = flags;
        particle[1] = 0;
        particle[8] = func_002A77E0(255);
        particle[2] = *D_L00_001FEAF8;
        *(short *)(particle + 0xA) = (((int)(func_002A7820(minimum, maximum)) * 5 + 2) / 6);
        *(int *)(motion + 0x18) = *(short *)(particle + 0xA);
        *(float *)(particle + 0xC) = scale * 630000.0f;
        if (((float *)position)[3] == -1.0f) {
            func_00282C88(&direction.q);
            direction.f[3] = 1.0f;
            direction.f[0] = -0.3f;
            func_00283098(&direction, &direction, owner->matrix);
            func_00282CC0(particle + 0x10, &direction, &owner->position);
        } else {
            *(Quadword *)(particle + 0x10) = *position;
        }
        origin = &owner->position;
        *(float *)(particle + 0x10) += func_002A7878(-0.015f, 0.015f);
        *(float *)(particle + 0x14) += func_002A7878(-0.015f, 0.015f);
        *(float *)(particle + 0x18) += func_002A7878(-0.015f, 0.015f);
        func_002FE8D8(origin, &direction);
        func_00282D30(motion, &direction, func_002A7878(0.01f, 0.015f));
        *(int *)(motion + 0x10) = func_002A7820(80, 200);
        shade = func_002A7820(96, 128);
        *(int *)(motion + 0x14) = shade + (shade << 8) + (shade << 16);
        *(unsigned int *)(particle + 4) = *(int *)(motion + 0x14) | (*(unsigned int *)(motion + 0x10) << 24);
    }
    return particle;
}

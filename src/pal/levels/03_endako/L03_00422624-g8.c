#include "include_asm.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef float f32;
extern u8 *D_L03_001B2A1C __attribute__((sda));
extern s32 D_L03_001B108C __attribute__((sda));
extern u32 D_L03_001B1058 __attribute__((sda));
extern int func_002A77E0(int id);
extern void func_00282948(void *target);
extern void func_00282978(void *target);
extern void func_002AEC48(void *entity, void *target, int a, float f0, float f1);
extern void func_002AFDD8(void *entity, void *out, void *target, int a);
extern void func_0029FCC0(void *entity, int a, void *out);
extern u8 *func_PAL_002BE9A8(void *p, float f0, float f1, float f2, int z, void *local,
                         float f3, int v, int t);
extern int func_00283CF0(float f);
extern void func_PAL_002B14F8(void *entity, float *target, float f, int a, int b);
extern float D_L03_001B1BF0 __attribute__((sda));
extern f32 D_L03_001B1C00 __attribute__((sda));
extern f32 D_L03_001B1C04 __attribute__((sda));
extern s32 func_002B38B8();
typedef struct {
    s32 a;
    s32 b;
    f32 c;
    f32 d;
} ParticleSetup;
extern u8 *D_L03_001FB5A0[];
extern s32 D_L03_001A8F00 __attribute__((sda));
extern s32 func_3240F0(u8 *a0);

/* Sets the entity's two blend channels up, then fires two particles: the engine builds
 * each one from the state's direction, a random count and a colour, and the caller fills
 * the record's own fields in.  The two blocks fill the FIRST particle's header again, and
 * the second one keeps its own pointer to the sub-record: both are the original's own
 * wording, and the compiler's schedule depends on it. */
void func_PAL_L03_004233F0(u8 *entity) {
    u8 *state = *(u8 **)(entity + 0x68);
    float buf[4];
    ParticleSetup setup;
    float vec[4];
    u16 timer;
    s32 count;
    f32 f;
    u8 *particle;
    u8 *particle2;
    u8 *data;
    u8 *data2;

    func_00282948(state + 0x34C);
    func_00282978(state + 0x330);
    func_00282978(state + 0x332);
    func_002AEC48(entity, state + 0x220, 0, 0.0432f, 0.43200004f);
    func_002AEC48(entity, state + 0x2A0, 1, 0.0432f, 0.43200004f);
    timer = *(u16 *)(entity + 0x96);
    if (timer <= 0xFFFE)
        *(u16 *)(entity + 0x96) = timer + 1;
    func_002AFDD8(entity, buf, state + 0x1A0, 0);
    f = buf[1] * D_L03_001B1BF0;
    *(float *)(entity + 0xF0) = f;
    /* The four words the engine reads the particle's setup from, in the order the
     * original stores them. */
    setup.a = 0;
    setup.c = -0.02f;
    setup.d = 1.0f;
    setup.b = 0;
    count = func_002A77E0(16);
    if (func_002A77E0(2))
        count = -count;
    func_0029FCC0(entity, 4, vec);
    vec[2] += 0.1f;
    particle = func_PAL_002BE9A8(vec, 0.1f, 1.0f, 0.9f, count, &setup,
                             105000.0f, 0xDF204080, 0);
    if (particle != 0) {
        data = particle + 0x20;
        *(u16 *)(particle + 0xA) = 4;
        particle[9] = func_00283CF0(4.0f) + 0x70;
        *(u32 *)(data + 4) = 2;
        data[0xA] = 0xDF;
        data[0xB] = particle[0xA];
    }
    particle2 = func_PAL_002BE9A8(vec, 0.1f, 1.0f, 0.9f, count, &setup,
                              105000.0f, 0xDF204080, 0);
    data2 = particle2;
    if (data2 != 0) {
        *(u16 *)(particle + 0xA) = 4;
        data2 += 0x20;
        particle[9] = func_00283CF0(4.0f) + 0x70;
        *(u32 *)(data2 + 4) = 2;
        data2[0xA] = 0xDF;
        data2[0xB] = particle[0xA];
    }
    if (entity[0x31] != 0)
        func_PAL_002B14F8(entity, (float *)(state + 0x360), 2.5f, 5, 1);
}

extern u8 *func_002BDCE8(void *p, float f0, float f1, float f2, int z, void *local,
                         float f3, int v, int t);

/* Same walk as func_L03_0041D0A8 after seeding two state halfwords. */
void func_PAL_L03_00423688(u8 *entity) {
    u8 *state = *(u8 **)(entity + 0x68);
    u8 *list;
    u8 *p;
    u8 *base;

    *(short *)(state + 0x336) = 1;
    *(short *)(state + 0x330) = 0xC8;
    if (entity[0x21] == 0xFF)
        return;
    list = D_L03_001FB5A0[entity[0x21]];
    if (list == 0)
        return;
    p = list;
    base = D_L03_001B2A1C;
    for (;;) {
        u8 *q = base + ((*(unsigned short *)p & 0x7FFF) << 8);

        if (*(signed char *)(q + 0x20) >= 0) {
            if (*(short *)(q + 0xAA) == 0xFFC) {
                *(short *)(*(u8 **)(q + 0x68) + 0x336) = 1;
            }
        }
        if (*(short *)p < 0)
            break;
        p += 2;
    }
}

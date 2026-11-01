#include "include_asm.h"

#include "common.h"
extern void func_00282CF0(float *off, float *v, char *p);
extern void func_00282F20(float *dst, float *src, float angle);
typedef unsigned int JointEffectQuad __attribute__((mode(TI)));
extern void func_0029FC20(char *, int, float *);
extern void func_00282CC0(float *, float *, float *);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern int func_002A7820(int, int);
extern void func_002ACB48(float *, float);
extern int func_002A8C28(char *, float *, float, int, float, float, int, int, int);
extern void *func_002C65A0(float *, float *, float, float, float, int, int, int, int, int, int);
extern unsigned char *func_PAL_002C23B8(float *, float *, int, int, int, int,
                                    float, float, float, float, float);
extern unsigned char *D_001F2540[];

/* Effect at an object's joint: func_002A8C28 at the joint and at two points along its axis,
   three grey func_002C65A0 particles at the joint and one func_PAL_002C23B8 particle at the near
   point, which at random takes flags 0x48 and the 0x707070 tint. */
void func_PAL_00323D48(char *object, float *position, int joint, float intensity)
{
    float matrix[16] __attribute__((aligned(16)));
    float axis[4] __attribute__((aligned(16)));
    float base[4] __attribute__((aligned(16)));
    float near[4] __attribute__((aligned(16)));
    float far[4] __attribute__((aligned(16)));
    float velocity[4] __attribute__((aligned(16)));
    float drift[4] __attribute__((aligned(16)));
    int i, j;
    float start, end, gravity;
    unsigned char *particle;

    func_0029FC20(object, joint, matrix);
    qcopy(axis, matrix + 4);
    func_00282CF0(base, matrix + 12, (char *)position);
    func_00282F20(near, axis, 0.85f);
    func_00282F20(far, axis, 1.6f);
    func_00282CC0(near, near, base);
    func_00282CC0(far, far, base);
    near[2] -= 0.1f;
    far[2] -= 0.1f;
    func_00282F20(velocity, matrix + 4, 0.3f);
    func_00282CC0(velocity, velocity, position);
    func_002A8C28(object, base, 0.3f, 1, intensity, 1.0f, 0, 1, 0);
    func_002A8C28(object, near, 0.3f, 1, intensity, 1.0f, 0, 1, 0);
    func_002A8C28(object, far, 0.3f, 1, intensity, 1.0f, 0, 1, 0);
    for (i = 0; i < 3; i++) {
        func_002ACB48(base, 0.1f);
        start = func_002A7878(0.2f, 0.4f) * 2.1e+05f;
        end = func_002A7878(1.0f, 1.5f) * 2.1e+05f;
        gravity = func_002A78D8(0.0f, 0.01f);
        func_002C65A0(base, velocity, start, end, gravity, 6, 0x808080, 30, 127, 32, 0);
    }
    *(JointEffectQuad *)drift = 0;
    drift[2] = 0.1f;
    drift[3] = 1.0f;
    func_00282CC0(drift, drift, position);
    for (j = 0; j < 1; j++) {
        particle = func_PAL_002C23B8(near, drift, 12, 60, 0x606060, 3,
                                 1.05e+05f, 2.1e+04f, 1.0f, -0.0002f, 0.0f);
        if (particle) {
            particle[2] = *D_001F2540[23];
            particle[3] = 0x44;
            if (func_002A7820(0, 1)) {
                unsigned char *payload;
                unsigned short alpha;
                particle[3] = 0x48;
                alpha = 127;
                *(unsigned int *)(particle + 4) = 0x70707F;
                payload = particle + 0x20;
                payload[0x11] = 0x70;
                payload[0x12] = 0x70;
                payload[0x13] = 0x70;
                *(unsigned short *)(payload + 0x1E) = alpha;
            }
        }
    }
}



extern void func_0029F338(void *);
extern int func_PAL_00273A10(char *);
extern void func_002A7750(unsigned char *, unsigned char, int);

void func_PAL_003242C8(char *object)
{
    char *data = *(char **)(object + 0x68);
    *(float *)(data + 4) -= 0.012f;
    switch (*(unsigned char *)(object + 0x20)) {
    case 0:
        if (func_PAL_00273A10(object)) {
            func_002A7750((unsigned char *)object, 1, -1);
            *(unsigned short *)(object + 0x34) |= 0x2800;
        }
        break;
    case 1:
        func_PAL_00273A10(object);
        if (*(unsigned char *)(object + 0x23) < 2)
            func_0029F338(object);
        else
            *(unsigned char *)(object + 0x23) -= 2;
        break;
    }
}


INCLUDE_ASM("asm/pal/game", func_PAL_00324378);

INCLUDE_ASM("asm/pal/game", func_PAL_00326010);

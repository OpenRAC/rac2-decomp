#include "include_asm.h"

#include "common.h"
extern void func_00282CC0(void *, void *, void *);
extern float func_00282C48(float);
extern float func_002A7878(float, float);
extern float D_L06_001B234C __attribute__((sda));
extern float D_001B2350 __attribute__((sda));
extern int func_002E5CF8(int, int, char *);
extern void func_0029F338(char *);
extern void func_00283098(void *, void *, void *);
extern double func_001234F0(float);
extern void func_0026FEB8(char *, ...);
extern char D_L06_001B18E0[];
extern void func_PAL_L00_00328480(char *, void *, int, float, int, void *, float, unsigned int, float, float, int);

void func_PAL_L06_0045D258(char *a0) {
    float pos[4], vel[4];
    int count = 13, i;
    if (D_L06_001B234C < 0.9f && D_001B2350 < 0.9f) count = 40;
    for (i = 0; i < count; i++) {
        pos[0] = func_002A7878(-8.045f, 8.045f);
        pos[1] = func_00282C48(pos[0] * 0.1243008077f) * 1.745f;
        pos[2] = func_002A7878(0.0f, 3.99f);
        vel[0] = pos[0] * 0.0049720327f;
        vel[1] = -0.16000001f;
        vel[2] = func_002A7878(3.0f, 7.0f) * 0.020000001f;
        func_00283098(pos, pos, a0 + 0xC0);
        func_00282CC0(pos, pos, a0 + 0x10);
        func_00283098(vel, vel, a0 + 0xC0);
        func_0026FEB8(D_L06_001B18E0, func_001234F0(pos[0]), func_001234F0(pos[1]), func_001234F0(pos[2]), func_001234F0(vel[0]), func_001234F0(vel[1]), func_001234F0(vel[2]));
        func_PAL_L00_00328480(a0, pos, 1, 0.0f, 1, vel, 3.0f, 0x50808040, 1.0f, 5.5f, 0);
        func_002E5CF8(0, 0, a0);
    }
    func_0029F338(a0);
}

extern void func_L06_00457C00(char *, int, void *, int, float, float, float, float);
extern float func_002A7940(void);
extern float func_00283180(float);
extern float func_00283198(float);
extern char *func_PAL_002735D0(char *, int, int, int, char *, char *,
                           float *, int, float, float);

void func_PAL_L06_0045CD20(char *object, int mask, void *offset, int color,
                      float speed_min, float speed_max,
                      float vertical_min, float vertical_max)
{
    float velocity[3];
    float angle, speed, life, size;
    char *particle;
    unsigned char shade = color;
    int i;

    for (i = 0; i < 15; i++) {
        if (((mask >> i) ^ 1) & 1)
            continue;
        angle = func_002A7940();
        speed = func_002A7878(speed_min, speed_max) * (0.020000001f);
        velocity[0] = func_00283180(angle) * speed;
        velocity[1] = func_00283198(angle) * speed;
        velocity[2] = 0.0f;
        velocity[2] = func_002A7878(vertical_min, vertical_max) * (0.020000001f);
        func_00282CC0(velocity, velocity, offset);
        life = func_002A7878(90.0f, 270.0f);
        size = func_002A7878(10.0f, 20.0f);
        particle = func_PAL_002735D0(object, 2, *(short *)(object + 0xAA), i,
                                object + 0x10, object + 0xF0, velocity, shade,
                                life, size);
        if (particle)
            *(unsigned short *)(particle + 0x34) |= 0x10;
    }
}

#include "common.h"
extern float D_001B5340[]; extern char D_00189ED0[];
extern int D_001A8CA0;
extern float D_001AFE0C __attribute__((sda));
extern float D_001AFE10 __attribute__((sda));
extern float D_001AFE14 __attribute__((sda));
extern float D_001AFE18 __attribute__((sda));
extern float D_001AFE1C __attribute__((sda));
extern float D_001AFE20 __attribute__((sda));
extern float D_001AFE24 __attribute__((sda));
extern void func_00282CF0(void *,void *,void *);
extern void func_00282CC0(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern void func_00282D30(void *,void *,float);
extern float func_00282DB0(void *,void *);
extern float func_002A7878(float,float),func_002A78D8(float,float);
extern int func_002A77E0(int);
extern int func_001163B0(void);
extern void func_002ACEC0(void *, void *, void *, float);
extern unsigned char *func_002C2210(void *, int, float, float, unsigned int, int, int, void *, int, float);
extern int func_00283CF0(float);
/* Emit paired particles, either outward or toward the camera. */
void func_0031F6E8(char *pos, int count, int mode) {
    float velocity[4] __attribute__((aligned(16)));
    float point[4] __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    float axis[4] __attribute__((aligned(16)));
    float extra[4] __attribute__((aligned(16)));
    int i, sign;
    float size, angle, speed;
    u8 *particle;

    func_00282CF0(direction, D_001B5340, (float *)pos);
    if (D_001A8CA0 == 0) {
        direction[2] = 0.0f;
        axis[0] = 0.0f; axis[1] = 0.0f; axis[2] = 1.0f; axis[3] = 1.0f;
    } else {
        func_00282CF0(extra, pos, D_00189ED0);
        func_00282F20(axis, extra, 1.0f);
        func_00282D30(extra, axis, func_00282DB0(axis, direction));
        func_00282CF0(direction, direction, extra);
    }
    for (i = 0; i < count; i++) {
        size = func_002A7878(D_001AFE20, D_001AFE24);
        sign = func_002A77E0(2);
        if (sign == 0)
            sign--;
        angle = func_002A7878(-1.0471977f, 1.0471977f);
        func_002ACEC0(velocity, direction, axis, angle);
        speed = func_002A7878(D_001AFE0C, D_001AFE10) * (1.0f / 60.0f);
        func_00282F20((char *)velocity, (char *)velocity, speed);
        velocity[2] = func_002A7878(D_001AFE14, D_001AFE18) * (1.0f / 60.0f);
        qcopy(point, pos);
        point[0] += func_002A78D8(0.0f, 0.15f);
        point[1] += func_002A78D8(0.0f, 0.15f);
        point[2] += func_002A78D8(0.0f, 0.15f);
        if (mode == 0) {
            if (!(func_001163B0() & 1)) {
                func_00282D30(velocity, velocity, 1.5f);
                particle = func_002C2210(point, 60, size * 0.35f, size, 0x7F800000, 0, sign, velocity, 1, D_001AFE1C);
                if (particle)
                    particle[9] = func_00283CF0(4.0f) + 0x70;
                particle = func_002C2210(point, 60, size * 0.245f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 1, D_001AFE1C);
            } else {
                func_00282CF0(extra, D_001B5340, point);
                func_00282F20((char *)extra, (char *)extra, speed);
                func_00282CC0((char *)velocity, (char *)velocity, (char *)extra);
                particle = func_002C2210(point, 40, size * 2.05f, size, 0x7F800000, 0, sign, velocity, 1, D_001AFE1C);
                if (particle)
                    particle[9] = func_00283CF0(4.0f) + 0x70;
                particle = func_002C2210(point, 40, size * 1.43500006f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 1, D_001AFE1C);
            }
        } else {
            if (!(func_001163B0() & 1)) {
                func_00282D30(velocity, velocity, 1.5f);
                particle = func_002C2210(point, 60, size * 0.3f, size, 0x7F800000, 0, sign, velocity, 1, D_001AFE1C);
                if (particle)
                    particle[9] = func_00283CF0(4.0f) + 0x70;
                particle = func_002C2210(point, 60, size * 0.21000000834465027f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 1, D_001AFE1C);
            } else {
                func_00282CF0(extra, D_001B5340, point);
                func_00282F20((char *)extra, (char *)extra, speed);
                func_00282CC0((char *)velocity, (char *)velocity, (char *)extra);
                particle = func_002C2210(point, 40, size * 0.25f, size, 0x7F800000, 0, sign, velocity, 1, D_001AFE1C);
                if (particle)
                    particle[9] = func_00283CF0(4.0f) + 0x70;
                particle = func_002C2210(point, 40, size * 0.175f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 1, D_001AFE1C);
            }
        }
        if (particle)
            particle[9] = func_00283CF0(4.0f) + 0x70;
    }
}

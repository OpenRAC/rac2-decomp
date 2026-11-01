#include "include_asm.h"

#include "common.h"
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282D30(void *, void *, float);
extern float func_00282DB0(void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern char D_L15_001B97C0[];
extern int func_00283CF0(float);
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern s32 D_L15_001AEE20[] __attribute__((sda));
extern s32 D_L15_001B1780[] SDATA(D_L15_001B1780);
extern s32 D_L15_001B17B0[] SDATA(D_L15_001B17B0);
extern u8 D_L15_00188660[];
extern s32 func_002E5CF8(s32 a, s32 b, void *c);
extern s32 func_002A77E0(s32 a);
extern f32 func_002A7878(f32 a, f32 b);
extern s32 func_00283CF0(f32 a);
extern float func_002A78D8(float, float);
extern float func_002A7878(float, float);
extern int func_00283CF0(float);
extern int func_002E5CF8(int, int, void *);
extern int D_L15_001A8FF0[] __attribute__((sda));
extern char D_00189ED0[];
extern int func_002A77E0(int);
extern int func_001163B0(void);
extern void func_002ACEC0(void *, void *, void *, float);
extern unsigned char *func_002C2210(void *, int, float, float, unsigned int, int, int, void *, int, float);

void func_PAL_L15_0043E840(char *pos, int count, int mode) {
    float velocity[4] __attribute__((aligned(16)));
    float point[4] __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    float axis[4] __attribute__((aligned(16)));
    float extra[4] __attribute__((aligned(16)));
    int i, sign;
    float size, angle, speed;
    u8 *particle;

    func_00282CF0(direction, D_L15_001B97C0, (float *)pos);
    if (D_L15_001A8FF0[0] == 0) {
        direction[2] = 0.0f;
        axis[0] = 0.0f; axis[1] = 0.0f; axis[2] = 1.0f; axis[3] = 1.0f;
    } else {
        func_00282CF0(extra, pos, D_00189ED0);
        func_00282F20(axis, extra, 1.0f);
        func_00282D30(extra, axis, func_00282DB0(axis, direction));
        func_00282CF0(direction, direction, extra);
    }
    for (i = 0; i < count; i++) {
        size = func_002A7878(0.75f, 2.0f);
        sign = func_002A77E0(2);
        if (sign == 0)
            sign--;
        angle = func_002A7878(-1.0471977f, 1.0471977f);
        func_002ACEC0(velocity, direction, axis, angle);
        speed = func_002A7878(0.05f, 3.0f) * (0.020000001f);
        func_00282F20((char *)velocity, (char *)velocity, speed);
        velocity[2] = func_002A7878(1.0f, 5.0f) * (0.020000001f);
        qcopy(point, pos);
        point[0] += func_002A78D8(0.0f, 0.15f);
        point[1] += func_002A78D8(0.0f, 0.15f);
        point[2] += func_002A78D8(0.0f, 0.15f);
        if (mode == 0) {
            if (!(func_001163B0() & 1)) {
                func_00282D30(velocity, velocity, 1.5f);
                particle = func_002C2210(point, 50, size * 0.35f, size, 0x7F800000, 0, sign, velocity, 0, 0.0028800003f);
                if (particle)
                    particle[9] = func_00283CF0(4.0f) + 0x70;
                particle = func_002C2210(point, 50, size * 0.245f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, 0.0028800003f);
            } else {
                func_00282CF0(extra, D_L15_001B97C0, point);
                func_00282F20((char *)extra, (char *)extra, speed);
                func_00282CC0((char *)velocity, (char *)velocity, (char *)extra);
                particle = func_002C2210(point, 33, size * 2.05f, size, 0x7F800000, 0, sign, velocity, 0, 0.0028800003f);
                if (particle)
                    particle[9] = func_00283CF0(4.0f) + 0x70;
                particle = func_002C2210(point, 33, size * 1.43500006f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, 0.0028800003f);
            }
        } else {
            if (!(func_001163B0() & 1)) {
                func_00282D30(velocity, velocity, 1.5f);
                particle = func_002C2210(point, 50, size * 0.3f, size, 0x7F800000, 0, sign, velocity, 0, 0.0028800003f);
                if (particle)
                    particle[9] = func_00283CF0(4.0f) + 0x70;
                particle = func_002C2210(point, 50, size * 0.21000000834465027f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, 0.0028800003f);
            } else {
                func_00282CF0(extra, D_L15_001B97C0, point);
                func_00282F20((char *)extra, (char *)extra, speed);
                func_00282CC0((char *)velocity, (char *)velocity, (char *)extra);
                particle = func_002C2210(point, 33, size * 0.25f, size, 0x7F800000, 0, sign, velocity, 0, 0.0028800003f);
                if (particle)
                    particle[9] = func_00283CF0(4.0f) + 0x70;
                particle = func_002C2210(point, 33, size * 0.175f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, 0.0028800003f);
            }
        }
        if (particle)
            particle[9] = func_00283CF0(4.0f) + 0x70;
    }
}

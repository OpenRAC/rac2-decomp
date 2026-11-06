/* func_PAL_L16_0040B0C8, the PAL copy of func_L16_00406550: the same C, where the emitter count
 * D_L16_001B1510 and every func_002A7820 lifetime take the 50 Hz scale, the per-frame floats grow
 * by 6/5 (0.0040555 by 36/25), 16 becomes 13, and the two fire loops count up.
 */
#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef float Vec4[4] __attribute__((aligned(16)));
#define F(p, o) (*(float *)((u8 *)(p) + (o)))
#define I(p, o) (*(int *)((u8 *)(p) + (o)))

typedef struct { u8 pad[0x140]; float target[4]; } CameraView;
typedef struct { u8 pad[0xD4]; u8 *sparkColors; u8 pad2[0x98]; u8 *fireColors; } EffectTables;

extern float D_L16_001B1508 __attribute__((sda));
extern float D_L16_001B150C __attribute__((sda));
extern int D_L16_001B1510 __attribute__((sda));
extern float D_L16_001A8F20[4] MACRO_ADDR;
extern CameraView D_L16_001B99C0;
extern EffectTables D_L16_001FF680;

extern u8 *func_002C65A0(void *, void *, int, int, int, int, int, float, float, float, int);
extern float func_00283248(float, float);
extern float func_002A78D8(float, float);
extern int func_00283CF0(float);
extern int func_002A7820(int, int);
extern float func_002A7878(float, float);
extern float func_00283B98(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CC0(void *, void *, void *);
extern u8 *func_002C7970(void *, void *, int, int, int, int, int, float, float, float, int);
extern void func_00282D30(void *, void *, float);
extern void func_002AB668(void *, void *, float);
extern void func_002ACDE8(void *, void *, void *);
extern u8 *func_PAL_002C7B18(void *, void *, int, float);
extern void func_PAL_003096D0(void *, void *, void *, int, int, int, int, int, float);
extern void func_PAL_002AC718(void *, void *, void *, float, float, int, int, int, float, float, float, float, int, int, int, int, int, int, float);
extern void func_002AF000(float *, float, float, float);
extern u8 *func_PAL_002BE9A8(void *, float, float, int, void *, int, int, float, float);
extern float func_00283CE0(int);

void func_PAL_L16_0040B0C8(u8 *object, void *unused)
{
    Vec4 position;
    Vec4 velocity;
    Vec4 rotation;
    u8 *state = *(u8 **)(object + 0x68);
    float inner, outer, angle, speed;
    u8 *effect;
    int na, nb, nc, ne, ng, nh, nk, sign;

    inner = D_L16_001B1508 * F(state, 0x14) * 210000.0f;
    outer = D_L16_001B150C * F(state, 0x14) * 210000.0f;
    effect = func_002C65A0(object + 0x10, D_L16_001A8F20, ((s32)(D_L16_001B1510) * 5 + 2) / 6, 0x388EF7, 0, 100, 0, inner, outer, 0.0f, 0);
    if (effect)
        effect[2] = D_L16_001FF680.fireColors[0];
    effect = func_002C65A0(object + 0x10, D_L16_001A8F20, ((s32)(D_L16_001B1510) * 5 + 2) / 6, 0x14F700, 0, 100, 0, inner, outer, 0.0f, 0);
    if (effect)
        effect[2] = D_L16_001FF680.fireColors[0];
    for (na = 0; na < 2; na++) {
        effect = func_002C65A0(object + 0x10, D_L16_001A8F20, ((s32)(D_L16_001B1510) * 5 + 2) / 6, 0x38F738, 0, 127, 0, inner, outer, 0.0f, 0);
        if (effect)
            effect[2] = D_L16_001FF680.fireColors[5];
    }
    for (nb = 0; nb < 2; nb++) {
        effect = func_002C65A0(object + 0x10, D_L16_001A8F20, ((s32)(D_L16_001B1510) * 5 + 2) / 6, 0x38F738, 0, 127, 0, inner, outer, 0.0f, 0);
        if (effect)
            effect[2] = D_L16_001FF680.fireColors[6];
    }
    for (nc = 0; nc < I(state, 0x20); nc++) {
        float heading, angle, size, speed;
        int lifetime, phase;
        heading = func_00283248(D_L16_001B99C0.target[0] - F(object, 0x10), D_L16_001B99C0.target[1] - F(object, 0x14));
        phase = func_00283CF0(func_002A78D8(2.0f, 5.0f));
        lifetime = func_002A7820(30, 50);
        position[0] = F(object, 0x10) + func_002A78D8(0.0f, 0.1f) * F(state, 0x14);
        position[1] = F(object, 0x14) + func_002A78D8(0.0f, 0.1f) * F(state, 0x14);
        position[2] = F(object, 0x18) + func_002A78D8(0.0f, 0.1f) * F(state, 0x14);
        size = func_002A7878(0.6f, 1.0f) * F(state, 0x14);
        speed = func_002A7878(9.0f, 12.0f) * F(state, 0x14);
        angle = func_00283B98(heading, func_002A78D8(0.0f, 1.3962636f));
        velocity[0] = func_00283180(angle) * 0.020000001f * speed;
        velocity[1] = func_00283198(angle) * 0.020000001f * speed;
        velocity[2] = 0.0f;
        speed = func_002A7878(0.0f, 12.0f) * F(state, 0x14);
        velocity[2] = speed * 0.020000001f;
        func_002C7970(position, velocity, ((s32)(lifetime) * 5 + 2) / 6, 0xFF7F40, phase, 127, 127, size * 210000.0f, F(state, 0x14) * 2100.0f, 0.00584f, 1);
        {
            u8 *effect = func_002C7970(position, velocity, ((s32)(lifetime) * 5 + 2) / 6, 0x20FF00, -(phase * 2), 48, 48, size * 1260000.0f, F(state, 0x14) * 4200.0f, 0.00584f, 0);
            if (effect)
                effect[2] = D_L16_001FF680.sparkColors[0];
        }
    }
    for (ne = 0; ne < I(state, 0x24); ne++) {
        float heading, angle, size, speed;
        int lifetime, phase;
        heading = func_00283248(D_L16_001B99C0.target[0] - F(object, 0x10), D_L16_001B99C0.target[1] - F(object, 0x14));
        phase = func_00283CF0(func_002A78D8(2.0f, 5.0f));
        lifetime = func_002A7820(30, 50);
        position[0] = F(object, 0x10) + func_002A78D8(0.0f, 0.1f) * F(state, 0x14);
        position[1] = F(object, 0x14) + func_002A78D8(0.0f, 0.1f) * F(state, 0x14);
        position[2] = F(object, 0x18) + func_002A78D8(0.0f, 0.1f) * F(state, 0x14);
        size = func_002A7878(0.75f, 1.5f) * F(state, 0x14);
        speed = func_002A7878(9.0f, 12.0f) * F(state, 0x14);
        angle = func_00283B98(heading, func_002A78D8(0.0f, 1.3962636f));
        velocity[0] = func_00283180(angle) * 0.020000001f * speed;
        velocity[1] = func_00283198(angle) * 0.020000001f * speed;
        velocity[2] = 0.0f;
        speed = func_002A7878(0.0f, 12.0f) * F(state, 0x14);
        velocity[2] = speed * 0.020000001f;
        func_002C7970(position, velocity, ((s32)(lifetime) * 5 + 2) / 6, 0x20FF00, phase, 127, 127, size * 210000.0f, F(state, 0x14) * 2100.0f, 0.00584f, 5);
    }
    for (ng = 0; ng < I(state, 0x28); ng++) {
        float heading, angle, size, speed;
        int lifetime, phase;
        heading = func_00283248(D_L16_001B99C0.target[0] - F(object, 0x10), D_L16_001B99C0.target[1] - F(object, 0x14));
        phase = func_00283CF0(func_002A78D8(2.0f, 5.0f));
        lifetime = func_002A7820(30, 50);
        position[0] = F(object, 0x10) + func_002A78D8(0.0f, 0.1f) * F(state, 0x14);
        position[1] = F(object, 0x14) + func_002A78D8(0.0f, 0.1f) * F(state, 0x14);
        position[2] = F(object, 0x18) + func_002A78D8(0.0f, 0.1f) * F(state, 0x14);
        size = func_002A7878(0.6f, 1.0f) * F(state, 0x14);
        speed = func_002A7878(9.0f, 12.0f) * F(state, 0x14);
        angle = func_00283B98(heading, func_002A78D8(0.0f, 1.3962636f));
        velocity[0] = func_00283180(angle) * 0.020000001f * speed;
        velocity[1] = func_00283198(angle) * 0.020000001f * speed;
        velocity[2] = 0.0f;
        speed = func_002A7878(0.0f, 12.0f) * F(state, 0x14);
        velocity[2] = speed * 0.020000001f;
        func_002C7970(position, velocity, ((s32)(lifetime) * 5 + 2) / 6, 0x64FF30, phase, 127, 127, size * 210000.0f, F(state, 0x14) * 2100.0f, 0.00584f, 3);
    }
    for (nh = 0; nh < I(state, 0x30); nh++) {
        float roll, turn;
        speed = func_002A7878(15.0f, 20.0f) * F(state, 0x14) * 0.020000001f;
        func_00282D30(position, object + 0xC0, speed);
        roll = func_002A78D8(0.261799425f, 1.3962636f);
        turn = func_002A78D8(0.261799425f, 1.3962636f);
        func_002AB668(rotation, object + 0xD0, roll);
        func_002ACDE8(velocity, position, rotation);
        func_002AB668(rotation, object + 0xC0, turn);
        func_002ACDE8(velocity, velocity, rotation);
        func_PAL_002C7B18(object + 0x10, velocity, ((s32)(func_002A7820(20, 35)) * 5 + 2) / 6, 0.00584f);
    }
    if (I(state, 0x34)) {
        *(Quad *)velocity = 0;
        velocity[2] = F(state, 0x14) * 0.16000001f;
        *(Quad *)position = *(Quad *)velocity;
        func_PAL_003096D0(object, object + 0x10, position, 13, 0, 0, 255, 40, F(state, 0x14) * 3.5f);
    }
    func_PAL_002AC718(object, D_L16_001A8F20, object + 0x10, 0.0f, 0.0f, 0, 0, 0, 0.0f, 0.0f, 9.0f, 0.0f, -1, 0, 0, -1, 0, 0x810001, F(state, 0x14) * 20.0f);
    sign = 1;
    angle = func_00283248(D_L16_001B99C0.target[0] - F(object, 0x10), D_L16_001B99C0.target[1] - F(object, 0x14));
    for (nk = 0; nk < I(state, 0x2C); nk++) {
        float radius, roll, turn;
        position[0] = F(object, 0x10) + func_002A78D8(0.0f, 1.0f) * F(state, 0x14);
        sign = -sign;
        position[1] = F(object, 0x14) + func_002A78D8(0.0f, 1.0f) * F(state, 0x14);
        position[2] = F(object, 0x18) + func_002A78D8(0.0f, 1.0f) * F(state, 0x14);
        radius = func_002A7878(0.020000001f, 0.040000003f) * F(state, 0x14);
        roll = func_002A78D8(0.0f, 1.3962636f);
        turn = func_00283B98(angle, func_002A78D8(0.0f, 1.5707965f));
        func_002AF000(velocity, radius, turn, roll);
        {
            u8 *effect = func_PAL_002BE9A8(position, 0.0f, 1.0f, sign, velocity, 0x7F20FF60, 0, 1.01f, F(state, 0x14) * 315000.0f);
            if (effect) {
                u8 *extra = effect + 0x20;
                *(u16 *)(effect + 0xA) = ((s32)(func_002A7820(40, 70)) * 5 + 2) / 6;
                effect[9] = func_00283CF0(4.0f) + 64;
                I(extra, 0x4) = 3;
                F(extra, 0x1C) = func_00283CE0(((s32)(func_002A7820(1, 10)) * 5 + 2) / 6);
                extra[0xA] = 64;
                extra[0xB] = effect[0xA];
            }
        }
    }
}

/* func_PAL_L11_003FCA30, the PAL copy of func_L11_003F8510: the same C, where two func_00283CF0 inputs get the
   50 Hz scale, 10 becomes 8, 120 becomes 100, and the speed and 0.3f passed to func_002AEC48 are scaled by 1.44f. */
#include "common.h"
extern void func_L04_00423178(void *);
extern void func_L01_003128C0(void *);
extern int func_002ACBC8(void *, int);
extern void func_L01_003246D0(int);
extern int func_00288AA0(void *, int);
extern int func_00288BE8(void *);
extern int func_002F5D10(void);
extern void func_PAL_002F6C18(void);
extern void func_002A7750(void *, int, int);
extern void func_00288308(int);
extern int func_002AD860(int);
extern void func_PAL_002B1588(int, int);
extern void func_002A0430(int);
extern void func_002DF3F8(void *, void *);
extern int func_0029B3E0(int, int);
extern void func_0029F338(void *);
extern int func_00282978(void *);
extern int func_00282948(void *);
extern float func_002A7878(float, float);
extern int func_00283CF0(float);
extern void func_PAL_002A7E68(void *, int, int, int);
extern float func_00282E80(void *, void *);
extern float func_00283248(float, float);
extern float func_00283C80(float, float);
extern float func_00282DF0(void *);
extern float func_00283B98(float, float);
extern void func_002AF000(void *, float, float, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00283BE0(float, float);
extern float func_00282E20(void *);
extern void func_002AEC48(void *, void *, int, float, float);
extern unsigned char D_001A7B2E, D_001A7A40;
extern int D_001397D8 NOT_SDA;
extern unsigned char D_0013960F NOT_SDA;
extern int D_L11_001A8F00;
/* Both dialogue states set this gate before polling and clear it on exit. */
extern volatile int D_L11_001B32E8[] MACRO_ADDR;
extern int D_001A79F0 __attribute__((sda));
extern unsigned char D_0019B2E8[][16];
extern unsigned char D_L11_001C0AC0[];
/* Measured player prefix used by the position, aiming and motion checks. */
typedef struct {
    unsigned char pad[0x80];
    float position[4];
    float rotation[4];
    unsigned char padA0[0x40];
    float aim[4];
    unsigned char padF0[0x20];
    float velocity[4];
} JobaPlayerView;
extern JobaPlayerView D_00189E20;
extern char D_00189F00[];

void func_PAL_L11_003FCA30(unsigned char *moby) {
    float target[4] __attribute__((aligned(16)));
    float origin[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    unsigned char *data = *(unsigned char **)(moby + 0x68);
    int track;
    float speed, blend, angle, pitch, heading;

    func_L04_00423178(moby);
    switch (moby[0x20]) {
    case 0:
        if (D_001A7B2E) {
            func_0029F338(moby);
            return;
        }
        {
            func_L01_003128C0(moby);
            if (D_001397D8 & 0x10000)
                func_002A7750(moby, 3, -1);
            else
                func_002A7750(moby, 1, -1);
        }
        break;
    case 1:
        if (func_002ACBC8(D_00189E20.position, *(int *)(data + 0x120))) {
            func_L01_003246D0((int)moby);
            if (func_00288AA0(D_L11_001C0AC0, 0x70)) {
                func_00288BE8(D_L11_001C0AC0);
                func_002A7750(moby, 2, -1);
            }
        }
        break;
    case 2:
        D_L11_001B32E8[0] = 1;
        if (D_L11_001A8F00 == 2) {
            moby[0x31] = 0;
            *(u16 *)(moby + 0x34) |= 1;
        }
        if (!func_002F5D10()) {
            D_L11_001B32E8[0] = 0;
            moby[0x31] = 1;
            *(u16 *)(moby + 0x34) &= 0xFFFE;
            func_002A7750(moby, 3, -1);
        }
        break;
    case 3:
        if (D_0013960F &&
            func_002ACBC8(D_00189E20.position, *(int *)(data + 0x120))) {
            func_L01_003246D0((int)moby);
            if (func_00288AA0(D_L11_001C0AC0, 0x71)) {
                func_00288BE8(D_L11_001C0AC0);
                func_PAL_002F6C18();
                func_002A7750(moby, 4, -1);
            }
        }
        break;
    case 4:
        D_L11_001B32E8[0] = 1;
        if (D_L11_001A8F00 == 2) {
            moby[0x31] = 0;
            *(u16 *)(moby + 0x34) |= 1;
        }
        if (!func_002F5D10()) {
            D_L11_001B32E8[0] = 0;
            moby[0x31] = 1;
            *(u16 *)(moby + 0x34) &= 0xFFFE;
            if (!D_001A7B2E) {
                func_00288308(0x36);
                func_002AD860(0x36);
                func_PAL_002B1588(0x1232, -1);
                if (moby[0xB0] != 255) {
                    if (!(D_0019B2E8[D_001A79F0][moby[0xB0]] & 0x80))
                        func_002A0430(moby[0xB0]);
                    func_002DF3F8(D_00189E20.position, D_00189E20.rotation);
                } else {
                    func_0029B3E0(0, -1);
                }
            }
            func_0029F338(moby);
            return;
        }
        break;
    }

    if (moby[0x20] != 0) {
        if (moby[0x43] == 1 && func_00282978(data + 0x11E)) {
            *(u16 *)(data + 0x11E) = func_00283CF0((func_002A7878(1200.0f, 2400.0f) * 5.0f + 2.0f) * 0.16666667f);
        } else if ((moby[0x60] & 2) && moby[0x43] != 1) {
            func_PAL_002A7E68(moby, 1, 0, 8);
        }
    }

    speed = 0.02f;
    blend = 0.3f;
    track = 0;
    if (moby[0x43] == 1) {
        track = 1;
        if (func_00282E80(moby + 0x10, D_00189E20.position) < 8.0f &&
            func_00283C80(*(float *)(moby + 0xF8),
                func_00283248(D_00189E20.aim[0] - *(float *)(moby + 0x10),
                              D_00189E20.aim[1] - *(float *)(moby + 0x14))) < 1.5707964897155762f) {
            if (func_00282DF0(D_00189E20.velocity) > 0.01f)
                *(int *)(data + 0x114) = 100;
            else
                func_00282948(data + 0x114);
        } else if (*(int *)(data + 0x114)) {
            *(int *)(data + 0x114) = 0;
            qcopy(data + 0x100, D_00189F00);
        }
        if (func_00282948(data + 0x118)) {
            *(int *)(data + 0x118) = func_00283CF0((func_002A7878(180.0f, 300.0f) * 5.0f + 2.0f) * 0.16666667f);
            heading = func_00283B98(*(float *)(moby + 0xF8),
                func_002A7878(-90.0f, 90.0f) * 0.01745329424738884f);
            angle = func_002A7878(0.0f, 30.0f);
            func_002AF000(data + 0x100, 6.0f, heading, angle * 0.01745329424738884f);
            func_00282CC0(data + 0x100, data + 0x100, moby + 0x10);
        }
        if (*(int *)(data + 0x114)) {
            qcopy(target, D_00189F00);
            speed = 0.04f;
            blend = 0.3f;
        } else {
            qcopy(target, data + 0x100);
        }
    }

    if (track) {
        qcopy(origin, moby + 0x10);
        origin[2] += 2.0f;
        func_00282CF0(delta, target, origin);
        angle = func_00283BE0(func_00283248(delta[0], delta[1]), *(float *)(moby + 0xF8));
        pitch = -func_00283248(func_00282E20(delta), delta[2]);
        if (angle > 1.5707964897155762f)
            angle = 1.5707964897155762f;
        else if (angle < -1.5707964897155762f)
            angle = -1.5707964897155762f;
        if (pitch > 0.523598849773407f)
            pitch = 0.523598849773407f;
        else if (pitch < -0.523598849773407f)
            pitch = -0.523598849773407f;
        *(float *)(data + 0x64) = pitch;
        *(float *)(data + 0x68) = angle * 0.6f;
        *(float *)(data + 0xE8) = angle * 0.4f;
    }
    if (D_001A7A40)
        *(float *)(data + 0x70) = 2.75f;
    {
        float scale = 1.44f;
        float step = speed * scale;
        float rate = blend * scale;
        func_002AEC48(moby, data, 0, step, rate);
        func_002AEC48(moby, data + 0x80, 1, step, rate);
    }
}

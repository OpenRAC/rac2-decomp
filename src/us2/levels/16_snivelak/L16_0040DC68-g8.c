#include "include_asm.h"

#include "common.h"
extern void func_L16_0040CD88(u8 *), func_L16_0040CF98(u8 *), func_L16_0040D258(u8 *);
extern int func_002A77E0(int), func_002A7820(int, int), func_00282978(short *);
extern void func_002A7750(void *, u8, int), func_002A7470(void *, int, int, int);
typedef struct {
    u8 reserved_00[0x18];
    u8 enabled, count, kind;
    u8 reserved_1b[0x65];
    u8 payload[1];
} DispatchContext;
typedef unsigned long DispatchFlags;
extern DispatchFlags func_002B1C20(
    void *, DispatchContext *);
extern void func_002A7A00(void *, float, float), func_00282CC0(void *, void *, void *);
extern float func_00282C48(float), func_002A7878(float, float), func_002A78D8(float, float);
extern u8 *func_00273730(void *, int, int, int, void *, void *, void *, int, float, float);
extern u8 *func_0029EFD0(int);
extern void func_002B37E8(void *, void *), func_002AB650(void *), func_00310C88(void *);
extern float func_002A89A8(void *, int, float);
extern void func_L13_00412748(void *, int, int, int, int, int, int, int, float, int, int);
extern void func_US2_002A7AA8(void *, int, int), func_0029F338(void *);
extern int func_US2_002AF9C8(void *, float);
extern void func_0029FCC0(char *, int, char *), func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_L16_00413D10(void *, void *, void *, int, float);
extern int func_L09_00329028(char *, int);
extern float D_L16_001A8F20[] __attribute__((sda));
extern struct {
    u8 pad000[0x160];
    float strength;
    u8 pad164[4];
    int duration, timer;
    u8 pad170[0x10];
    float damping;
    u8 pad184[4];
    int lifetime;
} D_L16_001B99C0;

/* Updates the object's activation states, death debris and timed aiming sequence. */
void func_US2_L16_0040DC68(u8 *moby)
{
    u8 *state = *(u8 **)(moby + 0x68);
    float velocity[4] __attribute__((aligned(16)));
    float aim[4] __attribute__((aligned(16)));
    DispatchFlags flags;
    u8 *child;
    int i;
    func_L16_0040CD88(moby);
    switch (moby[0x95]) {
    case 0:
        *(short *)(state + 0x23e) = func_002A77E0(30);
        if (*(int *)(state + 0x240) == 1 && func_00282978((short *)(state + 0x23e))) {
            if (moby[0x43] != 1) func_002A7470(moby, 1, 0, 10);
            func_002A7750(moby, 3, 2);
            break;
        }
        if (*(int *)(state + 0x244)) {
            func_002A7750(moby, 2, 1);
            *(int *)(state + 0x244) = 0;
            if (*(int *)(state + 0x238) < 300)
                *(int *)(state + 0x238) = func_002A7820(480, 600);
        }
        break;
    case 1:
        if (*(int *)(state + 0x354) != 1 && *(int *)(state + 0x240) != 1)
            break;
        func_002A7750(moby, 3, 2);
        break;
    case 2:
        if (*(int *)(state + 0x240) == 1) break;
        if (*(int *)(state + 0x354) == 1) break;
        func_002A7750(moby, 2, 1);
        *(int *)(state + 0x238) = func_002A7820(580, 600);
        break;
    case 3:
        flags = func_002B1C20(moby, (DispatchContext *)(state + 0x140));
        if ((flags & 1UL) == 1UL) {
            for (i = 0; i < 4; i++) {
                func_002A7A00(velocity, 0.13333334f, 0.20000002f);
                velocity[2] = func_00282C48(velocity[2]);
                velocity[2] *= 1.5f;
                func_00282CC0(velocity, velocity, D_L16_001A8F20);
                child = func_00273730(moby, 1, *(short *)(moby + 0xaa), i,
                    moby + 0x10, moby + 0xf0, velocity, 255, 30.0f, 15.0f);
                *(void (**)(void *))(child + 0x64) = func_00310C88;
            }
            child = func_0029EFD0(0x10ce);
            func_002B37E8(child, moby);
            *(float *)(child + 0x18) = func_002A89A8(moby + 0x10, 0, 0.5f);
            func_002AB650(child);
            func_L13_00412748(moby + 0x10, 0, 45, 40, 40, 40, 45, 1, 1.0f, 1, 1);
            D_L16_001B99C0.lifetime = 90;
            D_L16_001B99C0.strength = 0.2f;
            D_L16_001B99C0.duration = 60;
            D_L16_001B99C0.damping = 0.1f;
            D_L16_001B99C0.timer = 0;
            velocity[0] = func_002A78D8(0.5f, 4.0f) * 0.016666668f;
            velocity[1] = func_002A78D8(0.0f, 4.0f) * 0.016666668f;
            velocity[2] = func_002A7878(7.0f, 9.0f) * 0.016666668f;
            velocity[2] = func_00282C48(velocity[2]);
            velocity[2] *= 3.0f;
            func_00282CC0(velocity, velocity, D_L16_001A8F20);
            child = func_00273730(moby, 3, 0xecb, 0, moby + 0x10,
                moby + 0xf0, velocity, 255, 180.0f, 25.0f);
            func_002AB650(child);
            func_US2_002A7AA8(moby, 0, 3);
            func_0029F338(moby);
            return;
        }
        if ((flags & 2UL) == 2UL) {
            if (*(int *)(state + 0x240) == 1 || *(int *)(state + 0x354) == 1) {
                if (moby[0x43] != 1) func_002A7470(moby, 1, 0, 10);
                func_002A7750(moby, 3, 2);
            } else {
                func_002A7750(moby, 2, 1);
                *(int *)(state + 0x238) = func_002A7820(580, 600);
            }
        }
        break;
    }
    switch (moby[0x20]) {
    case 0:
    case 1:
    case 2:
        break;
    case 3:
        if (func_US2_002AF9C8(moby, 1.0f)) {
            func_0029FCC0((char *)moby, 2, (char *)velocity);
            func_00282CF0(aim, state + 0x1f0, velocity);
            func_00282F20(aim, aim, 0.416666687f);
            func_L16_00413D10(moby, aim, velocity, 0, 2.0f);
        }
        if (*(int *)(state + 0x24c) != -1)
            func_L09_00329028((char *)moby, *(int *)(state + 0x24c));
        if (*(unsigned short *)(moby + 0x96) > 180) {
            if (moby[0x43]) func_002A7470(moby, 0, 0, 10);
            func_002A7750(moby, 4, -1);
        }
        break;
    case 4:
        if (*(int *)(state + 0x24c) != -1)
            func_L09_00329028((char *)moby, *(int *)(state + 0x24c));
        if (*(unsigned short *)(moby + 0x96) > 180) {
            if (moby[0x43] != 1) func_002A7470(moby, 1, 0, 10);
            func_002A7750(moby, 3, -1);
        }
        break;
    }
    func_L16_0040CF98(moby);
    func_L16_0040D258(moby);
}

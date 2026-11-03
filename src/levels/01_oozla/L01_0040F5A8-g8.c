#include "common.h"

typedef union { int q __attribute__((mode(TI))); float f[4]; } DebrisVector;

extern s32 D_L01_001AEC38 SDATA(D_L01_001AEC38);
extern s32 D_L01_001AEC38_1 __asm__("D_L01_001AEC38");
extern s32 D_L01_001B3468 SDATA(D_L01_001B3468);
extern s32 D_L01_001B3468_1 __asm__("D_L01_001B3468");
extern float D_L01_001B2090 __attribute__((sda));
extern float D_L01_001B208C __attribute__((sda));
extern s32 D_L01_001B15E0 NOT_SDA;
extern float D_L01_001B1600[] SDATA(D_L01_001B1600);
extern float D_L01_001B15F8[] SDATA(D_L01_001B15F8);
extern float D_L01_001B15F0[] SDATA(D_L01_001B15F0);
extern float D_L01_001B1620 __attribute__((sda));
extern float D_L01_001B1624 NOT_SDA;
extern float D_L01_001B1628 NOT_SDA;
extern char D_L01_001A8F60[] NOT_SDA;

extern s32 func_00282948(char *);
extern void func_0029F338(char *);
extern void func_002A7750(char *, s32, s32);
extern s32 func_002A9640(char *, s32, s32);
extern float func_002A7878(float, float);
extern void *func_00273730(char *, s32, s32, s32, char *, char *, void *, s32, float, float);
extern void func_00283098(void *, void *, void *);
extern void func_002B0A68(char *, s32, char *, s32, float, float, float, float);
extern s32 func_002B3868(char *);
extern void func_002E5CF8(s32, s32, char *);
extern void func_L00_00324F18(char *, void *, float, float, float);
extern void func_L00_00326110(char *, s32, float);
extern void func_L00_0032A258(char *, void *, void *, void *, s32, s32, s32, s32, s32, u8, void *);
extern void func_L01_002E1680(float, float, float, void *, void *, s32, u32, s32);

typedef struct { char pad0[0x31]; u8 active; u16 pad32; u16 flags; char pad36[0x62]; int target; } RetiringObject;
void func_L01_0040F5A8(char *obj)
{
    DebrisVector velocity, jitter, position;
    char *rec = *(char **)(obj + 0x68);

    switch (*(u8 *)(obj + 0x20)) {
    case 0:
        D_L01_001AEC38 = D_L01_001AEC38_1 + 1;
        func_002A7750(obj, 1, -1);
        break;
    case 1:
        if (func_002A9640(obj, 0x04010000, 0) != 0 && *(s32 *)rec == 0) {
            D_L01_001AEC38 = D_L01_001AEC38_1 - 1;
            func_002A7750(obj, 2, -1);
        }
        *(u8 *)(obj + 0xA8) = 0xFF;
        break;
    case 2:
        if (*(u8 *)(obj + 0x31) != 0 && D_L01_001B2090 < 0.9f && D_L01_001B208C < 0.9f
            && D_L01_001B3468 < D_L01_001B15E0) {
            func_L00_0032A258(obj, D_L01_001B1600, D_L01_001B15F8, D_L01_001B15F0,
                65535, 0, 0, 6, 65535, 255, 0);
            jitter.q = 0;
            jitter.f[0] = func_002A7878(-1.0f, 1.0f) * 0.016666668f;
            jitter.f[1] = func_002A7878(-1.0f, 1.0f) * 0.016666668f;
            jitter.f[2] = 0.083333336f;
            velocity.q = jitter.q;
            func_00273730(obj, 2, *(s16 *)(obj + 0xaa), 0, obj + 0x10, obj + 0xf0,
                &velocity, 255, func_002A7878(180.0f, 360.0f), 15.0f);
            jitter.q = 0;
            jitter.f[1] = -0.015000000596046448f;
            func_L00_00324F18(obj, &position, D_L01_001B1620, D_L01_001B1624, D_L01_001B1628);
            func_00283098(&jitter, &jitter, obj + 0xc0);
            func_L01_002E1680(0.0066666672937572f, 1.0f, 1.0299999713897705f, &position, &jitter, 10, 0x80808080, 0);
            func_002A7750(obj, 3, -1);
        } else {
            func_002B0A68(obj, 17, D_L01_001A8F60, 255, 1.0f, 3.0f, 2.0f, 5.0f);
            func_L00_00326110(obj, 1, 0.0f);
            func_002E5CF8(0, 0, obj);
        }
        func_002A7750(obj, 3, -1);
        break;
    case 3:
        if (func_002B3868(obj) != 0) {
            RetiringObject *retiring = (RetiringObject *)obj;
            unsigned int flags = retiring->flags;
            int count;
            retiring->active = 0;
            retiring->target = 0;
            count = D_L01_001B3468_1;
            retiring->flags = flags | 1;
            *(int *)(rec + 8) = 0x78;
            D_L01_001B3468_1 = count + 1;
        }
        if (func_00282948(rec + 8) != 0) {
            D_L01_001B3468 = D_L01_001B3468 - 1;
            func_0029F338(obj);
        }
        break;
    }
}

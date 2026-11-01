#include "include_asm.h"

#include "common.h"
extern s32 D_L01_001AEC38 SDATA(D_L01_001AEC38);
extern s32 D_L01_001AEC38_1 __asm__("D_L01_001AEC38");
extern s32 D_L01_001B3468 SDATA(D_L01_001B3468);
extern s32 D_L01_001B3468_1 __asm__("D_L01_001B3468");
extern float D_L01_001B2090 __attribute__((sda));
extern float D_L01_001B208C __attribute__((sda));
extern s32 D_L01_001B15E0 __attribute__((sda));
extern char D_L01_001A8F60[] NOT_SDA;
extern s32 func_00282948(char *);
extern void func_0029F338(char *);
extern void func_002A7750(char *, s32, s32);
extern s32 func_002A9640(char *, s32, s32);
extern void func_PAL_002B15D8(char *, s32, char *, float, float, float, float, s32);
extern s32 func_002B3868(char *);
extern void func_002E5CF8(s32, s32, char *);
extern void func_PAL_L00_003281C0(char *, s32, float);
typedef struct { char pad0[0x31]; u8 active; u16 pad32; u16 flags; char pad36[0x62]; int target; } RetiringObject;

void func_PAL_L01_00414398(char *obj)
{
    char *rec = *(char **)(obj + 0x68);

    switch (*(u8 *)(obj + 0x20)) {
    case 0:
        D_L01_001B3468_1 = 0;
        D_L01_001AEC38 = D_L01_001AEC38 + 1;
        func_002A7750(obj, 1, -1);
        return;
    case 1:
        if (func_002A9640(obj, 0x04010000, 0) != 0 && *(s32 *)rec == 0) {
            D_L01_001AEC38 = D_L01_001AEC38_1 - 1;
            func_002A7750(obj, 2, -1);
        }
        *(u8 *)(obj + 0xA8) = 0xFF;
        return;
    case 2:
        if (*(u8 *)(obj + 0x31) != 0 && D_L01_001B2090 < 0.9f && D_L01_001B208C < 0.9f && D_L01_001B3468 < D_L01_001B15E0)
            func_PAL_002B15D8(obj, 0x7F, D_L01_001A8F60, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);
        else
            func_PAL_002B15D8(obj, 0xD, D_L01_001A8F60, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);
        func_PAL_L00_003281C0(obj, 4, 0.0f);
        func_002E5CF8(0, 0, obj);
        func_002A7750(obj, 3, -1);
        return;
    case 3:
        if (func_002B3868(obj) != 0) {
            RetiringObject *retiring = (RetiringObject *)obj;
            unsigned int flags = retiring->flags;
            int count;
            retiring->active = 0;
            retiring->target = 0;
            count = D_L01_001B3468_1;
            retiring->flags = flags | 1;
            *(int *)(rec + 4) = 0x64;
            D_L01_001B3468_1 = count + 1;
        }
        if (func_00282948(rec + 4) != 0) {
            D_L01_001B3468 = D_L01_001B3468 - 1;
            func_0029F338(obj);
        }
        return;
    }
}

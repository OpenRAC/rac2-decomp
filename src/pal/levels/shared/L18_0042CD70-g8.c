/* func_PAL_L18_0042CD70, the PAL copy of func_L18_00428138: the same C, with 50 Hz rate constants and the 5/6 scale on D_L18_001B1240. */
#include "common.h"
extern int D_L18_001AFBB0;
typedef struct { u8 pad[0x1E0]; s16 guard; u8 pad2[0x20B2]; int mode; } Player;
extern Player D_L18_00189E20;
extern float D_L18_001B1284 __attribute__((sda));
extern float D_L18_001B1280 __attribute__((sda));
extern float D_L18_001B126C __attribute__((sda));
extern int D_L18_001B1240 __attribute__((sda));
extern u8 D_L18_001B1308[];
extern float func_00308AD0(void *, void *);
extern void func_003476C8(void *, float, float, float, float);
extern void func_PAL_L18_0042BA90(void *, int, int, float);
extern void func_00335668(void *, int, int);
extern void func_002C27F0(void *, int);
int func_PAL_L18_0042CD70(u8 *obj) {
    u8 *state = *(u8 **)(obj + 0x68);
    float range;
    if (D_L18_001AFBB0 || D_L18_00189E20.guard || D_L18_00189E20.mode == 0x6F) return 0;
    range = D_L18_001B1284;
    switch (*(s16 *)(obj + 0xAA)) {
    case 0xEC0:
        if (func_00308AD0(obj + 0x10, state + 0x220) < D_L18_001B126C && !*(s16 *)(state + 0x396) && !D_L18_001AFBB0 && D_L18_00189E20.mode != 0x6F) {
            func_003476C8(obj, *(float *)(state + 0x3CC) * 0.00040000002f, *(float *)(state + 0x3C8) * 0.020000001f, *(float *)(state + 0x3DC) * 6.981318e-06f, *(float *)(state + 0x3D8) * 0.0003490659f);
            *(u16 *)(state + 0x392) = (D_L18_001B1240 * 5 + 2) / 6;
            func_PAL_L18_0042BA90(obj, 10, 0, 10.0f);
            func_00335668(obj, 6, -1);
            return 1;
        }
        return 0;
    case 0xED4:
        range = D_L18_001B1280;
    case 0xEE1:
        if (func_00308AD0(obj + 0x10, state + 0x220) < range && !*(s16 *)(state + 0x396) && !D_L18_001AFBB0 && D_L18_00189E20.mode != 0x6F) {
            func_PAL_L18_0042BA90(obj, 10, 0, 10.0f);
            func_00335668(obj, 6, -1);
            return 1;
        }
        return 0;
    default:
        func_002C27F0(D_L18_001B1308, *(s16 *)(obj + 0xAA));
        return 0;
    }
}

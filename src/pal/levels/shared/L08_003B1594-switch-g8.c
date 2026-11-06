/* func_PAL_L08_003B1594, a second PAL row for func_PAL_L03_003A7720's bytes, placed in levels 8, 11,
 * 16, 17 and 18. Like it, the PAL copy of func_L03_003A40A0: the same C, where the turn rates
 * 0.0017453294f and 0.20943955f become 0.0025132746f and 0.25132746f, and the particle time
 * D_L03_001AF510 is read through the 50 Hz scale (x * 5 + 2) / 6 at both of its uses. */
#include "include_asm.h"
typedef struct { float x, y, z, w; } SwitchVector;
typedef struct { char pad0[0x80]; float x,y; char pad1[0x2294-0x88]; int mode; } SwitchPlayer;
extern unsigned char D_L03_00189E20[] __attribute__((nosda));
extern unsigned char *D_L03_001B2A1C __attribute__((sda));
extern int D_L03_001B2548[] __attribute__((sda));
extern int D_001A79F0[] __attribute__((sda));
extern unsigned char D_0019B2E8[] __attribute__((nosda));
extern float D_L03_001AF510 __attribute__((sda));
extern int D_L03_001AF514 __attribute__((sda));
extern float D_L03_001AF518 __attribute__((sda));
extern float D_L03_001AF51C __attribute__((sda));
extern void func_002A0488(void *, int, int, int);
extern void func_L03_0043AC40(void *);
extern float func_00283248(float, float);
extern float func_002AAA00(void *, float, float, float, float, void *, int);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_00283CF0(float);
extern int func_002A77E0(int);
extern void func_002C3150(void *, void *, int, int, int, int, float);
extern void func_L03_0043AD30(void *);
extern int func_L02_002EF388(void *, void *, void *, int, int);

void func_PAL_L08_003B1594(unsigned char *object) {
    unsigned char *state = *(unsigned char **)(object + 0x68);
    unsigned char *related;
    SwitchVector position;
    SwitchVector velocity;
    float angle, direction;
    int color, random;
    unsigned short flags;
    float *anglePointer;
    int m;
    switch (object[0x20]) {
    case 0:
        flags = *(unsigned short *)(object + 0x34) | 0x1000;
        *(unsigned short *)(object + 0x34) = flags;
        if (*(int *)(state + 0x30) != -1 ||
            (*(int *)(state + 0x3C) != -1 &&
             (related = D_L03_001B2A1C + (*(int *)(state + 0x3C) << 8)) != 0 &&
             related[0x20] != 0xFE && related[0x20] != 0xFD)) {
            object[0x30] = 0xFF;
            *(unsigned short *)(object + 0x34) = flags | 0x41;
            object[0x20] = 2;
        } else {
            func_002A0488(object, 0xC0, 0xC0, 0xC0);
            func_L03_0043AC40(object);
            object[0x20] = 1;
        }
        break;
    case 1:
        if (*(short *)(object + 0xAA) == 0x323) {
            anglePointer = (float *)(object + 0xF8);
            angle = func_00283248(((SwitchPlayer *)D_L03_00189E20)->x - *(float *)(object + 0x10),
                                  ((SwitchPlayer *)D_L03_00189E20)->y - *(float *)(object + 0x14));
            func_002AAA00(anglePointer, angle, 0.0025132746f, 0.0025132746f, 0.25132746f, state + 0x38, 0);
            m = D_L03_001B2548[0];
            if ((m & 1) && object[0x31]) {
                direction = 1.0f;
                if (m & 4)
                    direction = -1.0f;
                func_00282F20(&position, object + 0xD0, direction * D_L03_001AF51C);
                func_00282F20(&velocity, &position, -2.0f / ((D_L03_001AF510 * 5.0f + 2.0f) * 0.16666667f));
                func_00282CC0(&position, &position, object + 0x10);
                color = func_00283CF0((D_L03_001AF510 * 5.0f + 2.0f) * 0.16666667f) & 0xFF;
                random = func_002A77E0(0xFF) & 0xFF;
                func_002C3150(&position, &velocity, D_L03_001AF514, color, random, 0, D_L03_001AF518);
            }
        }
        if (((SwitchPlayer *)D_L03_00189E20)->mode != 0x2B)
            func_L03_0043AD30(object);
        break;
    case 2:
        if (D_0019B2E8[*(int *)(state + 0x30) + D_001A79F0[0] * 16] == 0) {
            if (*(int *)(state + 0x3C) == -1)
                return;
            related = D_L03_001B2A1C + (*(int *)(state + 0x3C) << 8);
            if (related && related[0x20] != 0xFE && related[0x20] != 0xFD)
                return;
        }
        *(unsigned short *)(object + 0x34) &= 0xFFBE;
        func_L02_002EF388(object, object + 0x10, object + 0xF0, 0, 0);
        *(int *)(state + 0x30) = -1;
        object[0x20] = 0;
        break;
    default:
        break;
    }
}

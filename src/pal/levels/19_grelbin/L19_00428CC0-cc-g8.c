/* func_PAL_L19_00428CC0, the PAL copy of func_L19_00423548: the same C, where rename func_002A7470 becomes func_PAL_002A7E68; rename func_L19_00423270 becomes func_PAL_L19_004289C0; rename func_002B0A18 becomes func_PAL_002B1588; wrap *(float *)(*(u8 **)(object + 0x24) + 0x24) (({e}) * 1.2. */
#include "common.h"

extern int D_001A79F0[] __attribute__((sda));
extern char D_00189EA0[];
extern float D_L19_001B1EB0 __attribute__((sda)), D_L19_001B1EB4 __attribute__((sda));
extern float D_L19_001B1EB8 __attribute__((sda)), D_L19_001B1EBC __attribute__((sda));
extern float D_L19_001B1EC0 __attribute__((sda)), D_L19_001B1EC4 __attribute__((sda));
extern float D_L19_001B1EC8 __attribute__((sda));
/* The hero: its state word and another mode word. */
typedef struct {
    char pad0[0x2294];
    int state;
    int pad2298;
    int mode;
} HeroModes;
extern HeroModes D_00189E20;
extern u8 D_0019B4A8[];
/* Player stats: the pending bolt credit at +0x1C. */
typedef struct { u8 pad0[0x1C]; int pendingBolts; } PlayerStats;
extern PlayerStats D_001A7A00 MACRO_ADDR;
extern u8 D_001A7A60[] MACRO_ADDR;
extern int D_L19_001A903C[] MACRO_ADDR;
extern void func_PAL_002A7E68(void *, int, int, int);
extern void func_PAL_L19_004289C0(void *);
extern float func_00282E80(void *, void *);
extern float func_00282C48(float);
extern float func_00282E20(void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282FB8(void *, void *, float);
extern void func_0029F338(void *);
extern int func_002E5DA0(int, int, void *, int);
extern int func_002E5E58(int, int, void *);
extern int func_L19_0042A860(void);
extern void func_PAL_002B1588(int, int);

void func_PAL_L19_00428CC0(u8 *object)
{
    float direction[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(object + 0x68);
    float distance, movement, threshold;
    switch (object[0x20]) {
    case 0:
        object[0x23] = 0x80;
        *(u32 *)(object + 0x78) = 0xFFAAAAAA;
        *(u16 *)(object + 0x34) |= 0x800;
        object[0x20] = 1;
        if (object[0x43]) func_PAL_002A7E68(object, 0, 0, 0);
        break;
    case 1:
        if (func_00282E80(object + 0x10, D_00189EA0) < D_L19_001B1EB0 &&
            func_00282C48(*(float *)(object + 0x18) - *(float *)(D_00189EA0 + 8)) < D_L19_001B1EC0) {
            *(float *)state = D_L19_001B1EC4;
            if (object[0x43] != 1) func_PAL_002A7E68(object, 1, 0, 20);
            *(float *)(object + 0x48) = *(float *)state + *(float *)state;
            object[0x20] = 2;
        }
        if (object[0x31]) func_PAL_L19_004289C0(object);
        break;
    case 2:
        if (object[0x43] != 1) func_PAL_002A7E68(object, 1, 0, 20);
        *(float *)state += (1.0f - *(float *)state) * D_L19_001B1EBC;
        *(float *)(object + 0x48) = *(float *)state + *(float *)state;
        func_00282CF0(direction, D_00189EA0, object + 0x10);
        direction[2] += 0.6f;
        distance = func_00282E20(direction);
        threshold = 0.12f;
        if (*(int *)(D_00189EA0 + 0x2214) != 0x31)
            movement = D_L19_001B1EB4 * (*(float *)state * 0.020000001f);
        else {
            movement = D_L19_001B1EB8 * (*(float *)state * 0.020000001f);
            threshold = 0.8f;
        }
        func_00282FB8(direction, direction, movement);
        func_00282CC0(object + 0x10, object + 0x10, direction);
        if (*(float *)(object + 0x2C) > 0.1f || distance < threshold || distance < movement)
            *(float *)(object + 0x2C) -= D_L19_001B1EC8 * ((*(float *)(*(u8 **)(object + 0x24) + 0x24)) * 1.2f);
        if ((distance < movement &&
             *(float *)(object + 0x2C) < *(float *)(*(u8 **)(object + 0x24) + 0x24) * 0.01f) ||
            D_00189E20.mode == 0x14 || D_00189E20.mode == 0x19 ||
            D_00189E20.state == 0x39 || D_00189E20.state == 0x6F) {
            if (*(u8 **)(state + 4)) {
                u8 *linked = *(u8 **)(state + 4);
                int h = *(unsigned short *)(linked + 0xB2);
                if (h & 1) {
                    unsigned char *e = &D_0019B4A8[((short)h >> 1) + (D_001A79F0[0] << 10)];
                    if (((*e >> 4) & 7) != 7) {
                        *e += 0x10;
                    }
                } else {
                    unsigned char *e = &D_0019B4A8[((short)h >> 1) + (D_001A79F0[0] << 10)];
                    if ((*e & 7) != 7) {
                        *e += 1;
                    }
                }
                func_0029F338(*(u8 **)(state + 4));
            }
            D_001A7A00.pendingBolts++;
            func_002E5DA0(3, 0, object, 0x11C7);
            func_0029F338(object);
            if (!func_L19_0042A860() && !D_001A7A60[6]) {
                D_001A7A60[6] = 1;
                func_002E5E58(1, 0, 0);
                func_PAL_002B1588(0x1233, -1);
                D_L19_001A903C[0] = 1;
            }
            func_0029F338(object);
        } else func_PAL_L19_004289C0(object);
        break;
    }
}

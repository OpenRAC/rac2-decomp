/* Complete nonmatching reconstruction. -O2 -G8 -ffunction-sections:
 * 1108/1136 bytes; local US 0/1; US2 and PAL have no catalogue row.
 * Default and -g profiles tie. Remaining: collection control flow, saved FP lifetimes and checkpoint-counter addressing.
 * Reopen with independent original control-flow or lifetime evidence.
 * Aligned local vectors cover every actual 16-byte producer/consumer access.
 */
#include "common.h"
typedef struct { float v[4]; } CollectionVector __attribute__((aligned(16)));
extern float D_L19_001B1EB0 __attribute__((sda)), D_L19_001B1EB4 __attribute__((sda));
extern float D_L19_001B1EB8 __attribute__((sda)), D_L19_001B1EBC __attribute__((sda));
extern float D_L19_001B1EC0 __attribute__((sda)), D_L19_001B1EC4 __attribute__((sda));
extern float D_L19_001B1EC8 __attribute__((sda));
extern u8 D_00189EA0[], D_00189E20[], D_0019B4A8[] MACRO_ADDR;
extern int D_001A79F0, D_001A7A1C;
extern u8 D_001A7A66;
extern int D_L19_001A903C;
extern void func_002A7470(void *, int, int, int), func_L19_00423270(void *);
extern float func_00282E80(void *, void *), func_00282C48(float), func_00282E20(void *);
extern void func_00282CF0(void *, void *, void *), func_00282CC0(void *, void *, void *);
extern void func_00282FB8(void *, void *, float), func_0029F338(void *);
extern int func_002E5DA0(int, int, void *, int), func_002E5E58(int, int, void *);
extern int func_L19_0042A860(void);
extern void func_002B0A18(int, int);

/* Attract the collectible to the hero and record its linked object's checkpoint. */
void func_L19_00423548(u8 *object)
{
    CollectionVector direction;
    u8 *state = *(u8 **)(object + 0x68);
    float distance, movement, threshold;
    switch (object[0x20]) {
    case 0:
        *(u16 *)(object + 0x34) |= 0x800;
        object[0x23] = 0x80;
        *(u32 *)(object + 0x78) = 0xFFAAAAAA;
        object[0x20] = 1;
        if (object[0x43]) func_002A7470(object, 0, 0, 0);
        break;
    case 1:
        if (func_00282E80(object + 0x10, D_00189EA0) < D_L19_001B1EB0 &&
            func_00282C48(*(float *)(object + 0x18) - *(float *)(D_00189EA0 + 8)) < D_L19_001B1EC0) {
            *(float *)state = D_L19_001B1EC4;
            if (object[0x43] != 1) func_002A7470(object, 1, 0, 20);
            object[0x20] = 2;
            *(float *)(object + 0x48) = *(float *)state + *(float *)state;
        }
        if (object[0x31]) func_L19_00423270(object);
        break;
    case 2:
        if (object[0x43] != 1) func_002A7470(object, 1, 0, 20);
        *(float *)state += (1.0f - *(float *)state) * D_L19_001B1EBC;
        *(float *)(object + 0x48) = *(float *)state + *(float *)state;
        func_00282CF0(&direction, D_00189EA0, object + 0x10);
        direction.v[2] += 0.6f;
        distance = func_00282E20(&direction);
        threshold = 0.12f;
        if (*(int *)(D_00189EA0 + 0x2214) != 0x31)
            movement = D_L19_001B1EB4 * (*(float *)state * 0.016666668f);
        else {
            movement = D_L19_001B1EB8 * (*(float *)state * 0.016666668f);
            threshold = 0.8f;
        }
        func_00282FB8(&direction, &direction, movement);
        func_00282CC0(object + 0x10, object + 0x10, &direction);
        if (*(float *)(object + 0x2C) > 0.1f || distance < threshold || distance < movement) {
            *(float *)(object + 0x2C) -= D_L19_001B1EC8 * *(float *)(*(u8 **)(object + 0x24) + 0x24);
            if (distance < movement &&
                *(float *)(object + 0x2C) < *(float *)(*(u8 **)(object + 0x24) + 0x24) * 0.01f)
                goto collected;
        }
        if (*(int *)(D_00189E20 + 0x229C) == 0x14 || *(int *)(D_00189E20 + 0x229C) == 0x19 ||
            *(int *)(D_00189E20 + 0x2294) == 0x39 || *(int *)(D_00189E20 + 0x2294) == 0x6F) {
collected:
            if (*(u8 **)(state + 4)) {
                u8 *linked = *(u8 **)(state + 4);
                unsigned short id = *(u16 *)(linked + 0xB2);
                u8 *counter;
                int value;
                if (id & 1) {
                    counter = D_0019B4A8 + ((short)id >> 1) + (D_001A79F0 << 10);
                    value = *counter;
                    if (((value >> 4) & 7) != 7) *counter = value + 16;
                } else {
                    counter = D_0019B4A8 + ((short)id >> 1) + (D_001A79F0 << 10);
                    value = *counter;
                    if ((value & 7) != 7) *counter = value + 1;
                }
                func_0029F338(*(u8 **)(state + 4));
            }
            D_001A7A1C++;
            func_002E5DA0(3, 0, object, 0x11C7);
            func_0029F338(object);
            if (!func_L19_0042A860() && !D_001A7A66) {
                D_001A7A66 = 1;
                func_002E5E58(1, 0, 0);
                func_002B0A18(0x1233, -1);
                D_L19_001A903C = 1;
            }
            func_0029F338(object);
        } else func_L19_00423270(object);
        break;
    }
}

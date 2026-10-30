/* Complete nonmatching reconstruction. -O2 -G8 -ffunction-sections:
 * 1048/1064 bytes; local US/US2 each 0/1; PAL has no catalogue row.
 * Default and -g profiles tie. Remaining: trigger-table addressing, damage/constructor setup and allocation.
 * Reopen with independent original control-flow or lifetime evidence.
 * Aligned local vectors cover every actual 16-byte producer/consumer access.
 */
#include "common.h"
typedef struct { float v[4]; } DeathVector __attribute__((aligned(16)));
extern u8 D_L19_0021EA30[] MACRO_ADDR;
extern u8 D_0019B4A8[] MACRO_ADDR;
extern int D_001A79F0;
extern u32 D_L19_001B1DE0 __attribute__((sda));
extern u8 D_L19_001BFEC0[];
extern void func_0029F338(void *), func_0029FCC0(void *, int, void *);
extern int func_002ACD38(void *);
extern float func_002A89A8(void *, int, float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern void func_002B0408(void *, void *, void *);
extern void func_002A7398(void *, int, int);
extern void func_002A7750(void *, int, int), func_L19_00423270(void *);
extern u8 *func_002A9640(void *, int, int);
extern float func_002A96A0(void *, void *), func_00283CE0(int);
extern int func_00283CF0(float), func_002A7820(int, int);
extern void func_002AB800(void *, void *), func_002AB8C0(void *, void *);
extern int func_002E5CF8(int, int, void *);
extern void func_002B0A68(void *, int, void *, float, float, float, float, int);
extern u8 *func_0029EFD0(int);
extern void func_002A0F48(void *), func_002AB650(void *);

/* Check the checkpoint trigger, take damage, and replace the dead actor. */
void func_L19_004203F0(u8 *object)
{
    DeathVector direction, point;
    u8 *state, *hit, *replacement;
    float damage;
    int sound, count;
    unsigned short id;
    int bits;
    if (object[0xB0] != 255) {
        id = *(u16 *)(object + 0xB2);
        if (D_L19_0021EA30[(short)id + 0x464]) goto remove;
        bits = D_0019B4A8[((short)id >> 1) + (D_001A79F0 << 10)];
        if (id & 1 ? ((bits >> 4) & 7) : (bits & 7)) {
remove:
            func_0029F338(object);
            return;
        }
    }
    if (!func_002ACD38(object + 0x10)) return;
    state = *(u8 **)(object + 0x68);
    if (object[0x20] == 0) {
        *(u32 *)(object + 0x78) = D_L19_001B1DE0;
        *(float *)(object + 0x18) = func_002A89A8(object + 0x10, 0, 0.5f) - 0.1f;
        object[0x31] = 1;
        *(u16 *)(object + 0x34) |= 0x100;
        *(int *)(object + 0x48) = 0;
        qcopy(&direction, object + 0x10);
        qcopy(&point, object + 0x10);
        direction.v[2] += 1.0f;
        point.v[2] -= 10.0f;
        func_002761F8(&direction, &point, 2, object, 0);
        func_002B0408(object + 0xC0, D_L19_001BFEC0, 0);
        func_002A7750(object, 1, 0);
    }
    if (object[0x31]) func_L19_00423270(object);
    if (object[0x20] != 1) return;
    hit = func_002A9640(object, 0x230000, 0);
    damage = func_002A96A0(object, hit);
    if (damage > 0.0f) {
        *(float *)(state + 0x20) -= damage;
        state[0x59] = 255; state[0x57] = 255; state[0x58] = 255;
        func_002AB800(object, state + 0x50);
        count = func_00283CF0(func_00283CE0(*(short *)(state + 0x24)) - *(float *)(state + 0x20));
        if (count < 8)
            count = func_00283CF0(func_00283CE0(*(short *)(state + 0x24)) - *(float *)(state + 0x20));
        else count = 7;
        func_002A7398(object, 0, count);
    }
    sound = func_002A7820(0, 2);
    if (*(float *)(state + 0x20) > 0.0f) func_002E5CF8(sound, 0, object);
    object[0xA8] = 255;
    func_002AB8C0(object, state + 0x50);
    if (*(float *)(state + 0x20) > 0.0f) return;
    qzero(&direction);
    direction.v[2] = 1.0f / 6.0f;
    if (hit) qcopy(&point, hit);
    else {
        qcopy(&point, object + 0x10);
        point.v[2] += 2.0f;
    }
    qzero(&direction);
    direction.v[2] = 0.15f;
    func_002B0A68(object, 15, &direction, 3.0f, 6.0f, 3.0f, 6.0f, 255);
    replacement = func_0029EFD0(0x1266);
    if (replacement) {
        replacement[0x23] = 0x50;
        *(u16 *)(replacement + 0x34) |= 0x800;
        replacement[0x30] = 255;
        *(u16 *)(replacement + 0x32) = 255;
        replacement[0x31] = 1;
        replacement[0x20] = 0;
        *(float *)(replacement + 0x2C) = *(float *)(*(u8 **)(replacement + 0x24) + 0x24) * 0.65f;
        replacement[0xBC] = 0;
        qcopy(replacement + 0x10, object + 0x10);
        func_002A0F48(replacement);
        func_002AB650(replacement);
        func_002E5CF8(3, 0, object);
        *(u8 **)(*(u8 **)(replacement + 0x68) + 4) = object;
    }
    object[0x20] = 2;
    *(u16 *)(object + 0x34) = (*(u16 *)(object + 0x34) | 0x41) & 0xEFFF;
    *(int *)(object + 0x98) = 0;
}

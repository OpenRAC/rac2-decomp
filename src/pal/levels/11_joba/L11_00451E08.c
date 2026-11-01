#include "include_asm.h"

#include "common.h"
extern void func_002B60B0(char *, float, float, float, float);
extern void func_PAL_002A7E68(char *, int, int, int);
extern void func_002A7750(char *, int, int);
extern void func_PAL_002A0F68(char *);
extern void func_002A0488(char *, int, int, int);
extern int func_PAL_002B3F18(char *, char *, char *);
extern void func_L11_003973F8(char *, int, float, float);
extern u16 *D_L11_001FC420[];
extern u8 *D_L11_001B359C __attribute__((sda));

/*W23E*/


void func_PAL_L11_00451E08(char *object, int mode, int active) {
    char *state = *(char **)(object + 0x68);
    char **slot;
    char *collision, *health;
    int i;

    *(short *)(state + 0x4CA) = 0;
    *(short *)(state + 0x88) = 0;
    *(u8 *)(state + 0x2E) = 1;
    *(float *)(state + 0x20) = *(short *)(state + 0x24);
    *(short *)(state + 0x4D2) = active;
    func_002B60B0(object, 0.0064000003f, 0.16000001f,
                  0.0016755164f, 0.12566373f);
    *(u8 *)(object + 0x7F) = 0;
    *(u16 *)(object + 0x34) = (*(u16 *)(object + 0x34) | 0x1000) & 0xFFB9;
    *(int *)(object + 0x98) = *(int *)(*(char **)(object + 0x24) + 0x10);
    if (*(short *)(state + 0x4D2) != 0) {
        func_002A7750(object, 4, 2);
        *(u16 *)(object + 0x34) |= 0x100;
        func_PAL_002A7E68(object, 2, 0, 0);
        func_PAL_002A0F68(object);
        func_L11_003973F8(object, 0, 2.0f, 2.0f);
    } else {
        func_002A7750(object, 3, 0);
        *(u8 *)(object + 0x31) = 1;
        *(u16 *)(object + 0x34) &= 0xFEFE;
    }
    *(u8 *)(state + 0x6A) = 0;
    collision = state + 0x1F0;
    health = state + 0x20;
    for (i = 0; i < 2; i++) {
        slot = (char **)(state + 0x4A0 + i * 4);
        if (*slot != 0) {
            *(u16 *)(*slot + 0x34) &= 0xFFFE;
            *(u8 *)(*slot + 0x31) = 1;
            *(int *)(*slot + 0x98) = *(int *)(*(char **)(*slot + 0x24) + 0x10);
        }
    }
    *(short *)(state + 0x4D0) = mode;
    *(int *)(state + 0x200) = 0;
    func_PAL_002B3F18(object, collision, health);
    if (*(short *)(state + 0x50) != 0) {
        *(short *)(state + 0x50) = 0;
        func_002A0488(object, *(u8 *)(state + 0x54), *(u8 *)(state + 0x55),
                      *(u8 *)(state + 0x56));
        *(short *)(state + 0x52) = 1;
    }
}


extern void func_L11_00441978(s32 a0, int a1);
extern s32 func_441868(s32 a0, s32 a1);
extern s32 func_33C800(char *a0, s32 a1, s32 a2, s32 a3, float f12, float f13);
extern s32 D_L11_001B35B8[] __attribute__((sda));
extern f32 func_00282E80(u8 *, u8 *);
extern s32 func_L11_00441868(u8 *, s32);
extern s32 func_002B3BA8(u8 *, s32, f32, f32, s32, s32);
extern void func_002A7A00(void *a0, float f12, float f13);
extern void func_PAL_002B15D8(char *a0, int a1, void *a2, float f12, float f13, float f14,
                        float f15, int a3);
extern void func_L11_00441978(int, int);
extern void func_PAL_L00_003FB330(char *, int, int, int, int, int, int, int,
                         float, float, int, int, int, int);
extern void func_002E5DA0(int, int, char *, int);
extern void func_002A7A00(void *, float, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_PAL_002B15D8(char *, int, void *, float, float, float, float, int);

void func_PAL_L11_00451FD0(char *object) {
    char *state = *(char **)(object + 0x68);
    float direction[4];
    char **slot;
    int i;

    if (*(short *)(state + 0x4CA) == 1)
        func_L11_00441978(*(int *)(object + 0xB8), 0xDCF);
    *(short *)(state + 0x4CA) = 0;
    *(int *)(state + 0x490) = 0;
    if (*(u8 *)(object + 0x31) != 0) {
        func_PAL_L00_003FB330(object + 0x10, 0, 0x1E, 5, 5, 5, 0x2D, 1,
                     0.5f, 0.0f, 1, 0, 0, 0);
        func_002E5DA0(0, 0, object, 0xDF7);
        func_002A7A00(direction, 0.040000003f, 0.10000001f);
        func_00282CC0(direction, direction, state + 0xD0);
        func_PAL_002B15D8(object, 0x7F0, direction, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);
    }
    slot = (char **)(state + 0x4A0);
    for (i = 1; i >= 0; i--) {
        if (*slot != 0) {
            *(u16 *)(*slot + 0x34) |= 1;
            *(u8 *)(*slot + 0x31) = 0;
            *(int *)(*slot + 0x98) = 0;
        }
        slot++;
    }
    func_PAL_002A7E68(object, 0, 0, 3);
    func_PAL_002A0F68(object);
    func_002A7750(object, 1, 0);
    *(u8 *)(object + 0x31) = 0;
    *(int *)(object + 0x98) = 0;
    *(u16 *)(object + 0x34) = (*(u16 *)(object + 0x34) & 0xEFFF) | 0x47;
}


#include "include_asm.h"

#include "common.h"
extern void func_002A7750(char *, int, int);
extern void func_002A7750();
extern void *func_002B60B0(u8 *, float, float, float, float);
extern void func_002A0488(void *, u8, u8, u8);
extern u8 D_L02_00220730;

/* Sets the actor up: re-registers its sub-objects and arms its effects. */
void func_PAL_L02_003F5D78(char *arg0, int arg1) {
    char *state = *(char **)(arg0 + 0x68);
    int i;

    *(float *)(state + 0x20) = (float)*(short *)(state + 0x24);
    *(u16 *)(state + 0x98) = 0;
    func_002B60B0((u8 *)arg0, 0.0064000003f, 0.16000001f,
                  0.0016755164f, 0.12566373f);
    func_002A7750(arg0, 3, 0);
    *(int *)(arg0 + 0x98) = *(int *)(*(char **)(arg0 + 0x24) + 0x10);
    *(u8 *)(state + 0x7A) = 0;
    *(u8 *)(arg0 + 0x31) = 1;
    *(u8 *)(arg0 + 0x7F) = 0;
    *(u16 *)(arg0 + 0x34) = (*(u16 *)(arg0 + 0x34) | 0x1000) & 0xFFB8;
    {
        char **slot = (char **)(state + 0x4C0);

        for (i = 1; i >= 0; i--) {
            if (*slot != 0) {
                *(u16 *)(*slot + 0x34) &= 0xFFFE;
                *(u8 *)(*slot + 0x31) = 1;
                *(int *)(*slot + 0x98) = *(int *)(*(int *)(*slot + 0x24) + 0x10);
            }
            slot++;
        }
    }
    {
        short flag = *(short *)(state + 0x60);

        *(u16 *)(state + 0x4F0) = arg1;
        *(u16 *)(state + 0x4EA) = 0;
        if (flag != 0) {
            *(short *)(state + 0x60) = 0;
            func_002A0488(arg0, *(u8 *)(state + 0x64), *(u8 *)(state + 0x65),
                          *(u8 *)(state + 0x66));
            *(short *)(state + 0x62) = 1;
        }
    }
}


extern void func_L02_003F18E8(char *);
extern void func_PAL_002A7E68(char *, int, int, int);
extern void func_PAL_002A0F68(char *);
extern void func_002A7A00(char *, float, float);
extern void func_PAL_002B15D8(char *, int, char *, float, float, float, float, int);
extern void func_00282CC0(void *, void *, void *);
extern void func_L02_003FC1B0(int, int);
extern void func_PAL_L00_003FB330(char *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void func_002E5DA0(int, int, char *, int);

/* Tears the actor down: stops its effect, clears its sub-objects, resets flags. */
void func_PAL_L02_003F5EB0(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);
    char buffer[0x10];
    int i;

    if (*(short *)(state + 0x4EA) == 1)
        func_L02_003FC1B0(*(int *)(arg0 + 0xB8), 0xB22);
    *(short *)(state + 0x4EA) = 0;
    *(int *)(state + 0x4B0) = 0;
    *(unsigned char *)(state + 0x7A) = 0;
    *(unsigned char *)(state + 0x2E) = 1;
    if (*(unsigned char *)(arg0 + 0x31) != 0) {
        func_PAL_L00_003FB330(arg0 + 0x10, 0, 0x1E, 5, 5, 5, 0x2D, 1, 0.5f, 0.0f, 1, 0, 0, 0);
        func_002E5DA0(0, 0, arg0, 0xC3E);
        func_002A7A00(buffer, 0.040000003f, 0.10000001f);
        func_00282CC0(buffer, buffer, state + 0xE0);
        func_PAL_002B15D8(arg0, 0x7F, buffer, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);
    }
    {
        char **slot = (char **)(state + 0x4C0);

        for (i = 1; i >= 0; i--) {
            if (*slot != 0) {
                *(unsigned short *)(*slot + 0x34) |= 1;
                *(unsigned char *)(*slot + 0x31) = 0;
                *(int *)(*slot + 0x98) = 0;
            }
            slot++;
        }
    }
    func_PAL_002A7E68(arg0, 0, 0, 3);
    func_PAL_002A0F68(arg0);
    func_002A7750(arg0, 1, 0);
    *(unsigned char *)(arg0 + 0x31) = 0;
    *(int *)(arg0 + 0x98) = 0;
    *(unsigned short *)(arg0 + 0x34) =
        (*(unsigned short *)(arg0 + 0x34) & 0xEFFF) | 0x47;
}


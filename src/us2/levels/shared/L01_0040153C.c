/* func_US2_L01_0040153C, the USA v2.00 copy of func_L01_003FFFE8: the same C, where the
   func_L00_002B9D60 argument 0x6F becomes -1, case 4 tests before func_0029B3E0, and
   func_002AF0A8 and func_L01_002BEB90 become func_US2_002AFF10 and ref_US2_L01_0040153C_00
   (func_US2_L01_002BEEA8 in level 1, func_US2_L08_002D31F8 in level 8). */
#include "include_asm.h"
#include "common.h"

extern int D_001A79F0 __attribute__((sda));

extern void func_002A7750(char *, int, int);
extern void func_0026FEB8(void *, int);
extern void func_0029F338(void *);
extern int func_L00_00329520(void *, int);
extern void func_0027D330(int);
extern void func_L00_002B9D60(void *, void *, int, int);
extern void func_L00_00303530(int, int);
extern int func_00288AA0(void *, int);
extern void func_00288BE8(void *);
extern void func_002F5CC8(void);
extern int func_002F5D10(void);
extern void func_002AD7B8(int);
extern void func_US2_002AFF10(int);
extern void func_002A0430(int);
extern void func_002DF3F8(void *, void *);
extern void func_L01_002C1988(int);
extern void ref_US2_L01_0040153C_00(int, int);
extern void func_L01_00323310(int, int);
extern void func_0029B3E0(int, int);
extern unsigned char D_0019B2E8[];
extern char D_00189EA0[];

/* Level data, at another address in each level that has this function. The trigger flag is
   read at an offset from its owner: retail never moves it into a delay slot. */
extern int ref_L01_003FFFE8_00[] __attribute__((sda));
extern char ref_L01_003FFFE8_01[];
extern char ref_L01_003FFFE8_02[];
extern char ref_L01_003FFFE8_03[];
extern char ref_L01_003FFFE8_04[];
extern char *ref_L01_003FFFE8_05 __attribute__((sda));
extern char ref_L01_003FFFE8_06[];
extern int ref_L01_003FFFE8_07 __attribute__((sda));

/* a trigger moby: reports bad setup, waits to be activated, plays its effects and removes itself */
void func_US2_L01_0040153C(char *m)
{
    char *d = *(char **)(m + 0x68);
    int active;

    switch (*(unsigned char *)(m + 0x20)) {
    case 0:
        if (*(int *)d == -1)
            func_0026FEB8(ref_L01_003FFFE8_01, *(short *)(m + 0xB2));
        if (*(short *)(d + 4) == -1)
            func_0026FEB8(ref_L01_003FFFE8_02, *(short *)(m + 0xB2));
        if (*(int *)(d + 8) == -1)
            func_0026FEB8(ref_L01_003FFFE8_03, *(short *)(m + 0xB2));
        if (*(unsigned char *)(m + 0xB0) != 255) {
            if (D_0019B2E8[*(unsigned char *)(m + 0xB0) + (D_001A79F0 << 4)] & 128) {
                func_0029F338(m);
                break;
            }
        } else
            func_0026FEB8(ref_L01_003FFFE8_04, *(short *)(m + 0xB2));
        func_002A7750(m, 1, -1);
        break;
    case 1:
        active = 0;
        if (*(unsigned char *)(m + 0xBC) ||
            (*(int *)d != -1 && func_L00_00329520(D_00189EA0, *(int *)d) &&
             (*(int *)(d + 0x18) || *(int *)(D_00189EA0 + 0x2C0))))
            active = 1;
        if (active) {
            int ready;

            *(unsigned char *)(m + 0x30) = 255;
            func_0027D330(20);
            if (*(int *)(d + 0xC) != -1) {
                char *p = ref_L01_003FFFE8_05 + (*(int *)(d + 0xC) << 7);

                func_L00_002B9D60(p + 0x30, p + 0x70, -1, 1);
            }
            if (*(int *)(d + 8) != -1)
                func_L00_00303530(*(int *)(d + 8), 0);
            ready = 1;
            if (D_001A79F0 == 8 && *(short *)(d + 4) == 0) {
                if (func_00288AA0(ref_L01_003FFFE8_06, 0x57)) {
                    func_00288AA0(ref_L01_003FFFE8_06, 9);
                    func_00288AA0(ref_L01_003FFFE8_06, 0x58);
                    func_00288BE8(ref_L01_003FFFE8_06);
                    func_002F5CC8();
                    ref_L01_003FFFE8_07 = 1;
                } else
                    ready = 0;
            }
            if (ready)
                func_002A7750(m, 3, -1);
        }
        break;
    case 3:
        ref_L01_003FFFE8_00[1] = 1;
        if (!func_002F5D10()) {
            ref_L01_003FFFE8_00[1] = 0;
            if (*(short *)(d + 6) != -1) {
                func_002AD7B8(*(short *)(d + 6));
                func_US2_002AFF10(*(short *)(d + 6));
            }
            func_002A7750(m, 4, -1);
        }
        break;
    case 4:
        if (*(unsigned char *)(m + 0xB0) != 255) {
            int n = *(unsigned char *)(m + 0xB0);

            if (!(D_0019B2E8[n + (D_001A79F0 << 4)] & 128)) {
                func_002A0430(n);
                func_002DF3F8(m + 0x10, m + 0xF0);
            }
        }
        func_L01_002C1988(0);
        ref_US2_L01_0040153C_00(0, 1);
        func_L01_00323310(*(int *)(d + 0x14), *(int *)(d + 0x10));
        if (*(unsigned char *)(m + 0xB0) != 255 || *(short *)(d + 6) != -1)
            func_0029B3E0(0, -1);
        func_0029F338(m);
        break;
    }
}

/* func_PAL_L04_003F16D8, the PAL copy of func_L04_003ED740: the same C, where func_L00_002B9D60
   becomes func_PAL_L00_002B9CD8. */
#include "common.h"

typedef struct {
    char pad[0x284];
    char *target;
    int timer;
} HeroD740;

extern char *D_L04_001B24DC __attribute__((sda));
extern char *D_L04_001B25CC[] __attribute__((sda));
extern char D_00189EA0[], D_00188660[];
extern HeroD740 D_L04_001B9540;
extern u8 D_0019B2E8[];
extern char *D_0018C0B0;
extern int D_001A79F0 __attribute__((sda));
extern int func_002A8508(int, int);
extern int func_002E5DA0(int, int, void *, int);
extern int func_002ACBC8(void *, int);
extern void func_L00_00429020(int);
extern int func_L00_00429048(int);
extern void func_002A0430(unsigned int);
extern void func_002DF3F8(void *, void *);
extern int func_L00_0035F5A0(int, int, void *);
extern void func_L00_003294F0(void *, int);
extern void func_PAL_L00_002B9CD8(void *, void *, int, int);
extern void func_002E59F8(int);

void func_PAL_L04_003F16D8(char *o)
{
    char *p = *(char **)(o + 0x68);

    switch (*(u8 *)(o + 0x20)) {
    case 0:
        *(u8 *)(o + 0x20) = 1;
        break;
    case 1: {
        int i, busy;

        busy = 0;
        for (i = 0; i < 4; i++)
            if (func_002A8508(*(int *)(p + 4 * i), -1))
                busy = 1;
        if (!busy) {
            if (*(int *)(p + 0x18) == 0) {
                char *a, *b;

                a = D_L04_001B24DC + (*(int *)(p + 0x74) << 8);
                b = D_L04_001B24DC + (*(int *)(p + 0x78) << 8);
                if (*(u8 *)(a + 0x20) == 1)
                    func_002E5DA0(0, 0, a, 0xCE6);
                *(u8 *)(a + 0x20) = 2;
                *(u8 *)(b + 0x20) = 2;
                if (func_002ACBC8(D_00189EA0, *(int *)(p + 0x70)) &&
                    !(D_0019B2E8[*(u8 *)(o + 0xB0) + D_001A79F0 * 16] & 128)) {
                    func_L00_00429020(*(int *)(p + 0x10));
                    *(u8 *)(o + 0x20) = 2;
                    *(u8 *)(a + 0x20) = 3;
                    *(u8 *)(b + 0x20) = 3;
                }
            } else if (*(int *)(p + 0x18) == 1) {
                char *a, *b;

                if (!(D_0019B2E8[*(u8 *)(o + 0xB0) + D_001A79F0 * 16] & 128)) {
                    func_L00_00429020(*(int *)(p + 0x10));
                    *(u8 *)(o + 0x20) = 4;
                    a = D_L04_001B24DC + (*(int *)(p + 0x74) << 8);
                    b = D_L04_001B24DC + (*(int *)(p + 0x78) << 8);
                    func_002E5DA0(0, 0, a, 0xCE6);
                    *(u8 *)(a + 0x20) = 2;
                    *(u8 *)(b + 0x20) = 2;
                    if (!(D_0019B2E8[*(u8 *)(o + 0xB0) + D_001A79F0 * 16] & 128)) {
                        func_002A0430(*(u8 *)(o + 0xB0));
                        func_002DF3F8(o + 0x10, o + 0xF0);
                    }
                }
            }
        } else if (*(int *)(p + 0x18) == 0 &&
                   func_002ACBC8(D_00189EA0, *(int *)(p + 0x70)) &&
                   !(D_0019B2E8[*(u8 *)(o + 0xB0) + D_001A79F0 * 16] & 128)) {
            func_L00_00429020(*(int *)(p + 0x10));
            *(u8 *)(o + 0x20) = 2;
        }
        break;
    }
    case 2: {
        if (func_L00_00429048(*(int *)(p + 0x10))) {
            *(signed char *)(o + 0x95) = func_L00_0035F5A0(23, 4, D_0018C0B0);
            {
                char *base = D_L04_001B24DC;
                int i;

                for (i = 0; i < 14; i++) {
                    char *a, *q;
                    int id = *(int *)(p + 0x20 + i * 4);

                    if (id != -1) {
                        a = base + (id << 8);
                        if (a) {
                            q = *(char **)(a + 0x68);
                            *(int *)(q + 0x260) = *(int *)(q + 0x264);
                            *(int *)(q + 0x250) = *(int *)(q + 0x254);
                            *(int *)(a + 0x98) = *(int *)(*(char **)(a + 0x24) + 0x10);
                            *(u16 *)(a + 0x34) &= 0xFFBE;
                        }
                    }
                }
            }
            {
                char *a = D_L04_001B25CC[0] + (*(int *)(p + 0x14) << 7);

                qcopy(D_00189EA0, a + 0x30);
                qcopy(D_00189EA0 + 0x10, a + 0x70);
                func_L00_003294F0(o, 1);
                *(u16 *)(o + 0x96) = 0;
                *(u8 *)(o + 0x20) = 5;
            }
        }
        break;
    }
    case 3: {
        char *a, *b;

        if (func_L00_00429048(*(int *)(p + 0x10))) {
            {
                char *record = D_L04_001B25CC[0] + (*(int *)(p + 0x14) << 7);

                qcopy(D_00189EA0, record + 0x30);
                record += 0x70;
                qcopy(D_00189EA0 + 0x10, record);
            }
            a = D_L04_001B24DC + (*(int *)(p + 0x20) << 8);
            b = D_L04_001B24DC + (*(int *)(p + 0x24) << 8);
            *(u8 *)(a + 0x95) = 4;
            *(u8 *)(a + 0x20) = 17;
            if (!D_L04_001B9540.target) {
                D_L04_001B9540.target = b;
                D_L04_001B9540.timer = 0;
            }
            *(int *)(a + 0x98) = *(int *)(*(char **)(a + 0x24) + 0x10);
            {
                char *bd = *(char **)(b + 0x68);
                *(int *)(bd + 0x270) = *(int *)(bd + 0x274);
            }
            {
                char *ad = *(char **)(a + 0x68);
                *(int *)(ad + 0x270) = *(int *)(ad + 0x274);
            }
            *(u8 *)(o + 0x20) = 5;
        }
        break;
    }
    case 4: {
        char *a;

        if (func_L00_00429048(*(int *)(p + 0x10))) {
            a = D_L04_001B25CC[0] + (*(int *)(p + 0x14) << 7);
            func_PAL_L00_002B9CD8(a + 0x30, a + 0x70, 111, 1);
            *(u8 *)(o + 0x20) = 5;
            func_L00_003294F0(o, 1);
        }
        break;
    }
    case 5: {
        if (*(u16 *)(o + 0x96) < 60)
            ++*(u16 *)(o + 0x96);
        else if (func_L00_00429048(*(int *)(p + 0x10))) {
            int i = *(signed char *)(o + 0x95);

            if (i != -1) {
                char *a = (char *)D_00188660 + i * 0x70;
                if (*(char **)(a + 0x88) == D_0018C0B0 && *(u8 *)(a + 0x74))
                    func_002E59F8(i);
            }
            i = -1;
            *(signed char *)(o + 0x95) = i;
        }
        break;
    }
    }
}

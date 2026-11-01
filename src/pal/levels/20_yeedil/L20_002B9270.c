#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L20_002B9270);

#include "common.h"
extern char D_00189E20[];
extern u8 D_00139568[];
extern s32 func_L00_002ADEA0(s32 index);
extern void func_PAL_0028D6F0(void);
extern void func_PAL_0028D738(void);
extern void func_PAL_0028DC40(void);
extern s32 func_0028B3D0(s32, s32, void *, void *, void *, s32, s32);
extern void func_PAL_L00_002AF6C0(void);
extern void func_PAL_L00_002B1E88(void);
extern void func_L00_00322EC8(char *);
extern void func_L00_002D2E68(void);
extern void func_L00_002A6708(void);
extern void func_L00_002A53B8(void);
extern void func_L00_002F6B90(s32);
extern void func_L00_002D24B8(void);
extern void func_002A677C(s32);
extern s32 func_PAL_L20_002D7920(s32, s32);
extern void func_PAL_L00_002D2668(f32, s32, s32);
extern s32 D_00138320[];
extern void func_PAL_L20_002C6358(void);

/* func_L20_002B7A48 is defined in L20_002B7A48-selector.c. */

/*W23E*/

/* func_L20_002B93E0 is defined in L20_002B7A48-g8.c (it reaches data through $gp). */

void func_PAL_L20_002C5738(s32 a0, s32 a1, char *a2)
{
    char *D = D_00189E20;
    s32 p0 = a0;
    char *p2 = a2;
    s32 p1 = a1;
    char *block;

    func_PAL_L00_002AF6C0();
    *(u8 *)(D + 0x22B6) = 1;
    func_PAL_L00_002B1E88();
    *(s32 *)(D + 0x2290) = *(s32 *)(D + 0xC18);
    func_L00_00322EC8(D + 0x18E0);
    func_L00_00322EC8(D + 0x1A30);
    *(s32 *)(*(s32 *)(D + 0x2290) + 0x9C) = -1;
    if (p0 != 4 || *(u8 *)(D + 0x22B4) != p0)
        func_L00_002D2E68();
    func_L00_002A6708();
    func_L00_002A53B8();
    block = D_00189E20;
    *(u8 *)(block + 0x22B4) = p0;
    *(s32 *)(block + 0xC14) = (s32)p2;
    *(s32 *)(block + 0x2290) = (s32)p2;
    if ((p0 & 0xFF) == 1) {
        if (D_00138320[0] & 0x10) {
            func_0028B3D0(0x23, 0, (void *)func_PAL_0028D6F0, (void *)func_PAL_0028D738,
                          (void *)func_PAL_0028DC40, 0, 0);
            func_L00_002F6B90(3);
        }
    }
    func_PAL_L20_002C6358();
    D = D_00189E20;
    *(f32 *)(D + 0x250) = *(f32 *)(D + 0x258);
    *(f32 *)(D + 0x254) = *(f32 *)(D + 0x25C);
    *(u16 *)(*(s32 *)(D + 0x2290) + 0x34) |= 6;
    *(f32 *)(D + 0xC20) = 1.0f;
    *(f32 *)(D + 0xC24) = 1.0f;
    func_L00_002D24B8();
    func_002A677C(*(s32 *)(D + 0x2290));
    *(u16 *)(D + 0x24F2) = p1;
    switch (p0) {
    case 1:
        *(u16 *)(D + 0x24D4) = *(u16 *)(D + 0x24CC);
        *(s32 *)(D + 0x24CC) = *(s32 *)(D + 0x24D0);
        if (*(s32 *)(D + 0x24CC) >= 5)
            *(s32 *)(D + 0x24CC) = 4;
        break;
    case 4:
        qcopy(D + 0x80, p2 + 0x10);
        qcopy(D + 0x90, p2 + 0xF0);
        *(u16 *)(D + 0x24D4) = *(u16 *)(D + 0x24CC);
        *(s32 *)(D + 0x24CC) = 3;
    }
    func_PAL_L20_002D7920(p1, 2);
    if (p0 == 4)
        func_PAL_L00_002D2668(4.0f, 0xF, 0);
}


#include "include_asm.h"
#include "common.h"

typedef unsigned int TI128 __attribute__((mode(TI)));

extern void func_0029F338(void *);

extern void func_0029FCC0(void *, int, void *);

extern void *func_002A9640(void *, int, int);

extern void func_002A8E20(void *, void *);

typedef struct {
    TI128 f00;
    u32 f10;
    u32 f14;
    u8 f18;
    u8 f19;
    u16 f1A;
    f32 f1C;
    u32 f20;
} L01_003A6350_Params;

typedef struct {
    u8 pad[0x1FB0];
    f32 f1FB0;
    f32 f1FB4;
} D00189E20_View;

extern D00189E20_View D_00189E20;

extern void func_00282948();

/* func_L01_003835D8 is defined in L01_003835D8-match.c. */

/* func_L01_003839F0 is defined in L01_003839F0.c. */


INCLUDE_ASM("asm/levels", func_L01_003A5BB8);

/* func_L01_003A6028 is defined in L01_003A6028-g8.c. */

/* func_L01_003A6280 is defined in L01_003A6280-helper-g8.c. */

void func_L01_003A6350(u8 *arg0) {
    u8 *s0 = *(u8 **)(arg0 + 0x68);
    u8 *a0 = *(u8 **)(s0 + 0x50);
    L01_003A6350_Params p;
    void *r;

    if (a0 == 0 || *(s16 *)(a0 + 0xAA) != *(s32 *)(s0 + 0x54) ||
        a0[0x20] == 0xFE || a0[0x20] == 0xFD) {
        func_0029F338(arg0);
        return;
    }
    {
        if (*(s32 *)(s0 + 0x5C) != -1) {
            func_0029FCC0(*(u32 *)(s0 + 0x50), *(s32 *)(s0 + 0x5C), arg0 + 0x10);
        }
        r = func_002A9640(arg0, -1, 0);
        if (r != 0) {
            qcopy(&p.f00, (u8 *)r + 0x10);
            p.f10 = *(u32 *)((u8 *)r + 0x20);
            p.f14 = *(u32 *)((u8 *)r + 0x24);
            p.f18 = ((u8 *)r)[0x28];
            p.f19 = ((u8 *)r)[0x29];
            p.f1A = *(u16 *)((u8 *)r + 0x2A);
            p.f1C = *(f32 *)((u8 *)r + 0x2C) * *(f32 *)(s0 + 0x58);
            p.f20 = *(u32 *)((u8 *)r + 0x30);
            func_002A8E20(*(u32 *)(s0 + 0x50), &p);
        }
        arg0[0xA8] = 0xFF;
    }
}

INCLUDE_ASM("asm/levels", func_L01_003A6638);

void func_L01_003A6448(float *arg0, float *arg1) {
    *arg0 = -D_00189E20.f1FB0;
    *arg1 = -D_00189E20.f1FB4;
    if (*arg0 > 1.0f)
        *arg0 = 1.0f;
    else if (*arg0 < -1.0f)
        *arg0 = -1.0f;
    if (*arg1 > 1.0f)
        *arg1 = 1.0f;
    else if (*arg1 < -1.0f)
        *arg1 = -1.0f;
}



/* func_L01_003B1F08 lives in L01_003B1F08.c. */

/* func_L01_003B4200 lives in L01_003B4200.c: its grouped copies and
   global-address scheduling need a per-file profile. */

/* func_L01_003B4480 lives in L01_003B4480.c: its 128-bit copy needs the grouped
   copy profile, which is a per-file flag. */

extern void func_00115484(void *, int, int);

extern int func_00277F48(float, char *, int, char *, int);

extern void *D_L01_001C3980[];

void func_L01_003B45D8(void *arg0, void **arg1, int *arg2) {
    int i;
    int count;
    void *p;

    func_00115484(arg1, 0, 4);
    *arg2 = 0;
    count = func_00277F48(3.5f, (char *)arg0 + 0x10, 1, (char *)arg0, 0);
    if (count <= 0)
        return;
    for (i = 0; i < count; i++) {
        p = D_L01_001C3980[i];
        if (p == 0)
            continue;
        if (*(s16 *)((u8 *)p + 0xAA) != 0xA26)
            continue;
        *(u32 *)((u8 *)p + 0x9C) = 1;
        *(u8 *)((u8 *)D_L01_001C3980[i] + 0xBC) = 1;
        arg1[*arg2] = D_L01_001C3980[i];
        *arg2 = *arg2 + 1;
        if (*arg2 >= 16)
            break;
    }
}

void func_L01_003B46C8(char **arg0, int *arg1) {
    int i;

    if (*arg1 <= 0)
        return;
    i = 0;
    do {
        *(int *)(arg0[i] + 0x9C) = 0;
        i++;
    } while (i < *arg1);
}


/* func_L01_003B49D8 and func_L01_003B4AD0 live in L01_003B49D8.c: their clamp needs
   -ffast-math (the retail's min.s), which is a per-file flag. */

void func_L01_003B4BD8(u8 *arg0) {
    char *s0 = *(char **)(arg0 + 0x68);

    if (arg0[0x21] != 0xFF) {
        if (*(int *)(s0 + 0x340) != 0) {
            func_00282948(*(int **)(s0 + 0x33C));
        }
    }
    *(int *)(s0 + 0x340) = 0;
}

int func_L01_003B4C20(u8 *arg0) {
    char *a1 = *(char **)(arg0 + 0x68);
    int r = 1;

    if (arg0[0x21] != 0xFF) {
        if (*(int *)(a1 + 0x340) == 0) {
            int *p = *(int **)(a1 + 0x33C);
            *p = *p + 1;
        }
    }
    *(int *)(a1 + 0x340) = r;
    return r;
}

/* func_L01_003B4C58 is defined in L01_003B4C58-g8.c. */

extern float func_002A89A8(void *, int, float);
extern float func_002A7940(void);
extern float func_002A7878(float, float);
extern int func_002A7820(int, int);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CC0(void *, void *, void *);
extern void func_L01_0032EF38(void *, int, int, float, float, int);
extern void func_002B0990(u8 *, u8 *, s32, s32, f32);

void func_L01_003B50C8(char *object, int count, float height)
{
    float position[4];
    float angle, radius, first, second;
    char *state;
    int life, left;

    if (height == -1.0f) {
        state = *(char **)(object + 0x68);
        if (*(int *)(state + 0x1E8) != -1 || *(int *)(state + 0x198) != 0)
            return;
        height = *(float *)(state + 0x1A0) + 0.015f;
    }
    if (height == 0.0f)
        height = func_002A89A8(object + 0x10, 0, 0.5f) + 0.025f;
    for (left = 0; left < count; left++) {
        angle = func_002A7940();
        radius = func_002A7878(0.0f, 0.8f);
        first = func_002A7878(0.0f, 1.5f);
        second = func_002A7878(1.5f, 5.7f);
        life = func_002A7820(100, 180);
        position[0] = func_00283180(angle) * radius;
        position[1] = func_00283198(angle) * radius;
        position[2] = 0.0f;
        func_00282CC0(position, position, object + 0x10);
        position[2] = height;
        func_L01_0032EF38(position, 0x38002028, 0x2020, first, second, life);
    }
}

/* Clears the measured 0x350 word when it is set, then draws the new duration
   if the old one is still short. */
void func_L01_003B5310(u8 *a0) {
    u8 *p = *(u8 **)(a0 + 0x68);
    u16 flags;

    if (*(u32 *)(p + 0x350) != 0) {
        *(u32 *)(p + 0x350) = 0;
        if (*(s32 *)(p + 0x330) < 200) {
            *(u32 *)(p + 0x330) = func_002A7820(300, 360);
        }
    }
    if (*(u32 *)(p + 0x244) != 1)
        func_00282948(p + 0x330);
    flags = *(u16 *)(a0 + 0x96);
    if (flags < 65534)
        *(u16 *)(a0 + 0x96) = flags + 1;
    func_00282948(p + 0x32C);
    func_00282948(p + 0x334);
    func_002B0990(a0, p + 0x250, 6, 1, 4.0f);
}

INCLUDE_ASM("asm/levels", func_L01_003B53C8);

/* func_L01_003B57A8 uses the SDA pointer to the position table. */
extern u8 *D_L01_001B264C __attribute__((sda));
extern char D_00189EA0[];
extern float func_00282E80(void *, void *);

/* Of the (up to four) positions whose indices are listed at the state's +0x310, copies the one
   func_00282E80 rates highest against D_00189EA0 to OUT (its rating at +0xC), then stores
   func_002A89A8's value for it at +0x8. A position is the 16-byte record at +0x30 of the
   index's 0x80-byte entry in the D_L01_001B264C table. */
void func_L01_003B57A8(u8 *arg0, u8 *out) {
    s32 *p = (s32 *)(*(u8 **)(arg0 + 0x68) + 0x310);
    u8 pos[16] __attribute__((aligned(16)));
    s32 count = 4;
    f32 f;

    *(f32 *)(out + 0xC) = 0.0f;
    while (--count >= 0) {
        if (*p != -1) {
            qcopy(pos, D_L01_001B264C + *p * 0x80 + 0x30);
            f = func_00282E80(pos, D_00189EA0);
            if (*(f32 *)(out + 0xC) < f) {
                qcopy(out, pos);
                *(f32 *)(out + 0xC) = f;
            }
        }
        p++;
    }
    *(f32 *)(out + 0x8) = func_002A89A8(out, 0, 10.0f);
}

/* func_L01_003B5878 is defined in L01_003B5878-g8.c. */

/* func_L01_003B9F30 is defined in L01_003B9F30-g16.c. */

/* func_L01_003BAFB0 lives in the -g8 sibling file (it reads a float through $gp). */

/* func_L01_003BAFB8 is defined in L01_003BAFB8-g8.c. */

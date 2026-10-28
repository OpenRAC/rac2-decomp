#include "common.h"

extern char *D_L06_001B9890[];

extern char *func_00270280(int);

extern float func_002A8A20(char *);

extern int func_00273B70(char *);

extern void func_002A7750(char *, int, int);

extern void func_0029F338(char *);

extern void func_002ABBB8(void *, void *, int, int, int, int, int, int, int, int, int, int,
                          float, float, float, float, float, float, float);

extern void func_002A7A00(float *, float, float);

extern float func_00282C48(float);

extern float func_002A78D8(float, float);

extern float func_002A7878(float, float);

extern char *func_00273730(char *, int, int, int, char *, char *, float *, int, float, float);

extern void func_L06_0045C350(unsigned char *);

extern int func_002A8600(char **, int, int, int);

extern int func_002A86E8(char **, char *, int, int);

extern void func_002A7470(char *, int, int, int);

extern void func_002AA548(char *, char *, float, float, float, float);

extern int func_L04_0033CB08(char *, char *, int, int, float, float);

extern void func_00282D30(char *, char *, float);

extern float func_00282E20(char *);

extern float func_00283C80(float, float);

extern float func_00283180(float);

extern float func_00283198(float);

extern int func_002A9640(char *, int, int);

extern void func_L06_00457C00(char *, int, void *, int, float, float, float, float);

extern void func_002E5CF8(int, int, char *);

extern void func_L00_00326110(char *, int, float);

extern float D_L06_001B234C __attribute__((sda));

extern float D_001B2350 __attribute__((sda));

extern int func_0035CBA0(char *, int, int);

extern void func_L06_0045BE30(char *, int, float, float, float, float);

extern int func_003A0948(int, int, char *);

extern void func_00350388(char *);

INCLUDE_ASM("asm/levels", func_L06_00458138);

extern char *func_0029EFD0(int);
extern float func_00283B98(float, float);
extern void func_0029FCC0(void *, int, void *);
extern void func_002A0F48(char *);

/* Spawns a chained segment from the record at +0x68 and recurses while length remains. */
char *func_L06_004583A8(char *a0)
{
    char *state = *(char **)(a0 + 0x68);
    char *obj = 0;
    char *child;
    float angle;
    float d;
    float len;

    if (*(float *)(state + 4) > 0.0f) {
        obj = func_0029EFD0(0xFE2);
        if (obj != 0) {
            *(unsigned char *)(obj + 0x31) = 1;
            *(unsigned char *)(obj + 0x30) = 0xFF;
            *(short *)(obj + 0x32) = 0xFF;
            *(unsigned char *)(obj + 0x20) = 1;
            child = *(char **)(obj + 0x68);
            *(float *)(obj + 0x2C) = *(float *)(a0 + 0x2C);
            *(long *)(obj + 0x38) = *(long *)(a0 + 0x38);
            *(char **)(child + 0x10) = a0;
            *(int *)child = *(int *)state;
            len = *(float *)(state + 0x1C);
            *(float *)(child + 0x1C) = len;
            *(float *)(child + 4) = *(float *)(state + 4) - len;
            angle = func_00283B98(*(float *)(a0 + 0xF8), 3.1415927f);
            *(float *)(child + 8) = angle;
            qcopy(obj + 0xF0, a0 + 0xF0);
            *(float *)(obj + 0xF8) = angle;
            d = *(float *)(state + 0xC);
            if (d == 0.0001f)
                *(float *)(child + 0xC) = 1.0f;
            else if (d == -0.0001f)
                *(float *)(child + 0xC) = -1.0f;
            else if (d == 1.0f)
                *(float *)(child + 0xC) = -0.0001f;
            else if (d == -1.0f)
                *(float *)(child + 0xC) = 0.0001f;
            func_0029FCC0(*(char **)(child + 0x10), 0, obj + 0x10);
            func_002A0F48(obj);
            if (*(float *)(child + 4) > 0.0f)
                func_L06_004583A8(obj);
        }
    }
    return obj;
}

INCLUDE_ASM("asm/levels", func_L06_00458568);

INCLUDE_ASM("asm/levels", func_L06_004587E8);


INCLUDE_ASM("asm/levels", func_L06_00458F30);

INCLUDE_ASM("asm/levels", func_L06_00459020);

INCLUDE_ASM("asm/levels", func_L06_00459620);

INCLUDE_ASM("asm/levels", func_L06_00459828);

extern float func_0032D788(void *, void *);

void func_L06_00459B18(char *a0) {
    int count;
    int i;
    float f;

    if (a0 == 0) {
        return;
    }
    count = *(int *)a0;
    i = 0;
    while (i < count) {
        int off = i * 16;

        f = func_0032D788(a0 + (off + 16), a0 + (((i + 1) % count) * 16 + 0x10));
        *(float *)(a0 + off + 0x1C) = f;
        i++;
        count = *(int *)a0;
    }
}

int func_L06_00459BA8(char *a0, char *a1)
{
    float f = func_002A8A20(a0 + 0x10);
    float t;

    *(float *)(a1 + 0x120) = f;
    t = *(float *)(*(char **)(a1 + 0x11C)) - f;
    *(float *)(a1 + 0x128) = f + t * 0.5f;
    if (t < 0.41f) {
        return 2;
    }
    if (0.68f < t) {
        return 0;
    }
    return 1;
}

void func_L06_00459C38(unsigned char *a0)
{
    switch (a0[0xBC]) {
    case 0:
        if (a0[0x43] != 0) {
            func_002A7470((char *)a0, 0, 0, 0xA);
        }
        a0[0x20] = 1;
        break;
    case 1:
        if (a0[0x43] != 3) {
            func_002A7470((char *)a0, 3, 0, 0xA);
        }
        a0[0x20] = 7;
        break;
    case 2:
        if (a0[0x43] != 9) {
            func_002A7470((char *)a0, 9, 0, 0xA);
        }
        a0[0x20] = 0xF;
        break;
    }
}

/* func_L06_00459D08 is defined in L06_00458138-g8.c. */

INCLUDE_ASM("asm/levels", func_L06_00459EC0);

INCLUDE_ASM("asm/levels", func_L06_0045A0D0);

int func_L06_0045A1B0(char *a0, char *a1, float p1, float p2, float p3, float p4, float p5,
                      float p6, float p7)
{
    float x = func_00282E20(a1 + 0xC0);
    float y = func_00283C80(*(float *)(a0 + 0xF8), p1);
    int r = 0;

    if (y < p2) {
        x += p3;
        r = 1;
    } else if (p4 < y) {
        x -= p5;
    }
    if (p6 < x) {
        x = p6;
    } else if (x < p7) {
        x = p7;
    }
    *(float *)(a1 + 0xC0) = func_00283180(*(float *)(a0 + 0xF8)) * x;
    *(float *)(a1 + 0xC4) = func_00283198(*(float *)(a0 + 0xF8)) * x;
    return r;
}

INCLUDE_ASM("asm/levels", func_L06_0045A2D8);

extern void func_003514C8(void *, int, void *);

extern int func_0031EBF8(f32, void *, int, void *);

extern void *D_L06_001BFC98;

int func_L06_0045A490(void *a0, void *a1, f32 f12) {
    char buf[16];
    int r;

    func_003514C8(a0, 0, buf);
    r = func_0031EBF8(f12, buf, 0x21, a0);
    if (r != 0) {
        if (D_L06_001BFC98 == a1) {
            return 1;
        }
    }
    return 0;
}

int func_L06_0045A500(char *a0, int a1, int a2)
{
    char *found = 0;

    if (func_002A8600(&found, *(unsigned char *)(a0 + 0x21), 0, 0) != 0) {
        return 0;
    }
    while (found != 0) {
        if (found != a0) {
            int v = *(unsigned char *)(found + 0x20);

            if (v >= a1) {
                if (v <= a2) {
                    return 1;
                }
            }
        }
        if (func_002A86E8(&found, found, 0, 0) != 0) {
            return 0;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/levels", func_L06_0045A5B0);

void func_L06_0045BD38(char *a0)
{
    char *p;
    int n;

    if (*(unsigned char *)(a0 + 0x20) == 0) {
        *(unsigned char *)(a0 + 0x20) = 1;
        *(unsigned short *)(a0 + 0x34) |= 0x800;
    }

    p = (char *)func_0035CBA0(a0, 0x4010000, 0);
    if (p != 0 && *(short *)(*(char **)(p + 0x20) + 0xAA) != 0xFE5) {
        n = 3;
        if (D_L06_001B234C < 0.8999999761581421f && D_001B2350 < 0.8999999761581421f)
            n = 0xE;

        func_L06_0045BE30(a0, n, 0.0f, 3.263000011444092f, 1.9739999771118164f,
                          0.11666667461395264f);
        func_003A0948(0, 0, a0);
        func_00350388(a0);
    } else {
        *(unsigned char *)(a0 + 0xA8) = 0xFF;
    }
}

void func_L06_0045BFC0(unsigned char *a0)
{
    char *o = *(char **)(a0 + 0x68);

    switch (a0[0x20]) {
    case 0:
        *(unsigned short *)(a0 + 0x34) |= 0x800;
        func_002A7750((char *)a0, 1, -1);
        break;
    case 1:
        if (func_002A9640((char *)a0, 0x4010000, 0) != 0) {
            if (*(int *)o == 0) {
                func_002A7750((char *)a0, 2, -1);
            }
        }
        a0[0xA8] = 0xFF;
        break;
    case 2: {
        char tmp[16];

        func_00282D30(tmp, (char *)(a0 + 0xD0), -0.033333335f);
        func_L06_00457C00((char *)a0, 3, tmp, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
        func_002E5CF8(0, 0, (char *)a0);
        func_L00_00326110((char *)a0, 1, 0.0f);
        func_0029F338((char *)a0);
        break;
    }
    }
}

/* Looks up the object bound to the given flags; unless the hit object's own field says
   0xFE5, it starts a smoke emitter, spawns one particle with the level's own callback
   and six more in a loop, then clears the object's byte at 0xA8. */
void func_L06_0045C0F0(char *a0)
{
    char *hit;
    char *p;
    float local[3];
    int i;

    hit = (char *)func_002A9640(a0, 0x4010001, 0);
    if (hit != 0 && *(short *)(*(char **)(hit + 0x20) + 0xAA) != 0xFE5) {
        func_002E5CF8(0, 0, a0);
        func_002ABBB8(a0, a0 + 0x10, 0, 10, 3, 9, -1, 1, 1, -1, 0, 0x810001,
                      0.0f, 0.0f, 4.0f, 2.0f, 9.0f, 0.0f, 15.0f);
        func_002A7A00(local, 0.0333333350718021392822265625f, 0.066666670143604278564453125f);
        local[2] = func_00282C48(local[2]);
        p = func_00273730(a0, 1, *(short *)(a0 + 0xAA), 6, a0 + 0x10, a0 + 0xF0,
                          local, 1, func_002A78D8(20.0f, 45.0f), 15.0f);
        if (p != 0) {
            *(void (**)(void))(p + 0x64) = (void (*)(void))func_L06_0045C350;
        }
        for (i = 0; i < 6; i++) {
            func_002A7A00(local, 0.10000000894069671630859375f, 0.2000000178813934326171875f);
            local[2] = func_00282C48(local[2]);
            func_00273730(a0, 2, *(short *)(a0 + 0xAA), i, a0 + 0x10, a0 + 0xF0,
                          local, 0xFF, func_002A78D8(20.0f, 45.0f),
                          func_002A7878(15.0f, 25.0f));
        }
        func_002E5CF8(1, 0, a0);
        func_L00_00326110(a0, 1, 0.0f);
        func_0029F338(a0);
    }
    *(unsigned char *)(a0 + 0xA8) = 0xFF;
}

void func_L06_0045C350(unsigned char *a0)
{
    switch (a0[0x20]) {
    case 0:
        if (func_00273B70((char *)a0) != 0) {
            func_002A7750((char *)a0, 1, -1);
            *(unsigned short *)(a0 + 0x34) |= 0x2800;
        }
        break;
    case 1:
        func_00273B70((char *)a0);
        if (a0[0x23] < 2) {
            func_0029F338((char *)a0);
        } else {
            a0[0x23] -= 2;
        }
        break;
    }
}

INCLUDE_ASM("asm/levels", func_L06_0045C3E8);

INCLUDE_ASM("asm/levels", func_L06_0045C6D0);

INCLUDE_ASM("asm/levels", func_L06_004621C8);

INCLUDE_ASM("asm/levels", func_L06_004635E8);

INCLUDE_ASM("asm/levels", func_L06_00464900);

INCLUDE_ASM("asm/levels", func_L06_004649F0);

INCLUDE_ASM("asm/levels", func_L06_00464F40);


void func_L06_00478548(float a, float b)
{
    char *g = D_L06_001B9890[0];
    char *p;
    char *v;

    if (*(short *)(g + 0x86) != 5) {
        p = func_00270280(5);
    } else {
        p = g;
    }
    v = *(char **)(p + 0x70) + 0xE0;
    *(float *)(v + 0x44) = a;
    *(float *)(v + 0x48) = b;
}


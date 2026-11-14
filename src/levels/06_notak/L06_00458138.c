#include "common.h"
extern u8 *D_L06_001B281C MACRO_ADDR;
extern void func_L00_00429020(int);
extern short D_L06_001B3790[] __attribute__((sda));
extern short D_L06_001B37A0[] __attribute__((sda));
extern char D_L06_0025FFC0[];
extern float func_00283CE0(int);
extern void func_L06_00459020(char *, int, int, int, float, float, float);
extern void func_L06_00459620(char *);


extern float func_00283B98(float, float);
typedef struct NotakChild {
    char pad[0x20];
    unsigned char state;
    char pad21[15];
    unsigned int alpha : 8;
    unsigned int mode : 8;
    unsigned int flags : 16;
} NotakChild;
extern char *func_0029EFD0(int);
extern void func_002A0F48(char *);
extern void func_003514C8(void *, int, void *);

extern void func_002B0A68(char *, int, void *, int, float, float, float, float);
typedef unsigned int NotakQuad __attribute__((mode(TI)));
extern char D_00188660[];
extern char D_00189EA0[];
/* Keep this absolute address as one assembler macro under -G0. */
extern char D_L06_001A8F20[] __attribute__((sda));
extern void func_002A8598(int, int);
extern void func_002E59F8(int);
extern int func_002A7820(int, int);
extern int func_00282948(void *);
extern float func_00282E80(void *, void *);
extern void func_L06_0045C6D0(char *);
extern void *func_0032C700(void *, int, int, int, int, int, int, int,
                            float, float, int, int, int, int);

extern char D_L06_001B9840[];
extern void func_00282CF0(float *, const float *, const float *);
extern void func_00282F20(char *, char *, float);
extern int func_002A77E0(int);
extern void func_002ACEC0(void *, void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern char *func_002C2210(void *, int, float, float, unsigned int, int, int, void *, int, float);
extern int func_00283CF0(float);


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

extern void func_00283098(void *, void *, void *);
extern double func_001234F0(float);
extern void func_0026FEB8(char *, ...);
extern char D_L06_001B18E0[];
extern void func_L00_003263D0(char *, void *, int, float, int, void *, float, unsigned int, float, float, int);
void func_L06_00458138(char *a0) {
    float pos[4], vel[4];
    int count = 13, i;
    if (D_L06_001B234C < 0.9f && D_001B2350 < 0.9f) count = 40;
    for (i = 0; i < count; i++) {
        pos[0] = func_002A7878(-8.045f, 8.045f);
        pos[1] = func_00282C48(pos[0] * 0.1243008077f) * 1.745f;
        pos[2] = func_002A7878(0.0f, 3.99f);
        vel[0] = pos[0] * 0.0041433605f;
        vel[1] = -0.13333334f;
        vel[2] = func_002A7878(3.0f, 7.0f) * 0.0166666675f;
        func_00283098(pos, pos, a0 + 0xC0);
        func_00282CC0(pos, pos, a0 + 0x10);
        func_00283098(vel, vel, a0 + 0xC0);
        func_0026FEB8(D_L06_001B18E0, func_001234F0(pos[0]), func_001234F0(pos[1]), func_001234F0(pos[2]), func_001234F0(vel[0]), func_001234F0(vel[1]), func_001234F0(vel[2]));
        func_L00_003263D0(a0, pos, 1, 0.0f, 1, vel, 3.0f, 0x50808040, 1.0f, 5.5f, 0);
        func_003A0948(0, 0, a0);
    }
    func_00350388(a0);
}

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

/* func_L06_004587E8 is defined in L06_004587E8-axis-g8.c. */


void func_L06_00458F30(char *a0)
{
    char *obj = *(char **)(a0 + 0x68);
    char *p = D_L06_0025FFC0;
    short *t2 = D_L06_001B37A0;
    short *t1 = D_L06_001B3790;
    int i;

    for (i = 5; i >= 0; i--) {
        if (*t1 != 0) {
            float f = func_00283CE0(*t2);
            int r = func_00283CF0(f);

            func_L06_00459020(p + *(int *)(obj + 0x48) * 0x180, r, r, 4, 0.025f, 0.5f, 0.2f);
        }
        p += 0x40;
        t2++;
        t1++;
    }
    func_L06_00459620(a0);
}

/* func_L06_00459020 is defined in L06_00458138-ribbon-g8.c. */

/* func_L06_00459620 is defined in L06_00458138-render-g8.c. */

/* Emits paired particles with opposite spin and randomized velocities. */
void func_L06_00459828(float *pos, int count) {
    float velocity[4], origin[4], direction[4], axis[4], offset[4];
    float size, angle;
    int i;
    int sign;
    char *particle;
    func_00282CF0(direction, (float *)D_L06_001B9840, pos);
    func_00282F20((char *)offset, (char *)direction, 0.3f);
    direction[2] = 0;
    axis[0] = 0;
    axis[1] = 0;
    axis[2] = 1.0f;
    axis[3] = 1.0f;
    for (i = 0; i < count; i++) {
        size = func_002A7878(0.5f, 2.0f);
        sign = func_002A77E0(2);
        if (!sign) sign--;
        angle = func_002A7878(-1.0471977f, 1.0471977f);
        func_002ACEC0(velocity, direction, axis, angle);
        func_00282F20((char *)velocity, (char *)velocity, func_002A7878(0.05f, 3.0f) * 0.0166666675f);
        velocity[2] = func_002A7878(1.0f, 5.0f) * 0.0166666675f;
        func_00282CC0(origin, pos, offset);
        pos[0] += func_002A78D8(0, 0.15f);
        pos[1] += func_002A78D8(0, 0.15f);
        pos[2] += func_002A78D8(0, 0.15f);
        particle = func_002C2210(origin, 60, size * 0.1f, size, 0x7F801010, 0, sign, velocity, 0, 0.002f);
        if (particle) particle[9] = func_00283CF0(4.0f) + 0x70;
        particle = func_002C2210(origin, 60, size * 0.07f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, 0.002f);
        if (particle) particle[9] = func_00283CF0(4.0f) + 0x70;
    }
}


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

extern int func_002A8AF0(void *, void *, int);
extern int func_002761F8(void *, void *, int, void *, int);
extern int func_00277258(void *, int, void *, float);
extern float func_00283248(float, float);

/* Sweeps for a free heading when a sweep is pending, else (or when none is free) faces the
   target. The found block before the sweep is what puts the flag test's fallback on its own
   branch: its store goes into the sweep's branch-likely slot, leaving that branch behind. */
void func_L06_00459EC0(char *obj, char *st)
{
    float dir[3];
    char *p;
    float ang;
    float step;
    float total;

    if (*(int *)(st + 0x124) != 0)
        goto search;
    goto fallback;
found:
    *(float *)(st + 0x12C) = ang;
    return;
search:
    dir[0] = func_00283180(*(float *)(obj + 0xF8)) * 5.2f;
    dir[1] = func_00283198(*(float *)(obj + 0xF8)) * 5.2f;
    dir[2] = 0.0f;
    func_00282CC0(dir, dir, obj + 0x10);
    p = *(char **)(st + 0x118);
    if (func_002A8AF0(dir, p + 0x10, *(int *)p) != 0 &&
        func_002761F8(obj + 0x10, dir, 0x24, obj, 0) == 0 &&
        func_00277258(dir, 0x24, obj, 1.5f) == 0)
        return;
    step = func_00282C48(*(float *)(st + 0x130));
    ang = *(float *)(obj + 0xF8);
    total = 0.0f;
    do {
        ang = func_00283B98(ang, *(float *)(st + 0x130));
        dir[0] = func_00283180(ang) * 5.2f;
        dir[1] = func_00283198(ang) * 5.2f;
        dir[2] = 0.0f;
        func_00282CC0(dir, dir, obj + 0x10);
        p = *(char **)(st + 0x118);
        if (func_002A8AF0(dir, p + 0x10, *(int *)p) == 0 ||
            func_002761F8(obj + 0x10, dir, 0x24, obj, 0) != 0 ||
            func_00277258(dir, 0x24, obj, 1.5f) != 0) {
            total += step;
            continue;
        }
        goto found;
    } while (total < 6.283186f);
fallback:
    *(float *)(st + 0x12C) = func_00283248(*(float *)(st + 0xE0) - *(float *)(obj + 0x10),
                                         *(float *)(st + 0xE4) - *(float *)(obj + 0x14));
}

void func_L06_0045A0D0(char *a0, char *a1, float f, float g, float h)
{
    char buf[16];
    char *q = a1;

    if (*(float *)(*(char **)(a1 + 0x11C)) - 0.3f < *(float *)(a0 + 0x18)) {
        *(float *)(a1 + 0xC8) -= 0.163333335f;
    }
    qcopy(buf, a0 + 0x10);
    func_002AA548(buf + 8, q + 0xC8, *(float *)(q + 0x128), f, g, h);
    if (func_L04_0033CB08(a0, q + 0xC0, 0x400, 0x10, 1.0f, 0.0f) != 0) {
        func_00282D30(q + 0xC0, q + 0xC0, 0.5f);
    }
}

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

extern float func_0029F530(char *);
extern void func_002A8C00(void *, char *, int, void *, float);
extern int func_00277F48(void *, float, int, char *, void *);
extern void *D_L06_001BFC98;

/* Runs the shared pickup test: when the object is in the given state and the draw is inside the window, aims at the target and, on a hit with the expected tag, hands over to the next state. */
void func_L06_0045A2D8(char *obj, float lo, char *self, float hi, int kind, int sub, float scale, float reach, float range,
                       int anim, int link, int next, void *tag)
{
    float dir[4] __attribute__((aligned(16)));
    char aim[0x30] __attribute__((aligned(16)));
    float probe[4] __attribute__((aligned(16)));
    float roll = func_0029F530(obj);
    char *vec;

    if (*(u8 *)(obj + 0x20) == kind && *(u8 *)(obj + 0x42) == sub && lo < roll && roll < hi) {
        vec = self + 0xC0;
        func_00282F20((char *)dir, vec, scale);
        dir[2] = 1.0f;
        func_002A8C00(aim, obj, 1, dir, reach);
        func_003514C8(obj, 0, probe);
        if (func_00277F48(probe, range, 0x21, obj, aim) != 0 && D_L06_001BFC98 == tag) {
            func_00282D30(vec, vec, -1.0f);
            *(float *)(self + 0xC8) = -0.05f;
            if (*(u8 *)(obj + 0x43) != anim)
                func_002A7470(obj, anim, link, 5);
            *(u8 *)(obj + 0x20) = next;
        }
    }
}

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

void func_L06_0045C3E8(char *a0)
{
    char *state = *(char **)(a0 + 0x68);
    char *hit;
    float pos[4];
    *(unsigned char *)(a0 + 0x23) = 0x80;
    if (!state) {
        return;
    }
    hit = (char *)func_0035CBA0(a0, 0x4010000, 0);
    if (hit && *(short *)(*(char **)(hit + 0x20) + 0xAA) != 0xFE5) {
        if (*(unsigned char *)(a0 + 0x20) == 1) {
            func_002A8598(*(unsigned char *)(a0 + 0x21), 0);
        }
        func_003A0948(1, 0, a0);
        *(NotakQuad *)pos = 0;
        pos[2] = 1.0f;
        func_00282CC0(pos, pos, a0 + 0x10);
        func_0032C700(pos, 1, 25, 20, 20, 20, 45, 1, 1.25f, 20.0f, 1, 1, 0, 0);
        func_002B0A68(a0, 0x7F, D_L06_001A8F20, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
        func_L00_00326110(a0, 1, 0.0f);
        func_00350388(a0);
    }
    switch (*(unsigned char *)(a0 + 0x20)) {
    case 0:
        *(unsigned char *)(a0 + 0x23) = 0x80;
        *(int *)state = func_002A7820(40, 250);
        a0[0x20] = 2;
        *(int *)(state + 8) = -1;
        break;
    case 1:
        if (func_00282E80(a0 + 0x10, D_00189EA0) < 32.0f) {
            func_L06_0045C6D0(a0);
        }
        if (func_00282948(state + 4)) {
            *(int *)state = func_002A7820(200, 250);
            if (*(int *)(state + 8) != -1) {
                char *snd = D_00188660 + *(int *)(state + 8) * 0x70;
                if (*(char **)(snd + 0x88) == a0 && *(unsigned char *)(snd + 0x74)) {
                    func_002E59F8(*(int *)(state + 8));
                }
            }
            *(int *)(state + 8) = -1;
            a0[0x20] = 2;
            func_002A8598(*(unsigned char *)(a0 + 0x21), 0);
        }
        break;
    case 2:
        if (func_00282948(state) && *(unsigned char *)(a0 + 0xBC) == 0) {
            char *snd;
            *(int *)(state + 4) = func_002A7820(200, 250);
            snd = D_00188660 + *(int *)(state + 8) * 0x70;
            if (*(char **)(snd + 0x88) != a0 || !*(unsigned char *)(snd + 0x74)) {
                *(int *)(state + 8) = func_003A0948(0, 4, a0);
            }
            a0[0x20] = 1;
            func_002A8598(*(unsigned char *)(a0 + 0x21), 1);
        }
        break;
    }
    *(unsigned char *)(a0 + 0xA8) = 0xFF;
}

/* func_L06_004621C8 is defined in L06_00458138-effect-g8.c. */

void func_L06_00464900(char *a0)
{
    char *o = *(char **)(a0 + 0x68);

    switch (*(unsigned char *)(a0 + 0x20)) {
    case 0:
        *(unsigned char *)(a0 + 0x30) = 0xFF;
        *(unsigned char *)(a0 + 0x20) = 1;
        break;
    case 1: {
        int i = *(int *)(o + 4);
        char *base = (char *)D_L06_001B281C;
        char *p = (char *)(base + (i << 8));
        int t = *(unsigned char *)(p + 0x20);
        int j;
        char *q;

        if (t != 2) {
            break;
        }
        j = *(int *)(o + 8);
        q = (char *)(base + (j << 8));
        if (q == 0) {
            break;
        }
        if (*(unsigned char *)(q + 0x20) == 0xFE) {
            break;
        }
        if (*(unsigned char *)(q + 0x20) == 0xFD) {
            break;
        }
        func_L00_00429020(*(int *)o);
        *(unsigned char *)(a0 + 0x20) = t;
        break;
    }
    case 2: {
        int i = *(int *)(o + 4);
        char *p = (char *)(D_L06_001B281C + (i << 8));

        if (*(unsigned char *)(p + 0x20) != 2) {
            *(unsigned char *)(a0 + 0x20) = 1;
        }
        break;
    }
    }
}

/* func_L06_004649F0 is defined in L06_004649F0-g8.c. */

/* func_L06_00464F40 is defined in L06_00464F40-g8.c. */


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


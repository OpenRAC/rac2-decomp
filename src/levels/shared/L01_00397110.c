#include "common.h"


extern float func_002A7878(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00283098(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_00283CF0(float);
extern char *func_002BAA28(void *, void *, void *, int, int, int, int, int, int);
extern int func_001163B0(void);



INCLUDE_ASM("asm/levels", func_L01_003973A0);



extern int D_001A79F0 __attribute__((sda));

extern char D_0019B4A8[];

extern void func_L01_003115E8(int, int);

extern void func_002A7750(char *, int, int);

void func_L01_00398008(char *a2)
{
    unsigned short f = *(unsigned short *)(a2 + 0xB2);

    if (f & 1) {
        char *p = (char *)(((short)f >> 1) + (D_001A79F0 << 10)) + (int)D_0019B4A8;
        unsigned char c = *(unsigned char *)p;

        if (((c >> 4) & 7) != 7)
            *(unsigned char *)p = c + 0x10;
    } else {
        char *p = (char *)(((short)f >> 1) + (D_001A79F0 << 10)) + (int)D_0019B4A8;
        unsigned char c = *(unsigned char *)p;

        if ((c & 7) != 7)
            *(unsigned char *)p = c + 1;
    }

    if (*(unsigned char *)(a2 + 0x21) != 0xFF)
        func_L01_003115E8(*(unsigned char *)(a2 + 0x21), 1);
    else
        func_002A7750(a2, 1, -1);
}


INCLUDE_ASM("asm/levels", func_L01_00398B50);

void func_L01_00399098(char *a0)
{
    int i;
    char **p;

    *(unsigned short *)(a0 + 0x34) |= 1;
    *(unsigned char *)(a0 + 0x31) = 0;
    *(unsigned int *)(a0 + 0x98) = 0;
    p = (char **)(*(char **)(a0 + 0x68) + 0x14);
    for (i = 2; i >= 0; i--) {
        if (*p != 0) {
            *(unsigned short *)(*p + 0x34) |= 1;
            *(unsigned char *)(*p + 0x31) = 0;
        }
        p++;
    }
}


INCLUDE_ASM("asm/levels", func_L01_00399510);

void func_L01_003BD178(char *m, void *position, int count,
                      float speed, float rise, float maxRadius, float minRadius,
                      float size, float endSize)
{
    float offset[4], velocity[4], accel[4];
    int a, b, c;
    char *particle;

    {
        int i;
        for (i = 0; i < count; i++) {
            float x, y;
            x = func_00283180(func_002A7878(-3.1415927410125732f, 3.1415927410125732f));
            offset[0] = x * func_002A7878(minRadius, maxRadius);
            y = func_00283198(func_002A7878(-3.1415927410125732f, 3.1415927410125732f));
            y *= func_002A7878(minRadius, maxRadius);
            offset[1] = y;
            offset[2] = 0;
            func_00283098(offset, offset, m + 0xC0);
            {
                float range = speed * ((maxRadius - func_00282DF0(offset)) * 0.01666666753590107f) / maxRadius;
                func_00282F20(velocity, offset, func_002A7878(range * 0.25f, range));
            }
            velocity[2] += func_002A7878(rise * 0.25f, rise) * 0.01666666753590107f;
            qzero_nc(accel);
            func_00282CC0(offset, offset, position);
            velocity[3] = size;
            accel[3] = endSize;
            a = func_00283CF0(func_002A7878(15.0f, 25.0f));
            b = func_00283CF0(func_002A7878(20.0f, 40.0f));
            c = func_00283CF0(func_002A7878(30.0f, 60.0f));
            particle = func_002BAA28(offset, velocity, accel, 0x50204050, 0x7F7F7F, a, b, c, -1);
            if (particle && (func_001163B0() & 1))
                particle[3] = 0x48;
        }
    }
}




INCLUDE_ASM("asm/levels", func_L01_003D4270);

INCLUDE_ASM("asm/levels", func_L01_003D6B00);


extern int func_002A9640(char *, int, int);

extern void func_002A8598(int, int);

/* revives the round a moby belongs to and drops what it was carrying */
void func_L01_003EE8E0(char *a0)
{
    char *r = (char *)func_002A9640(a0, 0x10000, 0);

    if (r != 0) {
        char *q = *(char **)(r + 0x20);

        if (q != 0) {
            if (*(short *)(q + 0xAA) == 0x825) {
                if (*(unsigned char *)(a0 + 0x21) != 0xFF)
                    func_002A8598(*(unsigned char *)(a0 + 0x21), 2);
            }
        }
    }

    *(unsigned char *)(a0 + 0xA8) = 0xFF;
}

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
extern void func_002AF0A8(int);
extern void func_002A0430(int);
extern void func_002DF3F8(void *, void *);
extern void func_L01_002C1988(int);
extern void func_L01_002BEB90(int, int);
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
void func_L01_003FFFE8(char *m)
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

                func_L00_002B9D60(p + 0x30, p + 0x70, 0x6F, 1);
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
                func_002AF0A8(*(short *)(d + 6));
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
        func_L01_002BEB90(0, 1);
        func_L01_00323310(*(int *)(d + 0x14), *(int *)(d + 0x10));
        func_0029B3E0(0, -1);
        func_0029F338(m);
        break;
    }
}

extern void func_002A7750(char *, int, int);

extern void func_L00_00326048(char *, char *, float, int, int);

extern int D_L01_001A8F40 __attribute__((sda));

void func_L01_004110E0(char *a0)
{
    unsigned char v = *(unsigned char *)(a0 + 0x20);
    char *p = *(char **)(a0 + 0x68);

    switch (v) {
    case 0:
        func_002A7750(a0, 1, -1);
        break;
    case 1:
        if (p == 0)
            break;
        if (D_L01_001A8F40 == 2)
            func_L00_00326048(a0, p + 0xC, 0.055268768f,
                              (int)0x80AABED2u, (int)0x80466464u);
        else
            func_L00_00326048(a0, p + 0xC, 0.037815473f,
                              (int)0x8096AAAAu, (int)0x80466464u);
        break;
    }
}

extern void func_L00_004117B8(void *);
extern void ref_L01_004132D8_00(void (*)(void *), void *);
extern void func_L00_00411B30(void *);
extern void func_002A0488(void *, int, int, int);
extern int func_00283D38(int, int, float);
extern float func_00283180(float);
extern void func_L00_004110D8(void *);
extern void func_00282C88(void *);
extern void func_L00_004118A8(void *, void *, void *, void *, void *, int, int, int, void *, float);
extern int func_002A7820(int, int);
extern void func_002AF000(void *, float, float, float);
extern float func_002A7940(void);
extern float func_002A7878(float, float);
extern int func_001163B0(void);
extern int func_00277F48(void *, int, void *, int, float);
extern int func_002829D8(void *);
extern int func_00282948(void *);
extern float func_00283B98(float, float);
typedef struct {
    char data[0x18];
    char *target;
    char end[0x14];
} ParticleEffectSlot;
extern char D_00189E20[];
extern ParticleEffectSlot D_L01_00257920[];
extern char *D_L01_001C3980[];

void func_L01_004132D8(char *m) {
    float a[4], b[4];
    int i;

    qcopy_nc(m + 0x10, D_00189E20);
    for (i = 0; i < 30; i++) {
        char *s;
        char *other;
        int dead;

        if (!D_L01_00257920[i].target)
            continue;
        s = (char *)&D_L01_00257920[i];
        *(float *)(s + 0xC) = func_00283B98(*(float *)(s + 0xC), 0.20943954586982727f);
        dead = 0;
        if (*(signed char *)(*(char **)(s + 0x18) + 0x20) < 0)
            dead = 1;
        if (!*(int *)(*(char **)(s + 0x18) + 0x98))
            dead = 1;
        if (func_00282948(s))
            dead = 1;
        if (func_002829D8(s + 0x1C)) {
            int count, j;
            char *target = *(char **)(s + 0x18);

            *(float *)(s + 0x1C) = *(float *)(s + 0x14);
            count = func_00277F48(target + 0x10, 0, target, 0, 8.0f);
            for (j = 0; j < count; j++) {
                other = D_L01_001C3980[j];
                if ((*(unsigned short *)(other + 0x34) & 0x1000) && other &&
                    *(unsigned char *)(other + 0x20) != 254 && *(unsigned char *)(other + 0x20) != 253 &&
                    *(short *)(*(char **)(other + 0x24) + 0x46) == 5)
                    goto collide;
            }
        }
    random_particles:
        if (func_001163B0() % 11 == 0) {
            int j, count;

            {
                float scale = func_002A7878(0.3f, 0.65f) * 0.0009764999849721789f;
                float x = *(float *)(*(char **)(s + 0x18) + 0xC) * scale;
                float y = func_002A7940();
                float z = func_002A7940();

                func_002AF000(a, x, y, z);
            }
            {
                float scale = func_002A7878(0.3f, 0.65f) * 0.0009764999849721789f;
                float x = *(float *)(*(char **)(s + 0x18) + 0xC) * scale;
                float y = func_002A7940();
                float z = func_002A7940();

                func_002AF000(b, x, y, z);
            }
            j = func_002A7820(5, 15);
            count = func_002A7820(15, 30);
            func_L00_004118A8(m, *(char **)(s + 0x18), *(char **)(s + 0x18), a, b, 0, j, count, s, 0.0f);
        }
        if (dead) {
            func_L00_004110D8(s);
            *(char **)(s + 0x18) = 0;
            continue;
        }
        goto timer;
    collide:
        func_00282C88(a);
        func_L00_004118A8(m, *(char **)(s + 0x18), other, a, a, 1, 10, 30, s, *(float *)(s + 0x10));
        func_L00_004118A8(m, *(char **)(s + 0x18), other, a, a, 0, 10, 30, s, 0.0f);
        goto random_particles;
    timer:
        if (*(int *)(s + 0x24) == 0) {
            int c = func_00283D38(*(int *)(s + 4), *(int *)(s + 8),
                                  (func_00283180(*(float *)(s + 0xC)) + 1.0f) * 0.5f);

            func_002A0488(*(char **)(s + 0x18), c & 255, (c >> 8) & 255, (c >> 16) & 255);
        } else
            --*(int *)(s + 0x24);
    }
    func_L00_00411B30(m);
    ref_L01_004132D8_00(func_L00_004117B8, m);
}


extern char *D_001B9510;

extern float func_2E3618(char *);

extern char D_001B9380[];

extern char D_00189EA0[];

extern void func_2CF938(char *, char *);

typedef int TI128 __attribute__((mode(TI)));


extern void func_2E34A0(void *, char *, char *);

extern void func_2E3918(void *, void *, char *);

extern float func_2E33E0(float);

extern void func_323310(int, int);



extern void func_002A6CF0(void *, void *);

extern int ref_L01_004480C8_00;

void func_L01_004480C8(void *a0)
{
    func_002A6CF0(&ref_L01_004480C8_00, a0);
}

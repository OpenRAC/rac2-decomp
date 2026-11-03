#include "common.h"

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
extern int func_00282978(unsigned short *);
extern int func_00282948(char *);
extern float func_00283CE0(int);
extern int func_00283DB8(void *, float);
extern float func_002A7878(float, float);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(char *, char *, char *);
extern unsigned char *D_L09_001B285C MACRO_ADDR;
extern void func_00291450(int);
extern void func_0029F338(void *);
extern void func_00283098(void *, void *, void *);
extern int func_L00_002FCF18(void *, float, float, float, float, float);
extern unsigned char D_L09_001C7B80[];

#define S(p, o) (*(signed char *)((p) + (o)))
#define I(p, o) (*(int *)((p) + (o)))
#define F(p, o) (*(float *)((p) + (o)))
#define H(p, o) (*(short *)((p) + (o)))

void func_L09_0039BA18(unsigned char *object)
{
    unsigned char *s, *p, *sound, *m;
    Vec pos, origin, delta;
    int length;
    float r, g, b, pitch, num, den, t, nr, ng, nb, np, r2, g2, b2, pitch2;

    if (!object)
        return;
    s = *(unsigned char **)(object + 0x68);
    if (!s)
        return;
    if (H(s, 0x28) != -1 && func_00282978((unsigned short *)(s + 0x28))) {
        if (S(s, 0x2E) != -1) {
            func_00291450(S(s, 0x2E));
            S(s, 0x2E) = -1;
        }
        func_0029F338(object);
        return;
    }
    switch (object[0x20]) {
    case 0:
        object[0x30] = 255;
        qcopy(s + 0x10, object + 0x10);
        I(s, 0xC) = I(s, 0x24);
        S(s, 0x2E) = -1;
        if (I(s, 0x20) != -1)
            *(unsigned char **)(s + 0x34) = D_L09_001B285C + (I(s, 0x20) << 8);
        s[0x2D] = 0;
        I(s, 0x30) = s[0x2F];
        object[0x20] = 1;
        break;
    case 1:
        if (func_00282948((char *)(s + 0x30)))
            object[0x20] = 2;
        break;
    case 2:
        p = s + 0x38 + s[0x2D] * 5;
        r = func_00283CE0(*p++) * 0.01f;
        g = func_00283CE0(*p++) * 0.01f;
        b = func_00283CE0(*p++) * 0.01f;
        pitch = func_00283CE0(*p++);
        length = *p++;
        num = func_00283CE0(I(s, 0x30));
        den = func_00283CE0(length);
        t = num / den;
        if (s[0x2C] < s[0x2D] + 1) {
            if (I(s, 0x24) & 0x4000)
                p = s + 0x38;
            else
                p -= 5;
        }
        nr = func_00283CE0(*p++) * 0.01f;
        ng = func_00283CE0(*p++) * 0.01f;
        nb = func_00283CE0(*p++) * 0.01f;
        np = func_00283CE0(*p);
        r2 = r + (nr - r) * t;
        g2 = g + (ng - g) * t;
        b2 = b + (nb - b) * t;
        pitch2 = pitch + (np - pitch) * t;
        qcopy(&pos, object + 0x10);
        pos.f[3] = pitch2;
        if (func_00283DB8(&pos, 255.0f) != -1) {
            m = *(unsigned char **)(s + 0x34);
            if ((I(s, 0x24) & 0x1000000) && m && !((*(unsigned short *)(m + 0x34) ^ 1) & 1))
                goto stop;
            if (m)
                qcopy_nc(&origin, m + 0x10);
            else
                qcopy_nc(&origin, s + 0x10);
            if (!(I(s, 0x24) & 0x800000)) {
                if (I(s, 0x24) & 0x100000) {
                    if (I(s, 0x24) & 0x200000) {
                        delta.f[0] = func_002A7878(-F(s, 0), F(s, 0));
                        delta.f[1] = func_002A7878(-F(s, 4), F(s, 4));
                        delta.f[2] = func_002A7878(-F(s, 8), F(s, 8));
                    } else {
                        int saved = I(s, 0xC);
                        I(s, 0xC) = 0;
                        func_00282D30(&delta, s, func_002A7878(F(s, 0xC), 1.0f));
                        I(s, 0xC) = saved;
                    }
                } else {
                    int saved = I(s, 0xC);
                    I(s, 0xC) = 0;
                    qcopy(&delta, s);
                    I(s, 0xC) = saved;
                }
                if ((I(s, 0x24) & 0x400000) && *(unsigned char **)(s + 0x34))
                    func_00283098(&delta, &delta, *(unsigned char **)(s + 0x34) + 0xC0);
                func_00282CC0((char *)(object + 0x10), (char *)&origin, (char *)&delta);
            } else {
                qcopy(object + 0x10, &origin);
            }
            if (S(s, 0x2E) == -1) {
                s[0x2E] = func_L00_002FCF18(object + 0x10, pitch2, func_00283CE0(s[0x2A]) * 0.01f, r2, g2, b2);
            } else {
                sound = D_L09_001C7B80 + (S(s, 0x2E) << 5);
                qcopy(sound + 0x10, object + 0x10);
                F(sound, 0x1C) = pitch2;
                F(sound, 0) = r2;
                F(sound, 4) = g2;
                F(sound, 8) = b2;
                F(sound, 0xC) = func_00283CE0(s[0x2A]) * 0.01f;
            }
        } else {
        stop:
            if (S(s, 0x2E) != -1) {
                func_00291450(S(s, 0x2E));
                S(s, 0x2E) = -1;
            }
        }
        if (++I(s, 0x30) >= length) {
            I(s, 0x30) = 0;
            if (++s[0x2D] > s[0x2C]) {
                if (I(s, 0x24) & 0x4000)
                    s[0x2D] = 0;
                else
                    object[0x20] = 3;
            }
        }
        break;
    case 3:
        if (S(s, 0x2E) != -1) {
            func_00291450(S(s, 0x2E));
            S(s, 0x2E) = -1;
            func_0029F338(object);
        }
        break;
    }
}

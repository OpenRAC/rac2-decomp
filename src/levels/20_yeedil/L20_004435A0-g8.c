#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float func_00283CE0(int);

extern void func_L01_002F14E8(int, int, float);

extern void func_L20_00442890(char *);

extern void func_L20_004429F0(char *);

extern void func_002AEC48(void *, void *, int, float, float);

extern int func_00282948(void *);

extern void *func_L20_00442F80(char *);

extern void func_00283098(void *, const void *, const void *);

extern void func_002833F0(char *, char *);

extern void func_00282CF0(void *, void *, void *);

extern void func_002A93B0(void *);

extern void func_002B0990(void *, float *, float, int, int);


extern float D_L20_001B20B0[] SDATA(D_L20_001B20B0);


extern float D_L20_001B2164 __attribute__((sda));

void func_L20_004435A0(char *arg0) {
    char *s2 = arg0;
    char *s1 = *(char **)(arg0 + 0x68);
    char *p;
    char *dst;
    char *src;
    TI128 v0, v1, v2;
    float f;
    unsigned short n;

    if (*(unsigned char *)(arg0 + 0x95) != 6) {
        func_L01_002F14E8(0xA, 0,
                         *(float *)(s1 + 0x20)
                         / func_00283CE0(*(short *)(s1 + 0x24)));
        func_L20_00442890(arg0);
        func_L20_004429F0(arg0);
    }
    func_002AEC48(arg0, s1 + 0x250, 0, 0.015f, 0.3f);
    if (*(int *)(s1 + 0x1810) > 0) {
        if (func_00282948(s1 + 0x1810) != 0) {
            func_L20_00442F80(arg0);
            *(int *)(s1 + 0x1810) = -1;
        }
    }
    p = *(char **)(s1 + 0x1850);
    if (p != 0) {
        if (*(short *)(p + 0xAA) != 0x1316) {
            *(int *)(s1 + 0x1850) = 0;
        } else {
            if (*(unsigned char *)(p + 0x20) != 0xFE) {
                if (*(unsigned char *)(p + 0x20) != 0xFD) {
                    goto copy;
                }
            }
            *(int *)(s1 + 0x1850) = 0;
        }
    }
copy:
    dst = s1 + 0x17E0;
    src = arg0 + 0x10;
    qcopy(dst, src);
    f = *(float *)(s1 + 0x1800);
    if (f == 0.0f && *(float *)(s1 + 0x1804) == 0.0f) {
        goto done;
    }
    *(float *)(arg0 + 0xF0) = f;
    *(float *)(arg0 + 0xF4) = *(float *)(s1 + 0x1804);
    func_00283098(&v0, D_L20_001B20B0, arg0 + 0xC0);
    func_002833F0(arg0 + 0xC0, arg0 + 0xF0);
    func_00283098(&v1, D_L20_001B20B0, arg0 + 0xC0);
    func_00282CF0(&v2, &v1, &v0);
    func_00282CF0(src, src, &v2);
done:
    func_002A93B0(arg0);
    n = *(unsigned short *)(arg0 + 0x96);
    arg0[0xBD] = 2;
    if (n <= 0xFFFE) {
        *(unsigned short *)(arg0 + 0x96) = n + 1;
    }
    func_002B0990(arg0, (float *)(s1 + 0x250), D_L20_001B2164, 0, 1);
}

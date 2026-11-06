#include "include_asm.h"

#include "common.h"

extern int D_L10_00221CFC __attribute__((section(".data")));
extern int D_L10_001B13A4 __attribute__((sda));
extern void func_002B7320(void);
extern void func_L05_0037B210(void);
extern void func_L05_00379F18(int);
extern void *func_L05_00379EB8(void);
extern int func_L00_004272A0(void);
extern void func_L10_00425798(void);
extern void func_L10_00425410(int, int);
extern void func_L05_00379F48(int);
extern int D_L10_001B13F8 __attribute__((sda));
extern int D_L10_001B13FC __attribute__((sda));
extern int D_L10_001B1444 __attribute__((sda));
extern int D_L10_001B1390 __attribute__((sda));
extern int D_L10_001B1424 __attribute__((sda));
extern char *D_L10_001B251C;
extern void func_PAL_L10_003A0590(void *, void *, int, int, int, int, int, int, float, float, float, float);
extern int func_00282948(void *);
extern void func_L10_00425888(void);
extern int func_0029B3E0(int, int);
extern void func_L00_003294F0(void *, int);
extern void func_002AD7B8(int);
extern void func_0029F338(void *);
extern void *D_L10_001B1400 __attribute__((sda));
extern void *D_L10_001B1404 __attribute__((sda));

typedef struct { int idx; u8 pad[0x28]; int f2C; } G221CD0;
extern G221CD0 D_L10_00221CD0;
extern u8 *D_001B2614;
extern void func_PAL_L05_0037D9D0(void *, int);
extern void func_L05_0037CEE0(void *, void *, f32);
extern void func_L05_0037D608(void *, void *, f32);
extern void func_L10_00419188(void *);
extern void *func_L05_00379ED0(int);
extern int func_L10_0037D200(void *);
extern void func_PAL_L10_00429620(void *, int);
extern int func_L05_0037B3A0(void *);
extern void func_0027D330(int);
extern void func_L10_00423500(void *);

/* func_PAL_L10_00429880, the PAL copy of func_L10_00424028: the same C, where the first call
   also releases the D_L10_001B1400/1404 objects, the timer restarts at 8 instead of 10, and
   func_002AD7B8(12) also runs right after that restart.
   First call: resets the D_L10_001B13A4 block, marks every class-0xF85 moby, spawns 75
   objects and the effect box. Then, until the 0xF85 moby reports done, each timer expiry
   either closes the D_L10_001B1444 sequence (with D_L10_001B1390 raised around the
   func_0029B3E0 call, which returns an int) or restarts state 0 through func_PAL_L10_00429620. */
void func_PAL_L10_00429880(char *object)
{
    char **all;
    int result;
    char *st = *(char **)(object + 0x68);
    char *p;
    int i;
    if (!D_L10_001B13A4) {
        typedef int Quad __attribute__((mode(TI)));
        union { Quad q; float f[4]; } av, bv;
        D_L10_00221CFC = 0;
        D_L10_001B13A4 = 1;
        D_L10_001B13F8 = 0;
        D_L10_001B13FC = 0;
        func_002B7320();
        func_L05_0037B210();
        func_L05_00379F18(0);
        all = func_L05_00379EB8();
        result = func_L00_004272A0();
        for (i = 0; i < result; i++) {
            if (*(short *)(all[i] + 0xAA) == 0xF85) func_PAL_L05_0037D9D0(all[i], 1);
        }
        func_L10_00425798();
        func_L10_00425410(75,16);
        av.q = 0; bv.q = 0;
        av.f[0] = 469.63f; av.f[1] = 407.93f; av.f[2] = 502.79f;
        bv.f[0] = 476.13f; bv.f[1] = 415.41f; bv.f[2] = 502.79f;
        func_PAL_L10_003A0590(&av,&bv,1,2000000,0x7F7F7F,0xFF1010,70,70,0.5f,0.2f,0.402f,1.12225f);
        if (D_L10_001B1400) {
            func_0029F338(D_L10_001B1400);
            D_L10_001B1400 = 0;
        }
        if (D_L10_001B1404) {
            func_0029F338(D_L10_001B1404);
            D_L10_001B1404 = 0;
        }
    }
    p = func_L05_00379ED0(0xF85);
    result = p ? func_L10_0037D200(p) : 0;
    if (!result) {
        func_L05_0037B210();
        if (D_L10_001B1444) {
            if (func_00282948(st + 0x58)) {
                *(int *)(st + 0x58) = 8;
                func_002AD7B8(12);
                D_L10_001B1390++;
                func_L10_00425888();
                func_0029B3E0(0,-1);
                D_L10_001B1390--;
                func_L00_003294F0(D_L10_001B251C + *(int *)(st + 0x2C) * 256,1);
                D_L10_001B1424 = 0;
                D_L10_001B1444 = 0;
                func_L05_00379F48(1);
                func_002AD7B8(12);
            }
        } else if (func_00282948(st + 0x58)) {
            func_PAL_L10_00429620(object,0);
            D_L10_001B13F8 = 0;
            D_L10_001B13FC = 0;
        }
    }
}

/* func_PAL_L10_00429B20, the PAL copy of func_L10_00424290: the same C, where the first call
   also releases the D_L10_001B1400/1404 objects and func_0027D330 takes 0x19 instead of 0x1E. */
void func_PAL_L10_00429B20(u8 *a0) {
    u8 **p;
    int n;
    int i;
    u8 *o;
    void *v;
    int r;

    if (D_L10_001B13A4 == 0) {
        D_L10_001B13A4 = 1;
        D_L10_00221CD0.f2C = 0;
        func_002B7320();
        func_L05_0037B210();
        func_L05_00379F18(0);
        p = func_L05_00379EB8();
        n = func_L00_004272A0();
        for (i = 0; i < n; i++) {
            o = p[i];
            switch (*(short *)(o + 0xAA)) {
            case 0xCBE:
                func_PAL_L05_0037D9D0(o, 1);
                break;
            case 0xF93:
                func_PAL_L05_0037D9D0(o, 1);
                func_L05_0037CEE0(p[i], D_001B2614 + D_L10_00221CD0.idx * 128 + 0x30, 64.0f);
                func_L05_0037D608(p[i], D_001B2614 + D_L10_00221CD0.idx * 128 + 0x30, 64.0f);
                func_L10_00419188(p[i]);
                break;
            }
        }
        func_L10_00425798();
        func_L10_00425410(0x2D, 12);
        if (D_L10_001B1400) {
            func_0029F338(D_L10_001B1400);
            D_L10_001B1400 = 0;
        }
        if (D_L10_001B1404) {
            func_0029F338(D_L10_001B1404);
            D_L10_001B1404 = 0;
        }
    }
    v = func_L05_00379ED0(0xF93);
    r = v ? func_L10_0037D200(v) : 0;
    if (r == 0) {
        func_PAL_L10_00429620(a0, 1);
    }
    if (func_L05_0037B3A0(func_L05_00379ED0(0xCBE)) == 0) {
        func_0027D330(0x19);
        func_L05_00379F48(0);
        func_L10_00423500(a0);
    }
}

/* func_PAL_L10_00429D08, the PAL copy of func_L10_00424448: the same C, where the first call
   also releases the D_L10_001B1400/1404 objects. */
void func_PAL_L10_00429D08(void *object)
{
    unsigned char **entries;
    int i, count;

    if (!D_L10_001B13A4) {
        D_L10_00221CFC = 0;
        D_L10_001B13A4 = 1;
        func_002B7320();
        func_L05_0037B210();
        func_L05_00379F18(0);
        entries = func_L05_00379EB8();
        count = func_L00_004272A0();
        for (i = 0; i < count; i++) {
            if (*(short *)(entries[i] + 0xAA) == 0xF8E)
                func_PAL_L05_0037D9D0(entries[i], 1);
        }
        func_L10_00425798();
        func_L10_00425410(0x32, 0xC);
        if (D_L10_001B1400) {
            func_0029F338(D_L10_001B1400);
            D_L10_001B1400 = 0;
        }
        if (D_L10_001B1404) {
            func_0029F338(D_L10_001B1404);
            D_L10_001B1404 = 0;
        }
    }
    if (!func_L05_0037B3A0(func_L05_00379ED0(0xF8E)))
        func_PAL_L10_00429620(object, 2);
}

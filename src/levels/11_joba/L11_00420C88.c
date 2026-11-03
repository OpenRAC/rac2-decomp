#include "include_asm.h"

typedef signed char s8;
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef signed int s32;
typedef float f32;

INCLUDE_ASM("asm/levels", func_L11_00420C88);

extern void func_00282CF0(f32 *, f32 *, f32 *);
extern f32 func_00282DF0(f32 *);
extern void func_00282F20(f32 *, f32 *, f32);
extern void func_00282CC0(f32 *, f32 *, f32 *);
extern f32 func_00283C80(f32, f32);
extern int func_002A7EA0(char *, char *, char *, f32, f32, f32, f32, int);
extern f32 func_002AA2E8(f32 *, f32, f32);
extern void func_002AA548(f32 *, char *, f32, f32, f32, f32);
extern void func_002AAA00(char *, f32, f32, f32, f32, char *, int);
extern int func_L02_0032E998(char *, int, f32 *, char *, int, char *, char *, f32, f32);

/* Turns the object toward the point the caller names: it measures the angle between the
   object's own direction and that point, keeps the two angles it stores in its state, and
   reports whether the state changed. */
int func_L11_00425788(char *object, char *point, f32 value, f32 rate, f32 limit, f32 extra)
{
    char *st = *(char **)(object + 0x68);
    f32 v[4];
    f32 w[4];
    f32 x[4];
    f32 d = 0.0f;
    f32 out;
    f32 len;
    f32 t;
    int ret = 0;

    func_00282CF0(v, (f32 *)point, (f32 *)(object + 0x10));
    v[2] = 0.0f;
    len = func_00282DF0(v);
    t = rate * 0.0008333333535119891f;
    if (limit < len) {
        int c = *(int *)(st + 0x520);

        out = 0.0f;
        func_L02_0032E998(object + 0x10, (int)point, &out, st + 0x320, c, st + 0x530,
                          st + 0x534, extra, 0.4f);
        func_002AAA00(object + 0xF8, out, 0.006981317885220051f,
                      0.0034906589426100254f, 0.20943954586982727f, st + 0x27C, 0);
        if (func_00283C80(*(f32 *)(object + 0xF8), out) < 0.52359885f) {
            func_002AA548(&d, st + 0x538, len, t, t, rate * 0.01666666753590107f);
        } else {
            *(f32 *)(st + 0x538) = 0.0f;
        }
    } else {
        func_002AAA00(object + 0xF8, value, 0.006981317885220051f, 0.2f,
                      0.20943954586982727f, st + 0x27C, 0);
        func_002AA2E8((f32 *)(st + 0x538), 0.0f, t);
        if (*(f32 *)(st + 0x538) == 0.0f) {
            if (func_00283C80(*(f32 *)(object + 0xF8), value) < 0.0872664749622345f) {
                *(f32 *)(st + 0x27C) = 0.0f;
                ret = 1;
            }
        }
    }
    func_00282F20(w, (f32 *)(object + 0xC0), *(f32 *)(st + 0x538));
    func_00282CC0(x, w, (f32 *)(object + 0x10));
    if (func_002A7EA0(object, object + 0x10, (char *)x, 0.75f, 0.75f, 0.4f,
                     0.52359885f, 0) == 0) {
        *(int *)(st + 0x53C) = *(int *)(st + 0x53C) + 1;
    }
    /* The counter at +0x53C wraps at 0x1E, and the object then reports the change. */
    if (*(int *)(st + 0x53C) < 0x1E) {
        goto done;
    }
    *(int *)(st + 0x53C) = 0;
    ret = 1;
done:
    return ret;
}

extern void func_003315A0(char *object, char *p);
extern void func_00300180(char *p);
extern void func_003357E0(char *object, char *p, int kind, float f12, float f13);
extern void func_00338398(char *object, char *p, int kind, int a3, float f12);

/* re-arms the object's two guard nodes and restarts its measurement window */
void func_L11_00425A50(char *object)
{
    char *p = *(char **)(object + 0x68);

    func_003315A0(object, p + 0x50);
    func_00300180(p + 0x260);
    func_00300180(p + 0x26);
    if (*(u16 *)(object + 0x96) <= 0xFFFE)
        *(u16 *)(object + 0x96) = *(u16 *)(object + 0x96) + 1;
    func_003357E0(object, p + 0x2A0, 4, 0.03f, 0.3f);
    func_00338398(object, p + 0x2A0, 4, 1, 3.5f);
}

extern s16 *D_L11_001FC420[];
extern int D_L11_001B359C __attribute__((sda));

/* Walks the object's group list and, for every live member of class 0xCF5 or 0xCF6,
   marks it (0x266 = 1) and counts the visit at 0x560; class 0xCF5 members also count
   at 0x584 while the object's own state value at +0x20 is at most zero. */
void func_L11_00425AF8(char *object)
{
    s16 *list;
    s16 *p;
    char *base;
    char *o;
    char *vars;

    if (((u8 *)object)[0x21] == 0xFF) {
        return;
    }
    list = D_L11_001FC420[((u8 *)object)[0x21]];
    object = *(char **)(object + 0x68);
    if (list == 0) {
        return;
    }
    base = (char *)D_L11_001B359C;
    p = list;
    do {
        o = base + ((*(u16 *)p & 0x7FFF) << 8);
        if (((s8 *)o)[0x20] >= 0 && *(s16 *)(o + 0xAA) == 0xCF5) {
            vars = *(char **)(o + 0x68);
            *(u16 *)(vars + 0x266) = 1;
            *(int *)(vars + 0x560) += 1;
            if (*(f32 *)(object + 0x20) <= 0.0f) {
                *(int *)(vars + 0x584) += 1;
            }
        }
        if (((s8 *)o)[0x20] >= 0 && *(s16 *)(o + 0xAA) == 0xCF6) {
            vars = *(char **)(o + 0x68);
            *(u16 *)(vars + 0x266) = 1;
            *(int *)(vars + 0x560) += 1;
        }
    } while (*p++ >= 0);
}

extern char *func_0032F000(char *p, int a1, int a2);

/* ticks the object's clock down by the rate the linked node states */
int func_L11_00425EC0(char *object)
{
    char *p = *(char **)(object + 0x68);
    char *r = func_0032F000(*(char **)(p + 0x280), 0x10000, 0);

    if (r != 0) {
        *(float *)(p + 0x20) = *(float *)(p + 0x20) - *(float *)(r + 0x2C);
        return 1;
    }
    return 0;
}

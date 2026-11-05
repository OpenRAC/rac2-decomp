#include "common.h"
#include "include_asm.h"

extern void func_002AFFD8(void *, void *, int);
extern char *func_0029EFD0(int);
extern void func_00282F20(float *, float *, float);
extern void func_00282DD8(float *, float *, float *);

/* func_L23_0041E418 is defined in L23_0041E418-g8.c (this unit has no $gp access for it). */

/* func_L23_0041E5B0 is defined in its dedicated source unit. */

char *func_L23_00422540(char *pos, char *dir, float *damage) {
    char axis[16];
    char scaled[16];
    char *obj;
    char *state;
    func_002AFFD8(pos, axis, 1);
    obj = func_0029EFD0(0x118E);
    if (obj) {
        state = *(char **)(obj + 0x68);
        *(float *)(state + 0x1C) = *damage;
        *(int *)(state + 0x10) = 0x3C;
        *(u8 *)(obj + 0x30) = 0xFF;
        *(u16 *)(obj + 0x32) = 0xFF;
        *(u8 *)(obj + 0x20) = 0;
        qcopy(obj + 0x10, pos);
        qcopy(state, dir);
        *(int *)(state + 0x18) = 0;
        *(int *)(state + 0x14) = 0;
        func_00282F20((float *)scaled, (float *)dir, 1.0f);
        qcopy(obj + 0xC0, scaled);
        func_00282DD8((float *)(obj + 0xD0), (float *)(obj + 0xC0), (float *)axis);
        func_00282F20((float *)(obj + 0xD0), (float *)(obj + 0xD0), 1.0f);
        func_00282DD8((float *)(obj + 0xE0), (float *)(obj + 0xD0), (float *)(obj + 0xC0));
        *(float *)(obj + 0xCC) = *(float *)(obj + 0xDC) = *(float *)(obj + 0xEC) = 0.0f;
    }
    return obj;
}


/* func_L23_00422668 is matched in L23_00422668.c (built with -frac2-qcopy -frac2-no-annulled-wide-stores). */

/* func_L23_00422798 is matched in L23_00422798-g8.c (built with -frac2-zero-ti-por). */

/* func_L23_00422A30 is defined in L23_00422A30-g8.c. */

/* func_L23_00422E08 is defined in L23_00422E08-g8.c. */


/* func_L23_00423380 is defined in L23_0041E418-g8.c (this unit has no $gp access for it). */

/* func_L23_004234C0 is defined in L23_0041E418-g8.c (this unit has no $gp access for it). */

/* func_L23_004236B8 is matched in L23_004236B8-g8.c (built with -ffast-math). */

/* func_L23_00425568 is matched in L23_00425568.c (built with -frac2-qcopy). */

/* func_L23_004256F0 is matched in L23_004256F0.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

/* func_L23_00425848 is matched in L23_00425848.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

/* func_L23_00425AF8 is defined in L23_00425AF8-g8.c. */

typedef int TI16 __attribute__((mode(TI)));

extern void func_00282CF0(float *, float *, float *);

extern void func_00282DD8(float *, float *, float *);

extern void func_00282F20(float *, float *, float);

extern int func_002A7820(int, int);

extern float func_00283C28(float);

extern float func_00283198(float);

extern void func_00282D30(float *, float *, float);

extern void func_00282CC0(float *, float *, float *);

extern float D_L23_001BA640[];

/* builds two vectors from the sources, rotates one by the measured angle and writes the result */
void func_L23_004260F0(u8 *obj, float *dst, TI16 *src1, TI16 *src2, float scale) {
    TI16 loc[6];
    TI16 va;
    TI16 vb;
    u8 *o68;
    s16 x;
    s32 t;
    float f;
    float h;

    va = *src2;
    vb = *src1;
    loc[1] = va;
    loc[0] = vb;
    o68 = *(u8 **)(obj + 0x68);
    func_00282CF0((float *)&loc[2], (float *)&loc[0], (float *)&loc[1]);
    func_00282CF0((float *)&loc[3], (float *)&loc[0], D_L23_001BA640);
    func_00282DD8((float *)&loc[4], (float *)&loc[3], (float *)&loc[2]);
    func_00282F20((float *)&loc[4], (float *)&loc[4], 1.0f);
    x = *(s16 *)(o68 + 0xC);
    t = func_002A7820(-x, x);
    t = (((s32)*(u16 *)(obj + 0x96) << *(s16 *)(o68 + 0xE)) + t) % 360 - 180;
    f = func_00283C28((float)t * 0.017453294f);
    h = func_00283198(f) * scale;
    func_00282D30((float *)&loc[5], (float *)&loc[4], h);
    func_00282CC0(dst, (float *)&loc[0], (float *)&loc[5]);
}

/* func_L23_00426248 is defined in L23_00426248-g8.c. */

/* func_L23_004265D0 is defined in L23_004265D0-g8.c. */
extern void func_L23_004277E8(u8 *);
extern void func_L23_004278B0(u8 *);

void func_L23_004277B8(u8 *arg0) {
    func_L23_004277E8(arg0);
    func_L23_004278B0(arg0);
}

/* func_L23_004277E8 is matched in L23_0041E418-g8.c */


/* increments the 16-bit counter at object + 0x96 while it stays below 0xFFFF */
void func_L23_004278B0(u8 *arg0) {
    u16 *counter = (u16 *)(arg0 + 0x96);
    u16 value = *counter;

    if (value <= 0xFFFE) {
        *counter = value + 1;
    }
}

/* func_L23_004278D8 is matched in L23_004278D8-g8.c (built with -g). */

/* func_L23_00427CE8 is matched in L23_00427CE8-g8.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

/* func_L23_00428490 is defined in L23_00428490-g8.c. */

/* func_L23_00428CF8 is matched in L23_00428CF8-g8.c (built with -frac2-qcopy -frac2-qcopy-barrier -frac2-no-annulled-wide-stores). */

/* func_L23_00429098 is defined in L23_00429098-g8.c. */

/* func_L23_00429430 is defined in its dedicated source unit. */


/* func_L23_00429DC8 is matched in L23_00429DC8-g8.c (built with -frac2-qcopy -frac2-qcopy-barrier -frac2-zero-ti-por). */

/* increments the 16-bit counter at object + 0x96 while it stays below 0xFFFF */
void func_L23_00429FF8(u8 *arg0) {
    u16 *counter = (u16 *)(arg0 + 0x96);
    u16 value = *counter;

    if (value <= 0xFFFE) {
        *counter = value + 1;
    }
}

/* func_L23_0042A018 is defined in L23_0042A018-g8.c. */

/* func_L23_0042A438 is defined in L23_0042A438-g8.c. */

/* func_L23_0042A8C0 is defined in L23_0042A8C0-g8.c. */

/* Defined in L23_0042AD10.c. */

/* increments the 16-bit counter at object + 0x96 while it stays below 0xFFFF */
void func_L23_0042AD90(u8 *arg0) {
    u16 *counter = (u16 *)(arg0 + 0x96);
    u16 value = *counter;

    if (value <= 0xFFFE) {
        *counter = value + 1;
    }
}

/* func_L23_0042ADB0 is defined in L23_0042ADB0-g8.c. */

extern void func_L00_004287E8(void);

extern void func_L00_00428CE0(s32);

/* prepares the shared object then hands it to the shared starter */
void func_L23_0043F930(s32 arg0) {
    func_L00_004287E8();
    func_L00_00428CE0(arg0);
}

/* func_L23_004402D8 is matched in L23_004402D8-g8.c (built with -g). */

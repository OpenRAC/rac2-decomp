#include "include_asm.h"
#include "common.h"

extern void func_L00_00325AE8(void *, void *, float, float);

extern void *D_L02_001B17E8 __attribute__((sda));

extern float D_L02_001B17E4 __attribute__((sda));

extern float D_L02_001B17E0 __attribute__((sda));

extern float D_L02_001B17EC __attribute__((sda));

extern char *D_L02_001B1190[1] __attribute__((sda));

extern float func_00283CE0(int);

extern int func_00283CF0(float);

extern int func_L02_003F9B70(int);

extern int func_00288D58(void);

extern unsigned char D_001395B8[0x100];

/* Runs the kind's placement helper with the kind's own angles. */
void func_L02_00402440(char *a0) {
    if (*(unsigned char *)(a0 + 0x20) == 3)
        func_L00_00325AE8(a0 + 0x10, D_L02_001B17E8, D_L02_001B17E4, D_L02_001B17E0);
    else if (*(unsigned char *)(a0 + 0x20) == 2)
        func_L00_00325AE8(a0 + 0x10, D_L02_001B17E8, D_L02_001B17EC, D_L02_001B17E0);
}

#ifndef RAC2_T_TI128_L02
#define RAC2_T_TI128_L02
typedef int TI128 __attribute__((mode(TI)));
#endif

extern float D_L02_001B0180 __attribute__((sda));

extern float D_L02_001B0188 __attribute__((sda));

extern int D_L02_001B0184 __attribute__((sda));

extern float D_L02_001B0178 __attribute__((sda));

extern float D_L02_001B017C __attribute__((sda));

extern char D_L02_001BA500[];

extern void func_00282D30(void *, void *, float);

extern void func_00282CC0(void *, void *, void *);

extern void func_00282CF0(void *, void *, void *);

extern void func_00282F20(void *, void *, float);

extern float func_00282DB0(void *, void *);

/* The second declaration of the kind's helper in this unit: it takes the packed
   word where the call above takes a pointer. */
extern void func_L00_00325AE8_1(void *, int, float, float);

/* The 24-bit mask is written as 0xFFFFFF: the assembler expands `li` for 0xFF0000
   into `lui $v0,0xFF` and `ori $v0,$v0,0xFFFF`, so the register holds 0xFFFFFFFF. */
void func_L02_003D28E0(void *a0)
{
    void *s1 = a0;
    void *s2 = (char *)s1 + 0xE0;
    TI128 v0;
    TI128 v1;
    float f2;
    int a2;
    int a3;

    FastVecScale(&v0, s2, D_L02_001B0180);
    FastVecAdd(&v0, &v0, (char *)s1 + 0x10);
    FastVecSub(&v1, D_L02_001BA500, (char *)s1 + 0x10);
    vec_scale_to_length(&v1, &v1, 1.0f);
    f2 = FastVecDot(&v1, s2);
    if (D_L02_001B0188 < f2) {
        a2 = D_L02_001B0184;
        f2 = f2 * f2;
        a3 = (int)(f2 * (float)(a2 >> 24));
        func_L00_00325AE8_1(&v0, (a2 & 0xFFFFFF) | (a3 << 24), D_L02_001B0178,
                            D_L02_001B017C);
    }
}

/* func_L02_004013C0 is defined in L02_004013C0-g8.c. */

/* The kind's table gives a count; the kind's own helper gives the kind's id. */

/* The byte table the count is read from, at its address in the boot's resident memory. */

/* Scales the kind's own angle at +0xC down by 0.3 once per count the kind's byte table
   gives, keeps it inside the kind's own range, scales it by ten when the global flag is
   set, and hands it to the angle setter. */
int func_L02_003FCDF8(int a0) {
    float f20;
    int i = 0;

    f20 = IntToFloat(*(int *)(D_L02_001B1190[a0] + 0xC));
    while (i < D_001395B8[func_L02_003F9B70(a0)]) {
        f20 *= 0.3f;
        i++;
    }
    {
        float f0 = (float)*(int *)(D_L02_001B1190[a0] + 0xC);

        if (f0 < f20)
            f20 = f0;
        else if (f20 < 500.0f)
            f20 = 500.0f;
    }
    if (func_00288D58() != 0)
        f20 *= 10.0f;
    return FloatToInt(f20);
}

/* Near miss: same body with the other entry parameter (draft beside this one). */
int func_L02_003FCF08(int a0) {
    float f20;
    int i = 0;

    f20 = IntToFloat(*(int *)(D_L02_001B1190[a0] + 0x10));
    while (i < D_001395B8[func_L02_003F9B70(a0)]) {
        f20 *= 0.33333f;
        i++;
    }
    {
        float f0 = (float)*(int *)(D_L02_001B1190[a0] + 0x10);

        if (f0 < f20)
            f20 = f0;
        else if (f20 < 5.0f)
            f20 = 5.0f;
    }
    return FloatToInt(f20) << 5;
}

extern void func_00282C98(void *);
extern void func_00282DD8(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00282F70(void *, void *, float);
extern int func_L02_0032EF10(void *, char *, char *, int, float);

/* The level's 0x80-byte placement records, whose direction sits at +0x30. */
extern char *D_L02_001B368C;

/* Aligns the actor with the record its state names: the -1 case builds a direction from the
   +0x1F0 axis and the +0x340 vector and picks the 1.5-scaled or negated one by the sign of the
   dot product; the other case uses the 0x80-byte record from the boot table. The shared tail
   copies the +0x340 vector to the stack and hands it to the level's nine-place routine. */
int func_L02_003CCFE8(char *a0, char *a1)
{
    char *st = *(char **)(a0 + 0x68);
    TI128 a, b, c, d, e;
    int ret;

    if (*(int *)(st + 0x334) == -1) {
        FastVecSub((float *)&a, (float *)(st + 0x1F0), (float *)(st + 0x340));
        func_00282C98(&b);
        FastVecCross(&c, &a, &b);
        vec_scale_to_length((char *)&c, (char *)&c, 1.5f);
        FastVecScale(&d, &c, -1.0f);
        FastVecSub((float *)&e, a0 + 0x10, (float *)(st + 0x340));
        if (FastVecDot(&e, &c) < 0.0f) {
            FastVecAdd(a1, &c, st + 0x340);
            ret = 1;
        } else {
            FastVecAdd(a1, &d, st + 0x340);
            ret = 0;
        }
    } else {
        FastVecSub((float *)&a, (float *)(st + 0x1F0),
                      (float *)(D_L02_001B368C + (*(int *)(st + 0x334) << 7) + 0x30));
        ret = 1;
        func_00282F70((char *)&a, (char *)&a,
                      FastVecLength(D_L02_001B368C + (*(int *)(st + 0x334) << 7)));
        FastVecAdd(a1, &a, D_L02_001B368C + (*(int *)(st + 0x334) << 7) + 0x30);
        FastVecSub((float *)&b, a1, a0 + 0x10);
        if (!(0.0f <= FastVecDot(&b, a0 + 0xD0)))
            ret = 0;
    }
    a = *(TI128 *)(st + 0x340);
    func_L02_0032EF10(&a, a1, a1, *(int *)(st + 0x318), *(float *)(st + 0x100));
    return ret;
}


extern char *D_L02_001B359C __attribute__((sda));

extern int D_001A79F0[] __attribute__((sda));
extern unsigned char D_0019B2E8[];
extern unsigned char D_001395B8[];
struct PortalPlayer {
    char pad0[0x80];
    float pos[4];
    char pad90[0x182];
    short state;
    char pad214[0x128];
    char *portal;
    int active;
    char pad344[0x21ac];
    unsigned char flag;
};
extern struct PortalPlayer D_00189E20;
extern unsigned char D_00189EA0[];
extern unsigned char D_001A7BC8[] __attribute__((sda));
extern unsigned int D_00138324 __attribute__((nosda));
extern unsigned char D_L02_001C0700[];
extern void func_002A7470(void *, int, int, int);
extern void func_002A7750(void *, int, int);
extern void func_L00_003294F0(void *, int);
extern void func_L00_003672F8(void);
extern void func_L02_00327350(int, int);
extern void func_002DF3F8(void *, void *);
extern void func_002AF0A8(int);
extern void func_002AFDD8(void *, void *, void *, int);
extern void func_002B0C28(int, int, int);
extern void func_00288CB0(int, int);
extern int func_00288AA0(void *, int);
extern int func_00288BE8(void *);
extern void func_L02_00404778(void);
extern void func_002F5CB8(void (*)(void), void *);
extern void func_002AD7B8(int);

void func_L02_00404410(char *obj) {
    char *d = *(char **)(obj + 0x68);
    float v[4];
    int dest;

    switch (*(unsigned char *)(obj + 0x20)) {
    case 0: {
        int zone;
        if (*(unsigned char *)(obj + 0x43) != 2) func_002A7470(obj, 2, 0, 1);
        func_002A7750(obj, 1, -1);
        *(unsigned char *)(obj + 0x30) = 255;
        if (D_001A79F0[0] == 26) *(short *)(obj + 0x32) = 255;
        qcopy(d + 0x20, obj + 0x10);
        qcopy(d + 0x30, obj + 0xf0);
        zone = D_001A79F0[0] << 4;
        *(short *)(d + 0x1e) = D_0019B2E8[*(unsigned char *)(obj + 0xb0) + zone] >> 7;
        if (D_0019B2E8[*(unsigned char *)(obj + 0xb0) + zone] & 0x80) {
            if (*(int *)(d + 4)) func_L00_003294F0(D_L02_001B359C + (*(int *)(d + 4) << 8), 1);
        }
        if (D_001A79F0[0] == 2 && D_001395B8[0x71] == 26) {
            func_L00_003672F8();
            D_001395B8[0x71] = 1;
            func_L02_00327350(*(int *)(d + 0x14), *(int *)(d + 0x10));
            func_002DF3F8(D_00189EA0, D_00189EA0 + 0x10);
            if (D_001A7BC8[4] && !D_001395B8[0xa5]) {
                D_001395B8[0xa5] = 1;
                func_002AF0A8(4);
            }
        }
    }
    case 1:
        if (D_00189E20.portal == obj && D_00189E20.active) {
            FastVecSub(v, D_00189E20.pos, obj + 0x10);
            func_002AFDD8(obj, v, v, 0);
            if (v[2] < -0.6f) {
                int currentLevel;
                currentLevel = D_001A79F0[0];
                D_00189E20.state = 2;
                dest = 2;
                if (currentLevel == 26) {
                    TryClaimNotice(8, 0x27b1, 1);
                } else {
                    TryClaimNotice(8, D_0019B2E8[*(unsigned char *)(obj + 0xb0) + (currentLevel << 4)] & 0x80 ? 0x27cd : 0x27b0, 1);
                    dest = 26;
                }
                if (D_00138324 & 0x10) {
                    func_002DF3F8(D_00189EA0, D_00189EA0 + 0x10);
                    func_00288CB0(dest, 1);
                    if (dest == 26) D_001395B8[1] = 1;
                }
            }
        }
        if (D_001A79F0[0] == 26 && (D_0019B2E8[0x1a0 + *(unsigned char *)(obj + 0xb0)] & 0x80)) {
            if (D_001A7BC8[4]) return;
            if (func_00288AA0(D_L02_001C0700, 0xa7)) {
                func_00288AA0(D_L02_001C0700, 4);
                func_00288AA0(D_L02_001C0700, 0xa8);
                func_00288BE8(D_L02_001C0700);
                func_002F5CB8(func_L02_00404778, obj);
                D_00189E20.flag = 0;
                func_002AD7B8(4);
                func_002A7750(obj, 3, -1);
            }
        }
        break;
    }
}

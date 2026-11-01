#include "common.h"

#define RAC2_T_OBJ_F7B2F1854

typedef struct {
    unsigned char pad[0x1FB0];
    float limit_x;
    float limit_y;
} Glob_199E20;

typedef struct {
    unsigned char pad[0x50];
    float f50;
    float f54;
} Obj_32FDD0;

typedef int TI128 __attribute__((mode(TI)));

typedef struct Rac2Native_81be3b52930eb806_FallbackInterleavedFloat4Layout {
    unsigned char unknown_00[8];
    float first_0;
    float second_0;
    float first_1;
    float second_1;
    float first_2;
    float second_2;
    float first_3;
    float second_3;
} Rac2Native_81be3b52930eb806_FallbackInterleavedFloat4Layout;

typedef struct Obj_F7b2f1854 {
    int *f0;
    int *f4;
    int *f8;
    int *f12;
    int *f16;
    int f20;
    int f24;
    int f28;
    int f32;
    int f36;
    int f40;
    int f44;
} Obj_F7b2f1854;

typedef struct {
    char reserved[0x30];
    void *table;
} Constructor_3361A8;

extern Glob_199E20 D_00189E20;

extern float D_001B284C __attribute__((sda));

extern float D_00189EA0[];

extern void F7242f0a4_FUN_00282D30(char *out, void *source, float value);

extern void F7242f0a4_FUN_00334730(char *buffer, int mode);

extern f32 func_002A78D8(f32 low, f32 high);
extern f32 D_001A8BD0[] __attribute__((sda));

typedef union { TI128 quad; float v[4]; } EffectVector;

extern unsigned char *D_001F2540[];                     /* the texture table */
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_002A77E0(int);
extern unsigned char *func_002C65A0(void *, void *, int, unsigned int, int, int, int, float, float, float, int);

typedef struct {
    TI128 position;
    int f10;
    int f14;
    int f18;
    int f1C;
    int f20;
} State_332440;

/* The EE assigns the integer and FP banks independently: this is func_002FED90(obj, src, x, y, z)
   with its FP arguments set up first, as retail does. */
extern int func_002FED90(void *obj, f32 x, f32 y, f32 z, void *src);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, f32);
extern void func_002AFFD8(void *, void *, int);
extern char *func_0029EFD0(int);

extern void F7242f0a4_FUN_00334710(int value, char *buffer);

extern void F7242f0a4_FUN_00282CC0(char *first, char *second, char *third);

extern float F7242f0a4_FUN_00282DB0(void *owner, char *buffer);

extern int F7242f0a4_D_001B53A0[];

extern s32 func_00283D38(s32, s32, f32);

extern int func_00335E20(unsigned char *field);

extern void func_00336ED0(int a, int b);

extern int *F7b2f1854_FUN_00336E40(int n);

extern int *F7b2f1854_FUN_00336DA8(int size, int *p);

extern void F7b2f1854_FUN_00335E68(Obj_F7b2f1854 *o, int v);

extern void F36efd143_FUN_00335FC8(char *a);

extern void *F36efd143_FUN_00336E40(char *a);

extern void *F36efd143_FUN_00336DA8(int size, void *b);

extern void F081de6c9_FUN_00335FC8(char *s, int a1, char *a2);

extern int F081de6c9_FUN_00336E40(int x);

extern int *F081de6c9_FUN_00336DA8(int n, int x);

extern int D_001B2860[] __attribute__((sda));

extern char D_001B0A88[];

extern void func_0026FEB8(void *);

extern unsigned short *D_001EE5A0[];

extern char *D_001B1B5C __attribute__((sda));

extern void func_002FDBD8(void *, void *, int, float);

extern char D_001B5200[];

extern void func_002704D0(void);

extern void func_00283410(void *, void *);

extern void func_00283678(void *, void *);

extern void func_00282F20(void *, void *, float);

extern void func_00282CC0(void *, void *, void *);

extern void func_002704D0(void);

extern char D_001AD9C8[] __attribute__((sda));

extern void func_00336DA0(void *);

extern void func_00115E38(char *, int, char *);

extern char D_001AD8B0[];

extern char D_001AD8C8[];

extern char D_001AD9A8[] __attribute__((sda));

extern void func_00335870(void *, int);

extern int D_001B23A0 __attribute__((sda));

extern char D_001ADA78[] __attribute__((sda));

extern char D_001ADA78[] __attribute__((sda));

extern void func_00336DA0(void *);

extern void *func_00335FB0(void *);

extern char D_001ADA58[] __attribute__((sda));

extern int func_00336D50(int, int);

extern char D_001AD9F8[] __attribute__((sda));

extern char D_001ADA38[] __attribute__((sda));

/* Measured partial layouts; original type and game roles are unknown. */

/* func_0034CA68: owner ABI/declaration review retained. */

#ifndef RAC2_T_OBJ_F7B2F1854
#endif

/* func_0032EB28 uses small data in 0032EB28-update-g8.c. */

INCLUDE_ASM("asm/game", func_0032F3D0);


INCLUDE_ASM("asm/game", func_0032F598);

INCLUDE_ASM("asm/game", func_0032FDC0);


/* func_0032FEA8 uses small data in 0032EB28-g8.c. */


/* func_0032FFD8 is defined in its own sibling unit. */

INCLUDE_ASM("asm/game", func_00330150);

/* func_003304D8 is defined in 0032EB28-ground-g8.c. */


/* func_00330BC0 uses small data in 0032EB28-g8.c. */

/* func_00330CA0 is in 0032EB28-damage-g8.c. */


/* func_00330E48 is in 0032EB28-g8.c. */

/* func_00330EC0 is in 0032EB28-ring-g8.c. */

/* func_00331238 is in 0032EB28-spark.c. */


void func_003313E0(TI128 *a0, void *dir)
{
    EffectVector base;
    float vel[4];
    float pos[3];
    float size = 84000.0f;
    int i;
    int rnd;
    unsigned char *p;

    qcopy(&base, a0);
    func_00282D30(vel, dir, 0.5f);
    func_00282CC0(&base, &base, vel);
    i = 8;
    do {
        i--;
        pos[0] = base.v[0] + func_002A78D8(0.0f, 0.1f);
        pos[1] = base.v[1] + func_002A78D8(0.0f, 0.1f);
        pos[2] = base.v[2] + func_002A78D8(0.0f, 0.1f);
        rnd = func_002A77E0(0xFF);
        p = func_002C65A0(pos, D_001A8BD0, 10, 0x407FFF, rnd, 0x7F, 0, size, size, 0.0f, 1);
        if (p != 0)
            p[2] = D_001F2540[92][5];
        p = func_002C65A0(pos, D_001A8BD0, 10, 0x406080, rnd, 0x7F, 0, size, size, 0.0f, 1);
        if (p != 0)
            p[2] = D_001F2540[53][0];
    } while (i >= 0);
}

extern s32 func_00283CF0(f32 value);
extern u8 *func_002C16C0(f32 *pos, f32 *sym, s32 a2, s32 a3, u32 color, s32 alpha, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16);
extern u8 *D_001F26B0;
void func_00331580(f32 *pos, f32 scale)
{
    f32 v[3];
    f32 size = scale * 6300.0f;
    u8 *effect;
    s32 i;
    for (i = 1; i >= 0; i--) {
    v[0] = pos[0] + func_002A78D8(0.0f, 0.04f);
    v[1] = pos[1] + func_002A78D8(0.0f, 0.04f);
    v[2] = pos[2] + func_002A78D8(0.0f, 0.04f);
    func_002C16C0(v, D_001A8BD0, 15, 0x5F, 0x7F7F7F, func_00283CF0(func_002A78D8(1.0f, 3.0f)), size, 500.0f, 1.0f, 0.0f, 0.0f);
    }
    effect = func_002C16C0(v, D_001A8BD0, 15, 0x7F, 0x407FFF, func_00283CF0(func_002A78D8(1.0f, -1.0f)), size * 0.8f, 500.0f, 1.0f, 0.0f, 0.0f);
    if (effect != 0) {
        effect[2] = D_001F26B0[5];
    }
}

/* func_00331718 uses small data in 0032EB28-g8.c. */



void func_003323F0(int a0) {
    int i;

    for (i = 0; i < 16; i++) {
        if (D_001B2860[i] == a0) {
            D_001B2860[i] = 0;
            return;
        }
    }
    func_0026FEB8(D_001B0A88);
}

char *func_00332440(void *a0, void *a1, void *a2)
{
    TI128 localA;
    TI128 localB;
    char *object;
    State_332440 *state;
    int result;

    func_002AFFD8(a1, &localA, 1);
    object = func_0029EFD0(0xEAA);
    if (object != 0) {
        state = *(State_332440 **)(object + 0x68);
        state->f10 = 0x50;
        *(unsigned char *)(object + 0x30) = 0xFF;
        *(short *)(object + 0x32) = 0xFF;
        *(unsigned char *)(object + 0x20) = 0;
        qcopy(object + 0x10, a1);
        qcopy(state, a2);
        state->f18 = 0;
        state->f14 = 0;
        func_00282F20(&localB, a2, 1.0f);
        qcopy(object + 0xC0, &localB);
        func_00282DD8(object + 0xD0, object + 0xC0, &localA);
        func_00282F20(object + 0xD0, object + 0xD0, 1.0f);
        func_00282DD8(object + 0xE0, object + 0xD0, object + 0xC0);
        *(float *)(object + 0xCC) = *(float *)(object + 0xDC) = *(float *)(object + 0xEC) = 0.0f;
        result = func_002FED90(object, 1.0f, 1.0f, 1.0f, 0);
        state->f1C = result;
        state->f20 = (int)a0;
    }
    return object;
}



INCLUDE_ASM("asm/game", func_00333048);

INCLUDE_ASM("asm/game", func_003334B0);

/* func_00333AF8 is in 0032EB28-beam.c. */


void func_00334050(int index, int value)
{
    unsigned short *list = D_001EE5A0[index];
    if (list != 0) {
        unsigned short *entry = list;
        int key;
        do {
            char *object = (char *)(((*entry & 0x7FFF) << 8) + (unsigned int)D_001B1B5C);
            *(unsigned char *)(*(char **)(object + 0x68) + 0x15) = value;
            key = *(short *)entry++;
        } while (key >= 0);
    }
}

void func_003340A8(char *object)
{
    char *data = *(char **)(object + 0x68);
    unsigned int mode = *(unsigned char *)(object + 0x20);
    if (mode - 2 < 2 && *(int *)(data + 0x40) != 0)
        func_002FDBD8(data + 0x10, data + 0x20, 0, 1.0f);
}


/* The table func_00334100 walks: 0x30-byte entries with the searched id at +0x18.
   Its address differs from level to level, so the symbol carries no address. */
typedef struct {
    unsigned char pad_34100[0x18];
    int id_34100;
    unsigned char pad2_34100[0x14];
} Entry_34100;

extern Entry_34100 ref_L00_00334100_00[30];

s32 func_00334100(s32 a0)
{
    s32 i;
    s32 r;

    r = -1;
    for (i = 0; i < 30; i++) {
        if (ref_L00_00334100_00[i].id_34100 == a0) {
            r = i;
            break;
        }
    }
    return r;
}

INCLUDE_ASM("asm/game", func_00334160);

INCLUDE_ASM("asm/game", func_00334550);

/* func_00334710 is matched in 00334710-rc2.c. */




typedef int L_34730TI __attribute__((mode(TI)));
typedef union { unsigned char b[0x2600]; short h[0x1300]; int i[0x980]; float f[0x980]; } L_34730Hero;
extern L_34730TI func_00334710(int, L_34730TI *);
extern int func_002761F8(void *, void *, int, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern char D_001B53A0[];
extern float D_001BAFA0[];

int func_00334730(float *out, int flag)
{
    float base[4] __attribute__((aligned(16)));
    float near[4] __attribute__((aligned(16)));
    float far[4] __attribute__((aligned(16)));
    float ofs[4] __attribute__((aligned(16)));
    L_34730Hero *hero = (L_34730Hero *)&D_00189E20;
    float f;
    char *cam = D_001B53A0;

    if (hero->h[0x34C / 2] == 0) {
        func_00334710(((int *)cam)[-4], (L_34730TI *)out);
        return 1;
    }
    func_00334710(((int *)cam)[-4], (L_34730TI *)base);
    f = hero->f[0x31C / 4];
    if (f >= 30.0f || flag == 0) {
        func_00282D30(ofs, cam + 0x30, 0.2f);
        func_00282CC0(near, base, ofs);
        func_00282D30(ofs, cam + 0x30, -30.0f);
        func_00282CC0(far, base, ofs);
        if (func_002761F8(near, far, 0x12, (void *)hero->i[0x2290 / 4], 0) != 0) {
            qcopy(out, D_001BAFA0);
            return 0;
        }
        qcopy(out, base);
        return -1;
    }
    func_00282D30(near, cam + 0x30, -f);
    func_00282CC0(out, base, near);
    return 1;
}



void func_003349E8(void *owner, int flag, float value)
{
    char buffer[32];
    int *root = F7242f0a4_D_001B53A0;

    F7242f0a4_FUN_00282D30(buffer, root + 8, value);
    if (flag)
        F7242f0a4_FUN_00334730(buffer + 16, 1);
    else
        F7242f0a4_FUN_00334710(root[-4], buffer + 16);
    F7242f0a4_FUN_00282CC0(buffer, buffer, buffer + 16);
    F7242f0a4_FUN_00282D30(owner, root + 12, F7242f0a4_FUN_00282DB0(root + 12, buffer));
}


typedef int TI __attribute__((mode(TI)));
extern void *D_0026E810[7];
extern TI func_00334710(int, TI *);
extern void func_00282CC0(void *, void *, void *);

int func_003351B0(char *self, void *src, void *dst, int mode)
{
    static void *arms[7] = {&&transformed, &&direct, &&zero, &&zero, &&zero, &&zero, &&zero};
    TI local;
    int ret = 1;
    char *vector = *(char **)(self + 0x70) + 0x60;
    if ((unsigned int)(mode - 1) >= 7) goto direct;
    goto *D_0026E810[mode - 1];
zero:
    func_00282CC0(dst, src, vector);
    ret = 0;
    goto done;
transformed:
    func_00334710((int)self, &local);
    func_00282CC0(dst, src, &local);
    goto done;
direct:
    func_00282CC0(dst, src, vector);
done:
    return ret;
}

INCLUDE_ASM("asm/game", func_00335270);

/* func_00335370 is defined in 00335370-copy.c. */

/* func_003353C8 uses the quadword-copy profile in 0032EB28-qcopy.c. */



/* Moves camera 5 to a new position/rotation; mode 3 starts a transition back from the
   previous pose, modes 2 and 3 store the transition duration. */
/* func_00335438 is defined in its own sibling unit. */

void func_003355A8(int mode)
{
    struct { float scaled[4]; float negative[4]; float matrix[16]; } work;
    char *state = D_001B5200;
    char *camera = *(char **)(state + 0x190);
    func_002704D0();
    if (mode == 0) {
        char *position = camera + 0x30;
        func_00283410(work.matrix, D_00189EA0 + 4);
        func_00283678(camera, work.matrix);
        func_00282F20(work.negative, work.matrix, -1.0f);
        func_00282F20(work.scaled, work.matrix + 8, 1.2f);
        func_00282CC0(position, D_00189EA0, work.scaled);
        func_00282CC0(position, position, work.negative);
        *(short *)(*(char **)(state + 0x190) + 0x8A) = 1;
    } else if (mode == 2) {
        state[0x293] = 0;
        *(short *)(camera + 0x7E) = 2;
        *(float *)(state + 0x2B4) = 0.018f;
        *(float *)(state + 0x2A8) = 0.018f;
    } else if (mode == 1) {
        *(short *)(camera + 0x7E) = 3;
    } else if (mode == 4) {
        state[0x293] = 0;
        *(short *)(camera + 0x7E) = 5;
        *(float *)(state + 0x2B4) = 0.018f;
        *(float *)(state + 0x2A8) = 0.018f;
    }
}

INCLUDE_ASM("asm/game", func_003356E8);

void func_00335840(void) {
    func_002704D0();
}


void func_00335870(void *object, int flags) {
    *(void **)((char *)object + 4) = D_001AD9C8;
    if (flags & 1)
        func_00336DA0(object);
}

void func_003358A0(void *unused, char *out, float factor) {
    if (out == 0)
        func_00115E38(D_001AD8B0, 61, D_001AD8C8);
    *(float *)(out + 0x0) = factor;
    *(float *)(out + 0x4) = factor * 0.5f;
    *(float *)(out + 0x8) = 1.0f - factor;
    *(float *)(out + 0xC) = (1.0f - factor) * 0.5f;
}


/* func_00335960 is defined in its own sibling unit. */

void *func_00335AC8(void *object) {
    *(void **)object = D_001AD9A8;
    return object;
}

void func_00335AE0(void *object, int flags) {
    *(void **)object = D_001AD9A8;
    if (flags & 1)
        func_00336DA0(object);
}

/* Interpolate four scalar float components from separate input arrays using (1.0f - factor) * first + factor * second, writing each component to the destination. */
void func_00335B10(float factor, void *context,
                                   float *destination,
                                   const float *first, const float *second)
{
    float complement = 1.0f - factor;
    destination[0] = complement * first[0] + factor * second[0];
    destination[1] = complement * first[1] + factor * second[1];
    destination[2] = complement * first[2] + factor * second[2];
    destination[3] = complement * first[3] + factor * second[3];
}

/* calls one four-argument helper four times, left[i] and right[i] with the float scale, storing each result into dst[i]; the first pointer parameter is unused. */
void func_00335B80(s32 *unused, s32 *dst, s32 *left, s32 *right, f32 scale) {
    dst[0] = func_00283D38(left[0], right[0], scale);
    dst[1] = func_00283D38(left[1], right[1], scale);
    dst[2] = func_00283D38(left[2], right[2], scale);
    dst[3] = func_00283D38(left[3], right[3], scale);
}



/* Interpolate four scalar float components from interleaved endpoint pairs at source offsets 0x08 through 0x24 using (1.0f - factor) * first + factor * second, writing each component to the destination. */
void func_00335CC0(float factor,
                                     const Rac2Native_81be3b52930eb806_FallbackInterleavedFloat4Layout *source,
                                     float *destination)
{
    float complement = 1.0f - factor;
    destination[0] = complement * source->first_0 + factor * source->second_0;
    destination[1] = complement * source->first_1 + factor * source->second_1;
    destination[2] = complement * source->first_2 + factor * source->second_2;
    destination[3] = complement * source->first_3 + factor * source->second_3;
}


void func_00335D60(void *object, int flags) {
    func_00335870(object, flags);
}

/* func_00335DC0 uses small data in 0032EB28-g8.c. */

int func_00335E08(void) {
    return D_001B23A0;
}

/* Measured target: byte-identical across all 27 levels. */
s32 func_00335E10(u8 *a0) { return *(s32 *)(a0 + 0x0); }

/* Measured target: byte-identical across all 27 levels. */
s32 func_00335E18(u8 *a0) { return *(s32 *)(a0 + 0x4); }

/* Measured target: byte-identical across all 27 levels. */
s32 func_00335E20(u8 *a0) { return *(s32 *)(a0 + 0xc); }

void func_00335E38(u8 *a0,f32 f0,f32 f1,f32 f2,f32 f3) {
 (*(f32 **)a0)[0]=f0;(*(f32 **)a0)[1]=f1;
 (*(f32 **)a0)[2]=f2;(*(f32 **)a0)[3]=f3;
}


void func_00335E68(u8 *a0, s32 a1) {
 f32 *p=*(f32 **)(a0+0x10);
 *p=(a1!=0)?1.0f:0.0f;
}

s32 func_00335E88(u8 *a0) {
 return 0.0f<**(f32 **)(a0+0x10);
}

/* Compares the second argument with the word at offset 4 of the object; when they differ, and when the word at offset 44 is non-zero while the word at offset 24 is zero, it calls a two-argument helper with those two words, marks offset 24 with 1, and finally writes the second argument into offset 4. */
void func_00335EB0(char *a0, int a1)
{
    if (a1 != *(int *)(a0 + 4)) {
        if (*(int *)(a0 + 44) != 0 && *(int *)(a0 + 24) == 0) {
            func_00336ED0(*(int *)(a0 + 44), *(int *)(a0 + 4));
            *(int *)(a0 + 24) = 1;
        }
        *(int *)(a0 + 4) = a1;
    }
}


void func_00335F20(char *object, int value) {
    if (value != *(int *)(object + 0x10)) {
        if (*(int *)(object + 0x2C) != 0 && *(int *)(object + 0x24) == 0) {
            func_00336ED0(*(int *)(object + 0x2C), *(int *)(object + 0x10));
            *(int *)(object + 0x24) = 1;
        }
        *(int *)(object + 0x10) = value;
    }
}

void func_00335F88(u8 *a0,f32 f0,f32 f1,f32 f2,f32 f3) {
 (*(f32 **)(a0+4))[0]=f0;(*(f32 **)(a0+4))[1]=f1;
 (*(f32 **)(a0+4))[2]=f2;(*(f32 **)(a0+4))[3]=f3;
}

void *func_00335FB0(void *object) {
    *(void **)((char *)object + 0x30) = D_001ADA78;
    return object;
}

void func_00335FC8(Obj_F7b2f1854 *o, int a1, int count)
{
    int *p;
    int n;

    o->f44 = count;
    if (count != 0) {
        p = F7b2f1854_FUN_00336DA8(16, F7b2f1854_FUN_00336E40(count));
        n = o->f44;
        o->f0 = p;
        p[1] = 0;
        p[2] = 0;
        p[3] = 0;
        p[0] = 0;

        p = F7b2f1854_FUN_00336DA8(16, F7b2f1854_FUN_00336E40(n));
        n = o->f44;
        o->f8 = p;
        p[1] = 0;
        p[2] = 0;
        p[3] = 0;
        p[0] = 0;

        p = F7b2f1854_FUN_00336DA8(16, F7b2f1854_FUN_00336E40(n));
        n = o->f44;
        o->f4 = p;
        p[1] = 0;
        p[2] = 0;
        p[3] = 0;
        p[0] = 0;

        p = F7b2f1854_FUN_00336DA8(16, F7b2f1854_FUN_00336E40(n));
        n = o->f44;
        o->f12 = p;
        p[1] = 0;
        p[2] = 0;
        p[3] = 0;
        p[0] = 0;

        p = F7b2f1854_FUN_00336DA8(16, F7b2f1854_FUN_00336E40(n));
        o->f16 = p;
        p[1] = 0;
        p[2] = 0;
        p[3] = 0;
        p[0] = 0;
    }
    o->f40 = a1;
    o->f32 = 0;
    o->f20 = 0;
    o->f28 = 0;
    o->f24 = 0;
    o->f36 = 0;
    F7b2f1854_FUN_00335E68(o, 1);
}


void func_003360F8(char *object, int flags)
{
    *(char **)(object + 0x30) = D_001ADA78;
    if (*(int *)(object + 0x2C)) {
        if (*(int *)(object + 0x14) == 0)
            func_00336ED0(*(int *)(object + 0x2C), *(int *)object);
        if (*(int *)(object + 0x1C) == 0)
            func_00336ED0(*(int *)(object + 0x2C), *(int *)(object + 8));
        if (*(int *)(object + 0x18) == 0)
            func_00336ED0(*(int *)(object + 0x2C), *(int *)(object + 4));
        if (*(int *)(object + 0x20) == 0)
            func_00336ED0(*(int *)(object + 0x2C), *(int *)(object + 12));
    }
    if (flags & 1)
        func_00336DA0(object);
}

Constructor_3361A8 *func_003361A8(Constructor_3361A8 *object) {
    func_00335FB0(object);
    object->table = D_001ADA58;
    return object;
}

void func_003361E0(char *obj)
{
    int *p;
    int x;
    F36efd143_FUN_00335FC8(obj);
    if (*(int *)(obj + 44) != 0) {
        p = (int *)F36efd143_FUN_00336DA8(16, F36efd143_FUN_00336E40(*(int *)(obj + 44)));
        *(int *)(obj + 52) = (int)p;
        x = *(int *)(obj + 44);
        p[1] = 0; p[2] = 0; p[3] = 0; p[0] = 0;
        p = (int *)F36efd143_FUN_00336DA8(16, F36efd143_FUN_00336E40(x));
        *(int *)(obj + 56) = (int)p;
        {
            float *f = (float *)*(int *)(obj + 4);
            p[1] = 0;
            p[2] = 0;
            p[3] = 0;
            p[0] = 0;
            f[0] = 1.0f;
            *(float *)(*(int *)(obj + 4) + 4) = 1.0f;
            *(float *)(*(int *)(obj + 4) + 8) = 1.0f;
        }
    }
    *(int *)(obj + 68) = 0;
    *(int *)(obj + 72) = 0;
}



/* Measured target: byte-identical across all 27 levels. */
s32 func_00336318(u8 *a0) { return *(s32 *)(a0 + 0x38); }

void func_00336390(char *object, int a1, int a2) {
    *(int *)(object + 0x40) = func_00336D50(a1, a2);
}

void func_003363C0(u8 *a0, f32 a1) { f32 *p = *(f32 **)(a0 + 0x38); *p = a1; }

Constructor_3361A8 *func_003363D0(Constructor_3361A8 *object) {
    func_00335FB0(object);
    object->table = D_001AD9F8;
    return object;
}

void func_00336408(char *object, int a1, int a2, int a3, int a4) {
    func_00335FC8((Obj_F7b2f1854 *)object, a3, a4);
    *(int *)(object + 0x3C) = a1;
    *(int *)(object + 0x34) = a2;
    *(int *)(object + 0x40) = 100;
    *(int *)(object + 0x44) = 0x80000000;
}


/* lot12 -- measured bodies with sizes recorded in the catalogue. */
void func_00336498(u8 *a0, s32 a1, s32 a2) {
    *(s32 *)*(u8 **)(a0 + 0xc) = a1;
    *(s32 *)(*(u8 **)(a0 + 0xc) + 0x4) = a2;
}

void func_003364B0(u8 *a0, s32 a1, s32 a2) {
    *(s32 *)(*(u8 **)(a0 + 0xc) + 0x8) = a1;
    *(s32 *)(*(u8 **)(a0 + 0xc) + 0xc) = a2;
}

void func_003364C8(u8 *a0, s32 a1, s32 a2) {
    u8 *o = a0;
    *(u32 *)*(u8 **)(o + 0xC) = (*(u32 *)*(u8 **)(o + 0xC) & 0x00FFFFFF) | (u32)(a1 << 24);
    *((u32 *)*(u8 **)(o + 0xC) + 1) = (*((u32 *)*(u8 **)(o + 0xC) + 1) & 0x00FFFFFF) | (u32)(a2 << 24);
}

void func_00336508(u8 *a0, s32 a1, s32 a2) {
    u8 *o = a0;
    *((u32 *)*(u8 **)(o + 0xC) + 2) = (*((u32 *)*(u8 **)(o + 0xC) + 2) & 0x00FFFFFF) | (u32)(a1 << 24);
    *((u32 *)*(u8 **)(o + 0xC) + 3) = (*((u32 *)*(u8 **)(o + 0xC) + 3) & 0x00FFFFFF) | (u32)(a2 << 24);
}

/* func_00336548 is defined in 0032EB28-math-g8.c. */

Constructor_3361A8 *func_003366D0(Constructor_3361A8 *object) {
    func_00335FB0(object);
    object->table = D_001ADA38;
    return object;
}


void func_00336710(char *s1, int a1, char *a2)
{
    F081de6c9_FUN_00335FC8(s1, a1, a2);
    if (a2 != 0) {
        int *v = F081de6c9_FUN_00336DA8(16, F081de6c9_FUN_00336E40(*(int *)(s1 + 44)));

        *(int **)(s1 + 52) = v;
        v[1] = 0;
        v[2] = 0;
        v[3] = 0;
        v[0] = 0;
    }
    ((int *)*(int **)(s1 + 52))[0] = 0;
    ((int *)*(int **)(s1 + 52))[1] = 0;
    *(float *)(*(char **)s1 + 0) = 100.0f;
    *(float *)(*(char **)s1 + 4) = 100.0f;
    *(float *)(*((char **)s1 + 1) + 0) = 64.0f;
    *(float *)(*((char **)s1 + 1) + 4) = 64.0f;
    *(int *)(s1 + 56) = 0;
}

/* Measured target: byte-identical across all 27 levels. */
s32 func_003367B8(u8 *a0) { return *(s32 *)(a0 + 0x34); }

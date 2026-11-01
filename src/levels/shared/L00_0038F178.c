#include "include_asm.h"

extern int func_002A77E0(int mode);

extern float func_002A90F8(char *object, char *local);

extern void func_00282D30_7(char *local, int value, float scale);

extern float func_002A7878_1(float low, float high);

extern void func_002BF728(char *object, char *local, float amount, float base);

extern char *func_0029EFD0_1(int);

/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner {
    unsigned char prefix_00[0x68];
    void *context_68;
} Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner;

typedef struct Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext {
    unsigned char prefix_00[0x10];
    float vector_10[4];
    unsigned int field_20;
    unsigned int active_24;
} Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext;

extern void func_002FDBD8(float scale, Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context,
                                    float *vector, int mode);

extern void func_002FDBD8_1(float scale, Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context,
                                    float *vector, int mode);

typedef int TI128 __attribute__((mode(TI)));

extern int D_18C0A0;

extern int D_18C0B4;

extern int D_L00_001B9080;

extern void func_002A7470(char *object, int mode, int a2, int a3);

extern void func_002FEE50(int value);

extern void func_00282C88(char *quad);

extern void func_002A10E8(char *object);

extern void func_002A0F48(char *object);

extern void func_L00_004283C8(int value);

extern void func_L00_002C42E0(int a, int b);

extern void func_L00_002F4720(void);

extern void func_L00_00390F28(char *object, int mode);

typedef unsigned char u8;

typedef float f32;

/* Prototype775 is a research label. Field names below describe only the
 * independently observed byte23 and binary32 word2C operations. */
typedef struct {
    u8 pad00[0x23];
    u8 field23;
    u8 pad24[8];
    f32 field2C;
} NativeUpdate775View;

extern void func_0029F338(NativeUpdate775View *object);

typedef struct {
    char prefix[0x760];
    float aimAxis[4];
    char pad770[0xAC0];
    unsigned int buttons;
    char pad1234[0xC];
    int resource;
    char pad1244[0x1050];
    int level;
    char pad2298[0x24];
    unsigned char busy;
    char pad22BD[0x277];
    int cooldown;
} LaunchHero;
extern LaunchHero D_00189E20;
extern unsigned int D_00138320;
extern void func_0029FCC0(char *, int, char *);
/* Interleaved declarations preserve the EE ABI's independent GPR and FP argument order. */
extern void func_002FDF40(void *, void *, void *, float, float, float, float, void *);
extern int func_002FE5A0(void *, void *, void *, void *, void *, int, int, float);
extern int func_00282948(int *), func_L00_002D3F30(int, int);
extern void func_L00_002AF7D0(void), func_L00_002AF568(void);
extern int func_002E5CF8(int, int, char *);
extern char *func_L00_00398810(char *, char *);
extern void ref_L00_0039D110_00(void *, void *);
extern void func_L00_0039D340(Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner *);

typedef struct { float value[3]; } QuerySettings;
extern QuerySettings D_L00_001AF410;
typedef struct { char prefix[0x1A0]; unsigned int held, pressed; } LaunchInput;
extern LaunchInput D_00138180;
extern char *func_002AF580(void *, void *, int *, void *, int, int, float, float, float, float, float, int, void *);
extern char *func_L00_0038D530(char *, char *);
extern void ref_L00_00397E60_00(void *, void *);
extern void func_L00_00398118(Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner *);

/* func_L00_0038F178 is defined in L00_0038F178-effects.c. */

/* Family 6eb4f363e5305bed: seed body at func_L00_00387408. */
void func_L00_0038F3D8(char *object)
{
    char local[16];
    float base;
    int value = *(int *)(object + 104);

    if (func_002A77E0(5))
        return;
    base = func_002A90F8(object + 16, local);
    func_00282D30_7(local, value, 0.25f);
    func_002BF728(object + 16, local, func_002A7878_1(0.05f, 0.1f) * 210000.0f, base);
}

typedef union { TI128 quad; float f[4]; } ParticleUpdateVector;
typedef struct { int color[4]; } ParticleUpdateColors;
extern ParticleUpdateColors D_L00_001AF010;
extern float func_002A7878(float, float);
extern void func_00282F20(void *, void *, float);
extern int func_002AAFA0(int, int);
extern void func_002BAE50(void *, void *, int, int, int, int, int, int);
extern float func_00283B98(float, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_L00_003253A0(void *, void *, void *, float);
extern float func_00283CE0(int);
extern int func_00282978(short *);

void func_L00_0038F5F0(char *object)
{
    ParticleUpdateColors colors;
    ParticleUpdateVector direction, random;
    char *state = *(char **)(object + 0x68);
    int enabled = 1;
    if (*(int *)(state + 0x20) != 0)
        if (func_002A77E0(2))
            enabled = 0;
    if ((*(unsigned char *)(object + 0xBC) & 1) && enabled) {
        int color;
        colors = D_L00_001AF010;
        random.quad = 0;
        random.f[0] = func_002A7878(-1.0f, 1.0f);
        random.f[1] = func_002A7878(-1.0f, 1.0f);
        random.f[2] = func_002A7878(-1.0f, 1.0f);
        direction.quad = random.quad;
        func_00282F20(&direction, &direction, 1.0f / 60.0f);
        if (*(unsigned char *)(object + 0xBC) & 0xFE) {
            color = func_002AAFA0(colors.color[func_002A77E0(4)],
                                *(unsigned char *)(object + 0xBC) >> 1);
            func_002BAE50(object + 0x10, &direction, color,
                         func_002AAFA0(0x4FFF, *(unsigned char *)(object + 0xBC) >> 1),
                         45, 50, 120, 1);
        } else {
            func_002BAE50(object + 0x10, &direction, colors.color[func_002A77E0(4)],
                         0x4FFF, 45, 50, 120, 1);
        }
    }
    *(float *)(object + 0xF0) = func_00283B98(*(float *)(object + 0xF0), *(float *)(state + 0x10));
    *(float *)(object + 0xF4) = func_00283B98(*(float *)(object + 0xF4), *(float *)(state + 0x14));
    func_00282CC0(object + 0x10, object + 0x10, state);
    func_L00_003253A0(object, state, state, 0.0040555559f);
    if (*(float *)(object + 0x10) < 0.0f || *(float *)(object + 0x14) < 0.0f ||
        *(float *)(object + 0x18) < 0.0f) {
        func_0029F338((NativeUpdate775View *)object);
        return;
    }
    if (*(short *)(state + 0x18) < *(short *)(state + 0x1A) / 4) {
        float amount = func_00283CE0(*(short *)(state + 0x18));
        *(float *)(object + 0x2C) = *(float *)(state + 0x1C) * amount /
                                  func_00283CE0(*(short *)(state + 0x1A) / 4);
    }
    if (func_00282978((short *)(state + 0x18)))
        func_0029F338((NativeUpdate775View *)object);
}

/* func_L00_0038F8B8 is defined in L00_0038F8B8.c. */

/* func_L00_0038FC48 is defined in L00_0038FC48-g8.c. */

INCLUDE_ASM("asm/levels", func_L00_0038FE10);

/* Calls a callee with the constant 167 and, when it returns a non-zero object, stores the argument pointer at +4 of the object held at +104, clears the words at +0, +8 and +12 of that object, sets byte +48 to 255, the halfword at +50 to 126 and bytes +49 and +32 to 0, then returns the object. */
char *func_L00_00390938(char *p)
{
    char *o = func_0029EFD0_1(167);
    int *v;

    if (o != 0) {
        v = *(int **)(o + 104);
        v[1] = (int)p;
        v[0] = 0;
        v[2] = 0;
        v[3] = 0;
        *(unsigned char *)(o + 48) = 255;
        *(short *)(o + 50) = 126;
        o[49] = 0;
        o[32] = 0;
    }
    return o;
}

INCLUDE_ASM("asm/levels", func_L00_00390E10);


INCLUDE_ASM("asm/levels", func_L00_00390FF8);

/* Releases the second argument's object: clears a word of the sub-object at +0x68, clears
 * two globals, hands its +0x14 word over before clearing it, then runs five helpers and the
 * first argument through one more. */
void func_L00_00391310(char *arg0, char *arg1)
{
    char *s0 = arg1;
    char *s1 = arg0;
    int *v = *(int **)s0;

    v = (int *)*(int *)((char *)v + 0x68);
    if (v != 0)
        v[1] = 0;
    D_18C0A0 = 0;
    func_L00_004283C8(*(int *)(s0 + 0x14));
    *(int *)(s0 + 0x14) = 0;
    func_L00_002C42E0(0, 1);
    func_L00_00390F28(s1, 1);
    func_L00_002F4720();
    func_002FEE50(*(int *)(s0 + 0x4C));
    func_0029F338((NativeUpdate775View *)s1);
    D_L00_001B9080 = 0;
}





/* Gates on the sub-object's tag byte, mirrors one status bit from that object into its own
 * halfword, clamps the wrapped value at +4 against a signed window and finishes with the
 * three transform helpers; original game role is unknown. */
extern int D_0018B060;

extern void func_310440(char *object);

extern void func_310838(char *object, int mode, int delta);

extern float func_31A7C0(float low, float high);

extern float func_31F1C8(float angle);

extern float func_2EF0F8(float value, float amount);

extern void func_312D18(char *object);

void func_L00_003952E0(char *object)
{
    char *s1 = *(char **)(object + 0x68);
    char *other = *(char **)(s1 + 8);
    unsigned char tag = *(unsigned char *)(other + 0x20);

    if (tag == 0 || (tag & 0xF0) == 0xF0) {
        func_310440(object);
        return;
    }
    if (other != 0) {
        if ((*(unsigned short *)(object + 0x34) & 1) != (*(unsigned short *)(other + 0x34) & 1)) {
            unsigned short bits = *(unsigned short *)(object + 0x34) & 0xFFFE;

            *(unsigned short *)(object + 0x34) = bits;
            bits |= *(unsigned short *)(*(char **)(s1 + 8) + 0x34) & 1;
            *(unsigned short *)(object + 0x34) = bits;
        }
    }
    if (D_0018B060 < 0x19)
        *(unsigned short *)(object + 0x34) |= 0x41;
    {
        int current = *(int *)(s1 + 4);
        int next = current - 0xC0;
        int delta = -0xC0;

        *(int *)(s1 + 4) = next;
        if (next >= 0x1001) {
            delta = -0x10C0;
            *(int *)(s1 + 4) = current - 0x10C0;
        } else if (next < 0) {
            delta = 0xF40;
            *(int *)(s1 + 4) = current + 0xF40;
        }
        func_310838(*(char **)(object + 0x24), 0, delta);
    }
    *(float *)(object + 0x2C) = *(float *)(*(char **)(object + 0x24) + 0x24)
                                * *(float *)(s1 + 0xC) * func_31A7C0(0.5f, 1.0f);
    *(float *)(object + 0xF4) = func_2EF0F8(*(float *)(object + 0xF4),
                                             func_31F1C8(*(float *)(s1 + 0xC)));
    func_312D18(object);
}

/* Builds the object for type 0xB3 and, when the constructor returns one, fills its fields,
 * clears a quad at +0xF0, records the argument in the sub-object at +0x68 and copies three
 * quads from the argument before running two helpers. Returns the object. */
char *func_L00_00395240(char *arg)
{
    char *p = arg;
    char *object = func_0029EFD0_1(0xB3);

    if (object != 0) {
        int *sub = *(int **)(object + 0x68);
        *(unsigned char *)(object + 0x30) = 0xFF;
        *(unsigned short *)(object + 0x32) = 0xFF;
        *(unsigned char *)(object + 0x31) = 1;
        *(unsigned short *)(object + 0x34) = 0x204;
        *(unsigned char *)(object + 0x23) = 0x50;
        *(char *)(object + 0x20) = 0;
        sub[2] = (int)p;
        func_00282C88(object + 0xF0);
        *(TI128 *)(object + 0xC0) = *(TI128 *)(p + 0xC0);
        *(TI128 *)(object + 0xD0) = *(TI128 *)(p + 0xD0);
        *(TI128 *)(object + 0xE0) = *(TI128 *)(p + 0xE0);
        func_002A10E8(object);
        func_002A0F48(object);
    }
    return object;
}

INCLUDE_ASM("asm/levels", func_L00_00395428);

/* func_L00_003959C0 is defined in L00_003959C0-g8.c. */

/* func_L00_00395A88 is defined in L00_00395A88-g8.c. */

/* func_L00_00396078 is defined in L00_00396078-g64.c. */


/* func_L00_003973E8 is defined in L00_003973E8-g8.c. */

/* Selects an aim target before advancing the projectile launcher state. */
void func_L00_00397E60(char *actor)
{
    char *state = *(char **)(actor + 0x68);
    char position[16];
    QuerySettings settings;
    char direction[16];
    int foundCount;
    char *target;
    int ready;
    func_0029FCC0(actor, 0, position);
    settings = D_L00_001AF410;
    target = func_002AF580(actor + 0x10, D_00189E20.aimAxis, &foundCount, 0, 0, 0,
                          0.3926991f, 0.7853982f, 11.1f, 0.0f, 0.0f, 0, &settings);
    func_002FDF40(direction, position, target, 1.5f, D_00189E20.level == 29 ? 11.0f : 10.0f, 0.16666667f, 0.003055555745959282f, 0);
    ready = 1;
    *(int *)(state + 0x24) = func_002FE5A0(position, direction, state, state + 0x10, actor, 0, 0, 0.003055555745959282f);
    if (D_00189E20.level == 29) {
        if (!func_00282948(&D_00189E20.cooldown)) ready = 0;
    }
    else D_00189E20.cooldown = 40;
    switch (*(unsigned char *)(actor + 0x20)) {
    case 0:
        *(unsigned char *)(actor + 0x20) = 1;
        *(int *)(state + 0x24) = 0;
    case 1:
        if ((D_00138180.held & D_00189E20.buttons) == 0 || D_00189E20.busy || D_00189E20.resource < 23 || !ready) break;
        if (func_L00_002D3F30(-1, 1)) {
            func_L00_002AF568();
            *(unsigned char *)(actor + 0x20) = 2;
            *(int *)(state + 0x20) = 20;
            break;
        }
        if (D_00138180.pressed & D_00189E20.buttons) func_002E5CF8(2, 0, actor);
        break;
    case 2:
        if (!func_00282948((int *)(state + 0x20))) break;
        *(char **)(func_L00_0038D530(position, direction) + 0xB8) = actor;
        func_L00_002AF7D0();
        *(unsigned char *)(actor + 0x20) = 3;
        *(int *)(state + 0x20) = 10;
        break;
    case 3:
        if (func_00282948((int *)(state + 0x20))) *(unsigned char *)(actor + 0x20) = 1;
        break;
    }
    ref_L00_00397E60_00(func_L00_00398118, actor);
}


/* When the context flag at offset 0x24 is nonzero, pass scale 1.0, the context, its vector at offset 0x10 and mode zero to the bound helper; original game role is unknown. */
void func_L00_00398118(Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner *owner)
{
    Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context = owner->context_68;
    if (context->active_24 != 0) {
        func_002FDBD8(1.0f, context, context->vector_10, 0);
    }
}


INCLUDE_ASM("asm/levels", func_L00_00398810);


/* func_L00_0039B288 is defined in L00_0039B288-g8.c. */


/* Aims and launches the actor's projectile in response to the shared input gate. */
void func_L00_0039D110(char *actor)
{
    char *state = *(char **)(actor + 0x68);
    char position[16], direction[16];
    int ready;
    func_0029FCC0(actor, 0, position);
    func_002FDF40(direction, position, 0, 1.5f, D_00189E20.level == 29 ? 11.0f : 5.0f, 0.16666667f, 0.003055555745959282f, 0);
    ready = 1;
    *(int *)(state + 0x24) = func_002FE5A0(position, direction, state, state + 0x10, actor, 0, 0, 0.003055555745959282f);
    if (D_00189E20.level == 29) {
        if (!func_00282948(&D_00189E20.cooldown)) ready = 0;
    }
    else D_00189E20.cooldown = 40;
    switch (*(unsigned char *)(actor + 0x20)) {
    case 0:
        *(unsigned char *)(actor + 0x20) = 1;
        *(int *)(state + 0x24) = 0;
    case 1:
        if ((D_00138320 & D_00189E20.buttons) == 0 || D_00189E20.busy || D_00189E20.resource < 9 || !ready) break;
        if (func_L00_002D3F30(-1, 1)) {
            func_L00_002AF568();
            *(unsigned char *)(actor + 0x20) = 2;
            *(int *)(state + 0x20) = 20;
            break;
        }
        func_002E5CF8(2, 0, actor);
        break;
    case 2:
        if (!func_00282948((int *)(state + 0x20))) break;
        *(char **)(func_L00_00398810(position, direction) + 0xB8) = actor;
        func_L00_002AF7D0();
        *(unsigned char *)(actor + 0x20) = 3;
        *(int *)(state + 0x20) = 10;
        break;
    case 3:
        if (func_00282948((int *)(state + 0x20))) *(unsigned char *)(actor + 0x20) = 1;
        break;
    }
    ref_L00_0039D110_00(func_L00_0039D340, actor);
}

/* When the context flag at offset 0x24 is nonzero, pass scale 1.0, the context, its vector at offset 0x10 and mode zero to the bound helper; original game role is unknown. */
void func_L00_0039D340(Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner *owner)
{
    Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context = owner->context_68;
    if (context->active_24 != 0) {
        func_002FDBD8_1(1.0f, context, context->vector_10, 0);
    }
}

/* The mode word at 0x18C0B4 must be 8 and the object's byte 0x43 must not be 6; the
 * helper then takes the object with mode 6, zero and ten. */
void func_L00_0039D378(char *object)
{
    if (D_18C0B4 == 8) {
        if (*(unsigned char *)(object + 0x43) != 6)
            func_002A7470(object, 6, 0, 10);
    }
}

/* func_L00_0039E158 is defined in L00_0038F178-rail.c. */

/* multiply binary32 field2C by exact1.025f then subtract3 modulo256 from byte23; call original pointer helper if updated byte below4; no original semantic field names recovered */
void func_L00_0039E5B0(NativeUpdate775View *object)
{
    object->field2C *= 1.025f;
    object->field23 -= 3;
    if (object->field23 < 4)
        func_0029F338(object);
}

/* func_L00_0039E600 is defined in L00_0039E600.c. */


/* func_L00_003A09F8 is defined in L00_0038F178-tile.c. */

/* func_L00_003A0C00 is in L00_003A0C00.c. */


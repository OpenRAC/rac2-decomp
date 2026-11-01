#include "include_asm.h"
#include "common.h"


extern void func_00282C88(void *);
extern void func_002A7A00(void *, float, float);

typedef int TI128 __attribute__((mode(TI)));

extern void func_0029F338(void *);

struct CD758Object {
    char pad0[0x10];
    float pos[4];
    char pad1[0x48];
    struct CD758Data *data;
    char pad2[0x84];
    float angles[3];
};

struct CD758Data {
    char pad[0x370];
    char *other;
};

extern void func_00282978(void *);

extern void func_00282CF0(float *, const float *, const float *);

extern void func_002AFDD8(unsigned char *, unsigned char *, unsigned char *, int);

extern float func_00283248(float, float);

extern float func_00282E20(char *);

extern float func_002A7878(float, float);

extern float func_002A7940(void);

extern float func_00283180(float);

extern float func_00283198(float);

extern void func_00282CC0(void *, void *, void *);

extern void func_002AEC48(void *, void *, int, float, float);

extern void func_002B0990(void *, void *, int, float, int);

extern void func_L02_002F1FB8(void *, void *, void *);

extern void func_00282F20(char *, char *, float);

extern float func_00282DB0(void *, void *);

extern char *D_L02_001FF1C0[];

extern char *D_L02_001B359C __attribute__((sda));

extern char *D_L02_001FC060[];

extern float func_00283C80_3(float, float);

extern float func_00283B98_12(float, float);

extern float func_00283BE0_7(float, float);

extern void func_002833F0_2(void *, void *);

extern void func_002E5DA0(int, int, void *, int);

extern void func_0029FCC0(char *, int, void *);

extern int func_801234F0(float);

extern void func_0026FEB8(void *, int, int, int, int);

extern void func_L00_002D40A0(void *, int, float);

extern char D_L02_001AFE38[];

extern void func_002A6C58(void *, int, int);

extern void func_00288CB0(int, int);

extern void func_L00_0037E5F0(float);

extern int func_L00_0032EF10(int, int, int);

extern void func_002A7750(void *, int, int);

extern void func_002B6D28(void);

extern void func_002A7470(void *, int, int, int);

extern void func_L00_003DD2B8(void);

extern void func_L00_002E6EF8(void *, void *);

extern void func_L02_003D28E0(void);

extern void func_L02_00333438(char *, char *);

extern int func_L01_00321178(char *, char *);

extern int func_002B4FF0(char *, float *, float);

extern struct S_001A63A8 D_001A63A8;

extern int D_L02_001A8FF0 __attribute__((sda));

extern void func_002B60B0(void *, float, float, float, float);

extern long long func_0027C878(char *);

extern float func_00282E80(void *, void *);

extern int func_002ACBC8(void *, int);

/* The level's three trigger boxes and the point they hold. */
extern char D_L02_001AFEA0[];

extern char D_00189EA0[];

extern void func_00283410(float *, float *);

extern void func_00280B90(char *, float *, int);

/* The emitter table in the boot's resident memory, a ring of 0x70-byte records. */
extern unsigned char D_00188660[];

/* The level's own emitter counter, in the level's data. */
extern int D_L02_001B3FD8 __attribute__((sda));

extern void func_L02_003D6DF8(void *);

extern void func_L02_003D7040(void *);

extern void func_L02_003D7140(void *);

extern void func_L00_00323958(void *, void *);

extern void func_00283738(void *, void *, void *);

extern void func_00283658(void *, void *);

extern void func_002AB6D8(float *, float *);

extern int func_002E5CF8(int, int, char *);

extern int func_002E59B0(int, int);

extern void func_002E59F8(int);

extern int func_00282948(void *);

/* The packet reset, which the levels place in two copies: the one this function calls
   differs from level to level. */
extern void ref_L02_003FFC48_00(char *);

/* The vector scaler, in two copies as well. */
extern void ref_L02_003FFC48_01(char *, float);

struct S_001A63A8 {
    char pad0[0x6C];
    short f6C;
    char pad1[4];
    short f72;
};

struct Sub {
    float f0;
    int f4;
    int p8;
    int p12;
    int p16;
    int f20;
};

struct Elem {
    char pad[104];
    struct Sub *sub;
    char pad2[140];
    float f248;
};

struct G {
    char pad[192];
    struct Elem *arr[22];
    int count;
};

struct Outer {
    char pad[104];
    struct G *g;
};

/* The aim vector the L02 aiming helpers read, at 0x001BA3C0. */
typedef struct {
    char pad_000[0x140];
    float x_140;
    float y_144;
    float z_148;
} L02AimVector;

extern L02AimVector D_L02_001BA3C0;

typedef int BatchA_A17_s32;

typedef short BatchA_A17_BatchAs16;

INCLUDE_ASM("asm/levels", func_L02_003C43F0);

/* Walks an inline array of element pointers; for each element whose sub-object flag at +4 is zero it rewrites a 270-degree angle to -90, scales it by pi/180, compares a helper result against 0.001 and routes it through one of two pi/2 helpers, toggles the flag, then calls a two-pointer helper with element+192 and element+240. */
void func_L02_003C46E0(struct Outer *p)
{
    struct G *g = p->g;
    int i;

    for (i = 0; i < g->count; i++) {
        struct Sub *s = g->arr[i]->sub;

        if (s->f4 == 0) {
            if (s->f0 == 270.0f)
                s->f0 = -90.0f;
            if (func_00283C80_3(g->arr[i]->f248, s->f0 * 1.7453294247388839721680e-02f)
                < 1.0000000474974513053894e-03f)
                g->arr[i]->f248 = func_00283B98_12(g->arr[i]->f248, 1.5707964897155761718750e+00f);
            else
                g->arr[i]->f248 = func_00283BE0_7(g->arr[i]->f248, 1.5707964897155761718750e+00f);
            s->f20 = !s->f20;
            func_002833F0_2((char *)g->arr[i] + 192, (char *)g->arr[i] + 240);
        }
    }
    if (g->count != 0)
        func_002E5DA0(1, 0, g->arr[0], 2198);
}

/* Clears the three pointer-list flags, updates their counters and copies the vectors. */
/* Defined in L02_003C4848-helpers.c. */

extern char D_L02_001BA500[];
/* Two-float interface of the range RNG; other callers in this unit use an older declaration. */
extern float func_002A7878_range(float, float) __asm__("func_002A7878");
extern int func_002A77E0(int);
extern float func_002A78D8(float, float);
extern void func_002ACEC0(void *, void *, void *, float);
extern char *func_002C2210(void *, int, float, float, unsigned int, int, int, void *, int, float);
extern int func_00283CF0(float);

/* Emits paired particles with opposite spin and randomized velocities. */
void func_L02_003C49A0(float *pos, int count) {
    float velocity[4], origin[4], direction[4], axis[4], offset[4];
    float size, angle;
    int i;
    int sign;
    char *particle;
    func_00282CF0(direction, (float *)D_L02_001BA500, pos);
    func_00282F20((char *)offset, (char *)direction, 0.3f);
    direction[2] = 0;
    axis[0] = 0;
    axis[1] = 0;
    axis[2] = 1.0f;
    axis[3] = 1.0f;
    for (i = 0; i < count; i++) {
        size = func_002A7878_range(0.5f, 2.0f);
        sign = func_002A77E0(2);
        if (!sign) sign--;
        angle = func_002A7878_range(-1.0471977f, 1.0471977f);
        func_002ACEC0(velocity, direction, axis, angle);
        func_00282F20((char *)velocity, (char *)velocity, func_002A7878_range(0.05f, 3.0f) * 0.0166666675f);
        velocity[2] = func_002A7878_range(1.0f, 5.0f) * 0.0166666675f;
        func_00282CC0(origin, pos, offset);
        pos[0] += func_002A78D8(0, 0.15f);
        pos[1] += func_002A78D8(0, 0.15f);
        pos[2] += func_002A78D8(0, 0.15f);
        particle = func_002C2210(origin, 60, size * 0.1f, size, 0xDDFF1010, 0, sign, velocity, 0, 0.002f);
        if (particle) particle[9] = func_00283CF0(4.0f) + 0x70;
        particle = func_002C2210(origin, 60, size * 0.07f, size * 0.7f, 0xDDFF1010, 1, -sign, velocity, 0, 0.002f);
        if (particle) particle[9] = func_00283CF0(4.0f) + 0x70;
    }
}

/* Reads three angles through a helper, bends the object's own angle at +0xF8 into the same
   range, converts all four and hands them to the four-argument report, then applies the
   same bend to the local angles. */
void func_L02_003C4E18(char *a0)
{
    char *s0 = a0;
    float v[4];
    float f20;

    func_0029FCC0(a0, 1, v);
    /* retail holds 0x40490FD0 here; this spelling is what the rebuilt assembler reads to
       those bits */
    f20 = func_00283B98_12(*(float *)(s0 + 0xF8), 3.14159f);
    func_0026FEB8(D_L02_001AFE38, func_801234F0(v[0]), func_801234F0(v[1]),
                  func_801234F0(v[2]), func_801234F0(f20));
    func_L00_002D40A0(v, 0, f20);
}

/* The level's three trigger boxes, each a lower and an upper bound, and the point they hold:
   the point has to lie inside every box. */
struct L02Box {
    float lo;
    float hi;
};

struct L02Boxes {
    struct L02Box b[3];
};

struct L02Vec {
    float x, y, z, w;
} __attribute__((aligned(16)));

int func_L02_003C5098(char *a0)
{
    struct L02Boxes box;
    struct L02Vec vec;
    void *sub;
    float f0;

    box = *(struct L02Boxes *)D_L02_001AFEA0;
    sub = *(void **)(a0 + 0x68);
    f0 = func_00282E80(a0 + 0x10, D_00189EA0);
    if (f0 > 24.0f)
        return 0;
    if (*(int *)((char *)sub + 4) != -1)
        return func_002ACBC8(D_00189EA0, *(int *)((char *)sub + 4));
    func_00282CF0((float *)&vec, (float *)D_00189EA0, (float *)(a0 + 0x10));
    func_002AFDD8((unsigned char *)a0, (unsigned char *)&vec, (unsigned char *)&vec, 0);
    if (vec.x >= box.b[0].lo && vec.x <= box.b[0].hi &&
        vec.y >= box.b[1].lo && vec.y <= box.b[1].hi &&
        vec.z >= box.b[2].lo && vec.z <= box.b[2].hi)
        return 1;
    return 0;
}

extern int func_002A8508(int, int);
extern float func_00283B98(float, float);
/* (a, b, phase) with its float first: the EE passes each bank in order. */
extern u32 func_L01_0031BC68(float, u32, u32);
extern void func_002A0468(void *, u32, int, int, int);

/* Advances the group's pulse phase by pi/30, tints every moby of the object's group
   (and the child of each 0x873 moby) blue in state 7 or dim otherwise, then sets the
   pulsing color between COLOR1 and COLOR2 on the group's 0xAF9-0xAFD, 0xB03 and 0x873
   mobys. */
void func_L02_003C51F8(char *obj, u32 color1, u32 color2) {
    char *vars = *(char **)(obj + 0x68);
    u16 *list;
    char *moby;
    char *child;

    if (func_002A8508(*(u8 *)(obj + 0x21), -1) < 2)
        return;
    list = (u16 *)D_L02_001FC060[*(u8 *)(obj + 0x21)];
    *(float *)(vars + 0x128) = func_00283B98(*(float *)(vars + 0x128), 0.104719772f);
    do {
        moby = D_L02_001B359C + ((*list & 0x7FFF) << 8);
        if (*(u8 *)(obj + 0x20) == 7) {
            if (*(short *)(moby + 0xAA) != 0x896) {
                func_002A0468(moby, func_L01_0031BC68(*(float *)(vars + 0x128), 0x5050DD, 0x505050),
                              14, 14, 14);
                if (*(short *)(moby + 0xAA) == 0x873) {
                    child = *(char **)(moby + 0x68);
                    func_002A0468(*(void **)(child + 0x1C),
                                  func_L01_0031BC68(*(float *)(vars + 0x128), 0x5050DD, 0x505050),
                                  14, 14, 14);
                }
            }
        } else if (*(short *)(moby + 0xAA) != 0x896) {
            func_002A0468(moby, 0x505010, 14, 14, 14);
            if (*(short *)(moby + 0xAA) == 0x873)
                func_002A0468(*(void **)(*(char **)(moby + 0x68) + 0x1C), 0x505010, 14, 14, 14);
        }
        if (*(short *)(moby + 0xAA) == 0xAF9 || *(short *)(moby + 0xAA) == 0xAFA ||
            *(short *)(moby + 0xAA) == 0xAFB || *(short *)(moby + 0xAA) == 0xAFD ||
            *(short *)(moby + 0xAA) == 0xAFC || *(short *)(moby + 0xAA) == 0xB03 ||
            *(short *)(moby + 0xAA) == 0x873) {
            if (*(short *)(moby + 0xAA) == 0x873) {
                child = *(char **)(moby + 0x68);
                *(u32 *)(*(char **)(child + 0x1C) + 0x78) =
                    func_L01_0031BC68(*(float *)(vars + 0x128), color1, color2);
            } else {
                *(u32 *)(moby + 0x78) = func_L01_0031BC68(*(float *)(vars + 0x128), color1, color2);
            }
        }
    } while ((short)*list++ >= 0);
}

/* Defined in L02_003C5438.c. */

/* Defined in L02_003C9D78-g8.c. */

/* Defined in L02_003C9ED0-nsr.c. */

/* Defined in L02_003CA0A8-g8.c. */

/* Defined in L02_003CA280-g8.c. */

INCLUDE_ASM("asm/levels", func_L02_003CC7B0);



INCLUDE_ASM("asm/levels", func_L02_003CCEA0);

/* func_L02_003CCFE8 is defined in L02_003C43F0-g8.c (the -G8 profile reproduces its
   placement-table address reloads; the body itself reads no $gp data). */


extern int D_L02_001B35B8 __attribute__((sda));
extern float func_00282E48(void *, void *);

struct L02NearObject {
    char pad[0x21];
    unsigned char group;
};

struct L02NearBlock {
    char pad[0x378];
    unsigned short f378;
};

/* Finds the entity of the object's group nearest to the player (within 1000.0), then adds
   0x19 to the +0x378 timer of every other entity of the group. */
void func_L02_003CD298(struct L02NearObject *a0)
{
    unsigned short *q;
    unsigned short *p;
    unsigned short *r;
    char *e;
    char *best;
    struct L02NearBlock *o;
    float min;
    float d;

    if (a0->group == 0xFF)
        return;
    q = (unsigned short *)D_L02_001FC060[a0->group];
    if (q == 0)
        return;
    best = 0;
    min = 1000.0f;
    p = q;
    while (a0->group != 0xFF && a0->group <= D_L02_001B35B8 && p != 0 &&
           ((p != 0 && (short)p[-1] >= 0) || p == (unsigned short *)D_L02_001FC060[a0->group])) {
        e = D_L02_001B359C + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        d = func_00282E48(e + 0x10, D_00189EA0);
        if (d < min) {
            min = d;
            best = e;
        }
        p++;
    }
    if (best != 0) {
        for (r = (unsigned short *)D_L02_001FC060[a0->group];
             a0->group != 0xFF && a0->group <= D_L02_001B35B8 && r != 0 &&
             ((r != 0 && (short)r[-1] >= 0) ||
              r == (unsigned short *)D_L02_001FC060[a0->group]);
             r++) {
            e = D_L02_001B359C + ((*r & 0x7FFF) << 8);
            if (e == 0)
                break;
            if (e != best) {
                o = *(struct L02NearBlock **)(e + 0x68);
                o->f378 += 0x19;
            }
        }
    }
}

typedef int L02Word;

extern L02Word D_L02_001B35B8 __attribute__((sda));
extern int func_002A7820(int, int);

struct L02GroupObject {
    char pad[0x21];
    unsigned char group;
};

struct L02GroupEntityObj {
    char pad[0x378];
    short f378;
};

struct L02GroupEntity {
    char pad[0x68];
    struct L02GroupEntityObj *obj;
};

/* Gives every entity of the object's group a random timer between 0x1E and 0x5A at +0x378
   of its private block. */
void func_L02_003CD4A8(struct L02GroupObject *arg0)
{
    unsigned short *q;
    unsigned short *p;
    struct L02GroupEntity *e;

    if (arg0->group == 0xFF)
        return;
    q = (unsigned short *)D_L02_001FC060[arg0->group];
    if (q != 0) {
        p = q;
        while (arg0->group != 0xFF && arg0->group <= D_L02_001B35B8 && p != 0 &&
               ((p != 0 && (short)p[-1] >= 0) ||
                p == (unsigned short *)D_L02_001FC060[arg0->group])) {
            struct L02GroupEntityObj *o;

            e = (struct L02GroupEntity *)(D_L02_001B359C + ((*p & 0x7FFF) << 8));
            if (e == 0)
                break;
            o = e->obj;
            p++;
            o->f378 = func_002A7820(0x1E, 0x5A);
        }
    }
}

/* Removes the owner when its timer expires; otherwise replaces a mismatched child
   kind and restores the owner's saved position and state. */

extern int D_L02_001B35B8 __attribute__((sda));

/* Sets every entity of the object's group to state 1 with a 0xB4 timer. */
void func_L02_003CD8C0(unsigned char *arg0) {
    unsigned short *q;
    char *e;

    if (arg0[0x21] == 0xFF)
        return;
    q = (unsigned short *)D_L02_001FC060[arg0[0x21]];
    while (arg0[0x21] != 0xFF && arg0[0x21] <= D_L02_001B35B8 && q != 0 &&
           ((q != 0 && (short)q[-1] >= 0) || q == (unsigned short *)D_L02_001FC060[arg0[0x21]])) {
        char *o;

        e = D_L02_001B359C + ((*q & 0x7FFF) << 8);
        if (e == 0)
            break;
        o = *(char **)(e + 0x68);
        *(unsigned short *)(o + 0x382) = 1;
        *(unsigned short *)(o + 0x386) = 0xB4;
        q++;
    }
}

extern int D_001A79F0[] __attribute__((sda));
extern char *D_L02_001B3200 __attribute__((sda));
extern char D_L02_001B3210[] __attribute__((sda));
extern void func_002B0178(void *, void *, void *);
extern void func_002A93B0(void *);
extern int func_002B0ED8(void *, void *, int);
extern void func_L02_003CE9A8(void *);
extern int func_002B3BA8(void *, int, float, float, int, int);
extern void func_002AFFD8(void *, void *, int);

void func_L02_003CE4D0(char *obj) {
    char *d = *(char **)(obj + 0x68);
    char *entry;
    int hit;
    if (*(unsigned char *)(obj + 0x20) == 0) {
        if (D_001A79F0[0] == 26) {
            if (D_L02_001A8FF0 == 0) return;
            func_002B0178(obj + 0x10, obj, obj + 0x10);
            *(short *)(d + 0x338) = 1;
            *(int *)(obj + 0x9c) = 3;
            *(unsigned short *)(obj + 0x34) |= 0x100;
            *(float *)(d + 0x90) = func_00282E48(obj + 0x10, D_L02_001B3210) - 1.5f;
        } else {
            *(int *)(obj + 0x9c) = 12;
            *(float *)(d + 0x90) = *(float *)(obj + 0x18) - 1.0f;
        }
        if (*(int *)(d + 0x210) == -1) {
            func_0029F338(obj);
            return;
        }
        entry = D_L02_001B3200 + *(int *)(d + 0x210) * 0x30;
        if (*(short *)(entry + 0x30)) {
            *(int *)(d + 0x13c) = *(int *)(d + 0x218) = **(int **)(entry + 0x3c);
        } else *(int *)(d + 0x218) = -1;
        *(float *)(d + 0x324) = func_002A7878_range(1.0f, 1.332999945f);
        *(float *)(obj + 0x2c) = *(float *)(*(char **)(obj + 0x24) + 0x24) * *(float *)(d + 0x324);
        *(char *)(d + 0x48) = func_00283CF0(15.0f);
        *(char *)(d + 0x4a) = func_00283CF0(6.4f);
        *(int *)(d + 0x98) = 3;
        *(float *)(d + 0x80) = 0.2f;
        *(float *)(d + 0x84) = 0.2f;
        *(float *)(d + 0x8c) = 0.4f;
        *(float *)(d + 0x108) = 0.4f;
        *(float *)(d + 0x134) = 0.05f;
        *(char *)(d + 0x60) = 11;
        *(char *)(d + 0x28) = 3;
        *(float *)(d + 0x30) = 0.3330000043f;
        *(float *)(d + 0x104) = *(float *)(d + 0x324) * 0.2f;
        *(float *)(d + 0x100) = *(float *)(d + 0x324) * 0.3f;
        *(float *)(d + 0x10c) = 0.4f;
        *(float *)(d + 0x110) = 1.57079649f;
        *(float *)(d + 0x130) = 0.52359885f;
        *(int *)(d + 0x138) |= 0x280;
        *(float *)(d + 0x1dc) = func_002A78D8(18.0f, 22.0f) * 0.01745329425f;
        *(short *)(d + 0x1e2) = 120;
        *(short *)(d + 0x1e4) = 180;
        *(char *)(d + 0x1e8) = 7;
        *(char *)(d + 0x1e9) = 6;
        *(float *)(d + 0x1d4) = 3.0f;
        *(float *)(d + 0x1d0) = 0.06666667014f;
        *(float *)(d + 0x328) = func_002A7940();
        if (*(int *)(d + 0x214)) {
            *(int *)(obj + 0x98) = 0;
            *(unsigned short *)(obj + 0x34) = (*(unsigned short *)(obj + 0x34) | 0x41) & 0xefff;
            func_002A7750(obj, 13, 4);
            if (*(unsigned char *)(obj + 0x43) != 10) func_002A7470(obj, 10, 0, 0);
        } else {
            func_002A7750(obj, 1, 0);
            if (*(unsigned char *)(obj + 0x43)) func_002A7470(obj, 0, 0, 0);
        }
        qcopy(d + 0x2e0, obj + 0x10);
    }
    if (*(unsigned char *)(obj + 0x31) && func_00282E48(obj + 0x10, D_L02_001BA500) < 24.0f) {
        func_002A93B0(obj);
        *(char *)(obj + 0x6f) = 22;
    }
    hit = func_002B0ED8(obj, d + 0x50, 0);
    if (hit) {
        func_L02_003CE9A8(obj);
        if (hit >= 4) func_002A7750(obj, 12, -1);
    }
    if ((unsigned int)(*(unsigned char *)(obj + 0x95) - 3) >= 2)
        *(short *)(d + 0x314) = func_002B3BA8(obj, *(int *)(d + 0x210), 16.0f, 0.0f, 0, 0);
    if (*(short *)(d + 0x338)) func_002AFFD8(obj + 0x10, d + 0x300, 0);
}


/* Runs the kind's entry hook: the first when the level flag is set, the second when the third
   argument is clear, the third with the object's own angle otherwise. */
void func_L02_003CE8B0(char *a0, char *a1, int a2) {
    char *p = *(char **)(a0 + 0x68);

    if (D_L02_001A8FF0)
        func_L02_00333438(a0, a1);
    else if (a2 == 0)
        func_L01_00321178(a0, a1);
    else
        func_002B4FF0(a0, (float *)a1, *(float *)(p + 0x31C));
}

/* Clears the two angle words at +0x310 and +0x312 and counts up the +0x96 word, then runs the
   two placement helpers on the sub-object at +0x260. */
void func_L02_003CE908(char *a0) {
    char *p = *(char **)(a0 + 0x68);
    char *q;
    unsigned short n;

    func_00282978(p + 0x310);
    func_00282978(p + 0x312);
    n = *(unsigned short *)(a0 + 0x96);
    if (n <= 0xFFFE)
        *(unsigned short *)(a0 + 0x96) = n + 1;
    q = p + 0x260;
    func_002AEC48(a0, q, 0, 0.03f, 0.3000000119209289550781250f);
    func_002B0990(a0, q, 0, 1.79999995231628417968750f, 1);
}

/* Defined in L02_003CEA28.c. */

/* The entity pool base and the highest group id once more, as the `sda` arrays the twin walk
   func_L02_003CD5B0 reads (02_maktar_nebula/L02_002ED7B0.c): read as X[0] they give retail's
   rotated loop; func_L02_003CD8C0 above reads the same two words as scalars. */
extern u8 *D_L02_001B359C_tbl[] __asm__("D_L02_001B359C") __attribute__((sda));
extern int D_L02_001B35B8_tbl[] __asm__("D_L02_001B35B8") __attribute__((sda));

/* Returns the first entity of the group whose state byte is 0xD, or 0. */
u8 *func_L02_003CEBB8(int group) {
    u16 *p;
    u8 *e;

    for (p = (u16 *)D_L02_001FC060[group];
         (u8)group != 0xFF && group <= D_L02_001B35B8_tbl[0] && p != 0 &&
         ((s16)p[-1] >= 0 || p == (u16 *)D_L02_001FC060[group]);
         p++) {
        e = D_L02_001B359C_tbl[0] + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        if (e[0x20] == 0xD)
            return e;
    }
    return 0;
}

/* Reads the object's basis, clamps its pitch and yaw, and stores them back. */
void func_L02_003CEC70(char *a0) {
    char *p = *(char **)(a0 + 0x68);
    float v[4];
    float x;
    float y;

    func_00282CF0(v, (const float *)(p + 0x1F0), (const float *)(a0 + 0x10));
    func_002AFDD8((unsigned char *)a0, (unsigned char *)v, (unsigned char *)v, 0);
    x = func_00283248(v[0], v[1]);
    *(float *)(p + 0x2C0) = x;
    if (x > 0.7853982448577881f)
        *(float *)(p + 0x2C0) = 0.7853982448577881f;
    else if (x < -0.7853982448577881f)
        *(float *)(p + 0x2C0) = -0.7853982448577881f;
    y = -func_00283248(func_00282E20((char *)v), v[2]);
    *(float *)(p + 0x2C8) = y;
    if (y > 0.523598849773407f)
        *(float *)(p + 0x2C8) = 0.523598849773407f;
    else if (y < -0.523598849773407f)
        *(float *)(p + 0x2C8) = -0.523598849773407f;
}

INCLUDE_ASM("asm/levels", func_L02_003CED70);

/* The callback func_L02_003CEE40 registers; its body is the INCLUDE_ASM below. */
extern void func_L02_003CEFD8(char *);

extern int D_L02_001B30C8 __attribute__((sda));

struct L02PairWord {
    int a;
    int b;
};

extern struct L02PairWord D_L02_001B00C0;

extern float func_00283B98(float, float);

extern int func_00283D38(int, int, float);

extern void func_0029FC20(char *, int, void *);

extern void func_L00_002E6CF0(void *, void *);

/* The kind's private block, at +0x68 of the object and of each entity. */
struct L02Kind330 {
    char pad[0x328];
    float f328;
    float f32C;
    int f330;
};

struct L02Kind330Entity {
    char pad0[0x20];
    unsigned char state;
    char pad1[0x10];
    unsigned char f31;
    char pad2[0x36];
    struct L02Kind330 *obj;
    char pad3[0x3E];
    short type;
};

struct L02Kind330Object {
    char pad0[0x21];
    unsigned char group;
    char pad1[0x46];
    struct L02Kind330 *obj;
    char pad2[0x0C];
    int f78;
};

/* Turns the object's angle and its mirrored scale into its word at +0x78; when the frame
   counter D_L02_001B30C8 differs from the object's word at +0x330, walks the object's group
   and refreshes every live entity of kind 0xA4E, then registers func_L02_003CEFD8. */
void func_L02_003CEE40(struct L02Kind330Object *a0) {
    struct L02Kind330 *o = a0->obj;
    struct L02PairWord v = D_L02_001B00C0;
    float f;
    unsigned short *q;
    struct L02Kind330Entity *e;
    struct L02Kind330 *s0;

    f = func_00283B98(o->f328, 0.20943954586982727f);
    o->f328 = f;
    f = func_00283198(f);
    o->f32C = f * 0.5f + 0.5f;
    a0->f78 = func_00283D38(v.a, v.b, o->f32C);
    if (o->f330 != D_L02_001B30C8) {
        for (q = (unsigned short *)D_L02_001FC060[a0->group];
             a0->group != 0xFF && a0->group <= D_L02_001B35B8 && q != 0 &&
             ((q != 0 && (short)q[-1] >= 0) || q == (unsigned short *)D_L02_001FC060[a0->group]);
             q++) {
            e = (struct L02Kind330Entity *)(D_L02_001B359C + ((*q & 0x7FFF) << 8));
            if (e == 0)
                break;
            if (e->f31 != 0 && e->type == 0xA4E && e->state != 0xFE && e->state != 0xFD) {
                s0 = e->obj;
                func_0029FC20((char *)e, 0, (char *)s0 + 0x220);
                s0->f330 = D_L02_001B30C8;
            }
        }
        func_L00_002E6CF0((void *)func_L02_003CEFD8, a0);
    }
}

/* func_L02_003CEFD8 is in L02_003CEFD8.c. */

typedef struct {
    f32 x;
    f32 y;
} L02Pair_CF1B8;

typedef struct {
    s32 a;
    s32 b;
} L02Range_CF1B8;

extern L02Pair_CF1B8 D_L02_001B00D0;
extern L02Pair_CF1B8 D_L02_001B00D8;
extern L02Range_CF1B8 D_L02_001B00E0;
typedef struct {
    L02Range_CF1B8 r[2];
} L02Ranges_CF1B8;

extern L02Ranges_CF1B8 D_L02_001B00E8;

extern void func_00282C88(void *);
extern int func_002A77E0(int);
extern void *func_002C3150(void *, void *, int, int, int, int, float);
extern void func_002A7A00(void *, float, float);

void func_L02_003CF1B8(u8 *self)
{
    L02Pair_CF1B8 speed = D_L02_001B00D0;
    L02Pair_CF1B8 size = D_L02_001B00D8;
    L02Range_CF1B8 kind = D_L02_001B00E0;
    L02Ranges_CF1B8 count = D_L02_001B00E8;
    f32 vel[4] __attribute__((aligned(16)));
    f32 pos[4] __attribute__((aligned(16)));
    s32 i;

    func_00282C88(vel);
    func_002C3150(self + 0x10, vel, kind.a, func_002A7820(count.r[0].a, count.r[0].b) & 0xFF,
                  func_002A77E0(0xFF) & 0xFF, 0, size.x);
    for (i = 0; i < 1; i++) {
        func_002A7A00(pos, 0.0f, 0.5f);
        func_00282CC0(pos, pos, self + 0x10);
        vel[2] = -(func_002A7878(speed.x, speed.y) * 0.016666668f);
        func_002C3150(pos, vel, kind.b, func_002A7820(count.r[1].a, count.r[1].b) & 0xFF,
                      func_002A77E0(0xFF) & 0xFF, 0, size.y);
    }
}


/* Positions A0 with four angles, then moves it kind six to kind two of length ten. */
void func_L02_003D1588(char *a0) {
    func_002B60B0(a0, 0.0055555556900799274f, 0.03166666626930237f,
                  0.006981317885220051f, 0.8377581834793091f);
    func_002A7750(a0, 6, 3);
    if (*(unsigned char *)(a0 + 0x43) != 2)
        func_002A7470(a0, 2, 0, 10);
}

/* Positions A0 with four angles, then moves it kind ten to kind six of length five. */
void func_L02_003D1610(char *a0) {
    func_002B60B0(a0, 0.0055555556900799274f, 0.06666667014360428f,
                  0.0034906589426100254f, 0.41887909173965454f);
    func_002A7750(a0, 10, 4);
    if (*(unsigned char *)(a0 + 0x43) != 6)
        func_002A7470(a0, 6, 0, 5);
}

/* Builds three vectors, normalises the displacement and returns its dot product. */
float func_L02_003D1820(char *a0, char *a1) {
    TI128 v[3];

    v[0] = *(TI128 *)a1;
    v[1] = *(TI128 *)(a0 + 0xD0);
    func_L02_002F1FB8((char *)&v[2], (char *)&v[0], a0 + 0x10);
    func_00282F20((char *)&v[2], (char *)&v[2], 1.0f);
    return func_00282DB0((char *)&v[1], (char *)&v[2]);
}

/* func_L02_003D1FA0 is in L02_003D1FA0-g8.c for its small-data accesses. */

/* func_L02_003D28E0 lives in the -g8 sibling: it reads five $gp-relative scalars. */

/* When the +0x3C counter of the object at +0x68 is clear, runs the reset, then the dispatch. */
void func_L02_003D29D0(char *a0) {
    char *s0 = a0;

    if (*(BatchA_A17_s32 *)(*(BatchA_A17_s32 *)(s0 + 0x68) + 0x3C) == 0)
        func_L00_003DD2B8();
    func_L00_002E6EF8((void *)func_L02_003D28E0, s0);
}

/* The level's own sound-emitter update: the kind byte at +0x20 of the object picks the
   work, the shared emitter table at D_00188660 holds the listeners. */
void func_L02_003D6BC0(char *a0)
{
    char *s1 = a0;
    char *s2;
    unsigned char buf[0x40];

    s2 = *(char **)(s1 + 0x68);
    func_L02_003D6DF8(a0);

    switch (*(unsigned char *)(s1 + 0x20)) {
    case 2:
        if (*(int *)(s2 + 0xBC) == 0)
            return;
        func_002A7750(s1, 3, -1);
        *(int *)(s2 + 0xB4) = D_L02_001B3FD8;
        break;
    case 1:
        func_L02_003D7140(s1);
        if (*(unsigned char *)(s1 + 0x31) != 0)
            func_L02_003D7040(s1);
        if (*(int *)(s2 + 0xBC) != 0)
            return;
        func_002A7750(s1, 4, -1);
        *(int *)(s2 + 0xB4) = D_L02_001B3FD8;
        break;
    case 3:
        func_00283738(s1 + 0xC0, s2 + 0x80, s1 + 0xC0);
        if (*(int *)(s2 + 0xB4) == D_L02_001B3FD8)
            func_002E5CF8(1, 0, s1);
        func_00283658(buf, s1 + 0xC0);
        func_002AB6D8((float *)buf, s1 + 0xF0);
        func_L00_00323958(s1, s2 + 0x30);
        func_L02_003D7140(s1);
        func_00282948(s2 + 0xB4);
        if (*(int *)(s2 + 0xB4) == 0)
            func_002A7750(s1, 1, -1);
        if (func_002E59B0((int)s1, *(short *)(s2 + 0xC0)) != 0)
            return;
        *(short *)(s2 + 0xC0) = func_002E5CF8(0, 4, s1);
        break;
    case 4:
        func_00283738(s1 + 0xC0, s2 + 0x80, s1 + 0xC0);
        func_00283658(buf, s1 + 0xC0);
        func_002AB6D8((float *)buf, s1 + 0xF0);
        func_L00_00323958(s1, s2 + 0x30);
        func_L02_003D7140(s1);
        func_00282948(s2 + 0xB4);
        if (*(int *)(s2 + 0xB4) != 0)
            return;
        if (*(short *)(s2 + 0xC0) != -1) {
            unsigned char *e = D_00188660 + *(short *)(s2 + 0xC0) * 0x70;

            if (*(int *)(e + 0x88) == (int)s1 && *(unsigned char *)(e + 0x74) != 0)
                func_002E59F8(*(short *)(s2 + 0xC0));
        }
        *(short *)(s2 + 0xC0) = -1;
        func_002A7750(s1, 2, -1);
        break;
    }
}

/* Defined in L02_003D6DF8-helpers.c. */



/* Defined in L02_003D6EE0-g8.c. */

/* Defined in L02_003D7040-g8.c. */

/* func_L02_003D7140 is defined in L02_003D7140-g8.c. */

int func_L02_003D7300(char *a0) {
    return *(int *)(*(char **)(a0 + 0x68) + 0xBC);
}

void func_L02_003D7310(char *a0) {
    BatchA_A17_s32 p = (BatchA_A17_s32)*(BatchA_A17_s32 *)(a0 + 0x68);
    *(BatchA_A17_s32 *)((char *)p + 0xBC) = 1;
}

void func_L02_003D7320(char *a0) {
    *(int *)(*(char **)(a0 + 0x68) + 0xBC) = 0;
}

/* True when any of the three words at +0x10, +0x14, +0x18 of the object at +0x68 is set. */
int func_L02_003D77B8(char *a0) {
    char *p = *(char **)(a0 + 0x68);
    int r = 0;

    if (*(unsigned char *)(a0 + 0x20) == 2) {
        if (*(int *)(p + 0x10) == 0 || *(int *)(p + 0x14) == 0 || *(int *)(p + 0x18) == 0)
            r = 1;
    }
    return r;
}

/* True when any of the three words at +0x10, +0x14, +0x18 of the object at +0x68 is set. */
int func_L02_003D77F8(char *a0) {
    char *p = *(char **)(a0 + 0x68);
    int r = 0;

    if (*(int *)(p + 0x10) || *(int *)(p + 0x14) || *(int *)(p + 0x18))
        r = 1;
    return r;
}

/* Of kind two, reports whether the helper found nothing. */
int func_L02_003D7830(char *a0) {
    int r = 0;

    if (*(unsigned char *)(a0 + 0x20) == 2)
        r = func_L02_003D77F8(a0) == 0;
    return r;
}

/* True when the first free of the three words at +0x10, +0x14, +0x18 of the object at +0x68
   exists; A1 goes there and its kind byte is set to two. */
void func_L02_003D7868(char *a0, char *a1) {
    char *p = *(char **)(a0 + 0x68);

    if (*(int *)(p + 0x10) == 0)
        *(int *)(p + 0x10) = (int)a1;
    else if (*(int *)(p + 0x14) == 0)
        *(int *)(p + 0x14) = (int)a1;
    else if (*(int *)(p + 0x18) == 0)
        *(int *)(p + 0x18) = (int)a1;
    *(char *)(a1 + 0x20) = 2;
}

/* Resets the +0x48 float to one, then moves A0 from kind two to kind three. */
void func_L02_003D78A8(char *a0) {
    *(float *)(a0 + 0x48) = 1.0f;
    if (*(unsigned char *)(a0 + 0x43) != 0)
        func_002A7470(a0, 0, 0, 0);
    func_002A7750(a0, 3, -1);
}

void func_L02_003DED08(void) {
    func_L00_0037E5F0(10000.0f);
}

/* func_L02_003E1A40 is defined in L02_003E1A40-g8.c. */

/* func_L02_003E2150: defined in L02_003C43F0-ring-g8.c. */


/* Copies the byte at +0x40 of the object held at +0x68 over its byte at +0x25. */
void func_L02_003F0628(char *a0) {
    char *p = (char *)*(BatchA_A17_s32 *)(a0 + 0x68);

    *(unsigned char *)(p + 0x25) = *(unsigned char *)(p + 0x40);
}

/* Boundary suspect: the retail body at this row is an epilogue (`addiu $sp,$sp,0x50; nop;
   jr $ra; nop`), so the catalogue row starts inside the function before it. Not a function. */

/* Forwards the first argument with a null second and a third of three. */
/* Its callback callers also supply two integer slots that this body ignores. */
void func_L02_003FC248(void *a0, int unused_a1, int unused_a2) {
    func_002A6C58(a0, 0, 3);
}

/* The two entry scalers live in the -g8 sibling: retail reads the table through $gp. */

INCLUDE_ASM("asm/levels", func_L02_003FE768);

/* Allocates sixteen of sixty with no owner; on success attaches A0 as kind two. */
void func_L02_003FF698(void *a0) {
    if (func_L00_0032EF10(16, 60, 0))
        func_002A7750(a0, 2, -1);
}

/* Aims a 144-byte packet at the level's aim vector: the quaternion comes from the source
   point, the matrix's last row from the same point, and the packet is dispatched. */
void func_L02_003FFC48(char *pos, int a1, int a2, char *a3, int t0, float f12, float f13)
{
    char pkt[144];
    float m[16];
    float quat[4];
    long long r;

    ref_L02_003FFC48_00(pkt);
    r = func_0027C878(a3);

    *(long long *)(pkt + 136) = ((long long)t0 << 2) | 0x8000000040LL;
    *(long long *)(pkt + 128) = 280993940374112LL;
    *(int *)(pkt + 76) = a1 + (a2 << 24);
    *(int *)(pkt + 72) = a1 + (a2 << 24);
    *(int *)(pkt + 68) = a1 + (a2 << 24);
    *(int *)(pkt + 64) = a1 + (a2 << 24);
    *(long long *)(pkt + 112) = 0LL;
    *(long long *)(pkt + 120) = r;

    quat[3] = 0.0f;
    quat[2] = func_00283248(D_L02_001BA3C0.x_140 - *(float *)(pos + 0),
                            D_L02_001BA3C0.y_144 - *(float *)(pos + 4));
    quat[1] = -func_00283248(func_00282E80(pos, (void *)&D_L02_001BA3C0.x_140),
                             D_L02_001BA3C0.z_148 - *(float *)(pos + 8));
    quat[0] = f13;

    func_00283410(m, quat);

    m[12] = *(float *)(pos + 0);
    m[13] = *(float *)(pos + 4);
    m[14] = *(float *)(pos + 8);
    m[15] = 1.0f;

    ref_L02_003FFC48_01(pkt, f12);
    func_00280B90(pkt, m, 0);
}

/* Below 6000 in the low half-word, while the high one reads three. */
void func_L02_004006D8(void) {
    if (D_001A63A8.f72 == 3 && D_001A63A8.f6C < 0x1770)
        func_002B6D28();
}

/* True when the byte at +0x20 is two or more. */
int func_L02_00400B00(unsigned char *a0) {
    return *(unsigned char *)(a0 + 0x20) >= 2;
}


/* The pointer and the five helpers this calls sit at their own addresses in every level
   that has the function, so all six are reached under names that carry no address. */
extern char ref_L02_004012A0_00[] __attribute__((nosda));

extern void ref_L02_004012A0_01(void *, int, int, int, int, int, int, int, int, int, int,
                                int, float, float);
extern void ref_L02_004012A0_02(float *, const float *, const float *);
extern void ref_L02_004012A0_03(void *, void *, float);
extern void ref_L02_004012A0_04(void *, void *, int, int, int, int, float, float, float);
extern void ref_L02_004012A0_05(void *, void *, void *, float);

/* The kind at +0xAA decides the work: the second kind reports itself and leaves, every
   other kind turns the object's own basis, scales it and hands it on. */
void func_L02_004012A0(char *a0) {
    char *s1 = a0;
    char *s2 = *(char **)(a0 + 0x68);
    float v[4];
    short kind = *(short *)(a0 + 0xAA);

    switch (kind) {
    case 0xB1B:
        break;
    case 0xB5A:
        ref_L02_004012A0_01(a0 + 0x10, 0, 0, 0, 0, 20, 45, 1, 1, 0, 0, 0, 0.3f, 20.0f);
        return;
    }
    ref_L02_004012A0_02(v, (const float *)ref_L02_004012A0_00, a0 + 0x10);
    ref_L02_004012A0_03(v, v, 1.0f);
    ref_L02_004012A0_04(a0, a0 + 0x10, 0x10001, 0, 1, 0, 0.25f, *(float *)(s2 + 0x6C), 1.0f);
    ref_L02_004012A0_05(a0, a0 + 0x10, v, 0.0f);
}



/* Defined in L02_00401ED8-g8.c. */

/* Defined in L02_00402300-g8.c. */

/* func_L02_00402440 lives in the -g8 sibling: it reads four $gp-relative scalars. */

int func_L02_004024A0(char *a0) {
    return *(short *)(*(char **)(a0 + 0x68) + 0x30);
}

/* A17-ptr-store-16 freshly exact-verified under family reservation */
void func_L02_004024B0(char *a0) {
    BatchA_A17_s32 p = (BatchA_A17_s32)*(BatchA_A17_s32 *)(a0 + 0x68);
    *(BatchA_A17_BatchAs16 *)((char *)p + 0x30) = 1;
}

void func_L02_004024C0(char *a0) {
    *(short *)(*(char **)(a0 + 0x68) + 0x30) = 0;
}


void func_L02_00404778(void) {
    func_00288CB0(2, 1);
}

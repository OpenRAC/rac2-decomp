#include "include_asm.h"
#include "common.h"

extern void *func_00115484(void *, int, unsigned int);
extern float D_00189EA0[4];
extern float func_L02_002F21C0(void *, void *);
extern int func_L02_004127F8(unsigned char *);
extern int func_L18_003FB500(unsigned char *, int);

/* Frozen Batch A A18-void-store-16; acknowledged claim 4cf4f8b91176606a7af1fd853f7ccd89fa63964199d0883686e46fb6a47255a8. */
typedef unsigned char BatchA_A18_u8;

typedef int BatchA_A18_s32;

typedef short BatchA_A18_BatchAs16;

/* Frozen Batch A A09-cond-select-36; acknowledged claim 3dadb64036892dfb357f8b3f0f7b47fc608b60613dcd8c823ef8df1bc26f7e5b. */
typedef unsigned char BatchA_A09_u8;

typedef int BatchA_A09_s32;

extern void func_00335668(BatchA_A18_u8 *a0, BatchA_A18_s32 a1, BatchA_A18_s32 a2);


extern BatchA_A18_u8 D_0018C0D4;

/* func_L18_002D0C00 */
extern s32 D_L18_001AFBB0 MACRO_ADDR;
extern u8 D_00189E20[];
typedef struct {
    u8 reserved000[0x80];
    float position[4];
    u8 reserved090[0x1D00];
    float positionHistory[32][4];
    u8 reserved1F90[0x3AC];
    float headingHistory[32];
    s32 headingIndex, headingCount, positionIndex, positionCount;
} HeroHistory;
/* Partial input record: only the observed axes and button words are modeled. */
typedef struct {
    u8 reserved000[0x108];
    float horizontal, vertical;
    u8 reserved110[0x90];
    s32 held;
    u8 reserved1A4[12];
    s32 pressed;
} InputRecordPrefix;
extern InputRecordPrefix D_00138180;
extern void func_L00_002B2BD0(void);
extern s32 func_00282978(void *);
extern s32 func_L00_002D3400(void);
extern float func_L00_002B3900(void);
extern float func_00282E20(void *);
extern void func_L18_002D7650(void);
extern void func_00283410(void *, void *);
extern void func_00283388(void *);
extern void func_00283698(void *, void *);
extern void func_L18_002D0850(void);
extern void func_L00_002C2DE8(void);
extern void func_L18_002DEFF8(void);

/* func_L18_002D1998 */
/* Partial probe-collision record: only the hit object, hit count and surface normal are modeled. */
typedef struct { u8 prefix[0x18]; s32 object; s32 count; u8 gap[0x20]; float normal[4]; } MotionCollision;
extern MotionCollision D_L18_001BFC00;
extern float func_L00_002D3A58(void *);
/* func_L00_002D36E0(float *out, s32 flag, float x, float y, float z) elsewhere: this typed
   interleaving keeps both EE argument banks unchanged and gives retail's argument setup order. */
extern void func_L00_002D36E0(float *, float, float, float, s32);
extern void func_00282F20(void *, void *, float);
extern void func_L00_002D3B58(float *, void *, float);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern s32 func_002761F8(void *, void *, s32, void *, void *);
extern s32 func_00278E78(void);
extern float func_L00_002D3EA8(void *);
extern float func_00282DB0(void *, void *);

/* func_L18_002C4000 is defined in L18_002C4000-hero.c. */

/* func_L18_002C41F0 is defined in L18_002C4000-g8.c (this unit has $gp access for it). */

/* func_L18_002CFD68 is defined in L18_002CFD68-qcopy.c. */

/* func_L18_002CFF48 is defined in L18_002CFD68-qcopy.c. */

void func_L18_002D0C00(void)
{
    u8 *base;
    u8 *snapshot;
    u8 *positions;
    s32 index;
    s32 active = D_L18_001AFBB0;
    if (active) {
        func_L00_002B2BD0();
        return;
    }
    snapshot = D_00189E20 + 0x2030;
    qcopy(snapshot, snapshot - 0x1FB0);
    if (D_00138180.held & 3) {
        u8 *hero = snapshot - 0x2030;
        if (*(s16 *)(hero + 0x1454) < 1) *(s16 *)(hero + 0x1454) = 1;
    } else func_00282978(snapshot - 0xBDC);
    base = D_00189E20;
    if (*(s32 *)(base + 0x2294) == 16) *(s16 *)(base + 0x1454) = 0;
    base[0x22C3] = func_L00_002D3400();
    *(float *)(base + 0x1FB0) = D_00138180.horizontal;
    *(float *)(base + 0x1FB4) = D_00138180.vertical;
    *(s32 *)(base + 0x270) = 0;
    *(float *)(base + 0x24BC) = func_L00_002B3900();
    if (func_00282E20(base + 0x1FB0) < 0.25f) {
        /* horizontal and vertical start as the left and down bits. */
        s32 right = (D_00138180.pressed >> 13) & 1;
        s32 horizontal = (D_00138180.pressed >> 15) & 1;
        s32 up = (D_00138180.pressed >> 14) & 1;
        s32 vertical = (D_00138180.pressed >> 12) & 1;
        horizontal = right - horizontal;
        vertical = up - vertical;
        *(float *)(base + 0x1FB0) = (float)horizontal;
        *(float *)(base + 0x1FB4) = (float)vertical;
    }
    *(float *)(base + 0x24B8) = func_L00_002B3900();
    func_L18_002D7650();
    ((HeroHistory *)base)->headingHistory[((HeroHistory *)base)->headingIndex] = *(float *)(base + 0x98);
    *(s32 *)(base + 0x23BC) = (*(s32 *)(base + 0x23BC) + 1) % 32;
    if (++*(s32 *)(base + 0x23C0) > 32) *(s32 *)(base + 0x23C0) = 32;
    index = *(s32 *)(base + 0x23C4);
    positions = base + 0x1D90;
    qcopy_nc(positions + index * 16, (base + 0x80));
    *(s32 *)(base + 0x23C4) = (index + 1) % 32;
    if (++*(s32 *)(base + 0x23C8) > 32) *(s32 *)(base + 0x23C8) = 32;
    func_00283410(base, base + 0x90);
    func_00283388(base + 0x40);
    func_00283698(base + 0x40, base);
    func_L18_002D0850();
    func_L00_002C2DE8();
    func_L18_002DEFF8();
}

void func_L18_002D1998(s32 force)
{
    float start[4], end[4], lowerStart[4], lowerEnd[4];
    float height, reach, angle, dot;
    s32 material;
    if (func_L00_002D3A58(D_00189E20 + 0xF0) < 0.0016666668f) return;
    /* Each block forms its own hero pointer; retail keeps only the %hi part across calls. */
    {
        u8 *hero = D_00189E20;
        height = 0.37f;
        reach = 0.5f;
        if ((u32)(*(s32 *)(hero + 0x229C) - 17) < 2) {
            height = 0.0f;
            reach = 0.7f;
        } else if (hero[0x22B4] == 4) height = 0.35f;
    }
    func_L00_002D36E0(start, 0.0f, 0.0f, height, 1);
    func_L00_002D36E0(lowerStart, 0.0f, 0.0f, height * 0.3f, 1);
    if (force || func_00282E20(D_00189E20 + 0xF0) < 0.01f) {
        func_00282F20(end, D_00189E20, reach);
        func_00282F20(lowerEnd, D_00189E20, reach * 1.4f);
    } else {
        func_L00_002D3B58(end, D_00189E20 + 0xF0, 0.0f);
        func_00282F20(end, end, reach);
        func_00282D30(lowerEnd, end, 1.4f);
    }
    func_00282CC0(end, end, start);
    material = -1;
    func_00282CC0(lowerEnd, lowerEnd, lowerStart);
    {
        u8 *hero = D_00189E20;
        if (func_002761F8(lowerStart, lowerEnd, 2, *(u8 **)(hero + 0x2290), 0) && D_L18_001BFC00.count > 0) material = func_00278E78();
    }
    angle = 0.0f;
    {
        u8 *hero = D_00189E20;
        if (func_002761F8(start, end, 2, *(u8 **)(hero + 0x2290), 0) && D_L18_001BFC00.count > 0) angle = func_L00_002D3EA8(D_L18_001BFC00.normal);
    }
    if (angle >= 0.8726647f || material == 8 || material == 12) {
        u8 *hero = D_00189E20;
        *(s32 *)(hero + 0x270) = D_L18_001BFC00.object;
        func_L00_002D3B58(D_L18_001BFC00.normal, D_L18_001BFC00.normal, 0.0f);
        func_00282F20(D_L18_001BFC00.normal, D_L18_001BFC00.normal, 1.0f);
        dot = func_00282DB0(D_L18_001BFC00.normal, hero + 0xF0);
        if (dot < 0.0f) {
            func_00282D30(D_L18_001BFC00.normal, D_L18_001BFC00.normal, -dot);
            func_00282CC0(hero + 0xF0, hero + 0xF0, D_L18_001BFC00.normal);
        }
    }
}


extern BatchA_A18_s32 ref_L18_002E4090_00(BatchA_A18_s32 a0, BatchA_A18_s32 a1);

void func_L18_002E4090(BatchA_A18_s32 a0) {
    BatchA_A18_s32 e = a0 ? 2 : 1;
    switch (D_0018C0D4) {
    case 0:
        ref_L18_002E4090_00(0, e);
        break;
    case 4:
        ref_L18_002E4090_00(0x8D, e);
        break;
    }
}

/* func_L18_002E42F8 is defined in L18_002E42F8-flags-g8.c. */

/* func_L18_002F1098 is matched in its own unit, L18_002F1098-g8.c. */

extern void func_0027F1D8(void *a0, void *a1, const char *a2);
extern char D_L18_00296510[];

void func_L18_00303A58(void *a0, void *a1) {
    func_0027F1D8(a0, a1, D_L18_00296510);
}

/* func_L18_003044B8 is defined in L18_003044B8.c. */

INCLUDE_ASM("asm/levels", func_L18_00307C60);

BatchA_A18_s32 func_L18_0032B768(BatchA_A18_u8 *s, BatchA_A18_s32 a1, BatchA_A18_s32 a2) {
    BatchA_A18_u8 *p = *(BatchA_A18_u8 **)(s + 0x98);
    BatchA_A18_u8 *q;
    if (p == 0) {
        return 0;
    }
    if (a1 >= (*(BatchA_A18_s32 *)(p + 0x4) >> 5)) {
        return 0;
    }
    p += ((a1 << 5) + 0x10);
    *(p + 2) = (BatchA_A18_u8)a2;
    return 1;
}

extern BatchA_A18_s32 func_002A8AF0(BatchA_A18_s32 a0, BatchA_A18_s32 a1, BatchA_A18_s32 a2);
extern BatchA_A18_s32 D_001FE480[];

/* hands the slot's payload to its handler; the slot table entry holds count then payload */
BatchA_A18_s32 func_L18_0033B628(BatchA_A18_s32 a0, BatchA_A18_s32 a1, BatchA_A18_s32 a2) {
    BatchA_A18_u8 *p;
    if (a1 != -1) {
        p = (BatchA_A18_u8 *)D_001FE480[a1];
        if (p != 0) {
            if (*(BatchA_A18_s32 *)p != 0) {
                return func_002A8AF0(a0, (BatchA_A18_s32)(p + 0x10), *(BatchA_A18_s32 *)p);
            }
        }
    }
    return a2;
}

/* func_L18_0035D238 is defined in L18_0035D238.c. */

extern float func_L18_0035D5F8(void *a0, void *a1, void *a2, char *a3, float f12);
extern BatchA_A18_s32 D_001FE480[];

float func_L18_0035D5A8(void *a0, void *a1, void *a2, BatchA_A18_s32 a3, float f12) {
    if (a3 == -1) {
        return -1.0f;
    }
    a3 = D_001FE480[a3];
    if (a3 == 0) {
        return -1.0f;
    }
    return func_L18_0035D5F8(a0, a1, a2, (char *)a3, f12);
}

extern f32 func_L18_0035D238(void *, void *, void *, void *, void *, f32);
extern f32 func_00282C48(f32);
extern float func_00282E48(char *, void *);

/* GCC 2.9's zero-length trailing array describes the variable point payload. */
typedef struct { s32 count; u8 reserved04[12]; f32 point[0][4]; } PathPoints;

/* Finds the best projected point on the path, breaking near ties by distance. */
f32 func_L18_0035D5F8(void *out, void *origin, void *direction, char *path, float scale) {
    f32 candidate[4];
    f32 best = 100000000000.0f;
    f32 score, distance;
    s32 i = 0;
    PathPoints *points = (PathPoints *)path;
    for (; i < points->count - 1; i++) {
        score = func_L18_0035D238(candidate, origin, direction, points->point[i], points->point[i + 1], scale);
        if (score < best) {
            best = score;
            qcopy(out, candidate);
        } else if (func_00282C48(score - best) < 0.1f) {
            distance = func_00282E48((char *)candidate, origin);
            if (distance < func_00282E48(out, origin)) {
                best = score;
                qcopy(out, candidate);
            }
        }
    }
    return best;
}


/* func_L18_003F50D8 is matched in L18_003F50D8.c (built with -mno-split-addresses). */



INCLUDE_ASM("asm/levels", func_L18_003F5650);

INCLUDE_ASM("asm/levels", func_L18_003F6CA8);

extern void func_002A93B0(void *);
extern void func_L18_003F74B8(void *a0, void *a1);
extern void func_002B0990(char *a0, char *a1, BatchA_A18_s32 a2, BatchA_A18_s32 a3, float f12);
extern char D_L18_001B97C0[];

/* Advances the object's step counter, refreshes the emitter and asks the particle
   system for the new position; the distance test only runs when the flag is set. */
void func_L18_003F7198(void *a0) {
    BatchA_A18_u8 *s0 = (BatchA_A18_u8 *)a0;
    void *s1;
    unsigned short v1;

    v1 = *(unsigned short *)((char *)s0 + 0x96);
    if (v1 <= 0xFFFE) {
        s1 = *(void **)((char *)s0 + 0x68);
        *(unsigned short *)((char *)s0 + 0x96) = v1 + 1;
    } else {
        s1 = *(void **)((char *)s0 + 0x68);
    }
    *(unsigned short *)((char *)s1 + 0x290) = 0;
    if (s0[0x31] != 0) {
        if (func_00282E48((char *)s0 + 0x10, D_L18_001B97C0) < 24.0f) {
            func_002A93B0(s0);
            s0[0x6F] = 0x16;
        }
    }
    if (*(float *)((char *)s0 + 0x10) < 5.0f || *(float *)((char *)s0 + 0x10) > 1018.0f ||
        *(float *)((char *)s0 + 0x14) < 5.0f || *(float *)((char *)s0 + 0x14) > 1018.0f ||
        *(float *)((char *)s0 + 0x18) < 5.0f || *(float *)((char *)s0 + 0x18) > 1018.0f) {
        func_L18_003F74B8(s0, 0);
    }
    func_002B0990((char *)s0, (char *)s1 + 0x2B0, 2, 1, 1.8f);
}

extern float func_00283248(float a, float b);

void func_L18_003F72D8(BatchA_A18_u8 *a0, BatchA_A18_u8 *a1) {
    BatchA_A18_s32 p = *(BatchA_A18_s32 *)(a0 + 0x68);
    *(unsigned short *)((char *)p + 0x290) = 1;
    *(float *)((char *)p + 0x264) =
        func_00283248(*(float *)(a1 + 0x0) - *(float *)(a0 + 0x10),
                      *(float *)(a1 + 0x4) - *(float *)(a0 + 0x14));
}

int func_L18_003F7320(void *arg0) {
    int var_a2;
    void *temp_a1;

    var_a2 = 0;
    temp_a1 = *(void **)((unsigned char *)arg0 + 0x68);
    if (((unsigned short) (*(unsigned short *)((unsigned char *)arg0 + 0x96)) >= 0xF1U) || ((*(short *)((unsigned char *)temp_a1 + 0x294)) >= (*(short *)((unsigned char *)temp_a1 + 0x2A4)))) {
        var_a2 = 1;
    }
    return var_a2;
}

extern float func_00308AD0(BatchA_A18_u8 *a0, BatchA_A18_u8 *a1);
extern BatchA_A18_s32 func_L18_003F8E40(BatchA_A18_u8 *s);

BatchA_A18_s32 func_L18_003F7358(BatchA_A18_u8 *a0, BatchA_A18_u8 *a1) {
    BatchA_A18_s32 r = 0;
    if (func_00308AD0(a0 + 0x10, a1 + 0x10) < 5.0f) {
        r = func_L18_003F8E40(a1) != 0;
    }
    return r;
}

/* func_L18_003F73B8 */
extern float func_00282E80(char *, void *);
extern float func_00283248(float, float);
extern float func_00283C80(float, float);

/* The 1.5707964 spelling is load-bearing: this assembler under-rounds by an ulp
   (1.5707964f, 1.57079637f and even 1.5707963705062866f all encode 0x3FC90FDB,
   retail holds 0x3FC90FDC).  Measured by sweeping spellings, COMPILER-NOTES. */
int func_L18_003F73B8(char *a0, float *a1)
{
    char *s1 = a0;
    float *s0 = a1;
    int r = 0;

    if (*(unsigned char *)(s1 + 0x31) != 0) {
        if (func_00282E80(s1 + 0x10, a1) < 3.2f) {
            if (func_00283C80(*(float *)(s1 + 0xF8),
                             func_00283248(s0[0] - *(float *)(s1 + 0x10),
                                           s0[1] - *(float *)(s1 + 0x14))) < 1.5707965f)
                r = 1;
        }
    }
    return r;
}


extern BatchA_A18_s32 func_002A77E0(BatchA_A18_s32 a0);

extern BatchA_A18_s32 func_L18_003F75E8(BatchA_A18_s32 a0, BatchA_A18_u8 *a1);

/* runs the 0x1E gate and, when it clears, the record query into a local buffer;
   answers whether the query found anything */
BatchA_A18_s32 func_L18_003F7470(BatchA_A18_u8 *a0) {
    BatchA_A18_u8 buf[16];
    BatchA_A18_s32 p;

    if (func_002A77E0(0x1E) == 0) {
        p = *(BatchA_A18_s32 *)(a0 + 0x68);
        return func_L18_003F75E8(*(BatchA_A18_s32 *)((char *)p + 0x25C), buf) != 0;
    }
    return 0;
}

extern void func_002A7750(BatchA_A18_u8 *a0, BatchA_A18_s32 a1, BatchA_A18_s32 a2);
extern void func_0029F338(void *);
extern void func_L01_003E9CF8(void *, int, void *);
extern void func_L18_003F7590(BatchA_A18_u8 *a0);

void func_L18_003F74B8(void *a0, void *a1)
{
    char *s0 = a0;
    int s2 = (int)a1;
    char *s1 = *(char **)(s0 + 0x68);
    short t;

    *(int *)(s1 + 0x20) = 0;
    func_002A7750(s0, 0x13, 0);
    *(unsigned short *)(s0 + 0x34) &= 0xEFFF;
    *(unsigned short *)(s1 + 0x292) -= 1;
    t = *(unsigned short *)(s1 + 0x292);
    if (t != -1 || *(short *)(s1 + 0x296) == 0xE) {
        if (s2 != 0) {
            func_L18_003F7590(s0);
        } else {
            func_L01_003E9CF8(s0, 0, func_L18_003F7590);
        }
    } else {
        if (s2 != 0) {
            func_0029F338(s0);
        } else {
            func_L01_003E9CF8(s0, 0, 0);
        }
    }
}

void func_L18_003F7590(BatchA_A18_u8 *a0) {
    BatchA_A18_s32 p = *(BatchA_A18_s32 *)(a0 + 0x68);
    *(unsigned short *)((char *)p + 0x88) = 0;
    *(BatchA_A18_s32 *)(a0 + 0x98) = 0;
    *(unsigned short *)(a0 + 0x34) =
        (unsigned short)((*(unsigned short *)(a0 + 0x34) & 0xEFFF) | 0x43);
    func_002A7750(a0, 1, 0);
    *(BatchA_A18_s32 *)(a0 + 0x98) = 0;
    *(unsigned short *)(a0 + 0x34) =
        (unsigned short)(*(unsigned short *)(a0 + 0x34) & 0xEFFF);
}

/* The group id lists, the entity bank base and the resident group count. The two scalars are
   `sda` arrays of unknown size: cc1 emits the one-instruction load, which the assembler
   expands absolute (`lui`/`lw`) as retail has it in this -G0 unit. */
extern unsigned short *D_L18_001FB320[];
extern char *D_L18_001B281C[] __attribute__((sda));
extern int D_L18_001B2838[] __attribute__((sda));

/* Counts the entities of kind 0xB69 in state 1 that the group's id list names, stores the count
   through a1 and returns the last of them (0 when there is none). Retail compares the state with
   0xFE and 0xFD before testing it for 1. */
BatchA_A18_s32 func_L18_003F75E8(BatchA_A18_s32 a0, BatchA_A18_u8 *a1) {
    unsigned short *q;
    unsigned char *e;
    unsigned char *r;
    BatchA_A18_s32 *cnt = (BatchA_A18_s32 *)a1;

    *cnt = 0;
    if (a0 == -1)
        return 0;
    r = 0;
    for (q = D_L18_001FB320[a0];
         (a0 & 0xFF) != 0xFF && a0 <= D_L18_001B2838[0] && q != 0 &&
         ((short)q[-1] >= 0 || q == D_L18_001FB320[a0]);
         q++) {
        e = (unsigned char *)(D_L18_001B281C[0] + ((*q & 0x7FFF) << 8));
        if (e == 0)
            break;
        if (*(short *)(e + 0xAA) == 0xB69 && e[0x20] != 0xFE && e[0x20] != 0xFD && e[0x20] == 1) {
            (*cnt)++;
            r = e;
        }
    }
    return (BatchA_A18_s32)r;
}

/* func_L18_003F76F0 lives in L18_003F76F0-copy.c. */

extern void func_00282F20(void *a0, void *a1, float f12);
extern void func_00282CC0(void *a0, void *a1, void *a2);

/* the object's state flags and aim angle are set, then the target is handed
   over to the object's controller */
void func_L18_003F7818(BatchA_A18_u8 *s2, BatchA_A18_u8 *s3, BatchA_A18_s32 s7) {
    float local[4];
    BatchA_A18_u8 *s4;
    BatchA_A18_s32 *p;
    BatchA_A18_s32 v1;
    BatchA_A18_u8 state;

    s4 = *(BatchA_A18_u8 **)(s2 + 0x68);
    state = s2[0x20];
    if (state == 1) {
        p = *(BatchA_A18_s32 **)(s2 + 0x24);
        *(unsigned short *)(s2 + 0x34) =
            (unsigned short)((*(unsigned short *)(s2 + 0x34) & 0xFFBE) | 0x1000);
        v1 = p[4];
        *(unsigned short *)(s2 + 0x34) =
            (unsigned short)(*(unsigned short *)(s2 + 0x34) & 0xFFFD);
        *(BatchA_A18_s32 *)(s2 + 0x98) = v1;
        s4[0x2E] = state;
        s2[0x7F] = 0;
        *(float *)(s4 + 0x20) = (float)*(short *)(s4 + 0x24);
        func_00282F20(local, s3 + 0xC0, -0.5f);
        func_00282CC0(s2 + 0x10, s3 + 0x10, local);
        if (s7 != 0) {
            func_00282F20(local, s3 + 0xD0, 0.5f);
        } else {
            func_00282F20(local, s3 + 0xD0, -0.5f);
        }
        func_00282CC0(s2 + 0x10, s3 + 0x10, local);
        *(float *)(s2 + 0xF8) =
            func_00283248(*(float *)(s3 + 0x10) - *(float *)(s2 + 0x10),
                          *(float *)(s3 + 0x14) - *(float *)(s2 + 0x14));
    }
    *(BatchA_A18_s32 *)(s4 + 0x258) = (BatchA_A18_s32)s3;
    func_002A7750(s2, 0xB, 2);
    func_L18_003F8E30((BatchA_A18_u8 *)*(BatchA_A18_s32 *)(s4 + 0x258));
}

/* func_L18_003F7988 lives in L18_003F7988-copy.c. */

void func_L18_003F7A08(BatchA_A18_u8 *a0) {
    BatchA_A18_u8 *s0 = a0;
    BatchA_A18_s32 p;
    if (s0[0x95] != 1) {
        return;
    }
    p = *(BatchA_A18_s32 *)(s0 + 0x68);
    if (*(BatchA_A18_s32 *)(p + 0x258) != 0) {
        func_00335668(s0, 0xB, 2);
    } else if (*(BatchA_A18_s32 *)(p + 0x278) != -1) {
        func_00335668(s0, 0xD, 2);
    } else {
        func_00335668(s0, 0xC, 2);
    }
    func_00335668(s0, 7, -1);
}

extern void func_L18_003F7A08(BatchA_A18_u8 *a0);
void func_L18_003F7A88(BatchA_A18_u8 *a0) {
    if (a0[0x95] == 1) {
        func_L18_003F7A08(a0);
    }
}

/* func_L18_003F7AB8 is defined in L18_002C4000-g8.c (this unit has $gp access for it). */

extern void func_L18_003FB5E8(void *a0, void *a1);
extern void func_00282F20(void *a0, void *a1, float f12);
extern void func_00282CC0(void *a0, void *a1, void *a2);
extern float func_002A89A8(void *a0, BatchA_A18_s32 a1, float f12);
extern void func_002833F0(char *a, char *b);

/* Moves the object's state word, refreshes the two transform matrices through the
   shared helpers and writes the measured distance back into the object. */
void func_L18_003F8D28(void *a0, void *a1, void *a2) {
    char scratch[16];
    char mat[16];
    unsigned short v1;
    void *p;
    void *s4;
    void *v;
    float f;

    v1 = *(unsigned short *)((char *)a0 + 0x34);
    p = *(void **)((char *)a0 + 0x24);
    v1 = (unsigned short)((v1 & 0xFFBE) | 0x1000);
    *(unsigned short *)((char *)a0 + 0x34) = v1;
    v = *(void **)((char *)p + 0x10);
    *(void **)((char *)a0 + 0x98) = v;
    func_002A7750((BatchA_A18_u8 *)a0, 5, 2);
    s4 = *(void **)((char *)a0 + 0x68);
    *(void **)((char *)s4 + 0x74C) = a2;
    if (a1 != 0) {
        func_L18_003FB5E8(a1, mat);
        func_00282F20(scratch, (char *)a1 + 0xD0, -0.3f);
        func_00282CC0((char *)a0 + 0x10, mat, scratch);
        *(float *)((char *)a0 + 0x18) = func_002A89A8((char *)a0 + 0x10, 0, 0.5f);
        f = func_00283248(*(float *)mat - *(float *)((char *)a0 + 0x10),
                           *(float *)(mat + 4) - *(float *)((char *)a0 + 0x14));
        *(float *)((char *)a0 + 0xF8) = f;
        func_002833F0((char *)a0 + 0xC0, (char *)a0 + 0xF0);
        *(void **)((char *)s4 + 0x750) = a1;
        *(BatchA_A18_u8 *)((char *)a0 + 0x7F) = 0;
    }
}

/* A18-void-store-16 freshly exact-verified under family reservation */
void func_L18_003F8E30(BatchA_A18_u8 *s) {
    BatchA_A18_s32 p = *(BatchA_A18_s32 *)(s + 0x68);
    *(BatchA_A18_BatchAs16 *)((char *)p + 0x768) = 1;
}

/* A18-cond-select twin of 003F8E80: two independent state gates */
BatchA_A18_s32 func_L18_003F8E40(BatchA_A18_u8 *s) {
    BatchA_A18_s32 r = 0;
    if ((s[0x20] == 5 && s[0xBC] == 1) || (s[0x20] == 3 && s[0x94] == 5)) {
        r = 1;
    }
    return r;
}

/* A09-cond-select-36 freshly exact-verified under family reservation */
BatchA_A09_s32 func_L18_003F8E80(BatchA_A09_u8 *s) {
    BatchA_A09_s32 r = 0;
    if (s[0x20] == 6) { r = (s[0xBC] == 2); }
    return r;
}

/* func_L18_003F8EA8 is defined in L18_003F8EA8-qcopy.c. */

extern void func_00335388(BatchA_A18_u8 *a0, BatchA_A18_s32 a1, BatchA_A18_s32 a2,
                          BatchA_A18_s32 a3);

void func_L18_003F8FA8(BatchA_A18_u8 *a0) {
    BatchA_A18_s32 p = *(BatchA_A18_s32 *)(a0 + 0x68);
    func_00335388(a0, 0, 0, 3);
    *(BatchA_A18_s32 *)(a0 + 0x48) = 0;
    *(unsigned short *)((char *)p + 0x98) = 0;
    *(BatchA_A18_s32 *)(a0 + 0x98) = 0;
    *(unsigned short *)(a0 + 0x34) =
        (unsigned short)((*(unsigned short *)(a0 + 0x34) | 0x41) & 0xEFFF);
    func_00335668(a0, 1, 1);
    *(BatchA_A18_s32 *)(a0 + 0x98) = 0;
}

INCLUDE_ASM("asm/levels", func_L18_003F9DA0);


extern void func_L18_003FC9B8(unsigned char *a0);
extern void func_L18_003F7988(unsigned char *a0);

/* Slot i of the object's eight group ids (the words at +0x60). Retail rebuilds the slot address
   at every test of the walk, which is what an inline helper expanded in place does. */
static __inline__ int L18_GroupId(unsigned char *p, int i) {
    int off = i << 2;
    int *ids = (int *)(p + 0x60);
    return *(int *)((char *)ids + off);
}

/* Walks the id list of each of the object's eight groups and, for every entity in it, calls the
   handler of its kind (0xD5C, 0x11CC, 0xD9B, 0x11CF or 0xB69), clears the entity's word at +0x98
   and sets bits 0 and 1 of its flags at +0x34; then stores -1 at +0x88 of the object. */
void func_L18_003F9FB0(unsigned char *a0) {
    unsigned char *p = *(unsigned char **)(a0 + 0x68);
    unsigned short *q;
    unsigned char *e;
    int i;

    for (i = 0; i < 8; i++) {
        for (q = D_L18_001FB320[L18_GroupId(p, i)];
             (L18_GroupId(p, i) & 0xFF) != 0xFF && L18_GroupId(p, i) <= D_L18_001B2838[0] &&
             q != 0 && ((short)q[-1] >= 0 || q == D_L18_001FB320[L18_GroupId(p, i)]);
             q++) {
            e = (unsigned char *)(D_L18_001B281C[0] + ((*q & 0x7FFF) << 8));
            if (e == 0)
                break;
            if (*(short *)(e + 0xAA) == 0xD5C || *(short *)(e + 0xAA) == 0x11CC ||
                *(short *)(e + 0xAA) == 0xD9B || *(short *)(e + 0xAA) == 0x11CF) {
                func_L18_003FC9B8(e);
            } else if (*(short *)(e + 0xAA) == 0xB69) {
                func_L18_003F7988(e);
            }
            *(int *)(e + 0x98) = 0;
            *(unsigned short *)(e + 0x34) |= 3;
        }
    }
    *(int *)(p + 0x88) = -1;
}

INCLUDE_ASM("asm/levels", func_L18_003FA180);

INCLUDE_ASM("asm/levels", func_L18_003FA7C0);

BatchA_A18_s32 func_L18_003FA8E0(BatchA_A18_u8 *s) {
    BatchA_A18_s32 p = *(BatchA_A18_s32 *)(s + 0x68);
    if (*(short *)((char *)p + 0xA8) > 0) {
        *(unsigned short *)((char *)p + 0xA8) =
            (unsigned short)(*(unsigned short *)((char *)p + 0xA8) - 1);
        return 1;
    }
    return 0;
}

void func_L18_003FA908(BatchA_A18_u8 *s) {
    BatchA_A18_s32 p = *(BatchA_A18_s32 *)(s + 0x68);
    *(unsigned short *)((char *)p + 0xA8) =
        (unsigned short)(*(unsigned short *)((char *)p + 0xA8) + 1);
}

/* Each scan reads the current slot id again when advancing its group iterator. */
static __inline__ int L18_SelectionGroupId(char *p, int i, int base) {
    int off = i << 2;
    int *groups = (int *)(p + base);
    return *(int *)((char *)groups + off);
}

/* Selects the source, secondary member and target from the owner's three group
   lists. The first target scan prefers entries passing the flag and distance tests. */
int func_L18_003FA920(char *owner, int slot) {
    char *secondary[2];
    char *state = *(char **)(owner + 0x68);
    char *source = 0;
    char *selected = 0;
    char *entity;
    int i;

    func_00115484(secondary, 0, 8);
    {
        unsigned short *entry;
        for (entry = D_L18_001FB320[L18_SelectionGroupId(state, slot, 0)];
             (L18_SelectionGroupId(state, slot, 0) & 0xff) != 0xff &&
             L18_SelectionGroupId(state, slot, 0) <= D_L18_001B2838[0] && entry != 0 &&
             ((short)entry[-1] >= 0 ||
              entry == D_L18_001FB320[L18_SelectionGroupId(state, slot, 0)]); entry++) {
            entity = D_L18_001B281C[0] + (*entry & 0x7fff) * 0x100;
            if (entity == 0) break;
            if (entity != 0 && *(unsigned char *)(entity + 0x20) != 0xfe &&
                *(unsigned char *)(entity + 0x20) != 0xfd &&
                (*(unsigned short *)(entity + 0x34) & 1) != 0) {
                source = entity;
                break;
            }
        }
    }
    if (source == 0) return 0;
    for (i = 0; i < 1; i++) {
        {
            unsigned short *entry;
            for (entry = D_L18_001FB320[L18_SelectionGroupId(state, slot, 0x20)];
                 (L18_SelectionGroupId(state, slot, 0x20) & 0xff) != 0xff &&
                 L18_SelectionGroupId(state, slot, 0x20) <= D_L18_001B2838[0] && entry != 0 &&
                 ((short)entry[-1] >= 0 ||
                  entry == D_L18_001FB320[L18_SelectionGroupId(state, slot, 0x20)]); entry++) {
                entity = D_L18_001B281C[0] + (*entry & 0x7fff) * 0x100;
                if (entity == 0) break;
                if (entity != secondary[0] && entity != 0 &&
                    *(unsigned char *)(entity + 0x20) != 0xfe &&
                    *(unsigned char *)(entity + 0x20) != 0xfd &&
                    (*(unsigned short *)(entity + 0x34) & 1) != 0) {
                    secondary[i] = entity;
                    break;
                }
            }
        }
    }
    if (secondary[0] == 0) return 0;
    {
        unsigned short *entry;
        for (entity = 0, entry = D_L18_001FB320[L18_SelectionGroupId(state, slot, 0x10)];
             (L18_SelectionGroupId(state, slot, 0x10) & 0xff) != 0xff &&
             L18_SelectionGroupId(state, slot, 0x10) <= D_L18_001B2838[0] && entry != 0 &&
             ((short)entry[-1] >= 0 ||
              entry == D_L18_001FB320[L18_SelectionGroupId(state, slot, 0x10)]); entry++) {
            entity = D_L18_001B281C[0] + (*entry & 0x7fff) * 0x100;
            if (entity == 0) break;
            if (*(unsigned char *)(entity + 0x31) != 0 &&
                func_L02_002F21C0(D_00189EA0, entity + 0x10) > 16.0f &&
                func_L02_004127F8((unsigned char *)entity) == 0) {
                selected = entity;
                break;
            }
        }
    }
    if (selected == 0) {
        {
            unsigned short *entry;
            for (entity = 0, entry = D_L18_001FB320[L18_SelectionGroupId(state, slot, 0x10)];
                 (L18_SelectionGroupId(state, slot, 0x10) & 0xff) != 0xff &&
                 L18_SelectionGroupId(state, slot, 0x10) <= D_L18_001B2838[0] && entry != 0 &&
                 ((short)entry[-1] >= 0 ||
                  entry == D_L18_001FB320[L18_SelectionGroupId(state, slot, 0x10)]); entry++) {
                entity = D_L18_001B281C[0] + (*entry & 0x7fff) * 0x100;
                if (entity == 0) break;
                if (func_L02_004127F8((unsigned char *)entity) == 0) {
                    selected = entity;
                    break;
                }
            }
        }
        if (selected == 0) goto fail;
    }
    func_L18_003F8D28(source, entity, (void *)L18_SelectionGroupId(state, slot, 0x10));
    func_L18_003F7818((unsigned char *)secondary[0], (unsigned char *)source, 0);
    func_L18_003FB500((unsigned char *)selected, 1);
    return 1;
fail:
    return 0;
}

INCLUDE_ASM("asm/levels", func_L18_003FAE50);

/* func_L18_003FB500 lives in L18_003FB500.c. */

/* func_L18_003FB5E8 is matched in its own unit, src/levels/shared/L18_003FB5E8-qcopy.c (-frac2-qcopy). */

void func_L18_003FC958(BatchA_A18_u8 *a0, BatchA_A18_s32 a1) {
    if (a1 != 0) {
        func_00335668(a0, 3, -1);
    } else {
        func_00335668(a0, 2, -1);
    }
    *(BatchA_A18_s32 *)(a0 + 0x98) = 0;
    *(unsigned short *)(a0 + 0x34) =
        (unsigned short)((*(unsigned short *)(a0 + 0x34) | 0x41) & 0xEFFF);
}

/* func_L18_003FC9B8 lives in L18_003F7988-copy.c. */

/* func_L18_003FCA38 is defined in L18_003FCA38-g8.c. */



/* func_L18_003FCC48 lives in L18_003FCC48-particles.c. */

/* func_L18_003FCD70 lives in L18_003FCD70-particles.c. */


/* store -1 into field 0x74 of the object at s[0x68] */
void func_L18_003FE010(BatchA_A18_u8 *s) {
    BatchA_A18_s32 p = *(BatchA_A18_s32 *)(s + 0x68);
    *(BatchA_A18_s32 *)((char *)p + 0x74) = -1;
}

void func_L18_003FE020(BatchA_A18_u8 *s) {
    BatchA_A18_s32 p = *(BatchA_A18_s32 *)(s + 0x68);
    *(BatchA_A18_s32 *)((char *)p + 0x74) = 0;
}

INCLUDE_ASM("asm/levels", func_L18_00426AB0);

extern void func_0033A0B0(BatchA_A18_u8 *a0, BatchA_A18_u8 *a1);
extern void func_0032D118(BatchA_A18_u8 *a0, BatchA_A18_s32 a1, BatchA_A18_s32 a2,
                          BatchA_A18_s32 a3);

void func_L18_00426D98(BatchA_A18_u8 *a0) {
    BatchA_A18_s32 p = *(BatchA_A18_s32 *)(a0 + 0x68);
    *(unsigned short *)((char *)p + 0x50) = 0;
    *(unsigned short *)((char *)p + 0x52) = 1;
    func_0033A0B0(a0, (BatchA_A18_u8 *)p + 0x50);
    *(BatchA_A18_u8 *)((char *)p + 0x54) = 0x80;
    *(BatchA_A18_u8 *)((char *)p + 0x55) = 0x80;
    *(BatchA_A18_u8 *)((char *)p + 0x56) = 0x80;
    func_0032D118(a0, 0x80, 0x80, 0x80);
}


/* func_L18_00426E48 lives in L18_00426E48-g8.c. */

extern void func_002EC9C8(BatchA_A18_u8 *a0, BatchA_A18_s32 a1);

void func_L18_00426F28(BatchA_A18_u8 *a0, BatchA_A18_s32 a1, BatchA_A18_s32 a2, float f12) {
    if (a0[0xBC] == 0) {
        if (a0[0x43] != a1) {
            func_00335388(a0, a1, a2, (BatchA_A18_s32)f12);
        }
    } else {
        func_002EC9C8((BatchA_A18_u8 *)a1, a2);
    }
}

extern void *func_002B60B0(BatchA_A18_u8 *, float, float, float, float);
extern void func_00282948(void *a0);

/* the object's scale angles are re-submitted in degrees, then the matrix is rebuilt */
void func_L18_00426F78(BatchA_A18_u8 *a0) {
    BatchA_A18_u8 *p = *(BatchA_A18_u8 **)(a0 + 0x68);
    if (a0[0x21] != 0xFF) {
        if (*(BatchA_A18_u8 *)(p + 0x39F) != 0) {
            func_002B60B0(a0, 0.00027777778450399637f * *(float *)(p + 0x3C4),
                          0.01666666753590107f * *(float *)(p + 0x3C0),
                          4.848137450608192e-06f * *(float *)(p + 0x3D4),
                          0.0002908882452175021f * *(float *)(p + 0x3D0));
            func_00282948(*(void **)(p + 0x388));
        }
    }
    *(BatchA_A18_u8 *)(p + 0x39F) = 0;
}

extern void func_00282948(void *a0);

void func_L18_00427010(BatchA_A18_u8 *a0) {
    BatchA_A18_s32 p = *(BatchA_A18_s32 *)(a0 + 0x68);
    if (a0[0x21] != 0xFF && *(BatchA_A18_u8 *)(p + 0x3B0) != 0) {
        func_00282948(*(void **)(p + 0x3AC));
    }
    *(BatchA_A18_u8 *)(p + 0x3B0) = 0;
}

void func_L18_00427058(BatchA_A18_u8 *a0) {
    BatchA_A18_s32 p = *(BatchA_A18_s32 *)(a0 + 0x68);
    BatchA_A18_s32 q;
    if (a0[0x21] == 0xFF) {
        return;
    }
    if (*(BatchA_A18_u8 *)(p + 0x3B0) != 0) {
        return;
    }
    q = *(BatchA_A18_s32 *)(p + 0x3AC);
    (*(BatchA_A18_s32 *)q)++;
    *(BatchA_A18_u8 *)(p + 0x3B0) = 1;
}

extern BatchA_A18_s32 func_L09_0033E690(BatchA_A18_u8 *a0, BatchA_A18_s32 a1, float f12);
extern BatchA_A18_s32 func_L09_00329178(BatchA_A18_u8 *a0, BatchA_A18_s32 a1,
                                        BatchA_A18_s32 a2, BatchA_A18_s32 a3);

/* re-seats the object on a new animation; -1 means "leave it to the level" */
BatchA_A18_s32 func_L18_00427130(BatchA_A18_u8 *a0, BatchA_A18_s32 a1, BatchA_A18_s32 a2) {
    BatchA_A18_u8 *p = *(BatchA_A18_u8 **)(a0 + 0x68);
    BatchA_A18_s32 r;
    *(BatchA_A18_s32 *)(p + 0x38C) = a1;
    if (a1 == -1) {
        *(BatchA_A18_BatchAs16 *)(p + 0x1C8) = (BatchA_A18_BatchAs16)a1;
        return -1;
    }
    r = func_L09_0033E690(a0 + 0x10, a1, 0.0f);
    if (func_L09_00329178(a0, a1, a2, r) != 0) {
        return *(short *)(p + 0x1C8);
    }
    *(unsigned short *)(p + 0x1C8) = 0;
    return -1;
}

extern BatchA_A18_s32 func_L09_0033E658(void *a0);

BatchA_A18_s32 func_L18_004271C0(BatchA_A18_u8 *a0) {
    BatchA_A18_s32 p = *(BatchA_A18_s32 *)(a0 + 0x68);
    if (*(short *)((char *)p + 0x1CA) != 0) {
        *(BatchA_A18_BatchAs16 *)((char *)p + 0x1CA) = 0;
        return 0;
    }
    *(BatchA_A18_BatchAs16 *)((char *)p + 0x1CA) =
        (BatchA_A18_BatchAs16)func_L09_0033E658(*(void **)((char *)p + 0x38C));
    return 1;
}

/* func_L18_00427208 is defined in L18_00427208-qcopy.c. */

/* func_L18_004273F0 is matched in L18_004273F0-g8.c (built with -frac2-qcopy). */

INCLUDE_ASM("asm/levels", func_L18_00427688);

/* func_L18_00427B48: 144 bytes against retail's 148; the chain pointer and the
   stored 1 take each other's register. Deposited in nonmatching/levels/. */

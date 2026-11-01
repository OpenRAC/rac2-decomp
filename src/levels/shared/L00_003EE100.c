#include "include_asm.h"
#include "common.h"

/* func_L00_003F8280: a 16-byte vector with a quadword view, the 4-row basis the vertex
   transform reads (three axes and a position) and the 144-byte packet with a quad's vertices,
   colours and UVs. */
typedef unsigned int QuadWord __attribute__((mode(TI)));
typedef union { QuadWord word; float v[4]; } Vector;
typedef struct { Vector row[3]; Vector position; } Frame;
typedef struct {
    Vector vertex[4];
    unsigned int color[4];
    float uv[4][2];
    long f70, f78, f80, flags;
} RenderPacket;

extern Vector D_0018A0E0;
extern Vector D_L00_001AA310[4];
extern void func_00281DE8(void *, int, int, int);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_002833F0(void *, void *);
extern void func_00283738(void *, void *, void *);
extern void func_002830C0(void *, void *, void *);
extern void func_002FC560(unsigned int, unsigned long long);
extern void func_0027C768(int, float *, float *);
extern int func_002A77E0(int);
extern float func_002A7878(float, float);

/* The 0x50-stride record table both walkers below scan; the retail reaches it through $gp in
   ordinary flow, which the assembler only selects from a bare symbol operand. */
extern char *D_L00_001B2BB4_1 __attribute__((sda));

extern void func_002833F0_1(char *a, char *b);

extern float func_00283198_1(float value);

extern void func_00282D30_3(char *a, char *b, float value);

extern float func_00283B98_3(float value, float scale);

extern int func_002ABB78(char *object);

extern float *func_002AB1F0(char *object);

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

extern void func_002FDBD8_5(float scale, Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context,
                                    float *vector, int mode);

extern void func_00282D30_2(char *dst, char *src, float scale);

extern void func_00282CF0_9(char *local, char *first, char *second);

extern void func_00282CC0_15(char *target, char *first, char *local);

#ifndef RAC2_T_VEC16_FC936841D
#define RAC2_T_VEC16_FC936841D
typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec16_Fc936841d;
#endif

extern void func_00282F20_1(char *, char *, float);

extern void func_00282DD8(char *, char *, char *);

extern int func_002B4038(int, int);

extern void func_0029F338_1(char *);

extern void func_L00_003F5B10(char *);

extern void func_L00_003F6308(char *);

extern void func_L00_003F6B10(char *);

extern char *func_L00_0032A088(int a0, int a1);

extern char *func_L00_0032A0B8(int a0, int a1);

extern int func_00282978(char *a0);

extern float func_00283B98(float a0, float a1);

#ifndef RAC2_T_NODE16_FE48725C6
#define RAC2_T_NODE16_FE48725C6
typedef struct Node16_Fe48725c6 Node16_Fe48725c6;
#endif

#ifndef RAC2_T_NODE104_FE48725C6
#define RAC2_T_NODE104_FE48725C6
typedef struct Node104_Fe48725c6 Node104_Fe48725c6;
#endif

#ifndef RAC2_T_NODE24_FE48725C6
#define RAC2_T_NODE24_FE48725C6
typedef struct Node24_Fe48725c6 Node24_Fe48725c6;
#endif

struct Node16_Fe48725c6 {
    short h0;
    unsigned char pad2[2];
    unsigned char b4;
    unsigned char b5;
    unsigned char b6;
};

struct Node104_Fe48725c6 {
    unsigned char pad0[16];
    Node16_Fe48725c6 *p16;
};

struct Node24_Fe48725c6 {
    unsigned char pad0[52];
    unsigned short h52;
    unsigned char pad54[50];
    Node104_Fe48725c6 *p104;
};

#ifndef RAC2_T_OBJ_FE48725C6
#define RAC2_T_OBJ_FE48725C6
typedef struct Obj_Fe48725c6 {
    unsigned char pad0[4];
    union {
        int f4;
        struct {
            unsigned char b4;
            unsigned char b5;
            short h6;
        } b;
    } u;
    unsigned char pad8[12];
    Node24_Fe48725c6 *f24;
} Obj_Fe48725c6;
#endif

extern void func_002A0488_1(Node24_Fe48725c6 *a, unsigned char b, unsigned char c, unsigned char d);

/* Family 40487154aa250cc8: fixed-field addend writes into one resource record. */
void func_L00_003EE100(char *object)
{
    char *data;
    float x;
    float y;
    float z;

    data = *(char **)(object + 104);
    func_002833F0_1(object + 192, object + 240);
    x = func_00283198_1(*(float *)(data + 4)) * 0.15f + 0.35000002f;
    y = func_00283198_1(*(float *)(data + 8)) * 0.15f + 0.35000002f;
    z = func_00283198_1(*(float *)(data + 12)) * 0.15f + 0.35000002f;
    func_00282D30_3(object + 192, object + 192, x);
    func_00282D30_3(object + 208, object + 208, y);
    func_00282D30_3(object + 224, object + 224, z);
    *(float *)(data + 4) = func_00283B98_3(*(float *)(data + 4), 0.5f);
    *(float *)(data + 8) = func_00283B98_3(*(float *)(data + 8), 0.5f);
    *(float *)(data + 12) = func_00283B98_3(*(float *)(data + 12), 0.5f);
}

/* calls two guards and returns 1 only when both succeed and the object's float field is not positive */
int func_L00_003EE228(char *object)
{
    float *p;

    if (func_002ABB78(object) != 0)
        return 0;
    p = func_002AB1F0(object);
    if (p == 0)
        return 0;
    if (0.0f < *p)
        return 0;
    return 1;
}


/* When the context flag at offset 0x24 is nonzero, pass scale 1.0, the context, its vector at offset 0x10 and mode zero to the bound helper; original game role is unknown. */
void func_L00_003EE8E8(Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner *owner)
{
    Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context = owner->context_68;
    if (context->active_24 != 0) {
        func_002FDBD8_5(1.0f, context, context->vector_10, 0);
    }
}

/* func_L00_003EED10 uses its dedicated quadword-copy profile. */

/* func_L00_003EEE20 is defined in L00_003EEE20-g.c. */


/* func_L00_003EF3E0 uses its dedicated quadword-copy profile. */

extern int D_L00_001B0838 __attribute__((sda));

void func_L00_003EF548(void)
{
    D_L00_001B0838 = 0;
}

extern int D_L00_001B0838 __attribute__((sda));

extern int D_L00_001B2BB4 __attribute__((sda));

void func_L00_003EF550(void)
{
    D_L00_001B2BB4 = 0;
    D_L00_001B0838 = 0;
}


extern int func_00283DB8(char *local, float value);

/* func_L00_003EFA00 is in L00_003EFA00-qcopy.c (its own file: the quadword-copy profile). */

/* func_L00_003EFA98 and func_L00_003EFD00 are in L00_003EE100-g8.c (their tuning words are
   read through $gp). */

typedef int TI128_FF58 __attribute__((mode(TI)));
typedef struct { TI128_FF58 position, normal, velocity; char *owner; int value, phase; float scale; int first, last; } EffectRecord_FF58;
extern EffectRecord_FF58 *D_L00_001B2BB4_2[] __attribute__((sda));
extern void func_00282F20_2(char *, char *, float);
extern void func_00282CC0_2(char *, char *, char *);
extern void func_00282DD8_2(char *, char *, char *);
extern float func_002A7940(void);
extern void func_L00_003F0198_2(char *, int, float, float, int);
extern float func_00283B98_4(float, float);

/* The record is reached through three handles (entry for the header and the first trail,
   shape for the position/velocity block and the second): that is what reproduces retail's
   saved-register assignment. */
void func_L00_003EFF58(char *owner, int value, char *direction, char *position, float scale)
{
    TI128_FF58 local;
    EffectRecord_FF58 *base = D_L00_001B2BB4_2[0];
    EffectRecord_FF58 *record;
    char *velocity;
    char *normal;
    EffectRecord_FF58 *entry;
    int slot;
    int step;
    EffectRecord_FF58 *shape;
    float angle;

    slot = -1;
    while (++slot <= 0) {
        velocity = (char *)&base[slot].velocity;
        record = base + slot;
        normal = (char *)&base[slot].normal;
        entry = record;
        if (entry->owner != 0)
            continue;
        entry->value = value;
        record->scale = scale;
        entry->owner = owner;
        record->phase = 0;
        shape = record;
        qcopy(&shape->position, position);
        qcopy(velocity, direction);
        ((float *)&shape->velocity)[2] = *(float *)(owner + 0x18);
        func_00282F20_2((char *)&local, position, 2.0f);
        func_00282CC0_2((char *)&local, (char *)&local, velocity);
        func_00282DD8_2(normal, velocity, (char *)&local);
        angle = func_002A7940();
        for (step = 99; step >= 0; step--) {
            func_L00_003F0198_2((char *)entry, 2, angle, 0.0f, 0);
            func_L00_003F0198_2((char *)shape, 0, angle, 0.0f, 0);
            angle = func_00283B98_4(angle, 0.06346652f);
        }
        entry->first = 0;
        entry->last = 0;
        break;
    }
}

extern int func_00282948(char *p);

extern void func_L00_003F0680(char *rec);

void func_L00_003F00A0(char *obj)
{
    char *rec;
    int i;
    int offset;

    offset = 0;
    i = 0;
    do {
        i--;
        rec = (char *)(offset + (int)D_L00_001B2BB4_1);
        if (*(int *)(rec + 0x30) == (int)obj) {
            if (func_00282948(rec + 0x34) != 0 && *(int *)(rec + 0x38) == 0)
                *(int *)(rec + 0x30) = 0;
            func_L00_003F0680(rec);
        }
        offset += 0x50;
    } while (i >= 0);
}

extern void func_L00_003F09A0(char *rec);

void func_L00_003F0130(char *obj)
{
    char *rec;
    int i;
    int offset;

    offset = 0;
    i = 0;
    do {
        i--;
        rec = (char *)(offset + (int)D_L00_001B2BB4_1);
        if (*(int *)(rec + 0x30) == (int)obj)
            func_L00_003F09A0(rec);
        offset += 0x50;
    } while (i >= 0);
}

INCLUDE_ASM("asm/levels", func_L00_003F0198);


extern char *D_L00_001B2BB8 __attribute__((sda));

extern void ref_L00_003F09A0_00(char *rec, float f1, int a1, int a2, int a3,
                                float f2, int a4, float f3);

void func_L00_003F09A0(char *obj)
{
    char *rec;
    int i;

    for (i = 0; i < 320; i++) {
        rec = (char *)(i * 128 + (int)D_L00_001B2BB8);
        if (*(int *)(rec + 0x7C) == (int)obj)
            ref_L00_003F09A0_00(rec, *(float *)(rec + 0x48), *(int *)(rec + 0x68),
                                *(int *)(rec + 0x60), 46, *(float *)(rec + 0x34),
                                *(int *)(rec + 0x70), 0.25f);
    }
}

/* resets a state record: zero words, plus/minus one float flags and two 64-bit fields in the retail store order */
void func_L00_003F0A20(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 84) = 0;
    *(float *)(p + 88) = 1.0f;
    *(int *)(p + 92) = 0;
    *(int *)(p + 96) = 0;
    *(float *)(p + 100) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -1.0f;
    *(float *)(p + 24) = 1.0f;
    *(float *)(p + 40) = -1.0f;
    *(float *)(p + 56) = 1.0f;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 280993940374112LL;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}

/* Scales four consecutive 16-byte XYZ vectors in place by one scalar through a vector helper. */
void func_L00_003F0AA8(char *p, float scale)
{
    func_00282D30_2(p, p, scale);
    func_00282D30_2(p + 16, p + 16, scale);
    func_00282D30_2(p + 32, p + 32, scale);
    func_00282D30_2(p + 48, p + 48, scale);
}

extern void ref_L00_003F0B10_00(char *pkt);

extern void ref_L00_003F0B10_01(char *, float);

extern long long func_0027C878(char *p);

extern float func_00283248(float x, float y);

extern float func_00282E80(char *p, float *v);

extern void func_00283410(float *matrix, float *quat);

extern void func_00282CF0(char *off, char *v, char *pos);

extern void func_00282F20(char *dst, char *src, float angle);

extern void func_00280B90(char *pkt, float *matrix, int mode);

/* The vector the aim helpers read, at 0x001B8C80; per level at its own copy. */
#ifndef RAC2_T_AIMVEC_F0B10
#define RAC2_T_AIMVEC_F0B10
typedef struct {
    char pad_000[0x140];
    float x_140;
    float y_144;
    float z_148;
} Aimvec_F0b10;
#endif

extern Aimvec_F0b10 D_L00_001B8C80;

/* Builds a 144-byte packet, aims a quaternion at the shared 0x001B8C80 vector from pos through three float helpers, derives an offset basis by a fourth, writes the last matrix row from pos plus that offset, then dispatches the packet. */
void func_L00_003F0B10(char *pos, int a1, int a2, char *a3, int t0,
                       float fA, float fB, float fC)
{
    char pkt[144];
    float m[16];
    float quat[4];
    float off[4];
    long long r;

    ref_L00_003F0B10_00(pkt);
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
    quat[2] = func_00283248(D_L00_001B8C80.x_140 - *(float *)(pos + 0),
                            D_L00_001B8C80.y_144 - *(float *)(pos + 4));
    quat[1] = -func_00283248(func_00282E80(pos, &D_L00_001B8C80.x_140),
                             D_L00_001B8C80.z_148 - *(float *)(pos + 8));
    quat[0] = fB;

    func_00283410(m, quat);
    func_00282CF0(off, &D_L00_001B8C80.x_140, pos);
    func_00282F20(off, off, fC);

    m[12] = *(float *)(pos + 0) + off[0];
    m[13] = *(float *)(pos + 4) + off[1];
    m[14] = *(float *)(pos + 8) + off[2];
    m[15] = 1.0f;

    ref_L00_003F0B10_01(pkt, fA);
    func_00280B90(pkt, m, 0);
}

INCLUDE_ASM("asm/levels", func_L00_003F0CC8);

/* func_L00_003F1300 is defined in L00_003F1300-g8.c. */

extern int D_L00_001B08D0 __attribute__((sda));

void func_L00_003F1448(void)
{
    D_L00_001B08D0 = 0;
}

/* resets a state record: zero words, plus/minus one float flags and two 64-bit fields in the retail store order */
void func_L00_003F1DC8(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 84) = 0;
    *(float *)(p + 88) = 1.0f;
    *(int *)(p + 92) = 0;
    *(int *)(p + 96) = 0;
    *(float *)(p + 100) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -1.0f;
    *(float *)(p + 24) = 1.0f;
    *(float *)(p + 40) = -1.0f;
    *(float *)(p + 56) = 1.0f;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 280993940374112LL;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}

/* Scales four consecutive 16-byte XYZ vectors in place by one scalar through a vector helper. */
void func_L00_003F1E50(char *p, float scale)
{
    func_00282D30_2(p, p, scale);
    func_00282D30_2(p + 16, p + 16, scale);
    func_00282D30_2(p + 32, p + 32, scale);
    func_00282D30_2(p + 48, p + 48, scale);
}

extern Aimvec_F0b10 D_L00_001B8C80;

extern void ref_L00_003F1EB8_00(char *pkt);

extern void ref_L00_003F1EB8_01(char *, float);

/* Builds a 144-byte packet, aims a quaternion at the shared 0x001B8C80 vector from pos through three float helpers, derives an offset basis by a fourth, writes the last matrix row from pos plus that offset, then dispatches the packet. */
void func_L00_003F1EB8(char *pos, int a1, int a2, char *a3, int t0,
                       float fA, float fB, float fC)
{
    char pkt[144];
    float m[16];
    float quat[4];
    float off[4];
    long long r;

    ref_L00_003F1EB8_00(pkt);
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
    quat[2] = func_00283248(D_L00_001B8C80.x_140 - *(float *)(pos + 0),
                            D_L00_001B8C80.y_144 - *(float *)(pos + 4));
    quat[1] = -func_00283248(func_00282E80(pos, &D_L00_001B8C80.x_140),
                             D_L00_001B8C80.z_148 - *(float *)(pos + 8));
    quat[0] = fB;

    func_00283410(m, quat);
    func_00282CF0(off, &D_L00_001B8C80.x_140, pos);
    func_00282F20(off, off, fC);

    m[12] = *(float *)(pos + 0) + off[0];
    m[13] = *(float *)(pos + 4) + off[1];
    m[14] = *(float *)(pos + 8) + off[2];
    m[15] = 1.0f;

    ref_L00_003F1EB8_01(pkt, fA);
    func_00280B90(pkt, m, 0);
}

/* func_L00_003F26C8 is defined in L00_003F26C8-qcopy.c. */

/* Derives a 16-byte element at index-1 from its index-2 and index-3 neighbours through two bound helpers; original game role is unknown. */
void func_L00_003F28A0(Vec16_Fc936841d *object, int index)
{
    char local[16];

    func_00282CF0_9(local, (char *)&object[index - 2], (char *)&object[index - 3]);
    func_00282CC0_15((char *)&object[index - 1], (char *)&object[index - 2], local);
}

extern void func_0029F338(char *);
extern int func_002ACBC8(void *, int);
extern float func_00283198(float);
extern int func_00283D38(int, int, float);
extern void func_L00_0036EF68(char *, int, int, int);

/* The binder both state paths hand the handler to: func_L00_002E6EF8 in eleven of the twelve
   programs, but level 09 calls its sibling variant (func_L08_002F2D10, another task array), so
   the call carries a name without an address. */
extern void ref_L00_003F3160_00(void *, void *);

extern void func_L00_003F3518(char *);

extern int D_L00_001A9018 __attribute__((sda));

extern unsigned short **D_L00_001A9014 __attribute__((sda));

extern unsigned char *D_L00_001B2514 __attribute__((sda));

/* A three-state object whose record (the pointer at +0x68) carries a group index at +0, two
   RGB triples and two RGBA quadruples as separate bytes, a packed colour at +0x10 and a few
   angle and flag words. State 0 arms it: an index outside the group table releases the object;
   otherwise the two angles are turned into radians, the byte triples are packed into the words
   at +0x14, +0x18, +0x30 and +0x34, and the object is handed to the binder with
   func_L00_003F3518 as its handler (state 2), or parked in state 1 when the word at +0x1C is set.
   State 1 steps the angle at +0xC and eases the colour at +0x10 towards one of the two packed
   colours; when it changed, its three bytes go to every entity of the group's id list. State 2
   re-binds the handler. The two stores of the byte at +0x30 sit in the arms of the select: the
   record's word at +0x68 either supplies its low byte or the object gets 0xFF. */
void func_L00_003F3160(char *obj)
{
    unsigned char *st = *(unsigned char **)(obj + 0x68);
    int group;
    int prev;
    int stamp;
    int word_a, word_b;
    int target;
    float angle;
    unsigned short *q;
    unsigned char *e;
    int r, g, b;

    switch (*(unsigned char *)(obj + 0x20)) {
    case 0:
        group = *(int *)st;
        if (group >= D_L00_001A9018 || D_L00_001A9014[group] == 0 || group == -1) {
            func_0029F338(obj);
            return;
        }
        *(float *)(st + 8) = *(float *)(st + 8) * 0.017453294f;
        *(float *)(st + 4) = *(float *)(st + 4) * 0.00029088825f;
        *(int *)(st + 0x14) = st[0x22] << 16 | st[0x21] << 8 | st[0x20];
        *(int *)(st + 0x18) = st[0x25] << 16 | st[0x24] << 8 | st[0x23];
        if (*(int *)(st + 0x68) != 0) {
            stamp = st[0x68];
            obj[0x30] = stamp;
        } else {
            stamp = 0xFF;
            obj[0x30] = stamp;
        }
        if (*(int *)(st + 0x1C) != 0) {
            obj[0x20] = 1;
            return;
        }
        word_a = st[0x29] << 24 | st[0x28] << 16;
        word_a |= st[0x27] << 8;
        word_a |= st[0x26];
        *(int *)(st + 0x30) = word_a;
        word_b = st[0x2D] << 24 | st[0x2C] << 16;
        word_b |= st[0x2B] << 8;
        word_b |= st[0x2A];
        *(int *)(st + 0x34) = word_b;
        if (*(float *)(st + 0x40) == 0.0f && *(float *)(st + 0x44) == 0.0f &&
            *(float *)(st + 0x48) == 0.0f)
            *(int *)(st + 0x6C) = 1;
        ref_L00_003F3160_00((void *)func_L00_003F3518, obj);
        obj[0x20] = 2;
        return;
    case 1:
        if (*(int *)(st + 0x64) != -1) {
            if (func_002ACBC8(&D_L00_001B8C80.x_140, *(int *)(st + 0x64)) == 0)
                return;
        }
        angle = func_00283B98(*(float *)(st + 0xC), *(float *)(st + 4));
        prev = *(int *)(st + 0x10);
        *(float *)(st + 0xC) = angle;
        if (*(float *)(st + 8) != 0.0f) {
            target = *(int *)(st + 0x14);
            if (angle > *(float *)(st + 8))
                target = *(int *)(st + 0x18);
            *(int *)(st + 0x10) = func_00283D38(prev, target, 0.1f);
        } else {
            *(int *)(st + 0x10) = func_00283D38(*(int *)(st + 0x14), *(int *)(st + 0x18),
                                                func_00283198(angle) * 0.5f + 0.5f);
        }
        if (*(int *)(st + 0x10) == prev)
            return;
        q = D_L00_001A9014[*(int *)st];
        r = *(int *)(st + 0x10) & 0xFF;
        g = (*(int *)(st + 0x10) >> 8) & 0xFF;
        b = (*(int *)(st + 0x10) >> 16) & 0xFF;
        for (; q != 0 && ((short)q[-1] >= 0 || q == D_L00_001A9014[*(int *)st]) &&
               (e = D_L00_001B2514 + ((*q & 0x7FFF) << 5)) != 0;
             q++)
            func_L00_0036EF68((char *)e, r, g, b);
        return;
    case 2:
        if (*(int *)(st + 0x64) == -1 ||
            func_002ACBC8(&D_L00_001B8C80.x_140, *(int *)(st + 0x64)) != 0)
            ref_L00_003F3160_00((void *)func_L00_003F3518, obj);
        return;
    }
}

/* func_L00_003F34D8 is in L00_003F34D8-qcopy.c (its own file: the quadword-copy profile). */

/* func_L00_003F3518 is defined in L00_003F3518-helpers.c. */

extern void ref_L00_003F37A0_00(void *p, char *obj);

extern void func_L00_003F37E8(char *object);

typedef struct Obj_L00_003F37A0 {
    unsigned char pad0[0x20];
    unsigned char f20;
    unsigned char pad21[0xC0 - 0x21];
    float fC0;
    unsigned char padC4[0xD4 - 0xC4];
    float fD4;
    unsigned char padD8[0xE8 - 0xD8];
    float fE8;
} Obj_L00_003F37A0;

void func_L00_003F37A0(Obj_L00_003F37A0 *obj)
{
    if (obj->f20 == 0) {
        obj->f20 = 1;
        obj->fC0 = 1.0f;
        obj->fD4 = 1.0f;
        obj->fE8 = 1.0f;
    }
    ref_L00_003F37A0_00((void *)func_L00_003F37E8, (char *)obj);
}

extern void func_00283098(void *, void *, void *);
extern float func_00282DB0(void *, void *);
extern Vector D_L00_0029DAE0[];
extern Vector D_L00_0029D7C0[];
extern Vector D_L00_0029CB30[];
extern short D_L00_0029D170[][4][2];
extern float D_L00_0029D490[][2];

/* Draws 50 quads through the object's frame (its basis at 0xC0 and position at 0x10). Per
   quad, a transformed table point is offset from the 0x001B8C80 vector and normalised, a
   second table vector is transformed, and both go to func_00282DB0 (its result is unused);
   the four corners then take their vertices and UVs from tables, and a corner at
   z = -0.002112 gets a transparent colour. */
void func_L00_003F37E8(char *object)
{
    RenderPacket packet;
    struct {
        Frame frame;
        Vector facing, transformed;
    } scratch;
    int *state = *(int **)(object + 0x68);
    int face, corner;
    unsigned int color;
    Vector *matrix;

    packet.f78 = func_0027C878((char *)5);
    matrix = scratch.frame.row;
    packet.f80 = 0xff9000000260LL;
    packet.flags = 0x8000000048LL;
    packet.f70 = 0;
    qcopy(matrix, object + 0xc0);
    qcopy(&scratch.frame.row[1], object + 0xd0);
    qcopy(&scratch.frame.row[2], object + 0xe0);
    scratch.frame.position.v[0] = *(float *)(object + 0x10);
    scratch.frame.position.v[1] = *(float *)(object + 0x14);
    scratch.frame.position.v[2] = *(float *)(object + 0x18);
    scratch.frame.position.v[3] = 1.0f;
    color = (*state << 24) | 0xff0000;
    packet.color[3] = color;
    packet.color[2] = color;
    packet.color[1] = color;
    packet.color[0] = color;
    for (face = 0; face < 50; face++) {
        func_00282D30(&scratch.transformed, &D_L00_0029DAE0[face], 1.0f);
        func_002830C0(&scratch.transformed, &scratch.transformed, &scratch.frame);
        func_00282CF0((char *)&scratch.facing, (char *)&scratch.transformed,
                      (char *)&D_L00_001B8C80.x_140);
        func_00282F20((char *)&scratch.facing, (char *)&scratch.facing, 1.0f);
        func_00283098(&scratch.transformed, &D_L00_0029D7C0[face], matrix);
        func_00282DB0(&scratch.facing, &scratch.transformed);
        for (corner = 0; corner < 4; corner++) {
            Vector *position = &D_L00_0029CB30[D_L00_0029D170[face][corner][0]];
            int uv = D_L00_0029D170[face][corner][1];

            func_00282D30(&packet.vertex[corner], position, 1.0f);
            packet.uv[corner][0] = D_L00_0029D490[uv][0];
            packet.uv[corner][1] = D_L00_0029D490[uv][1];
            if (position->v[2] == -0.002112f)
                packet.color[corner] = 0xff0000;
        }
        func_00280B90((char *)&packet, (float *)&scratch.frame, 0);
    }
}

extern void func_L00_003F3AD0(char *);

typedef struct Obj_L00_003F3A88 {
    unsigned char pad0[0x20];
    unsigned char f20;
    unsigned char pad21[0xC0 - 0x21];
    float fC0;
    unsigned char padC4[0xD4 - 0xC4];
    float fD4;
    unsigned char padD8[0xE8 - 0xD8];
    float fE8;
} Obj_L00_003F3A88;

void func_L00_003F3A88(Obj_L00_003F3A88 *obj)
{
    if (obj->f20 == 0) {
        obj->f20 = 1;
        obj->fC0 = 1.0f;
        obj->fD4 = 1.0f;
        obj->fE8 = 1.0f;
    }
    ref_L00_003F3A88_00((void *)func_L00_003F3AD0, (char *)obj);
}

extern Vector D_L00_0029EDB0[];
extern Vector D_L00_0029EA90[];
extern Vector D_L00_0029DE00[];
extern short D_L00_0029E440[][4][2];
extern float D_L00_0029E760[][2];

void func_L00_003F3AD0(char *object)
{
    RenderPacket packet;
    struct {
        Frame frame;
        Vector facing, transformed;
    } scratch;
    int *state = *(int **)(object + 0x68);
    int face, corner;
    unsigned int color;
    Vector *matrix;

    packet.f78 = func_0027C878((char *)5);
    matrix = scratch.frame.row;
    packet.f80 = 0xff9000000260LL;
    packet.flags = 0x8000000048LL;
    packet.f70 = 0;
    qcopy(matrix, object + 0xc0);
    qcopy(&scratch.frame.row[1], object + 0xd0);
    qcopy(&scratch.frame.row[2], object + 0xe0);
    scratch.frame.position.v[0] = *(float *)(object + 0x10);
    scratch.frame.position.v[1] = *(float *)(object + 0x14);
    scratch.frame.position.v[2] = *(float *)(object + 0x18);
    scratch.frame.position.v[3] = 1.0f;
    color = (*state << 24) | 0xff0000;
    packet.color[3] = color;
    packet.color[2] = color;
    packet.color[1] = color;
    packet.color[0] = color;
    for (face = 0; face < 50; face++) {
        func_00282D30(&scratch.transformed, &D_L00_0029EDB0[face], 1.0f);
        func_002830C0(&scratch.transformed, &scratch.transformed, &scratch.frame);
        func_00282CF0((char *)&scratch.facing, (char *)&scratch.transformed,
                      (char *)&D_L00_001B8C80.x_140);
        func_00282F20((char *)&scratch.facing, (char *)&scratch.facing, 1.0f);
        func_00283098(&scratch.transformed, &D_L00_0029EA90[face], matrix);
        func_00282DB0(&scratch.facing, &scratch.transformed);
        for (corner = 0; corner < 4; corner++) {
            Vector *position = &D_L00_0029DE00[D_L00_0029E440[face][corner][0]];
            int uv = D_L00_0029E440[face][corner][1];

            func_00282D30(&packet.vertex[corner], position, 1.0f);
            packet.uv[corner][0] = D_L00_0029E760[uv][0];
            packet.uv[corner][1] = D_L00_0029E760[uv][1];
            if (position->v[2] == 0.001432f)
                packet.color[corner] = 0xff0000;
        }
        func_00280B90((char *)&packet, (float *)&scratch.frame, 0);
    }
}



INCLUDE_ASM("asm/levels", func_L00_003F4210);

/* func_L00_003F4B68 uses its dedicated quadword-copy profile. */


/* Computes two sub-record addresses of a 192-byte block and hands three of its sub-records to four helpers, threading a second argument through two of them. */
void func_L00_003F51A0(char *obj, char *arg)
{
    char *base = obj + 192;
    char *other = obj + 208;
    float one = 1.0f;

    func_00282F20_1(base, (char *)(*(int *)(obj + 104)), one);
    func_00282DD8(other, base, arg);
    func_00282F20_1(other, other, one);
    func_00282DD8(obj + 224, other, base);
}

/* func_L00_003F5238 is in L00_003F5238-helpers.c. */

/* func_L00_003F5390 is in L00_003F5390-g8.c. */

void func_L00_003F5658(void)
{
}

extern int func_L00_003F59F0(char *);
extern int func_L00_003F6168(char *);
extern int func_L00_003F6A58(int *);
extern void func_L00_003F56F0(char *);
extern void ref_L00_003F5660_00(void (*handler)(char *), char *object);

/* Runs the three per-frame passes; when any of them reports work the record is handed to the
   binder with the shared follow-up pass as its handler, otherwise a record in state 2 is
   advanced by the shared state call. */
void func_L00_003F5660(char *a0)
{
    int a = func_L00_003F59F0(a0);
    int b = func_L00_003F6168(a0);
    int c = func_L00_003F6A58((int *)a0);

    if (a == 0 && b == 0 && c == 0) {
        if (*(unsigned char *)(a0 + 0x20) == 2) {
            func_0029F338_1(a0);
        }
    } else {
        ref_L00_003F5660_00(func_L00_003F56F0, a0);
    }
}

/* Reads the short at +26 of the object held at +104, calls a callee with (3076, that short), then calls one callee with this when the result is zero or three callees with this when it is non-zero. */
void func_L00_003F56F0(char *p)
{
    if (func_002B4038(3076, *(short *)(*(int *)(p + 104) + 26)) == 0)
        func_0029F338_1(p);
    else {
        func_L00_003F5B10(p);
        func_L00_003F6308(p);
        func_L00_003F6B10(p);
    }
}

INCLUDE_ASM("asm/levels", func_L00_003F5750);

INCLUDE_ASM("asm/levels", func_L00_003F5870);

/* func_L00_003F5B10 is in L00_003F5B10-g8.c. */


/* func_L00_003F6168 is in L00_003F6168-helpers-g8.c. */

INCLUDE_ASM("asm/levels", func_L00_003F6308);

/* func_L00_003F6900 is defined in L00_003F6900-g8-qcopy.c. */

/* Walks 120 records of 64 bytes from a base resolved through two descriptor lookups; for each live record it calls an update helper and, when that reports zero, counts it and advances a float pair by one step, clearing the record's live flag otherwise. */
int func_L00_003F6A58(int *a0)
{
    int i;
    int count = 0;
    char *base;
    char *rec;
    char *obj;

    rec = *(char **)((char *)a0 + 104);
    base = func_L00_0032A088(3076, *(short *)(rec + 26));
    base = base + *(int *)(func_L00_0032A0B8(3076, *(short *)(rec + 26)) + 4);
    obj = base + 16;
    rec = base;

    for (i = 119; i >= 0; i--) {
        if (*(short *)(rec + 18) != 0) {
            if (func_00282978(obj) != 0) {
                *(short *)(rec + 18) = 0;
            } else {
                count++;
                *(float *)(rec + 24) = func_00283B98(*(float *)(rec + 24), *(float *)(rec + 28));
            }
        }
        obj += 64;
        rec += 64;
    }
    return count;
}


extern void func_002AD0E0(char *a0, char *a1, char *a2, char *a3, char *a4, char *a5);

extern void func_0029F338(char *a0);

extern int func_00282978(char *a0);

extern void ref_L00_003F71E8_01(void *p, char *obj);

extern void ref_L00_003F71E8_00(void);

void func_L00_003F71E8(char *a0)
{
    char *s1 = *(char **)(a0 + 0x68);

    if (*(char **)(s1 + 0x3C) != 0) {
        func_002AD0E0(a0, *(char **)(s1 + 0x3C), a0 + 0x10, a0 + 0xF0, a0 + 0x10, a0 + 0xF0);
    }
    if (func_00282978(s1) == 0) {
        func_00282978(s1 + 4);
        ref_L00_003F71E8_01((void *)ref_L00_003F71E8_00, a0);
    } else {
        func_0029F338(a0);
    }
}


/* Draws a camera-facing textured quad of the given size at a position, optionally rolled and
   moved along the camera direction, then redraws it with texture -1 and UVs projected to the
   screen (from points pulled 20% towards the quad's centre when mode is set), jittered and
   clamped to [0, 1]. */
void func_L00_003F8280(Vector *position, float size, float offset, float roll,
                       float unused, float jitter, int texture, int mode)
{
    RenderPacket packet;
    Frame frame;
    /* One 64-byte scratch area: the roll angles (later the offset), then the roll rotation,
       whose first two rows are reused for the projection's centre and point. */
    struct {
        Vector angles;
        union {
            Vector rotation[3];
            struct { Vector center, point; } projection;
        } u;
    } scratch;
    Vector *corner;

    func_00281DE8(&packet, texture, 1, 0x80);
    packet.flags = 0x800000004aULL;
    packet.color[3] = 0x80808080;
    packet.color[2] = 0x80808080;
    packet.color[1] = 0x80808080;
    packet.color[0] = 0x80808080;
    packet.uv[0][0] = 0.0f;
    packet.uv[0][1] = 0.0f;
    packet.uv[1][0] = 0.0f;
    packet.uv[1][1] = 1.0f;
    packet.uv[2][0] = 1.0f;
    packet.uv[2][1] = 0.0f;
    packet.uv[3][0] = 1.0f;
    packet.uv[3][1] = 1.0f;
    qcopy(&frame.position, position);
    func_00282CF0((char *)&frame.row[0], (char *)&D_L00_001B8C80.x_140, (char *)&frame.position);
    func_00282F20((char *)&frame.row[0], (char *)&frame.row[0], 1.0f);
    func_00282DD8((char *)&frame.row[1], (char *)&frame.row[0], (char *)&D_0018A0E0);
    func_00282F20((char *)&frame.row[1], (char *)&frame.row[1], 1.0f);
    func_00282DD8((char *)&frame.row[2], (char *)&frame.row[1], (char *)&frame.row[0]);
    if (roll != 0.0f) {
        scratch.angles.word = 0;
        scratch.angles.v[0] = roll;
        func_002833F0(scratch.u.rotation, &scratch.angles);
        func_00283738(frame.row, frame.row, scratch.u.rotation);
    }
    func_00282D30(&scratch.angles, &frame.row[0], offset);
    func_00282CC0(&frame.position, &frame.position, &scratch.angles);
    {
        Vector *vertex = packet.vertex;
        int count;
        corner = D_L00_001AA310;
        count = 3;
        do {
            func_00282D30(vertex, corner, size);
            ++corner;
            --count;
            func_002830C0(vertex, vertex, &frame);
            ++vertex;
        } while (count >= 0);
    }
    func_002FC560(0x47, 0x31001ULL);
    func_00280B90((char *)&packet, 0, 0);
    if (mode != 0) {
        int i;

        qcopy(&scratch.u.projection.center, &packet.vertex[0]);
        {
            Vector *vertex = &packet.vertex[1];
            int count;
            count = 2;
            do {
                func_00282CC0(&scratch.u.projection.center, &scratch.u.projection.center,
                              vertex);
                ++vertex;
                --count;
            } while (count >= 0);
        }
        func_00282D30(&scratch.u.projection.center, &scratch.u.projection.center, 0.25f);
        for (i = 0; i < 4; ++i) {
            func_00282CF0((char *)&scratch.u.projection.point, (char *)&packet.vertex[i],
                          (char *)&scratch.u.projection.center);
            func_00282D30(&scratch.u.projection.point, &scratch.u.projection.point, 0.8f);
            func_00282CC0(&scratch.u.projection.point, &scratch.u.projection.center,
                          &scratch.u.projection.point);
            func_0027C768((int)&scratch.u.projection.point, &packet.uv[i][0], &packet.uv[i][1]);
            if (func_002A77E0(1) == 0) {
                packet.uv[i][0] += func_002A7878(-jitter, jitter);
                packet.uv[i][1] += func_002A7878(-jitter, jitter);
            }
            if (packet.uv[i][0] > 1.0f) packet.uv[i][0] = 1.0f;
            else if (packet.uv[i][0] < 0.0f) packet.uv[i][0] = 0.0f;
            if (packet.uv[i][1] > 1.0f) packet.uv[i][1] = 1.0f;
            else if (packet.uv[i][1] < 0.0f) packet.uv[i][1] = 0.0f;
        }
    } else {
        int i;

        for (i = 0; i < 4; ++i) {
            func_0027C768((int)&packet.vertex[i], &packet.uv[i][0], &packet.uv[i][1]);
            if (func_002A77E0(1) == 0) {
                packet.uv[i][0] += func_002A7878(-jitter, jitter);
                packet.uv[i][1] += func_002A7878(-jitter, jitter);
            }
            if (packet.uv[i][0] > 1.0f) packet.uv[i][0] = 1.0f;
            else if (packet.uv[i][0] < 0.0f) packet.uv[i][0] = 0.0f;
            if (packet.uv[i][1] > 1.0f) packet.uv[i][1] = 1.0f;
            else if (packet.uv[i][1] < 0.0f) packet.uv[i][1] = 0.0f;
        }
    }
    func_00281DE8(&packet, -1, 1, 0x80);
    packet.flags = 0x8000000054ULL;
    func_002FC560(0x47, 0x33001ULL);
    func_00280B90((char *)&packet, 0, 0);
    func_002FC560(0x47, 0x5360bULL);
}

/* func_L00_003F87B0 is in L00_003F87B0.c. */

/* Same body as 23626ad829daa908 with the node field 4 bytes earlier: calls a helper with a referenced node and three identity bytes, then copies them into a linked record guarded by a flag bit and a non-zero leading short. */
void func_L00_003F89F8(Obj_Fe48725c6 *p)
{
    Node24_Fe48725c6 *s;
    Node16_Fe48725c6 *d;
    int v;

    func_002A0488_1(p->f24, p->u.b.b4, p->u.b.b5, p->u.b.h6);
    s = p->f24;
    if ((s->h52 & 0x20) == 0)
        return;
    d = ((Node104_Fe48725c6 *)s->p104)->p16;
    if (d == 0)
        return;
    if (d->h0 == 0)
        return;
    d->b4 = p->u.b.b4;
    d->b5 = p->u.f4 >> 8;
    v = p->u.b.h6;
    d->b6 = v;
}

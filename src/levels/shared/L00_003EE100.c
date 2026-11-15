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
/* Makes the object pulse: it scales its three axes by wobbling amounts and eases the wobble values back. */
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
/* Says whether the object can be used as a target, which needs both checks to pass and its health to be zero or less. */
int func_L00_003EE228(char *object)
{
    float *info;

    if (IsMobyInSpecialClassRange(object) != 0)
        return 0;
    info = GetMobyPrivateValue0(object);
    if (info == 0)
        return 0;
    if (0.0f < *info)
        return 0;
    return 1;
}


/* When the context flag at offset 0x24 is nonzero, pass scale 1.0, the context, its vector at offset 0x10 and mode zero to the bound helper; original game role is unknown. */
/* Draws the aiming effect of a weapon object while its active flag is set. */
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

/* Clears an effect flag. */
void func_L00_003EF548(void)
{
    D_L00_001B0838 = 0;
}

extern int D_L00_001B0838 __attribute__((sda));

extern int D_L00_001B2BB4 __attribute__((sda));

/* Clears the effect record table pointer and an effect flag. */
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
/* Starts a new trail effect in a free record slot, then steps it 100 times to fill in its shape. */
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
        angle = RandomAngle();
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

/* Updates every effect record that belongs to the given object and frees those whose timer has run out. */
void func_L00_003F00A0(char *ownerMoby)
{
    char *rec;
    int i;
    int offset;

    offset = 0;
    i = 0;
    do {
        i--;
        rec = (char *)(offset + (int)D_L00_001B2BB4_1);
        if (*(int *)(rec + 0x30) == (int)ownerMoby) {
            if (FastFloatHelperD(rec + 0x34) != 0 && *(int *)(rec + 0x38) == 0)
                *(int *)(rec + 0x30) = 0;
            UpdateBlastPoolRecords(rec);
        }
        offset += 0x50;
    } while (i >= 0);
}

extern void func_L00_003F09A0(char *rec);

/* Goes through the effect records of the given object and draws each one. */
void func_L00_003F0130(char *ownerMoby)
{
    char *rec;
    int i;
    int offset;

    offset = 0;
    i = 0;
    do {
        i--;
        rec = (char *)(offset + (int)D_L00_001B2BB4_1);
        if (*(int *)(rec + 0x30) == (int)ownerMoby)
            RespawnOwnerParticles(rec);
        offset += 0x50;
    } while (i >= 0);
}



extern char *D_L00_001B2BB8 __attribute__((sda));

extern void ref_L00_003F09A0_00(char *rec, float f1, int a1, int a2, int a3,
                                float f2, int a4, float f3);

/* Finds all particles that belong to the given object and respawns them. */
void func_L00_003F09A0(char *ownerMoby)
{
    char *rec;
    int i;

    for (i = 0; i < 320; i++) {
        rec = (char *)(i * 128 + (int)D_L00_001B2BB8);
        if (*(int *)(rec + 0x7C) == (int)ownerMoby)
            ref_L00_003F09A0_00(rec, *(float *)(rec + 0x48), *(int *)(rec + 0x68),
                                *(int *)(rec + 0x60), 46, *(float *)(rec + 0x34),
                                *(int *)(rec + 0x70), 0.25f);
    }
}

/* resets a state record: zero words, plus/minus one float flags and two 64-bit fields in the retail store order */
/* Sets a block of four quad corner vectors and packet fields to their starting values. */
void func_L00_003F0A20(char *entry)
{
    *(long long *)(entry + 112) = 0LL;
    *(int *)(entry + 80) = 0;
    *(int *)(entry + 84) = 0;
    *(float *)(entry + 88) = 1.0f;
    *(int *)(entry + 92) = 0;
    *(int *)(entry + 96) = 0;
    *(float *)(entry + 100) = 1.0f;
    *(float *)(entry + 104) = 1.0f;
    *(float *)(entry + 108) = 1.0f;
    *(float *)(entry + 8) = -1.0f;
    *(float *)(entry + 24) = 1.0f;
    *(float *)(entry + 40) = -1.0f;
    *(float *)(entry + 56) = 1.0f;
    *(float *)(entry + 4) = -1.0f;
    *(float *)(entry + 36) = 1.0f;
    *(float *)(entry + 52) = 1.0f;
    *(int *)(entry + 0) = 0;
    *(int *)(entry + 16) = 0;
    *(int *)(entry + 32) = 0;
    *(int *)(entry + 48) = 0;
    *(float *)(entry + 12) = 1.0f;
    *(float *)(entry + 28) = 1.0f;
    *(float *)(entry + 44) = 1.0f;
    *(long long *)(entry + 128) = 280993940374112LL;
    *(float *)(entry + 20) = -1.0f;
    *(float *)(entry + 60) = 1.0f;
}

/* Scales four consecutive 16-byte XYZ vectors in place by one scalar through a vector helper. */
/* Scales four vectors in a row by the same amount. */
void func_L00_003F0AA8(char *vectors, float scale)
{
    func_00282D30_2(vectors, vectors, scale);
    func_00282D30_2(vectors + 16, vectors + 16, scale);
    func_00282D30_2(vectors + 32, vectors + 32, scale);
    func_00282D30_2(vectors + 48, vectors + 48, scale);
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
/* Draws a flat sprite at a position that turns to face the camera. */
void func_L00_003F0B10(char *pos, int colorBase, int alpha, char *texture, int flagBits,
                       float size, float roll, float pull)
{
    char packet[144];
    float matrix[16];
    float quat[4];
    float offset[4];
    long long textureKey;

    ref_L00_003F0B10_00(packet);
    textureKey = GetEffectTextureDescriptor(texture);

    *(long long *)(packet + 136) = ((long long)flagBits << 2) | 0x8000000040LL;
    *(long long *)(packet + 128) = 280993940374112LL;
    *(int *)(packet + 76) = colorBase + (alpha << 24);
    *(int *)(packet + 72) = colorBase + (alpha << 24);
    *(int *)(packet + 68) = colorBase + (alpha << 24);
    *(int *)(packet + 64) = colorBase + (alpha << 24);
    *(long long *)(packet + 112) = 0LL;
    *(long long *)(packet + 120) = textureKey;

    quat[3] = 0.0f;
    quat[2] = FastMatrixHelperA(D_L00_001B8C80.x_140 - *(float *)(pos + 0),
                            D_L00_001B8C80.y_144 - *(float *)(pos + 4));
    quat[1] = -FastMatrixHelperA(vec_distance_xy(pos, &D_L00_001B8C80.x_140),
                             D_L00_001B8C80.z_148 - *(float *)(pos + 8));
    quat[0] = roll;

    euler_to_matrix(matrix, quat);
    FastVecSub(offset, &D_L00_001B8C80.x_140, pos);
    vec_scale_to_length(offset, offset, pull);

    matrix[12] = *(float *)(pos + 0) + offset[0];
    matrix[13] = *(float *)(pos + 4) + offset[1];
    matrix[14] = *(float *)(pos + 8) + offset[2];
    matrix[15] = 1.0f;

    ref_L00_003F0B10_01(packet, size);
    draw_world_quad(packet, matrix, 0);
}


/* func_L00_003F1300 is defined in L00_003F1300-g8.c. */

extern int D_L00_001B08D0 __attribute__((sda));

/* Clears the flag that says the lightning burst exists. */
void func_L00_003F1448(void)
{
    D_L00_001B08D0 = 0;
}

/* resets a state record: zero words, plus/minus one float flags and two 64-bit fields in the retail store order */
/* Sets a block of four quad corner vectors and packet fields to their starting values. */
void func_L00_003F1DC8(char *entry)
{
    *(long long *)(entry + 112) = 0LL;
    *(int *)(entry + 80) = 0;
    *(int *)(entry + 84) = 0;
    *(float *)(entry + 88) = 1.0f;
    *(int *)(entry + 92) = 0;
    *(int *)(entry + 96) = 0;
    *(float *)(entry + 100) = 1.0f;
    *(float *)(entry + 104) = 1.0f;
    *(float *)(entry + 108) = 1.0f;
    *(float *)(entry + 8) = -1.0f;
    *(float *)(entry + 24) = 1.0f;
    *(float *)(entry + 40) = -1.0f;
    *(float *)(entry + 56) = 1.0f;
    *(float *)(entry + 4) = -1.0f;
    *(float *)(entry + 36) = 1.0f;
    *(float *)(entry + 52) = 1.0f;
    *(int *)(entry + 0) = 0;
    *(int *)(entry + 16) = 0;
    *(int *)(entry + 32) = 0;
    *(int *)(entry + 48) = 0;
    *(float *)(entry + 12) = 1.0f;
    *(float *)(entry + 28) = 1.0f;
    *(float *)(entry + 44) = 1.0f;
    *(long long *)(entry + 128) = 280993940374112LL;
    *(float *)(entry + 20) = -1.0f;
    *(float *)(entry + 60) = 1.0f;
}

/* Scales four consecutive 16-byte XYZ vectors in place by one scalar through a vector helper. */
/* Scales four vectors in a row by the same amount. */
void func_L00_003F1E50(char *vectors, float scale)
{
    func_00282D30_2(vectors, vectors, scale);
    func_00282D30_2(vectors + 16, vectors + 16, scale);
    func_00282D30_2(vectors + 32, vectors + 32, scale);
    func_00282D30_2(vectors + 48, vectors + 48, scale);
}

extern Aimvec_F0b10 D_L00_001B8C80;

extern void ref_L00_003F1EB8_00(char *pkt);

extern void ref_L00_003F1EB8_01(char *, float);

/* Builds a 144-byte packet, aims a quaternion at the shared 0x001B8C80 vector from pos through three float helpers, derives an offset basis by a fourth, writes the last matrix row from pos plus that offset, then dispatches the packet. */
/* Draws a flat sprite at a position that turns to face the camera. */
void func_L00_003F1EB8(char *pos, int colorBase, int alpha, char *texture, int flagBits,
                       float size, float roll, float pull)
{
    char packet[144];
    float matrix[16];
    float quat[4];
    float offset[4];
    long long textureKey;

    ref_L00_003F1EB8_00(packet);
    textureKey = GetEffectTextureDescriptor(texture);

    *(long long *)(packet + 136) = ((long long)flagBits << 2) | 0x8000000040LL;
    *(long long *)(packet + 128) = 280993940374112LL;
    *(int *)(packet + 76) = colorBase + (alpha << 24);
    *(int *)(packet + 72) = colorBase + (alpha << 24);
    *(int *)(packet + 68) = colorBase + (alpha << 24);
    *(int *)(packet + 64) = colorBase + (alpha << 24);
    *(long long *)(packet + 112) = 0LL;
    *(long long *)(packet + 120) = textureKey;

    quat[3] = 0.0f;
    quat[2] = FastMatrixHelperA(D_L00_001B8C80.x_140 - *(float *)(pos + 0),
                            D_L00_001B8C80.y_144 - *(float *)(pos + 4));
    quat[1] = -FastMatrixHelperA(vec_distance_xy(pos, &D_L00_001B8C80.x_140),
                             D_L00_001B8C80.z_148 - *(float *)(pos + 8));
    quat[0] = roll;

    euler_to_matrix(matrix, quat);
    FastVecSub(offset, &D_L00_001B8C80.x_140, pos);
    vec_scale_to_length(offset, offset, pull);

    matrix[12] = *(float *)(pos + 0) + offset[0];
    matrix[13] = *(float *)(pos + 4) + offset[1];
    matrix[14] = *(float *)(pos + 8) + offset[2];
    matrix[15] = 1.0f;

    ref_L00_003F1EB8_01(packet, size);
    draw_world_quad(packet, matrix, 0);
}

/* func_L00_003F26C8 is defined in L00_003F26C8-qcopy.c. */

/* Derives a 16-byte element at index-1 from its index-2 and index-3 neighbours through two bound helpers; original game role is unknown. */
/* Computes the next point of a chain from the two points before it. */
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
/* Fades a group of lights or objects between two colors over time, and passes the new color to every object in the group. */
void func_L00_003F3160(char *moby)
{
    unsigned char *vars = *(unsigned char **)(moby + 0x68);
    int group;
    int prev;
    int stamp;
    int colorA, colorB;
    int target;
    float angle;
    unsigned short *idList;
    unsigned char *entity;
    int red, green, blue;

    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        group = *(int *)vars;
        if (group >= D_L00_001A9018 || D_L00_001A9014[group] == 0 || group == -1) {
            MarkMobySpawned(moby);
            return;
        }
        *(float *)(vars + 8) = *(float *)(vars + 8) * 0.017453294f;
        *(float *)(vars + 4) = *(float *)(vars + 4) * 0.00029088825f;
        *(int *)(vars + 0x14) = vars[0x22] << 16 | vars[0x21] << 8 | vars[0x20];
        *(int *)(vars + 0x18) = vars[0x25] << 16 | vars[0x24] << 8 | vars[0x23];
        if (*(int *)(vars + 0x68) != 0) {
            stamp = vars[0x68];
            moby[0x30] = stamp;
        } else {
            stamp = 0xFF;
            moby[0x30] = stamp;
        }
        if (*(int *)(vars + 0x1C) != 0) {
            moby[0x20] = 1;
            return;
        }
        colorA = vars[0x29] << 24 | vars[0x28] << 16;
        colorA |= vars[0x27] << 8;
        colorA |= vars[0x26];
        *(int *)(vars + 0x30) = colorA;
        colorB = vars[0x2D] << 24 | vars[0x2C] << 16;
        colorB |= vars[0x2B] << 8;
        colorB |= vars[0x2A];
        *(int *)(vars + 0x34) = colorB;
        if (*(float *)(vars + 0x40) == 0.0f && *(float *)(vars + 0x44) == 0.0f &&
            *(float *)(vars + 0x48) == 0.0f)
            *(int *)(vars + 0x6C) = 1;
        ref_L00_003F3160_00((void *)DrawLitGroupPoints, moby);
        moby[0x20] = 2;
        return;
    case 1:
        if (*(int *)(vars + 0x64) != -1) {
            if (IsPointInCuboid(&D_L00_001B8C80.x_140, *(int *)(vars + 0x64)) == 0)
                return;
        }
        angle = FastAddRotations(*(float *)(vars + 0xC), *(float *)(vars + 4));
        prev = *(int *)(vars + 0x10);
        *(float *)(vars + 0xC) = angle;
        if (*(float *)(vars + 8) != 0.0f) {
            target = *(int *)(vars + 0x14);
            if (angle > *(float *)(vars + 8))
                target = *(int *)(vars + 0x18);
            *(int *)(vars + 0x10) = FastTweenColor(prev, target, 0.1f);
        } else {
            *(int *)(vars + 0x10) = FastTweenColor(*(int *)(vars + 0x14), *(int *)(vars + 0x18),
                                                FastSinOrCosB(angle) * 0.5f + 0.5f);
        }
        if (*(int *)(vars + 0x10) == prev)
            return;
        idList = D_L00_001A9014[*(int *)vars];
        red = *(int *)(vars + 0x10) & 0xFF;
        green = (*(int *)(vars + 0x10) >> 8) & 0xFF;
        blue = (*(int *)(vars + 0x10) >> 16) & 0xFF;
        for (; idList != 0 && ((short)idList[-1] >= 0 || idList == D_L00_001A9014[*(int *)vars]) &&
               (entity = D_L00_001B2514 + ((*idList & 0x7FFF) << 5)) != 0;
             idList++)
            func_L00_0036EF68((char *)entity, red, green, blue);
        return;
    case 2:
        if (*(int *)(vars + 0x64) == -1 ||
            IsPointInCuboid(&D_L00_001B8C80.x_140, *(int *)(vars + 0x64)) != 0)
            ref_L00_003F3160_00((void *)DrawLitGroupPoints, moby);
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

/* Starts a drawn shape object, setting its scale to one, and keeps its draw function running. */
void func_L00_003F37A0(Obj_L00_003F37A0 *moby)
{
    if (moby->f20 == 0) {
        moby->f20 = 1;
        moby->fC0 = 1.0f;
        moby->fD4 = 1.0f;
        moby->fE8 = 1.0f;
    }
    ref_L00_003F37A0_00((void *)DrawFiftyQuadShapeA, (char *)moby);
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
/* Draws the 50 quads of the first shape, fading with the object alpha. */
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

    packet.f78 = GetEffectTextureDescriptor((char *)5);
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
        FastVecScale(&scratch.transformed, &D_L00_0029DAE0[face], 1.0f);
        transform_vector(&scratch.transformed, &scratch.transformed, &scratch.frame);
        FastVecSub((char *)&scratch.facing, (char *)&scratch.transformed,
                      (char *)&D_L00_001B8C80.x_140);
        vec_scale_to_length((char *)&scratch.facing, (char *)&scratch.facing, 1.0f);
        matrix_mul_vec3(&scratch.transformed, &D_L00_0029D7C0[face], matrix);
        FastVecDot(&scratch.facing, &scratch.transformed);
        for (corner = 0; corner < 4; corner++) {
            Vector *position = &D_L00_0029CB30[D_L00_0029D170[face][corner][0]];
            int uv = D_L00_0029D170[face][corner][1];

            FastVecScale(&packet.vertex[corner], position, 1.0f);
            packet.uv[corner][0] = D_L00_0029D490[uv][0];
            packet.uv[corner][1] = D_L00_0029D490[uv][1];
            if (position->v[2] == -0.002112f)
                packet.color[corner] = 0xff0000;
        }
        draw_world_quad((char *)&packet, (float *)&scratch.frame, 0);
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

/* Starts a second drawn shape object, setting its scale to one, and keeps its draw function running. */
void func_L00_003F3A88(Obj_L00_003F3A88 *moby)
{
    if (moby->f20 == 0) {
        moby->f20 = 1;
        moby->fC0 = 1.0f;
        moby->fD4 = 1.0f;
        moby->fE8 = 1.0f;
    }
    ref_L00_003F3A88_00((void *)DrawFiftyQuadShapeB, (char *)moby);
}

extern Vector D_L00_0029EDB0[];
extern Vector D_L00_0029EA90[];
extern Vector D_L00_0029DE00[];
extern short D_L00_0029E440[][4][2];
extern float D_L00_0029E760[][2];

/* Draws the 50 quads of the second shape, fading with the object alpha. */
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

    packet.f78 = GetEffectTextureDescriptor((char *)5);
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
        FastVecScale(&scratch.transformed, &D_L00_0029EDB0[face], 1.0f);
        transform_vector(&scratch.transformed, &scratch.transformed, &scratch.frame);
        FastVecSub((char *)&scratch.facing, (char *)&scratch.transformed,
                      (char *)&D_L00_001B8C80.x_140);
        vec_scale_to_length((char *)&scratch.facing, (char *)&scratch.facing, 1.0f);
        matrix_mul_vec3(&scratch.transformed, &D_L00_0029EA90[face], matrix);
        FastVecDot(&scratch.facing, &scratch.transformed);
        for (corner = 0; corner < 4; corner++) {
            Vector *position = &D_L00_0029DE00[D_L00_0029E440[face][corner][0]];
            int uv = D_L00_0029E440[face][corner][1];

            FastVecScale(&packet.vertex[corner], position, 1.0f);
            packet.uv[corner][0] = D_L00_0029E760[uv][0];
            packet.uv[corner][1] = D_L00_0029E760[uv][1];
            if (position->v[2] == 0.001432f)
                packet.color[corner] = 0xff0000;
        }
        draw_world_quad((char *)&packet, (float *)&scratch.frame, 0);
    }
}



/* func_L00_003F4210 uses its dedicated debug-profile unit. */

/* func_L00_003F4B68 uses its dedicated quadword-copy profile. */


/* Computes two sub-record addresses of a 192-byte block and hands three of its sub-records to four helpers, threading a second argument through two of them. */
/* Builds three axis vectors for the object from its direction and a reference vector. */
void func_L00_003F51A0(char *moby, char *reference)
{
    char *base = moby + 192;
    char *other = moby + 208;
    float one = 1.0f;

    func_00282F20_1(base, (char *)(*(int *)(moby + 104)), one);
    FastVecCross(other, base, reference);
    func_00282F20_1(other, other, one);
    FastVecCross(moby + 224, other, base);
}

/* func_L00_003F5238 is in L00_003F5238-helpers.c. */

/* func_L00_003F5390 is in L00_003F5390-g8.c. */

/* Does nothing. */
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
/* Updates the Vaporizer by running its three passes; it keeps running while any pass has work and ends when all are done. */
void func_L00_003F5660(char *moby)
{
    int chainActive = UpdateVaporizerJointChain(moby);
    int passB = UpdateBoltTrailSample(moby);
    int recordCount = UpdateVaporizerTimedRecords((int *)moby);

    if (chainActive == 0 && passB == 0 && recordCount == 0) {
        if (*(unsigned char *)(moby + 0x20) == 2) {
            func_0029F338_1(moby);
        }
    } else {
        ref_L00_003F5660_00(DrawVaporizerEffects, moby);
    }
}

/* Reads the short at +26 of the object held at +104, calls a callee with (3076, that short), then calls one callee with this when the result is zero or three callees with this when it is non-zero. */
/* Draws the Vaporizer effects, or removes the object if its table entry is gone. */
void func_L00_003F56F0(char *moby)
{
    if (IsSavedRecordValue(3076 /* Vaporizer */, *(short *)(*(int *)(moby + 104) + 26)) == 0)
        func_0029F338_1(moby);
    else {
        RenderTwoLayerEffectStrip(moby);
        DrawBoltBeamRings(moby);
        DrawBoltSparks(moby);
    }
}

/* func_L00_003F5750 is in L00_003EE100-g8.c. */

/* func_L00_003F5870 is in L00_003F5870-g8.c. */

/* func_L00_003F5B10 is in L00_003F5B10-g8.c. */


/* func_L00_003F6168 is in L00_003F6168-helpers-g8.c. */

/* func_L00_003F6308 is defined in L00_003F6308-rings-g8.c. */

/* func_L00_003F6900 is defined in L00_003F6900-g8-qcopy.c. */

/* Walks 120 records of 64 bytes from a base resolved through two descriptor lookups; for each live record it calls an update helper and, when that reports zero, counts it and advances a float pair by one step, clearing the record's live flag otherwise. */
/* Updates up to 120 timed records of the Vaporizer and returns how many are still running. */
int func_L00_003F6A58(int *moby)
{
    int i;
    int count = 0;
    char *base;
    char *entry;
    char *timer;

    entry = *(char **)((char *)moby + 104);
    base = GetSlotBody(3076 /* Vaporizer */, *(short *)(entry + 26));
    base = base + *(int *)(GetSlotHeader(3076 /* Vaporizer */, *(short *)(entry + 26)) + 4);
    timer = base + 16;
    entry = base;

    for (i = 119; i >= 0; i--) {
        if (*(short *)(entry + 18) != 0) {
            if (FastDecTimer(timer) != 0) {
                *(short *)(entry + 18) = 0;
            } else {
                count++;
                *(float *)(entry + 24) = FastAddRotations(*(float *)(entry + 24), *(float *)(entry + 28));
            }
        }
        timer += 64;
        entry += 64;
    }
    return count;
}


extern void func_002AD0E0(char *a0, char *a1, char *a2, char *a3, char *a4, char *a5);

extern void func_0029F338(char *a0);

extern int func_00282978(char *a0);

extern void ref_L00_003F71E8_01(void *p, char *obj);

extern void ref_L00_003F71E8_00(void);

/* Moves an object along with its target and removes it when its timer has run out. */
void func_L00_003F71E8(char *moby)
{
    char *vars = *(char **)(moby + 0x68);

    if (*(char **)(vars + 0x3C) != 0) {
        TransformPointAndRotationByParent(moby, *(char **)(vars + 0x3C), moby + 0x10, moby + 0xF0, moby + 0x10, moby + 0xF0);
    }
    if (FastDecTimer(vars) == 0) {
        FastDecTimer(vars + 4);
        ref_L00_003F71E8_01((void *)ref_L00_003F71E8_00, moby);
    } else {
        MarkMobySpawned(moby);
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

    InitQuadPacketState(&packet, texture, 1, 0x80);
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
    FastVecSub((char *)&frame.row[0], (char *)&D_L00_001B8C80.x_140, (char *)&frame.position);
    vec_scale_to_length((char *)&frame.row[0], (char *)&frame.row[0], 1.0f);
    FastVecCross((char *)&frame.row[1], (char *)&frame.row[0], (char *)&D_0018A0E0);
    vec_scale_to_length((char *)&frame.row[1], (char *)&frame.row[1], 1.0f);
    FastVecCross((char *)&frame.row[2], (char *)&frame.row[1], (char *)&frame.row[0]);
    if (roll != 0.0f) {
        scratch.angles.word = 0;
        scratch.angles.v[0] = roll;
        euler_rotation_basis(scratch.u.rotation, &scratch.angles);
        multiply_matrix3x3(frame.row, frame.row, scratch.u.rotation);
    }
    FastVecScale(&scratch.angles, &frame.row[0], offset);
    FastVecAdd(&frame.position, &frame.position, &scratch.angles);
    {
        Vector *vertex = packet.vertex;
        int count;
        corner = D_L00_001AA310;
        count = 3;
        do {
            FastVecScale(vertex, corner, size);
            ++corner;
            --count;
            transform_vector(vertex, vertex, &frame);
            ++vertex;
        } while (count >= 0);
    }
    VU1_addGSregister(0x47, 0x31001ULL);
    draw_world_quad((char *)&packet, 0, 0);
    if (mode != 0) {
        int i;

        qcopy(&scratch.u.projection.center, &packet.vertex[0]);
        {
            Vector *vertex = &packet.vertex[1];
            int count;
            count = 2;
            do {
                FastVecAdd(&scratch.u.projection.center, &scratch.u.projection.center,
                              vertex);
                ++vertex;
                --count;
            } while (count >= 0);
        }
        FastVecScale(&scratch.u.projection.center, &scratch.u.projection.center, 0.25f);
        for (i = 0; i < 4; ++i) {
            FastVecSub((char *)&scratch.u.projection.point, (char *)&packet.vertex[i],
                          (char *)&scratch.u.projection.center);
            FastVecScale(&scratch.u.projection.point, &scratch.u.projection.point, 0.8f);
            FastVecAdd(&scratch.u.projection.point, &scratch.u.projection.center,
                          &scratch.u.projection.point);
            ProjectWorldToScreen((int)&scratch.u.projection.point, &packet.uv[i][0], &packet.uv[i][1]);
            if (RandomIntBelow(1) == 0) {
                packet.uv[i][0] += RandomFloatRange(-jitter, jitter);
                packet.uv[i][1] += RandomFloatRange(-jitter, jitter);
            }
            if (packet.uv[i][0] > 1.0f) packet.uv[i][0] = 1.0f;
            else if (packet.uv[i][0] < 0.0f) packet.uv[i][0] = 0.0f;
            if (packet.uv[i][1] > 1.0f) packet.uv[i][1] = 1.0f;
            else if (packet.uv[i][1] < 0.0f) packet.uv[i][1] = 0.0f;
        }
    } else {
        int i;

        for (i = 0; i < 4; ++i) {
            ProjectWorldToScreen((int)&packet.vertex[i], &packet.uv[i][0], &packet.uv[i][1]);
            if (RandomIntBelow(1) == 0) {
                packet.uv[i][0] += RandomFloatRange(-jitter, jitter);
                packet.uv[i][1] += RandomFloatRange(-jitter, jitter);
            }
            if (packet.uv[i][0] > 1.0f) packet.uv[i][0] = 1.0f;
            else if (packet.uv[i][0] < 0.0f) packet.uv[i][0] = 0.0f;
            if (packet.uv[i][1] > 1.0f) packet.uv[i][1] = 1.0f;
            else if (packet.uv[i][1] < 0.0f) packet.uv[i][1] = 0.0f;
        }
    }
    InitQuadPacketState(&packet, -1, 1, 0x80);
    packet.flags = 0x8000000054ULL;
    VU1_addGSregister(0x47, 0x33001ULL);
    draw_world_quad((char *)&packet, 0, 0);
    VU1_addGSregister(0x47, 0x5360bULL);
}

/* func_L00_003F87B0 is in L00_003F87B0.c. */

/* Same body as 23626ad829daa908 with the node field 4 bytes earlier: calls a helper with a referenced node and three identity bytes, then copies them into a linked record guarded by a flag bit and a non-zero leading short. */
/* Copies three color bytes of the object into the record linked to it, if that record is in use. */
void func_L00_003F89F8(Obj_Fe48725c6 *link)
{
    Node24_Fe48725c6 *node;
    Node16_Fe48725c6 *entry;
    int blueByte;

    func_002A0488_1(link->f24, link->u.b.b4, link->u.b.b5, link->u.b.h6);
    node = link->f24;
    if ((node->h52 & 0x20) == 0)
        return;
    entry = ((Node104_Fe48725c6 *)node->p104)->p16;
    if (entry == 0)
        return;
    if (entry->h0 == 0)
        return;
    entry->b4 = link->u.b.b4;
    entry->b5 = link->u.f4 >> 8;
    blueByte = link->u.b.h6;
    entry->b6 = blueByte;
}

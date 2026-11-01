#include "include_asm.h"

#define RAC2_T_V4_F213135AA
#define RAC2_T_WORKER_F9E2CD219
#define RAC2_T_OWNER_F9E2CD219

typedef int s32;

typedef unsigned char u8;

typedef unsigned int u32;



typedef float f32;

typedef unsigned long long NativeCompactU64;

typedef union {
    s32 field00[4];
    struct {
        NativeCompactU64 field00;
        short field08;
        short field0A;
        unsigned short field0C;
        unsigned short field0E;
    } compact;
} NativeCompactRow16;

typedef struct {
    u8 field00[6];
    short field06;
    u8 field08[4];
    f32 field0C;
    u32 field10;
    u32 field14;
    u32 field18;
    u32 field1C;
    u32 field20;
} NativeCompactHeader;

typedef struct { float x, y, z, w; } V4_F213135aa;

typedef struct {
    unsigned char pad00[76];
    short field4C;
    unsigned char pad4E[2];
    int field50;
    float field54;
    float field58;
} Worker_F9e2cd219;

typedef struct {
    unsigned char pad00[104];
    Worker_F9e2cd219 *child;
} Owner_F9e2cd219;

typedef struct {
    float x;
    float y;
    float z;
    int w;
} MotionVector;

typedef struct {
    unsigned char pad00[0x70];
    void *motion;
    float field74;
    float field78;
    float field7C;
} MotionChild;

typedef struct {
    unsigned char pad00[0x10];
    float field10;
    float field14;
    float field18;
    unsigned char pad1C[8];
    void *field24;
    unsigned char pad28[0x40];
    void *field68;
} MotionState;

typedef struct {
    unsigned char pad00[0x24];
    void *owner;
    unsigned char pad28[8];
} MotionEntry;

extern s32 func_00282A18(s32 value);

extern void func_00283388 (float *local);

extern void func_00300AA8 (char *object, float a, float b, int flags, float d, float *local);

extern float F213135aa_FUN_002A7878(float a, float b);

extern void F213135aa_FUN_002833F0(char *a, char *b);

extern void F213135aa_FUN_00282F20(char *a, char *b, float f);

extern void F213135aa_FUN_00282CF0(char *a, char *b, char *c);

extern void F213135aa_FUN_00282DD8(char *a, char *b, char *c);

extern void F213135aa_FUN_002AB668(char *a, char *b, float f);

extern int F6eb4f363_FUN_002A77E0(int mode);

extern float F6eb4f363_FUN_002A90F8(char *object, char *local);

extern void F6eb4f363_FUN_00282D30(char *local, int value, float scale);

extern float F6eb4f363_FUN_002A7878(float low, float high);

extern void F6eb4f363_FUN_002BF728(char *object, char *local, float amount, float base);

extern float F9e2cd219_FUN_002A7798(float value);

extern void F9e2cd219_FUN_002ACF68(void *out, void *in, void *tmp, int mode, float value);

extern void F9e2cd219_FUN_00305310(void *owner, void *out);

extern void F9e2cd219_FUN_00307AD0(void *owner, void *out);

    extern void func_0029FCC0(void *, int, void *);

    extern int func_00277258(void *, int, void *, float);

    extern int D_001BAF9C;

extern void func_00282CF0(void *out, void *a, void *b);

extern void func_00282CC0(void *out, void *a, void *b);

extern char D_00227DA0[];

extern void func_00300330(void *);

extern char ref_00305798_00[];

extern void ref_00305798_01(void *out, void *in, float scale);

extern void ref_00305798_02(void *out, void *a, void *b);

extern void ref_00305798_03(void *owner, void *entry, void *out);

extern int func_00282948(void *);

extern void func_00305C10(void *);

extern void func_00305798(void *);

extern void func_0029FCC0(void *, int, void *);

extern int func_00277258(void *, int, void *, float);

extern int D_001BAF9C;

extern char D_00228610[];

extern void func_00300330(void *);

extern int func_00282948(void *p);

extern void func_00307FC0(void *p);

typedef struct {
    u8 pad00[0x80]; float position[4];
    u8 pad90[0x288]; float previousHeight;
    u8 pad31C[0x1514]; char *field1830;
    u8 pad1834[0xA5C]; char *field2290; int state;
    u8 pad2298[0x1C]; u8 field22B4;
} SurfacePlayer;
extern SurfacePlayer D_00189E20;
extern char D_001A8BD0[] __attribute__((sda));
typedef struct {
    u8 pad000[0x140]; float position[4];
    u8 pad150[0x3C8 - 0x150]; float heightOffset;
} SurfaceCamera;
extern SurfaceCamera D_001B5200;
extern V4_F213135aa ref_00302DA0_04[];
extern void ref_00302DA0_00(int, int, float);
extern int ref_00302DA0_01(int, int);
extern void ref_00302DA0_02(void);
extern int ref_00302DA0_03(void);
extern int func_00303E20(char *, void *, int *, int *);
extern void func_002A7750(u8 *, u8, s32);
extern float func_002AA140(float, float, float);
extern void func_002ABBB8(void *, void *, void *, float, float, int, int, int,
    float, float, float, float, int, float, int, int, int, int, int);

/* Relocates serialized header offsets and compacts each row in its original storage. */

#ifndef RAC2_T_V4_F213135AA
#endif

#ifndef RAC2_T_WORKER_F9E2CD219
#endif

#ifndef RAC2_T_OWNER_F9E2CD219
#endif

/* relocates serialized offsets and compacts16-byte rows in their original storage using captured sourcewords */
NativeCompactHeader *func_00300618(NativeCompactHeader *header) {
    u32 base = (u32)header;
    NativeCompactRow16 *source;
    s32 index;
    header->field10 += base;
    header->field14 += base;
    header->field18 += base;
    header->field1C += base;
    if (header->field20 != 0) header->field20 += base;
    index = 0;
    source = (NativeCompactRow16 *)header->field18;
    header->field0C *= 0.0032116016f;
    if (header->field06 > 0) {
        do {
            s32 first = source->field00[0];
            s32 second = source->field00[1];
            s32 third = source->field00[2];
            s32 fourth = source->field00[3];
            ((NativeCompactRow16 *)header->field18)[index].compact.field0A = first >> 4;
            source++;
            ((NativeCompactRow16 *)header->field18)[index].compact.field08 = second >> 4;
            ((NativeCompactRow16 *)header->field18)[index].compact.field0C = func_00282A18(third);
            ((NativeCompactRow16 *)header->field18)[index].compact.field0E = func_00282A18(fourth);
            ((NativeCompactRow16 *)header->field18)[index].compact.field00 = 0;
            index++;
        } while (index < header->field06);
    }
    return header;
}

typedef struct {
    char pad00[4];
    short field04;
    char pad06[2];
    short field08;
    short field0A;
    char pad0C[0x14];
    u32 field20;
} NativeSpawnHeader;

typedef struct {
    char pad00[0x16];
    short field16;
} NativeSpawnRow;

void func_00300748(NativeSpawnHeader *header, char *base, float f)
{
    extern void func_00283AF0(void *a, void *b);
    extern float func_00283CB8(float value);
    extern void func_00283B48(void *a, void *b, void *c, float d);
    extern void func_00283A58(void *a, void *b, void *c, void *d);
    extern void func_00283788(void *a, void *b, void *c);

    int count = (int)f;
    int i;
    int j;
    char local[0x30];
    char *row;
    NativeSpawnRow *record;
    float value;

    row = (char *)header->field20 + count * header->field0A;
    for (i = 0; i < header->field04; i++)
        func_00283AF0(row + i * 0x18, base + i * 0x40);

    value = func_00283CB8(f);
    if (value > 0.001f) {
        int index = count + 1;
        int pick = (index < header->field08) ? index : 0;
        for (row = (char *)header->field20 + pick * header->field0A, i = 0;
                i < header->field04; i++, row += 0x18) {
            func_00283AF0(row, local);
            func_00283B48(base + i * 0x40, base + i * 0x40, local, value);
        }
    }

    for (record = (NativeSpawnRow *)((char *)header->field20 + (int)f * header->field0A),
            j = 0; j < header->field04; j++, record++) {
        func_00283A58(base + j * 0x40, base + j * 0x40 + 0x10, base + j * 0x40 + 0x20,
                base + j * 0x40);
        if (record->field16 >= 0)
            func_00283788(base + j * 0x40, base + (record->field16 << 6), base + j * 0x40);
    }
}


/* scales a float argument by a field of the object into a stack buffer, then calls a second routine with the object, its flags, the buffer and three float arguments */
void func_00300968 (char *object, int flags, float a, float b, float c, float d)
{
  float local[16];

  if (flags >> 24)
    {
      c = c * *(float *) (object + 12);
      func_00283388 (local);
      local[0] = c;
      local[10] = c;
      func_00300AA8 (object, a, b, flags, d, local);
    }
}

void func_00300A00(char *object, int flags, float a, float b, float c, float d, float e)
{
    float local[16];
    if (flags >> 24) {
        func_00283388(local);
        local[0] = c * *(float *)(object + 12);
        local[10] = d * *(float *)(object + 12);
        func_00300AA8(object, a, b, flags, e, local);
    }
}

INCLUDE_ASM("asm/game", func_00300AA8);

/* func_00300F58 is defined in 00300F58-g8.c. */


INCLUDE_ASM("asm/game", func_00301F18);

int func_003022A0(char *obj, char *obj2, float x, float y)
{
    V4_F213135aa m0, m1, m2;
    char *s1;
    char *s3;
    float f22;

    s1 = *(char **)(obj + 104);
    if (*(unsigned char *)(obj + 32) == 4)
        return 0;
    f22 = 0.0f;
    if (x == 0.0f)
        x = F213135aa_FUN_002A7878(-30.0f, 30.0f) * 1.7453294247388839721680e-02f;
    if (y == 0.0f)
        y = F213135aa_FUN_002A7878(f22, 30.0f) * 1.7453294247388839721680e-02f;
    s3 = s1 + 32;
    if (*(unsigned char *)(obj + 32) == 3) {
        F213135aa_FUN_002833F0((char *)&m0, s1 + 16);
        F213135aa_FUN_00282F20(s3, (char *)&m2, 1.3333334028720855712891e-01f);
    }
    *(float *)(s1 + 100) = f22;
    *(float *)(s1 + 76) = x;
    *(float *)(s1 + 72) = y;
    *(char **)(s1 + 96) = obj2;
    F213135aa_FUN_00282CF0((char *)&m1, obj2 + 16, obj + 16);
    s1 = s1 + 48;
    F213135aa_FUN_00282DD8((char *)&m0, s3, (char *)&m1);
    F213135aa_FUN_00282F20(s1, (char *)&m0, 1.0f);
    F213135aa_FUN_002AB668(s1, s1, 2.0943954586982727050781e-01f);
    *(unsigned char *)(obj + 32) = 4;
    return 1;
}

int func_00302440(char *obj, char *obj2)
{
    if (*(u8 *)(obj + 32) != 3)
        return 3;
    return func_003022A0(obj, obj2, 0.0f, 0.0f);
}



INCLUDE_ASM("asm/game", func_00302470);

INCLUDE_ASM("asm/game", func_00302848);

/* func_00302A20 uses the quadword-copy profile in 00300618-qcopy.c. */

/* func_00302A88 uses the debug profile in 00300618-state.c. */



/* Resolve the player onto the surface grid and blend their height into it. */
void func_00302DA0(char *object)
{
    char *state=*(char **)(object+0x68);
    float center, ceiling, blend;
    int index;
    if (*(int *)(state+0x98)==-1) {
        if (func_00303E20(object,D_00189E20.position,(int *)(state+0x90),(int *)(state+0x94))) {
            *(int *)(state+0x98)=0;
            func_002A7750((u8 *)object,5,-1);
        }
    }
    if (*(int *)(state+0x98)>=0) {
        center=*(float *)(state+0x70)+*(float *)(state+4);
        ceiling=center+*(float *)(state+0x34)+1.0f;
        if (D_001B5200.position[2]<=ceiling && center-*(float *)(state+0x34)-1.0f<=D_001B5200.position[2])
            D_001B5200.heightOffset=ceiling-D_001B5200.position[2];
        { SurfacePlayer *player = &D_00189E20;
        if (player->state!=0x38 && player->state!=0x79 &&
            (player->state!=0x39 || *(int *)(*(char **)(player->field2290+0x24)+0x1f0)) &&
            player->state!=0x7a) {
            if (player->state==0x31) {
                func_002ABBB8(player->field1830, D_001A8BD0, 0, 0.0f, 0.0f, 10, 3, 16,
                    4.0f, 2.0f, 9.0f, 1.0f, -1, 15.0f, 1, 1, -1, 0, 0x00810001);
                ref_00302DA0_00(0x88,0,0.0f);
                player->field1830=0;
                ref_00302DA0_01(0,1);
                ref_00302DA0_02();
                player->previousHeight=player->position[2];
            }
            if (player->field22B4)
                ref_00302DA0_01(0x7a,1);
            else if (*(int *)(*(char **)(player->field2290+0x24)+0x1f0))
                ref_00302DA0_01(0x79,1);
            else ref_00302DA0_01(0x39,1);
        }
        }
        if (D_00189E20.state==0x31 && *(int *)(state+0x98)>5)
            ref_00302DA0_03();
        blend=(float)*(int *)(state+0x98)*0.05f;
        if (blend>1.0f) blend=1.0f;
        index=*(int *)(state+0x40)*64+*(int *)(state+0x94)*8+*(int *)(state+0x90);
        D_00189E20.position[2]=func_002AA140(D_00189E20.position[2],
            ref_00302DA0_04[index].z-(float)*(int *)(state+0x98)*0.016666668f,blend);
        ++*(int *)(state+0x98);
    }
}

typedef unsigned long long u64;

typedef struct {
    u8 pad00[0x40];
    u32 w40;
    u32 w44;
    u32 w48;
    u32 w4c;
    u32 w50;
    u32 w54;
    u32 w58;
    f32 f5c;
    f32 f60;
    u32 w64;
    f32 f68;
    f32 f6c;
    u64 l70;
    u64 l78;
    u64 l80;
    u64 l88;
} Pkt_00303070;

extern char D_00189EA0[];
extern int func_002ACBC8(void *, int);
extern unsigned long func_0027C878(int);
extern void func_00303738(void *, void *, int, int, int);
extern void func_00280B90(void *, void *, int);

void func_00303070(u8 *obj)
{
    u8 *p = *(u8 **)(obj + 0x68);
    int v = *(int *)(p + 0x44);

    if (v != -1 && func_002ACBC8(D_00189EA0, v) != 0 && (*(u32 *)(p + 0x4C) & 4) == 0) {
        Pkt_00303070 pk;
        int i = 0;
        int j;

        pk.w50 = 0;
        pk.w4c = 0x80808080;
        pk.w48 = 0x80808080;
        pk.w44 = 0x80808080;
        pk.w40 = 0x80808080;
        pk.w54 = 0;
        pk.w58 = 0;
        pk.f5c = 1.0f;
        pk.f60 = 1.0f;
        pk.w64 = 0;
        pk.f68 = 1.0f;
        pk.f6c = 1.0f;
        pk.l78 = func_0027C878(*(int *)(p + 0x48) + 0x3F);
        pk.l80 = 0xFF9000000260ULL;
        pk.l88 = 0x8000000088ULL;
        pk.l70 = 0;
        do {
            j = 0;
            do {
                func_00303738(obj, &pk, j, i, 0);
                func_00303738(obj, &pk, j + 1, i, 1);
                func_00303738(obj, &pk, j, i + 1, 2);
                func_00303738(obj, &pk, j + 1, i + 1, 3);
                func_00280B90(&pk, 0, 0);
                j = j + 1;
            } while (j < 7);
            i = i + 1;
        } while (i < 7);
    }
}

INCLUDE_ASM("asm/game", func_00303210);

/* func_00303568 is defined in 00303568.c. */




/* func_00303E20 is defined in 00303E20.c. */

/* func_00304128 is defined in 00304128.c. */

/* func_00304210 is defined in 00304210-g8.c. */

/* func_00304AD0 uses the profile in 00304AD0-g8-qcopy.c. */

void func_00304B68(char *object)
{
    char local[16];
    float base;
    int value = *(int *)(object + 104);

    if (F6eb4f363_FUN_002A77E0(5))
        return;
    base = F6eb4f363_FUN_002A90F8(object + 16, local);
    F6eb4f363_FUN_00282D30(local, value, 0.25f);
    F6eb4f363_FUN_002BF728(object + 16, local, F6eb4f363_FUN_002A7878(0.05f, 0.1f) * 210000.0f, base);
}

void func_00304C18(void *object) {
    char local[16];
    func_0029FCC0(object, 0, local);
    if (func_00277258(local, 2, object, 0.2f) && D_001BAF9C > 0)
        *((unsigned char *)object + 0x20) = 8;
}

/* Takes the position of the owner's child, and lets the child's motion take it over
   once the motion is of the right kind and is not busy. */
void func_00304C78(void *object)
{
    MotionVector local;
    float tmp[4];
    MotionChild *child;
    MotionState *motion;

    local.w = 0;
    child = *(MotionChild **)((char *)object + 0x68);
    local.x = child->field74;
    local.y = child->field78;
    local.z = child->field7C;
    func_00282CF0(tmp, (char *)child->motion + 0x10, &local);
    func_00282CC0((char *)object + 0x10, tmp, (char *)object + 0x10);
    motion = child->motion;
    child->field74 = motion->field10;
    child->field78 = motion->field14;
    child->field7C = motion->field18;
    if (*(short *)((char *)motion->field24 + 0x46) == 0x12) {
        if (*(u8 *)((char *)motion->field68 + 0x14) == 0)
            *(u8 *)((char *)object + 0x20) = 7;
    }
}

/* func_00304D38 is defined in 00304D38-g8.c. */


/* func_00305058 is defined in 00305058-qcopy.c. */

void func_00305228(Owner_F9e2cd219 *self)
{
    Worker_F9e2cd219 *child = self->child;

    F9e2cd219_FUN_002ACF68((char *)child + 48, (char *)child + 16, (char *)child + 32, 0,
            F9e2cd219_FUN_002A7798(child->field54));

    child->field54 = child->field54 + child->field58;
    F9e2cd219_FUN_00305310(self, (char *)child + 48);

    if (child->field54 > 0.9f)
        child->field50 = 1;
    else
        child->field50 = 0;

    if (child->field54 >= 1.0f) {
        child->field54 = 1.0f;
        child->field4C = 1;
    }
}



void func_00305418(void) {
    func_00300330(D_00227DA0);
}

INCLUDE_ASM("asm/game", func_003054E8);

/* The table of hundred objects and the three helpers it uses sit at another
   address in every program, so they have no address of their own. */

/* Walks the table of objects and lets every entry the owner owns move it. */
void func_00305798(void *owner)
{
    s32 i;
    char *base = ref_00305798_00;
    float local[4];

    for (i = 0; i < 100; i++) {
        MotionEntry *entry = (MotionEntry *)(base + i * 0x30);
        if (entry->owner == owner) {
            ref_00305798_01(local, base + i * 0x30 + 0x10, 2.1f);
            ref_00305798_02(local, entry, local);
            ref_00305798_03(owner, entry, local);
        }
    }
}

void func_00305838(char *p)
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
    *(float *)(p + 8) = -2.0f;
    *(float *)(p + 24) = 2.0f;
    *(float *)(p + 40) = -2.0f;
    *(float *)(p + 56) = 2.0f;
    *(float *)(p + 4) = -2.0f;
    *(float *)(p + 36) = 2.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 0x0000FF9000000260LL;
    *(float *)(p + 20) = -2.0f;
    *(float *)(p + 52) = 2.0f;
    *(float *)(p + 60) = 1.0f;
}

void func_003058C8(void *owner)
{
    void *p = *(void **)((char *)owner + 0x68);
    if (func_00282948((char *)p + 0x44) == 0)
        func_00305C10(owner);
    func_00305798(owner);
}

typedef struct { float x, y, z, w; } EffectVector __attribute__((aligned(16)));
typedef struct {
    EffectVector position[4];
    u32 color[4];
    float uv[4][2];
    unsigned long primitive, texture, mode, registers;
} EffectPacket;
typedef struct { u8 prefix[0x140]; EffectVector position; } EffectCameraView;
extern unsigned long func_0027C878(int);
extern int func_002A7820(int, int);
extern float func_002A7878(float, float);
extern float func_002A7940(void);
extern float func_00283248(float, float);
extern float func_00282E80(void *, void *);
extern void func_00283410(void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282D30(void *, void *, float);
extern void func_00280B90(void *, void *, int);

extern EffectCameraView ref_00305910_00;

/* Draw three shrinking, independently colored layers facing the camera. */
void func_00305910(void *owner, float *position)
{
    EffectPacket packet;
    EffectVector matrix[4];
    float rotation[4], offset[4];
    u32 color;
    float distance, scale;
    func_00305838((char *)&packet);
    packet.texture = func_0027C878(44);
    packet.mode = 0x0000ff9000000260UL;
    packet.registers = 0x0000008000000048UL;
    packet.primitive = 0;
    color = ((u32)func_002A7820(48,64) << 24) + 0x8183f;
    rotation[3] = 0;
    packet.color[0] = packet.color[1] = packet.color[2] = packet.color[3] = color;
    rotation[2] = func_00283248(ref_00305910_00.position.x-position[0], ref_00305910_00.position.y-position[1]);
    distance = func_00282E80(position, &ref_00305910_00.position);
    rotation[1] = -func_00283248(distance, ref_00305910_00.position.z-position[2]);
    rotation[0] = func_002A7940();
    func_00283410(matrix,rotation);
    func_00282CF0(offset,&ref_00305910_00.position,position);
    func_00282F20(offset,offset,0.25f);
    matrix[3].x = position[0] + offset[0];
    matrix[3].y = position[1] + offset[1];
    matrix[3].z = position[2] + offset[2];
    matrix[3].w = 1.0f;
    scale = func_002A7878(0.3f,0.4f);
    func_00282D30(&packet.position[0],&packet.position[0],scale);
    func_00282D30(&packet.position[1],&packet.position[1],scale);
    func_00282D30(&packet.position[2],&packet.position[2],scale);
    func_00282D30(&packet.position[3],&packet.position[3],scale);
    func_00280B90(&packet,matrix,0);
    func_00282D30(&packet.position[0],&packet.position[0],0.5f);
    func_00282D30(&packet.position[1],&packet.position[1],0.5f);
    func_00282D30(&packet.position[2],&packet.position[2],0.5f);
    func_00282D30(&packet.position[3],&packet.position[3],0.5f);
    color = ((u32)func_002A7820(64,127) << 24) + 0x103080;
    packet.color[0] = packet.color[1] = packet.color[2] = packet.color[3] = color;
    func_00280B90(&packet,matrix,0);
    func_00282D30(&packet.position[0],&packet.position[0],0.5f);
    func_00282D30(&packet.position[1],&packet.position[1],0.5f);
    func_00282D30(&packet.position[2],&packet.position[2],0.5f);
    func_00282D30(&packet.position[3],&packet.position[3],0.5f);
    color = ((u32)func_002A7820(64,127) << 24) + 0x7f7f7f;
    packet.color[0] = packet.color[1] = packet.color[2] = packet.color[3] = color;
    func_00280B90(&packet,matrix,0);
}




extern EffectCameraView ref_00306040_00;
/* Packet initialization has distinct boot and level catalogue identities. */
extern void ref_00306040_01(void *packet);

/* Draw three shrinking, independently colored layers facing the camera. */
void func_00306040(void *owner, float *position)
{
    EffectPacket packet;
    EffectVector matrix[4];
    float rotation[4], offset[4];
    u32 color;
    float distance, scale;
    ref_00306040_01(&packet);
    packet.texture = func_0027C878(11);
    packet.mode = 0x0000ff9000000260UL;
    packet.registers = 0x0000008000000048UL;
    packet.primitive = 0;
    color = ((u32)func_002A7820(48,64) << 24) + 0x80;
    rotation[3] = 0;
    packet.color[0] = packet.color[1] = packet.color[2] = packet.color[3] = color;
    rotation[2] = func_00283248(ref_00306040_00.position.x-position[0], ref_00306040_00.position.y-position[1]);
    distance = func_00282E80(position, &ref_00306040_00.position);
    rotation[1] = -func_00283248(distance, ref_00306040_00.position.z-position[2]);
    rotation[0] = func_002A7940();
    func_00283410(matrix,rotation);
    func_00282CF0(offset,&ref_00306040_00.position,position);
    func_00282F20(offset,offset,0.25f);
    matrix[3].x = position[0];
    matrix[3].y = position[1];
    matrix[3].z = position[2];
    matrix[3].w = 1.0f;
    scale = func_002A7878(0.03f,0.0625f);
    func_00282D30(&packet.position[0],&packet.position[0],scale);
    func_00282D30(&packet.position[1],&packet.position[1],scale);
    func_00282D30(&packet.position[2],&packet.position[2],scale);
    func_00282D30(&packet.position[3],&packet.position[3],scale);
    func_00280B90(&packet,matrix,0);
    func_00282D30(&packet.position[0],&packet.position[0],0.5f);
    func_00282D30(&packet.position[1],&packet.position[1],0.5f);
    func_00282D30(&packet.position[2],&packet.position[2],0.5f);
    func_00282D30(&packet.position[3],&packet.position[3],0.5f);
    color = ((u32)func_002A7820(64,127) << 24) + 0x1f1f1f;
    packet.color[0] = packet.color[1] = packet.color[2] = packet.color[3] = color;
    func_00280B90(&packet,matrix,0);
    func_00282D30(&packet.position[0],&packet.position[0],0.5f);
    func_00282D30(&packet.position[1],&packet.position[1],0.5f);
    func_00282D30(&packet.position[2],&packet.position[2],0.5f);
    func_00282D30(&packet.position[3],&packet.position[3],0.5f);
    color = ((u32)func_002A7820(64,127) << 24) + 0x7f7f7f;
    packet.color[0] = packet.color[1] = packet.color[2] = packet.color[3] = color;
    func_00280B90(&packet,matrix,0);
}






/* func_00307298 uses the profile in 00307298-g8-qcopy.c. */

void func_00307330(char *object)
{
    char local[16];
    float base;
    int value = *(int *)(object + 104);

    if (F6eb4f363_FUN_002A77E0(5))
        return;
    base = F6eb4f363_FUN_002A90F8(object + 16, local);
    F6eb4f363_FUN_00282D30(local, value, 0.25f);
    F6eb4f363_FUN_002BF728(object + 16, local, F6eb4f363_FUN_002A7878(0.05f, 0.1f) * 210000.0f, base);
}

void func_003073E0(void *owner)
{
    char local[16];
    func_0029FCC0(owner, 0, local);
    if (func_00277258(local, 2, owner, 0.25f) && D_001BAF9C > 0)
        *((unsigned char *)owner + 0x20) = 8;
}

/* The same as func_00304C78: the retail holds the two copies byte for byte the same. */
void func_00307440(void *object)
{
    MotionVector local;
    float tmp[4];
    MotionChild *child;
    MotionState *motion;

    local.w = 0;
    child = *(MotionChild **)((char *)object + 0x68);
    local.x = child->field74;
    local.y = child->field78;
    local.z = child->field7C;
    func_00282CF0(tmp, (char *)child->motion + 0x10, &local);
    func_00282CC0((char *)object + 0x10, tmp, (char *)object + 0x10);
    motion = child->motion;
    child->field74 = motion->field10;
    child->field78 = motion->field14;
    child->field7C = motion->field18;
    if (*(short *)((char *)motion->field24 + 0x46) == 0x12) {
        if (*(u8 *)((char *)motion->field68 + 0x14) == 0)
            *(u8 *)((char *)object + 0x20) = 7;
    }
}

/* func_00307500 is defined in 00307500-g8.c. */



void func_003079E8(Owner_F9e2cd219 *self)
{
    Worker_F9e2cd219 *child = self->child;

    F9e2cd219_FUN_002ACF68((char *)child + 48, (char *)child + 16, (char *)child + 32, 0,
            F9e2cd219_FUN_002A7798(child->field54));

    child->field54 = child->field54 + child->field58;
    F9e2cd219_FUN_00307AD0(self, (char *)child + 48);

    if (child->field54 > 0.9f)
        child->field50 = 1;
    else
        child->field50 = 0;

    if (child->field54 >= 1.0f) {
        child->field54 = 1.0f;
        child->field4C = 1;
    }
}


void func_00307BD0(void) {
    func_00300330(D_00228610);
}

void func_00307BF0(void *owner) { void *p = *(void **)((char *)owner + 0x68); if (func_00282948((char *)p + 0x44) != 0) return; func_00307FC0(owner); }

void func_00307C30(char *p)
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
    *(float *)(p + 8) = -2.0f;
    *(float *)(p + 24) = 2.0f;
    *(float *)(p + 40) = -2.0f;
    *(float *)(p + 56) = 2.0f;
    *(float *)(p + 4) = -2.0f;
    *(float *)(p + 36) = 2.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 0x0000FF9000000260LL;
    *(float *)(p + 20) = -2.0f;
    *(float *)(p + 52) = 2.0f;
    *(float *)(p + 60) = 1.0f;
}

extern EffectCameraView ref_00307CC0_00;

/* Draw three shrinking, independently colored layers facing the camera. */
void func_00307CC0(void *owner, float *position)
{
    EffectPacket packet;
    EffectVector matrix[4];
    float rotation[4], offset[4];
    u32 color;
    float distance, scale;
    func_00307C30((char *)&packet);
    packet.texture = func_0027C878(44);
    packet.mode = 0x0000ff9000000260UL;
    packet.registers = 0x0000008000000048UL;
    packet.primitive = 0;
    color = ((u32)func_002A7820(48,64) << 24) + 0x8183f;
    rotation[3] = 0;
    packet.color[0] = packet.color[1] = packet.color[2] = packet.color[3] = color;
    rotation[2] = func_00283248(ref_00307CC0_00.position.x-position[0], ref_00307CC0_00.position.y-position[1]);
    distance = func_00282E80(position, &ref_00307CC0_00.position);
    rotation[1] = -func_00283248(distance, ref_00307CC0_00.position.z-position[2]);
    rotation[0] = func_002A7940();
    func_00283410(matrix,rotation);
    func_00282CF0(offset,&ref_00307CC0_00.position,position);
    func_00282F20(offset,offset,0.25f);
    matrix[3].x = position[0] + offset[0];
    matrix[3].y = position[1] + offset[1];
    matrix[3].z = position[2] + offset[2];
    matrix[3].w = 1.0f;
    scale = func_002A7878(0.3f,0.4f);
    func_00282D30(&packet.position[0],&packet.position[0],scale);
    func_00282D30(&packet.position[1],&packet.position[1],scale);
    func_00282D30(&packet.position[2],&packet.position[2],scale);
    func_00282D30(&packet.position[3],&packet.position[3],scale);
    func_00280B90(&packet,matrix,0);
    func_00282D30(&packet.position[0],&packet.position[0],0.5f);
    func_00282D30(&packet.position[1],&packet.position[1],0.5f);
    func_00282D30(&packet.position[2],&packet.position[2],0.5f);
    func_00282D30(&packet.position[3],&packet.position[3],0.5f);
    color = ((u32)func_002A7820(64,127) << 24) + 0x103080;
    packet.color[0] = packet.color[1] = packet.color[2] = packet.color[3] = color;
    func_00280B90(&packet,matrix,0);
    func_00282D30(&packet.position[0],&packet.position[0],0.5f);
    func_00282D30(&packet.position[1],&packet.position[1],0.5f);
    func_00282D30(&packet.position[2],&packet.position[2],0.5f);
    func_00282D30(&packet.position[3],&packet.position[3],0.5f);
    color = ((u32)func_002A7820(64,127) << 24) + 0x7f7f7f;
    packet.color[0] = packet.color[1] = packet.color[2] = packet.color[3] = color;
    func_00280B90(&packet,matrix,0);
}






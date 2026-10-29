#include "common.h"

extern float func_00283B98(float, float);
extern float func_00283BE0(float, float);
extern void func_002833F0(void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_002FEE70(int, void *, int);
extern void func_00300190(void *, void *);
extern void func_00300248(void *, void *);
extern float func_00282DF0(void *);
extern void func_002ACF68(void *, void *, void *, int, float);
extern int func_00277258(void *, int, void *, float);
extern char *D_L00_001BF218;
extern char *D_0018C0B0;
extern char D_L00_001BF230[];
typedef struct { float x, y, z; int unused; float position[4]; } EffectLightRecord;
extern EffectLightRecord D_L00_001C6F40[];
extern float func_00282DB0(void *, void *);
extern void func_00283028(void *, void *, void *);
extern void func_L00_003BD510(void *, void *, int, int);
extern void func_002E5CF8(int, int, void *);
extern void func_L00_003BC998(char *, char *);


extern float func_802EE7A8_1(float x, float y);

extern float func_802EE2E8_1(char *p, float *v);

extern void func_802EE970_1(float *matrix, float *quat);

extern void func_802EE138_1(float *off, float *v, char *p);

extern void func_802EE3D0_1(float *dst, float *src, float angle);

extern void func_802EAC30_1(char *pkt, float *matrix, int mode);

extern void ref_L00_003C1FC8_00(char *p);
extern long long func_002E67A0_2(int id);
extern float func_0031A888_1(void);
extern void func_002EE178_1(char *dst, char *src, float scale);
/* The vector the aim helpers read, at 0x001B8C80. */
typedef struct {
    char pad_000[0x140];
    float x_140;
    float y_144;
    float z_148;
} L00AimVector;

extern L00AimVector D_L00_001B8C80;



/* The 128-bit unit four of these bodies copy whole. */
typedef int Rac2TI128 __attribute__((mode(TI)));

/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_86f665335d9cb905_AnalysisOwner {
    unsigned char prefix_00[0x68];
    void *context_68;
} Rac2Native_86f665335d9cb905_AnalysisOwner;

extern void func_L00_003B9310(Rac2Native_86f665335d9cb905_AnalysisOwner *owner, void *context);

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

extern char D_L00_001BF240[];

extern void func_00282F20_2(void *out, void *in, float scale);

extern void func_00282CC0_6(void *out, void *in1, void *in2);

extern int func_002761F8(void *a, void *b, int mode, void *self, int flag);

extern void func_00282D30_6(void *out, void *in, float scale);

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

extern void func_002FDBD8_2(float scale, Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context,
                                    float *vector, int mode);

extern void func_002A77E0_1(int a);

extern float func_002A7878_2(float a, float b);

extern unsigned int func_002A7820_1(int a, int b);

extern void func_002A7A00(char *p, float a, float b);

extern char *func_002BDCE8(float fa, float fb, float fc, float fd, char *p, int z,
                     char *local, unsigned int v, int one);

extern char D_00189E20_13[];

/* Pass the owner and its pointer at offset 0x68 to the explicitly bound helper; original game role is unknown. */
void func_L00_003B9CB8(Rac2Native_86f665335d9cb905_AnalysisOwner *owner)
{
    func_L00_003B9310(owner, owner->context_68);
}

extern void func_003182C0(void);

/* Calls the measured no-argument callee. */
void func_L00_003BAAD0(void)
{
    func_003182C0();
}

INCLUDE_ASM("asm/levels", func_L00_003BAC30);

/* Integrates motion, reflects a collision, updates the light and emits trail slots. */
char *func_L00_003BB1F8(char *self)
{
    float saved[4] __attribute__((aligned(16)));
    float normal[4] __attribute__((aligned(16)));
    float projection[4] __attribute__((aligned(16)));
    float remainder[4] __attribute__((aligned(16)));
    char *ctx = *(char **)(self + 0x68);
    char *hit = 0;
    char *p;
    EffectLightRecord *light;
    int light_index;
    float f;
    *(float *)(self + 0xF0) = func_00283B98(*(float *)(self + 0xF0), 0.0523598865f);
    *(float *)(self + 0xF4) = func_00283BE0(*(float *)(self + 0xF4), 0.0130899716f);
    *(int *)(self + 0xFC) = 0;
    func_002833F0(self + 0xC0, self + 0xF0);
    qcopy(saved, self + 0x10);
    func_00282CC0(self + 0x10, ctx, self + 0x10);
    func_002FEE70(*(int *)(ctx + 0x50), ctx, 0);
    func_00300190(self + 0x10, self + 0x10);
    func_00300248(ctx, ctx);
    if (func_00282DF0(ctx) != 0.0f && func_00282DF0(ctx + 0x20) != 0.0f)
        func_002ACF68(ctx, ctx, ctx + 0x20, 0, 0.075f);
    if (func_00277258(self + 0x10, 0, self, *(float *)(ctx + 0x4C))) {
        p = D_L00_001BF218;
        if (p && p != D_0018C0B0 && *(short *)(p + 0xAA) != 0x5CA)
            hit = (*(unsigned short *)(p + 0x34) & 0x1000) ? p : 0;
        qcopy(self + 0x10, D_L00_001BF230);
        func_002EE178_1((char *)normal, D_L00_001BF230 + 0x10, 0.0009765625f);
        func_802EE3D0_1(normal, normal, 1.0f);
        func_00283028(ctx, ctx, normal);
        f = func_00282DB0(ctx, normal);
        func_002EE178_1((char *)projection, (char *)normal, f);
        func_802EE138_1(remainder, (float *)ctx, (char *)projection);
        func_002EE178_1(ctx, (char *)projection, 0.85f);
        func_00282CC0(ctx, remainder, ctx);
        func_002EE178_1(ctx + 0x20, ctx + 0x20, 0.95f);
        func_L00_003BD510(D_L00_001BF230 - 0x10, normal, 6, 0x72FF);
        func_L00_003BD510(D_L00_001BF230 - 0x10, normal, 6, 0xFF0000);
        func_002E5CF8(1, 0, self);
    }
    light_index = *(int *)(ctx + 0x5C);
    if (light_index != -1) {
        light = D_L00_001C6F40 + light_index;
        qcopy(light->position, self + 0x10);
        light->position[3] = 4.0f;
        light->x = 0.25f;
        light->y = 0.14f;
        light->z = 1.0f;
        light->unused = 0;
        f = func_002A7878_2(-0.1f, 0.1f);
        light->x += f;
        light->y += f;
        light->z += f;
    }
    if (*(float *)(self + 0x10) < 2.0f || *(float *)(self + 0x10) > 1021.0f ||
        *(float *)(self + 0x14) < 2.0f || *(float *)(self + 0x14) > 1021.0f ||
        *(float *)(self + 0x18) < 2.0f || *(float *)(self + 0x18) > 1021.0f) {
        qcopy(self + 0x10, saved);
        self[0x20] = 3;
    }
    if (*(int *)(ctx + 0x58) < 8)
        func_L00_003BC998(self, (char *)func_002A7820_1(8, 20));
    return hit;
}


extern void func_002FC560(unsigned int reg, unsigned long value);

extern float func_002A7940(void);

extern void func_00281EB8(char *a, int b, unsigned int c, int d, float e, float f,
                          float g);

extern void func_L00_003BBF48(char *a0);

extern void func_L00_003BCDC0(char *a0);

/* Opens the block, lays seven oriented sprites over it from two helper draws and the shared
   colour word, then runs the two slot-table passes and closes the block. */
void func_L00_003BB668(char *a0)
{
    char *ctx;

    ctx = *(char **)(a0 + 0x68);
    func_002FC560(0x47, 0x00053001);

    func_00281EB8(a0 + 0x10, 0x2C,
                  (func_002A7820_1(0x80, 0xC8) << 24) | 0x72FF, 1,
                  func_002A7878_2(0.38500002f, 0.415f) * *(float *)(ctx + 0x4C),
                  -0.01f, func_002A7940());
    func_00281EB8(a0 + 0x10, 0x2D,
                  (func_002A7820_1(4, 0x28) << 24) | 0x00DDB973, 1,
                  *(float *)(ctx + 0x4C) * 1.225f, 0.0f, func_002A7940());
    func_00281EB8(a0 + 0x10, 0x29,
                  (func_002A7820_1(4, 0x28) << 24) | 0x00DDB973, 1,
                  *(float *)(ctx + 0x4C) * 0.6f, 0.0f, func_002A7940());
    func_00281EB8(a0 + 0x10, 0x2A,
                  (func_002A7820_1(4, 0x2D) << 24) | 0x00DDB973, 1,
                  func_002A7878_2(0.975f, 1.025f) * *(float *)(ctx + 0x4C),
                  0.0f, func_002A7940());
    func_00281EB8(a0 + 0x10, 0x2A,
                  (func_002A7820_1(4, 0x2D) << 24) | 0x00DDB973, 1,
                  func_002A7878_2(0.975f, 1.025f) * *(float *)(ctx + 0x4C),
                  0.0f, func_002A7940());
    func_L00_003BBF48(a0);
    func_L00_003BCDC0(a0);
    func_002FC560(0x47, 0x0005360B);
}

INCLUDE_ASM("asm/levels", func_L00_003BB8B8);

INCLUDE_ASM("asm/levels", func_L00_003BBF48);

/* resets a state record: zero words, plus/minus one float flags and two 64-bit fields in the retail store order */
void func_L00_003BC080(char *p)
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

/* Derives a 16-byte element at index-1 from its index-2 and index-3 neighbours through two bound helpers; original game role is unknown. */
void func_L00_003BC400(Vec16_Fc936841d *object, int index)
{
    char local[16];

    func_00282CF0_9(local, (char *)&object[index - 2], (char *)&object[index - 3]);
    func_00282CC0_15((char *)&object[index - 1], (char *)&object[index - 2], local);
}

/* Implemented in L00_003B9CB8-ribbons.c. */

/* Measured partial layout of one 0xB0-byte record of the table at D_L00_0023F060. */
typedef struct Rac2Native_003BC998_Slot {
    unsigned char prefix_00[0x50];
    float f_50;
    float f_54;
    float f_58;
    float f_5C;
    float f_60;
    float f_64;
    float f_68;
    float f_6C;
    float f_70;
    float f_74;
    float f_78;
    float f_7C;
    float f_80;
    float f_84;
    float f_88;
    float f_8C;
    float f_90;
    float f_94;
    void *w_98;
    void *w_9C;
    void *owner_A0;
    unsigned char tail_A4[0xC];
} Rac2Native_003BC998_Slot;

extern Rac2Native_003BC998_Slot D_L00_0023F060[];

extern float func_002A78D8_1(float low, float high);

extern void func_002AF000_1(float *out, float a, float b, float c);

extern void func_00282C88_1(void *p);

/* Claims the first free record of the sixteen 0xB0-byte records at D_L00_0023F060, keeps the
   owner's pointer in it and fills the drawn values. The base and the output pointer are kept
   in their own variables, and the two owner words are stored in the order 0x9C, 0x98, so that
   cc1 keeps the table base and the output pointer in registers and fills the delay slots the
   way retail does. */
void func_L00_003BC998(char *owner, char *arg1)
{
    Rac2Native_003BC998_Slot *base = D_L00_0023F060;
    Rac2Native_003BC998_Slot *slot;
    float *out;
    char *ctx;
    int i;
    float r1;
    float r2;

    ctx = *(char **)(owner + 0x68);
    for (i = 0; i < 16; i++) {
        slot = base + i;
        if (slot->owner_A0 != 0)
            continue;
        slot->owner_A0 = owner;
        out = (float *)((char *)slot + 0x40);
        (*(int *)(ctx + 0x58))++;
        slot->f_50 = func_002A7878_2(-3.14159274f, 3.14159274f);
        slot->f_54 = func_002A7878_2(-3.14159274f, 3.14159274f);
        slot->f_58 = func_002A7878_2(-3.14159274f, 3.14159274f);
        slot->f_74 = func_002A7878_2(-3.14159274f, 3.14159274f);
        slot->f_78 = func_002A7878_2(-3.14159274f, 3.14159274f);
        slot->f_7C = func_002A7878_2(-3.14159274f, 3.14159274f);
        slot->f_5C = func_002A78D8_1(0.1f, 0.5f);
        slot->f_60 = func_002A78D8_1(0.1f, 0.5f);
        slot->f_64 = func_002A78D8_1(0.1f, 0.5f);
        slot->f_80 = func_002A78D8_1(0.1f, 0.5f);
        slot->f_84 = func_002A78D8_1(0.1f, 0.5f);
        slot->f_88 = func_002A78D8_1(0.1f, 0.5f);
        slot->f_68 = func_002A7878_2(3.25f, 4.75f) * 0.25f;
        slot->f_6C = func_002A7878_2(3.25f, 4.75f) * 0.25f;
        slot->f_70 = func_002A7878_2(3.25f, 4.75f) * 0.25f;
        slot->f_8C = func_002A7878_2(3.25f, 4.75f) * 0.25f;
        slot->f_90 = func_002A7878_2(3.25f, 4.75f) * 0.25f;
        slot->f_94 = func_002A7878_2(3.25f, 4.75f) * 0.25f;
        func_00282C88_1(slot);
        func_00282C88_1((char *)slot + 0x10);
        slot->w_9C = arg1;
        slot->w_98 = arg1;
        r1 = func_002A7940();
        r2 = func_002A7940();
        func_002AF000_1(out, *(float *)(ctx + 0x4C), r1, r2);
        break;
    }
}


extern void func_L00_003BCE28(char *a0, char *a1);

extern char D_0023F060[];

/* Near miss: nonmatching/levels/func_L00_003BCDC0.c - every instruction present but the
   loop test is `sltu` here against retail's `slt`, and the base is derived from the end
   pointer instead of being materialised on its own. */

INCLUDE_ASM("asm/levels", func_L00_003BCF88);

INCLUDE_ASM("asm/levels", func_L00_003BD510);

INCLUDE_ASM("asm/levels", func_L00_003BD7E0);

/* Normalises and combines two temporary vectors from a state block, dispatches on the combined result and conditionally scales the output vector. */
void func_L00_003BFDE8(char *self, char *p1, int p2)
{
    float a[4];
    float b[4];

    func_00282F20_2(a, self + 224, 0.1f);
    func_00282F20_2(b, self + 224, -3.0f);
    func_00282CC0_6(a, a, self + 16);
    func_00282CC0_6(b, b, self + 16);

    if (func_002761F8(a, b, 2, self, 0))
        func_00282F20_2(p1, D_L00_001BF240, 1.0f);
    else
        func_00282F20_2(p1, self + 224, -1.0f);

    if (p2 == 0)
        func_00282D30_6(p1, p1, -1.0f);
}

/* Read the word at offset 0x 18 through the pointer stored at owner offset 0x 68. */
unsigned int func_L00_003BFF58(unsigned int param_1)
{
    unsigned int inner_ptr;
    unsigned int result;

    inner_ptr = *(unsigned int *)(param_1 + 0x68);
    result = *(unsigned int *)(inner_ptr + 0x18);
    return result;
}

extern float func_002B04E0(char *a0, float *src, char *third);

/* The four floats are declared before the two other arguments, which sets the order this caller
   evaluates them in (the registers are the same either way). */
extern float func_002AAA00(void *out, float f12, float f13, float f14, float f15, char *in, int a2);

extern void func_002833F0(void *out, void *in);

extern void func_00283738(char *a0, char *a1, void *a2);

extern float func_00282C48(float f);

/* Copies the caller's 16-byte block into a stack scratch area, runs the three-argument starter on
   it, then fills the scratch area's upper half from the state block's 0xB4 float and the pair
   helper before folding the starter's result against the state's own reading of that float. One
   `char scratch[0x50]` gives retail's frame. The 16-byte clear is retail's `sq $zero,0($sp)`:
   with the scheduling barrier of zero_ti_store_barrier.py it takes retail's place, and so does
   the prologue's save order. */
float func_L00_003BFF68(char *a0, char *a1, char *a2, char *a3)
{
    char scratch[0x50];
    float f;

    *(Rac2TI128 *)scratch = *(Rac2TI128 *)a2;
    f = func_002B04E0(a0, (float *)scratch, a3);
    *(int *)(scratch + 0x40) = 0;
    func_002AAA00(scratch + 0x40, f, *(float *)(a1 + 0x14), *(float *)(a1 + 0x18), 3.14159274f, a1 + 0xB4, 0);
    *(Rac2TI128 *)scratch = 0;
    *(float *)(scratch + 8) = *(float *)(a1 + 0xB4);
    func_002833F0(scratch + 0x10, scratch);
    func_00283738(a0 + 0xC0, a0 + 0xC0, scratch + 0x10);
    return func_00282C48(f) - func_00282C48(*(float *)(a1 + 0xB4));
}

/* shared native body of family a04928c6 */
void func_L00_003C1D30(char *p)
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

void func_L00_003C1FC8(int unused, char *pos, int color, int first, int second, float scale)
{
    char pkt[144];
    float m[16];
    float quat[4];
    float off[4];
    long long r;
    float dx, dy;

    ref_L00_003C1FC8_00(pkt);
    *(int *)(pkt + 80) = 0;
    *(float *)(pkt + 92) = 1.0f;
    *(float *)(pkt + 96) = 1.0f;
    *(float *)(pkt + 104) = 1.0f;
    *(float *)(pkt + 108) = 1.0f;
    *(int *)(pkt + 84) = 0;
    *(int *)(pkt + 88) = 0;
    *(int *)(pkt + 100) = 0;
    r = func_002E67A0_2(11);
    *(long long *)(pkt + 112) = 0;
    *(long long *)(pkt + 120) = r;
    *(long long *)(pkt + 128) = 0xFF9000000260LL;
    *(long long *)(pkt + 136) = 0x8000000048LL;
    dx = D_L00_001B8C80.x_140 - *(float *)pos;
    dy = D_L00_001B8C80.y_144 - *(float *)(pos + 4);
    *(int *)(pkt + 76) = color + first;
    *(int *)(pkt + 72) = color + first;
    *(int *)(pkt + 68) = color + first;
    *(int *)(pkt + 64) = color + first;
    quat[3] = 0;
    quat[2] = func_802EE7A8_1(dx, dy);
    quat[1] = -func_802EE7A8_1(func_802EE2E8_1(pos, &D_L00_001B8C80.x_140),
                              D_L00_001B8C80.z_148 - *(float *)(pos + 8));
    quat[0] = func_0031A888_1();
    func_802EE970_1(m, quat);
    func_802EE138_1(off, &D_L00_001B8C80.x_140, pos);
    func_802EE3D0_1(off, off, 0.5f);
    m[12] = *(float *)(pos) + off[0];
    m[13] = *(float *)(pos + 4) + off[1];
    m[14] = *(float *)(pos + 8) + off[2];
    m[15] = 1.0f;
    func_002EE178_1(pkt, pkt, scale);
    func_002EE178_1(pkt + 16, pkt + 16, scale);
    func_002EE178_1(pkt + 32, pkt + 32, scale);
    func_002EE178_1(pkt + 48, pkt + 48, scale);
    func_802EAC30_1(pkt, m, 0);
    *(int *)(pkt + 76) = color + second;
    *(int *)(pkt + 72) = color + second;
    *(int *)(pkt + 68) = color + second;
    *(int *)(pkt + 64) = color + second;
    func_002EE178_1(pkt, pkt, 0.5f);
    func_002EE178_1(pkt + 16, pkt + 16, 0.5f);
    func_002EE178_1(pkt + 32, pkt + 32, 0.5f);
    func_002EE178_1(pkt + 48, pkt + 48, 0.5f);
    func_802EAC30_1(pkt, m, 0);
}


INCLUDE_ASM("asm/levels", func_L00_003C27A0);

extern void func_L00_003263D0(char *a, char *b, float h, int c, int d, char *e, float i,
                               int f, int g, float j, float k);

/* Twenty rounds of four bound helpers on three 16-byte scratch vectors, the first of which
   starts as the second argument's record; each round ends with the eleven-argument emitter. */
void func_L00_003C2DE8(char *a0, char *a1, float fa, float fb)
{
    char v0[16];
    char v1[16];
    char v2[16];
    char *pv0 = v0;
    int i;

    *(Rac2TI128 *)pv0 = *(Rac2TI128 *)a1;
    i = 0x13;
    do {
        func_002A7A00(v1, fa, fa);
        func_00282F20_2(v2, v1, func_002A7878_2(fb * 0.75f, fb * 1.25f));
        func_00282CC0_6(v1, v1, pv0);
        func_L00_003263D0(a0, v1, 0.0f, 1, 0, v2, 0.0f, 0x50804040, 0, 2.0f, 5.0f);
        i--;
    } while (i >= 0);
}

/* Two-state gate on the record's byte 0x20 (the same body as func_L09_003C8CD8, which
   the level 09 file already carries). In state 0, as long as the live word the sub-object
   opens with is not -1, the record is stamped 0xFF, the shared eight-argument starter is
   run on the sub-object's track block and the record flips to state 1. In state 1 the
   sub-object's first float is scaled by 2*pi/21600 (a per-frame 1/100 s turn rate) and
   folded into the record's own angle before its track block is stepped again. */
extern void func_323448();
extern void func_323958(unsigned char *, unsigned char *);
extern float func_2EF0F8(float, float);

void func_L00_003C2F10(unsigned char *a0) {
    unsigned char *s0 = a0;
    unsigned char *s1 = *(unsigned char **)(s0 + 0x68);
    switch (s0[0x20]) {
    case 0:
        if (*(long long *)s1 == -1) {
            break;
        }
        {
            unsigned char stamp = 0xFF;
            *(unsigned char *)(s0 + 0x30) = stamp;
        }
        func_323448(s0, s1 + 0x30, 0x64, *(int *)(s1 + 4), *(int *)s1, -1, 7, 0);
        s1[0xC5A] = 1;
        s0[0x20] = 1;
        break;
    case 1:
        *(float *)(s0 + 0xF4) = func_2EF0F8(
            *(float *)(s0 + 0xF4), *(float *)(s1 + 8) * 0.000290888245f);
        func_323958(s0, s1 + 0x30);
        break;
    }
}


/* When the context flag at offset 0x24 is nonzero, pass scale 1.0, the context, its vector at offset 0x10 and mode zero to the bound helper; original game role is unknown. */
void func_L00_003C33E0(Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner *owner)
{
    Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context = owner->context_68;
    if (context->active_24 != 0) {
        func_002FDBD8_2(1.0f, context, context->vector_10, 0);
    }
}


/* The 0x68 context block starts with two words and a halfword that this body clears. */
void func_L00_003C37A0(char *p)
{
    char *q = *(char **)(p + 0x68);

    if (*(unsigned char *)(p + 0x20) == 0) {
        *(int *)(q + 0x8) = 0;
        *(short *)(q + 0xE) = 0;
        *(int *)(q + 0x0) = 0;
        *(unsigned char *)(p + 0x20) = 1;
    }
}

INCLUDE_ASM("asm/levels", func_L00_003C37C8);

/* Runs 20 local iterations; the first two calls each pass integer 2 to the same bound target; on each non-null final result, stores a short at +10, an int at +36, and bytes at +42 and +43. */
void func_L00_003C3920(char *unused, char *arg)
{
    char local[16];
    float f;
    int i;
    unsigned int v;
    unsigned int w;
    unsigned int x;
    char *r;

    i = 19;
    do {
        func_002A77E0_1(2);
        i = i - 1;
        func_002A77E0_1(2);
        f = func_002A7878_2(70000.0f, 150000.0f);
        v = func_002A7820_1(10, 127);
        w = (v << 8) | 0x7f000000U;
        x = (v << 16) | w;
        v = x | v;
        func_002A7A00(local, 1.6666668670950457453728e-05f,
                6.6666672937572002410889e-03f);
        r = func_002BDCE8(0.3f, 1.0f, 1.01f, f, arg, 0, local, v, 1);
        if (r != 0) {
            char *q = r + 32;

            *(short *)(r + 10) = 120;
            *(int *)(q + 4) = 2;
            *(char *)(q + 10) = 127;
            *(char *)(q + 11) = *(unsigned char *)(r + 10);
        }
    } while (i >= 0);
}

INCLUDE_ASM("asm/levels", func_L00_003C3A70);

INCLUDE_ASM("asm/levels", func_L00_003C3D90);

INCLUDE_ASM("asm/levels", func_L00_003C48D0);

INCLUDE_ASM("asm/levels", func_L00_003C4F78);

INCLUDE_ASM("asm/levels", func_L00_003C5310);

/* func_L00_003C58E8 is in L00_003C58E8-qcopy.c. */

/* Implemented in L00_003C58E8.c. */

/* one float gate followed by five integer gates; every failing gate */
int func_L00_003C5B18(float f12)
{
    char *b;

    if (f12 <= 0.0f)
        goto fail;
    b = D_00189E20_13;
    if (*(short *)(*(int *)(b + 8848) + 170) != 0)
        goto fail;
    if (*(unsigned char *)(b + 8884) != 0)
        goto fail;
    if (*(int *)(b + 8852) == 49)
        goto fail;
    if (*(int *)(b + 8860) == 20)
        goto fail;
    if (*(int *)(b + 9420) > 0)
        goto ok;
fail:
    return 0;
ok:
    return 1;
}

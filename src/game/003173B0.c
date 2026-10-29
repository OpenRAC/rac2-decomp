#include "include_asm.h"
#include "common.h"

extern int D_001B2758 MACRO_ADDR;
extern float func_002A7878(float, float), func_002A78D8(float, float);
extern void func_00282C88(void *), func_002B00B0(void *, void *, int);
extern char *func_002AB1F0(void *);
extern void func_00282CC0(void *, void *, void *);
extern int func_00283CF0(float), func_002A7820(int, int);
extern void func_002B60B0(void *, float, float, float, float);
extern void func_0029FCC0(void *, int, void *);
extern int func_002761F8(void *, void *, int, void *, int);
extern void func_002A7750(void *, int, int), func_002A7470(void *, int, int, int);
extern float D_001BAFA8;

/* One of the twelve 0xA0-byte records at *D_001B2758 that func_0031DEE8 steps for their
   owner: the boot counterpart of the level records func_L00_003BBB68 updates. */
typedef struct {
    float out0[4];          /* 0x00: ang0 through the two angle helpers, times amp0 */
    float out1[4];          /* 0x10: the same for ang1 */
    float start[4];         /* 0x20: copied from the owner's position each frame */
    float pos[4];           /* 0x30: follows the target */
    float ang0[3];          /* 0x40 */
    float rate0[3];         /* 0x4C */
    float amp0[3];          /* 0x58 */
    float ang1[3];          /* 0x64 */
    float rate1[3];         /* 0x70 */
    float amp1[3];          /* 0x7C */
    int life;               /* 0x88: timer, frees the record when it expires */
    char *owner;            /* 0x8C */
    char *target;           /* 0x90 */
    int time;               /* 0x94: timer, also counts the approach */
    int duration;           /* 0x98 */
    int hit;                /* 0x9C */
} Slot31DEE8;

/* The 0xE0-byte class records; D_00139568 maps a class number to its record. */
typedef struct {
    char pad_00[0x74];
    float f74;
    char pad_78[0xE0 - 0x78];
} Class31DEE8;

extern unsigned char D_00139568[];
extern Class31DEE8 D_00239BA0[];
extern float func_00283B98(float angle, float step);
extern float func_00283180(float angle);
extern float func_00283198(float angle);
extern float func_00283CE0(int ticks);
extern int func_00282948(void *timer);
extern void func_00282D08(void *out, void *from, void *to, float t);
extern void func_002A8C00(void *packet, char *owner, int flags, void *direction, float amount);
extern void func_002A8E20(char *target, void *packet);
extern void func_0031F6E8(void *pos, int count, int mode);
extern void func_0032D758(char *target, int kind, int value);

extern char F669d6320_D_001BAFC0[];

extern void F669d6320_FUN_00282F20(void *out, void *in, float scale);

extern void F669d6320_FUN_00282CC0(void *out, void *in1, void *in2);

extern int F669d6320_FUN_002761F8(void *a, void *b, int mode, void *self, int flag);

extern void F669d6320_FUN_00282D30(void *out, void *in, float scale);

extern void F2c74c194_FUN_00282D30(char *dst, char *src, float scale);

extern void F5a19df7a_FUN_002FC560(unsigned int a, unsigned long b);

extern void F5a19df7a_FUN_0031E2A0(char *p);

extern void F5a19df7a_FUN_0031E560(char *p);

extern char *F5a19df7a_FUN_002A7820(int a, int b);

extern float F5a19df7a_FUN_002A7940(void);

extern void F5a19df7a_FUN_0031EB00(char *a, int b, float e, char *c, float f, int d, int g);

extern void Fc936841d_FUN_00282CF0(char *local, char *first, char *second);

extern void Fc936841d_FUN_00282CC0(char *target, char *first, char *local);

#ifndef RAC2_T_VEC16_FC936841D
#define RAC2_T_VEC16_FC936841D
typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec16_Fc936841d;
#endif

/* The four 16-byte blocks the record carries and scales. */
#ifndef RAC2_T_BLOCK_0031A340
#define RAC2_T_BLOCK_0031A340
typedef struct {
    float q[4];
} Block_0031a340;
#endif

/* The 240-byte record func_0031A340 builds: a scaled matrix, a colour, the
   looked-up handle, the fixed fields and the two computed vectors. */
#ifndef RAC2_T_LOC_0031A340
#define RAC2_T_LOC_0031A340
typedef struct {
    Block_0031a340 b0;
    Block_0031a340 b1;
    Block_0031a340 b2;
    Block_0031a340 b3;
    int k0;
    int k1;
    int k2;
    int k3;
    int z80;
    int z84;
    int z88;
    float f92;
    float f96;
    int z100;
    float f104;
    float f108;
    long long v112;
    long long v120;
    long long v128;
    long long v136;
    float m00;
    float m01;
    float m02;
    float m03;
    float m10;
    float m11;
    float m12;
    float m13;
    float m20;
    float m21;
    float m22;
    float m23;
    float v192;
    float v196;
    float v200;
    float v204;
    float v208;
    float f212;
    float f216;
    float v220;
    float e0;
    float e1;
    float e2;
    float e3;
} Loc_0031a340;
#endif

/* The state block whose +0x140 holds the position the record is built around. */
#ifndef RAC2_T_STATE_001B5200
#define RAC2_T_STATE_001B5200
typedef struct {
    char pad_000[0x140];
    float pos[3];
} State_001b5200;
#endif

extern State_001b5200 D_001B5200;

extern void func_002A91F0(void *, float *);

INCLUDE_ASM("asm/game", func_003173B0);

INCLUDE_ASM("asm/game", func_00317D78);

extern void func_003182C0(void *);

void func_003181E0(void *object) {
    func_003182C0(object);
}

extern void func_002AB8C0(char *, char *);
extern int func_00282978(void *);
extern void func_002AEE70(char *, float, float, char *, float, char *);
extern void func_002AEF28(float, float, char *, char *, float, char *);

void func_00318200(char *object)
{
    char *data = *(char **)(object + 0x68);
    func_002AB8C0(object, data + 0x50);
    func_00282978(data + 0x270);
    if (func_00282978(data + 0x272)) {
        func_002AEE70(object, 0.1f, 0.08726647496223449707f, data + 0x27C, -1.0f, data + 0x280);
        func_002AEF28(0.13962635397911071777f, 0.026179943233728408813f, object, data + 0x284, 0.026179943233728408813f, data + 0x288);
    }
    if (*(unsigned short *)(object + 0x96) <= 65534)
        (*(unsigned short *)(object + 0x96))++;
}

INCLUDE_ASM("asm/game", func_00318340);

/* func_00319780 is in 00319780-g8.c. */

void func_00319B38(char *self)
{
    char *d = *(char **)(self + 0x68);
    *(u8 *)(d+0x68) = func_00283CF0(15.0f);
    *(u8 *)(d+0x6A) = func_00283CF0(12.0f);
    *(float *)(self+0x2C) *= 1.1f;
    *(u16 *)(self+0x34) |= 0x8100;
    *(char **)(d+0x18) = d+0x130;
    *(u8 *)(d+0x48)=3;
    *(u8 *)(d+0x90)=17;
    *(int *)(d+0xC8)=4;
    *(int *)(d+0xFC)=*(int *)(d+0x270);
    *(u8 *)(d+0x95)=13;
    *(float *)(d+220)=0.30000001192092896f;
    *(float *)(d+216)=0.05000000074505806f;
    *(float *)(d+160)=0.06666667014360428f;
    *(float *)(d+164)=0.004166666883975267f;
    *(float *)(d+168)=0.008333333767950535f;
    *(float *)(d+176)=0.5f;
    *(float *)(d+180)=0.5f;
    *(float *)(d+188)=0.4000000059604645f;
    *(float *)(d+156)=0.10000000894069672f;
    if ((float)*(int *)(d+0x2E8)>0.0f) *(float *)(d+0xC0)=(float)*(int *)(d+0x2E8);
    *(float *)(d+0x15C)=0.0f;
    *(float *)(d+320)=12.56637191772461f;
    *(float *)(d+304)=0.800000011920929f;
    *(float *)(d+308)=0.5f;
    *(float *)(d+0x138)=0.4f;
    *(float *)(d+316)=0.4000000059604645f;
    *(float *)(d+352)=0.523598849773407f;
    *(int *)(d+0x168)|=5;
    func_002B60B0(self,0.0033333334140479565f,0.10000000894069672f,0.0011635529808700085f,0.10471977293491364f);
    qcopy(d+0x220,self+0x10);
    *(float *)(d+0x230)=1.0f;
    *(float *)(d+0x23C)=3.0f;
    *(float *)(d+0x240)=10.0f;
    *(int *)(d+0x2D8)=func_002A7820(120,700);
    *(float *)(d+0x294)*=0.01745329424738884f;
    *(u8 *)(d+0x250)=176;
    *(u8 *)(d+0x251)=128;
    *(u8 *)(d+0x252)=64;
    *(int *)(d+0x2C4)=1;
    *(float *)(d+0x2BC)=0.0f;
    *(int *)(d+0x2C0)=0;
    qcopy(d+0x340,self+0x10);
    *(float *)(d+0x290)=0.0f;
    *(int *)(d+0x2C8)=0;
    *(int *)(d+0x2CC)=0;
    *(int *)(d+0x37C)=0;
    func_0029FCC0(self,0,d+0x2F0);
    qcopy(d+0x300,d+0x2F0);
    *(float *)(d+0x2F8)+=20.0f;
    if (func_002761F8(d+0x300,d+0x2F0,0,self,0))
        *(float *)(d+0x2F8)=D_001BAFA8;
    *(int *)(d+0x168)|=4;
    *(u16 *)(self+0x34)|=0x100;
    *(float *)(d+0x140)=12.56637191772461f;
    *(int *)(d+0x168)|=1;
    if (*(int *)(d+0x28C)==0) {
        if (*(int *)(d+0x370)!=-1) {
            func_002A7750(self,15,3);
            if (*(u8 *)(self+0x43)!=7) func_002A7470(self,7,0,0);
        } else {
            func_002A7750(self,1,0);
            if (*(u8 *)(self+0x43)!=0) func_002A7470(self,0,0,0);
        }
    } else {
        func_002A7750(self,3,1);
        if (*(u8 *)(self+0x43)!=11) func_002A7470(self,11,0,0);
    }
}

extern void func_002AB8C0(char *, char *);
extern int func_00282978(void *);
extern void func_002B0990(char *, char *, int, int, float);

void func_00319EC0(char *object)
{
    char *data = *(char **)(object + 0x68);
    func_002AB8C0(object, data + 0x70);
    func_00282978(data + 0x280);
    func_00282978(data + 0x282);
    if (*(unsigned short *)(object + 0x96) < 65535)
        (*(unsigned short *)(object + 0x96))++;
    func_002B0990(object, data + 0x380, 5, 1, 2.0f);
}

extern void func_0031A158(char *);
extern void func_0031A340(char *, char *, float, int, int, int);

void func_00319FB8(char *object)
{
    char *data = *(char **)(object + 0x68);
    int mode = *(unsigned char *)(object + 0x20);
    if (mode == 12 || mode == 14 || mode == 16 || mode == 13 || *(unsigned char *)(object + 0x95) == 1)
        func_0031A158(object);
    func_0031A340(object, data + 0x310, 0.125f, 0x36F6, 0x20000000, 0x20000000);
    func_0031A340(object, data + 0x320, 0.15f, 0x1050B0, 0x30000000, 0x20000000);
    func_0031A340(object, data + 0x330, 0.15f, 0x1050B0, 0x10000000, 0x30000000);
}

INCLUDE_ASM("asm/game", func_0031A098);


extern void func_0031A098(void *record);
extern long long func_0027C878_1(int id);
extern float func_00283248(float x, float y);
extern float func_00282E80(void *a, void *b);
extern float func_002A7940(void);
extern void func_00283410(void *dst, void *src);
extern void func_00282CF0(void *dst, void *a, void *b);
extern void func_00282F20(void *dst, void *src, float scale);
extern void func_00282D30(void *dst, void *src, float scale);
extern void func_00280B90(void *dst, void *src, int flag);

/* Builds the 240-byte record around a position: the looked-up handle, the colour
   of the object, the position the object sits at and the scaled matrix it keeps.
   The first argument is not read. */
void func_0031A340(char *unused, char *p1, float scale, int col0, int col1, int col2)
{
    Loc_0031a340 local;
    float x;

    func_0031A098(&local);
    local.v120 = func_0027C878_1(11);
    local.k3 = col0 + col1;
    local.k2 = col0 + col1;
    local.k1 = col0 + col1;
    local.k0 = col0 + col1;
    local.v136 = 0x0000008000000048LL;
    local.v220 = 0.0f;
    local.f216 = func_00283248(D_001B5200.pos[0] - *(float *)p1,
                                D_001B5200.pos[1] - *(float *)(p1 + 4));
    x = func_00283248(func_00282E80(p1, &D_001B5200.pos),
                      D_001B5200.pos[2] - *(float *)(p1 + 8));
    local.f212 = -x;
    local.v208 = func_002A7940();
    func_00283410(&local.m00, &local.v208);
    func_00282CF0(&local.e0, &D_001B5200.pos, p1);
    func_00282F20(&local.e0, &local.e0, 0.5f);
    local.v192 = *(float *)p1 + local.e0;
    local.v196 = *(float *)(p1 + 4) + local.e1;
    local.v200 = *(float *)(p1 + 8) + local.e2;
    local.v204 = 1.0f;
    func_00282D30(&local.b0, &local.b0, scale);
    func_00282D30(&local.b1, &local.b1, scale);
    func_00282D30(&local.b2, &local.b2, scale);
    func_00282D30(&local.b3, &local.b3, scale);
    func_00280B90(&local, &local.m00, 0);
    local.k3 = col0 + col2;
    local.k2 = col0 + col2;
    local.k1 = col0 + col2;
    local.k0 = col0 + col2;
    func_00282D30(&local.b0, &local.b0, 0.5f);
    func_00282D30(&local.b1, &local.b1, 0.5f);
    func_00282D30(&local.b2, &local.b2, 0.5f);
    func_00282D30(&local.b3, &local.b3, 0.5f);
    func_00280B90(&local, &local.m00, 0);
}

int func_0031A708(unsigned char *object) {
    return object[0x21] != 255;
}

typedef union { u8 b[0x2600]; float v[0x980][1]; } Hero_0031A718;

extern u8 D_00189E20[];
extern short *D_001EE5A0[];
extern u8 *D_001B1B5C MACRO_ADDR;
extern float func_00282E48(void *, void *);

/* Picks the nearest live moby on the object's list (skipping 0x9B4 ones) that is closer than
   the hero, and records it as the object's target. */
void func_0031A718(u8 *self)
{
    u8 *vars = *(u8 **)(self + 0x68);
    short *list;
    u8 *moby;
    float best;

    best = func_00282E48(self + 0x10, &((Hero_0031A718 *)D_00189E20)->b[0x80]);
    if (self[0x21] == 0xFF && D_001EE5A0[self[0x21]] == 0 && *(int *)(vars + 0x350) == 0)
        return;
    list = D_001EE5A0[self[0x21]];
    do {
        moby = D_001B1B5C + ((*list & 0x7FFF) << 8);
        if (*(s8 *)(moby + 0x20) >= 0 && *(s16 *)(moby + 0xAA) != 0x9B4) {
            if (func_00282E48(self + 0x10, moby + 0x10) < best) {
                *(u8 **)(vars + 0x30) = moby;
                best = func_00282E48(self + 0x10, moby + 0x10);
            }
        }
    } while (*list++ >= 0);
}


void func_0031A998(char *self, char *p1, int p2)
{
    float a[4];
    float b[4];

    F669d6320_FUN_00282F20(a, self + 224, 0.1f);
    F669d6320_FUN_00282F20(b, self + 224, -3.0f);
    F669d6320_FUN_00282CC0(a, a, self + 16);
    F669d6320_FUN_00282CC0(b, b, self + 16);

    if (F669d6320_FUN_002761F8(a, b, 2, self, 0))
        F669d6320_FUN_00282F20(p1, F669d6320_D_001BAFC0, 1.0f);
    else
        F669d6320_FUN_00282F20(p1, self + 224, -1.0f);

    if (p2 == 0)
        F669d6320_FUN_00282D30(p1, p1, -1.0f);
}

extern void func_00282CF0(void *, void *, void *);
extern unsigned int func_0031AB08(unsigned int);
extern void func_0031AB18(void *, unsigned int, void *, int);

/* func_0031AAB0 is matched in 0031AAB0.c. */


unsigned int func_0031AB08(unsigned int param_1)
{
    unsigned int inner_ptr;
    unsigned int result;

    inner_ptr = *(unsigned int *)(param_1 + 0x68);
    result = *(unsigned int *)(inner_ptr + 0x18);
    return result;
}

/* func_0031AB18 is defined in 0031AB18-zero-ti.c. */


INCLUDE_ASM("asm/game", func_0031BCC8);

/* func_0031C498 is in 0031C498.c. */

extern void func_0031C970(char *);
extern void func_0031CB78(char *, char *, int, int, int, float);
extern void func_0031CDF8(char *, char *, float, int, int);

/* Refresh the auxiliary state for modes 4, 5, 10 or flag 2, then issue
   three calls with the embedded vectors and three with the referenced vectors. */
void func_0031C7A0(char *self)
{
    char *data = *(char **)(self + 0x68);
    unsigned char mode = self[0x20];

    if (mode == 4 || mode == 5 || (unsigned char)self[0x95] == 2 || mode == 10)
        func_0031C970(self);

    func_0031CB78(self, data + 0x370, 0x41DE, 0x10000000, 0x20000000, 0.125f);
    func_0031CB78(self, data + 0x380, 0x00800000, 0x10000000, 0x30000000, 0.125f);
    func_0031CB78(self, data + 0x390, 0x00800000, 0x10000000, 0x30000000, 0.125f);

    func_0031CDF8(self, *(char **)(data + 0x270) + 0x10, 0.075f, 0x204080, 0x204080);
    func_0031CDF8(self, *(char **)(data + 0x274) + 0x10, 0.075f, 0x204080, 0x204080);
    func_0031CDF8(self, *(char **)(data + 0x278) + 0x10, 0.075f, 0x204080, 0x204080);
}

void func_0031C8E0(char *p)
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


/* func_0031CB78 is in its own unit: func_0031C7A0 has different placements. */

/* func_0031CDF8 is defined in 0031CDF8.c. */

void func_0031D268(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);

    *(int *)(state + 0x288) = 0;
    *(int *)(state + 0x284) = (*(int *)(state + 0x284) + 1) % 4;
    if (*(int *)(state + 0x280) < 4)
        (*(int *)(state + 0x280))++;
    func_002A91F0(state + (*(int *)(state + 0x284) * 16 + 0x4A0), (float *)(arg0 + 0xF0));
    qcopy(state + *(int *)(state + 0x284) * 16 + 0x3A0,
          (char *)(*(int *)(state + 0x278) + 0x10));
}


/* func_0031D308 is in the -G8 sibling. */

INCLUDE_ASM("asm/game", func_0031D350);

/* func_0031D3E0 is in 0031D3E0.c. */

INCLUDE_ASM("asm/game", func_0031D588);


void func_0031DC18(char *self, char *target, int count)
{
    int pool = D_001B2758;
    char *position = self + 0x10;
    char *target_position = target + 0x10;
    char *data = *(char **)(self + 0x68);
    char *p;
    char *info;
    float v[4];
    int i;
    for (i = 0; i < 12; i++) {
        p = (char *)(pool + i * 0xA0);
        if (*(int *)(p + 0x8C) == 0) {
            *(char **)(p + 0x8C) = self;
            (*(int *)(data + 0x1C))++;
            qcopy(p + 0x20, position);
            *(float *)(p + 64) = func_002A7878(-3.14159274101257324219f, 3.14159274101257324219f);
            *(float *)(p + 68) = func_002A7878(-3.14159274101257324219f, 3.14159274101257324219f);
            *(float *)(p + 72) = func_002A7878(-3.14159274101257324219f, 3.14159274101257324219f);
            *(float *)(p + 100) = func_002A7878(-3.14159274101257324219f, 3.14159274101257324219f);
            *(float *)(p + 104) = func_002A7878(-3.14159274101257324219f, 3.14159274101257324219f);
            *(float *)(p + 108) = func_002A7878(-3.14159274101257324219f, 3.14159274101257324219f);
            *(float *)(p + 76) = func_002A78D8(0.001f, 0.05f);
            *(float *)(p + 80) = func_002A78D8(0.001f, 0.05f);
            *(float *)(p + 84) = func_002A78D8(0.001f, 0.05f);
            *(float *)(p + 112) = func_002A78D8(0.001f, 0.05f);
            *(float *)(p + 116) = func_002A78D8(0.001f, 0.05f);
            *(float *)(p + 120) = func_002A78D8(0.001f, 0.05f);
            *(float *)(p + 88) = func_002A7878(3.25f, 6.75f);
            *(float *)(p + 92) = func_002A7878(3.25f, 6.75f);
            *(float *)(p + 96) = func_002A7878(3.25f, 6.75f);
            *(float *)(p + 124) = func_002A7878(1.25f, 4.75f);
            *(float *)(p + 128) = func_002A7878(1.25f, 4.75f);
            *(float *)(p + 132) = func_002A7878(1.25f, 4.75f);
            func_00282C88(p);
            func_00282C88(p + 0x10);
            *(int *)(p + 0x94) = count;
            *(int *)(p + 0x98) = count;
            *(char **)(p + 0x90) = target;
            *(int *)(p + 0x9C) = 0;
            *(int *)(p + 0x88) = 20;
            info = func_002AB1F0(target);
            if (info) {
                func_002B00B0(target, v, 1);
                func_00282D30(v, v, *(float *)(info + 0x10));
                func_00282CC0(p + 0x30, v, target + 0x10);
            } else {
                qcopy(p + 0x30, target_position);
            }
            break;
        }
    }
}

static inline Class31DEE8 *Class31DEE8At(int index)
{
    return &D_00239BA0[index];
}

/* Steps every record the owner holds: refreshes its start from the owner, advances the two
   angle triples (faster while the approach timer runs), and while it has a target moves its
   position towards it. When the approach timer expires and the target is still live, it
   sends one hit packet (func_002A8C00/func_002A8E20) and marks the record; when the life
   timer expires the record is released and the owner's count drops. */
void func_0031DEE8(char *owner)
{
    float v[4];
    struct {
        char pad_00[0x18];
        unsigned char kind;
        unsigned char mode;
        short id;
        char pad_1c[0x14];
    } packet;
    char *ctx = *(char **)(owner + 0x68);
    Slot31DEE8 *slot;
    char *other;
    float ratio;
    float damage;
    float boost = 100.0f;
    int i;

    for (i = 0; i < 12; i++) {
        if (((Slot31DEE8 *)D_001B2758)[i].owner != owner)
            continue;
        slot = &((Slot31DEE8 *)D_001B2758)[i];
        qcopy(slot->start, owner + 0x10);
        if (slot->time) {
            slot->ang0[0] = func_00283B98(slot->ang0[0], slot->rate0[0] * boost);
            slot->ang0[1] = func_00283B98(slot->ang0[1], slot->rate0[1] * boost);
            slot->ang0[2] = func_00283B98(slot->ang0[2], slot->rate0[2] * boost);
            slot->ang1[0] = func_00283B98(slot->ang1[0], slot->rate1[0] * boost);
            slot->ang1[1] = func_00283B98(slot->ang1[1], slot->rate1[1] * boost);
            slot->ang1[2] = func_00283B98(slot->ang1[2], slot->rate1[2] * boost);
        } else {
            slot->ang0[0] = func_00283B98(slot->ang0[0], slot->rate0[0]);
            slot->ang0[1] = func_00283B98(slot->ang0[1], slot->rate0[1]);
            slot->ang0[2] = func_00283B98(slot->ang0[2], slot->rate0[2]);
            slot->ang1[0] = func_00283B98(slot->ang1[0], slot->rate1[0]);
            slot->ang1[1] = func_00283B98(slot->ang1[1], slot->rate1[1]);
            slot->ang1[2] = func_00283B98(slot->ang1[2], slot->rate1[2]);
        }
        slot->out0[0] = func_00283180(slot->ang0[0]) * slot->amp0[0];
        slot->out0[1] = func_00283198(slot->ang0[1]) * slot->amp0[1];
        slot->out0[2] = -func_00283198(slot->ang0[2]) * slot->amp0[2];
        slot->out1[0] = func_00283180(slot->ang1[0]) * slot->amp1[0];
        slot->out1[1] = func_00283198(slot->ang1[1]) * slot->amp1[1];
        slot->out1[2] = -func_00283198(slot->ang1[2]) * slot->amp1[2];
        if (slot->target) {
            other = func_002AB1F0(slot->target);
            if (other) {
                func_002B00B0(slot->target, v, 1);
                func_00282D30(v, v, *(float *)(other + 0x10));
                func_00282CC0(slot->pos, v, slot->target + 0x10);
            } else {
                qcopy(slot->pos, slot->target + 0x10);
            }
            ratio = func_00283CE0(slot->time);
            ratio /= func_00283CE0(slot->duration);
            func_00282D08(slot->pos, slot->start, slot->pos, 1.0f - ratio);
        }
        if (!func_00282948(&slot->time))
            continue;
        if (*(int *)(slot->target + 0x98) && !slot->hit) {
            func_00282CF0(v, slot->pos, slot->start);
            func_00282F20(v, v, 0.033333335f);
            damage = Class31DEE8At(D_00139568[0x1C])->f74;
            func_002A8C00(&packet, owner, 0x210000, v, damage);
            packet.kind = 1;
            packet.mode = 3;
            packet.id = *(short *)(owner + 0xAA);
            func_002A8E20(slot->target, &packet);
            slot->hit = 1;
            func_0031F6E8(slot->pos, 10, 1);
            func_0032D758(slot->target, 28, *(int *)(owner + 0xB8));
        }
        if (func_00282948(&slot->life)) {
            slot->owner = 0;
            --*(int *)(ctx + 0x1C);
        }
    }
}

INCLUDE_ASM("asm/game", func_0031E3A8);


/* func_0031E560 is defined in 0031E560-dbg.c (-g). */

INCLUDE_ASM("asm/game", func_0031E6D8);



void func_0031E750(char *p)
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

void func_0031E7D8(float *out, float *a, float *b, float *c, float *d, float t)
{
    float t2, t3, x, y, z;
    if (t == 0.0f) { qcopy(out, a); return; }
    if (t == 1.0f) { qcopy(out, b); return; }
    t2 = t*t;
    t3 = t2*t;
    y = d[0]-b[0]-(c[0]-a[0]); x = c[0]-a[0]-y; z = b[0]-c[0];
    out[0] = y*t3 + x*t2 + z*t + a[0];
    y = d[1]-b[1]-(c[1]-a[1]); x = c[1]-a[1]-y; z = b[1]-c[1];
    out[1] = y*t3 + x*t2 + z*t + a[1];
    y = d[2]-b[2]-(c[2]-a[2]); x = c[2]-a[2]-y; z = b[2]-c[2];
    out[2] = y*t3 + x*t2 + z*t + a[2];
    out[3] = 0.0f;
}

void func_0031E8F8(char *p, float scale)
{
    F2c74c194_FUN_00282D30(p, p, scale);
    F2c74c194_FUN_00282D30(p + 16, p + 16, scale);
    F2c74c194_FUN_00282D30(p + 32, p + 32, scale);
    F2c74c194_FUN_00282D30(p + 48, p + 48, scale);
}

void func_0031E960(char *p)
{
    char *q;
    char *o;
    char *r;
    float v;
    float w;

    q = p + 16;
    o = *(char **)(p + 104);
    F5a19df7a_FUN_002FC560(0x47, 0x53001UL);
    F5a19df7a_FUN_0031E2A0(p);
    F5a19df7a_FUN_0031E560(p);

    v = *(float *)(o + 24);
    v = v * 0.5f;
    r = F5a19df7a_FUN_002A7820(80, 96);
    w = F5a19df7a_FUN_002A7940();
    F5a19df7a_FUN_0031EB00(q, 0x103080, v, r, w, 49, 2);

    v = *(float *)(o + 24);
    v = v * 3.00000011920928955078125e-01f;
    r = F5a19df7a_FUN_002A7820(80, 96);
    w = F5a19df7a_FUN_002A7940();
    F5a19df7a_FUN_0031EB00(q, 0xFFFFFF, v, r, w, 49, 2);

    v = *(float *)(o + 24);
    v = v * 6.99999988079071044921875e-01f;
    r = F5a19df7a_FUN_002A7820(8, 22);
    w = F5a19df7a_FUN_002A7940();
    F5a19df7a_FUN_0031EB00(q, 0x803010, v, r, w, 11, 2);

    v = *(float *)(o + 24);
    v = v * 4.49999988079071044921875e-01f;
    r = F5a19df7a_FUN_002A7820(32, 64);
    w = F5a19df7a_FUN_002A7940();
    F5a19df7a_FUN_0031EB00(q, 0x803010, v, r, w, 11, 2);

    F5a19df7a_FUN_002FC560(0x47, 0x5360bUL);
}

extern float D_FLT_001B5200[];
extern int func_0027C878(int);
extern float func_00283248(float, float);
extern float func_00282E80(void *, void *);
extern void func_00283410(void *, void *);
extern void func_00280B90(void *, void *, int);

void func_0031EB00(char *position, int color, float scale, char *resource, float alpha, int mode, int flag)
{
    unsigned char work[0xE0];
    unsigned int rgba;
    unsigned long long mode_bits;
    float first_angle;
    float second_angle;
    float distance;

    func_0031E750((char *)work);
    *(long long *)(work + 0x78) = func_0027C878(mode);

    mode_bits = ((unsigned long long)flag << 2) | 0x0000008000000040ULL;
    *(long long *)(work + 0x88) = mode_bits;
    *(long long *)(work + 0x80) = 0x0000FF9000000260ULL;

    rgba = (unsigned int)color + ((unsigned int)resource << 24);
    *(int *)(work + 0x4C) = rgba;
    *(int *)(work + 0x48) = rgba;
    *(int *)(work + 0x44) = rgba;
    *(int *)(work + 0x40) = rgba;
    *(long long *)(work + 0x70) = 0;

    *(int *)(work + 0xDC) = 0;
    first_angle = func_00283248(D_FLT_001B5200[0x140 / 4] - *(float *)(position + 0),
                                D_FLT_001B5200[0x144 / 4] - *(float *)(position + 4));
    *(float *)(work + 0xD8) = first_angle;

    distance = func_00282E80(position, &D_FLT_001B5200[0x140 / 4]);
    second_angle = func_00283248(distance, D_FLT_001B5200[0x148 / 4] - *(float *)(position + 8));
    *(float *)(work + 0xD0) = alpha;
    *(float *)(work + 0xD4) = -second_angle;

    func_00283410(work + 0x90, work + 0xD0);
    *(float *)(work + 0xC0) = *(float *)(position + 0);
    *(float *)(work + 0xC4) = *(float *)(position + 4);
    *(float *)(work + 0xC8) = *(float *)(position + 8);
    *(float *)(work + 0xCC) = 1.0f;
    func_0031E8F8((char *)work, scale);
    func_00280B90(work, work + 0x90, 0);
}


/* func_0031EFC8 uses the profile in 003173B0-qcopy.c. */

void func_0031F1A8(Vec16_Fc936841d *object, int index)
{
    char local[16];

    Fc936841d_FUN_00282CF0(local, (char *)&object[index - 2], (char *)&object[index - 3]);
    Fc936841d_FUN_00282CC0((char *)&object[index - 1], (char *)&object[index - 2], local);
}

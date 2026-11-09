#include "common.h"

typedef int VectorWord4140 __attribute__((mode(TI)));
typedef union { VectorWord4140 q; float f[4]; } Vector4140;
typedef struct {
    unsigned char pad0[128];
    Vector4140 pos;
    Vector4140 rot;
    unsigned char pada0[96];
    Vector4140 f100;
    unsigned char pad110[64];
    Vector4140 f150;
    Vector4140 f160;
    unsigned char pad170[52];
    float f1a4;
    unsigned char pad1a8[110];
    short f216;
    unsigned char pad218[14];
    short f226;
    unsigned char pad228[276];
    int ground_platform;
    unsigned char pad340[14];
    short platform_timer;
    Vector4140 f350;
    Vector4140 f360;
    Vector4140 f370;
    unsigned char pad380[16];
    Vector4140 platform_delta;
    int platform;
    int platform_flags;
    unsigned char pad3a8[424];
    Vector4140 ledge_offset;
    unsigned char pad560[20];
    float ledge_angle;
    unsigned char pad578[16];
    int ledge_platform;
    unsigned char pad58c[7428];
    int f2290;
    int state;
    unsigned char pad2298[4];
    int state2;
    unsigned char pad22a0[21];
    unsigned char f22b5;
} Hero4140;
extern Hero4140 D_00189E20_4140;
extern void func_00283CE0(int);
typedef struct {
    unsigned char pad0[60];
    int flags;
} PlatformObject;
extern PlatformObject *func_002AD0B0(int);
extern float func_00282DF0(void *);
extern float func_00283B98(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern int func_002AD0E0(int, int, void *, void *, void *, void *);
extern int func_002AD5F8(int, int, void *, void *, void *, void *);
extern int func_002AD470(int, int, void *, void *, void *, void *);
extern void func_00282C88(void *);
extern float func_00282E20(void *);
extern void func_002AA2E8(float *, float, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern float func_00283248(float, float);
extern float func_00283BE0(float, float);

#ifndef RAC2_T_V4_F6A70B950
#define RAC2_T_V4_F6A70B950
typedef int V4_F6a70b950 __attribute__((mode(TI)));
#endif

extern char D_00189E20_19[];

extern float func_00283180_6(float);

extern float func_00283198_6(float);

extern void func_00283410_4(float *m, char *src);

extern void func_002830C0_6(float *dst, float *src, float *m);

extern void func_00282CC0_16(V4_F6a70b950 *out, V4_F6a70b950 *in, float *v);

#ifndef RAC2_T_V4_FE23FE324
#define RAC2_T_V4_FE23FE324
typedef int V4_Fe23fe324 __attribute__((mode(TI)));
#endif

extern char D_00189E20_33[];

extern void func_00282C88_6();

extern void func_00283410_10();

extern void func_002830C0_11();

extern void func_00282CC0_37();

extern void func_00282F20_5(char *local, char *a, float k);

extern float func_00282DB0_2(char *a, char *src);

extern void func_00282D30_11(char *dst, char *src, float k);

extern void func_00282CF0_8(char *dst, char *src, char *local);

extern char D_00189E20_14[];

            /* 0x00189E20 */

#ifndef RAC2_T_V4_FC186F630
#define RAC2_T_V4_FC186F630
typedef int V4_Fc186f630 __attribute__((mode(TI)));
#endif

extern unsigned char D_00189E20_4[];

extern float func_00282E20_1(char *object);

extern void func_00283410_2(char *dst, char *src);

extern void func_00283698_1(char *dst, char *src);

extern void func_002830C0_1(char *dst, char *src, char *extra);

extern unsigned char D_00189E20_18[];

extern void func_00282F70(char *a, int b, float f);

extern void func_002830C0_5(char *a, char *b, char *c);

extern char D_00189E20_31[];

extern void func_002830C0_9(char *dst, char *src, char *extra);

#ifndef RAC2_T_V4_FD337D953
#define RAC2_T_V4_FD337D953
typedef int V4_Fd337d953 __attribute__((mode(TI)));
#endif

extern char D_00189E20_32[];

extern void func_002830C0_10(void *a, void *b, void *c);

#ifndef RAC2_T_PERSISTENT_F882F1178
#define RAC2_T_PERSISTENT_F882F1178
typedef struct {
    unsigned char pad0[4960];
    void *p1360;
    void *p1364;
    void *p1368;
    unsigned char pad1[4512];
    float f250C;
    float f2510;
    float f2514;
} Persistent_F882f1178;
#endif

#ifndef RAC2_T_NODE_F882F1178
#define RAC2_T_NODE_F882F1178
typedef struct {
    unsigned char pad[120];
    int field120;
} Node_F882f1178;
#endif

extern Persistent_F882f1178 D_00189E20_11;

extern int D_L00_001A8F00 __attribute__((sda));

extern float func_00283B98_4(float, float);

extern float func_00283198_3(float);

extern int func_00283D38_1(int, int, float);

extern void func_L00_00326048(int, float *, int, int, float);

/* Dispatches on one byte of a fixed global table: when it is zero it copies a 16-byte block from the second argument to the first and then accumulates two table-derived floats, each scaled by the third argument, into the first two words of that block; when it is 1 or 2 it builds a 16-byte vector from two table-derived values and a zero, fills two 64-byte matrices through helper routines, composes them into a vector and passes that vector with the two pointers to a closing routine. */
void func_L00_002D3798(V4_F6a70b950 *out, V4_F6a70b950 *in, float scale)
{
    char *p = D_00189E20_19;
    unsigned char mode;
    float z;

    mode = *(unsigned char *)(p + 8899);

    switch (mode) {
    case 0:
        *out = *in;
        *(float *)out += func_00283180_6(*(float *)(*(int *)(p + 8848) + 248)) * scale;
        *(float *)((char *)out + 4) += func_00283198_6(*(float *)(*(int *)(p + 8848) + 248)) * scale;
        break;
    case 1:
    case 2: {
        float m[16];
        float v[4];

        z = 0.0f;
        v[0] = func_00283180_6(z) * scale;
        v[1] = func_00283198_6(z) * scale;
        v[2] = z;
        func_00283410_4(m, (char *)*(int *)(p + 8848) + 240);
        func_002830C0_6(v, v, m);
        func_00282CC0_16(out, in, v);
        break;
    }
    }
}

/* Reads a byte state from a global root; when zero it copies a 16-byte vector and adds a float to its third element, otherwise (state 1 or 2) it builds a 4x4 matrix from a global object and transforms a vector by it. */
void func_L00_002D38A0(V4_Fe23fe324 *a0, V4_Fe23fe324 *a1, float f)
{
    char *p = D_00189E20_33;
    unsigned char raw = p[8899];
    int state = raw;
    float m[4][4];
    float v[4];

    if (state == 0) {
        *a0 = *a1;
        ((float *)a0)[2] += f;
        return;
    }
    if (state < 0)
        return;
    if (state >= 3)
        return;
    func_00282C88_6(v);
    v[2] = f;
    func_00283410_10(m, *(int *)(p + 8848) + 240);
    func_002830C0_11(v, v, m);
    func_00282CC0_37(a0, a1, v);
}

/* switches on a state byte in a shared table: copies 16 bytes and clears the third word, or computes a dot product that scales a vector and subtracts it into the destination */
void func_L00_002D3960(char *dst, char *src)
{
    char local[16];
    char *base;
    float f;

    base = D_00189E20_14;
    switch (*(unsigned char *)(base + 8899)) {
    case 0:
        *(V4_Fc186f630 *)dst = *(V4_Fc186f630 *)src;
        *(int *)(dst + 8) = 0;
        break;
    case 1:
        func_00282F20_5(local, base + 672, 1.0f);
        f = func_00282DB0_2(local, src);
        func_00282D30_11(local, local, f);
        func_00282CF0_8(dst, src, local);
        break;
    case 2:
        f = func_00282DB0_2(base + 704, src);
        func_00282D30_11(local, base + 704, f);
        func_00282CF0_8(dst, src, local);
        break;
    }
}

/* Reads one byte and one pointer from a shared global; returns a callee float when the byte is zero, returns 0.0f when the byte is outside 0..2, otherwise fills three stack locals through three callees and returns the last callee float. */
float func_L00_002D3A58(char *arg)
{
    char first[64];
    char second[64];
    char third[16];
    unsigned char *p = D_00189E20_4;
    int flag = p[8899];

    if (flag == 0)
        return func_00282E20_1(arg);
    if (flag < 0)
        return 0.0f;
    if (flag >= 3)
        return 0.0f;
    func_00283410_2(first, (char *)(*(int *)(p + 8848) + 240));
    func_00283698_1(second, first);
    func_002830C0_1(third, arg, second);
    return func_00282E20_1(third);
}

extern void func_00283098(void *a, void *b, void *c);

float func_L00_002D3B00(char *in)
{
    char *p = (char *)&D_00189E20_11;
    int mode = *(unsigned char *)(p + 8899);
    float local[4];

    if (mode == 0)
        return *(float *)(in + 8);
    if (mode < 0)
        return 0.0f;
    if (mode >= 3)
        return 0.0f;
    func_00283098(local, in, p + 64);
    return local[2];
}

extern void func_002830C0(void *a, void *b, void *c);

void func_L00_002D3B58(V4_F6a70b950 *dst, V4_F6a70b950 *src, float k)
{
    char *p = (char *)&D_00189E20_11;
    int mode = *(unsigned char *)(p + 8899);

    if (mode == 0) {
        *dst = *src;
        ((float *)dst)[2] = k;
        return;
    }
    if (mode < 0)
        return;
    if (mode >= 3)
        return;
    func_002830C0(dst, src, p + 64);
    ((float *)dst)[2] = k;
    func_002830C0(dst, dst, p);
}

/* reads a mode byte from a global block; when zero it forwards the arguments to one helper, otherwise it range-checks the byte and drives two helpers with the object and block pointers */
void func_L00_002D3BD8(char *a0, int a1, float f12)
{
    unsigned char *d = D_00189E20_18;
    float f20;
    int v;

    f20 = f12;
    v = d[8899];
    if (v == 0) {
        func_00282F70(a0, a1, f12);
        return;
    }
    if (v < 0)
        return;
    if (v >= 3)
        return;
    func_002830C0_5(a0, a1, (char *)d + 64);
    func_00282F70(a0, a0, f20);
    func_002830C0_5(a0, a0, (char *)d);
}

/* Flag-gated record update: copies 16 bytes src->dst and scales dst+8 by k when a byte flag is zero, otherwise runs two helper calls with DATA0+64 and DATA0 offsets and scales the same field between them. */
void func_L00_002D3C68(char *dst, char *src, float k)
{
    char *base = D_00189E20_31;
    int flag = *(unsigned char *)(base + 8899);

    if (flag == 0) {
        *(V4_Fd337d953 *)dst = *(V4_Fd337d953 *)src;
        *(float *)(dst + 8) = *(float *)(dst + 8) * k;
        return;
    }
    if (flag < 0)
        return;
    if (flag >= 3)
        return;
    func_002830C0_9(dst, src, base + 64);
    *(float *)(dst + 8) = *(float *)(dst + 8) * k;
    func_002830C0_9(dst, dst, base);
}

/* dispatches on one byte of a global table with a three-case switch: case 0 scales two floats of the destination by the incoming scale, cases 1 and 2 first run a helper over the destination with a table at +64, scale the same two floats and then run a second helper with the destination as both source and destination */
void func_L00_002D3CF8(float *dst, void *src, float scale)
{
    char *d = D_00189E20_32;
    int v = *(unsigned char *)(d + 8899);

    switch (v) {
    case 0:
        dst[0] = dst[0] * scale;
        dst[1] = dst[1] * scale;
        break;
    case 1:
    case 2:
        func_002830C0_10(dst, src, d + 64);
        dst[0] = dst[0] * scale;
        dst[1] = dst[1] * scale;
        func_002830C0_10(dst, dst, d);
        break;
    }

}

/* func_L00_002D3D98 is in L00_002D3798-3D98.c (block-order profile). */


#ifndef RAC2_T_ENTRY_262570
#define RAC2_T_ENTRY_262570
typedef struct {
    unsigned char pad0[142];
    unsigned short f8E;
    unsigned char rest[80];
} Entry_262570;
#endif

extern unsigned char D_L00_00139568[];

extern Entry_262570 D_L00_00262570[];

extern int D_L00_00139688[];

extern int D_0018B068;

int func_L00_002D3F30(int a0, int a1)
{
    int idx = a0;
    unsigned char b;
    Entry_262570 *e;
    int word;

    if (idx == -1)
        idx = D_0018B068;
    b = D_L00_00139568[idx];

    e = &D_L00_00262570[b];
    if (e->f8E == 0)
        return 1;
    word = D_L00_00139688[idx];
    if (word < a1)
        return 0;
    D_L00_00139688[idx] = word - a1;
    return 1;
}

/* Return the complete supplied unsigned-long 64-bit value unchanged. */
/* Target: FUN_003427B0 — identity function returning its first argument */
/* Disassembly: jr ra; move v0,a0 (MIPS delay slot) */
/* Compiled with: -O2 -G0 -ffunction-sections */

unsigned long func_L00_002D3FB0(unsigned long param_1)
{
  return param_1;
}


extern unsigned char D_L00_00139568[];

#ifndef RAC2_T_ENTRY_262570
#define RAC2_T_ENTRY_262570
typedef struct {
    unsigned char pad0[142];
    unsigned short f8E;
    unsigned char rest[80];
} Entry_262570;
#endif

extern Entry_262570 D_L00_00262570[];

extern int D_L00_00139688[];

extern int D_0018B068;

int func_L00_002D4040(int a0)
{
    int idx = a0;
    unsigned char b;
    Entry_262570 *e;

    if (idx == -1)
        idx = D_0018B068;
    b = D_L00_00139568[idx];

    e = &D_L00_00262570[b];
    if (e->f8E == 0)
        return 1;
    return D_L00_00139688[idx];
}

extern void func_L00_002C42E0(int, int);

void func_L00_002D40A0(V4_F6a70b950 *v, int mode, float t)
{
    char *addr = (char *)&D_00189E20_11 + 0x18A0;
    int x;

    *(V4_F6a70b950 *)addr = *v;
    /* rebase the copy destination (base + 0x18A0) back to the record base */
    addr -= 0x18A0;
    x = *(int *)(addr + 0x2294);
    *(int *)(addr + 0x18B0) = mode;
    *(float *)(addr + 0x18AC) = t;
    if ((unsigned)(x - 98) >= 3)
        func_L00_002C42E0(98, 2);
}

extern int D_0018C0B4;

int func_L00_002D40F0(void)
{
    switch (D_0018C0B4) {
    case 98:
    case 99:
        return 1;
    case 100:
        return 2;
    }
    return 0;
}


/* Carry the hero with the supporting platform, including ledge anchors,
 * rotation and the displacement retained while the hero leaves the platform.
 * Counterpart: RAC1 update_hero_attachment in hero_mapped_animations.c.
 */
void func_L00_002D4140(void)
{
    float local_pos[4], local_rot[4], delta[4], next[4];
    float hero_pos[4], hero_rot[4], anchor_pos[4], anchor_rot[4], anchor2_pos[4], anchor2_rot[4];
    float offset[4];
    float height, length;
    int mode = 0;
    float blend = 0.0f;
    float old_yaw = D_00189E20_4140.rot.f[2];
    PlatformObject *object;

    if (D_00189E20_4140.platform_timer == 0) {
        if (D_00189E20_4140.ground_platform) {
            mode = 1;
            if (D_00189E20_4140.platform != D_00189E20_4140.ground_platform)
                D_00189E20_4140.platform_flags &= ~1;
            D_00189E20_4140.platform = D_00189E20_4140.ground_platform;
        } else {
            D_00189E20_4140.platform = 0;
            D_00189E20_4140.platform_flags &= ~1;
            D_00189E20_4140.platform_flags &= ~2;
        }
    } else if (D_00189E20_4140.state == 27 && D_00189E20_4140.ledge_platform) {
        D_00189E20_4140.platform = D_00189E20_4140.ledge_platform;
        mode = 1;
    } else if (D_00189E20_4140.state2 == 3 && D_00189E20_4140.ledge_platform) {
        D_00189E20_4140.platform = D_00189E20_4140.ledge_platform;
        mode = 1;
    } else if (D_00189E20_4140.platform) {
        mode = 1;
        func_00283CE0(120 - D_00189E20_4140.platform_timer);
        blend = D_00189E20_4140.platform_timer;
    } else {
        D_00189E20_4140.platform = 0;
        D_00189E20_4140.platform_flags &= ~1;
        D_00189E20_4140.platform_flags &= ~2;
    }

    if (!mode)
        return;
    object = func_002AD0B0(D_00189E20_4140.platform);
    if (!object)
        return;

    if (((D_00189E20_4140.state2 == 0 || D_00189E20_4140.state2 == 12) &&
         func_00282DF0(&D_00189E20_4140.f160) == 0.0f &&
         D_00189E20_4140.platform_timer == 0 && D_00189E20_4140.f216 == 0) ||
        (unsigned)(D_00189E20_4140.state - 23) < 2) {
        if (((D_00189E20_4140.platform_flags ^ 1) & 1)) {
            if ((unsigned)(D_00189E20_4140.state - 23) < 2) {
                qcopy(delta, &D_00189E20_4140.ledge_offset);
                delta[0] += func_00283180(func_00283B98(D_00189E20_4140.ledge_angle,
                        3.1415925f)) * 0.45f;
                delta[1] += func_00283198(func_00283B98(D_00189E20_4140.ledge_angle,
                        3.1415925f)) * 0.45f;
                delta[2] -= -1.43f;
                func_002AD0E0(D_00189E20_4140.f2290, D_00189E20_4140.platform,
                        &D_00189E20_4140.ledge_offset, &D_00189E20_4140.rot, next, hero_pos);
                func_002AD0E0(D_00189E20_4140.f2290, D_00189E20_4140.platform, delta,
                        &D_00189E20_4140.rot, delta, hero_pos);
                func_002AD5F8(D_00189E20_4140.f2290, D_00189E20_4140.platform,
                        &D_00189E20_4140.ledge_offset, &D_00189E20_4140.rot, &D_00189E20_4140.f350,
                        hero_pos);
                func_002AD5F8(D_00189E20_4140.f2290, D_00189E20_4140.platform, delta,
                        &D_00189E20_4140.rot, &D_00189E20_4140.f370, hero_pos);
            } else if (object->flags & 4) {
                func_002AD5F8(D_00189E20_4140.f2290, D_00189E20_4140.platform,
                        &D_00189E20_4140.pos, &D_00189E20_4140.rot, &D_00189E20_4140.f350, delta);
            } else {
                func_002AD0E0(D_00189E20_4140.f2290, D_00189E20_4140.platform,
                        &D_00189E20_4140.pos, &D_00189E20_4140.rot, next, hero_pos);
                func_002AD5F8(D_00189E20_4140.f2290, D_00189E20_4140.platform, next, hero_pos,
                        &D_00189E20_4140.f350, delta);
            }
            D_00189E20_4140.platform_flags |= 1;
        }
    } else
        D_00189E20_4140.platform_flags &= ~1;

    if ((D_00189E20_4140.state2 == 0 || D_00189E20_4140.state2 == 12) && D_00189E20_4140.f1a4 == 0.0f &&
        D_00189E20_4140.platform_timer == 0) {
        if (!(D_00189E20_4140.platform_flags & 2)) {
            func_002AD5F8(D_00189E20_4140.f2290, D_00189E20_4140.platform, &D_00189E20_4140.pos,
                    &D_00189E20_4140.rot, delta, &D_00189E20_4140.f360);
            D_00189E20_4140.platform_flags |= 2;
        }
    } else
        D_00189E20_4140.platform_flags &= ~2;

    if (D_00189E20_4140.platform_flags & 3)
        mode = 2;
    func_00282C88(delta);
    func_00282C88(next);

    if (blend != 0.0f) {
        int flags;
        float planar = func_00282E20(&D_00189E20_4140.platform_delta);

        flags = object->flags;
        height = D_00189E20_4140.platform_delta.f[2];
        length = planar;
        if (!(flags & 2)) {
            float rate = 2.0f;

            if (flags & 16)
                rate = 20.0f;
            rate *= 0.00027777778f;
            func_002AA2E8(&height, 0.0f, blend * 0.0069444445f);
            func_002AA2E8(&length, 0.0f, rate * blend);
            func_00282F70((char *)delta, (int)&D_00189E20_4140.platform_delta, length);
            delta[2] = height;
        } else if (D_00189E20_4140.platform) {
            func_002AD0E0(D_00189E20_4140.f2290, D_00189E20_4140.platform, &D_00189E20_4140.pos,
                    &D_00189E20_4140.rot, local_pos, local_rot);
            if (D_00189E20_4140.f226 == 0)
                D_00189E20_4140.rot.q = *(V4_F6a70b950 *)local_rot;
            func_00282CF0(delta, local_pos, &D_00189E20_4140.pos);
            qcopy(&D_00189E20_4140.platform_delta, delta);
        } else
            qcopy(delta, &D_00189E20_4140.platform_delta);
        qcopy(next, delta);
    } else if (mode == 1) {
        func_002AD0E0(D_00189E20_4140.f2290, D_00189E20_4140.platform, &D_00189E20_4140.pos,
                &D_00189E20_4140.rot, local_pos, local_rot);
        if (D_00189E20_4140.f226 == 0)
            D_00189E20_4140.rot.q = *(V4_F6a70b950 *)local_rot;
        func_00282CF0(delta, local_pos, &D_00189E20_4140.pos);
        qcopy(&D_00189E20_4140.platform_delta, delta);
    } else if (mode == 2) {
        func_002AD0E0(D_00189E20_4140.f2290, D_00189E20_4140.platform, &D_00189E20_4140.pos,
                &D_00189E20_4140.rot, hero_pos, hero_rot);
        func_002AD470(D_00189E20_4140.f2290, D_00189E20_4140.platform, &D_00189E20_4140.f350,
                &D_00189E20_4140.f360, anchor_pos, anchor_rot);
        func_002AD470(D_00189E20_4140.f2290, D_00189E20_4140.platform, &D_00189E20_4140.f370,
                &D_00189E20_4140.f360, anchor2_pos, anchor2_rot);
        if (D_00189E20_4140.f226 == 0) {
            if ((D_00189E20_4140.state == 1 || D_00189E20_4140.state == 29) &&
                D_00189E20_4140.f22b5)
                D_00189E20_4140.rot.f[2] = hero_rot[2];
            else
                D_00189E20_4140.rot.f[2] =
                    (D_00189E20_4140.platform_flags & 2) ? anchor_rot[2] : hero_rot[2];
        }
        if (D_00189E20_4140.platform_flags & 1) {
            if ((unsigned)(D_00189E20_4140.state - 23) < 2) {
                offset[0] = func_00283180(D_00189E20_4140.ledge_angle) * 0.45f;
                offset[1] = func_00283198(D_00189E20_4140.ledge_angle) * 0.45f;
                offset[2] = 0;
                func_00282CC0(offset, offset, anchor2_pos);
                offset[2] += -1.43f;
                func_00282CF0(delta, hero_pos, &D_00189E20_4140.pos);
                qcopy(&D_00189E20_4140.ledge_offset, offset);
                D_00189E20_4140.ledge_angle = func_00283248(anchor_pos[0] - anchor2_pos[0],
                        anchor_pos[1] - anchor2_pos[1]);
            } else {
                float distance;

                func_00282CF0(delta, anchor_pos, &D_00189E20_4140.pos);
                distance = func_00282DF0(delta);
                if (distance < 0.0001f) {
                    func_00282C88(delta);
                    qcopy(&D_00189E20_4140.pos, anchor_pos);
                } else if (distance > 2.0f) {
                    func_00282C88(delta);
                    D_00189E20_4140.platform_flags &= ~2;
                    D_00189E20_4140.platform_flags &= ~1;
                }
                func_00282CC0(&D_00189E20_4140.ledge_offset, &D_00189E20_4140.ledge_offset, delta);
                func_00282CF0(offset, delta, &D_00189E20_4140.f150);
                if (func_00282DF0(offset) > 0.1f)
                    D_00189E20_4140.platform_flags &= ~1;
            }
        } else {
            func_00282CF0(delta, hero_pos, &D_00189E20_4140.pos);
            qcopy(next, delta);
        }
        qcopy(&D_00189E20_4140.platform_delta, delta);
    }

    func_00282CC0(&D_00189E20_4140.f100, &D_00189E20_4140.f100, delta);
    D_00189E20_4140.f100.f[3] = func_00283BE0(D_00189E20_4140.rot.f[2], old_yaw);
}


extern int func_003425F8(int, float, char *, char *);

void func_L00_002D49F0(void)
{
    char *p = (char *)&D_00189E20_11;

    if (func_003425F8(*(short *)(p + 0x24FE), *(float *)(p + 0x264), p + 0x80, p + 0x80)) {
        *(short *)(p + 0x216) = 4;
    }
}

extern int ref_L00_002D4A38_00 __attribute__((sda));

void func_L00_002D4A38(void)
{
    Node_F882f1178 *node;

    node = (Node_F882f1178 *)D_00189E20_11.p1360;
    if (node != 0) {
        if (ref_L00_002D4A38_00 == 2)
            D_00189E20_11.f250C = func_00283B98_4(D_00189E20_11.f250C, 0.020362177863717079f);
        else
            D_00189E20_11.f250C = func_00283B98_4(D_00189E20_11.f250C, 0.034906592220067978f);
        node->field120 = func_00283D38_1(0xd2d2d2, 0x285050,
                                 func_00283198_3(D_00189E20_11.f250C) * 0.5f + 0.5f);
    }
    node = (Node_F882f1178 *)D_00189E20_11.p1364;
    if (node != 0) {
        if (D_L00_001A8F00 != 2) {
            float limit;
            int which;

            limit = func_00283B98_4(D_00189E20_11.f2510, 0.049451004713773727f);
            D_00189E20_11.f2510 = limit;
            which = 0x1ee628;
            if (limit > 0.0f && limit < 1.9198623895645142f) {
                which = 0x1e1ed2;
            }
            node->field120 = func_00283D38_1(node->field120, which, 0.070000000298023224f);
        } else {
            D_00189E20_11.f2510 = func_00283B98_4(D_00189E20_11.f2510, 0.026179943233728409f);
            node->field120 = func_00283D38_1(0x1e1ed2, 0x1e1e50,
                                     func_00283198_3(D_00189E20_11.f2510) * 0.5f + 0.5f);
        }
    }
    if (D_00189E20_11.p1368 != 0) {
        if (D_L00_001A8F00 == 2)
            func_L00_00326048((int)D_00189E20_11.p1368, &D_00189E20_11.f2514, 0xdcdcdc, 0x323232,
                    0.026179943233728409f);
        else
            func_L00_00326048((int)D_00189E20_11.p1368, &D_00189E20_11.f2514, 0xdcdcdc, 0x323232,
                    0.040724355727434158f);
    }
}




extern char D_00189E20_4D98[];
extern char *func_0029EFD0(int);
extern void func_L00_002AA178(char *);
extern void func_L00_002B0968(char *);

/* One-shot spawn: arms the state word, and when the slot is free asks the allocator for a
   0x50A object, writes its flags, the packed constant at +0x38 and the level's tag, then runs
   the two level entry points on the argument. */
void func_L00_002D4D98(char *arg0) {
    char *base = D_00189E20_4D98;
    char *node;

    *(int *)(base + 0x12E8) = 0x2F;
    if (*(int *)(base + 0x12C0) == 0) {
        node = func_0029EFD0(0x50A);
        if (node != 0) {
            *(unsigned short *)(node + 0x32) = 0x20;
            *(unsigned short *)(node + 0x34) =
                *(unsigned short *)(node + 0x34) | 2;
            *(unsigned char *)(node + 0x31) = 1;
            *(unsigned long *)(node + 0x38) = 0x20202000000000UL;
            *(int *)(node + 0x64) = 0;
            if (*(unsigned char *)(*(int *)(node + 0x24) + 6) != 0)
                *(unsigned char *)(node + 0x63) = 0x10;
            *(unsigned short *)(node + 0x34) =
                *(unsigned short *)(node + 0x34) | 0x800;
            *(int *)(base + 0x12C0) = (int)node;
            *(int *)(base + 0x12E4) = 2;
        }
    }
    func_L00_002AA178(arg0);
    func_L00_002B0968(arg0);
}

/* func_L00_002D4E58 is in L00_002D4E58-g8.c (-G8). */





/* func_L00_002D5158 is in L00_002D3798-aim-g8.c (-G8 and division line labels). */

/* func_L00_002D5940 is in L00_002D3798-g8.c (-G8). */

extern short D_L00_00262260[];

extern int D_001A7A0C __attribute__((sda));

/* Walks the halfword pairs of the table at D_L00_00262260 (a negative first half ends it, and
   so do 77 pairs): the first half of each pair is added to a running sum while the sum stays
   within D_001A7A0C / 32, and each pair that passes adds its second half to *a2 and stores the
   sum to *a0. *a1 gets the final sum. The retail unit returns int without setting it: $v0 is
   live at the exit, which keeps the load of D_001A7A0C out of the exit branch's delay slot
   (a void function gives that slot to the load, as a $gp access). */
int func_L00_002D5E30(int *a0, int *a1, int *a2) {
    int sum = 0;
    int i = 0;
    short *second = &D_L00_00262260[1];
    short *first = second - 1;

    for (; i < 77 && *first >= 0 && (sum += *first) <= (D_001A7A0C >> 5);
         i++, second += 2, first += 2) {
        *a2 += *second;
        *a0 = sum;
    }
    *a1 = sum;
}

extern int D_001A7908 __attribute__((sda));
extern char *D_L00_001B8E10;
extern unsigned char D_00189E20[];

int func_L00_002D6418(void)
{
    int v;

    if (D_001A7908 == 0)
        return 0;
    v = D_L00_001A8F00;
    if (v == 2 || v == 6)
        return 0;
    if (D_L00_001B8E10 != 0 && *(short *)(D_L00_001B8E10 + 0x86) == 5)
        return 0;
    if (D_00189E20[0x22B4] != 0 || *(int *)(D_00189E20 + 0x229C) == 0x14 ||
        *(int *)(D_00189E20 + 0x24CC) == 0)
        return 0;
    v = *(int *)(D_00189E20 + 0x2294);
    if (v == 0x6F || v == 0x31 || v == 0x1C || v == 0x8C)
        return 0;
    return 1;
}

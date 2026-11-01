#include "common.h"

extern void func_002A7398(void *, int, int);
extern char D_00189EA0[];
extern unsigned char *D_L04_001B24E8 __attribute__((sda));

extern signed char *D_L04_001B24DC __attribute__((sda));
extern void func_L04_0040E248(int, unsigned char *);
extern float func_0033BBE0(void);
extern float func_0033BB78(float, float);
extern void func_002AF000(void *, float, float, float);
extern void func_00282CD8(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
/* Integer and float arguments keep their order within each EE register bank. */
extern void func_002C2210(void *, int, unsigned int, int, int, void *, float, float, float, int);

extern void func_00282CF0(void *, void *, void *);
extern float func_L00_002EE290(void *);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern unsigned char *D_L04_001FE340[];
extern float func_00282E48(void *, void *);
typedef struct {
    unsigned char pad[0x1a8];
    int primary;
    int branches[4];
    int links[4];
    int parents[4];
} L04PathState;


/* Frozen Batch A A04-table-select-76; acknowledged claim 8c4d82cfbf43e138ed35e757fdaeee3e7c4651fa684549ba9d5e8ac22c56d111. */
typedef unsigned char BatchA_A04_u8;

typedef unsigned int BatchA_A04_u32;

extern BatchA_A04_u32 D_001A79F0[] __attribute__((sda));

extern BatchA_A04_u8 D_001395B8[];

INCLUDE_ASM("asm/levels", func_L04_00402D90);

extern void func_L00_002ECFE8(void *a0, void *a1, int a2, unsigned int a3,
                              float f12, float f13, float f14, int t0, int t1);

/* Steps the record's phase at +0x1FC down by 0.1 (wrapping up by 8 once it reaches -8) and
   draws the effect with it. */
void func_L04_00404068(void *arg0) {
    char *o = *(char **)((char *)arg0 + 0x68);

    *(float *)(o + 0x1FC) -= 0.1f;
    if (*(float *)(o + 0x1FC) <= -8.0f)
        *(float *)(o + 0x1FC) += 8.0f;
    func_L00_002ECFE8(arg0, o + 0x200, 3, 0x60005AFF, 0.08f, 0.45f, *(float *)(o + 0x1FC), 0xFF,
                      0x17);
}

typedef unsigned int B781AimQuad __attribute__((mode(TI)));
extern float func_00282C48(float);
extern void func_002AA898(void *, void *, float, float, float, float, int);
extern void func_002A7470(void *, int, int, int);
extern void func_002A05A8(void *);
extern void func_002A0F48(void *);
extern void *func_L04_003E5E40(void *, int, float);
extern int func_L04_00343498(void *, float);
extern void func_L00_002E6EF8(void (*)(void *), void *);
extern void func_L04_00404068(void *);
extern void func_L00_0033E220(void *, void *, unsigned int, float, int, int, float, int, int, int);
extern void func_00282CF0(void *, void *, void *);
extern float func_L00_002EE290(void *);
extern void func_L04_00416390(void *, void *, void *, float);
void func_L04_00404100(unsigned char *m, unsigned char *p)
{
    float point[4];
    float end[4];
    float total = *(float *)(p + 0x138) + *(float *)(p + 0x13c);
    float a, b, c, angle, factor;
    if (total < 0.083333336f) total = 0.083333336f;
    a = *(float *)(p + 0x130) * 13.750985f;
    b = total * 2.7088037f;
    c = *(float *)(p + 0x130) * 28.647884f;
    a = a * func_00282C48(a);
    c = 1.0f - (1.0f - c) * (1.0f - c);
    if (b > 1.0f) b = 1.0f;
    if (*(float *)(p + 0x1f4) != 0.0f) {
        if (func_00282C48(*(float *)(m + 0xf0) - *(float *)(p + 0x1f4)) < 0.003f) *(float *)(p + 0x1f4) = 0.0f;
        factor = *(float *)(p + 0x1f8);
        angle = *(float *)(p + 0x1f4);
    } else {
        factor = 1.0f;
        angle = (factor - b) * a + b * c;
        if (angle > factor) angle = factor;
        if (angle < -1.0f) angle = -1.0f;
        angle *= -0.52359885f;
    }
    func_002AA898(m + 0xf0, p + 0x128, angle, factor * 0.035f, 0.45f, factor * 0.027634384f, 0);
    if (*(unsigned char **)(p + 0x8c)) {
        unsigned char *child = *(unsigned char **)(p + 0x8c);
        if ((child[0x60] & 2) && child[0x42]) func_002A7470(child, 0, 0, 3);
        *(short *)(*(unsigned char **)(p + 0x8c) + 0x32) = 30;
        (*(unsigned char **)(p + 0x8c))[0x31] = 1;
        *(B781AimQuad *)(*(unsigned char **)(p + 0x8c) + 0x10) = *(B781AimQuad *)(m + 0x10);
        *(B781AimQuad *)(*(unsigned char **)(p + 0x8c) + 0xf0) = *(B781AimQuad *)(m + 0xf0);
        (*(unsigned char **)(p + 0x8c))[0x30] = 0;
        func_002A05A8(*(void **)(p + 0x8c));
        func_002A0F48(*(void **)(p + 0x8c));
        *(unsigned short *)(*(unsigned char **)(p + 0x8c) + 0x34) |= 6;
    } else *(void **)(p + 0x8c) = func_L04_003E5E40(m, 0x8ef, 0.25f);
    if ((*(unsigned char **)(p + 0x164))[0xbc] == 5) {
        if (func_L04_00343498(m, 20.0f) != -1) {
            func_L00_002E6EF8(func_L04_00404068, m);
            func_L00_0033E220(p + 0x200, m, 0x3096ffff, 94500.0f, -1, 0, 0.01f, 2, 0, -1);
            func_L00_0033E220(p + 0x210, m, 0x3096ffff, 94500.0f, -1, 0, 0.01f, 2, 0, -1);
            func_L00_0033E220(p + 0x220, m, 0x3096ffff, 94500.0f, -1, 0, 0.01f, 2, 0, -1);
        }
    }
    if (*(int *)(p + 0x244)) {
        func_00282CF0(point, *(unsigned char **)(p + 0x164) + 0x10, m + 0x10);
        if (func_L00_002EE290(point) < 100.0f) {
            *(B781AimQuad *)(point) = *(B781AimQuad *)(m + 0x10);
            point[2] -= 0.25f;
            *(B781AimQuad *)(end) = *(B781AimQuad *)(m + 0x10);
            func_L04_00416390(m, end, p + 0xd0, *(float *)(p + 0x138) + *(float *)(p + 0x13c));
        }
    }
}


INCLUDE_ASM("asm/levels", func_L04_004045E0);

/* func_L04_00407078 is in L04_00402D90-debris.c. */

/* func_L04_004073E8 is in L04_00402D90-trail.c. */

extern int func_00282978(void *);
extern void func_L00_002E6EF8(void (*)(void *), void *);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00283738(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_00283028(void *, void *, void *);
extern float func_00282DB0(void *, void *);
extern float func_00282DF0(void *);
extern int func_00283CF0(float);
extern void func_002833F0(void *, void *);
extern void func_L00_003200F8(void *, void *, float, float, int);
extern void func_0032C700(void *, float, float, int, int, int, int, int, int, int, int, int, int, int);
extern void func_0029F338(void *);
extern int func_00277258(void *, int, float, void *);
extern void func_002AB668(void *, void *, float);
extern void func_002839D0(void *, void *);
extern void func_002AB6D8(void *, void *);
extern float D_L04_001BFB00[];
extern void func_L04_004073E8(void *);

void func_L04_004077A0(unsigned char *m)
{
    float oldpoint[4];
    float rot[12];
    float point[4];
    float delta[4];
    float probe[4];
    float matrix[16];
    float bounce[4];
    float axis[4];
    unsigned char *p = *(unsigned char **)(m + 0x68);
    float speed, dot;
    float radius;
    *(unsigned short *)(p + 0x32) += 1;
    switch (m[0x20]) {
    case 1:
        if (func_00282978(p + 0x30)) {
            m[0x20] = (*(int *)(p + 0x34) & 1) ? 3 : 2;
            *(short *)(p + 0x30) = func_00283CF0(10.0f);
            return;
        }
        if (*(int *)(p + 0x34) & 4) func_L00_002E6EF8(func_L04_004073E8, m);
        break;
    case 2:
        func_00283098(oldpoint, p + 0x20, m + 0xc0);
        func_00282CC0(oldpoint, oldpoint, m + 0x10);
        if (*(int *)(p + 0x34) & 2) func_L00_003200F8(m, oldpoint, 0.3f, 10.0f, -1);
        else func_0032C700(m + 0x10, 0.5f, 0.0f, 0, 25, 20, 20, 20, 45, 0, 0, 0, 0, 0);
        goto destroy;
    case 3:
        if (func_00282978(p + 0x30)) {
        case 0:
        destroy:
            func_0029F338(m);
            return;
        }
        m[0x23] = func_00283CF0((float)*(short *)(p + 0x30) * 12.8f);
        break;
    }
    func_002833F0(rot, p + 0x10);
    func_00283098(oldpoint, p + 0x20, m + 0xc0);
    func_00283738(m + 0xc0, rot, m + 0xc0);
    func_00283098(point, p + 0x20, m + 0xc0);
    func_00282CF0(delta, point, oldpoint);
    func_00282CF0(m + 0x10, m + 0x10, delta);
    func_00282CC0(m + 0x10, m + 0x10, p);
    *(float *)(p + 8) -= *(float *)(p + 0x38);
    radius = *(float *)(p + 0x2c);
    func_00283098(probe, p + 0x20, m + 0xc0);
    func_00282CC0(probe, probe, m + 0x10);
    if (func_00277258(probe, 0, radius, m)) {
        func_00282F20(D_L04_001BFB00, D_L04_001BFB00, 1.0f);
        speed = func_00282DF0(p);
        dot = func_00282DB0(p, D_L04_001BFB00);
        if (dot < 0.0f) {
            func_00283028(p, p, D_L04_001BFB00);
            func_00282F20(bounce, D_L04_001BFB00, dot * 0.5f);
            func_00282CC0(p, p, bounce);
            func_00282F20(p, p, speed);
            func_00282DD8(axis, D_L04_001BFB00, p);
            func_00282F20(axis, axis, 1.0f);
            func_002AB668(axis, axis, func_00282DF0(p + 0x10));
            func_002839D0(axis, matrix);
            func_002AB6D8(matrix, p + 0x10);
            if (*(short *)(p + 0x32) >= 16) *(short *)(p + 0x30) = 0;
        }
    }
}




/* A04-table-select-76 freshly exact-verified under family reservation */
BatchA_A04_u32 func_L04_0040A1D0(BatchA_A04_u8 *a0) {
    BatchA_A04_u32 v = D_001A79F0[0];
    BatchA_A04_u32 r = 0;
    if (v == 4) r = D_001395B8[(BatchA_A04_u32)a0 + 0x4D];
    else if (v == 0xB) r = D_001395B8[(BatchA_A04_u32)a0 + 0x57];
    return r;
}

/* A04-table-select family, incrementing form: bumps the state-selected byte */
void func_L04_0040A220(BatchA_A04_u8 *a0)
{
    BatchA_A04_u32 v = D_001A79F0[0];

    if (v == 4) D_001395B8[(BatchA_A04_u32)a0 + 0x4D]++;
    else if (v == 0xB) D_001395B8[(BatchA_A04_u32)a0 + 0x57]++;
}

/* shared native body of family A04-table-select: reads the state-selected byte */
unsigned int func_L04_0040A268(unsigned char *a0)
{
    unsigned int v = D_001A79F0[0];
    unsigned int r = 0;

    if (v == 4) r = D_001395B8[(unsigned int)a0 + 0x52];
    else if (v == 0xB) r = D_001395B8[(unsigned int)a0 + 0x5C];
    return r;
}

/* A04-table-select family, incrementing form (second slot pair) */
void func_L04_0040A2B8(BatchA_A04_u8 *a0)
{
    BatchA_A04_u32 v = D_001A79F0[0];

    if (v == 4) D_001395B8[(BatchA_A04_u32)a0 + 0x52]++;
    else if (v == 0xB) D_001395B8[(BatchA_A04_u32)a0 + 0x5C]++;
}

extern BatchA_A04_u8 *D_001B26F0 __attribute__((sda));

extern void func_002B9180(void *);

/* Sweeps the 0x800 packed 64-byte records, redrawing the four live kinds */
void func_L04_0040A310(void)
{
    int i;

    for (i = 0; i < 0x800; i++) {
        BatchA_A04_u8 b = *(BatchA_A04_u8 *)((i << 6) + (BatchA_A04_u32)D_001B26F0);

        if (b == 0x4A || b == 8 || b == 0xB || b == 0xF) {
            func_002B9180(D_001B26F0 + (i << 6));
        }
    }
}

void func_L04_0040A3B8(unsigned char *m, int keep)
{
    unsigned char *p = *(unsigned char **)(m + 0x68), *node;
    unsigned char *other;
    qzero(p + 0x2b0);
    *(float *)(p + 0x2b8) = 1.0f;
    qzero(p + 0x290);
    qzero(p + 0x2a0);
    qzero(p + 0x2c0);
    qzero(p + 0x6c0);
    *(B781AimQuad *)(m + 0x10) = *(B781AimQuad *)D_00189EA0;
    *(int *)(p + 0x76c) = 0;
    *(int *)(p + 0x718) = 0;
    *(short *)(p + 0x274) = 0;
    p[0x349] = 0;
    *(int *)(p + 0x34c) = 0;
    *(int *)(p + 0x354) = 0;
    *(int *)(p + 0x358) = 0;
    *(int *)(p + 0x278) = 0;
    *(int *)(p + 0x27c) = 0;
    *(int *)(p + 0x300) = 0;
    *(int *)(p + 0x304) = 0;
    *(int *)(p + 0x308) = 0;
    *(int *)(p + 0x30c) = 0;
    *(int *)(p + 0x280) = 0;
    *(int *)(p + 0x288) = 0;
    *(int *)(p + 0x750) = 0;
    *(int *)(p + 0x738) = 0;
    *(int *)(p + 0x724) = 0;
    *(float *)(p + 0x28c) = 90.0f;
    func_L04_0040E248((int)m, p);
    other = (unsigned char *)D_L04_001B24DC + (*(int *)(p + 0x1dc) << 8);
    *(int *)(p + 0x3a8) = 10;
    *(int *)(p + 0x328) = -1;
    *(int *)(p + 0x330) = -1;
    *(int *)(p + 0x334) = -1;
    *(int *)(p + 0x3bc) = -1;
    *(int *)(p + 0x714) = -1;
    *(int *)(p + 0x324) = 0;
    *(int *)(p + 0x32c) = 0;
    *(int *)(p + 0x33c) = 0;
    *(int *)(p + 0x338) = 0;
    *(int *)(p + 0x38c) = 0;
    *(int *)(p + 0x390) = 0;
    *(int *)(p + 0x4c4) = 0;
    *(int *)(p + 0x3b0) = 0;
    *(int *)(p + 0x3ac) = 0;
    *(int *)(p + 0x3b4) = 0;
    *(int *)(p + 0x360) = 0;
    *(int *)(p + 0x364) = 0;
    *(int *)(p + 0x368) = 0;
    *(int *)(p + 0x4d8) = 0;
    *(int *)(p + 0x4dc) = 0;
    if (other) func_002A7398(other, 0, 0);
    *(short *)(p + 0x34a) = -1;
    *(int *)(p + 0x36c) = 0;
    /* This cleared vector has no scalar consumers in the surrounding resets. */
    qzero_nc(p + 0x2f0);
    *(int *)(p + 0x64c) = 0;
    *(int *)(p + 0x70c) = 0;
    if (!keep) {
        *(int *)(p + 0x3a4) = 0;
        *(int *)(p + 0x314) = -1;
        *(int *)(p + 0x3b8) = 0;
        *(int *)(p + 0x310) = 0;
        *(int *)(p + 0x318) = 0;
    }
    for (node = D_L04_001B24E8; node; node = *(unsigned char **)(node + 0x28)) {
        unsigned short type = *(unsigned short *)(node + 0xaa);
        if ((unsigned int)(type - 0xb3d) < 4 || (short)type == 0x27f ||
            (short)type == 0x70 || (short)type == 0x7a) {
            func_0029F338(node);
        }
    }
    *(int *)(p + 0x388) = 0;
}



/* func_L04_0040A628 is in L04_00402D90-racers-g8.c. */

/* func_L04_0040A958 is in L04_00402D90-reset-g8.c. */

extern signed char *D_L04_001B24DC __attribute__((sda));

extern void func_40E248(char *a0, char *a1);

/* Retail reaches its record base off $gp (a small-data symbol), and the three
   state words at 0x48 of the record and of the indexed record. */
void func_L04_0040AC30(char *a0, char *a1)
{
    char *s0 = a0;
    char *s1 = a1;

    func_40E248(s0, s1);
    *(int *)(s0 + 0x48) = 0;
    if (*(int *)(s1 + 0x1DC) != -1) {
        *(int *)((*(int *)(s1 + 0x1DC) << 8) + (int)D_L04_001B24DC + 0x48) = 0;
    }
}

/* func_L04_0040AC98 reaches its global off $gp, so its body lives in
   L04_00402D90-g8.c. */

/* func_L04_0040ACA8 reaches one of its globals absolutely and another off $gp,
   so its body lives in L04_00402D90-g8.c. */


INCLUDE_ASM("asm/levels", func_L04_0040AD28);

INCLUDE_ASM("asm/levels", func_L04_0040BA68);

typedef unsigned int L04Quad __attribute__((mode(TI)));
extern int func_0030FF98(float);
extern int func_0033BA80(int);
extern float func_0033BB18(float, float);
extern void func_L04_003C4AF8(void *, float);
/* The EE assigns the point, parameter and mode to a0-a2, and the two
 * float arguments to f12-f13, independently of their C interleaving. */
extern void func_0035BF30(void *, float, float, void *, int);
void func_L04_0040BD50(L04Quad *position, int count, float value, float intensity)
{
    float origin[4];
    float point[4];
    float parameter;
    float *base = origin;
    *(L04Quad *)origin = *position;
    parameter = value;
    if (intensity >= 0.12f) {
        if (!func_0033BA80(func_0030FF98(1.0f / intensity) + 1))
            func_L04_003C4AF8(origin, func_0033BB18(0.5f, 1.25f) * intensity * 9.0f);
    }
    if (intensity >= 0.1f) {
        if (count > 0) do {
            point[0] = base[0] + func_0033BB18(-0.3f, 0.3f);
            count--;
            point[1] = base[1] + func_0033BB18(-0.3f, 0.3f);
            point[2] = base[2];
            func_0035BF30(point, func_0033BB18(0.3f, 0.6f), 5250.0f, &parameter, -1);
        } while (count != 0);
    }
}




void func_L04_0040C0C0(L04Quad *position, L04Quad *direction, int count, int mode)
{
    float velocity[4], point[4], scaled[4], result[4];
    float size, angle, pitch;
    int sign, i;
    for (i = 0; i < count; i++) {
        size = func_0033BB18(0.025f, 0.5f);
        sign = func_0033BA80(2);
        if (!sign) sign--;
        angle = func_0033BBE0();
        pitch = func_0033BB18(0.6981318f, 1.5358899f);
        func_002AF000(velocity, func_0033BB18(0.012500001f, 0.025000002f), angle, pitch);
        *(L04Quad *)scaled = *direction;
        func_00282D30(scaled, direction, func_0033BB18(0.75f, 0.95f));
        if (mode) {
            velocity[0] *= 5.0f;
            velocity[1] *= 5.0f;
            size *= 3.0f;
        }
        func_00282CD8(result, velocity, scaled);
        qcopy(point, position);
        point[0] += func_0033BB78(0.0f, 0.0375f);
        point[1] += func_0033BB78(0.0f, 0.0375f);
        point[2] += func_0033BB78(0.0f, 0.0375f);
        func_002C2210(point, 30, 0x7f207f7f, 0, sign, velocity, size * 0.1f, size, 0.003f, 0);
        func_002C2210(point, 30, 0x7f7f7f7f, 1, -sign, velocity, size * 0.07f, size * 0.7f, 0.003f, 0);
    }
}

INCLUDE_ASM("asm/levels", func_L04_0040C368);

INCLUDE_ASM("asm/levels", func_L04_0040C880);

extern void func_L04_0040D148();

extern void func_L04_0040CE30();

void func_L04_0040CDD0(unsigned char *a0)
{
    unsigned char *s = *(unsigned char **)(a0 + 0x68);

    if (*(unsigned int *)(s + 0x4D8) != 0) {
        func_L04_0040D148(a0, -1);
    } else if (*(unsigned int *)(s + 0x768) != 0) {
        func_L04_0040D148(a0, *(unsigned int *)(s + 0x764));
    } else if (*(unsigned char *)(a0 + 0xBC) != 6) {
        func_L04_0040CE30(a0);
    }
}

extern void func_0029FCC0(void *, int, void *);

extern void func_00282D30(void *, void *, float);

extern void func_00282CC0(void *, void *, void *);

extern float func_00283CE0(int);

/* The five floats come first and the two ints last: the floats then go to
   f12-f16 and the ints to a1 and a2, and the int argument is set up after
   the float ones, as the retail code has it. */
extern void func_L00_003F8280(void *, float, float, float, float, float, int, int);

/* The emitter table the object points at: the slot id at 0x644, then the
   four rows of four heights from 0x660 on. */
typedef struct {
    char pad_000[0x644];
    int slot;
    char pad_648[0x18];
    float row660[4];
    float row670[4];
    float row680[4];
    float row690[4];
} L04_0040CE30_OBJ;

/* Walks the four rows of the emitter table: every row's height is lowered by
   the shared floor, the three threshold vectors are nudged by the row's share
   and handed to the particle scheduler, and a row that sinks too far is lifted
   back to the floor. */
void func_L04_0040CE30(char *a0)
{
    L04_0040CE30_OBJ *s2 = *(L04_0040CE30_OBJ **)(a0 + 0x68);
    float vec3[4];
    float vec4[4];
    float vec2[4];
    float tmp[4];
    char *dir = a0 + 0xC0;
    int i;

    for (i = 0; i < 4; i++) {
        float f22;
        float f21;
        float f20;

        func_0029FCC0(a0, 2, vec2);
        func_0029FCC0(a0, 3, vec3);
        func_0029FCC0(a0, 4, vec4);

        s2->row670[i] = s2->row670[i] - s2->row660[i];
        func_00282D30(tmp, dir, s2->row670[i]);
        func_00282CC0(vec3, vec3, tmp);

        f22 = func_00283CE0(i) * 0.25f;
        f21 = f22 * 0.1f;
        vec3[2] = vec3[2] + f21;
        f20 = f22 * -0.025f + 0.05f;
        func_L00_003F8280(vec3, f20, 0.0f, 0.0f, 0.0f, 0.0025f, s2->slot, 1);
        if (s2->row670[i] < -0.2f) {
            s2->row670[i] = -0.05f;
        }

        s2->row680[i] = s2->row680[i] - s2->row660[i];
        func_00282D30(tmp, dir, s2->row680[i]);
        func_00282CC0(vec2, vec2, tmp);
        vec2[2] = vec2[2] + f21;
        func_L00_003F8280(vec2, f20, 0.0f, 0.0f, 0.0f, 0.0025f, s2->slot, 1);
        if (s2->row680[i] < -0.2f) {
            s2->row680[i] = -0.05f;
        }

        s2->row690[i] = s2->row690[i] - s2->row660[i];
        func_00282D30(tmp, dir, s2->row690[i]);
        func_00282CC0(vec4, vec4, tmp);
        vec4[2] = vec4[2] + f21;
        func_L00_003F8280(vec4, f22 * -0.050000004f + 0.075f, 0.0f, 0.0f, 0.0f, 0.0025f, s2->slot, 1);
        if (s2->row690[i] < -0.19f) {
            s2->row690[i] = -0.05f;
        }
    }
}

INCLUDE_ASM("asm/levels", func_L04_0040D148);

INCLUDE_ASM("asm/levels", func_L04_0040DCA8);

INCLUDE_ASM("asm/levels", func_L04_0040DF90);

extern BatchA_A04_u8 D_00188660[];

extern void func_002E59F8(int handle);

/* Releases the callback records this moby still holds: every handle slot that is set
   names a record of the callback table, and the one that belongs to this moby is
   handed to the release helper. Each slot is cleared afterwards. */
void func_L04_0040E248(int a0, BatchA_A04_u8 *a1)
{
    int id = a0;
    BatchA_A04_u8 *p = a1;
    int v;
    BatchA_A04_u8 *rec;

    v = *(int *)(p + 0x748);
    if (v != -1) {
        rec = D_00188660 + v * 0x70;
        if (*(int *)(rec + 0x88) == id && rec[0x74] != 0) {
            func_002E59F8(v);
        }
    }
    *(int *)(p + 0x748) = -1;

    v = *(int *)(p + 0x74C);
    if (v != -1) {
        rec = D_00188660 + v * 0x70;
        if (*(int *)(rec + 0x88) == id && rec[0x74] != 0) {
            func_002E59F8(v);
        }
    }
    *(int *)(p + 0x74C) = -1;

    v = *(int *)(p + 0x714);
    if (v != -1) {
        rec = D_00188660 + v * 0x70;
        if (*(int *)(rec + 0x88) == id && rec[0x74] != 0) {
            func_002E59F8(v);
        }
    }
    *(int *)(p + 0x714) = -1;

    v = *(int *)(p + 0x3BC);
    if (v != -1) {
        rec = D_00188660 + v * 0x70;
        if (*(int *)(rec + 0x88) == id && rec[0x74] != 0) {
            func_002E59F8(v);
        }
    }
    *(int *)(p + 0x3BC) = -1;

    v = *(int *)(p + 0x328);
    if (v != -1) {
        rec = D_00188660 + v * 0x70;
        if (*(int *)(rec + 0x88) == id && rec[0x74] != 0) {
            func_002E59F8(v);
        }
    }
    *(int *)(p + 0x328) = -1;

    v = *(int *)(p + 0x330);
    if (v != -1) {
        rec = D_00188660 + v * 0x70;
        if (*(int *)(rec + 0x88) == id && rec[0x74] != 0) {
            func_002E59F8(v);
        }
    }
    *(int *)(p + 0x330) = -1;

    v = *(int *)(p + 0x334);
    if (v != -1) {
        rec = D_00188660 + v * 0x70;
        if (*(int *)(rec + 0x88) == id && rec[0x74] != 0) {
            func_002E59F8(v);
        }
    }
    *(int *)(p + 0x32C) = 0;
    *(int *)(p + 0x334) = -1;
    *(int *)(p + 0x324) = 0;
}

INCLUDE_ASM("asm/levels", func_L04_0040E460);

/* func_L04_0040EC80 is in L04_00402D90-aim.c. */

INCLUDE_ASM("asm/levels", func_L04_0040EF50);

void func_L04_0040F5D0(unsigned char *m)
{
    float delta[4];
    L04PathState *p = *(L04PathState **)(m + 0x68);
    unsigned char *base, *path, *other;
    int i, j;
    float closest, index, distance;
    if (p->primary == -1) return;
    base = D_L04_001FE340[p->primary];
    if (*(int *)base < 3) {
        p->primary = -1;
        return;
    }
    *(float *)(base + 0x1c) = func_00282E48(base + 0x10, base + 0x20);
    for (i = 0; i < 4; i++) {
        if (p->branches[i] == -1) continue;
        path = D_L04_001FE340[p->branches[i]];
        if (*(int *)path >= 4) {
            *(float *)(path + 0x1c) = func_00282E48(path + 0x10, path + 0x20);
            index = 0.0f;
            closest = 999999.0f;
            if (p->parents[i] != -1) other = D_L04_001FE340[p->branches[p->parents[i]]];
            else other = base;
            for (j = 0; j < *(int *)other - 1; j++) {
                func_00282CF0(delta, other + 0x10 + j * 16, path + 0x10);
                distance = func_L00_002EE290(delta);
                if (distance < closest) {
                    index = func_00283CE0(j);
                    closest = distance;
                }
            }
            *(float *)(path + 0x2c) = index;
            *(float *)(path + 0x4c) = func_00282E48(other + 0x10 + func_00283CF0(index) * 16, path + 0x10) + *(float *)(path + 0x2c) * *(float *)(other + 0x1c);
            index = 0.0f;
            closest = 999999.0f;
            if (p->links[i] != -1) other = D_L04_001FE340[p->branches[p->links[i]]];
            else other = base;
            for (j = 0; j < *(int *)other - 1; j++) {
                func_00282CF0(delta, other + 0x10 + j * 16, path + *(int *)path * 16);
                distance = func_L00_002EE290(delta);
                if (distance < closest) {
                    index = func_00283CE0(j);
                    closest = distance;
                }
            }
            *(float *)(path + 0x3c) = index;
            *(float *)(path + 0x5c) = func_00282E48(other + 0x10 + func_00283CF0(index) * 16, path + *(int *)path * 16) + *(float *)(path + 0x3c) * *(float *)(other + 0x1c);
        } else p->branches[i] = -1;
    }
}

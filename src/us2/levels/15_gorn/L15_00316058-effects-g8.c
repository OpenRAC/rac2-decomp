/* func_US2_L15_00316058, the USA v2.00 copy of func_L15_00315428: the same C, plus a level test (0x33) before the
 * 0xFA0 effect. */
#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef union Vec {
    Quad q;
    float f[4];
} Vec;
#define FIELD(t, p, o) (*(t *)((char *)(p) + (o)))

typedef struct Stage {
    char pad[0x30];
    int busy, frame;
    char pad38[12];
    short count;
    char pad46[0x146];
    char *objects[4];
} Stage;

extern Stage D_L15_001BD4C0;
extern int D_001A79F0;
extern float D_L15_00293010[][8];
extern char D_L15_001A9420[16] SDATA(D_L15_001A9420);
extern char D_L15_001A9430[16] SDATA(D_L15_001A9430);
extern char D_L15_001A9440[16] SDATA(D_L15_001A9440);
extern void func_L00_002FC980(void);
extern void func_US2_002E72D8(void *);
extern void func_L00_00326048(void *, void *, int, int, float);
extern void func_00283AF0(void *, void *);
extern void func_00283958(void *, void *);
extern void func_L01_0031A278(void *, void *, float, float, float);
extern void func_L05_00424990(void *, int, int, int, int, int, int, int, int, int, int, float);
extern int func_002A77E0(int);
extern float func_002A78D8(float, float);
extern float func_002A7878(float, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_L05_00419CC8(void *, void *, void *, int, int, int, int, int, float);
extern void func_0029FC20(void *, int, void *);
extern void func_00283678(void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_002ACB48(void *, float);
extern void func_L00_0033C0D0(void *, void *, void *, void *, int);

/* Updates the stage objects and emits effects at the scripted frame counts. */
void func_US2_L15_00316058(void)
{
    /* The joint transform reuses the earlier effect vectors and writes 64 bytes. */
    union {
        struct { Vec a, b, c; } effect;
        Vec joint[4];
    } scratch;
    Vec matrix[3], offset, velocity, first, second, third, fourth;
    char *p;
    int n;
    float sign;
    float *row;

    func_L00_002FC980();
    for (n = 0; n < D_L15_001BD4C0.count; n++) {
        /* Stage.objects[n], word 99 of the stage. */
        char **slot = (char **)&D_L15_001BD4C0 + n;
        char *p = slot[99];
        if (p && FIELD(short, p, 0xAA) == 0xE29) {
            FIELD(unsigned short, p, 0x34) |= 0x800;
        }
        if (FIELD(short, p, 0xAA) == 0xD54) {
            func_US2_002E72D8(p);
        }
        if (p && FIELD(short, p, 0xAA) == 0xFA0 && D_001A79F0 != 0x33) {
            if (FIELD(char *, p, 0x68)) {
                func_L00_00326048(p, FIELD(char *, p, 0x68) + 0xC,
                                 0x80AAAAD2, 0x80396464, 0.061086535f);
            }
        }
    }
    if (D_001A79F0 != 15 || D_L15_001BD4C0.busy) {
        return;
    }

    p = D_L15_001BD4C0.objects[2];
    if (D_L15_001BD4C0.frame == 13) {
        func_00283AF0(FIELD(char *, p, 0x58) + 0x10, &scratch.effect.b);
        func_00283958(&scratch.effect.b, p + 0xC0);
        func_L01_0031A278(p, &scratch.effect.a, 4, 3, 5);
        func_L05_00424990(&scratch.effect.a, 1, 25, 20, 20, 20, 45, 1, 1, 1, 0, 1.5f);
    }
    if ((unsigned)(D_L15_001BD4C0.frame - 20) >= 31 && !func_002A77E0(3)) {
        sign = 1;
        if (func_002A77E0(2)) {
            sign = -1;
        }
        row = D_L15_00293010[func_002A77E0(3)];
        func_L01_0031A278(p, &scratch.effect.a, row[0], row[1], row[2]);
        func_L01_0031A278(p, &scratch.effect.b, row[4], row[5], row[6]);
        scratch.effect.b.f[0] += func_002A78D8(.5f, 1.5f);
        scratch.effect.b.f[1] += func_002A78D8(.5f, 1.5f);
        scratch.effect.b.f[2] += func_002A78D8(.5f, 1.5f);
        func_00282CF0(&scratch.effect.c, &scratch.effect.b, &scratch.effect.a);
        func_00282F20(&scratch.effect.c, &scratch.effect.c, 1.1666667f);
        func_L05_00419CC8(p, &scratch.effect.a, &scratch.effect.c, 0xbe4620, 0x783214, 1, 0, 1, sign);
    }
    if (D_L15_001BD4C0.frame < 140) {
        char *p = D_L15_001BD4C0.objects[3];
        float strength = .4f;
        func_0029FC20(p, 0, scratch.joint);
        /* Only the three rotation rows are needed by the following transforms. */
        func_00283678(matrix, scratch.joint);
        offset.q = 0;
        offset.f[0] = -.3f;
        offset.f[3] = 1;
        velocity.q = 0;
        func_00283098(&first, &offset, matrix);
        func_00282CC0(&first, &first, p + 0x10);
        first.f[3] = 0;
        second.q = first.q;
        third.q = first.q;
        fourth.q = first.q;
        func_002ACB48(&first, .3f);
        func_002ACB48(&second, .3f);
        func_002ACB48(&third, .3f);
        func_002ACB48(&fourth, .3f);
        velocity.f[0] = -(func_002A7878(30, 40) * 0.016666668f) * strength;
        func_00283098(&velocity, &velocity, matrix);
        func_L00_0033C0D0(p, &first, &velocity, D_L15_001A9420, 1);
        velocity.f[0] = -(func_002A7878(30, 40) * 0.016666668f) * strength;
        func_00283098(&velocity, &velocity, matrix);
        func_L00_0033C0D0(p, &second, &velocity, D_L15_001A9420, 1);
        velocity.f[0] = -(func_002A7878(30, 40) * 0.016666668f) * strength;
        func_00283098(&velocity, &velocity, matrix);
        func_L00_0033C0D0(p, &third, &velocity, D_L15_001A9430, 1);
        velocity.f[0] = -(func_002A7878(30, 40) * 0.016666668f) * strength;
        func_00283098(&velocity, &velocity, matrix);
        func_L00_0033C0D0(p, &fourth, &velocity, D_L15_001A9440, 1);
    }
}

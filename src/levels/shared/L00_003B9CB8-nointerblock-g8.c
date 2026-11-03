#include "include_asm.h"
#include "common.h"

/* func_L00_003C4B98 needs -fno-sched-interblock (config/cflags.txt): retail's inner-loop
   arms keep the index load common to both and the increments at the join. The basis pointer
   is taken before the first vector call: a frame address first used after a call is
   anchored behind it. */

extern int D_L00_001AFF28 __attribute__((sda));
extern float D_L00_001AFF2C __attribute__((sda));
extern float D_L00_001AFF30 __attribute__((sda));
extern float D_L00_001AFF34 __attribute__((sda));
extern unsigned int D_L00_001AFF38 __attribute__((sda));
extern char D_L00_001B8DC0[];
extern char D_0018A0E0[];
extern float D_L00_0023A770[][3];
extern float D_L00_00292370[][4];
extern float D_L00_00293590[][2];
extern float D_L00_00293EB0[][4];
extern short D_L00_002944B0[][4];
extern unsigned long func_0027C878(int);
extern void func_002FC560(unsigned int, unsigned long);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_002830C0(void *, void *, void *);
extern void func_00280328(void);
extern void func_00281810(int, void *, void *, void *, int);
extern void func_00280B90(void *, void *, int);

/* The quad func_00280B90 draws: four corners, their colours and texture coordinates, then the
   four GS register values it is drawn with. */
typedef struct {
    float corners[4][4];
    unsigned int colors[4];
    float uvs[4][2];
    unsigned long regs[4];
} Quad4B98;

/* The record the owner points to at 0x68. */
typedef struct {
    char pad_00[8];
    unsigned int color;
    char pad_0C[0x24];
    float position[4];
} Context4B98;

/* Builds a basis that faces the point at D_L00_001B8DC0 from the owner's record, transforms the
   290 points of D_L00_00292370 through it and draws them as three strips in the record's
   colour, then draws 32 quads whose corners are D_L00_00293EB0 points picked by D_L00_002944B0,
   corners 0-1 scaled by D_L00_001AFF30 and corners 2-3 by that times D_L00_001AFF34. */
void func_L00_003C4B98(char *owner)
{
    struct {
        Quad4B98 quad;
        float basis[3][4];
        float position[4], delta[4], up[4], point[4];
        unsigned int colors[290];
    } frame __attribute__((aligned(16)));
    Context4B98 *ctx = *(Context4B98 **)(owner + 0x68);
    float (*basis)[4];
    unsigned int rgba, rim;
    int i, j, k;
    short *indices;
    float scale, scale2;

    frame.quad.regs[1] = func_0027C878(D_L00_001AFF28);
    frame.quad.regs[2] = 0xFF9000000260UL;
    frame.quad.regs[3] = 0x8000000044UL;
    frame.quad.regs[0] = 0;
    func_002FC560(0x47, 0x53001);
    qcopy(frame.position, ctx->position);
    frame.position[3] = 1.0f;
    basis = frame.basis;
    func_00282CF0(frame.delta, D_L00_001B8DC0, frame.position);
    func_00282F20(basis[0], frame.delta, 1.0f);
    func_00282D30(frame.up, D_0018A0E0, -1.0f);
    func_00282DD8(basis[1], basis[0], frame.up);
    func_00282F20(basis[1], basis[1], 1.0f);
    func_00282DD8(basis[2], basis[1], basis[0]);
    func_00282D30(basis[0], basis[0], D_L00_001AFF2C);
    func_00282D30(basis[1], basis[1], D_L00_001AFF2C);
    func_00282D30(basis[2], basis[2], D_L00_001AFF2C);
    rgba = D_L00_001AFF38 | ctx->color;
    frame.quad.colors[3] = rgba;
    frame.quad.colors[2] = rgba;
    frame.quad.colors[1] = rgba;
    frame.quad.colors[0] = rgba;
    func_002FC560(6, func_0027C878(D_L00_001AFF28));
    func_002FC560(0x42, 0x8000000044UL);
    func_002FC560(8, 0);
    func_002FC560(0x14, 0xFF9000000260UL);
    func_002FC560(0x4A, 0);
    func_00280328();
    for (j = 0; j < 290; j++) {
        func_002830C0(frame.point, D_L00_00292370[j], frame.basis);
        D_L00_0023A770[j][0] = frame.point[0];
        D_L00_0023A770[j][1] = frame.point[1];
        D_L00_0023A770[j][2] = frame.point[2];
        frame.colors[j] = frame.quad.colors[0];
    }
    func_00281810(148, D_L00_0023A770[0], &frame.colors[0], D_L00_00293590[0], 1);
    func_00281810(109, D_L00_0023A770[146], &frame.colors[146], D_L00_00293590[146], 1);
    func_00281810(36, D_L00_0023A770[254], &frame.colors[254], D_L00_00293590[254], 1);

    frame.quad.regs[1] = func_0027C878(11);
    frame.quad.regs[3] = 0x8000000048UL;
    scale = D_L00_001AFF30;
    rim = ctx->color | 0x40000000;
    scale2 = scale * D_L00_001AFF34;
    frame.quad.colors[3] = 0;
    frame.quad.colors[1] = rim;
    frame.quad.colors[0] = rim;
    frame.quad.colors[2] = 0;
    for (i = 0; i < 32; i++) {
        indices = D_L00_002944B0[i];
        for (j = 0; j < 4; j++) {
            k = indices[j];
            if (j >= 2)
                func_00282D30(frame.quad.corners[j], D_L00_00293EB0[k], scale2);
            else
                func_00282D30(frame.quad.corners[j], D_L00_00293EB0[k], scale);
        }
        frame.quad.uvs[0][0] = 0.5f;
        frame.quad.uvs[0][1] = 0.5f;
        frame.quad.uvs[1][0] = 0.5f;
        frame.quad.uvs[1][1] = 0.5f;
        frame.quad.uvs[2][0] = 0.5f;
        frame.quad.uvs[2][1] = 1.0f;
        frame.quad.uvs[3][0] = 0.5f;
        frame.quad.uvs[3][1] = 1.0f;
        func_00280B90(&frame.quad, frame.basis, 0);
    }
}

extern char D_L00_0023DDA0[] __attribute__((nosda));

extern void func_L00_003BC228(char *a0, char *a1);

extern int func_002A7820(int a, int b);

extern float func_002A7940(void);

extern void func_00281EB8(char *a, int b, unsigned int c, int d, float e, float f, float g);

/* Walks the level's table of records and draws the two sprites of the record the owner
   holds, when that record is still free. The record's own field is the owner, the one
   after it says whether it is free. Without interblock scheduling the two skips stay likely
   branches. Each sprite's colour is its own local: one shared variable dies twice, becomes a
   global pseudo, and the shifted alpha no longer ties to its saved register. */
void func_L00_003BBF48(char *a0)
{
    unsigned int firstRGB = 0x103080;
    unsigned int secondRGB = 0xFFFFFF;
    char *base = D_L00_0023DDA0;
    char *p = base + 0x30;
    char *q = base;
    int i;
    int color;
    int color2;
    float f;

    for (i = 29; i >= 0; p += 0xA0, i--, q += 0xA0) {
        if (*(int *)(p + 0x5C) == (int)a0) {
            func_L00_003BC228(a0, q);
            if (*(int *)(p + 0x64) == 0) {
                color = func_002A7820(0x50, 0x60);
                color = (int)(color << 24) | firstRGB;
                f = func_002A7940();
                func_00281EB8(p, 0x31, color, 1, 0.5f, 0.15f, f);
                color2 = func_002A7820(0x50, 0x60);
                color2 = (int)(color2 << 24) | secondRGB;
                f = func_002A7940();
                func_00281EB8(p, 0x31, color2, 1, 0.3f, 0.151f, f);
            }
        }
    }
}

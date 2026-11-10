#include "common.h"

/* A textured quad as func_00281DE8 sets it up and func_00280B90 draws it. */
typedef struct {
    f32 corners[4][4];          /* 0x00 */
    u32 color[4];               /* 0x40: one per corner */
    f32 uv[8];                  /* 0x50: u, v per corner */
    u32 renderState[8];         /* 0x70 */
} BeamQuad;

/* The instance data of the beam moby. */
typedef struct {
    u8 pad000[0x260];
    s32 target;                 /* 0x260: index of the moby the beam ends on */
    u8 pad264[0x26C - 0x264];
    s32 joint;                  /* 0x26C: the joint of that moby it ends at */
    f32 scroll[2];              /* 0x270: texture scroll of the two beam layers */
} BeamVars;

/* The moby, as far as func_L10_003F61C8 reads it: one 0x100-byte moby table entry. */
typedef struct {
    u8 pad00[0x10];
    f32 position[4];            /* 0x10 */
    u8 pad20[0x68 - 0x20];
    BeamVars *vars;             /* 0x68 */
    u8 pad6C[0x100 - 0x6C];
} Moby;

/* The moby table. Read as [0] of an incomplete sda array, for the absolute lui/lw
   load (docs/build/compiler-notes.md). */
extern Moby *D_L10_001B251C[] __attribute__((sda));
extern u8 D_L10_001B9680[];

extern s32 func_002A7820(s32 min, s32 max);
extern f32 func_002A7878(f32 min, f32 max);
extern f32 func_002A7940(void);
extern void func_00282CC0(void *out, void *a, void *b);
extern void func_0029FC20(Moby *moby, s32 joint, f32 matrix[4][4]);
extern s32 func_001163B0(void);
extern void func_00281DE8(BeamQuad *quad, s32 texture, s32 kind, s32 a3);
extern void func_00280B90(BeamQuad *quad, s32 a1, s32 a2);
extern void func_00282CF0(void *out, void *a, void *b);
extern void func_00282DD8(void *out, void *a, void *b);
extern void func_00282F20(void *out, void *in, f32 length);
extern void func_00281EB8(void *position, s32 texture, u32 color, s32 kind,
                          f32 scale, f32 offset, f32 angle);

/* Draws the beam from the moby to a joint of its target moby: two scrolling layers (each
   frame one of two textures at random) and a wider glow, each a quad either side of the
   line facing D_L10_001B9680, then two sprites at the far end. */
void func_L10_003F61C8(Moby *moby)
{
    BeamQuad q;
    f32 end[4] __attribute__((aligned(16)));
    f32 matrix[4][4] __attribute__((aligned(16)));
    f32 view[4];
    f32 direction[4];
    f32 side[4];
    Moby *mobies = D_L10_001B251C[0];
    BeamVars *vars = moby->vars;
    f32 *position;
    f32 *uv;
    s32 i;
    u32 layer1Color;
    u32 layer2Color;
    u32 spriteColor;
    f32 size1;
    f32 size2;

    func_0029FC20(&mobies[vars->target], vars->joint, matrix);
    qcopy(end, matrix[3]);

    /* First layer. */
    if (func_001163B0() & 1)
        func_00281DE8(&q, 0x17, 0, 0x80);
    else
        func_00281DE8(&q, 0x30, 0, 0x80);
    layer1Color = ((u32)func_002A7820(0x20, 0x80) << 24) | 0xFFFFFF;
    position = moby->position;
    uv = q.uv;
    q.color[0] = q.color[1] = q.color[2] = q.color[3] = layer1Color;
    q.uv[0] = 0;
    q.uv[1] = 0;
    q.uv[2] = 0;
    q.uv[3] = 1;
    q.uv[5] = 0;
    q.uv[6] = 5;
    q.uv[4] = 5;
    q.uv[7] = 1;
    for (i = 0; i < 4; ++i) {
        uv[i * 2] -= vars->scroll[0];
        if (uv[i * 2] <= -8.0f)
            uv[i * 2] += 8.0f;
    }
    vars->scroll[0] += func_002A7878(0.1f, 0.25f);
    if (vars->scroll[0] >= 8.0f)
        vars->scroll[0] -= 8.0f;
    func_00282CF0(view, position, D_L10_001B9680);
    func_00282CF0(direction, end, position);
    func_00282DD8(side, view, direction);
    func_00282F20(side, side, 2.0f);
    func_00282CC0(q.corners[0], position, side);
    func_00282CF0(q.corners[1], position, side);
    func_00282CC0(q.corners[2], end, side);
    func_00282CF0(q.corners[3], end, side);
    func_00280B90(&q, 0, 0);

    /* Second layer. */
    if (func_001163B0() & 1)
        func_00281DE8(&q, 0x17, 0, 0x80);
    else
        func_00281DE8(&q, 0x2F, 0, 0x80);
    layer2Color = ((u32)func_002A7820(0x20, 0x80) << 24) | 0xFFFFFF;
    q.color[0] = q.color[1] = q.color[2] = q.color[3] = layer2Color;
    q.uv[0] = 0;
    q.uv[1] = 0;
    q.uv[2] = 0;
    q.uv[3] = 1;
    q.uv[5] = 0;
    q.uv[6] = 5;
    q.uv[7] = 1;
    q.uv[4] = 5;
    for (i = 0; i < 4; ++i) {
        uv[i * 2] -= vars->scroll[1];
        if (uv[i * 2] <= -8.0f)
            uv[i * 2] += 8.0f;
    }
    vars->scroll[1] += func_002A7878(0.08f, 0.1f);
    if (vars->scroll[1] >= 8.0f)
        vars->scroll[1] -= 8.0f;
    func_00282CF0(view, position, D_L10_001B9680);
    func_00282CF0(direction, end, position);
    func_00282DD8(side, view, direction);
    func_00282F20(side, side, 2.0f);
    func_00282CC0(q.corners[0], position, side);
    func_00282CF0(q.corners[1], position, side);
    func_00282CC0(q.corners[2], end, side);
    func_00282CF0(q.corners[3], end, side);
    func_00280B90(&q, 0, 0);

    /* The glow: four units either side at the moby, three at the far end. */
    func_00281DE8(&q, 0xE, 1, 0x80);
    q.color[0] = q.color[1] = q.color[2] = q.color[3] = 0x40FF0020;
    q.uv[0] = 0;
    q.uv[1] = 0;
    q.uv[2] = 0;
    q.uv[3] = 1;
    q.uv[4] = 1;
    q.uv[5] = 0;
    q.uv[6] = 1;
    q.uv[7] = 1;
    func_00282F20(side, side, 4.0f);
    func_00282CC0(q.corners[0], position, side);
    func_00282CF0(q.corners[1], position, side);
    func_00282F20(side, side, 3.0f);
    func_00282CC0(q.corners[2], end, side);
    func_00282CF0(q.corners[3], end, side);
    func_00280B90(&q, 0, 0);

    /* Two sprites of random size and angle at the far end. */
    size1 = func_002A7878(3.5f, 4.5f);
    func_00281EB8(end, 0x31, 0x40800000, 1, size1, 2.5f, func_002A7940());
    spriteColor = ((u32)func_002A7820(0x40, 0x80) << 24) | 0x7F7F7F;
    size2 = func_002A7878(2.5f, 3.5f);
    func_00281EB8(end, 0x31, spriteColor, 1, size2, 2.5f, func_002A7940());
}

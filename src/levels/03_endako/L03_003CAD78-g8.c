#include "common.h"
typedef int TI128 __attribute__((mode(TI)));

/* A pair of floats: the level's tables of them at 0x1B0368 (the first halves,
   in the small data area) and at 0x1B036C (the second halves, absolute). */
typedef struct {
    f32 v;
    f32 w;
} L03_Pair;

extern u32 D_L03_001B035C __attribute__((sda));
extern s32 D_L03_001B0360 __attribute__((sda));
extern s32 D_L03_001B0364 __attribute__((sda));
extern L03_Pair D_L03_001B0368[] SDATA(D_L03_001B0368);
extern L03_Pair D_L03_001B036C[] __attribute__((sda));
extern TI128 D_L03_001B0390[] SDATA(D_L03_001B0390);
extern s32 D_L03_001B03D0[] SDATA(D_L03_001B03D0);
extern f32 D_L03_001B9840[];

extern void func_00282C88(TI128 *moby);
extern f32  func_00283248(f32 moby, f32 a1);
extern void func_00283410(void *moby, void *a1);
extern s32  func_0027C878(s32 moby);
extern void func_00280B90(void *moby, void *a1, s32 a2);

/* Builds the actor's effect track: the aim, the four corners of the level's
   tables, and the two packed words the level keeps. */
void func_L03_003CAD78(char *moby)
{
    u8 packet[0xE0];
    f32 *vars;
    u64 mode_bits;
    s32 *pi;
    L03_Pair *pd;
    L03_Pair *px;
    TI128 *pq;
    TI128 *sourceq;
    L03_Pair *sourcex;
    int i;

    vars = *(f32 **)(moby + 0x68);
    ClearVector128((TI128 *)(packet + 0xD0));
    *(f32 *)(packet + 0xD8) = FastMatrixHelperA(D_L03_001B9840[0x140 / 4] - *(f32 *)(moby + 0x10),
                                          D_L03_001B9840[0x144 / 4] - *(f32 *)(moby + 0x14));
    euler_to_matrix(packet + 0x90, packet + 0xD0);
    qcopy(packet + 0xC0, moby + 0x10);
    *(f32 *)(packet + 0xCC) = 1.0f;

    sourceq = D_L03_001B0390;
    pq = (TI128 *)packet;
    px = (L03_Pair *)(packet + 0x54);
    sourcex = D_L03_001B036C;
    pd = (L03_Pair *)(packet + 0x50);
    pi = (s32 *)(packet + 0x40);
    for (i = 0; i < 4; i++) {
        pi[i] = D_L03_001B03D0[i];
        pd[i].v = D_L03_001B0368[i].v + *vars;
        px[i].v = sourcex[i].v;
        qcopy(&pq[i], &sourceq[i]);
    }

    *(u64 *)(packet + 0x78) = GetEffectTextureDescriptor(D_L03_001B035C);
    mode_bits = ((u64)D_L03_001B0360 << 2) | ((u64)D_L03_001B0364 << 6)
               | ((u64)0x8000 << 24);
    *(u64 *)(packet + 0x88) = mode_bits;
    *(u64 *)(packet + 0x80) = 0x0000FF9000000260ULL;
    *(u64 *)(packet + 0x70) = 0;
    draw_world_quad(packet, packet + 0x90, 1);
}

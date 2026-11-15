#include "common.h"

/* g_nGameState (symbol_addrs): read once through $gp, once by its absolute address. */
extern int D_001A8BB0;
extern int D_001A8BB0_gp SDATA(D_001A8BB0);
extern short D_00152C00[];
/* Two GP-addressed tables: a 32-byte block copied into the packet, and four row vectors. */
extern char D_001ABF90[32] SDATA(D_001ABF90);
extern char D_001ABFB0[64] SDATA(D_001ABFB0);

typedef struct {
    float v[4];
} Vector;

typedef struct {
    Vector rows[4];
    int colors[4];
    char block[32];
    long long tags[4];
} Packet;

extern void func_00282D60(void *, void *, float);
extern int func_00283EB0(void *, int *, float);
extern u64 func_0027C878(int);
extern void func_00282B50(void *, void *, int);
extern void func_00282D30(void *, void *, float);
extern float func_002A89A8(void *, int, float);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00280B90(void *, void *, int);

/* Draws a soft shadow square on the ground under an object, fading it with distance and during the end-of-level fade. */
void func_002E6B78(char *object)
{
    float projected[4];
    Packet packet;
    float pos[4];
    int alpha;
    int i;
    float height;
    char *point;

    alpha = 0;
    scale_vector(projected, object, 0.0009765625f);
    if (FastMathHelperB(projected, &alpha, 32.0f) < 0)
        return;
    if (D_001A8BB0_gp == 6 && gHeroMoby_00152C00[16] == 1 && gHeroMoby_00152C00[17] >= 151) {
        alpha -= (gHeroMoby_00152C00[17] - 150) * 4;
        if (alpha <= 0)
            return;
    }
    packet.tags[1] = GetEffectTextureDescriptor(0);
    packet.tags[2] = 0xFF9000000260ULL;
    packet.tags[3] = 0x8000000044ULL;
    packet.tags[0] = 0;
    FastMemoryHelperC(packet.block, D_001ABF90, 32);
    FastVecScale(pos, object, 0.0009765625f);
    height = *(float *)(object + 24) + 0.1f;
    if (gCurrentGameMode == 6 || gCurrentGameMode == 0)
        height = ProbeGroundHeightBelow(object + 16, 0, 0.5f) + 0.1f;
    point = object + 16;
    for (i = 0; i < 4; i++) {
        Vector *row;

        packet.colors[i] = ((alpha >> 1) << 24) | 0x808080;
        row = &packet.rows[i];
        matrix_mul_vec3(row, D_001ABFB0 + 16 * i, object + 192);
        FastVecAdd(row, row, point);
        row->v[2] = height;
    }
    draw_world_quad(packet.rows, 0, 0);
}

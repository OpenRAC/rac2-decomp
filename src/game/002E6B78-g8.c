#include "common.h"

/* g_nGameState (symbol_addrs): read once through $gp, once by its absolute address. */
extern int g_current_game_mode;
extern int D_001A8BB0_gp SDATA(D_001A8BB0);
extern short g_hero_moby_default[];
/* Two GP-addressed tables: a 32-byte block copied into the packet, and four row vectors. */
extern char g_ground_shadow_header[32] SDATA(D_001ABF90);
extern char g_ground_shadow_matrix[64] SDATA(D_001ABFB0);

typedef struct {
    float v[4];
} Vector;

typedef struct {
    Vector rows[4];
    int colors[4];
    char block[32];
    long long tags[4];
} Packet;

extern void scale_vector(void *, void *, float);
extern int math_fast_helper_b(void *, int *, float);
extern u64 GetEffectTextureDescriptor(int);
extern void mem_fast_helper_c(void *, void *, int);
extern void FastVecScale(void *, void *, float);
extern float coll_probe_ground_height_below(void *, int, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void draw_world_quad(void *, void *, int);

/* Draws a soft shadow square on the ground under an object, fading it with distance and during the end-of-level fade. */
void gfx_draw_ground_shadow(char *object)
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
    if (math_fast_helper_b(projected, &alpha, 32.0f) < 0)
        return;
    if (D_001A8BB0_gp == 6 && g_hero_moby_default[16] == 1 && g_hero_moby_default[17] >= 151) {
        alpha -= (g_hero_moby_default[17] - 150) * 4;
        if (alpha <= 0)
            return;
    }
    packet.tags[1] = GetEffectTextureDescriptor(0);
    packet.tags[2] = 0xFF9000000260ULL;
    packet.tags[3] = 0x8000000044ULL;
    packet.tags[0] = 0;
    mem_fast_helper_c(packet.block, g_ground_shadow_header, 32);
    FastVecScale(pos, object, 0.0009765625f);
    height = *(float *)(object + 24) + 0.1f;
    if (g_current_game_mode == 6 || g_current_game_mode == 0)
        height = coll_probe_ground_height_below(object + 16, 0, 0.5f) + 0.1f;
    point = object + 16;
    for (i = 0; i < 4; i++) {
        Vector *row;

        packet.colors[i] = ((alpha >> 1) << 24) | 0x808080;
        row = &packet.rows[i];
        matrix_mul_vec3(row, g_ground_shadow_matrix + 16 * i, object + 192);
        FastVecAdd(row, row, point);
        row->v[2] = height;
    }
    draw_world_quad(packet.rows, 0, 0);
}

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));

/* A pair of floats: the level's tables of them at 0x1B0368 (the first halves,
   in the small data area) and at 0x1B036C (the second halves, absolute). */
typedef struct {
    f32 v;
    f32 w;
} L03_Pair;

extern u32 g_effect_packet_texture_id __attribute__((sda));
extern s32 g_effect_packet_mode_a __attribute__((sda));
extern s32 g_effect_packet_mode_b __attribute__((sda));
extern L03_Pair g_effect_packet_offset_table[] SDATA(D_L03_001B0368);
extern L03_Pair g_effect_packet_source_table[] __attribute__((sda));
extern TI128 g_effect_packet_quad_table[] SDATA(D_L03_001B0390);
extern s32 g_effect_packet_index_table[] SDATA(D_L03_001B03D0);
extern f32 g_hero_l03_state_alias[];

extern void vec_clear_128(TI128 *moby);
extern f32  mat_fast_helper_a(f32 moby, f32 a1);
extern void euler_to_matrix(void *moby, void *a1);
extern long long GetEffectTextureDescriptor(s32 moby);
extern void draw_world_quad(void *moby, void *a1, s32 a2);

/* Builds the actor's effect track: the aim, the four corners of the level's
   tables, and the two packed words the level keeps. */
void moby_build_effect_packet(char *moby)
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
    vec_clear_128((TI128 *)(packet + 0xD0));
    *(f32 *)(packet + 0xD8) = mat_fast_helper_a(g_hero_l03_state_alias[0x140 / 4] - *(f32 *)(moby + 0x10),
                                          g_hero_l03_state_alias[0x144 / 4] - *(f32 *)(moby + 0x14));
    euler_to_matrix(packet + 0x90, packet + 0xD0);
    qcopy(packet + 0xC0, moby + 0x10);
    *(f32 *)(packet + 0xCC) = 1.0f;

    sourceq = g_effect_packet_quad_table;
    pq = (TI128 *)packet;
    px = (L03_Pair *)(packet + 0x54);
    sourcex = g_effect_packet_source_table;
    pd = (L03_Pair *)(packet + 0x50);
    pi = (s32 *)(packet + 0x40);
    for (i = 0; i < 4; i++) {
        pi[i] = g_effect_packet_index_table[i];
        pd[i].v = g_effect_packet_offset_table[i].v + *vars;
        px[i].v = sourcex[i].v;
        qcopy(&pq[i], &sourceq[i]);
    }

    *(u64 *)(packet + 0x78) = GetEffectTextureDescriptor(g_effect_packet_texture_id);
    mode_bits = ((u64)g_effect_packet_mode_a << 2) | ((u64)g_effect_packet_mode_b << 6)
               | ((u64)0x8000 << 24);
    *(u64 *)(packet + 0x88) = mode_bits;
    *(u64 *)(packet + 0x80) = 0x0000FF9000000260ULL;
    *(u64 *)(packet + 0x70) = 0;
    draw_world_quad(packet, packet + 0x90, 1);
}

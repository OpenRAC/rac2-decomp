#include "names.h"
/* The complete 64-byte corner table needs -G64 -Wa,-G64 for GP addressing.
 * Same packet and traversal as func_L00_00407C18, with this effect's data.
 */
#include "common.h"
typedef struct {
    float points[4][4];
    int colours[4];
    float params[8];
    u64 regs[4];
} DrawPacket8608;
extern float g_quad_l00_corner_table[4][4] __attribute__((sda));
extern float g_quad_inner_corner_scale __attribute__((sda));
extern float g_quad_outer_corner_scale __attribute__((sda));
extern float g_quad_offset_length __attribute__((sda));
extern int g_quad_l00_color __attribute__((sda));
extern char g_lightning_beam_points[];
extern char g_camera_l00_position[];
extern char g_hero_state_block[];
extern u64 GetEffectTextureDescriptor(int);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecCross(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void transform_vector(void *, void *, void *);
extern void draw_world_quad(void *, int, int);
typedef unsigned int Quad83E0 __attribute__((mode(TI)));
typedef union { Quad83E0 q; float f[4]; } Vec83E0;
typedef struct {
    Vec83E0 points[4];
    unsigned int colours[4];
    float params[8];
    u64 regs[4];
} DrawPacket83E0;
extern int FloatToInt(float);
extern unsigned int g_lightning_spark_color __attribute__((sda));
extern int g_lightning_spark_active[] __attribute__((sda));
extern float g_lightning_spark_alphas[] __attribute__((sda));
extern float g_lightning_spark_sizes[] __attribute__((sda));
extern Vec83E0 g_lightning_spark_positions[] __attribute__((sda));
extern Vec83E0 g_lightning_spark_directions[] __attribute__((sda));
/* Two passes of a camera-facing quad placed from object + 0xD0 (scaled by D_L00_001B00E8) and
   D_L00_002403C0: first with colour D_L00_001B00EC and corner scale D_L00_001B00E0, then
   white with corner scale D_L00_001B00E4. */
void DrawBeamOriginCameraFacingQuads(char *object)
{
    DrawPacket8608 packet;
    float basis[4][4];
    float vertex[4], offset[4];
    int i;
    packet.regs[1] = GetEffectTextureDescriptor(11);
    packet.regs[3] = 0x8000000048ULL;
    packet.regs[2] = 0xFF9000000260ULL;
    packet.regs[0] = 0;
    packet.params[0] = 0; packet.params[1] = 0; packet.params[2] = 0; packet.params[3] = 1;
    packet.params[4] = 1; packet.params[5] = 0; packet.params[6] = 1; packet.params[7] = 1;
    packet.colours[0] = packet.colours[1] =
        packet.colours[2] = packet.colours[3] = g_quad_l00_color;
    vec_scale_to_length(offset, object + 0xD0, g_quad_offset_length);
    FastVecAdd(basis[3], g_lightning_beam_points, offset);
    FastVecSub(offset, g_camera_l00_position, basis[3]);
    vec_scale_to_length(basis[0], offset, 1.0f);
    FastVecCross(basis[1], basis[0], g_hero_state_block);
    vec_scale_to_length(basis[1], basis[1], -1.0f);
    FastVecCross(basis[2], basis[1], basis[0]);
    for (i = 3; i >= 0; i--) {
        FastVecScale(vertex, g_quad_l00_corner_table[3 - i], g_quad_inner_corner_scale);
        transform_vector(packet.points[3 - i], vertex, basis);
    }
    draw_world_quad(&packet, 0, 0);
    packet.colours[3] = -1; packet.colours[2] = -1; packet.colours[1] = -1; packet.colours[0] = -1;
    for (i = 3; i >= 0; i--) {
        FastVecScale(vertex, g_quad_l00_corner_table[3 - i], g_quad_outer_corner_scale);
        transform_vector(packet.points[3 - i], vertex, basis);
    }
    draw_world_quad(&packet, 0, 0);
}

/* Twin of func_L00_004079C8 with this level code's data: a quad for each of the three active
   sparks of func_L00_003C6B98's table, basis from the spark's direction D_L00_001B2A50[i] and
   the up vector D_0018A0E0, placed at D_L00_001B2A20[i], corners D_L00_001B00A0 scaled by
   D_L00_001B2AB0[i], alpha from D_L00_001B2A90[i] and colour D_L00_001B003C. The spark tables
   are incomplete sda arrays, which gives retail's unsplit lui/addiu addresses. */
void DrawLightningArcSparks2(void)
{
    DrawPacket83E0 packet;
    Vec83E0 basis[4], vertex;
    Vec83E0 *corner;
    unsigned int color, c;
    int i, j;

    packet.regs[1] = GetEffectTextureDescriptor(8);
    packet.regs[3] = 0x8000000048ULL;
    packet.regs[2] = 0xFF9000000260ULL;
    color = g_lightning_spark_color & 0xFFFFFF;
    packet.regs[0] = 0;
    packet.params[0] = 0; packet.params[1] = 0; packet.params[2] = 0; packet.params[3] = 1;
    packet.params[4] = 1; packet.params[5] = 0; packet.params[6] = 1; packet.params[7] = 1;
    for (i = 0; i < 3; i++) {
        if (g_lightning_spark_active[i]) {
            c = color | (FloatToInt(g_lightning_spark_alphas[i]) << 24);
            packet.colours[0] = packet.colours[1] = packet.colours[2] = packet.colours[3] = c;
            qcopy(&basis[3], &g_lightning_spark_positions[i]);
            qcopy(&basis[0], &g_lightning_spark_directions[i]);
            FastVecScale(&basis[2], g_hero_state_block, -1.0f);
            FastVecCross(&basis[1], &basis[0], &basis[2]);
            vec_scale_to_length(&basis[1], &basis[1], 1.0f);
            FastVecCross(&basis[2], &basis[1], &basis[0]);
            corner = (Vec83E0 *)g_quad_l00_corner_table;
            for (j = 3; j >= 0; corner++, j--) {
                FastVecScale(&vertex, corner, g_lightning_spark_sizes[i]);
                transform_vector(&packet.points[3 - j], &vertex, basis);
            }
            draw_world_quad(&packet, 0, 0);
        }
    }
}

#include "names.h"
/* func_L00_00407C18 needs -G64 -Wa,-G64: its 64-byte corner table D_L00_001B0F20 is reached
   through $gp. Same packet layout as func_L00_00396078. The packet's GS registers are set in
   RAC1's order (texture, flags, mode, primitive), the colours last: sched1 and local-alloc
   then give retail's store order and registers. */
#include "common.h"
typedef struct {
    float points[4][4];
    int colours[4];
    float params[8];
    u64 regs[4];
} DrawPacket7C18;
extern float g_beam_l00_corner_table[4][4] __attribute__((sda));
extern float g_beam_corner_scale_main __attribute__((sda));
extern float g_beam_corner_scale_white __attribute__((sda));
extern float g_beam_quad_offset_scale __attribute__((sda));
extern int g_beam_l00_quad_color __attribute__((sda));
extern char g_sheepinator_beam_points[];
extern char g_camera_l00_position[];
extern char g_hero_state_block[];
extern u64 GetEffectTextureDescriptor(int);
extern void vec_scale_to_length(void *, void *, float);
extern void func_002EE108(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecCross(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void transform_vector(void *, void *, void *);
extern void draw_world_quad(void *, int, int);
/* Two passes of a camera-facing quad placed from object + 0xD0 (scaled by D_L00_001B0F68) and
   D_L00_00254A60: first with colour D_L00_001B0F6C and corner scale D_L00_001B0F60, then
   white with corner scale D_L00_001B0F64. */
/* Draws the glowing flare at the start of the Sheepinator beam. */
void DrawTwoPassCameraQuad(char *object)
{
    DrawPacket7C18 packet;
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
        packet.colours[2] = packet.colours[3] = g_beam_l00_quad_color;
    vec_scale_to_length(offset, object + 0xD0, g_beam_quad_offset_scale);
    func_002EE108(basis[3], g_sheepinator_beam_points, offset);
    FastVecSub(offset, g_camera_l00_position, basis[3]);
    vec_scale_to_length(basis[0], offset, 1.0f);
    FastVecCross(basis[1], basis[0], g_hero_state_block);
    vec_scale_to_length(basis[1], basis[1], -1.0f);
    FastVecCross(basis[2], basis[1], basis[0]);
    for (i = 3; i >= 0; i--) {
        FastVecScale(vertex, g_beam_l00_corner_table[3 - i], g_beam_corner_scale_main);
        transform_vector(packet.points[3 - i], vertex, basis);
    }
    draw_world_quad(&packet, 0, 0);
    packet.colours[3] = -1; packet.colours[2] = -1; packet.colours[1] = -1; packet.colours[0] = -1;
    for (i = 3; i >= 0; i--) {
        FastVecScale(vertex, g_beam_l00_corner_table[3 - i], g_beam_corner_scale_white);
        transform_vector(packet.points[3 - i], vertex, basis);
    }
    draw_world_quad(&packet, 0, 0);
}

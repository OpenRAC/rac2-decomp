/* func_PAL_L02_003EC4E8, the PAL copy of func_L02_003E80F8: the same C. */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef struct { float vertex[4][4]; unsigned int color[4]; float uv[4][2]; unsigned long long state[4]; } Packet __attribute__((aligned(16)));
extern int g_frame_l02_counter;
extern char *g_moby_l02_pool;
extern unsigned short *g_entity_group_lists[];
extern int g_quad_packet_texture_ids[] __attribute__((sda)), g_quad_packet_colors[] __attribute__((sda));
extern int D_L02_001B0A68_gp SDATA(D_L02_001B0A68), D_L02_001B0A98_gp SDATA(D_L02_001B0A98);
extern float g_quad_packet_uv_pairs[][2] SDATA(D_L02_001B0A78);
extern float g_quad_packet_extents[][4] MACRO_ADDR;
extern float D_L02_001B0AB0_gp[][4] SDATA(D_L02_001B0AB0);
extern float D_L02_001B0AF0_gp[][4] SDATA(D_L02_001B0AF0);
extern int g_quad_l02_packet_texture_id __attribute__((sda));
extern unsigned int g_quad_packet_color_pair[] SDATA(D_L02_001B0B38);
extern float g_quad_packet_extent_step __attribute__((sda));
extern float g_quad_packet_uv_table[][2] MACRO_ADDR;
extern float D_L02_001B0B48_gp[][2] SDATA(D_L02_001B0B48);
extern char g_camera_l02_position[];
extern float IntToFloat(int);
extern void euler_to_matrix(void *, void *), moby_transform_joint_point(void *, int, void *), transform_vector(void *, void *, void *);
extern int math_fast_helper_a(void *, float);
extern void multiply_matrix(void *, void *, void *);
extern void FillQuadPacket(void *, int, int, void *, void *, int);
extern void vec_clear_128(void *), euler_rotation_basis(void *, void *), matrix_mul_vec3(void *, void *, void *);
extern void multiply_matrix3x3(void *, void *, void *), draw_world_quad(void *, void *, int);
extern unsigned long long GetEffectTextureDescriptor(int);
extern void set_identity_matrix(void *), FastVecSub(void *, void *, void *), FastVecCross(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float), FastVecAdd(void *, void *, void *);
extern float math_random_float_range(float, float), math_random_angle(void);
extern unsigned int FastTweenColor(unsigned int, unsigned int, float);
extern void gfx_draw_billboard_quad(void *, int, unsigned int, int, float, float, float);

/* Draws the actor's object group as rotating quads, then a mirrored quad and three effects per
 * visible object. Each bound of the first vertex loop is built in two steps beside its test:
 * loop.c moves such a pair out of the loop after the copy of offsetAddress, while a single load
 * would stay ahead of that copy. */
void func_PAL_L02_003EC4E8(char *actor) {
    float matrices[32][16] __attribute__((aligned(16)));
    float rotation[16] __attribute__((aligned(16)));
    unsigned int visible[32];
    float tilt[12] __attribute__((aligned(16)));
    float probe[4] __attribute__((aligned(16)));
    Packet packet[2];
    float angles[4] __attribute__((aligned(16))), point[4] __attribute__((aligned(16)));
    float doubled[12] __attribute__((aligned(16))), identity[16] __attribute__((aligned(16)));
    float normal[4] __attribute__((aligned(16))), offset[4] __attribute__((aligned(16)));
    unsigned short *entry;
    unsigned short id;
    float frame;
    int count = 0, i = 0, layer, pass, nextLayer, nextPass;
    int uvIndex;
    int draw;
    float *offsetAddress;
    unsigned int color;
    *(Quad *)probe = 0;
    probe[0] = 30.0f;
    probe[3] = 1.0f;
    *(Quad *)point = 0;
    frame = IntToFloat(g_frame_l02_counter % 500);
    point[0] = (frame * 0.0016666667f + frame * 0.0016666667f) * 3.1415927f - 3.1415927f;
    *(Quad *)angles = *(Quad *)point;
    euler_to_matrix(rotation, angles);
    entry = g_entity_group_lists[*(unsigned char *)(actor + 0x21)];
    while (count < 32) {
        char *object;
        id = *entry;
        object = g_moby_l02_pool + (id & 0x7FFF) * 0x100;
        visible[count] = (*(unsigned short *)(object + 0x7C) >> 15) ^ 1;
        moby_transform_joint_point(object, 0, matrices[count]);
        transform_vector(point, probe, matrices[count]);
        point[3] = 30.0f;
        if (math_fast_helper_a(point, 512.0f) != -1) {
            multiply_matrix(matrices[count], matrices[count], rotation);
            count++;
        }
        if ((short)*entry++ < 0) break;
    }
    FillQuadPacket(packet, D_L02_001B0A68_gp, D_L02_001B0A98_gp, g_quad_packet_uv_pairs, D_L02_001B0AB0_gp, 1);
    FillQuadPacket(packet + 1, g_quad_packet_texture_ids[1], g_quad_packet_colors[2], g_quad_packet_uv_pairs, D_L02_001B0AF0_gp, 1);
    packet[0].color[1] = packet[0].color[3] = g_quad_packet_colors[1];
    packet[1].color[1] = packet[1].color[3] = g_quad_packet_colors[3];
    vec_clear_128(angles);
    angles[0] = 0.3926991f;
    euler_rotation_basis(tilt, angles);
    for (i = 0; i < 2; i++) {
        matrix_mul_vec3(packet[i].vertex[2], packet[i].vertex[2], tilt);
        matrix_mul_vec3(packet[i].vertex[3], packet[i].vertex[3], tilt);
    }
    multiply_matrix3x3(doubled, tilt, tilt);
    for (pass = 0; pass < 16; pass = nextPass) {
        int pair = (pass & 1) ? 2 : 0;
        nextPass = pass + 1;
        for (layer = 0; layer < 1; layer = nextLayer) {
            nextLayer = layer + 1;
            matrix_mul_vec3(packet[layer].vertex[pair], packet[layer].vertex[pair], doubled);
            matrix_mul_vec3(packet[layer].vertex[pair + 1], packet[layer].vertex[pair + 1], doubled);
            for (draw = 0; draw < count; draw++) {
                if (visible[draw]) draw_world_quad(packet + layer, matrices[draw], 1);
            }
        }
    }
    packet[0].state[1] = GetEffectTextureDescriptor(g_quad_l02_packet_texture_id);
    for (uvIndex = 0; uvIndex < 4; uvIndex++) {
        packet[0].uv[uvIndex][0] = D_L02_001B0B48_gp[uvIndex][0];
        packet[0].uv[uvIndex][1] = g_quad_packet_uv_table[uvIndex][1];
        packet[0].color[uvIndex] = g_quad_packet_color_pair[uvIndex & 1];
    }
    set_identity_matrix(identity);
    {
    int objectIndex;
    for (objectIndex = 0; objectIndex < count; objectIndex++) {
        int vertex;
        float *geometry;
        if (!visible[objectIndex]) continue;
        FastVecSub(point, g_camera_l02_position, matrices[objectIndex] + 12);
        FastVecCross(normal, matrices[objectIndex], point);
        normal[3] = 1.0f;
        qcopy(identity + 12, matrices[objectIndex] + 12);
        geometry = (float *)D_L02_001B0AB0_gp;
        {
            float *g = geometry;
            float (*v)[4] = packet[0].vertex;
            float (*lowerEnd)[4], (*allEnd)[4];
            do {
                float extent = g[2];
                offsetAddress = offset;
                lowerEnd = g_quad_packet_extents;
                lowerEnd += 2;
                if ((int)g < (int)lowerEnd) extent += g_quad_packet_extent_step;
                else extent -= g_quad_packet_extent_step;
                vec_scale_to_length(*v, normal, extent);
                vec_scale_to_length(offset, matrices[objectIndex], g[0]);
                g += 4;
                FastVecAdd(*v, *v, offset);
                v++;
                allEnd = g_quad_packet_extents;
                allEnd += 4;
            } while ((int)g < (int)allEnd);
        }
        draw_world_quad(packet, identity, 0);
        for (vertex = 0; vertex < 4; vertex++) {
            float extent = geometry[vertex * 4 + 2];
            if (vertex < 2) extent += g_quad_packet_extent_step;
            else extent -= g_quad_packet_extent_step;
            vec_scale_to_length(offset, normal, extent * -2.0f);
            FastVecAdd(packet[0].vertex[vertex], packet[0].vertex[vertex], offset);
        }
        draw_world_quad(packet, identity, 0);
        *(Quad *)offset = 0;
        offset[0] = 2.666f;
        offset[3] = 1.0f;
        transform_vector(offset, offsetAddress, matrices[objectIndex]);
        frame = math_random_float_range(0.0f, 1.0f);
        color = FastTweenColor(D_L02_001B0A98_gp, g_quad_packet_colors[1], frame);
        frame = math_random_angle();
        gfx_draw_billboard_quad(offset, 11, color, 1, 2.0f, 0.0f, frame);
        frame = math_random_float_range(0.0f, 1.0f);
        color = FastTweenColor(g_quad_packet_colors[2], g_quad_packet_colors[3], frame);
        frame = math_random_angle();
        gfx_draw_billboard_quad(offset, 11, color, 1, 2.75f, 0.0f, frame);
        frame = math_random_angle();
        gfx_draw_billboard_quad(offset, 49, color, 1, 2.75f, 0.0f, frame);
    }
    }
}

#include "common.h"

typedef struct { s16 vertex, texture; } SpriteIndex;
typedef struct {
    float points[4][4];
    u32 colors[4];
    float uv[4][2];
    u64 primitive, texture, tag, blend;
} SpritePacket;
extern int g_current_map_index;
extern unsigned char g_origin_vec[];
extern float g_aim_crosshair_vertices[][4];
extern float g_aim_crosshair_uvs[][2];
/* One table: retail addresses its vertex fields through $gp and its texture fields absolutely. */
extern SpriteIndex g_ship_crosshair_sprites[4][4] MACRO_ADDR;
extern SpriteIndex indices_gp[4][4] SDATA(D_L05_001B1C40);
extern int g_ship_crosshair_blend_a SDATA(D_L05_001B1C80);
extern int g_ship_crosshair_blend_b SDATA(D_L05_001B1C84);
extern int g_ship_crosshair_blend_c SDATA(D_L05_001B1C88);
extern int g_ship_crosshair_blend_d SDATA(D_L05_001B1C8C);
extern int g_ship_crosshair_blend_e SDATA(D_L05_001B1C90);
extern u32 g_ship_crosshair_color SDATA(D_L05_001B1C94);
extern float g_ship_crosshair_scale SDATA(D_L05_001B1C98);
extern u64 GetEffectTextureDescriptor(int);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void draw_world_quad(void *, void *, int);

/* Draws the object's four textured quads, each with four corners taken from the index table,
   in a basis facing the camera. */
/* Draws the ship's aiming mark as four small sprites facing the camera. */
void ship_draw_aim_crosshair(unsigned char *object)
{
    unsigned char *state = *(unsigned char **)(object + 0x68);
    SpritePacket packet;
    float matrix[4][4];
    int i, j;
    u64 blend;
    if (g_current_map_index == 20)
        packet.texture = GetEffectTextureDescriptor(65);
    else
        packet.texture = GetEffectTextureDescriptor(63);
    packet.tag = 0xFF9000000260ULL;
    blend = (u64)g_ship_crosshair_blend_a;
    blend |= (u64)g_ship_crosshair_blend_b << 2;
    blend |= (u64)g_ship_crosshair_blend_c << 4;
    blend |= (u64)g_ship_crosshair_blend_d << 6;
    blend |= (u64)g_ship_crosshair_blend_e << 32;
    packet.blend = blend;
    packet.colors[0] = packet.colors[1] = packet.colors[2] = packet.colors[3] = g_ship_crosshair_color;
    packet.primitive = 0;
    qcopy(matrix[3], state + 0x20);
    FastVecSub(matrix[0], g_origin_vec, matrix[3]);
    vec_scale_to_length(matrix[0], matrix[0], 1.0f);
    FastVecCross(matrix[1], matrix[0], g_origin_vec + 0x250);
    vec_scale_to_length(matrix[1], matrix[1], 1.0f);
    FastVecCross(matrix[2], matrix[1], matrix[0]);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            int vertex = indices_gp[i][j].vertex;
            int texture = g_ship_crosshair_sprites[i][j].texture;
            FastVecScale(packet.points[j], g_aim_crosshair_vertices[vertex], g_ship_crosshair_scale);
            packet.uv[j][0] = g_aim_crosshair_uvs[texture][0];
            packet.uv[j][1] = g_aim_crosshair_uvs[texture][1];
        }
        draw_world_quad(&packet, matrix, 0);
    }
}

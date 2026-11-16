#include "include_asm.h"
#include "names.h"

/* Level counterpart of func_00327D50; the vector clear takes one register,
   as in the matched boot unit. */

typedef unsigned int RenderQuad __attribute__((mode(TI)));
typedef union { RenderQuad word; float v[4]; } RenderVector;
typedef struct { float x, y, z, w; } RenderVec __attribute__((aligned(16)));

typedef struct {
    RenderVec vertex[4];
    unsigned int color[4];
    float uv[4][2];
    long long tag[4];
} RenderPacket;

extern long long GetEffectTextureDescriptor(int);
extern void FastVecSub(void *, const void *, const void *);
extern void vec_scale_to_length(void *, const void *, float);
extern void FastVecCross(void *, const void *, const void *);
extern void FastVecScale(void *, const void *, float);
extern void transform_vector(void *, const void *, const void *);
extern void gfx_world_to_screen_unit(void *, float *, float *);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float math_ease_out_quad(float);
extern float FastAddRotations(float, float);
extern void draw_world_quad(void *, void *, int);
extern char g_camera_l00_position[];
extern int g_ball_gs_flag_a __attribute__((sda));
extern int g_ball_gs_flag_b __attribute__((sda));
extern int g_ball_gs_flag_c __attribute__((sda));
extern int g_ball_gs_flag_d __attribute__((sda));
extern int g_ball_gs_flag_e __attribute__((sda));
extern int g_ball_texture_id __attribute__((sda));
extern unsigned int g_ball_color __attribute__((sda));
extern float g_wobbling_ball_duration __attribute__((sda));
extern short g_wobbling_ball_face_indices[][4][2];
extern RenderVec g_wobbling_ball_vertices[];
extern float g_wobbling_ball_angles[][2];

/* Draws a wobbling 3D ball made of 48 textured faces around the object, facing the camera. The wobble shrinks as the object grows. */
void gfx_draw_wobbling_ball(char *object)
{
    RenderPacket packet;
    RenderVec matrix[4];
    RenderVector up;
    char *vars;
    int face, corner, index, vtx;
    long long flags;
    float *texU, *texV, *uvStart;
    float delta, scale, cosValue, sinValue;

    vars = *(char **)(object + 0x68);
    up.word = 0;
    up.v[2] = 1.0f;
    packet.tag[1] = GetEffectTextureDescriptor(g_ball_texture_id);
    packet.tag[2] = 0xFF9000000260LL;
    flags = (long long)g_ball_gs_flag_a;
    flags |= (long long)g_ball_gs_flag_b << 2;
    flags |= (long long)g_ball_gs_flag_c << 4;
    flags |= (long long)g_ball_gs_flag_d << 6;
    flags |= (long long)g_ball_gs_flag_e << 32;
    packet.tag[3] = flags;
    packet.tag[0] = 0;
    FastVecSub(&matrix[0], g_camera_l00_position, object + 0x10);
    vec_scale_to_length(&matrix[0], &matrix[0], 1.0f);
    FastVecCross(&matrix[1], &matrix[0], &up);
    vec_scale_to_length(&matrix[1], &matrix[1], 1.0f);
    FastVecCross(&matrix[2], &matrix[1], &matrix[0]);
    matrix[3].x = *(float *)(object + 0x10);
    matrix[3].y = *(float *)(object + 0x14);
    matrix[3].z = *(float *)(object + 0x18);
    matrix[3].w = 1.0f;
    packet.color[3] = g_ball_color;
    packet.color[2] = g_ball_color;
    packet.color[1] = g_ball_color;
    packet.color[0] = g_ball_color;
    uvStart = &packet.uv[0][0];
    for (face = 0; face < 48; face++) {
        texV = &packet.uv[0][1];
        texU = uvStart;
        for (corner = 0; corner < 4; corner++) {
            vtx = g_wobbling_ball_face_indices[face][corner][0];
            index = g_wobbling_ball_face_indices[face][corner][1];
            FastVecScale(&packet.vertex[corner], &g_wobbling_ball_vertices[vtx], *(float *)(vars + 0x24) * 2.0f);
            transform_vector(&packet.vertex[corner], &packet.vertex[corner], matrix);
            gfx_world_to_screen_unit(&packet.vertex[corner], &packet.uv[corner][0], &packet.uv[corner][1]);
            cosValue = math_fast_sin_or_cos_a(g_wobbling_ball_angles[index][0]);
            delta = cosValue * math_ease_out_quad((1.0f - *(float *)(vars + 0x24) / g_wobbling_ball_duration) * 0.0125f);
            *texU += delta;
            sinValue = math_fast_sin_or_cos_b(g_wobbling_ball_angles[index][0]);
            scale = math_ease_out_quad((1.0f - *(float *)(vars + 0x24) / g_wobbling_ball_duration) * 0.0125f);
            delta = -sinValue;
            delta *= scale;
            *texV += delta;
            if (*texU > 1.0f) *texU = 1.0f;
            else if (*texU < 0.0f) *texU = 0.0f;
            if (*texV > 1.0f) *texV = 1.0f;
            else if (*texV < 0.0f) *texV = 0.0f;
            texV += 2;
            texU += 2;
        }
        draw_world_quad(&packet, 0, 0);
    }
    for (face = 0; face < 98; face++)
        g_wobbling_ball_angles[face][0] = FastAddRotations(g_wobbling_ball_angles[face][0], g_wobbling_ball_angles[face][1]);
}

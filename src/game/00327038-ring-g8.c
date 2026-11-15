#include "include_asm.h"
#include "names.h"

/* func_00327D50 is a unit of its own: it reads small data (-G8), and retail
   reloads its 16-byte clear as one register (the compiler's default since
   ti_one_gpr.py). func_00327D08 in 00327038-g8.c calls it. */

typedef unsigned int RenderQuad __attribute__((mode(TI)));
typedef union { RenderQuad word; float v[4]; } RenderVector;
typedef struct { float x, y, z, w; } RenderVec __attribute__((aligned(16)));

/* The 144-byte quad packet func_00280B90 draws: four vertices, their colours,
   their UVs and four GS words. */
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
extern RenderVec g_camera_eye_state;
extern int D_001B01B4 __attribute__((sda));
extern int D_001B01B8 __attribute__((sda));
extern int D_001B01BC __attribute__((sda));
extern int D_001B01C0 __attribute__((sda));
extern int D_001B01C4 __attribute__((sda));
extern int D_001B01C8 __attribute__((sda));
extern unsigned int D_001B01CC __attribute__((sda));
extern float D_001B00F4 __attribute__((sda));
/* 48 quads of a flat ring of 98 vertices: per corner a vertex index and an
   index into the angle table, which holds an angle and its step. */
extern short D_0026A6A0[][4][2];
extern RenderVec D_0026A0A0[];
extern float D_0022AC90[][2];

/* Draws the object's ring facing the camera (D_001B5340), scaled by its
   state's size, with each corner's UV taken from its screen position and
   pushed along a rotating angle; the push weakens as the size nears
   D_001B00F4. Then advances every angle. */
void gfx_draw_distortion_ring(char *object)
{
    RenderPacket packet;
    RenderVec matrix[4];
    RenderVector up;
    char *state;
    int face, corner, index, vtx;
    long long flags;
    float *u, *v, *uv;
    float delta, scale, c, s;

    state = *(char **)(object + 0x68);
    up.word = 0;
    up.v[2] = 1.0f;
    packet.tag[1] = GetEffectTextureDescriptor(D_001B01C8);
    packet.tag[2] = 0xFF9000000260LL;
    flags = (long long)D_001B01B4;
    flags |= (long long)D_001B01B8 << 2;
    flags |= (long long)D_001B01BC << 4;
    flags |= (long long)D_001B01C0 << 6;
    flags |= (long long)D_001B01C4 << 32;
    packet.tag[3] = flags;
    packet.tag[0] = 0;
    FastVecSub(&matrix[0], &g_camera_eye_state, object + 0x10);
    vec_scale_to_length(&matrix[0], &matrix[0], 1.0f);
    FastVecCross(&matrix[1], &matrix[0], &up);
    vec_scale_to_length(&matrix[1], &matrix[1], 1.0f);
    FastVecCross(&matrix[2], &matrix[1], &matrix[0]);
    matrix[3].x = *(float *)(object + 0x10);
    matrix[3].y = *(float *)(object + 0x14);
    matrix[3].z = *(float *)(object + 0x18);
    matrix[3].w = 1.0f;
    packet.color[3] = D_001B01CC;
    packet.color[2] = D_001B01CC;
    packet.color[1] = D_001B01CC;
    packet.color[0] = D_001B01CC;
    uv = &packet.uv[0][0];
    for (face = 0; face < 48; face++) {
        v = &packet.uv[0][1];
        u = uv;
        for (corner = 0; corner < 4; corner++) {
            vtx = D_0026A6A0[face][corner][0];
            index = D_0026A6A0[face][corner][1];
            FastVecScale(&packet.vertex[corner], &D_0026A0A0[vtx], *(float *)(state + 0x24) * 2.0f);
            transform_vector(&packet.vertex[corner], &packet.vertex[corner], matrix);
            gfx_world_to_screen_unit(&packet.vertex[corner], &packet.uv[corner][0], &packet.uv[corner][1]);
            c = math_fast_sin_or_cos_a(D_0022AC90[index][0]);
            delta = c * math_ease_out_quad((1.0f - *(float *)(state + 0x24) / D_001B00F4) * 0.0125f);
            *u += delta;
            s = math_fast_sin_or_cos_b(D_0022AC90[index][0]);
            scale = math_ease_out_quad((1.0f - *(float *)(state + 0x24) / D_001B00F4) * 0.0125f);
            delta = -s;
            delta *= scale;
            *v += delta;
            if (*u > 1.0f) *u = 1.0f;
            else if (*u < 0.0f) *u = 0.0f;
            if (*v > 1.0f) *v = 1.0f;
            else if (*v < 0.0f) *v = 0.0f;
            v += 2;
            u += 2;
        }
        draw_world_quad(&packet, 0, 0);
    }
    for (face = 0; face < 98; face++)
        D_0022AC90[face][0] = FastAddRotations(D_0022AC90[face][0], D_0022AC90[face][1]);
}

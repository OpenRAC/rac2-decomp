/* func_PAL_0032DB00, the PAL copy of func_0032C2E8: the same C. */
/* func_PAL_0032DB00: -G8 unit. The counter steps through an inline helper so PRE leaves the increment
 * alone, and the second loop's table base uses the _1 alias so its %hi stays out of PRE. The initial
 * values fix the order and bucket count of the PRE expressions, which sets the two spill slots. */
#include "common.h"
#include <stddef.h>

typedef struct {
    float x;
    float y;
    float z;
    float w;
} RenderVec __attribute__((aligned(16)));

typedef struct { float u, v; } UVPair;
typedef struct { short vertex, uv; } FaceCorner;
typedef struct { FaceCorner corner[4]; } QuadFace;

typedef struct {
    RenderVec vertex[4];
    unsigned int color[4];
    UVPair uv[4];
    long long tag[4];
    RenderVec matrix[4];
} RenderPacket;

typedef struct {
    char pad_000[0xE0];
    RenderVec pos;
} HeroPosBlock;

extern void FastVecSub(void *, const void *, const void *);
extern void vec_scale_to_length(void *, const void *, float);
extern void FastVecCross(void *, const void *, const void *);
extern void FastVecScale(void *, const void *, float);
extern void transform_vector(void *, const void *, const void *);
extern void gfx_world_to_screen_unit(void *, float *, float *);
extern float math_fast_sin_or_cos_a(float);
extern float FastAddRotations(float, float);
extern void draw_world_quad(void *, void *, int);
extern void moby_get_facing_direction(void *, void *);

extern RenderVec g_camera_eye_state;
extern HeroPosBlock g_hero_state;
extern long long D_001B2810;
extern int D_001B059C __attribute__((sda));
extern int D_001B05A0 __attribute__((sda));
extern int D_001B05A4 __attribute__((sda));
extern int D_001B05A8 __attribute__((sda));
extern int D_001B05AC __attribute__((sda));
extern unsigned int D_001B05B0 __attribute__((sda));
extern QuadFace D_0026B210[];
extern RenderVec D_0026AA00[];
extern UVPair D_00235D00[];
extern UVPair D_00235D00_1[];

static inline void ClampUnit(float *value)
{
    if (*value > 1.0f) {
        *value = 1.0f;
    } else if (*value < 0.0f) {
        *value = 0.0f;
    }
}

static inline void NextFace(int *value)
{
    *value = *value + 1;
}

void func_PAL_0032DB00(char *object)
{
    RenderPacket packet;
    RenderVec up;
    RenderVec difference;
    char *state;
    int face;
    int corner = 0;
    FaceCorner *quad = 0;
    QuadFace *faces = 0;
    UVPair *phase;

    state = *(char **)(object + 0x68);
    packet.tag[1] = D_001B2810;
    packet.tag[2] = 0xFF9000000260LL;
    packet.tag[3] = (long long)D_001B059C;
    packet.tag[3] |= (long long)D_001B05A0 << 2;
    packet.tag[3] |= (long long)D_001B05A4 << 4;
    packet.tag[3] |= (long long)D_001B05A8 << 6;
    packet.tag[3] |= (long long)D_001B05AC << 32;
    packet.tag[0] = 0;

    moby_get_facing_direction(&g_hero_state.pos, &up);
    FastVecSub(&difference, &g_camera_eye_state, &g_hero_state.pos);
    vec_scale_to_length(&packet.matrix[0], &difference, 1.0f);
    FastVecCross(&packet.matrix[1], &packet.matrix[0], &up);
    vec_scale_to_length(&packet.matrix[1], &packet.matrix[1], 1.0f);
    FastVecCross(&packet.matrix[2], &packet.matrix[1], &packet.matrix[0]);
    vec_scale_to_length(&difference, &difference, 2.0f);
    packet.matrix[3].x = g_hero_state.pos.x + difference.x;
    packet.matrix[3].y = g_hero_state.pos.y + difference.y;
    packet.matrix[3].z = g_hero_state.pos.z + difference.z;
    packet.matrix[3].w = 1.0f;

    packet.color[0] = packet.color[1] = packet.color[2] = packet.color[3] = D_001B05B0;

    {
        char *u = (char *)&packet + offsetof(RenderPacket, uv);
        char *v;

        face = 0;
        do {
            faces = D_0026B210;
            quad = faces[face].corner;
            v = (char *)&packet + offsetof(RenderPacket, uv) + sizeof(float);
            u = (char *)&packet + offsetof(RenderPacket, uv);
            for (corner = 0; corner < 4; corner++) {
                int index = quad[corner].uv;

                FastVecScale(&packet.vertex[corner], &D_0026AA00[quad[corner].vertex], *(float *)(state + 0x14) * 4.0f);
                transform_vector(&packet.vertex[corner], &packet.vertex[corner], packet.matrix);
                gfx_world_to_screen_unit(&packet.vertex[corner], &packet.uv[corner].u, &packet.uv[corner].v);
                *(float *)u += math_fast_sin_or_cos_a(D_00235D00[index].u) * 0.01f;
                *(float *)v += math_fast_sin_or_cos_a(D_00235D00[index].v) * 0.02f;
                ClampUnit((float *)u);
                ClampUnit((float *)v);
                v += 8;
                u += 8;
            }
            draw_world_quad(&packet, 0, 0);
            NextFace(&face);
        } while (face < 127);
    }

    phase = D_00235D00_1;
    face = 136;
    do {
        phase->u = FastAddRotations(phase->u, 0.75398237f);
        phase->v = FastAddRotations(phase->v, 0.37699118f);
        phase++;
        face--;
    } while (face >= 0);
}

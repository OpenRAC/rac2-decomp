#include "include_asm.h"

#include "common.h"
typedef struct { float x, y, z, w; } RotorVector __attribute__((aligned(16)));
typedef struct { RotorVector rows[4]; } RotorMatrix;
typedef struct {
    RotorVector vertices[4];
    unsigned int colors[4];
    float uv[4][2];
    unsigned long zero, texture, textureState, flags;
} RotorQuad __attribute__((aligned(16)));
typedef struct {
    char reserved00[0x10];
    RotorVector position, direction;
} RotorStatePrefix;
extern int g_game_l00_mode MACRO_ADDR;
extern int g_frame_l00_counter MACRO_ADDR;
extern RotorVector g_spinning_quad_rotors[] MACRO_ADDR;
extern RotorVector D_L00_001AF7C0_gp[] SDATA(D_L00_001AF7C0) __attribute__((sda));
extern float square_root(float);
extern float mat_fast_helper_a(float, float);
extern float FastAddRotations(float, float);
extern float IntToFloat(int);
extern float math_fast_float_g(float);
extern void euler_to_matrix(void *, void *);
extern void multiply_matrix(void *, void *, void *);
extern unsigned long GetEffectTextureDescriptor(int);
extern void draw_world_quad(void *, void *, int);

/* Draws a pair of crossed, spinning textured quads at the object, turned along its direction. */
void gfx_draw_spinning_quad_pair_pal(unsigned char *object)
{
    RotorQuad quad;
    RotorMatrix model, phaseMatrix;
    RotorVector angles;
    RotorStatePrefix *state = *(RotorStatePrefix **)(object + 0x68);
    int i;
    float one, minus;
    if (g_game_l00_mode == 2)
        return;
    minus = -1.0f;
    one = 1.0f;
    for (i = 0; i < 2; i++) {
        int side = i & 1;
        float phase;
        unsigned long texture;
        float radius = square_root(state->direction.x * state->direction.x +
                                    state->direction.z * state->direction.z);
        angles.x = FastAddRotations(-mat_fast_helper_a(radius, state->direction.y), 1.5707963705062866f);
        angles.y = mat_fast_helper_a(state->direction.z, state->direction.x);
        angles.z = 0.0f;
        angles.w = 0.0f;
        D_L00_001AF7C0_gp[0].x = 0.0f;
        phase = math_fast_float_g(IntToFloat(g_frame_l00_counter % 150) * 0.041795027f);
        if (side)
            phase = -phase;
        g_spinning_quad_rotors[0].y = phase;
        g_spinning_quad_rotors[0].z = 0.0f;
        g_spinning_quad_rotors[0].w = 0.0f;
        euler_to_matrix(&phaseMatrix, &D_L00_001AF7C0_gp[0]);
        euler_to_matrix(&model, &angles);
        multiply_matrix(&model, &model, &phaseMatrix);
        qcopy(&model.rows[3], &state->position);
        quad.colors[0] = 0x80808080U;
        quad.colors[1] = 0x80808080U;
        quad.colors[2] = 0x80808080U;
        quad.colors[3] = 0x80808080U;
        texture = GetEffectTextureDescriptor(side ? 18 : 17);
        quad.textureState = 0xFF9000000260UL;
        quad.texture = texture;
        quad.flags = 0x8000000048UL;
        quad.zero = 0;
        quad.vertices[0].x = minus; quad.vertices[0].y = 0.0f;
        quad.vertices[0].z = one; quad.vertices[0].w = one;
        quad.vertices[1].x = one; quad.vertices[1].y = 0.0f;
        quad.vertices[1].z = one; quad.vertices[1].w = one;
        quad.vertices[2].x = minus; quad.vertices[2].y = 0.0f;
        quad.vertices[2].z = minus; quad.vertices[2].w = one;
        quad.vertices[3].x = one; quad.vertices[3].y = 0.0f;
        quad.vertices[3].z = minus; quad.vertices[3].w = one;
        quad.uv[0][0] = 0.0f; quad.uv[0][1] = one;
        quad.uv[1][0] = one; quad.uv[1][1] = one;
        quad.uv[2][0] = 0.0f; quad.uv[2][1] = 0.0f;
        quad.uv[3][0] = one; quad.uv[3][1] = 0.0f;
        draw_world_quad(&quad, &model, 1);
    }
}


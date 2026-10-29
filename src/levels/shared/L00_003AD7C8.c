/* Quad layout and rendering idiom checked against current RAC1
 * draw_offset_textured_effect_quad, moby_path_and_manipulators.c at 8bbc6b38
 * (GPL-3.0). RAC2 angle/state behavior is reconstructed independently.
 * The renderer reads a complete 0x90-byte packet, so its vertices, colors,
 * UVs and four 64-bit states belong to one fully initialized C object. */
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
extern int D_L00_001A8F00 MACRO_ADDR;
extern int D_L00_001B19C8 MACRO_ADDR;
/* Four measured Euler lanes; both externally owned views remain unbounded.
 * Retail writes X and passes the full vector through GP, Y/Z/W absolutely. */
extern RotorVector D_L00_001AF7C0[] MACRO_ADDR;
extern RotorVector D_L00_001AF7C0_gp[] SDATA(D_L00_001AF7C0) __attribute__((sda));
extern float func_00282C10(float);
extern float func_00283248(float, float);
extern float func_00283B98(float, float);
extern float func_00283CE0(int);
extern float func_00283C28(float);
extern void func_00283410(void *, void *);
extern void func_00283788(void *, void *, void *);
extern unsigned long func_0027C878(int);
extern void func_00280B90(void *, void *, int);

void func_L00_003AD7C8(unsigned char *object)
{
    RotorQuad quad;
    RotorMatrix model, phaseMatrix;
    RotorVector angles;
    RotorStatePrefix *state = *(RotorStatePrefix **)(object + 0x68);
    int i;
    float one, minus;
    if (D_L00_001A8F00 == 2)
        return;
    minus = -1.0f;
    one = 1.0f;
    for (i = 0; i < 2; i++) {
        int side = i & 1;
        float phase;
        unsigned long texture;
        float radius = func_00282C10(state->direction.x * state->direction.x +
                                    state->direction.z * state->direction.z);
        angles.x = func_00283B98(-func_00283248(radius, state->direction.y), 1.5707963705062866f);
        angles.y = func_00283248(state->direction.z, state->direction.x);
        angles.z = 0.0f;
        angles.w = 0.0f;
        D_L00_001AF7C0_gp[0].x = 0.0f;
        phase = func_00283C28(func_00283CE0(D_L00_001B19C8 % 180) * 0.03490659f);
        if (side)
            phase = -phase;
        D_L00_001AF7C0[0].y = phase;
        D_L00_001AF7C0[0].z = 0.0f;
        D_L00_001AF7C0[0].w = 0.0f;
        func_00283410(&phaseMatrix, &D_L00_001AF7C0_gp[0]);
        func_00283410(&model, &angles);
        func_00283788(&model, &model, &phaseMatrix);
        qcopy(&model.rows[3], &state->position);
        quad.colors[0] = 0x80808080U;
        quad.colors[1] = 0x80808080U;
        quad.colors[2] = 0x80808080U;
        quad.colors[3] = 0x80808080U;
        texture = func_0027C878(side ? 18 : 17);
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
        func_00280B90(&quad, &model, 1);
    }
}

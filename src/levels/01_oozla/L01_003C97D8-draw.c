#include "common.h"
extern unsigned long func_0027C878(int);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern int func_002AAE98(float, float, float, float);
extern float func_00283CC8(void *, float);
extern float func_00283198(float);
extern float func_002A7798(float);
extern int func_00283CF0(float);
extern void func_00280B90(void *, int, int);

typedef struct {
    float pos[4][4];
    unsigned int color[4];
    float uv[4][2];
    unsigned long reserved, texture, state, primitive;
} L01_003C97D8_QUAD;

/* Draws the glowing scrolling ribbon strips of the moby in five layers. */
void func_L01_003C97D8(char *moby)
{
    L01_003C97D8_QUAD quad;
    float origin[4], step[4], center[4], width[4], offset[4];
    float scratch;
    char *vars = *(char **)(moby + 0x68);
    float phase, scrollV, t, doubleScale, scale;
    float stepScale = 2.0f;
    float increment;
    quad.texture = GetEffectTextureDescriptor(*(int *)(vars + 0x78) + 63);
    quad.state = 0xFF9000000260UL;
    quad.primitive = 0x8000000044UL;
    quad.reserved = 0;
    scale = *(float *)(moby + 0x2C) / *(float *)(*(char **)(moby + 0x24) + 0x24);
    *(float *)(vars + 0x74) -= (*(float *)(vars + 0x68) * 0.016666668f) / stepScale;
    qzero_nc(origin);
    if (*(int *)(vars + 0x7C) == 1) vec_scale_to_length(origin, moby + 0xC0, scale * -10.0f);
    FastVecAdd(origin, origin, moby + 0x10);
    t = scale + scale;
    vec_scale_to_length(step, moby + 0xC0, stepScale * (float)*(int *)(vars + 0x7C));
    vec_scale_to_length(width, moby + 0xD0, scale * -2.0f);
    vec_scale_to_length(offset, moby + 0xD0, t * 0.8f);
    doubleScale = t;
    increment = 0.2f;
    {
        int i;
        for (i = 0; i < 5; i++) {
            scrollV = 0.0f;
            switch (i) {
            case 0:
                origin[2] += 0.02f;
                qcopy(center, origin);
                quad.color[2] = quad.color[3] = PackColorFloatsToWord(0.25f, 1.0f, 0.5f, 0.0f);
                phase = SplitFloatFraction(&scratch, *(float *)(vars + 0x74));
                scrollV = phase;
                break;
            case 1:
                qcopy(center, origin);
                quad.color[2] = quad.color[3] = PackColorFloatsToWord(0.25f, 0.5f, 1.0f, 0.0f);
                scrollV = SplitFloatFraction(&scratch, *(float *)(vars + 0x74) + 0.5f);
                break;
            case 2:
                origin[2] += 0.02f;
                qcopy(center, origin);
                quad.color[2] = quad.color[3] = PackColorFloatsToWord(1.0f, 0.0f, 0.0f, 0.0f);
                vec_scale_to_length(width, width, doubleScale * 0.2f);
                stepScale *= 0.4f;
                increment *= 0.4f;
                vec_scale_to_length(step, moby + 0xC0, stepScale * (float)*(int *)(vars + 0x7C));
                scrollV = SplitFloatFraction(&scratch, *(float *)(vars + 0x74) * 3.0f);
                break;
            case 3:
                scrollV = SplitFloatFraction(&scratch, *(float *)(vars + 0x74) * 3.5f);
                quad.color[2] = quad.color[3] = PackColorFloatsToWord(1.0f, 1.0f, 1.0f, 0.0f);
                FastVecAdd(center, origin, offset);
                break;
            case 4:
                FastVecSub(center, origin, offset);
                break;
            }
            FastVecSub(quad.pos[2], center, width);
            t = increment;
            FastVecAdd(quad.pos[3], center, width);
            FastVecAdd(center, center, step);
            quad.uv[2][0] = quad.uv[0][0] = 0.0f;
            quad.uv[3][0] = quad.uv[1][0] = 1.0f;
            quad.uv[1][1] = quad.uv[0][1] = scrollV;
            quad.uv[3][1] = quad.uv[2][1] = scrollV + 1.0f;
            while (t < 1.0f) {
                phase = EaseOutQuad(FastSinOrCosB(t * 3.1415927f));
                quad.color[0] = quad.color[1] = quad.color[2];
                {
                    int alpha = FloatToInt(phase * (*(float *)(vars + 0x70) * 102.4f));
                    quad.color[2] = quad.color[3] = (quad.color[0] & 0xFFFFFF) | (alpha << 24);
                }
                qcopy(quad.pos[0], quad.pos[2]);
                qcopy(quad.pos[1], quad.pos[3]);
                FastVecSub(quad.pos[2], center, width);
                FastVecAdd(quad.pos[3], center, width);
                FastVecAdd(center, center, step);
                draw_world_quad(&quad, 0, 1);
                t += increment;
            }
        }
    }
}

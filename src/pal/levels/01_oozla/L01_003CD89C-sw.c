#include "include_asm.h"

#include "common.h"
extern unsigned long GetEffectTextureDescriptor(int);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern int gfx_pack_color_floats(float, float, float, float);
extern float SplitFloatFraction(void *, float);
extern float math_fast_sin_or_cos_b(float);
extern float math_ease_out_quad(float);
extern int FloatToInt(float);
extern void draw_world_quad(void *, int, int);
typedef struct {
    float pos[4][4];
    unsigned int color[4];
    float uv[4][2];
    unsigned long reserved, texture, state, primitive;
} L01_003C97D8_QUAD;

void func_PAL_L01_003CD89C(char *obj)
{
    L01_003C97D8_QUAD q;
    float origin[4], step[4], center[4], width[4], offset[4];
    float scratch;
    char *s = *(char **)(obj + 0x68);
    float phase, v, t, doubleScale, scale;
    float stepScale = 2.0f;
    float increment;
    q.texture = GetEffectTextureDescriptor(*(int *)(s + 0x78) + 63);
    q.state = 0xFF9000000260UL;
    q.primitive = 0x8000000044UL;
    q.reserved = 0;
    scale = *(float *)(obj + 0x2C) / *(float *)(*(char **)(obj + 0x24) + 0x24);
    *(float *)(s + 0x74) -= (*(float *)(s + 0x68) * 0.020000001f) / stepScale;
    qzero_nc(origin);
    if (*(int *)(s + 0x7C) == 1) vec_scale_to_length(origin, obj + 0xC0, scale * -10.0f);
    FastVecAdd(origin, origin, obj + 0x10);
    t = scale + scale;
    vec_scale_to_length(step, obj + 0xC0, stepScale * (float)*(int *)(s + 0x7C));
    vec_scale_to_length(width, obj + 0xD0, scale * -2.0f);
    vec_scale_to_length(offset, obj + 0xD0, t * 0.8f);
    doubleScale = t;
    increment = 0.2f;
    {
        int i;
        for (i = 0; i < 5; i++) {
            v = 0.0f;
            switch (i) {
            case 0:
                origin[2] += 0.02f;
                qcopy(center, origin);
                q.color[2] = q.color[3] = gfx_pack_color_floats(0.25f, 1.0f, 0.5f, 0.0f);
                phase = SplitFloatFraction(&scratch, *(float *)(s + 0x74));
                v = phase;
                break;
            case 1:
                qcopy(center, origin);
                q.color[2] = q.color[3] = gfx_pack_color_floats(0.25f, 0.5f, 1.0f, 0.0f);
                v = SplitFloatFraction(&scratch, *(float *)(s + 0x74) + 0.5f);
                break;
            case 2:
                origin[2] += 0.02f;
                qcopy(center, origin);
                q.color[2] = q.color[3] = gfx_pack_color_floats(1.0f, 0.0f, 0.0f, 0.0f);
                vec_scale_to_length(width, width, doubleScale * 0.2f);
                stepScale *= 0.4f;
                increment *= 0.4f;
                vec_scale_to_length(step, obj + 0xC0, stepScale * (float)*(int *)(s + 0x7C));
                v = SplitFloatFraction(&scratch, *(float *)(s + 0x74) * 3.0f);
                break;
            case 3:
                v = SplitFloatFraction(&scratch, *(float *)(s + 0x74) * 3.5f);
                q.color[2] = q.color[3] = gfx_pack_color_floats(1.0f, 1.0f, 1.0f, 0.0f);
                FastVecAdd(center, origin, offset);
                break;
            case 4:
                FastVecSub(center, origin, offset);
                break;
            }
            FastVecSub(q.pos[2], center, width);
            t = increment;
            FastVecAdd(q.pos[3], center, width);
            FastVecAdd(center, center, step);
            q.uv[2][0] = q.uv[0][0] = 0.0f;
            q.uv[3][0] = q.uv[1][0] = 1.0f;
            q.uv[1][1] = q.uv[0][1] = v;
            q.uv[3][1] = q.uv[2][1] = v + 1.0f;
            while (t < 1.0f) {
                phase = math_ease_out_quad(math_fast_sin_or_cos_b(t * 3.1415927f));
                q.color[0] = q.color[1] = q.color[2];
                {
                    int alpha = FloatToInt(phase * (*(float *)(s + 0x70) * 102.4f));
                    q.color[2] = q.color[3] = (q.color[0] & 0xFFFFFF) | (alpha << 24);
                }
                qcopy(q.pos[0], q.pos[2]);
                qcopy(q.pos[1], q.pos[3]);
                FastVecSub(q.pos[2], center, width);
                FastVecAdd(q.pos[3], center, width);
                FastVecAdd(center, center, step);
                draw_world_quad(&q, 0, 1);
                t += increment;
            }
        }
    }
}

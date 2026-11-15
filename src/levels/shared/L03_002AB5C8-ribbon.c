#include "common.h"

typedef struct { float x, y, z, w; } __attribute__((aligned(16))) RibbonVector;
typedef struct { RibbonVector vertices[4]; int colors[4]; float uv[8]; unsigned long long flags; unsigned long long texture, alpha, test; } RibbonQuad;
extern void func_L03_0038B390(unsigned char *, int, int, int);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DF0(void *);
extern float func_00282C48(float);
extern int func_00283D38(float, int, int);
extern float func_002AA140(float, float, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00280B90(void *, int, int);
extern void func_002FC560(int, unsigned long long);
extern RibbonVector D_L03_00237F50;
extern RibbonVector D_L03_001B9980;

/* Draws a glowing ribbon through a list of points: a bright inner strip with a wider glow, brighter where a pulse passes. */
void func_L03_0038AB30(unsigned char *object, RibbonVector *points, int count,
                      int colorA, int colorB, int glowA, int glowB,
                      float innerA, float innerB, float outerA, float outerB, float extension) {
    unsigned char *state = *(unsigned char **)(object + 0x68);
    RibbonVector view;
    RibbonQuad outer, inner;
    RibbonVector direction, side, origin, offset;
    float phase = 0.0f;
    float startBlend, endBlend, delta, distance, width, length;
    float startInner, endInner, startOuter, endOuter;
    int startColor, endColor, startGlow, endGlow;
    int i, j;
    float *uv;
    InitEffectRecord_L03((unsigned char *)&inner, *(int *)(state + 0x9C), 1, colorA);
    inner.flags = 0;
    for (uv = inner.uv, j = 3; j >= 0; j--, uv += 2)
        *uv += *(float *)(state + 0x84);
    InitEffectRecord_L03((unsigned char *)&outer, *(int *)(state + 0x80), 1, glowA);
    outer.flags = 0;
    qcopy(&origin, object + 0x10);
    origin.z += 1.1f;
    if (object[0x20] == 3) {
        float phaseWidth = *(float *)(state + 0xCC);
        phase = (phaseWidth + phaseWidth + 1.0f) * (1.0f - (float)*(int *)(state + 0x24) / (float)*(int *)(state + 0x1C)) - phaseWidth;
        if (1.0f - phaseWidth < phase && (*(int *)(state + 0x3C) & 2)) {
            vec_scale_to_length(&offset, &D_L03_00237F50, *(float *)(state + 0xD0));
            FastVecAdd(object + 0x10, state, &offset);
        }
    }
    for (i = 0; i < count - 1; i++) {
        startBlend = 0.0f;
        endBlend = 0.0f;
        if (object[0x20] == 3) {
            FastVecSub(&offset, &origin, &points[i]);
            distance = FastVecLength(&offset) * 0.9090909f;
            delta = phase - distance;
            if (FloatAbs(delta) < *(float *)(state + 0xCC))
                startBlend = 1.0f - FloatAbs(delta) / *(float *)(state + 0xCC);
            FastVecSub(&offset, &origin, &points[i + 1]);
            distance = FastVecLength(&offset) * 0.9090909f;
            delta = phase - distance;
            if (FloatAbs(delta) < *(float *)(state + 0xCC))
                endBlend = 1.0f - FloatAbs(delta) / *(float *)(state + 0xCC);
        } else if (object[0x20] == 2) {
            FastVecSub(&offset, &origin, &points[i]);
            distance = FastVecLength(&offset) * 0.9090909f;
            if (distance < *(float *)(state + 0xCC))
                startBlend = (1.0f - distance / *(float *)(state + 0xCC)) *
                             (1.0f - (float)*(int *)(state + 0x24) / (float)*(int *)(state + 0x18));
            FastVecSub(&offset, &origin, &points[i + 1]);
            distance = FastVecLength(&offset) * 0.9090909f;
            if (distance < *(float *)(state + 0xCC))
                endBlend = 1.0f - distance / *(float *)(state + 0xCC);
        }
        width = 1.0f;
        startColor = FastTweenColor(startBlend, colorA, colorB);
        startGlow = FastTweenColor(startBlend, glowA, glowB);
        startInner = LerpFloat_002AA140(innerA, innerB, startBlend);
        startOuter = LerpFloat_002AA140(outerA, outerB, startBlend);
        endColor = FastTweenColor(endBlend, colorA, colorB);
        endGlow = FastTweenColor(endBlend, glowA, glowB);
        endInner = LerpFloat_002AA140(innerA, innerB, endBlend);
        endOuter = LerpFloat_002AA140(outerA, outerB, endBlend);
        if (*(int *)(state + 0x3C) & 4) {
            float reach;
            FastVecSub(&direction, &points[i], &origin);
            reach = FastVecLength(&direction);
            if (reach < *(float *)(state + 0xB0))
                width = *(float *)(state + 0xAC) * (1.0f - reach / *(float *)(state + 0xB0)) + 1.0f;
        }
        FastVecSub(&view, &points[i], &D_L03_001B9980);
        FastVecSub(&direction, &points[i + 1], &points[i]);
        length = FastVecLength(&direction);
        FastVecCross(&side, &direction, &view);
        inner.colors[0] = inner.colors[1] = inner.colors[2] = inner.colors[3] = startColor;
        vec_scale_to_length(&side, &side, width * startInner * length);
        FastVecAdd(&inner.vertices[0], &points[i], &side);
        FastVecSub(&inner.vertices[1], &points[i], &side);
        inner.colors[0] = inner.colors[1] = inner.colors[2] = inner.colors[3] = endColor;
        vec_scale_to_length(&side, &side, width * endInner * length);
        FastVecAdd(&inner.vertices[2], &points[i + 1], &side);
        FastVecSub(&inner.vertices[3], &points[i + 1], &side);
        draw_world_quad(&inner, 0, 0);
        outer.colors[0] = outer.colors[1] = outer.colors[2] = outer.colors[3] = startGlow;
        vec_scale_to_length(&side, &side, width * startOuter * length);
        FastVecAdd(&outer.vertices[0], &points[i], &side);
        FastVecSub(&outer.vertices[1], &points[i], &side);
        outer.colors[0] = outer.colors[1] = outer.colors[2] = outer.colors[3] = endGlow;
        vec_scale_to_length(&side, &side, width * endOuter * length);
        FastVecAdd(&outer.vertices[2], &points[i + 1], &side);
        FastVecSub(&outer.vertices[3], &points[i + 1], &side);
        FastVecScale(&direction, &direction, extension);
        FastVecSub(&outer.vertices[0], &outer.vertices[0], &direction);
        FastVecSub(&outer.vertices[1], &outer.vertices[1], &direction);
        FastVecAdd(&outer.vertices[2], &outer.vertices[2], &direction);
        FastVecAdd(&outer.vertices[3], &outer.vertices[3], &direction);
        draw_world_quad(&outer, 0, 0);
    }
    VU1_addGSregister(0x47, 0x5360B);
}

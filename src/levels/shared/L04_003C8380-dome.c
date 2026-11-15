#include "common.h"

/* func_L04_003FBEF8 has a unit of its own because it needs -g: retail pads its first
   division (lo's div.s) against the statement's line label, see the div.s floor in
   docs/build/compiler-notes.md. */

typedef int QuadWord __attribute__((mode(TI)));

/* The dome's state (L04_C678Vars in L04_003C8380.c): a height per band segment, then the
   radius, the owner, the fade timer and the age the radius and heights are scaled by. */
typedef struct {
    float heights[28];
    float radius;
    void *owner;
    int timer;
    float age;
} L04_DomeVars;

extern int D_L04_001B2008 MACRO_ADDR;
extern unsigned long func_0027C878(int);
extern void func_00280B90(void *, void *, int);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00283410(void *, void *);
extern float func_00283C28(float);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern float func_00283D00(float, float);
extern unsigned int func_00283D38(unsigned int, unsigned int, float);
extern float func_002A7878(float, float);
extern void func_002AF000(void *, float, float, float);

/* Draws the shield dome: ten rings of sixteen quads over the upper sphere, fading in at the
   seam, then three rings of a jagged band of twenty-eight quads around its base. */
void func_L04_003FBEF8(unsigned char *moby)
{
    struct {
        float vertices[4][4];
        unsigned int colors[4];
        float uv[8];
        unsigned long packet[4];
    } quad;
    float matrix[16];
    union { QuadWord q; float f[4]; } rotation;
    L04_DomeVars *vars = *(L04_DomeVars **)(moby + 0x68);
    float radius = vars->radius * vars->age;
    float phase = fast_fmod(IntToFloat(D_L04_001B2008), 30.0f) * (1.0f / 30.0f);
    int i, j, k, l;

    rotation.q = *(QuadWord *)(moby + 0xF0);
    rotation.f[0] = 0;
    euler_to_matrix(matrix, &rotation);
    *(QuadWord *)(matrix + 12) = *(QuadWord *)(moby + 0x10);
    quad.packet[1] = GetEffectTextureDescriptor(21);
    quad.packet[2] = 0xFF9000000260UL;
    quad.packet[3] = 0x8000000048UL;
    quad.packet[0] = 0;
    for (i = 0; i < 10; i++) {
        float lo = IntToFloat(i) * 0.17453295f / IntToFloat(10) - 0.087266475f;
        float hi = IntToFloat(i + 1) * 0.17453295f / IntToFloat(10) - 0.087266475f;
        for (j = 0; j < 16; j++) {
            float left = FastFloatHelperG(IntToFloat(j) * 1.3962636f / IntToFloat(16)) - 0.6981318f;
            float right = FastFloatHelperG(IntToFloat(j + 1) * 1.3962636f / IntToFloat(16)) - 0.6981318f;
            float alpha, baseAlpha;
            int alpha0, alpha1;
            quad.uv[0] = phase + (FastSinOrCosA(left) + 1.0f) * 0.5f;
            quad.uv[2] = phase + (FastSinOrCosA(right) + 1.0f) * 0.5f;
            quad.uv[4] = phase + (FastSinOrCosA(left) + 1.0f) * 0.5f;
            quad.uv[6] = phase + (FastSinOrCosA(right) + 1.0f) * 0.5f;
            quad.uv[1] = (FastSinOrCosB(lo) + 1.0f) * 0.5f;
            quad.uv[3] = (FastSinOrCosB(lo) + 1.0f) * 0.5f;
            quad.uv[5] = (FastSinOrCosB(hi) + 1.0f) * 0.5f;
            quad.uv[7] = (FastSinOrCosB(hi) + 1.0f) * 0.5f;
            baseAlpha = IntToFloat(64);
            if (vars->timer) alpha = IntToFloat(vars->timer) * (baseAlpha * (1.0f / 15.0f));
            else alpha = baseAlpha;
            alpha0 = FloatToInt(alpha * FastSinOrCosB(IntToFloat(i) * 3.141593f / IntToFloat(10)));
            alpha1 = FloatToInt(alpha * FastSinOrCosB(IntToFloat(i + 1) * 3.141593f / IntToFloat(10)));
            quad.colors[0] = j ? ((unsigned)alpha0 << 24) | 0xA06060 : 0xA06060;
            quad.colors[1] = j != 15 ? ((unsigned)alpha0 << 24) | 0xA06060 : 0xA06060;
            quad.colors[2] = j ? ((unsigned)alpha1 << 24) | 0xA06060 : 0xA06060;
            quad.colors[3] = j != 15 ? ((unsigned)alpha1 << 24) | 0xA06060 : 0xA06060;
            BuildSphericalOffset(quad.vertices[0], radius, left, lo);
            BuildSphericalOffset(quad.vertices[1], radius, right, lo);
            BuildSphericalOffset(quad.vertices[2], radius, left, hi);
            BuildSphericalOffset(quad.vertices[3], radius, right, hi);
            quad.vertices[0][3] = 1.0f;
            quad.vertices[1][3] = 1.0f;
            quad.vertices[2][3] = 1.0f;
            quad.vertices[3][3] = 1.0f;
            draw_world_quad(&quad, matrix, 0);
        }
    }
    quad.packet[1] = GetEffectTextureDescriptor(14);
    for (k = 0; k < 3; k++) {
        float previousHeight = 0, previous = 0;
        for (l = 0; l < 28; l++) {
            float left = FastFloatHelperG(IntToFloat(l) * 0.04986656f) - 0.6981318f;
            float right = FastFloatHelperG(IntToFloat(l + 1) * 0.04986656f) - 0.6981318f;
            float next = RandomFloatRange(left, right);
            float alpha, height;
            unsigned int color;
            if (l == 0) previous = left;
            else if (l == 27) next = right;
            quad.uv[0] = IntToFloat(l) * (1.0f / 28.0f);
            quad.uv[2] = IntToFloat(l + 1) * (1.0f / 28.0f);
            quad.uv[4] = IntToFloat(l) * (1.0f / 28.0f);
            quad.uv[6] = IntToFloat(l + 1) * (1.0f / 28.0f);
            quad.uv[1] = 0;
            quad.uv[3] = 0;
            quad.uv[5] = 1;
            quad.uv[7] = 1;
            if (vars->timer) alpha = 1.0f - IntToFloat(vars->timer) * (1.0f / 15.0f);
            else alpha = 0;
            if (alpha < 0) alpha = 0;
            color = FastTweenColor(0x7FC04070, 0xFF0000, alpha);
            quad.colors[0] = quad.colors[1] = quad.colors[2] = quad.colors[3] = color;
            height = (vars->heights[l] * (RandomFloatRange(-1, 1) * 0.017453294f)) * vars->age;
            if (height > 0.069813184f) height = 0.069813184f;
            if (height < -0.069813184f) height = -0.069813184f;
            if (l == 0) previousHeight = 0;
            BuildSphericalOffset(quad.vertices[0], radius, previous, previousHeight);
            BuildSphericalOffset(quad.vertices[1], radius, next, height);
            BuildSphericalOffset(quad.vertices[2], radius, previous, previousHeight);
            BuildSphericalOffset(quad.vertices[3], radius, next, height);
            previousHeight = height;
            previous = next;
            quad.vertices[2][2] -= 0.15f;
            quad.vertices[3][2] -= 0.15f;
            quad.vertices[0][3] = 1.0f;
            quad.vertices[1][3] = 1.0f;
            quad.vertices[2][3] = 1.0f;
            quad.vertices[3][3] = 1.0f;
            draw_world_quad(&quad, matrix, 0);
        }
    }
}

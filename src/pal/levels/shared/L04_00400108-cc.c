/* func_PAL_L04_00400108, the PAL copy of func_L04_003FBEF8: the same C. */
#include "common.h"

/* func_PAL_L04_00400108 has a unit of its own because it needs -g: retail pads its first
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
void func_PAL_L04_00400108(unsigned char *m)
{
    struct {
        float vertices[4][4];
        unsigned int colors[4];
        float uv[8];
        unsigned long packet[4];
    } quad;
    float matrix[16];
    union { QuadWord q; float f[4]; } rotation;
    L04_DomeVars *p = *(L04_DomeVars **)(m + 0x68);
    float radius = p->radius * p->age;
    float phase = func_00283D00(func_00283CE0(D_L04_001B2008), 25.333334f) * (1.0f / 25.333334f);
    int i, j, k, l;

    rotation.q = *(QuadWord *)(m + 0xF0);
    rotation.f[0] = 0;
    func_00283410(matrix, &rotation);
    *(QuadWord *)(matrix + 12) = *(QuadWord *)(m + 0x10);
    quad.packet[1] = func_0027C878(21);
    quad.packet[2] = 0xFF9000000260UL;
    quad.packet[3] = 0x8000000048UL;
    quad.packet[0] = 0;
    for (i = 0; i < 10; i++) {
        float lo = func_00283CE0(i) * 0.17453295f / func_00283CE0(10) - 0.087266475f;
        float hi = func_00283CE0(i + 1) * 0.17453295f / func_00283CE0(10) - 0.087266475f;
        for (j = 0; j < 16; j++) {
            float left = func_00283C28(func_00283CE0(j) * 1.3962636f / func_00283CE0(16)) - 0.6981318f;
            float right = func_00283C28(func_00283CE0(j + 1) * 1.3962636f / func_00283CE0(16)) - 0.6981318f;
            float alpha, baseAlpha;
            int alpha0, alpha1;
            quad.uv[0] = phase + (func_00283180(left) + 1.0f) * 0.5f;
            quad.uv[2] = phase + (func_00283180(right) + 1.0f) * 0.5f;
            quad.uv[4] = phase + (func_00283180(left) + 1.0f) * 0.5f;
            quad.uv[6] = phase + (func_00283180(right) + 1.0f) * 0.5f;
            quad.uv[1] = (func_00283198(lo) + 1.0f) * 0.5f;
            quad.uv[3] = (func_00283198(lo) + 1.0f) * 0.5f;
            quad.uv[5] = (func_00283198(hi) + 1.0f) * 0.5f;
            quad.uv[7] = (func_00283198(hi) + 1.0f) * 0.5f;
            baseAlpha = func_00283CE0(64);
            if (p->timer) alpha = func_00283CE0(p->timer) * (baseAlpha * (1.0f / 15.0f));
            else alpha = baseAlpha;
            alpha0 = func_00283CF0(alpha * func_00283198(func_00283CE0(i) * 3.141593f / func_00283CE0(10)));
            alpha1 = func_00283CF0(alpha * func_00283198(func_00283CE0(i + 1) * 3.141593f / func_00283CE0(10)));
            quad.colors[0] = j ? ((unsigned)alpha0 << 24) | 0xA06060 : 0xA06060;
            quad.colors[1] = j != 15 ? ((unsigned)alpha0 << 24) | 0xA06060 : 0xA06060;
            quad.colors[2] = j ? ((unsigned)alpha1 << 24) | 0xA06060 : 0xA06060;
            quad.colors[3] = j != 15 ? ((unsigned)alpha1 << 24) | 0xA06060 : 0xA06060;
            func_002AF000(quad.vertices[0], radius, left, lo);
            func_002AF000(quad.vertices[1], radius, right, lo);
            func_002AF000(quad.vertices[2], radius, left, hi);
            func_002AF000(quad.vertices[3], radius, right, hi);
            quad.vertices[0][3] = 1.0f;
            quad.vertices[1][3] = 1.0f;
            quad.vertices[2][3] = 1.0f;
            quad.vertices[3][3] = 1.0f;
            func_00280B90(&quad, matrix, 0);
        }
    }
    quad.packet[1] = func_0027C878(14);
    for (k = 0; k < 3; k++) {
        float previousHeight = 0, previous = 0;
        for (l = 0; l < 28; l++) {
            float left = func_00283C28(func_00283CE0(l) * 0.04986656f) - 0.6981318f;
            float right = func_00283C28(func_00283CE0(l + 1) * 0.04986656f) - 0.6981318f;
            float next = func_002A7878(left, right);
            float alpha, height;
            unsigned int color;
            if (l == 0) previous = left;
            else if (l == 27) next = right;
            quad.uv[0] = func_00283CE0(l) * (1.0f / 28.0f);
            quad.uv[2] = func_00283CE0(l + 1) * (1.0f / 28.0f);
            quad.uv[4] = func_00283CE0(l) * (1.0f / 28.0f);
            quad.uv[6] = func_00283CE0(l + 1) * (1.0f / 28.0f);
            quad.uv[1] = 0;
            quad.uv[3] = 0;
            quad.uv[5] = 1;
            quad.uv[7] = 1;
            if (p->timer) alpha = 1.0f - func_00283CE0(p->timer) * (1.0f / 15.0f);
            else alpha = 0;
            if (alpha < 0) alpha = 0;
            color = func_00283D38(0x7FC04070, 0xFF0000, alpha);
            quad.colors[0] = quad.colors[1] = quad.colors[2] = quad.colors[3] = color;
            height = (p->heights[l] * (func_002A7878(-1, 1) * 0.017453294f)) * p->age;
            if (height > 0.069813184f) height = 0.069813184f;
            if (height < -0.069813184f) height = -0.069813184f;
            if (l == 0) previousHeight = 0;
            func_002AF000(quad.vertices[0], radius, previous, previousHeight);
            func_002AF000(quad.vertices[1], radius, next, height);
            func_002AF000(quad.vertices[2], radius, previous, previousHeight);
            func_002AF000(quad.vertices[3], radius, next, height);
            previousHeight = height;
            previous = next;
            quad.vertices[2][2] -= 0.15f;
            quad.vertices[3][2] -= 0.15f;
            quad.vertices[0][3] = 1.0f;
            quad.vertices[1][3] = 1.0f;
            quad.vertices[2][3] = 1.0f;
            quad.vertices[3][3] = 1.0f;
            func_00280B90(&quad, matrix, 0);
        }
    }
}

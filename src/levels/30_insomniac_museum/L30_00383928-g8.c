#include "common.h"

typedef struct {
    float position[4][4];
    unsigned int color[4];
    float uv[4][2];
    unsigned long flags, texture, blend, alpha;
} GridQuad;

extern int D_L30_001AEBC0 __attribute__((sda));
extern float D_L30_001AEBF0 __attribute__((sda));
extern int D_L30_001AEBF4 __attribute__((sda));
extern int D_L30_001AEBF8 __attribute__((sda));
extern int D_L30_001AEBFC __attribute__((sda));
extern int D_L30_001AEC00 __attribute__((sda));
extern int D_L30_001AEC04 __attribute__((sda));
extern float D_L30_00233A60[][24][24];
extern float D_L30_00235560[24][24][2];
extern float D_L30_00236760[24][24][2];
extern float D_L30_00237960[24][24][2];
extern unsigned char D_L30_00238B60[24][24];
extern unsigned long func_0027C878(int);
extern void func_L30_00383398(void *);
extern void func_002FC560(unsigned int, unsigned long);
extern void func_00280B90(void *, int, int);

/* Draw the 24-by-24 grid twice as quads: once with the coordinates in D_L30_00236760 and once,
   raised by D_L30_001AEBF0 and blended by the packed GS ALPHA value, with those in D_L30_00237960. */
void func_L30_00383928(char *obj)
{
    GridQuad q;
    unsigned int rgb;
    unsigned long tex0, tex1, alpha, alpha01, alpha012, alpha0123;
    int row, col;

    tex0 = GetEffectTextureDescriptor(0x47);
    tex1 = GetEffectTextureDescriptor(0x48);
    alpha01 = (unsigned long)D_L30_001AEBF8 | ((unsigned long)D_L30_001AEBFC << 2);
    alpha012 = alpha01 | ((unsigned long)D_L30_001AEC00 << 4);
    alpha0123 = alpha012 | ((unsigned long)D_L30_001AEC04 << 6);
    alpha = alpha0123 | ((unsigned long)D_L30_001AEBF4 << 32);
    q.blend = 0xFF9000000260UL;
    q.flags = 0;
    UpdateMuseumWaterGridOptics(obj + 0x10);
    VU1_addGSregister(0x47, 0x53001);
    q.alpha = 0x80000000A8UL;
    q.texture = tex1;
    row = 0;
    rgb = 0x808080;
    for (; row < 23; row++) {
        for (col = 0; col < 23; col++) {
            q.color[0] = (D_L30_00238B60[row][col] << 24) | rgb;
            q.position[0][0] = D_L30_00235560[row][col][0] + *(float *)(obj + 0x10);
            q.position[0][1] = D_L30_00235560[row][col][1] + *(float *)(obj + 0x14);
            q.position[0][2] = D_L30_00233A60[D_L30_001AEBC0][row][col] + *(float *)(obj + 0x18);
            q.position[0][3] = 1.0f;
            q.color[1] = (D_L30_00238B60[row + 1][col] << 24) | rgb;
            q.position[1][0] = D_L30_00235560[row + 1][col][0] + *(float *)(obj + 0x10);
            q.position[1][1] = D_L30_00235560[row + 1][col][1] + *(float *)(obj + 0x14);
            q.position[1][2] = D_L30_00233A60[D_L30_001AEBC0][row + 1][col] + *(float *)(obj + 0x18);
            q.position[1][3] = 1.0f;
            q.color[2] = (D_L30_00238B60[row][col + 1] << 24) | rgb;
            q.position[2][0] = D_L30_00235560[row][col + 1][0] + *(float *)(obj + 0x10);
            q.position[2][1] = D_L30_00235560[row][col + 1][1] + *(float *)(obj + 0x14);
            q.position[2][2] = D_L30_00233A60[D_L30_001AEBC0][row][col + 1] + *(float *)(obj + 0x18);
            q.position[2][3] = 1.0f;
            q.color[3] = (D_L30_00238B60[row + 1][col + 1] << 24) | rgb;
            q.position[3][0] = D_L30_00235560[row + 1][col + 1][0] + *(float *)(obj + 0x10);
            q.position[3][1] = D_L30_00235560[row + 1][col + 1][1] + *(float *)(obj + 0x14);
            q.position[3][2] = D_L30_00233A60[D_L30_001AEBC0][row + 1][col + 1] + *(float *)(obj + 0x18);
            q.position[3][3] = 1.0f;
            q.uv[0][0] = D_L30_00236760[row][col][0];
            q.uv[0][1] = D_L30_00236760[row][col][1];
            q.uv[1][0] = D_L30_00236760[row + 1][col][0];
            q.uv[1][1] = D_L30_00236760[row + 1][col][1];
            q.uv[2][0] = D_L30_00236760[row][col + 1][0];
            q.uv[2][1] = D_L30_00236760[row][col + 1][1];
            q.uv[3][0] = D_L30_00236760[row + 1][col + 1][0];
            q.uv[3][1] = D_L30_00236760[row + 1][col + 1][1];
            draw_world_quad(&q, 0, 0);
        }
    }
    VU1_addGSregister(0x47, 0x5360B);
    q.alpha = alpha;
    q.texture = tex0;
    for (row = 0; row < 23; row++) {
        for (col = 0; col < 23; col++) {
            q.color[0] = (D_L30_00238B60[row][col] << 24) | rgb;
            q.position[0][0] = D_L30_00235560[row][col][0] + *(float *)(obj + 0x10);
            q.position[0][1] = D_L30_00235560[row][col][1] + *(float *)(obj + 0x14);
            q.position[0][2] = D_L30_00233A60[D_L30_001AEBC0][row][col] + *(float *)(obj + 0x18) + D_L30_001AEBF0;
            q.position[0][3] = 1.0f;
            q.color[1] = (D_L30_00238B60[row + 1][col] << 24) | rgb;
            q.position[1][0] = D_L30_00235560[row + 1][col][0] + *(float *)(obj + 0x10);
            q.position[1][1] = D_L30_00235560[row + 1][col][1] + *(float *)(obj + 0x14);
            q.position[1][2] = D_L30_00233A60[D_L30_001AEBC0][row + 1][col] + *(float *)(obj + 0x18) + D_L30_001AEBF0;
            q.position[1][3] = 1.0f;
            q.color[2] = (D_L30_00238B60[row][col + 1] << 24) | rgb;
            q.position[2][0] = D_L30_00235560[row][col + 1][0] + *(float *)(obj + 0x10);
            q.position[2][1] = D_L30_00235560[row][col + 1][1] + *(float *)(obj + 0x14);
            q.position[2][2] = D_L30_00233A60[D_L30_001AEBC0][row][col + 1] + *(float *)(obj + 0x18) + D_L30_001AEBF0;
            q.position[2][3] = 1.0f;
            q.color[3] = (D_L30_00238B60[row + 1][col + 1] << 24) | rgb;
            q.position[3][0] = D_L30_00235560[row + 1][col + 1][0] + *(float *)(obj + 0x10);
            q.position[3][1] = D_L30_00235560[row + 1][col + 1][1] + *(float *)(obj + 0x14);
            q.position[3][2] = D_L30_00233A60[D_L30_001AEBC0][row + 1][col + 1] + *(float *)(obj + 0x18) + D_L30_001AEBF0;
            q.position[3][3] = 1.0f;
            q.uv[0][0] = D_L30_00237960[row][col][0];
            q.uv[0][1] = D_L30_00237960[row][col][1];
            q.uv[1][0] = D_L30_00237960[row + 1][col][0];
            q.uv[1][1] = D_L30_00237960[row + 1][col][1];
            q.uv[2][0] = D_L30_00237960[row][col + 1][0];
            q.uv[2][1] = D_L30_00237960[row][col + 1][1];
            q.uv[3][0] = D_L30_00237960[row + 1][col + 1][0];
            q.uv[3][1] = D_L30_00237960[row + 1][col + 1][1];
            draw_world_quad(&q, 0, 0);
        }
    }
}

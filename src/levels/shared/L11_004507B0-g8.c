#include "common.h"
struct EffectQuad { float position[4][4]; u32 color[4]; float uv[4][2]; u64 clear, texture, giftag, flags; };
extern float D_L11_001BA780[];
extern int D_L11_001B1CE4 __attribute__((sda));
extern u32 D_L11_001B1CE8 __attribute__((sda));
extern u32 D_L11_001B1CEC __attribute__((sda));
extern float D_L11_001B1CF0 __attribute__((sda));
extern float D_L11_001B1CF4 __attribute__((sda));
extern int D_L11_001B1CF8 __attribute__((sda));
extern int D_L11_001B1CFC __attribute__((sda));
extern float D_L11_001B1D00 __attribute__((sda));
extern void ref_L11_004507B0_00(char *);
extern long long func_0027C878(int);
extern float func_00283248(float, float);
extern float func_00282E80(char *, float *);
extern void func_00283410(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_L11_00450748(char *, float);
extern void func_00280B90(void *, void *, int);
extern void func_00282CC0(void *, void *, void *);
extern void func_00281EB8(void *, u32, int, int, float, float, float);

/* Draws one glowing sprite at a position, facing the camera, and adds light flares behind it. */
void func_L11_004507B0(void *position, u32 color, float size, int alpha, float roll, int texture, int flags, float offset, void *owner) {
    struct EffectQuad quad;
    float matrix[16], rotation[4], toward[4], light[4];
    char *object = owner;
    char *vars = *(char **)(object + 0x68);
    float *point = position;
    
    u32 packedColor;
    ref_L11_004507B0_00((char *)&quad);
    quad.texture = GetEffectTextureDescriptor(texture);
    quad.giftag = 0xFF9000000260ULL;
    quad.flags = ((u64)flags << 2) | 0x8000000040ULL;
    packedColor = color + (alpha << 24);
    quad.color[3] = packedColor;
    quad.color[2] = packedColor;
    quad.color[1] = packedColor;
    quad.color[0] = packedColor;
    quad.clear = 0;
    
    rotation[3] = 0.0f;
    rotation[2] = FastMatrixHelperA(D_L11_001BA780[0x50] - point[0], D_L11_001BA780[0x51] - point[1]);
    rotation[1] = -FastMatrixHelperA(vec_distance_xy(position, D_L11_001BA780 + 0x50), D_L11_001BA780[0x52] - point[2]);
    rotation[0] = roll;
    euler_to_matrix(matrix, rotation);
    FastVecSub(toward, D_L11_001BA780 + 0x50, position);
    vec_scale_to_length(toward, toward, offset);
    matrix[12] = point[0] + toward[0];
    matrix[13] = point[1] + toward[1];
    matrix[14] = point[2] + toward[2];
    matrix[15] = 1.0f;
    ScaleFourVectors_L11((char *)&quad, size);
    draw_world_quad(&quad, matrix, 0);
    if (D_L11_001B1CE4 == 0) {
        vec_scale_to_length(light, vars, D_L11_001B1D00);
        FastVecAdd(light, object + 0x10, light);
        DrawBillboardQuad_00281EB8(light, D_L11_001B1CE8, D_L11_001B1CF8, 1, D_L11_001B1CF0, 0.08f, 0.0f);
        vec_scale_to_length(light, vars, -0.03f);
        FastVecAdd(light, object + 0x10, light);
        DrawBillboardQuad_00281EB8(light, D_L11_001B1CEC, D_L11_001B1CFC, 1, D_L11_001B1CF4, 0.08f, 0.0f);
    }
}

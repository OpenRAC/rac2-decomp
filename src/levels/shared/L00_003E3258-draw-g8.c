#include "common.h"

typedef float RenderVec5BD8[4] __attribute__((aligned(16)));
typedef struct {
    RenderVec5BD8 vertices[4];
    int colors[4];
    float uv[4][2];
    unsigned long gs[4];
} Quad5BD8;
extern int D_L00_001B0600 __attribute__((sda));
extern int D_L00_001B0604 __attribute__((sda));
extern int D_L00_001B0608 __attribute__((sda));
extern int D_L00_001B060C __attribute__((sda));
extern int D_L00_001B0610 __attribute__((sda));
extern int D_L00_001B0614 __attribute__((sda));
extern int D_L00_001B0618 __attribute__((sda));
extern float D_L00_001B061C __attribute__((sda));
extern float D_L00_001B05D4 __attribute__((sda));
extern float D_L00_001B05D8 __attribute__((sda));
extern char *D_L00_001B2B50 __attribute__((sda));
extern int *D_L00_001B2B58 MACRO_ADDR;
extern short D_L00_002983B0[][4][2];
extern RenderVec5BD8 D_L00_002976D0[];
extern float D_L00_00299130[][2];
extern RenderVec5BD8 D_L00_001B8DC0;
extern unsigned long func_0027C878(int);
extern void func_00282C88(void *);
extern void func_00282D30(void *,void *,float);
extern void func_00283098(void *,void *,void *);
extern float func_00282E20(void *);
extern float ref_L00_003E5BD8_00(float);
extern void func_00282CC0(void *,void *,void *);
extern void func_00282CF0(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern void func_00282DD8(void *,void *,void *);
extern float func_00282DB0(void *,void *);
extern char * func_L00_003E6778(char *,int,float,float,void *);
extern void func_00280B90(void *,int,int);

/* Draws the large blast shell around the object as 215 quads, skipping the ones that face away from the camera. */
void func_L00_003E5BD8(char *object_)
{
    Quad5BD8 quad;
    RenderVec5BD8 matrix[3];
    RenderVec5BD8 normal, center, edge1, edge2;
    int p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15;
    char *object = object_;
    int index;
    char *data = *(char **)(object + 0x68);
    quad.gs[1] = GetEffectTextureDescriptor(D_L00_001B0614);
    quad.gs[3] = (unsigned long)D_L00_001B0600 | ((unsigned long)D_L00_001B0604 << 2);
    quad.gs[3] |= (unsigned long)D_L00_001B0608 << 4;
    quad.gs[3] |= (unsigned long)D_L00_001B060C << 6;
    quad.gs[3] |= (unsigned long)D_L00_001B0610 << 32;
    quad.gs[2] = 0xFF9000000260UL;
    quad.gs[0] = 0;
    quad.colors[0] = quad.colors[1] = quad.colors[2] = quad.colors[3] = D_L00_001B0618 + (*(int *)(data+28) << 24);
    ClearVector128(matrix[0]);
    ClearVector128(matrix[1]);
    ClearVector128(matrix[2]);
    matrix[0][0] = 1.0f;
    matrix[1][1] = 1.0f;
    matrix[2][2] = *(float *)(data+16)*0.865f;
    index=0;
    do {
        int i;
        for (i=0;i<4;i++) {
            int vertex_index = D_L00_002983B0[index][i][0];
            int uv_index = D_L00_002983B0[index][i][1];
            FastVecScale(quad.vertices[i],D_L00_002976D0[vertex_index],D_L00_001B061C);
            quad.uv[i][0] = D_L00_00299130[uv_index][0] + D_L00_001B05D4;
            quad.uv[i][1] = D_L00_00299130[uv_index][1] + D_L00_001B05D8;
            if (D_L00_002976D0[vertex_index][2] == -0.001052f)
                quad.colors[i] = D_L00_001B0618;
            else
                quad.colors[i] = D_L00_001B0618 | (*(int *)(data+28)<<24);
        }
        matrix_mul_vec3(quad.vertices[0],quad.vertices[0],matrix);
        matrix_mul_vec3(quad.vertices[1],quad.vertices[1],matrix);
        matrix_mul_vec3(quad.vertices[2],quad.vertices[2],matrix);
        matrix_mul_vec3(quad.vertices[3],quad.vertices[3],matrix);
        ClearVector128(center);
        for(i=0;i<4;i++) {
            quad.uv[i][0] -= quad.vertices[i][2]*0.125f;
            quad.vertices[i][0] *= ref_L00_003E5BD8_00(quad.vertices[i][2]) + 2.0f;
            quad.vertices[i][1] *= ref_L00_003E5BD8_00(quad.vertices[i][2]) + 2.0f;
            matrix_mul_vec3(quad.vertices[i],quad.vertices[i],object+192);
            quad.vertices[i][0] += *(float *)(object+16);
            quad.vertices[i][1] += *(float *)(object+20);
            quad.vertices[i][2] += *(float *)(object+24);
            FastVecAdd(center,center,quad.vertices[i]);
        }
        FastVecScale(center,center,0.25f);
        FastVecSub(normal,center,gCameraPosition_L00);
        vec_scale_to_length(normal,normal,1.0f);
        FastVecSub(edge1,quad.vertices[2],quad.vertices[0]);
        FastVecSub(edge2,quad.vertices[2],quad.vertices[1]);
        FastVecCross(center,edge1,edge2);
        vec_scale_to_length(center,center,1.0f);
        if(FastVecDot(normal,center)>0.0f)
            draw_world_quad(&quad,0,0);
    } while(++index<215);
}

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

void func_L00_003E5BD8(char *object_)
{
    Quad5BD8 q;
    RenderVec5BD8 matrix[3];
    RenderVec5BD8 normal, center, edge1, edge2;
    int p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15;
    char *object = object_;
    int index;
    char *data = *(char **)(object + 0x68);
    q.gs[1] = func_0027C878(D_L00_001B0614);
    q.gs[3] = (unsigned long)D_L00_001B0600 | ((unsigned long)D_L00_001B0604 << 2);
    q.gs[3] |= (unsigned long)D_L00_001B0608 << 4;
    q.gs[3] |= (unsigned long)D_L00_001B060C << 6;
    q.gs[3] |= (unsigned long)D_L00_001B0610 << 32;
    q.gs[2] = 0xFF9000000260UL;
    q.gs[0] = 0;
    q.colors[0] = q.colors[1] = q.colors[2] = q.colors[3] = D_L00_001B0618 + (*(int *)(data+28) << 24);
    func_00282C88(matrix[0]);
    func_00282C88(matrix[1]);
    func_00282C88(matrix[2]);
    matrix[0][0] = 1.0f;
    matrix[1][1] = 1.0f;
    matrix[2][2] = *(float *)(data+16)*0.865f;
    index=0;
    do {
        int i;
        for (i=0;i<4;i++) {
            int vertex_index = D_L00_002983B0[index][i][0];
            int uv_index = D_L00_002983B0[index][i][1];
            func_00282D30(q.vertices[i],D_L00_002976D0[vertex_index],D_L00_001B061C);
            q.uv[i][0] = D_L00_00299130[uv_index][0] + D_L00_001B05D4;
            q.uv[i][1] = D_L00_00299130[uv_index][1] + D_L00_001B05D8;
            if (D_L00_002976D0[vertex_index][2] == -0.001052f)
                q.colors[i] = D_L00_001B0618;
            else
                q.colors[i] = D_L00_001B0618 | (*(int *)(data+28)<<24);
        }
        func_00283098(q.vertices[0],q.vertices[0],matrix);
        func_00283098(q.vertices[1],q.vertices[1],matrix);
        func_00283098(q.vertices[2],q.vertices[2],matrix);
        func_00283098(q.vertices[3],q.vertices[3],matrix);
        func_00282C88(center);
        for(i=0;i<4;i++) {
            q.uv[i][0] -= q.vertices[i][2]*0.125f;
            q.vertices[i][0] *= ref_L00_003E5BD8_00(q.vertices[i][2]) + 2.0f;
            q.vertices[i][1] *= ref_L00_003E5BD8_00(q.vertices[i][2]) + 2.0f;
            func_00283098(q.vertices[i],q.vertices[i],object+192);
            q.vertices[i][0] += *(float *)(object+16);
            q.vertices[i][1] += *(float *)(object+20);
            q.vertices[i][2] += *(float *)(object+24);
            func_00282CC0(center,center,q.vertices[i]);
        }
        func_00282D30(center,center,0.25f);
        func_00282CF0(normal,center,D_L00_001B8DC0);
        func_00282F20(normal,normal,1.0f);
        func_00282CF0(edge1,q.vertices[2],q.vertices[0]);
        func_00282CF0(edge2,q.vertices[2],q.vertices[1]);
        func_00282DD8(center,edge1,edge2);
        func_00282F20(center,center,1.0f);
        if(func_00282DB0(normal,center)>0.0f)
            func_00280B90(&q,0,0);
    } while(++index<215);
}

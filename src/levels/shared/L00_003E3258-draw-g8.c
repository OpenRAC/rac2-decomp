#include "common.h"

typedef float RenderVec5BD8[4] __attribute__((aligned(16)));
typedef struct {
    RenderVec5BD8 vertices[4];
    int colors[4];
    float uv[4][2];
    unsigned long gs[4];
} Quad5BD8;
extern int g_blast_shell_gs_flag_a __attribute__((sda));
extern int g_blast_shell_gs_flag_b __attribute__((sda));
extern int g_blast_shell_gs_flag_c __attribute__((sda));
extern int g_blast_shell_gs_flag_d __attribute__((sda));
extern int g_blast_shell_gs_flag_e __attribute__((sda));
extern int g_blast_shell_texture_id __attribute__((sda));
extern int g_blast_shell_color __attribute__((sda));
extern float g_blast_shell_scale __attribute__((sda));
extern float g_blast_uv_scroll_u __attribute__((sda));
extern float g_blast_uv_scroll_v __attribute__((sda));
extern char *g_blast_effect_records __attribute__((sda));
extern int *g_blast_l00_ripple_particles MACRO_ADDR;
extern short g_blast_shell_quad_indices[][4][2];
extern RenderVec5BD8 g_blast_shell_vertices[];
extern float g_blast_shell_uvs[][2];
extern RenderVec5BD8 g_camera_l00_position;
extern unsigned long GetEffectTextureDescriptor(int);
extern void vec_clear_128(void *);
extern void FastVecScale(void *,void *,float);
extern void matrix_mul_vec3(void *,void *,void *);
extern float vec_length_xy(void *);
extern float ref_L00_003E5BD8_00(float);
extern void FastVecAdd(void *,void *,void *);
extern void FastVecSub(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float);
extern void FastVecCross(void *,void *,void *);
extern float FastVecDot(void *,void *);
extern char * AllocateOwnedEffectParticle(char *,int,float,float,void *);
extern void draw_world_quad(void *,int,int);

/* Draws the large blast shell around the object as 215 quads, skipping the ones that face away from the camera. */
void blast_draw_shell_mesh(char *object_)
{
    Quad5BD8 quad;
    RenderVec5BD8 matrix[3];
    RenderVec5BD8 normal, center, edge1, edge2;
    int p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15;
    char *object = object_;
    int index;
    char *data = *(char **)(object + 0x68);
    quad.gs[1] = GetEffectTextureDescriptor(g_blast_shell_texture_id);
    quad.gs[3] = (unsigned long)g_blast_shell_gs_flag_a | ((unsigned long)g_blast_shell_gs_flag_b << 2);
    quad.gs[3] |= (unsigned long)g_blast_shell_gs_flag_c << 4;
    quad.gs[3] |= (unsigned long)g_blast_shell_gs_flag_d << 6;
    quad.gs[3] |= (unsigned long)g_blast_shell_gs_flag_e << 32;
    quad.gs[2] = 0xFF9000000260UL;
    quad.gs[0] = 0;
    quad.colors[0] = quad.colors[1] = quad.colors[2] = quad.colors[3] = g_blast_shell_color + (*(int *)(data+28) << 24);
    vec_clear_128(matrix[0]);
    vec_clear_128(matrix[1]);
    vec_clear_128(matrix[2]);
    matrix[0][0] = 1.0f;
    matrix[1][1] = 1.0f;
    matrix[2][2] = *(float *)(data+16)*0.865f;
    index=0;
    do {
        int i;
        for (i=0;i<4;i++) {
            int vertex_index = g_blast_shell_quad_indices[index][i][0];
            int uv_index = g_blast_shell_quad_indices[index][i][1];
            FastVecScale(quad.vertices[i],g_blast_shell_vertices[vertex_index],g_blast_shell_scale);
            quad.uv[i][0] = g_blast_shell_uvs[uv_index][0] + g_blast_uv_scroll_u;
            quad.uv[i][1] = g_blast_shell_uvs[uv_index][1] + g_blast_uv_scroll_v;
            if (g_blast_shell_vertices[vertex_index][2] == -0.001052f)
                quad.colors[i] = g_blast_shell_color;
            else
                quad.colors[i] = g_blast_shell_color | (*(int *)(data+28)<<24);
        }
        matrix_mul_vec3(quad.vertices[0],quad.vertices[0],matrix);
        matrix_mul_vec3(quad.vertices[1],quad.vertices[1],matrix);
        matrix_mul_vec3(quad.vertices[2],quad.vertices[2],matrix);
        matrix_mul_vec3(quad.vertices[3],quad.vertices[3],matrix);
        vec_clear_128(center);
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
        FastVecSub(normal,center,g_camera_l00_position);
        vec_scale_to_length(normal,normal,1.0f);
        FastVecSub(edge1,quad.vertices[2],quad.vertices[0]);
        FastVecSub(edge2,quad.vertices[2],quad.vertices[1]);
        FastVecCross(center,edge1,edge2);
        vec_scale_to_length(center,center,1.0f);
        if(FastVecDot(normal,center)>0.0f)
            draw_world_quad(&quad,0,0);
    } while(++index<215);
}

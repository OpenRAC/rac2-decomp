#include "names.h"
/* func_PAL_L00_003B7FC0, the PAL copy of func_L00_003B4560: the same C, where wrap D_L00_001AF9E0 (({e}) * 1.2f). */
/* func_PAL_L00_003B7FC0 needs -G8 (sda reads) and -frac2-sticky-volatile-refs:
 * retail leaves the slot of `jal func_00280328` empty because reorg's forward
 * search stops at qcopy's volatile asm, as in func_L00_002A9460 and
 * func_L00_003C5310 (see tools/compiler/README.md).
 */
#include "common.h"
typedef unsigned int MeshQuad __attribute__((mode(TI)));
typedef union { MeshQuad q; float v[4]; } MeshVector;
typedef struct { float x, y, z; } MeshPoint;
extern float g_mesh_uv_scroll __attribute__((sda)), g_mesh_uv_scroll_rate __attribute__((sda)), g_mesh_scale __attribute__((sda));
extern int g_mesh_effect_texture __attribute__((sda)), g_glint_effect_texture_a __attribute__((sda)), g_glint_effect_texture_b __attribute__((sda));
extern u32 g_mesh_alpha_bits __attribute__((sda));
extern int D_L00_001AF998_1[] __attribute__((sda)), D_L00_001AF9D0_1[] __attribute__((sda));
extern signed char D_L00_001AF9E8_1[] __attribute__((sda));
extern MeshVector g_camera_l00_position NOT_SDA, g_hero_state_block NOT_SDA;
extern float g_effect_mesh_vertices_a[][3], g_effect_mesh_vertices_b[][3];
extern float g_effect_mesh_uvs_a[][2], g_effect_mesh_uvs_b[][2];
extern u32 g_effect_mesh_colors_a[], g_effect_mesh_colors_b[];
extern u64 GetEffectTextureDescriptor(int);
extern void VU1_addGSregister(int,u64), font_queue_vu_state(void);
extern void FastVecSub(void *,void *,void *), vec_scale_to_length(void *,void *,float), FastVecCross(void *,void *,void *), transform_vector(void *,void *,void *);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern void part_draw_glint_effect(int,void *,int,void *,int);
static inline void MeshStorePoint(MeshPoint *point, MeshVector *value)
{
    point->x = value->v[0];
    point->y = value->v[1];
    point->z = value->v[2];
}
/* Draws the four-sided glowing mesh that faces the camera, as eight flipped copies of two vertex
 * sets, fading with opacity. (PAL: 50 Hz timings) */
void mesh_draw_four_signs_pal(unsigned char *object, float opacity)
{
    MeshVector transform[4];
    MeshPoint positions[148];
    float uv[148][2];
    MeshVector temp;
    int alpha;
    unsigned char *origin;
    g_mesh_uv_scroll += ((g_mesh_uv_scroll_rate) * 1.2f);
    if (g_mesh_uv_scroll >= 7.0f) g_mesh_uv_scroll -= 7.0f;
    { u64 texture = GetEffectTextureDescriptor(g_mesh_effect_texture);
      origin = object + 0x10;
      VU1_addGSregister(6,texture); }
    VU1_addGSregister(0x42,0x8000000048ULL);
    VU1_addGSregister(8,0);
    VU1_addGSregister(0x14,0xFF9000000260ULL);
    font_queue_vu_state();
    FastVecSub(&transform[0],&g_camera_l00_position,origin);
    vec_scale_to_length(&transform[0],&transform[0],1.0f);
    FastVecCross(&transform[1],&transform[0],&g_hero_state_block);
    vec_scale_to_length(&transform[1],&transform[1],-1.0f);
    FastVecCross(&transform[2],&transform[1],&transform[0]);
    qcopy(&transform[3], origin);
    {
    int i;
    for (i=0;i<148;++i) {
        temp.v[0] = 0.0f;
        temp.v[1] = g_effect_mesh_vertices_a[i][1] * g_mesh_scale;
        temp.v[2] = g_effect_mesh_vertices_a[i][0] * g_mesh_scale;
        temp.v[3] = 1.0f;
        transform_vector(&temp,&temp,transform);
        MeshStorePoint(&positions[i], &temp);
        uv[i][0] = g_effect_mesh_uvs_a[i][1] + g_mesh_uv_scroll;
        uv[i][1] = g_effect_mesh_uvs_a[i][0];
        if (g_effect_mesh_colors_a[i] & 0xFF000000) {
            alpha=FloatToInt(IntToFloat(D_L00_001AF9E8_1[7])*opacity);
            if (alpha < 1) alpha=1;
            alpha <<= 24;
            alpha |= g_mesh_alpha_bits;
            g_effect_mesh_colors_a[i] = alpha;
        } else g_effect_mesh_colors_a[i] = g_mesh_alpha_bits;
    }
    part_draw_glint_effect(g_glint_effect_texture_a,positions,g_glint_effect_texture_b,uv,1);
    }
    {
    int i;
    for (i=0;i<60;++i) {
        temp.v[0] = 0.0f;
        temp.v[1] = g_effect_mesh_vertices_b[i][1] * g_mesh_scale;
        temp.v[2] = g_effect_mesh_vertices_b[i][0] * g_mesh_scale;
        temp.v[3] = 1.0f;
        transform_vector(&temp,&temp,transform);
        MeshStorePoint(&positions[i], &temp);
        uv[i][0] = g_effect_mesh_uvs_b[i][1] + g_mesh_uv_scroll;
        uv[i][1] = g_effect_mesh_uvs_b[i][0];
        if (g_effect_mesh_colors_b[i] & 0xFF000000) {
            alpha=FloatToInt(IntToFloat(D_L00_001AF9E8_1[7])*opacity);
            if (alpha < 1) alpha=1;
            alpha <<= 24;
            alpha |= g_mesh_alpha_bits;
            g_effect_mesh_colors_b[i] = alpha;
        } else g_effect_mesh_colors_b[i] = g_mesh_alpha_bits;
    }
    part_draw_glint_effect(D_L00_001AF998_1[1],positions,D_L00_001AF9D0_1[1],uv,1);
    }
    {
    int i;
    for (i=0;i<148;++i) {
        temp.v[0] = 0.0f;
        temp.v[1] = -g_effect_mesh_vertices_a[i][1] * g_mesh_scale;
        temp.v[2] = g_effect_mesh_vertices_a[i][0] * g_mesh_scale;
        temp.v[3] = 1.0f;
        transform_vector(&temp,&temp,transform);
        MeshStorePoint(&positions[i], &temp);
        uv[i][0] = g_effect_mesh_uvs_a[i][1] + g_mesh_uv_scroll;
        uv[i][1] = g_effect_mesh_uvs_a[i][0];
    }
    part_draw_glint_effect(g_glint_effect_texture_a,positions,g_glint_effect_texture_b,uv,1);
    }
    {
    int i;
    for (i=0;i<60;++i) {
        temp.v[0] = 0.0f;
        temp.v[1] = -g_effect_mesh_vertices_b[i][1] * g_mesh_scale;
        temp.v[2] = g_effect_mesh_vertices_b[i][0] * g_mesh_scale;
        temp.v[3] = 1.0f;
        transform_vector(&temp,&temp,transform);
        MeshStorePoint(&positions[i], &temp);
        uv[i][0] = g_effect_mesh_uvs_b[i][1] + g_mesh_uv_scroll;
        uv[i][1] = g_effect_mesh_uvs_b[i][0];
    }
    part_draw_glint_effect(D_L00_001AF998_1[1],positions,D_L00_001AF9D0_1[1],uv,1);
    }
    {
    int i;
    for (i=0;i<148;++i) {
        temp.v[0] = 0.0f;
        temp.v[1] = g_effect_mesh_vertices_a[i][1] * g_mesh_scale;
        temp.v[2] = -g_effect_mesh_vertices_a[i][0] * g_mesh_scale;
        temp.v[3] = 1.0f;
        transform_vector(&temp,&temp,transform);
        MeshStorePoint(&positions[i], &temp);
        uv[i][0] = g_effect_mesh_uvs_a[i][1] + g_mesh_uv_scroll;
        uv[i][1] = g_effect_mesh_uvs_a[i][0];
    }
    part_draw_glint_effect(g_glint_effect_texture_a,positions,g_glint_effect_texture_b,uv,1);
    }
    {
    int i;
    for (i=0;i<60;++i) {
        temp.v[0] = 0.0f;
        temp.v[1] = g_effect_mesh_vertices_b[i][1] * g_mesh_scale;
        temp.v[2] = -g_effect_mesh_vertices_b[i][0] * g_mesh_scale;
        temp.v[3] = 1.0f;
        transform_vector(&temp,&temp,transform);
        MeshStorePoint(&positions[i], &temp);
        uv[i][0] = g_effect_mesh_uvs_b[i][1] + g_mesh_uv_scroll;
        uv[i][1] = g_effect_mesh_uvs_b[i][0];
    }
    part_draw_glint_effect(D_L00_001AF998_1[1],positions,D_L00_001AF9D0_1[1],uv,1);
    }
    {
    int i;
    for (i=0;i<148;++i) {
        temp.v[0] = 0.0f;
        temp.v[1] = -g_effect_mesh_vertices_a[i][1] * g_mesh_scale;
        temp.v[2] = -g_effect_mesh_vertices_a[i][0] * g_mesh_scale;
        temp.v[3] = 1.0f;
        transform_vector(&temp,&temp,transform);
        MeshStorePoint(&positions[i], &temp);
        uv[i][0] = g_effect_mesh_uvs_a[i][1] + g_mesh_uv_scroll;
        uv[i][1] = g_effect_mesh_uvs_a[i][0];
    }
    part_draw_glint_effect(g_glint_effect_texture_a,positions,g_glint_effect_texture_b,uv,1);
    }
    {
    int i;
    for (i=0;i<60;++i) {
        temp.v[0] = 0.0f;
        temp.v[1] = -g_effect_mesh_vertices_b[i][1] * g_mesh_scale;
        temp.v[2] = -g_effect_mesh_vertices_b[i][0] * g_mesh_scale;
        temp.v[3] = 1.0f;
        transform_vector(&temp,&temp,transform);
        MeshStorePoint(&positions[i], &temp);
        uv[i][0] = g_effect_mesh_uvs_b[i][1] + g_mesh_uv_scroll;
        uv[i][1] = g_effect_mesh_uvs_b[i][0];
    }
    part_draw_glint_effect(D_L00_001AF998_1[1],positions,D_L00_001AF9D0_1[1],uv,1);
    }
}

#include "names.h"
/* func_L09_0037FCE8: the water sheet draw callback of Dobbo and Yeedil.
 * Adapted from public OpenRAC/rac1-decomp draw_pokitaru_ocean
 * (src/overlays/shared/homing_missile_and_water_sheet.c, GPL-3.0): RAC2 drops
 * the far quad and the height fade, and lifts each grid layer 0.05 above the
 * water height. Own unit: -G8 for the gp-relative wave speeds, -g for the
 * nops before the strip's div.s. */
#include "common.h"
typedef struct { float x,y,z,w; } Vec4f;
extern void FastVecAdd(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float);
extern void FastVecScale(void *,void *,float);
extern int FastTweenColor(int,int,float);
extern u64 GetEffectTextureDescriptor(int);
extern float vec_length_xy(void *);
extern void math_trap_always(void);
typedef struct { float u, v; } UV_30BCD8;
typedef struct { float x, y, z; } Pos_30BCD8;
typedef struct {
    Vec4f v[4];
    int col[4];
    UV_30BCD8 uv[4];
    long long z70;
    long long z78;
    long long q80;
    long long q88;
} Quad_30BCD8;
typedef struct {
    int f0;
    int f4;
    int f8;
    int fC;
    int f10;
    float f14;
    float f18;
    int f1C;
    int f20;
    float f24;
    float f28;
    float f2C;
    int pad30, pad34, f38;
} Data_30BCD8;
typedef struct { char pad[0x140]; float x, y, z; } Cam_30BCD8;
typedef struct { char pad[0x228]; float f228, f22C; } Fog_30BCD8;

extern void VU1_addGSregister(unsigned int, unsigned long long);
extern void font_queue_vu_state(void);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern float IntToFloat(int);
extern void part_draw_glint_effect(int, void *, void *, void *, int);
extern int g_game_mode __attribute__((nosda));
extern int g_current_map_index MACRO_ADDR;
extern char g_fog_state[];
extern int g_water_sheet_disable MACRO_ADDR;
extern char g_camera_matrix[];
extern float g_camera_l09_position[];
extern float g_water_sheet_z MACRO_ADDR;
extern char g_hero_l09_aux_state[];
extern Pos_30BCD8 g_water_sheet_positions[];
extern int g_water_sheet_colors[];
extern UV_30BCD8 g_water_sheet_uvs[];
extern Pos_30BCD8 g_water_sheet_fade_positions[];
extern int g_water_sheet_fade_colors[];
extern UV_30BCD8 g_water_sheet_fade_uvs[];
extern float g_water_sheet_uv_scales[2] __attribute__((sda));
extern UV_30BCD8 g_water_layer_uv_offsets[] MACRO_ADDR;

/* Draws the fading edge strip and two scrolling water grid layers. */
void water_sheet_draw(char *moby) {
    Vec4f v0;
    Vec4f v1;
    Vec4f a;
    Vec4f b;
    Vec4f c[4];
    Vec4f d0;
    Vec4f d1;
    Quad_30BCD8 q;
    Data_30BCD8 *d = (Data_30BCD8 *)*(void **)(moby + 0x68);
    float s228 = ((Fog_30BCD8 *)g_fog_state)->f228;
    float s22C = ((Fog_30BCD8 *)g_fog_state)->f22C;
    int i;
    int layer;
    int colA;
    int colB;
    int n;
    float t;
    float x;
    float y;

    if (g_game_mode != 0x1C && g_water_sheet_disable == 0) {
        ((Fog_30BCD8 *)g_fog_state)->f228 = 255.0f;
        ((Fog_30BCD8 *)g_fog_state)->f22C = 249.9f;
    }
    VU1_addGSregister(0x42, 0x3200000044LL);
    VU1_addGSregister(8, 0);
    VU1_addGSregister(0x14, 0xFF9000000260LL);
    if (d->f38) VU1_addGSregister(0x47, 0x5310B);
    else VU1_addGSregister(0x47, 0x513F1);
    VU1_addGSregister(6, GetEffectTextureDescriptor(0x16));
    font_queue_vu_state();
    a.x = 1.0f;
    a.y = 0.0f;
    a.z = 0.0f;
    a.w = 1.0f;
    matrix_mul_vec3(&a, &a, g_camera_matrix);
    b.x = 0.0f;
    b.y = 1.0f;
    b.z = 0.0f;
    b.w = 1.0f;
    matrix_mul_vec3(&b, &b, g_camera_matrix);
    if (g_current_map_index != 13) a.z = 0.0f;
    vec_scale_to_length(&a, &a, 1.0f);
    if (g_current_map_index != 13) b.z = 0.0f;
    vec_scale_to_length(&b, &b, 1.0f);
    vec_scale_to_length(&v0, &a, -75.0f);
    vec_scale_to_length(&v1, &b, -87.0f);
    FastVecAdd(&c[0], &v0, &v1);
    vec_scale_to_length(&v1, &b, 87.0f);
    FastVecAdd(&c[2], &v0, &v1);
    vec_scale_to_length(&v0, &a, d->f28);
    vec_scale_to_length(&v1, &b, -750.0f);
    FastVecAdd(&c[1], &v0, &v1);
    vec_scale_to_length(&v1, &b, 750.0f);
    FastVecAdd(&c[3], &v0, &v1);
    for (i = 0; i < 4; i++) {
        Vec4f *p = &c[i];
        FastVecAdd(p, p, g_camera_l09_position);
        p->z = g_water_sheet_z;
    }
    FastVecSub(&d0, &c[1], &c[0]);
    FastVecSub(&d1, &c[3], &c[2]);
    t = 10.0f;
    for (i = 0; i < 12; i += 2) {
        float f = IntToFloat(i) * 0.1f;
        float blend = IntToFloat(i);
        int col;
        blend = blend / t;
        col = FastTweenColor(d->f0, d->f4, blend);
        FastVecScale(&v0, &d0, f);
        g_water_sheet_colors[i] = col;
        g_water_sheet_uvs[i].u = 0.0f;
        g_water_sheet_uvs[i].v = 0.0f;
        FastVecAdd(&v0, &v0, &c[0]);
        g_water_sheet_positions[i].x = v0.x;
        g_water_sheet_positions[i].y = v0.y;
        g_water_sheet_positions[i].z = v0.z;
        FastVecScale(&v0, &d1, f);
        g_water_sheet_colors[i + 1] = col;
        g_water_sheet_uvs[i + 1].u = 0.0f;
        g_water_sheet_uvs[i + 1].v = 0.0f;
        FastVecAdd(&v0, &v0, &c[2]);
        g_water_sheet_positions[i + 1].x = v0.x;
        g_water_sheet_positions[i + 1].y = v0.y;
        g_water_sheet_positions[i + 1].z = v0.z;
    }
    part_draw_glint_effect(0xC, g_water_sheet_positions, g_water_sheet_colors, g_water_sheet_uvs, 1);
    q.z78 = GetEffectTextureDescriptor(0x16);
    q.q80 = 0xFF9000000260LL;
    q.q88 = 0x8000000044LL;
    q.z70 = 0;
    VU1_addGSregister(0x42, 0x8000000048LL);
    VU1_addGSregister(8, 0);
    VU1_addGSregister(0x14, 0xFF9000000260LL);
    VU1_addGSregister(0x47, 0x513F1);
    colA = d->fC;
    colB = d->f10;
    t = 1.0f;
    {
        colA = FastTweenColor(0, colA, t);
        colB = FastTweenColor(0, colB, t);
        for (layer = 0; layer < 2; layer++) {
            int id = layer + 0x3F;
            VU1_addGSregister(6, GetEffectTextureDescriptor(d->f1C + id));
            for (y = d->f18 * -2.0f; y < d->f18 * 2.0f; y += d->f18) {
                n = 0;
                for (x = d->f18 * -2.0f; x < d->f18 * 2.0f; x += d->f18) {
                    float z;

                    g_water_sheet_fade_uvs[n].u = x / (d->f18 * 2.0f) * g_water_sheet_uv_scales[layer] + g_water_layer_uv_offsets[layer].u;
                    g_water_sheet_fade_uvs[n].v = y / (d->f18 * 2.0f) * g_water_sheet_uv_scales[layer] + g_water_layer_uv_offsets[layer].v;
                    g_water_sheet_fade_positions[n].x = x + ((Cam_30BCD8 *)g_hero_l09_aux_state)->x + 1.0f;
                    g_water_sheet_fade_positions[n].y = y + ((Cam_30BCD8 *)g_hero_l09_aux_state)->y + 1.0f;
                    z = g_water_sheet_z;
                    z += (float)(layer + 1) * 0.05f;
                    g_water_sheet_fade_positions[n].z = z;
                    i = n + 1;
                    g_water_sheet_fade_uvs[i].u = x / (d->f18 * 2.0f) * g_water_sheet_uv_scales[layer] + g_water_layer_uv_offsets[layer].u;
                    g_water_sheet_fade_uvs[i].v = (y + d->f18) / (d->f18 * 2.0f) * g_water_sheet_uv_scales[layer] + g_water_layer_uv_offsets[layer].v;
                    g_water_sheet_fade_positions[i].x = x + ((Cam_30BCD8 *)g_hero_l09_aux_state)->x + 1.0f;
                    g_water_sheet_fade_positions[i].y = y + d->f18 + ((Cam_30BCD8 *)g_hero_l09_aux_state)->y + 1.0f;
                    g_water_sheet_fade_positions[i].z = z;
                    i = n + 2;
                    g_water_sheet_fade_uvs[i].u = (x + d->f18) / (d->f18 * 2.0f) * g_water_sheet_uv_scales[layer] + g_water_layer_uv_offsets[layer].u;
                    g_water_sheet_fade_uvs[i].v = y / (d->f18 * 2.0f) * g_water_sheet_uv_scales[layer] + g_water_layer_uv_offsets[layer].v;
                    g_water_sheet_fade_positions[i].x = x + d->f18 + ((Cam_30BCD8 *)g_hero_l09_aux_state)->x + 1.0f;
                    g_water_sheet_fade_positions[i].y = y + ((Cam_30BCD8 *)g_hero_l09_aux_state)->y + 1.0f;
                    g_water_sheet_fade_positions[i].z = z;
                    i = n + 3;
                    g_water_sheet_fade_uvs[i].u = (x + d->f18) / (d->f18 * 2.0f) * g_water_sheet_uv_scales[layer] + g_water_layer_uv_offsets[layer].u;
                    g_water_sheet_fade_uvs[i].v = (y + d->f18) / (d->f18 * 2.0f) * g_water_sheet_uv_scales[layer] + g_water_layer_uv_offsets[layer].v;
                    g_water_sheet_fade_positions[i].x = x + d->f18 + ((Cam_30BCD8 *)g_hero_l09_aux_state)->x + 1.0f;
                    g_water_sheet_fade_positions[i].y = y + d->f18 + ((Cam_30BCD8 *)g_hero_l09_aux_state)->y + 1.0f;
                    g_water_sheet_fade_positions[i].z = z;
                    for (i = n; i < n + 4; i++) {
                        v0.x = g_water_sheet_fade_positions[i].x - ((Cam_30BCD8 *)g_hero_l09_aux_state)->x;
                        v0.y = g_water_sheet_fade_positions[i].y - ((Cam_30BCD8 *)g_hero_l09_aux_state)->y;
                        v0.z = g_water_sheet_fade_positions[i].z - ((Cam_30BCD8 *)g_hero_l09_aux_state)->z;
                        v0.w = 1.0f;
                        t = vec_length_xy(&v0) / (d->f18 * 2.0f);
                        if (t > 1.0f) {
                            t = 1.0f;
                        }
                        g_water_sheet_fade_colors[i] = FastTweenColor(colA, colB, t);
                    }
                    n += 4;
                    if (n >= 0x40) {
                        math_trap_always();
                    }
                }
                part_draw_glint_effect(n, g_water_sheet_fade_positions, g_water_sheet_fade_colors, g_water_sheet_fade_uvs, 1);
            }
        }
    }
    ((Fog_30BCD8 *)g_fog_state)->f228 = s228;
    ((Fog_30BCD8 *)g_fog_state)->f22C = s22C;
    VU1_addGSregister(0x47, 0x5360B);
}

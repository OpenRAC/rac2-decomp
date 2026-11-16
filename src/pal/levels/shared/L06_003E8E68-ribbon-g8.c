#include "names.h"
/* Adapted from RAC1's render_data_processor_linked_effect in
   src/overlays/l10_orxon/platforms_doors_and_bombthrower.c (GPL-3.0). */
/* func_PAL_L06_003E8E68, the PAL copy of func_L06_003E57E8: the same C, where the
   fade duration D * 60 is scaled to 50 Hz as (D * 300 + 2) / 6, and D is read from PAL's own copy
   of the value, not the one func_PAL_L06_004042F8 reads, so it has a name of its own. */
#include "common.h"
extern char *g_moby_l06_table;
extern char g_hero_l06_position[];
extern float fast_vec_dist(char *,char *);
extern void set_scale_matrix(void *,float);
extern void euler_to_matrix(void *,void *);
extern void multiply_matrix(void *,void *,void *);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern int FastTweenColor(int,int,float);
extern unsigned long GetEffectTextureDescriptor(int);
extern void FastVecAdd(void *,void *,void *);
extern void draw_world_quad(void *,void *,int);
extern int g_ribbon_l06_blend_a __attribute__((sda)),g_ribbon_l06_blend_b __attribute__((sda)),g_ribbon_l06_blend_c __attribute__((sda)),g_ribbon_l06_blend_d __attribute__((sda));
extern int g_ribbon_color_start __attribute__((sda)),g_ribbon_color_end __attribute__((sda));
extern float g_ribbon_uv_table[] SDATA(D_L06_001AF578);
extern float g_ribbon_vertex_offsets[] SDATA(D_L06_001AF5A0);
extern float ref_PAL_L06_003E8E68_00 __attribute__((sda));
extern float g_ribbon_uv_init_table[7] __attribute__((sda));
extern float g_texture_scroll_step;
extern int g_ripple_grid_duration,g_ripple_grid_fade_start;
typedef unsigned int Quad57 __attribute__((mode(TI)));

void func_PAL_L06_003E8E68(u8 *moby) {
    char *data = (*(char **)(moby + 0x68));
    char *base = *(char **)((*(int *)(data + 0xc) << 8) + (int)g_moby_l06_table + 0x68);
    char scratch[(unsigned int)*(int *)(data + 4) * 0x40];
    struct {
        struct {
            float xyz[4][4];
            unsigned int color[4];
            float uv[8];
            u64 tag[4];
        } front, back;
        float rotation[16];
    } buffers __attribute__((aligned(16)));
    int i, j, group, row, vertex;
    float fade, phase;
    unsigned char *order;
    int group_age;
    char *age_base;
    char *ages;
    int group_vertices;
    float *matrix1;
    int next_group, next_row;
    float *matrix2, *uv1, *uv2;

    {
        float distance = fast_vec_dist(moby + 0x10, g_hero_l06_position);
        if (distance > 48.0f) fade = (80.0f - distance) * 0.03125f;
        else fade = 1.0f;
    }
    set_scale_matrix(buffers.rotation, *(float *)data * 0.5f);
    matrix1 = buffers.front.uv;
    matrix2 = buffers.back.uv;
    uv1 = matrix1 + 1;
    uv2 = matrix2 + 1;
    {
        int n;
        for (n = 0; n < *(int *)(data + 4); n++) {
            euler_to_matrix(scratch + n * 0x40, moby + 0xf0);
            multiply_matrix(scratch + n * 0x40, scratch + n * 0x40, buffers.rotation);
            *(Quad57 *)(scratch + n * 0x40 + 0x30) = *(Quad57 *)(moby + 0x10);
            *(float *)(scratch + n * 0x40 + 0x38) += IntToFloat(n + 1) * *(float *)(data + 8);
        }
    }
    {
        u64 texture = GetEffectTextureDescriptor(14);
        u64 packet_flags = (u64)g_ribbon_l06_blend_a | ((u64)g_ribbon_l06_blend_b << 2);
        packet_flags |= (u64)g_ribbon_l06_blend_c << 4;
        packet_flags |= (u64)g_ribbon_l06_blend_d << 6;
        packet_flags |= 0x8000000000ULL;
        ((u64 *)buffers.back.uv)[5] = texture;
        ((u64 *)buffers.front.uv)[5] = texture;
        ((u64 *)buffers.back.uv)[6] = 0xff9000000260ULL;
        ((u64 *)buffers.front.uv)[6] = 0xff9000000260ULL;
        ((u64 *)buffers.back.uv)[4] = 0;
        ((u64 *)buffers.front.uv)[4] = 0;
        ((u64 *)buffers.back.uv)[7] = packet_flags;
        ((u64 *)buffers.front.uv)[7] = packet_flags;
    }
    {
        int k;
        for (k = 0; k < 4; k++) {
            uv1[k * 2] = uv2[k * 2] = g_ribbon_uv_init_table[k * 2];
        }
    }
    group = 0;
    do {
        next_group = group + 1;
        phase = 0.0f;
        row = 0;
        do {
            int next;
            phase += g_texture_scroll_step;
            if (phase > 1.0f) phase -= 1.0f;
            next_row = row + 1;
            for (j = 0; j < 4; j++) {
                matrix1[j * 2] = matrix2[j * 2] =
                    g_ribbon_uv_table[j * 2] + phase + *(float *)(base + 0x12de0);
            }
            for (i = 0; i < *(int *)(data + 4); i = next) {
                int offset;
                int age;
                float progress;
                unsigned int color;
                order = (unsigned char *)(data + 0x10);
                group_age = group * 0x78;
                age_base = base + 0x10000;
                ages = age_base + 0x2c00;
                age = *(int *)(ages + (order[i] * 4 + group_age));
                group_vertices = group * 0x2580;
                if (age > g_ripple_grid_fade_start) {
                    progress = IntToFloat(age - g_ripple_grid_fade_start) /
                               IntToFloat(g_ripple_grid_duration - g_ripple_grid_fade_start);
                } else {
                    progress = 1.0f - IntToFloat(age) /
                               IntToFloat(g_ripple_grid_fade_start);
                }
                color = FastTweenColor(g_ribbon_color_start, g_ribbon_color_end, progress);
                color = (color & 0xffffff) +
                        (FloatToInt(fade * fade *
                         IntToFloat((int)color >> 24)) << 24);
                if (moby[0x20] == 2) {
                    float alpha = IntToFloat(*(int *)(data + 0x34));
                    float duration;
                    alpha *= 255.0f;
                    duration = (ref_PAL_L06_003E8E68_00 * 300.0f + 2.0f) * 0.16666667f;
                    color = (FloatToInt(alpha / duration) << 24) | 0xffffff;
                }
                vertex = 0;
                offset = i * 0x40;
                next = i + 1;
                buffers.back.color[3] = color;
                buffers.back.color[2] = color;
                buffers.back.color[1] = color;
                buffers.back.color[0] = color;
                for (; vertex < 4; vertex++) {
                    FastVecAdd(buffers.back.xyz[vertex], (char *)g_ribbon_vertex_offsets + vertex * 0x10,
                        (char *)((float (*)[80])(base + group_vertices))[(row + (vertex >> 1))] + order[i] * 0x10);
                }
                draw_world_quad(buffers.back.xyz, scratch + offset, 0);
            }
            row = next_row;
        } while (row < 19);
        group = next_group;
    } while (group < 4);
}

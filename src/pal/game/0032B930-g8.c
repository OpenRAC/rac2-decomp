/* func_PAL_0032B930, the PAL copy of func_0032A140: the same C, where the 60, 120, 10 and 40 frame
 * counts become 50, 100, 8 and 33 and the 0.0523599 spin step becomes 0.0628319 (x6/5). */
#include "include_asm.h"
#include "common.h"

typedef unsigned int Quad __attribute__((mode(TI)));
typedef struct { float x, y, z, w; } Vec4 __attribute__((aligned(16)));
typedef struct { float u, v; } UVPair;

typedef struct {
    char pad[0xE0];
    Vec4 pos;
    char pad2[0x21A0];
    char *object;
} Context;

typedef struct {
    int done;
    int timer;
    char *first;
    char *second;
    int light;
    float radius;
} BlastState;

typedef struct {
    char pad[0x10];
    Vec4 pos;
    unsigned char mode;
    char pad21[0x47];
    BlastState *state;
} Blast;

typedef struct {
    char pad[8];
    float scale;
    int zero;
    Vec4 pos;
} Light;

extern Context g_hero_state;
extern char g_blast_direction[];
extern UVPair g_blast_uv_angles[];
extern char g_coll_hit_position[], g_camera_eye_state[];
extern Light g_dynamic_lights[];
extern int g_nearby_mobys[];
extern int g_blast_state_flag __attribute__((sda));
extern float math_random_angle(void), IntToFloat(int), math_square(float);
extern float math_fast_sin_or_cos_a(float), FastAddRotations(float,float), fast_subtract_rotations(float,float);
extern int FloatToInt(float), math_fast_float_d(void *);
extern void vec_build_spherical_offset(void *,float,float,float), FastVecAdd(void *,void *,void *);
extern void FastVecSub(void *,void *,void *), vec_scale_to_length(void *,void *,float);
extern int CollLine(void *,void *,int,void *,int), coll_process_hit(void *,int,void *,int,float);
extern void part_claim_ring_piece_pal(void *,void *,int), part_claim_debris_piece_pal(void *), math_init_random_direction_table(void *);
extern void make_hit_descriptor(void *,void *,int,void *,float), QueueMobyImpact(void *,void *);
extern void part_init_trail_sparkle_pairs_pal(void *), moby_mark_spawned(void *), gfx_free_point_light(int);
extern void euler_rotation_basis(void *,void *), part_update_debris_pieces(void *), part_update_trail_nodes(void *);
extern void part_update_ring_pieces(void *), gfx_update_screen_fade_pal(void), gfx_register_overlay_draw_callback(void (*)(void),void *);

void func_PAL_0032B930(Blast *self)
{
    float v[4] __attribute__((aligned(16)));
    struct {
        float direction[4];
        char pad10[8];
        unsigned char kind, mode;
        short classid;
        int pad1C;
        int enabled;
        char tail[12];
    } hit;
    BlastState *state = self->state;
    Light *light;
    int count;
    int i;
    int *list;
    void *info;
    float t, ratio, phase;

    qcopy(&self->pos, g_hero_state.object + 0x10);
    switch (self->mode) {
    case 0:
        self->mode = 1;
        state->timer = 50;
        state->radius = 0;
        for (i = 0; i < 137; i++) {
            g_blast_uv_angles[i].u = math_random_angle();
            g_blast_uv_angles[i].v = math_random_angle();
        }
    case 1:
        self->mode = 2;
    case 2:
        ratio = IntToFloat(state->timer);
        ratio /= IntToFloat(50);
        state->radius = math_square(1.0f - ratio) * 15.0f;
        if (state->timer % 3 == 0) {
            float a = math_random_angle();
            float b = math_random_angle();
            vec_build_spherical_offset(v, state->radius, a, b);
            FastVecAdd(v, v, &g_hero_state.pos);
            if (CollLine(&g_hero_state.pos, v, 0, g_hero_state.object, 0))
                qcopy(v, g_coll_hit_position);
            part_claim_ring_piece_pal(self, v, 8);
        }
        if (state->timer < 8 && !(state->timer & 7))
            part_claim_debris_piece_pal(self);
        if (math_fast_float_d(&state->timer)) {
            state->timer = 100;
            self->mode = 3;
            count = coll_process_hit(&g_hero_state.pos, 0, self, 0, 15.0f);
            i = 0;
            if (i < count) {
                list = g_nearby_mobys;
                info = &hit;
                for (; i < count; i++) {
                    if ((*(unsigned long long *)((char *)list[i] + 0x30) & 0x500000000000ULL) &&
                        (char *)list[i] != g_hero_state.object &&
                        *(short *)((char *)list[i] + 0xAA) != 3303 && *(short *)((char *)list[i] + 0xAA) != 3000) {
                        FastVecSub(v, (char *)list[i] + 0x10, &g_hero_state.pos);
                        vec_scale_to_length(v, v, 1.0f);
                        vec_scale_to_length(info, info, 1.0f);
                        make_hit_descriptor(info, self, 0x830000, v, 30.0f);
                        *(Quad *)hit.direction = *(Quad *)v;
                        hit.enabled = 1;
                        hit.direction[3] = 5627.925f;
                        hit.kind = 5;
                        hit.mode = 3;
                        hit.classid = *(short *)((char *)list[i] + 0xAA);
                        QueueMobyImpact((char *)list[i], info);
                    }
                }
            }
            math_init_random_direction_table(self);
        }
        break;
    case 3:
        if (!(state->timer & 7))
            part_claim_debris_piece_pal(self);
        math_fast_float_d(&state->timer);
        part_init_trail_sparkle_pairs_pal(self);
        if (state->timer == 33)
            self->mode = 4;
        break;
    case 4:
        if (math_fast_float_d(&state->timer) && !state->done) {
            if (state->first)
                moby_mark_spawned(state->first);
            if (state->second)
                moby_mark_spawned(state->second);
            if (state->light != -1)
                gfx_free_point_light(state->light);
            g_blast_state_flag = 0;
            moby_mark_spawned(self);
            return;
        }
        break;
    }
    phase = IntToFloat(state->timer);
    phase /= IntToFloat(100);
    phase = 1.0f - phase;
    phase *= 6.2831855f;
    t = (math_fast_sin_or_cos_a(phase - 3.1415927f) + 1.0f) * 0.5f;
    if (state->first) {
        i = FloatToInt(t * 32.0f);
        **(int **)(state->first + 0x68) = i;
        *(float *)(state->first + 0xF8) = FastAddRotations(*(float *)(state->first + 0xF8), 0.062831864f);
        euler_rotation_basis(state->first + 0xC0, state->first + 0xF0);
        *(float *)(state->first + 0xC0) *= 0.5f;
        *(float *)(state->first + 0xD4) *= 0.5f;
        *(float *)(state->first + 0xE8) = t * 1.5f;
        qcopy(state->first + 0x10, g_hero_state.object + 0x10);
    }
    if (state->second) {
        i = FloatToInt(t * 32.0f);
        **(int **)(state->second + 0x68) = i;
        *(float *)(state->second + 0xF8) = fast_subtract_rotations(*(float *)(state->second + 0xF8), 0.062831864f);
        euler_rotation_basis(state->second + 0xC0, state->second + 0xF0);
        *(float *)(state->second + 0xE8) = t;
        qcopy(state->second + 0x10, g_hero_state.object + 0x10);
    }
    if (state->light != -1) {
        light = &g_dynamic_lights[state->light];
        vec_scale_to_length(v, g_blast_direction, 0.5f);
        FastVecAdd(&light->pos, *(char **)(g_blast_direction + 0x1FF0) + 16, v);
        FastVecSub(v, g_camera_eye_state, &light->pos);
        vec_scale_to_length(v, v, 0.15f);
        FastVecAdd(&light->pos, &light->pos, v);
        light->scale = t;
        light->pos.w = 5.0f;
        light->zero = 0;
    }
    part_update_debris_pieces(self);
    part_update_trail_nodes(self);
    part_update_ring_pieces(self);
    gfx_register_overlay_draw_callback(gfx_update_screen_fade_pal, self);
}

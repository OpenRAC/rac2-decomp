#include "include_asm.h"
#include "common.h"
extern u8 g_effect_descriptor_default[] MACRO_ADDR;
extern int FastTweenColor(int, int, float);
typedef struct { float v[4]; } __attribute__((aligned(16))) VecF720;
typedef struct { VecF720 v[4]; int color[4]; float uv[4][2]; u64 r70, tex, r80, r88; } QuadF720;
extern float g_laser_bot_beam_origin[4] __attribute__((sda));
extern float g_laser_bot_beam_end[4] __attribute__((sda));
extern VecF720 g_collision_start_point, g_camera_pose_buffer;
extern int g_laser_beam_textures[2] __attribute__((sda));
extern int g_laser_beam_draw_bits_a __attribute__((sda)), g_laser_beam_draw_bits_b __attribute__((sda));
extern int g_laser_beam_color_start __attribute__((sda));
extern float g_laser_beam_alpha_step __attribute__((sda));
extern float g_laser_beam_widths[2] __attribute__((sda));
extern float g_laser_beam_uvs[8] __attribute__((sda));
extern float g_laser_beam_uv_v[] MACRO_ADDR;
extern int g_laser_beam_colors[2] __attribute__((sda));
extern int g_frame_l03_counter, g_laser_beam_color_end;
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecCross(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecScale(void *, void *, float);
extern void make_hit_descriptor(void *, void *, int, void *, float);
extern int CollLine(void *, void *, int, void *, void *);
extern u64 GetEffectTextureDescriptor(int);
extern void draw_world_quad(void *, int, int);
extern int PlayMobySound(int, int, void *);
extern int snd_is_voice_playing_for_owner(void *, int);
/* Draws the laser beam as glowing strips with a fading trail and plays its sound. */
void DrawBeamQuadsAndRingTrail(u8 *obj)
{
    QuadF720 q[2];
    VecF720 cross, delta, side, start, end;
    u8 hit[0x30] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(obj + 0x68);
    int j, k, n, c, trail, mask;
    float alpha, scale, w;

    g_laser_bot_beam_end[0] = *(float *)(state + 0x33C);
    matrix_mul_vec3(&start, &g_laser_bot_beam_origin, obj + 0xC0);
    FastVecAdd(&start, &start, obj + 0x10);
    matrix_mul_vec3(&end, &g_laser_bot_beam_end, obj + 0xC0);
    FastVecAdd(&end, &end, obj + 0x10);
    {
        VecF720 *verts = q[0].v;
        int i;

        mask = 1;
        if (obj[0x95] == 2) mask = 0x10001;
        make_hit_descriptor(hit, obj, mask, &g_effect_descriptor_default, (float)state[0x34]);
        {
            int found = CollLine(&start, &end, 0, obj, hit);
            QuadF720 *quads = q;

            if (found) qcopy(&end, &g_collision_start_point);
            scale = 1.0f;
            FastVecSub(&delta, &g_camera_pose_buffer, &start);
            FastVecSub(&side, &end, &start);
            FastVecCross(&cross, &side, &delta);
            vec_scale_to_length(&cross, &cross, scale);
            for (i = 0; i < 2; i++) {
                for (j = 0; j < 4; j++) {
                    w = 1.0f;
                    q[i].color[j] = FastTweenColor(g_laser_beam_colors[i] & 0xFF000000,
                                                 g_laser_beam_colors[i], *(float *)(state + 0x330));
                    q[i].uv[j][0] = g_laser_beam_uvs[j * 2];
                    q[i].uv[j][1] = g_laser_beam_uv_v[j * 2];
                    if (j & 1) FastVecScale(&q[i].v[j], &cross, g_laser_beam_widths[i]);
                    else FastVecScale(&q[i].v[j], &cross, -g_laser_beam_widths[i]);
                    if (j < 2) {
                        FastVecAdd(&q[i].v[j], &q[i].v[j], &start);
                    } else {
                        FastVecAdd(&q[i].v[j], &q[i].v[j], &end);
                    }
                    q[i].v[j].v[3] = w;
                }
                q[i].tex = GetEffectTextureDescriptor(g_laser_beam_textures[i]);
                q[i].r80 = 0xFF9000000260ULL;
                q[i].r88 = ((u64)g_laser_beam_draw_bits_a << 2) | ((u64)g_laser_beam_draw_bits_b << 6) | 0x8000000000ULL;
                q[i].r70 = 0;
            }
            draw_world_quad(&q[0], 0, 1);
            draw_world_quad(quads + 1, 0, 1);
            for (n = 3, j = 0; n >= 0; n--, j++) { q[0].uv[j][0] = .5f; q[0].uv[j][1] = .5f; }
            alpha = .1f;
            if (g_frame_l03_counter & 1) alpha = 0;
            c = FastTweenColor(g_laser_beam_color_start, g_laser_beam_color_end, alpha);
            q[0].color[0] = q[0].color[1] = c;
            c = FastTweenColor(g_laser_beam_color_start, g_laser_beam_color_end, alpha + g_laser_beam_alpha_step);
            q[0].color[2] = q[0].color[3] = c;
            {
                int span = *(s16 *)(state + 0x336) - 4;

                k = (*(s16 *)(state + 0x334) - span) % 4;
            }
            for (trail = 0; trail < *(s16 *)(state + 0x336); trail++) {
                qcopy(&q[0].v[0], state + 0x2A0 + k * 32);
                qcopy(&verts[1], state + 0x2B0 + k * 32);
                k = (k + 1) % 4;
                qcopy(&verts[2], state + 0x2A0 + k * 32);
                qcopy(&verts[3], state + 0x2B0 + k * 32);
                draw_world_quad(&q[0], 0, 1);
                alpha += g_laser_beam_alpha_step;
                c = FastTweenColor(g_laser_beam_color_start, g_laser_beam_color_end, alpha);
                q[0].color[0] = q[0].color[1] = c;
                c = FastTweenColor(g_laser_beam_color_start, g_laser_beam_color_end, alpha + g_laser_beam_alpha_step);
                q[0].color[2] = q[0].color[3] = c;
            }
            qcopy(&q[0].v[0], state + 0x2A0 + k * 32);
            qcopy(&verts[1], state + 0x2B0 + k * 32);
            qcopy(&verts[2], &start);
            qcopy(&verts[3], &end);
            draw_world_quad(&q[0], 0, 1);
            if (*(int *)(state + 0x340) == -1)
                *(int *)(state + 0x340) = PlayMobySound(5, 4, obj);
            else if (!snd_is_voice_playing_for_owner(obj, *(int *)(state + 0x340)))
                *(int *)(state + 0x340) = PlayMobySound(5, 4, obj);
        }
    }
}

extern void moby_mark_spawned(void *);
extern void moby_set_state(void *, int, int);
extern u8 *part_find_owned_effect_slot(void *, int, int);
extern int flag_set_first_pending(void *);
extern int math_fast_float_d(void *);
extern void vec_local_offset_to_world(void *, void *, float, float, float);
extern void *SpawnExplosion(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void fading_effect_update(void);
extern void ScatterObjectPieces(void *, void *, void *, void *, int, int, int, int, int, int, void *);
typedef struct { u8 pad[0x120]; int entries[10]; int count; int active; } EntryGroup;
extern u8 g_barrel_entry_groups[];
typedef struct { u8 header[0x464]; u8 entries[0]; } TriggerTable;
extern TriggerTable g_trigger_l03_flags;
extern u8 g_moby_nibble_table[];
extern int g_current_map_index __attribute__((sda));
typedef struct { unsigned short key; char reserved02[10]; } SelectorRow;
extern SelectorRow g_subtitle_history[];
extern int g_object_group_count;
extern u8 *g_moby_record_base;
extern u16 *g_entity_id_lists[];
extern float g_barrier_piece_speeds[2] __attribute__((sda)), g_barrier_piece_spin[2] __attribute__((sda)), g_barrier_piece_lifetimes[2] __attribute__((sda));
/* A four-state object. State 0 clears the 16 entry groups, then removes the object when its trigger
   entry is set or its 3-bit counter in the level's save bits (high nibble for an odd id, low nibble
   for an even one) is nonzero; otherwise it moves to state 1. State 1 waits for a hit from an object
   of class 0xCFC no lower than half a unit beneath it and sends every entity of its id list to state
   2. States 2 and 3 spawn rows of three explosions at rising heights on a timer, then state 3 raises
   the counter (up to 7), sets subtitle row 60's key to 0xFFFF, scatters the object's pieces and removes it. The row
   pointer is set at the store so the table keeps its own lui/addiu base, as retail has it. */
void endako_exploding_barrier_update(u8 *obj)
{
    u8 *state = *(u8 **)(obj + 0x68);
    u8 pos[16] __attribute__((aligned(16)));
    u8 *hit, *other;
    u16 *p;
    int i, j, index, bits;
    u8 *counter;
    SelectorRow *rows;

    if (!state) {
        moby_mark_spawned(obj);
        return;
    }
    switch (obj[0x20]) {
    case 0: {
        int group;

        for (group = 0; group < 16; group++) {
            for (j = 0; j < ((EntryGroup *)(g_barrel_entry_groups + group * 0x150))->count; j++)
                if (((EntryGroup *)(g_barrel_entry_groups + group * 0x150))->entries[j])
                    ((EntryGroup *)(g_barrel_entry_groups + group * 0x150))->entries[j] = 0;
            ((EntryGroup *)(g_barrel_entry_groups + group * 0x150))->active = 0;
        }
        index = *(s16 *)(obj + 0xB2);
        if (g_trigger_l03_flags.entries[index]) {
            moby_mark_spawned(obj);
        } else {
            bits = g_moby_nibble_table[(index >> 1) + (g_current_map_index << 10)];
            if (*(u16 *)(obj + 0xB2) & 1) {
                if ((bits >> 4) & 7) moby_mark_spawned(obj);
                else moby_set_state(obj, 1, -1);
            } else {
                if (bits & 7) moby_mark_spawned(obj);
                else moby_set_state(obj, 1, -1);
            }
        }
        break;
    }
    case 1:
        hit = part_find_owned_effect_slot(obj, 0x10000, 0);
        if (hit && (other = *(u8 **)(hit + 0x20)) && *(s16 *)(other + 0xAA) == 0xCFC /* moby class 3324 */ &&
            *(float *)(obj + 0x18) <= *(float *)(other + 0x18) + 0.5f) {
            for (p = g_entity_id_lists[obj[0x21]];
                 obj[0x21] != 0xFF && obj[0x21] <= g_object_group_count && p != 0 &&
                 ((p != 0 && (s16)p[-1] >= 0) || p == g_entity_id_lists[obj[0x21]]); p++) {
                other = g_moby_record_base + ((*p & 0x7FFF) << 8);
                if (!other) break;
                moby_set_state(other, 2, -1);
            }
        }
        obj[0xA8] = 0xFF;
        break;
    case 2:
        if (flag_set_first_pending(obj)) {
            *(int *)(state + 4) = 230;
            for (i = -1; i < 2; i++) {
                vec_local_offset_to_world(obj, pos, (float)(i << 3), -6.0f, 5.0f);
                SpawnExplosion(pos, 0, 5, 5, 5, 5, 5, 0, .75f, 20.0f, 0, 0, 0, 0);
            }
            *(int *)(state + 4) = 10;
        } else if (math_fast_float_d(state + 4)) {
            for (i = -1; i < 2; i++) {
                vec_local_offset_to_world(obj, pos, (float)(i << 3), -6.0f, 15.0f);
                SpawnExplosion(pos, 0, 5, 5, 5, 5, 5, 0, .75f, 20.0f, 0, 0, 0, 0);
            }
            *(int *)(state + 4) = 10;
            moby_set_state(obj, 3, -1);
        }
        break;
    case 3:
        if (!math_fast_float_d(state + 4)) break;
        for (i = -1; i < 2; i++) {
            vec_local_offset_to_world(obj, pos, (float)(i << 3), -6.0f, 25.0f);
            SpawnExplosion(pos, 0, 5, 5, 5, 5, 5, 0, .75f, 20.0f, 0, 0, i == 0, 0);
        }
        if (*(u16 *)(obj + 0xB2) & 1) {
            counter = g_moby_nibble_table + ((*(s16 *)(obj + 0xB2) >> 1) + (g_current_map_index << 10));
            if (((*counter >> 4) & 7) != 7) *counter += 16;
        } else {
            counter = g_moby_nibble_table + ((*(s16 *)(obj + 0xB2) >> 1) + (g_current_map_index << 10));
            if ((*counter & 7) != 7) *counter += 1;
        }
        rows = g_subtitle_history;
        rows[60].key = 0xFFFF;
        if (*(int *)state)
            ScatterObjectPieces(obj, g_barrier_piece_lifetimes, g_barrier_piece_spin, g_barrier_piece_speeds,
                              0xFFFF, 0, -1, 1, 0xFFFF, 0xFF, fading_effect_update);
        else
            ScatterObjectPieces(obj, g_barrier_piece_lifetimes, g_barrier_piece_spin, g_barrier_piece_speeds,
                              0xFFFF, 0, -1, 1, 0xFFFF, 0xFF, 0);
        moby_mark_spawned(obj);
        break;
    }
}

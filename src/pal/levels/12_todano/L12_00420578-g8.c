#include "include_asm.h"

#include "common.h"
typedef unsigned int u128 __attribute__((mode(TI), aligned(16)));
typedef struct {
    float axis0[4], axis1[4], axis2[4], position[4];
    u8 pad40[0x30];
    float rotation[4];
} BeamVolume;
typedef struct {
    int index;
    float phase;
    u8 *objects[2];
    float start[4], end[4];
    float f30;
    float heights[3];
    float width, length;
    int sound;
} BeamState;
extern struct { u8 pad[0x464]; u8 flags[0]; } g_object_flags;
extern u8 g_moby_nibble_table[], g_hero_position[], g_line_end_point[], g_sound_state[];
extern BeamVolume *g_path_waypoint_table MACRO_ADDR;
extern int g_current_map_index MACRO_ADDR;
extern u8 *g_tracked_object_ptr MACRO_ADDR;
extern u8 *g_second_tracked_object MACRO_ADDR;
extern float g_sweeping_beam_offset[] MACRO_ADDR;
extern float D_L12_001B1D00_gp[] SDATA(D_L12_001B1D00);
extern float D_L12_001B1D10_gp[] SDATA(D_L12_001B1D10);
extern u8 *g_hero_moby NOT_SDA;
extern u8 g_sweeping_beam_draw_callback[];
extern void helper_clear_states(u8 *), beam_restore_child_collision(u8 *), helper_push_objects(u8 *);
extern void moby_mark_spawned(void *);
extern float math_random_float_range(float, float), FastVecLength(void *), math_fabs(float);
extern void FastVecSub(void *, void *, void *), FastVecAdd(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern int CollLine(void *, void *, int, void *, int);
extern u8 *CreateMoby(int);
extern void moby_init_child_from_parent(void *, void *), euler_rotation_basis(void *, void *), matrix_from_basis_rows(void *, void *);
extern void func_002A0F48(void *), matrix_mul_vec3(void *, void *, void *);
extern int PlayMobySound(int, int, void *);
extern void snd_stop_voice(int);
extern int IsPointInCuboid(void *, int), tracked_object_is_open(void), tracked_moby_is_active(void), second_tracked_object_is_open(void);
extern void make_hit_descriptor(void *, void *, int, void *, float), QueueMobyImpact(void *, void *);
extern void tracked_moby_set_state_pal(int, int), global_object_start_pal(int, int), gfx_add_draw_callback_first(void *, void *);

/* Runs a beam that sweeps through its volume. It hurts the hero and the buddy when they stand in it, and plays a humming sound while the way is clear (PAL: 50 Hz timings). */
void sweeping_beam_update_pal(u8 *self)
{
    float start[4], end[4], delta[4], local[4];
    float matrix[12], inverse[16];
    u8 event[48];
    BeamState *state = *(BeamState **)(self + 0x68);

    helper_clear_states(self);
    switch (self[0x20]) {
    case 0: {
        u16 id = *(u16 *)(self + 0xB2);
        int i;

        if (g_object_flags.flags[(s16)id])
            goto Destroy;
        {
            int packed = g_moby_nibble_table[((s16)id >> 1) + (g_current_map_index << 10)];

            if (id & 1) {
                if ((packed >> 4) & 7)
                    goto Destroy;
            } else if (packed & 7) {
Destroy:
                moby_mark_spawned(self);
                return;
            }
        }
        state->sound = -1;
        self[0x20] = 1;
        state->phase = math_random_float_range(0.0f, 1.0f);
        state->f30 = -10.0f;
        {
            float length = FastVecLength(g_path_waypoint_table[state->index].axis1);

            state->width = length + length;
            length = FastVecLength(g_path_waypoint_table[state->index].axis2);
            state->length = length + length;
        }
        FastVecSub(state->start, g_path_waypoint_table[state->index].position, g_path_waypoint_table[state->index].axis1);
        FastVecAdd(state->end, g_path_waypoint_table[state->index].position, g_path_waypoint_table[state->index].axis1);
        {
            BeamVolume *volumes = g_path_waypoint_table;
            BeamVolume *volume = (BeamVolume *)((u32)(state->index << 7) + (u32)volumes);

            state->start[2] += 1.5f - volume->axis2[2];
            state->end[2] += 1.5f - volume->axis2[2];
            qcopy(end, volume->position);
            end[2] += 1.5f;
            vec_scale_to_length(start, volumes[state->index].axis1, 0.1f);
        }
        while (CollLine(state->start, end, 2, 0, 0))
            FastVecAdd(state->start, state->start, start);
        while (CollLine(state->end, end, 2, 0, 0))
            FastVecSub(state->end, state->end, start);
        for (i = 0; i < 2; i++) {
            u8 *obj;

            if (g_path_waypoint_table[state->index].axis2[2] < 2.0f && i > 0)
                continue;
            obj = CreateMoby(0xFDF);
            if (obj) {
                moby_init_child_from_parent(obj, self);
                qcopy(obj + 0xF0, g_path_waypoint_table[state->index].rotation);
                euler_rotation_basis(obj + 0xC0, obj + 0xF0);
                obj[0x31] = 0;
                *(u16 *)(obj + 0x34) |= 0x105;
                *(u128 *)local = 0;
                local[1] = -1.0f;
                local[2] = -1.0f;
                matrix_mul_vec3(delta, local, &g_path_waypoint_table[state->index]);
                FastVecAdd(obj + 0x10, delta, g_path_waypoint_table[state->index].position);
                *(float *)(obj + 0x18) += i * 3.0f;
                func_002A0F48(obj);
                {
                    float radius = *(float *)(*(u8 **)(obj + 0x24) + 0x3C);

                    *(float *)(obj + 0xC) = radius + radius;
                }
            }
            state->objects[i] = obj;
        }
        return;
    }
    case 1:
        break;
    default:
        return;
    }
    state->phase += 0.010000001f;
    if (state->phase > 1.0f)
        state->phase -= 1.0f;
    {
        float height = state->width * 0.5f;

        state->heights[0] = state->heights[1] = state->heights[2] = height;
        euler_rotation_basis(matrix, g_path_waypoint_table[state->index].rotation);
    }
    matrix_from_basis_rows(inverse, matrix);
    qcopy(start, state->start);
    qcopy(end, state->end);
    {
        int clear = 1;
        int j = 0;

        do {
            if (!CollLine(start, end, 2, 0, 0))
                break;
            FastVecSub(delta, g_line_end_point, g_path_waypoint_table[state->index].position);
            matrix_mul_vec3(delta, delta, inverse);
            if (state->heights[j] - delta[1] > 1.5f) {
                u16 id = *(u16 *)(self + 0xB2);

                if (id & 1) {
                    u8 *counter = (u8 *)(((s16)id >> 1) + (g_current_map_index << 10)) + (int)g_moby_nibble_table;
                    u8 packed = *counter;

                    if (((packed >> 4) & 7) != 7)
                        *counter = packed + 16;
                } else {
                    u8 *counter = (u8 *)(((s16)id >> 1) + (g_current_map_index << 10)) + (int)g_moby_nibble_table;
                    u8 packed = *counter;

                    if ((packed & 7) != 7)
                        *counter = packed + 1;
                }
                clear = 0;
            }
            state->heights[j] = delta[1];
            start[2] += 2.0f;
            end[2] += 2.0f;
            j++;
        } while (j < 3);
        if (clear) {
            u8 *sound = g_sound_state + state->sound * 0x70;

            if (*(u8 **)(sound + 0x88) != self || !sound[0x74])
                state->sound = PlayMobySound(1, 4, self);
        } else {
            int id = state->sound;

            if (id != -1) {
                u8 *sound = g_sound_state + id * 0x70;

                if (*(u8 **)(sound + 0x88) == self && sound[0x74])
                    snd_stop_voice(id);
            }
            state->sound = -1;
        }
    }
    {
        u8 *query = g_hero_position;
        float height, probe_z;
        float *pos;

        if (IsPointInCuboid(query, state->index)) {
            probe_z = *(float *)(query + 8);
            if (state->start[2] + 4.0f <= probe_z)
                height = state->heights[2];
            else if (state->start[2] + 1.0f <= probe_z)
                height = state->heights[1];
            else
                height = state->heights[0];
            FastVecSub(delta, g_hero_position, g_path_waypoint_table[state->index].position);
            matrix_mul_vec3(delta, delta, inverse);
            if (delta[1] < height && delta[0] <= D_L12_001B1D10_gp[0]) {
                beam_restore_child_collision(self);
                if (delta[0] >= 0.0f) {
                    matrix_mul_vec3(local, D_L12_001B1D00_gp, matrix);
                    pos = local;
                } else {
                    D_L12_001B1D00_gp[0] = -0.5f;
                    g_sweeping_beam_offset[2] = -1.0f;
                    matrix_mul_vec3(local, D_L12_001B1D00_gp, matrix);
                    pos = local;
                    D_L12_001B1D00_gp[0] = 3.0f;
                    g_sweeping_beam_offset[2] = -3.0f;
                }
                make_hit_descriptor(event, self, 0x10001, pos, 2.0f);
                QueueMobyImpact(g_hero_moby, event);
            } else if (delta[1] < height) {
                beam_restore_child_collision(self);
            }
        } else if (IsPointInCuboid(query + 0x60, state->index)) {
            probe_z = *(float *)(query + 0x68);
            if (state->start[2] + 4.0f <= probe_z)
                height = state->heights[2];
            else if (state->start[2] + 1.0f <= probe_z)
                height = state->heights[1];
            else
                height = state->heights[0];
            FastVecSub(delta, g_hero_position + 0x60, g_path_waypoint_table[state->index].position);
            matrix_mul_vec3(delta, delta, inverse);
            if (delta[1] < height) {
                beam_restore_child_collision(self);
                if (delta[0] >= 0.0f) {
                    matrix_mul_vec3(local, D_L12_001B1D00_gp, matrix);
                    pos = local;
                } else {
                    D_L12_001B1D00_gp[0] = -0.5f;
                    g_sweeping_beam_offset[2] = -1.0f;
                    matrix_mul_vec3(local, D_L12_001B1D00_gp, matrix);
                    pos = local;
                    D_L12_001B1D00_gp[0] = 3.0f;
                    g_sweeping_beam_offset[2] = -3.0f;
                }
                make_hit_descriptor(event, self, 0x10001, pos, 2.0f);
                QueueMobyImpact(g_hero_moby, event);
            }
        }
    }
    if (tracked_object_is_open() && !tracked_moby_is_active()) {
        u8 *candidate = g_tracked_object_ptr;

        qcopy(delta, candidate + 0x10);
        if (math_fabs(*(float *)(candidate + 0x18) - g_path_waypoint_table[state->index].position[2]) < 2.0f)
            delta[2] = g_path_waypoint_table[state->index].position[2];
        if (IsPointInCuboid(delta, state->index))
            tracked_moby_set_state_pal(1, -1);
    }
    if (second_tracked_object_is_open()) {
        u8 *candidate = g_second_tracked_object;

        qcopy(delta, candidate + 0x10);
        if (math_fabs(*(float *)(candidate + 0x18) - g_path_waypoint_table[state->index].position[2]) < 2.0f)
            delta[2] = g_path_waypoint_table[state->index].position[2];
        if (IsPointInCuboid(delta, state->index))
            global_object_start_pal(1, -1);
    }
    gfx_add_draw_callback_first(g_sweeping_beam_draw_callback, self);
    helper_push_objects(self);
}

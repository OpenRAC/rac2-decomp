#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; struct { f32 x, y, z, w; } f; } V;
typedef struct { V rows[8]; } Transform;

/* The moby's variables (at +0x68). */
typedef struct {
    s32 transform;          /* 0x00: index into D_L12_001B2F8C[0] */
    u8 pad04[0x34 - 0x04];
    f32 depth;              /* 0x34 */
    u8 pad38[0x48 - 0x38];
    s32 base;               /* 0x48 */
    s32 hit;                /* 0x4C */
    s32 done;               /* 0x50 */
    u8 pad54[0x58 - 0x54];
    s32 other;              /* 0x58 */
    s32 mode;               /* 0x5C */
} Vars7CA8;

typedef struct {
    u8 pad00[0x10];
    V position;             /* 0x10 */
    u8 state;               /* 0x20 */
    u8 pad21[0x68 - 0x21];
    Vars7CA8 *vars;         /* 0x68 */
    u8 pad6C[0xB2 - 0x6C];
    u16 uid;                /* 0xB2 */
    u8 padB4[0xF0 - 0xB4];
    V rotation;             /* 0xF0 */
} Moby7CA8;

typedef struct { u8 pad[0x18]; u8 *hit; s32 count; V point; } Collision;
typedef struct { u8 pad[0x464]; u8 collected[0]; } LevelSaveState;

extern Transform *g_path_waypoint_table[] __attribute__((sda));
extern Transform *D_L12_001B2F8C_gp SDATA(D_L12_001B2F8C) __attribute__((sda));
extern u8 *g_tracked_object_ptr[] __attribute__((sda));
extern V g_hero_position NOT_SDA;
extern LevelSaveState g_object_flags;
extern Collision g_collision_l12_result;
extern u8 g_moby_nibble_table[];
extern s32 g_current_map_index[] __attribute__((sda));
extern s32 D_001A79F0_gp SDATA(D_001A79F0) __attribute__((sda));
extern s32 g_player_stats[] __attribute__((sda));
extern void *g_hero_moby NOT_SDA;
extern f32 g_barrier_depth_margin_back __attribute__((sda));
extern f32 g_barrier_depth_margin_front __attribute__((sda));
extern f32 g_barrier_point_z_offset __attribute__((sda));
extern f32 g_barrier_push_strength __attribute__((sda));
extern V g_barrier_hit_local_point __attribute__((sda));

extern void moby_set_state(void *, s32, s32);
extern void matrix_mul_vec3(void *, void *, void *);
extern void euler_rotation_basis(void *, void *);
extern void matrix_from_basis_rows(void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void transform_vector(void *, void *, void *);
extern f32 FastVecLength(void *);
extern f32 math_fabs(f32);
extern s32 CollLine(void *, void *, s32, void *, void *);
extern s32 IsPointInCuboid(void *, s32);
extern int moby_transform_point_and_rotation_by_parent(void *, void *, void *, void *, void *, void *);
extern void FastVecScale(void *, void *, f32);
extern void make_hit_descriptor(void *, void *, s32, void *, f32);
extern void QueueMobyImpact(void *, void *);
extern s32 tracked_object_is_open(void);
extern s32 tracked_moby_is_active(void);
extern void tracked_moby_set_state(s32, s32);
extern void gfx_add_draw_callback_first(void *, void *);
extern void gfx_draw_barrier_field_strips(void);

/* Updates a barrier field. It checks how deep the hero has pushed into it, knocks the hero back, and counts progress when the end is reached. */
void barrier_field_update(Moby7CA8 *self)
{
    V offset, direction, rotation[3], matrix[4], hit, ray_start, ray_end, push_dir, point, normal, tmp;
    u8 impulse[0x30] __attribute__((aligned(16)));
    Vars7CA8 *vars = self->vars;
    f32 length;
    s32 index;
    u16 rawIndex;

    switch (self->state) {
    case 0:
        rawIndex = self->uid;
        index = (s16)rawIndex;
        if (g_object_flags.collected[index])
            goto active;
        {
            /* One 3-bit count per nibble; the low bit of the id picks the nibble. */
            s32 bits = g_moby_nibble_table[(index >> 1) + (g_current_map_index[0] << 10)];
            if (rawIndex & 1) {
                if ((bits >> 4) & 7)
                    goto active;
                moby_set_state(self, 1, -1);
            } else {
                if (bits & 7) {
active:
                    moby_set_state(self, 2, -1);
                } else {
                    moby_set_state(self, 1, -1);
                }
            }
        }
        break;
    case 1:
        direction.q = 0;
        direction.f.z = 1;
        direction.f.w = 1;
        matrix_mul_vec3(&direction, &direction, &g_path_waypoint_table[0][vars->transform]);
        length = FastVecLength(&direction);
        {
            V *transform = &g_path_waypoint_table[0][vars->transform].rows[7];
            vars->depth = 1;
            euler_rotation_basis(rotation, transform);
        }
        matrix_from_basis_rows(matrix, rotation);
        matrix_mul_vec3(&hit, &g_barrier_hit_local_point, &g_path_waypoint_table[0][vars->base].rows[4]);
        ray_start.q = 0;
        ray_end.q = 0;
        ray_start.f.x = 1;
        ray_start.f.w = 1;
        ray_end.f.x = 1;
        ray_end.f.w = 1;
        FastVecAdd(&ray_start, &ray_start, &hit);
        matrix_mul_vec3(&ray_start, &ray_start, &g_path_waypoint_table[0][vars->base]);
        FastVecSub(&ray_end, &g_path_waypoint_table[0][vars->base].rows[3], &ray_start);
        FastVecAdd(&ray_start, &g_path_waypoint_table[0][vars->base].rows[3], &ray_start);
        ray_start.f.z += 2.5f;
        ray_end.f.z += 2.5f;
        vars->hit = 0;
        push_dir.q = 0;
        if (CollLine(&ray_start, &ray_end, 0x12, 0, 0)) {
            V *collision = &g_collision_l12_result.point;
            V *transform = &g_path_waypoint_table[0][vars->transform].rows[3];
            vars->hit = 1;
            FastVecSub(&offset, collision, transform);
            transform_vector(&offset, &offset, matrix);
            {
                f32 numerator = -offset.f.z;
                f32 denominator = -length;
                vars->depth = numerator / denominator;
            }
            if (*(s16 *)(g_collision_l12_result.hit + 0xAA) == 0xFC4 /* moby class 4036 */) {
                moby_transform_point_and_rotation_by_parent(self, g_collision_l12_result.hit, &self->position, &self->rotation, &point, &normal);
                point.f.z = 0;
                FastVecSub(&tmp, &point, &self->position);
                point.q = tmp.q;
                point.f.z = 0;
                qcopy(&push_dir, &point);
                FastVecScale(&push_dir, &push_dir, g_barrier_push_strength);
            }
        }
        qcopy(&point, &g_hero_position);
        point.f.z += g_barrier_point_z_offset;
        if (IsPointInCuboid(&point, vars->transform)) {
            FastVecSub(&offset, &g_hero_position, &g_path_waypoint_table[0][vars->transform].rows[3]);
            transform_vector(&offset, &offset, matrix);
            offset.f.z = -offset.f.z / -length;
            if (offset.f.z < vars->depth - (g_barrier_depth_margin_back / length) * 1.5f ||
                offset.f.z >= vars->depth + (g_barrier_depth_margin_front / length) * 0.5f ||
                !vars->hit || vars->mode == 1) {
                normal.q = 0;
                normal.f.z = -3;
                FastVecSub(&normal, &normal, &push_dir);
                make_hit_descriptor(&impulse, self, 0x10001, &normal, (f32)(g_player_stats[0] / 2));
                QueueMobyImpact(g_hero_moby, &impulse);
            }
        }
        point.f.z = g_path_waypoint_table[0][vars->transform].rows[3].f.z;
        if (IsPointInCuboid(&point, vars->transform)) {
            FastVecSub(&offset, &point, &g_path_waypoint_table[0][vars->transform].rows[3]);
            transform_vector(&offset, &offset, matrix);
            {
                f32 numerator = -offset.f.z;
                f32 denominator = -length;
                offset.f.z = numerator / denominator;
            }
            if (math_fabs(offset.f.z + 1) < 0.01f && !vars->done) {
                u16 uid;
                vars->done = 1;
                uid = self->uid;
                if (uid & 1) {
                    s32 tableIndex = ((s16)uid >> 1) + (D_001A79F0_gp << 10);
                    if (((g_moby_nibble_table[tableIndex] >> 4) & 7) != 7)
                        g_moby_nibble_table[tableIndex] += 16;
                } else {
                    s32 tableIndex = ((s16)uid >> 1) + (D_001A79F0_gp << 10);
                    if ((g_moby_nibble_table[tableIndex] & 7) != 7)
                        ++g_moby_nibble_table[tableIndex];
                }
            }
        }
        if (vars->other != -1 && IsPointInCuboid(&point, vars->other) && !vars->done) {
            u16 uid;
            vars->done = 1;
            uid = self->uid;
            if (uid & 1) {
                s32 tableIndex = ((s16)uid >> 1) + (D_001A79F0_gp << 10);
                if (((g_moby_nibble_table[tableIndex] >> 4) & 7) != 7)
                    g_moby_nibble_table[tableIndex] += 16;
            } else {
                s32 tableIndex = ((s16)uid >> 1) + (D_001A79F0_gp << 10);
                if ((g_moby_nibble_table[tableIndex] & 7) != 7)
                    ++g_moby_nibble_table[tableIndex];
            }
        }
        if (tracked_object_is_open() && !tracked_moby_is_active()) {
            u8 *player = g_tracked_object_ptr[0];
            qcopy_nc(&normal, player + 0x10);
            if (math_fabs(*(f32 *)(player + 0x18) - g_path_waypoint_table[0][vars->transform].rows[3].f.z) < 2)
                normal.f.z = D_L12_001B2F8C_gp[vars->transform].rows[3].f.z;
            if (IsPointInCuboid(&normal, vars->transform))
                tracked_moby_set_state(1, -1);
        }
        gfx_add_draw_callback_first(gfx_draw_barrier_field_strips, self);
        break;
    }
}

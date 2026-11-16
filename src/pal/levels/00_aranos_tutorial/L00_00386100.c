#include "include_asm.h"

#include "common.h"
typedef unsigned int LaunchQuad __attribute__((mode(TI)));
typedef union {
    LaunchQuad q;
    float f[4];
} LaunchVec;
typedef struct {
    int count;
    char pad04[12];
    LaunchVec points[0];
} AranosLaunchPath;
typedef struct {
    char pad00[0x30];
    LaunchVec position;
    char pad40[0x30];
    LaunchVec rotation;
} AranosLaunchPose;
typedef struct LaunchMoby LaunchMoby;
typedef struct {
    int flag;
    int pose;
    int cue;
    char pad0C[4];
    int target;
    int pathIndex;
    LaunchMoby *child;
    float speed;
    int pointIndex;
} AranosLaunchCtx;
struct LaunchMoby {
    char pad00[0x10];
    LaunchVec position;
    unsigned char state;
    char pad21[0xF];
    unsigned char f30;
    char pad31;
    short f32;
    unsigned short flags;
    char pad36[0x32];
    AranosLaunchCtx *ctx;
    char pad6C[0x29];
    unsigned char f95;
    unsigned short timer;
    int f98;
    char pad9C[0x24];
    char matrix[0x30];
    LaunchVec rotation;
};
typedef struct {
    char pad00[0x80];
    char flagBits[0x2214];
    int state;
    char pad2298[0x234];
    int count;
} AranosLaunchHero;
extern AranosLaunchPose *g_aranos_launch_poses __attribute__((sda));
extern AranosLaunchPath *g_launch_path_table[];
extern LaunchMoby *g_launch_moby_list[];
extern int g_aranos_launch_state __attribute__((sda));
extern int g_frame_l00_counter __attribute__((sda));
extern int g_game_l00_mode __attribute__((sda));
extern int g_effect_table_base;
extern unsigned int g_progress_flags_c[];
extern unsigned int g_save_menu_flags __attribute__((sda));
extern float g_hero_scalar_transition_value __attribute__((sda));
extern float g_scene_vector[4] __attribute__((sda));
extern char g_request_l00_queue[];
extern char g_str_aranos_launch_message[];
extern AranosLaunchHero g_hero_state;
extern int game_is_either_mode_two(void);
extern int flag_is_byte_set(void);
extern int flag_set_first_pending(void *);
extern int cam_is_trigger_ready(int);
extern int hero_get_target_state_kind(void);
extern int MemcardSave(int, int);
extern int IsPointInCuboid(char *, unsigned int);
extern void hero_reset_position_and_direction_pal(void *, void *, int, int);
extern void SpawnEquipmentPieces(void *);
extern void cam_lock_entry(int);
extern void moby_set_state(void *, int, int);
extern void part_init_effect_table(int);
extern void moby_mark_flag_and_append_to_list(int);
extern void state_set_flag_one(void);
extern void moby_init_child_from_parent(void *, void *);
extern LaunchMoby *CreateMoby(int);
extern int req_push_queue(void *, int);
extern int req_launch_queued(void *);
extern int snd_start_in_slot(int, int, int);
extern void STUB_printf(const char *, ...);
extern float mat_fast_helper_a(float, float);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float vec_distance_xy(void *, void *);
extern void euler_rotation_basis(char *, char *);
extern void game_set_slowdown_factor_pal(void);
extern void gfx_add_draw_callback_first(void (*)(void *), void *);
extern void gfx_draw_object_multi_pass(void *);
extern void FastVecAdd(void *, void *, void *);
extern void hero_start_target_state(void *, int, float);
extern void cam_reset_entry(int);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void SnapMobyListToParent(void *);

/* State machine for the launch object: drives its child along a path, then hands off to the next state. */
void aranos_launch_update_pal(LaunchMoby *obj) {
    LaunchVec offset;
    AranosLaunchCtx *ctx = obj->ctx;
    AranosLaunchPath *path;
    int i;
    float angle;

    switch (obj->state) {
    case 0: {
        LaunchMoby *child;
        AranosLaunchPath *initialPath;

        if (flag_is_byte_set())
            moby_mark_flag_and_append_to_list(0x18);
        state_set_flag_one();
        if (ctx->pose != -1)
            hero_reset_position_and_direction_pal(&g_aranos_launch_poses[ctx->pose].position, &g_aranos_launch_poses[ctx->pose].rotation, 0, 1);
        moby_init_child_from_parent(ctx->child = CreateMoby(0xD54), obj);
        initialPath = g_launch_path_table[ctx->pathIndex];
        /* The copies write only the child position, so the no-clobber form is enough. */
        qcopy_nc(&ctx->child->position, &initialPath->points[0]);
        SpawnEquipmentPieces(ctx->child);
        child = ctx->child;
        qcopy_nc(&child->position, &initialPath->points[0]);
        child->f32 = 0x28F;
        ctx->child->rotation.f[2] = mat_fast_helper_a(initialPath->points[1].f[0] - obj->position.f[0],
                                                  initialPath->points[1].f[1] - obj->position.f[1]);
        euler_rotation_basis(ctx->child->matrix, (char *)&ctx->child->rotation);
        ctx->pointIndex = 0;
        obj->f30 = 0xFF;
        if (!(g_progress_flags_c[0] & 2) && g_hero_state.state != 0x1C && g_hero_state.count > 0 && !g_game_l00_mode &&
            (ctx->flag == -1 || IsPointInCuboid(g_hero_state.flagBits, ctx->flag))) {
            req_push_queue(g_request_l00_queue, 0x21);
            req_launch_queued(g_request_l00_queue);
            if (g_frame_l00_counter < 5)
                game_set_slowdown_factor_pal();
            moby_set_state(obj, 1, -1);
        } else {
            moby_set_state(obj, 4, -1);
        }
        break;
    }
    case 1:
        if (!game_is_either_mode_two()) {
            if (ctx->pose != -1)
                hero_reset_position_and_direction_pal(&g_aranos_launch_poses[ctx->pose].position, &g_aranos_launch_poses[ctx->pose].rotation, 0, 1);
            SpawnEquipmentPieces(ctx->child);
            cam_lock_entry(ctx->cue);
            g_aranos_launch_state = 0;
            g_hero_scalar_transition_value = 1.5f;
            moby_set_state(obj, 2, -1);
            part_init_effect_table(g_effect_table_base + 0xF0000);
        }
        break;
    case 2:
        if (flag_set_first_pending(obj)) {
            snd_start_in_slot(0x17, 0, 0);
            g_aranos_launch_state = 0;
        }
        angle = FastAddRotations(ctx->child->rotation.f[2], 3.1415927f);
        g_scene_vector[0] = math_fast_sin_or_cos_a(angle) * 0.6f;
        g_scene_vector[1] = math_fast_sin_or_cos_b(angle) * 0.6f;
        g_scene_vector[2] = 0.0f;
        ctx->child->f95 = 0xFF;
        gfx_add_draw_callback_first(gfx_draw_object_multi_pass, ctx->child);
        ++obj->timer;
        if (obj->timer > 10 && cam_is_trigger_ready(ctx->cue)) {
            AranosLaunchPose *poses;

            STUB_printf(g_str_aranos_launch_message);
            poses = g_aranos_launch_poses;
            ctx->child->flags |= 0x41;
            ctx->child->flags &= 0xEFFF;
            ctx->child->f98 = 0;
            offset.f[0] = math_fast_sin_or_cos_a(poses[ctx->pose].rotation.f[2]);
            offset.f[0] += offset.f[0];
            offset.f[1] = math_fast_sin_or_cos_b(g_aranos_launch_poses[ctx->pose].rotation.f[2]);
            offset.f[1] += offset.f[1];
            offset.f[2] = 0;
            FastVecAdd(&offset, &offset, &g_aranos_launch_poses[ctx->pose].position);
            hero_start_target_state(&offset, 1, g_aranos_launch_poses[ctx->pose].rotation.f[2]);
            cam_reset_entry(ctx->target);
            g_aranos_launch_state = 2;
            moby_set_state(obj, 4, -1);
        }
        path = g_launch_path_table[ctx->pathIndex];
        if (vec_distance_xy(&ctx->child->position, &path->points[ctx->pointIndex]) < 0.75f)
            ++ctx->pointIndex;
        if (path->count - 1 < ctx->pointIndex)
            ctx->pointIndex = path->count - 1;
        FastVecSub(&offset, &path->points[ctx->pointIndex], &ctx->child->position);
        vec_scale_to_length(&offset, &offset, ctx->speed * 0.020000001f);
        FastVecAdd(&ctx->child->position, &ctx->child->position, &offset);
        break;
    case 4:
        if (flag_set_first_pending(obj)) {
            int target = ctx->target;

            g_aranos_launch_state = 2;
            cam_reset_entry(target);
        }
        if (!hero_get_target_state_kind()) {
            if (MemcardSave(1, -1))
                g_save_menu_flags |= 0x200;
            moby_set_state(obj, 5, -1);
        }
        break;
    }

    if (obj->state != 4 && obj->state != 5) {
        path = g_launch_path_table[ctx->pathIndex];
        SnapMobyListToParent(ctx->child);
        ctx->child->rotation.f[2] = mat_fast_helper_a(path->points[1].f[0] - ctx->child->position.f[0],
                                                  path->points[1].f[1] - ctx->child->position.f[1]);
        euler_rotation_basis(ctx->child->matrix, (char *)&ctx->child->rotation);
    } else {
        i = 0;
        while (g_launch_moby_list[i]) {
            g_launch_moby_list[i]->flags |= 0x41;
            g_launch_moby_list[i]->flags &= 0xEFFF;
            g_launch_moby_list[i]->f98 = 0;
            ++i;
        }
    }
}


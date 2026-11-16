#include "names.h"
/* func_PAL_L00_0040E9F0, the PAL copy of func_L00_00409E48: the same C, where 1.0f / 60.0f becomes
   0.020000001f; 300 becomes 250. */
#include "common.h"

typedef int Quadword __attribute__((mode(TI)));
typedef float Vector[4] __attribute__((aligned(16)));

extern char *CreateMoby(int);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern int CollLine(void *, void *, int, void *, int);
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern float math_random_angle(void);
extern char *moby_get_private_value_0(void *);
extern void moby_get_offset_point(void *, void *);
extern void func_002A0F48(void *);
extern void AddMobyToIndexList(void *, void *, int);
extern int part_alloc_effect_slot(void *, int, float, float, float);

extern int g_shot_record_next_index __attribute__((sda));
extern unsigned char g_targeted_weapon_index __attribute__((nosda));

typedef struct ScaleRecord {
    char pad00[0x50];
    float value;
    char pad54[0x8c];
} ScaleRecord;
extern ScaleRecord g_weapon_l00_table[];

typedef struct ProjectileState {
    /* 0x00 */ float last_target[3];
    /* 0x0C */ void *owner;
    /* 0x10 */ void *target;
    /* 0x14 */ float height;
    /* 0x18 */ float speed;
    /* 0x1C */ float yaw;
    /* 0x20 */ float spin_speed;
    /* 0x24 */ short life;
    /* 0x26 */ unsigned char homing;
    /* 0x27 */ unsigned char age;
    /* 0x28 */ float spin;
    /* 0x2C */ int index;
    /* 0x30 */ Vector forward;
    /* 0x40 */ Vector color;
    /* 0x50 */ int sound;
    /* 0x54 */ int handle;
} ProjectileState;

typedef struct ProjectileObject {
    /* 0x00 */ char pad00[0x10];
    /* 0x10 */ Vector position;
    /* 0x20 */ signed char status;
    /* 0x21 */ char pad21[0x0b];
    /* 0x2C */ float radius;
    /* 0x30 */ unsigned char alpha;
    /* 0x31 */ signed char enabled;
    /* 0x32 */ short color;
    /* 0x34 */ unsigned short flags;
    /* 0x36 */ char pad36[0x32];
    /* 0x68 */ ProjectileState *state;
    /* 0x6C */ char pad6c[0x50];
    /* 0xBC */ unsigned char hit;
    /* 0xBD */ char padbd[3];
    /* 0xC0 */ Vector forward;
    /* 0xD0 */ Vector right;
    /* 0xE0 */ Vector up;
} ProjectileObject;

typedef struct PlayerState {
    /* 0x0000 */ char pad0000[0x750];
    /* 0x0750 */ Vector up;
    /* 0x0760 */ Vector forward;
    /* 0x0770 */ char pad0770[0x1b20];
    /* 0x2290 */ char *object;
    /* 0x2294 */ int mode;
    /* 0x2298 */ char pad2298[0x254];
    /* 0x24EC */ short orientation;
} PlayerState;
extern PlayerState g_hero_state;

extern Vector g_cam_follow_matrix[3];   /* camera basis rows */
extern float g_camera_l00_position[4];    /* camera position */
extern float g_hero_l00_position[4];    /* collision hit point */
extern char g_shot_history_points[];
extern char g_homing_moby_index_list[] MACRO_ADDR;

/* Spawns a projectile (moby 0xED7) from owner at position, aimed at target or along the view. */
char *aimed_projectile_spawn_pal(char *owner, void *position, char *target, void *color, float height)
{
    Vector aim, offset, side_offset, forward_offset, trace_end, trace_direction;
    ProjectileObject *projectile = (ProjectileObject *)CreateMoby(0xed7);
    ProjectileState *state;
    char *target_vars;
    float scale;

    if (projectile) {
        projectile->alpha = 255;
        projectile->enabled = 1;
        projectile->status = 0;
        projectile->color = 255;
        projectile->flags |= 0x100;
        state = projectile->state;
        state->sound = -1;
        if ((unsigned)g_shot_record_next_index > 32)
            g_shot_record_next_index = 0;
        state->index = g_shot_record_next_index;
        g_shot_record_next_index = (g_shot_record_next_index + 1) % 32;
        scale = (g_weapon_l00_table + g_targeted_weapon_index)->value * (0.020000001f);
        qcopy(projectile->position, position);
        if (target) {
            FastVecScale(offset, target + 0xe0, height);
            FastVecAdd(aim, target + 0x10, offset);
        } else {
            qzero(aim);
        }

        if (g_hero_state.mode == 29) {
            qcopy(projectile->forward, g_cam_follow_matrix[0]);
            qcopy(projectile->right, g_cam_follow_matrix[1]);
            qcopy(projectile->up, g_cam_follow_matrix[2]);
            qcopy(projectile->position, g_camera_l00_position);
            FastVecScale(offset, g_cam_follow_matrix[2], -0.2f);
            FastVecAdd(projectile->position, projectile->position, offset);
            FastVecScale(side_offset, g_cam_follow_matrix[1], -0.25f);
            FastVecAdd(projectile->position, projectile->position, side_offset);
            FastVecScale(forward_offset, g_cam_follow_matrix[0], 0.0f);
            FastVecAdd(projectile->position, projectile->position, forward_offset);
            if (target) {
                FastVecSub(projectile->forward, aim, projectile->position);
                vec_scale_to_length(projectile->forward, projectile->forward, 1.0f);
                FastVecCross(projectile->right, projectile->forward, g_hero_state.object + 0xe0);
                vec_scale_to_length(projectile->right, projectile->right, 1.0f);
                FastVecCross(projectile->up, projectile->right, projectile->forward);
            } else {
                FastVecScale(trace_end, g_cam_follow_matrix[0], 30.0f);
                FastVecAdd(trace_end, g_camera_l00_position, trace_end);
                if (CollLine(g_camera_l00_position, trace_end, 0, g_hero_state.object, 0))
                    qcopy(trace_end, g_hero_l00_position);
                FastVecSub(trace_direction, trace_end, projectile->position);
                vec_scale_to_length(projectile->forward, trace_direction, 1.0f);
                FastVecCross(projectile->right, projectile->forward, g_hero_state.object + 0xe0);
                vec_scale_to_length(projectile->right, projectile->right, 1.0f);
                FastVecCross(projectile->up, projectile->right, projectile->forward);
            }
        } else if (g_hero_state.orientation == 1) {
            vec_scale_to_length(projectile->forward, owner + 0xd0, -1.0f);
            FastVecScale(projectile->right, owner + 0xc0, -1.0f);
            qcopy(projectile->up, owner + 0xe0);
        } else if (target) {
            FastVecSub(projectile->forward, aim, projectile->position);
            vec_scale_to_length(projectile->forward, projectile->forward, 1.0f);
            FastVecCross(projectile->right, projectile->forward, g_hero_state.object + 0xe0);
            vec_scale_to_length(projectile->right, projectile->right, 1.0f);
            FastVecCross(projectile->up, projectile->right, projectile->forward);
        } else {
            qcopy(projectile->forward, g_hero_state.forward);
            FastVecCross(projectile->right, projectile->forward, g_hero_state.up);
            vec_scale_to_length(projectile->right, projectile->right, 1.0f);
            FastVecCross(projectile->up, projectile->right, projectile->forward);
        }
        projectile->forward[3] = projectile->right[3] = projectile->up[3] = 0;

        state->owner = owner;
        state->yaw = math_random_float_range(4.0f, 10.0f);
        if (target)
            state->yaw = 0;
        state->spin_speed = math_random_signed_float_range(6.0f, 10.0f);
        state->speed = scale;
        state->spin = math_random_angle();
        state->target = 0;
        state->age = 1;
        state->homing = 1;
        qcopy(state->forward, projectile->forward);
        qcopy(state->color, color);
        if (target) {
            target_vars = moby_get_private_value_0(target);
            if (target_vars) {
                *(unsigned short *)(target_vars + 0x1e) |= 0x80;
                if (*(unsigned char *)(target_vars + 0xb))
                    state->homing = 0;
            }
        }
        state->life = 250;
        if (target) {
            float *target_position = (float *)(target + 0x10);

            state->last_target[0] = *(float *)(target + 0x10);
            state->last_target[1] = target_position[1];
            state->last_target[2] = target_position[2] + height;
            state->height = height;
        }

        /* Trace from the owner (at the spawn height) to the spawn point. */
        *(Quadword *)offset = *(Quadword *)(owner + 0x10);
        offset[2] = ((float *)position)[2];
        if (CollLine(offset, position, 0, g_hero_state.object, 0)) {
            projectile->hit = 1;
            qcopy(projectile->position, g_hero_l00_position);
        }
        moby_get_offset_point(projectile, g_shot_history_points + state->index * 64);
        func_002A0F48(projectile);
        AddMobyToIndexList(projectile, g_homing_moby_index_list, 31);
        state->handle = part_alloc_effect_slot(projectile, 0, 1.0f, 1.0f, 1.0f);
        projectile->radius *= 2.5f;
    }
    return (char *)projectile;
}

#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern f32 g_barlow_enemy_move_time __attribute__((sda));
extern u8 g_probe_hit[];
extern TI128 g_scratch_direction_quad;
extern f32 mat_fast_helper_a(f32, f32);
extern f32 FastAddRotations(f32, f32);
extern void MobySpringTurn(void *, float *, f32, f32, f32, f32);
extern int FloatToInt(f32);
extern void coll_probe_ahead_of_moby_pal(void *, void *);
extern int path_push_point_away(int, void *, void *, f32);
extern int moby_transform_point_and_rotation_by_parent(void *, void *, void *, void *, void *, void *);
extern f32 coll_probe_ground_height_below(void *, int, f32);
extern char *moby_get_private_value_2(void *);
extern void mat_build_axis_angle_rotation(void *, void *, f32);
typedef struct {
    u8 pad0[0x140]; int steps; f32 time;
    u8 pad148[0x240-0x148]; f32 target[2];
    u8 pad248[0x2f0-0x248]; int channel;
    u8 pad2f4[0x310-0x2f4]; f32 turn, heading;
    u8 pad318[8]; void *ground; f32 velocity;
} D428Data;
typedef struct {
    u8 pad0[0x10]; f32 position[4]; u8 state;
    u8 pad21[0x68-0x21]; D428Data *vars;
    u8 pad6c[0x95-0x6c]; u8 animation;
    u8 pad96[0xf0-0x96]; union { TI128 q; f32 f[4]; } rotation;
} D428Object;

/* Turns the enemy toward its target while it walks and keeps it on the ground each frame, riding moving ground if there is any (PAL). */
void barlow_enemy_update_movement_pal(D428Object *moby) {
    union { TI128 q; f32 f[4]; } angles;
    TI128 rotation;
    D428Data *vars = moby->vars;
    f32 heading, floor;
    if (moby->state == 4) {
        heading = mat_fast_helper_a(vars->target[0] - moby->position[0],
                               vars->target[1] - moby->position[1]);
        heading = FastAddRotations(heading, vars->heading);
        MobySpringTurn(moby, &vars->turn, heading, 0.05f, 0.3f, 0.12566373f);
        vars->steps = FloatToInt(g_barlow_enemy_move_time * 1024.0f);
        vars->time = g_barlow_enemy_move_time;
        coll_probe_ahead_of_moby_pal(moby, &vars->steps);
        if (vars->channel != -1)
            path_push_point_away(vars->channel, moby->position, moby->position, g_barlow_enemy_move_time);
    } else if (moby->state == 5) {
        heading = mat_fast_helper_a(vars->target[0] - moby->position[0],
                               vars->target[1] - moby->position[1]);
        heading = FastAddRotations(heading, vars->heading);
        MobySpringTurn(moby, &vars->turn, heading, 0.05f, 0.3f, 0.12566373f);
    }
    if (vars->ground) {
        angles.q = 0;
        moby_transform_point_and_rotation_by_parent(moby, vars->ground, moby->position, &moby->rotation, moby->position, &angles);
        moby->rotation.f[2] = angles.f[2];
    }
    if (moby->animation != 3) {
        vars->velocity += 0.00392f;
        moby->position[2] -= vars->velocity - 2.0f;
        floor = coll_probe_ground_height_below(moby->position, 0, 0.5f);
        moby->position[2] -= 2.0f;
        if (moby->position[2] < floor) {
            u8 *controller = g_probe_hit;
            if (*(void **)(controller + 0x18) && moby_get_private_value_2(*(void **)(controller + 0x18))) {
                vars->ground = *(void **)(controller + 0x18);
            } else if (vars->ground) {
                vars->ground = 0;
            }
            moby->position[2] = floor;
            vars->velocity = 0;
            if (vars->ground) {
                rotation = moby->rotation.q;
                angles.q = g_scratch_direction_quad;
                mat_build_axis_angle_rotation(&angles, &rotation, moby->rotation.f[2]);
            }
        }
    }
}

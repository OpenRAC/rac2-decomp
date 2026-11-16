#include "include_asm.h"

#include "common.h"
extern void FastVecAdd(void *, void *, void *);
extern float FastVecLength(void *);
extern void vec_scale_to_length(float *, float *, float);
extern void FastVecSub(float *, float *, float *);
extern float FastVecDot(void *, void *);
extern void FastVecScale(void *, void *, float);
typedef int MovementQuadword __attribute__((mode(TI)));
typedef struct {
    u8    pad00[0x80];
    f32   position[4];
    f32   rotation[4];
    u8    padA0[0x50];
    f32   velocity[4];
    f32   surface_motion[4];
    f32   displacement[4];
    f32   resolved_velocity[4];
    f32   resolved_velocity_xy[4];
    f32   resolved_velocity_planar[4];
    f32   surface_displacement[4];
    u8    pad160[0x10];
    f32   speed;
    f32   planar_speed;
    f32   forward_speed;
    f32   slope;
    f32   vertical_speed;
    f32   surface_speed;
    u8    pad188[0x68];
    s16   air_frames;
    u8    pad1F2[0x72];
    f32   speed_limit;
    u8    pad268[4];
    s32   collision_id;
    u8    pad270[0x17];
    u8    collision_flag;
    u8    pad288[0x94];
    f32   fall_speed_limit;
    u8    pad320[0x268];
    s32   collision_mode;
    u8    pad58C[0x4D4];
    f32   move_impulse[4];
    u8    padA70[0x1824];
    s32   state;
    u8    pad2298[4];
    s32   control_mode;
} Hero;
extern Hero g_hero_state;
extern void UpdateHeroAttachment_pal(int, void *, void *);
extern float cam_get_view_space_vector_length(void *);
extern float cam_get_view_space_height(void *);
extern void cam_set_view_space_vector_length(void *, void *, float);
extern void cam_set_view_space_height(void *, void *, float);
extern void cam_project_vector_onto_view_plane(void *, void *);
extern void vec_clear_128(void *);
extern void hero_resolve_collision_with_rewind(void);
extern void Hero_ProbeGround(void);
extern void EaseHeroPositionToGoal_pal(void);
extern float hero_get_speed_along_forward(void *);

/* Moves the hero by its velocity, impulse and surface motion, then measures the
   resolved displacement and the speeds derived from it. */
void ApplyHeroVelocityAndResolveDisplacement_pal(void) {
    float old[4];
    float horizontal[4];
    float flat[4];

    qcopy(old, g_hero_state.position);
    UpdateHeroAttachment_pal(g_hero_state.collision_mode, g_hero_state.surface_motion,
                      g_hero_state.rotation);
    if (g_hero_state.state == 0x14 || g_hero_state.state == 0x5B ||
        g_hero_state.state == 0x58 || g_hero_state.state == 0x81) {
        if (g_hero_state.air_frames == 0) {
            if (cam_get_view_space_vector_length(g_hero_state.velocity) > g_hero_state.speed_limit - 0.02f) {
                cam_set_view_space_vector_length(g_hero_state.velocity, g_hero_state.velocity,
                                  g_hero_state.speed_limit - 0.02f);
            }
        }
        if (cam_get_view_space_height(g_hero_state.velocity) < -g_hero_state.fall_speed_limit) {
            float fall = -g_hero_state.fall_speed_limit - 0.02f;

            if (fall > 0.0f)
                fall = 0.0f;
            cam_set_view_space_height(g_hero_state.velocity, g_hero_state.velocity, fall);
        }
    } else if (g_hero_state.control_mode != 13) {
        if (g_hero_state.control_mode != 14) {
            if (g_hero_state.air_frames == 0) {
                if (FastVecLength(g_hero_state.velocity) > g_hero_state.speed_limit - 0.02f) {
                    vec_scale_to_length(g_hero_state.velocity, g_hero_state.velocity,
                                  g_hero_state.speed_limit - 0.02f);
                }
            }
        }
    }
    FastVecAdd(g_hero_state.position, g_hero_state.position, g_hero_state.velocity);
    FastVecAdd(g_hero_state.position, g_hero_state.position, g_hero_state.move_impulse);
    vec_clear_128(g_hero_state.move_impulse);
    g_hero_state.collision_flag = 0;
    g_hero_state.collision_id = 0;
    if (FastVecLength(g_hero_state.surface_motion) <= 0.0001f) {
        hero_resolve_collision_with_rewind();
        Hero_ProbeGround();
        FastVecSub(g_hero_state.displacement, g_hero_state.position, old);
        EaseHeroPositionToGoal_pal();
    } else {
        Hero_ProbeGround();
    }

    /* the move actually made, projected on the velocity in three variants */
    FastVecSub(g_hero_state.resolved_velocity, g_hero_state.position, old);
    qcopy(g_hero_state.resolved_velocity_planar, g_hero_state.resolved_velocity);
    qcopy(g_hero_state.resolved_velocity_xy, g_hero_state.resolved_velocity);
    vec_scale_to_length(g_hero_state.resolved_velocity, g_hero_state.resolved_velocity, 1.0f);
    {
        float dot = FastVecDot(g_hero_state.resolved_velocity, g_hero_state.velocity);

        if (dot < 0.0f)
            dot = 0.0f;
        vec_scale_to_length(g_hero_state.resolved_velocity, g_hero_state.velocity, dot);
    }
    qcopy(horizontal, g_hero_state.velocity);
    cam_project_vector_onto_view_plane(horizontal, horizontal);
    cam_project_vector_onto_view_plane(g_hero_state.resolved_velocity_planar, g_hero_state.resolved_velocity_planar);
    vec_scale_to_length(g_hero_state.resolved_velocity_planar, g_hero_state.resolved_velocity_planar,
                  1.0f);
    {
        float dot = FastVecDot(g_hero_state.resolved_velocity_planar, horizontal);

        if (dot < 0.0f)
            dot = 0.0f;
        vec_scale_to_length(g_hero_state.resolved_velocity_planar, horizontal, dot);
    }
    qcopy(flat, g_hero_state.velocity);
    cam_set_view_space_vector_length(flat, flat, 0.0f);
    cam_set_view_space_vector_length(g_hero_state.resolved_velocity_xy, g_hero_state.resolved_velocity_xy, 0.0f);
    vec_scale_to_length(g_hero_state.resolved_velocity_xy, g_hero_state.resolved_velocity_xy, 1.0f);
    {
        float dot = FastVecDot(g_hero_state.resolved_velocity_xy, flat);

        if (dot < 0.0f)
            dot = 0.0f;
        vec_scale_to_length(g_hero_state.resolved_velocity_xy, flat, dot);
    }

    g_hero_state.speed = FastVecLength(g_hero_state.resolved_velocity);
    g_hero_state.planar_speed = cam_get_view_space_vector_length(g_hero_state.resolved_velocity);
    *(MovementQuadword *)horizontal = *(MovementQuadword *)g_hero_state.resolved_velocity;
    g_hero_state.forward_speed = hero_get_speed_along_forward(horizontal);
    g_hero_state.vertical_speed = cam_get_view_space_height(g_hero_state.resolved_velocity);
    if (g_hero_state.forward_speed < 0.0f)
        g_hero_state.forward_speed = 0.0f;

    /* the part of the move caused by the surface the hero stands on */
    qcopy(horizontal, g_hero_state.position);
    if (FastVecLength(g_hero_state.surface_motion) > 0.0001f) {
        float surface_w;

        FastVecAdd(g_hero_state.position, g_hero_state.position, g_hero_state.surface_motion);
        surface_w = g_hero_state.surface_motion[3];
        vec_clear_128(g_hero_state.surface_motion);
        g_hero_state.surface_motion[3] = surface_w;
        hero_resolve_collision_with_rewind();
        Hero_ProbeGround();
        FastVecSub(g_hero_state.displacement, g_hero_state.position, old);
        EaseHeroPositionToGoal_pal();
    }
    FastVecSub(g_hero_state.surface_displacement, g_hero_state.position, horizontal);
    g_hero_state.surface_speed = FastVecLength(g_hero_state.surface_displacement);
    g_hero_state.surface_displacement[3] = g_hero_state.surface_motion[3];
    g_hero_state.surface_motion[3] = 0.0f;
    FastVecSub(g_hero_state.displacement, g_hero_state.position, old);

    g_hero_state.slope = 0.0f;
    if (g_hero_state.planar_speed > 0.004f) {
        g_hero_state.slope = g_hero_state.displacement[2] / g_hero_state.planar_speed;
        if (g_hero_state.slope > 0.5f)
            g_hero_state.slope = 0.5f;
        else if (g_hero_state.slope < -0.5f)
            g_hero_state.slope = -0.5f;
    }
    if (g_hero_state.speed > 1.0400001f) {
        FastVecScale(g_hero_state.displacement, g_hero_state.displacement,
                      1.0400001f / g_hero_state.speed);
        g_hero_state.speed = 1.0400001f;
    }
}

#include "include_asm.h"


#include "common.h"
extern u8 g_hero_state[];
extern float vec_distance_xy(void *, void *);
extern float ApproachValue(float *, float, float);
extern float math_spring_float_to_goal(float *, float *, float, float, float, float);

/* Sets and eases the three hero blend channel targets from the hero state; PAL copy of func_L01_002B3D28: the same C with the step and rates at 50 Hz. */
void hero_l01_update_blend_channels_pal(void) {
    int mode;
    int state;
    float distance;

    if (g_hero_state[0x22B4] == 0) {
        *(float *)(g_hero_state + 0x258) = 0.8f;
        *(float *)(g_hero_state + 0x25C) = 0.7f;
        *(float *)(g_hero_state + 0x260) = 0.45f;
    }

    mode = *(int *)(g_hero_state + 0x229C);
    if (mode == 4) {
        if (*(short *)(g_hero_state + 0x4AC) < *(int *)(g_hero_state + 0x1B8)) {
            if (g_hero_state[0x49E] == 0) {
                *(float *)(g_hero_state + 0x25C) = *(float *)(g_hero_state + 0x4B8);
            }
        }
    } else {
        state = *(int *)(g_hero_state + 0x2294);
        if (state == 6) {
            *(float *)(g_hero_state + 0x25C) = 0.5f;
        } else if (state == 4) {
            *(float *)(g_hero_state + 0x258) = 0.35000002384185791f;
        } else if (state == 0x7C) {
            *(float *)(g_hero_state + 0x260) = 0.8f;
        }
    }

    if (g_hero_state[0x287] == 0)
        goto slow;
    if (*(int *)(g_hero_state + 0x22A4) == 0x12)
        goto slow;
    if (*(int *)(g_hero_state + 0x22B0) == 0x12)
        goto slow;
    if (g_hero_state[0x22B4] == 0) {
        if (*(float *)(g_hero_state + 0x254) < 0.53f)
            goto slow;
    }
    if (*(int *)(g_hero_state + 0x229C) == 0x11)
        goto slow;
    if (g_hero_state[0x1494] != 0)
        goto slow;

    distance = vec_distance_xy(g_hero_state + 0x240, g_hero_state + 0x80);
    if (distance > *(float *)(g_hero_state + 0x264) * 0.5f)
        goto slow;
    return;

slow:
    {
        /* The channel block sits 0x250 into the runtime block; the block pointer
           is taken first and the runtime block is reached back from it. */
        u8 *channels = g_hero_state + 0x250;
        u8 *hero = channels - 0x250;
        float step = 0.024f;
        ApproachValue((float *)channels, *(float *)(hero + 0x258), step);
        ApproachValue((float *)(channels + 4), *(float *)(hero + 0x25C), step);
        math_spring_float_to_goal(
            (float *)(channels + 0x14),
            (float *)(channels + 0x18),
            *(float *)(hero + 0x260),
            0.028800001f,
            0.43200004f,
            0.080000006f);
    }
}

typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; u8 *ptr[0x980]; } MovementHero;
extern u8 g_hero_state[];
extern float g_hero_speed_params[] MACRO_ADDR;
extern void hero_resolve_stick_direction(int, float);

/* Recomputes the hero speed from the timer while it is positive (PAL: 50 Hz). */
void hero_refresh_speed_from_timer_pal(void)
{
    hero_resolve_stick_direction(0, 1.0f);
    if (0.0f < ((MovementHero *)g_hero_state)->f[0x1b0 / 4])
        ((MovementHero *)g_hero_state)->f[0x1b0 / 4] = g_hero_speed_params[4] * (((MovementHero *)g_hero_state)->f[0x24b8 / 4] * 0.020000001f);
}


extern float FastVecDot(void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern char g_hero_l01_state_block[];
extern char g_hero_l01_state_block[];
typedef struct { char prefix[0x2290]; void *moby; } ProbeHero;
typedef struct { char pad[0x18]; void *moby; int count; char gap[0x20]; float normal[4]; } ProbeResult;
extern ProbeResult g_collision_l01_hit;
extern char g_hero_l01_velocity[];
extern int g_collision_hit_count;
extern float cam_get_view_space_vector_length(void *);
extern void hero_build_relative_point(void *, float, float, float, int);
extern float vec_length_xy(void *);
extern void cam_set_view_space_height(void *, void *, float);
extern void FastVecScale(void *, void *, float);
extern int CollLine(void *, void *, int, void *, int);
extern int GetCollHitMaterial(void);
extern float cam_get_view_space_angle(void *);

/* func_L01_002B3788 is defined in L01_002B3788-contact.c. */

/* func_L01_002B3D28 is defined in L01_002B3D28.c. */



/* Stops the hero against a wall: casts two rays along the movement direction (or the vector at
   the start of the hero's data when forced or nearly still), keeps the moby it hit and takes the
   velocity component into the wall's flattened normal away. */
void ClipHeroVelocityAgainstWall_pal(int force)
{
    float origin[4] __attribute__((aligned(16)));
    float endpoint[4] __attribute__((aligned(16)));
    float low_origin[4] __attribute__((aligned(16)));
    float far_endpoint[4] __attribute__((aligned(16)));
    float height, radius, slope;
    int material;
    char *base;
    char *velocity = g_hero_l01_velocity;

    if (cam_get_view_space_vector_length(velocity) < 0.002f)
        return;
    base = velocity - 0xF0;
    height = 0.37f;
    radius = 0.5f;
    if ((unsigned)(*(int *)(base + 0x229C) - 17) < 2) {
        height = 0;
        radius = 0.7f;
    }
    hero_build_relative_point(origin, 0, 0, height, 1);
    hero_build_relative_point(low_origin, 0, 0, height * 0.3f, 1);
    if (force || vec_length_xy(velocity) < 0.01f) {
        vec_scale_to_length(endpoint, base, radius);
        vec_scale_to_length(far_endpoint, base, radius * 1.4f);
    } else {
        cam_set_view_space_height(endpoint, velocity, 0);
        vec_scale_to_length(endpoint, endpoint, radius);
        FastVecScale(far_endpoint, endpoint, 1.4f);
    }
    FastVecAdd(endpoint, endpoint, origin);
    material = -1;
    FastVecAdd(far_endpoint, far_endpoint, low_origin);
    {
        char *hero = g_hero_l01_state_block;

        if (CollLine(low_origin, far_endpoint, 2, ((ProbeHero *)hero)->moby, 0) && g_collision_hit_count > 0)
            material = GetCollHitMaterial();
    }
    slope = 0;
    {
        char *hero = g_hero_l01_state_block;

        if (CollLine(origin, endpoint, 2, ((ProbeHero *)hero)->moby, 0) && g_collision_l01_hit.count > 0)
            slope = cam_get_view_space_angle(g_collision_l01_hit.normal);
    }
    if (slope >= 0.8726647f || material == 8 || material == 12) {
        float dot;
        char *hero = g_hero_l01_state_block;

        *(void **)(hero + 0x270) = g_collision_l01_hit.moby;
        cam_set_view_space_height(g_collision_l01_hit.normal, g_collision_l01_hit.normal, 0);
        vec_scale_to_length(g_collision_l01_hit.normal, g_collision_l01_hit.normal, 1);
        dot = FastVecDot(g_collision_l01_hit.normal, hero + 0xF0);
        if (dot < 0) {
            FastVecScale(g_collision_l01_hit.normal, g_collision_l01_hit.normal, -dot);
            FastVecAdd(hero + 0xF0, hero + 0xF0, g_collision_l01_hit.normal);
        }
    }
}


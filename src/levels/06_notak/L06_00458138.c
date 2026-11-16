#include "common.h"
extern u8 *g_moby_l06_table MACRO_ADDR;
extern void cam_lock_entry(int);
extern short g_trail_active_timers[] __attribute__((sda));
extern short g_trail_alpha_timers[] __attribute__((sda));
extern char g_trail_vertex_buffer[];
extern float IntToFloat(int);
extern void DrawNotakRibbonWithHalo(char *, int, int, int, float, float, float);
extern void gfx_l06_draw_facing_glow_sprite(char *);


extern float FastAddRotations(float, float);
typedef struct NotakChild {
    char pad[0x20];
    unsigned char state;
    char pad21[15];
    unsigned int alpha : 8;
    unsigned int mode : 8;
    unsigned int flags : 16;
} NotakChild;
extern char *CreateMoby(int);
extern void func_002A0F48(char *);
extern void func_003514C8(void *, int, void *);

extern void part_spawn_masked_debris(char *, int, void *, int, float, float, float, float);
typedef unsigned int NotakQuad __attribute__((mode(TI)));
extern char g_sound_state[];
extern char g_hero_position[];
/* Keep this absolute address as one assembler macro under -G0. */
extern char g_effect_vector[] __attribute__((sda));
extern void moby_set_byte_on_group(int, int);
extern void snd_stop_voice(int);
extern int math_random_int_range(int, int);
extern int math_fast_float_d(void *);
extern float vec_distance_xy(void *, void *);
extern void part_emit_facing(char *);
extern void *SpawnExplosion(void *, int, int, int, int, int, int, int,
                            float, float, int, int, int, int);

extern char g_hero_l06_position[];
extern void FastVecSub(float *, const float *, const float *);
extern void vec_scale_to_length(char *, char *, float);
extern int math_random_int_below(int);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern char *part_spawn_ground_effect(void *, int, float, float, unsigned int, int, int, void *, int, float);
extern int FloatToInt(float);


extern char *g_camera_l06_state_ptr[];

extern char *moby_find_record_by_handle_id(int);

extern float coll_get_ground_height_under_object(char *);

extern int cam_moby_update(char *);

extern void moby_set_state(char *, int, int);

extern void moby_mark_spawned(char *);

extern void SpawnExplosionEffects(void *, void *, int, int, int, int, int, int, int, int, int, int,
                          float, float, float, float, float, float, float);

extern void vec_random_direction(float *, float, float);

extern float math_fabs(float);

extern float math_random_signed_float_range(float, float);

extern float math_random_float_range(float, float);

extern char *cam_moby_create(char *, int, int, int, char *, char *, float *, int, float, float);

extern void flying_fragment_update(unsigned char *);

extern int GetFirstMobyInGroup(char **, int, int, int);

extern int GetNextMobyInGroup(char **, char *, int, int);

extern void anim_start_blended(char *, int, int, int);

extern float math_step_value_toward_target(char *, char *, float, float, float, float);

extern int math_blend_scaled_count(char *, char *, int, int, float, float);

extern void FastVecScale(char *, char *, float);

extern float vec_length_xy(char *);

extern float FastDiffRots(float, float);

extern float math_fast_sin_or_cos_a(float);

extern float math_fast_sin_or_cos_b(float);

extern void *part_find_owned_effect_slot(char *, int, int);

extern void part_spawn_debris_mask(char *, int, void *, int, float, float, float, float);

extern int PlayMobySound(int, int, char *);

extern void part_spawn_scaled_bolts(char *, int, float);

extern float g_spark_burst_threshold __attribute__((sda));

extern float g_level_float_param __attribute__((sda));

extern int func_0035CBA0(char *, int, int);

extern void func_L06_0045BE30(char *, int, float, float, float, float);

extern int func_003A0948(int, int, char *);

extern void func_00350388(char *);

extern void matrix_mul_vec3(void *, void *, void *);
extern double __extendsfdf2(float);
extern void STUB_printf(char *, ...);
extern char g_str_spark_burst_debug[];
extern void SpawnTintedEffects(char *, void *, int, float, int, void *, float, unsigned int, float, float, int);
/* Throws a burst of sparks out from the object, then removes it. */
void part_emit_spark_burst_remove(char *moby) {
    float pos[4], vel[4];
    int count = 13, i;
    if (g_spark_burst_threshold < 0.9f && g_level_float_param < 0.9f) count = 40;
    for (i = 0; i < count; i++) {
        pos[0] = math_random_float_range(-8.045f, 8.045f);
        pos[1] = math_fabs(pos[0] * 0.1243008077f) * 1.745f;
        pos[2] = math_random_float_range(0.0f, 3.99f);
        vel[0] = pos[0] * 0.0041433605f;
        vel[1] = -0.13333334f;
        vel[2] = math_random_float_range(3.0f, 7.0f) * 0.0166666675f;
        matrix_mul_vec3(pos, pos, moby + 0xC0);
        FastVecAdd(pos, pos, moby + 0x10);
        matrix_mul_vec3(vel, vel, moby + 0xC0);
        STUB_printf(g_str_spark_burst_debug, __extendsfdf2(pos[0]), __extendsfdf2(pos[1]), __extendsfdf2(pos[2]), __extendsfdf2(vel[0]), __extendsfdf2(vel[1]), __extendsfdf2(vel[2]));
        SpawnTintedEffects(moby, pos, 1, 0.0f, 1, vel, 3.0f, 0x50808040, 1.0f, 5.5f, 0);
        func_003A0948(0, 0, moby);
    }
    func_00350388(moby);
}

extern char *CreateMoby(int);
extern float FastAddRotations(float, float);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void func_002A0F48(char *);

/* Spawns a chained segment from the record at +0x68 and recurses while length remains. */
char *chained_segment_spawn(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    char *segment = 0;
    char *segment_vars;
    float angle;
    float dir_tag;
    float seg_length;

    if (*(float *)(vars + 4) > 0.0f) {
        segment = CreateMoby(0xFE2 /* moby class 4066 */);
        if (segment != 0) {
            *(unsigned char *)(segment + 0x31) = 1;
            *(unsigned char *)(segment + 0x30) = 0xFF;
            *(short *)(segment + 0x32) = 0xFF;
            *(unsigned char *)(segment + 0x20) = 1;
            segment_vars = *(char **)(segment + 0x68);
            *(float *)(segment + 0x2C) = *(float *)(moby + 0x2C);
            *(long *)(segment + 0x38) = *(long *)(moby + 0x38);
            *(char **)(segment_vars + 0x10) = moby;
            *(int *)segment_vars = *(int *)vars;
            seg_length = *(float *)(vars + 0x1C);
            *(float *)(segment_vars + 0x1C) = seg_length;
            *(float *)(segment_vars + 4) = *(float *)(vars + 4) - seg_length;
            angle = FastAddRotations(*(float *)(moby + 0xF8), 3.1415927f);
            *(float *)(segment_vars + 8) = angle;
            qcopy(segment + 0xF0, moby + 0xF0);
            *(float *)(segment + 0xF8) = angle;
            dir_tag = *(float *)(vars + 0xC);
            if (dir_tag == 0.0001f)
                *(float *)(segment_vars + 0xC) = 1.0f;
            else if (dir_tag == -0.0001f)
                *(float *)(segment_vars + 0xC) = -1.0f;
            else if (dir_tag == 1.0f)
                *(float *)(segment_vars + 0xC) = -0.0001f;
            else if (dir_tag == -1.0f)
                *(float *)(segment_vars + 0xC) = 0.0001f;
            moby_transform_joint_to_world(*(char **)(segment_vars + 0x10), 0, segment + 0x10);
            func_002A0F48(segment);
            if (*(float *)(segment_vars + 4) > 0.0f)
                chained_segment_spawn(segment);
        }
    }
    return segment;
}

/* func_L06_004587E8 is defined in L06_004587E8-axis-g8.c. */


/* Draws every active ribbon trail of the projectile, then its glowing sprite. */
void projectile_draw_trails(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    char *trail = g_trail_vertex_buffer;
    short *alpha_timers = g_trail_alpha_timers;
    short *active_timers = g_trail_active_timers;
    int i;

    for (i = 5; i >= 0; i--) {
        if (*active_timers != 0) {
            float alpha_float = IntToFloat(*alpha_timers);
            int alpha = FloatToInt(alpha_float);

            DrawNotakRibbonWithHalo(trail + *(int *)(vars + 0x48) * 0x180, alpha, alpha, 4, 0.025f, 0.5f, 0.2f);
        }
        trail += 0x40;
        alpha_timers++;
        active_timers++;
    }
    gfx_l06_draw_facing_glow_sprite(moby);
}

/* func_L06_00459020 is defined in L06_00458138-ribbon-g8.c. */

/* func_L06_00459620 is defined in L06_00458138-render-g8.c. */

/* Emits paired particles with opposite spin and randomized velocities. */
void part_emit_paired_spin(float *pos, int count) {
    float velocity[4], origin[4], direction[4], axis[4], offset[4];
    float size, angle;
    int i;
    int sign;
    char *particle;
    FastVecSub(direction, (float *)g_hero_l06_position, pos);
    vec_scale_to_length((char *)offset, (char *)direction, 0.3f);
    direction[2] = 0;
    axis[0] = 0;
    axis[1] = 0;
    axis[2] = 1.0f;
    axis[3] = 1.0f;
    for (i = 0; i < count; i++) {
        size = math_random_float_range(0.5f, 2.0f);
        sign = math_random_int_below(2);
        if (!sign) sign--;
        angle = math_random_float_range(-1.0471977f, 1.0471977f);
        math_apply_axis_rotation_to_quat(velocity, direction, axis, angle);
        vec_scale_to_length((char *)velocity, (char *)velocity, math_random_float_range(0.05f, 3.0f) * 0.0166666675f);
        velocity[2] = math_random_float_range(1.0f, 5.0f) * 0.0166666675f;
        FastVecAdd(origin, pos, offset);
        pos[0] += math_random_signed_float_range(0, 0.15f);
        pos[1] += math_random_signed_float_range(0, 0.15f);
        pos[2] += math_random_signed_float_range(0, 0.15f);
        particle = part_spawn_ground_effect(origin, 60, size * 0.1f, size, 0x7F801010, 0, sign, velocity, 0, 0.002f);
        if (particle) particle[9] = FloatToInt(4.0f) + 0x70;
        particle = part_spawn_ground_effect(origin, 60, size * 0.07f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, 0.002f);
        if (particle) particle[9] = FloatToInt(4.0f) + 0x70;
    }
}


extern float func_0032D788(void *, void *);

/* Fills in the length of each segment of a closed path of points. */
void path_l06_compute_segment_lengths(char *path) {
    int count;
    int i;
    float length;

    if (path == 0) {
        return;
    }
    count = *(int *)path;
    i = 0;
    while (i < count) {
        int byte_offset = i * 16;

        length = func_0032D788(path + (byte_offset + 16), path + (((i + 1) % count) * 16 + 0x10));
        *(float *)(path + byte_offset + 0x1C) = length;
        i++;
        count = *(int *)path;
    }
}

/* Works out how much room there is above the object and returns a size class (0, 1 or 2). */
int actor_classify_headroom(char *moby, char *vars)
{
    float height = coll_get_ground_height_under_object(moby + 0x10);
    float gap;

    *(float *)(vars + 0x120) = height;
    gap = *(float *)(*(char **)(vars + 0x11C)) - height;
    *(float *)(vars + 0x128) = height + gap * 0.5f;
    if (gap < 0.41f) {
        return 2;
    }
    if (0.68f < gap) {
        return 0;
    }
    return 1;
}

/* Starts the animation and state that match the object's size class. */
void actor_start_size_anim(unsigned char *moby)
{
    switch (moby[0xBC]) {
    case 0:
        if (moby[0x43] != 0) {
            anim_start_blended((char *)moby, 0, 0, 0xA);
        }
        moby[0x20] = 1;
        break;
    case 1:
        if (moby[0x43] != 3) {
            anim_start_blended((char *)moby, 3, 0, 0xA);
        }
        moby[0x20] = 7;
        break;
    case 2:
        if (moby[0x43] != 9) {
            anim_start_blended((char *)moby, 9, 0, 0xA);
        }
        moby[0x20] = 0xF;
        break;
    }
}

/* func_L06_00459D08 is defined in L06_00458138-g8.c. */

extern int point_in_path_xy(void *, void *, int);
extern int CollLine(void *, void *, int, void *, int);
extern int coll_test_point(void *, int, void *, float);
extern float mat_fast_helper_a(float, float);

/* Sweeps for a free heading when a sweep is pending, else (or when none is free) faces the
   target. The found block before the sweep is what puts the flag test's fallback on its own
   branch: its store goes into the sweep's branch-likely slot, leaving that branch behind. */
void actor_choose_free_heading(char *obj, char *st)
{
    float dir[3];
    char *p;
    float ang;
    float step;
    float total;

    if (*(int *)(st + 0x124) != 0)
        goto search;
    goto fallback;
found:
    *(float *)(st + 0x12C) = ang;
    return;
search:
    dir[0] = math_fast_sin_or_cos_a(*(float *)(obj + 0xF8)) * 5.2f;
    dir[1] = math_fast_sin_or_cos_b(*(float *)(obj + 0xF8)) * 5.2f;
    dir[2] = 0.0f;
    FastVecAdd(dir, dir, obj + 0x10);
    p = *(char **)(st + 0x118);
    if (point_in_path_xy(dir, p + 0x10, *(int *)p) != 0 &&
        CollLine(obj + 0x10, dir, 0x24, obj, 0) == 0 &&
        coll_test_point(dir, 0x24, obj, 1.5f) == 0)
        return;
    step = math_fabs(*(float *)(st + 0x130));
    ang = *(float *)(obj + 0xF8);
    total = 0.0f;
    do {
        ang = FastAddRotations(ang, *(float *)(st + 0x130));
        dir[0] = math_fast_sin_or_cos_a(ang) * 5.2f;
        dir[1] = math_fast_sin_or_cos_b(ang) * 5.2f;
        dir[2] = 0.0f;
        FastVecAdd(dir, dir, obj + 0x10);
        p = *(char **)(st + 0x118);
        if (point_in_path_xy(dir, p + 0x10, *(int *)p) == 0 ||
            CollLine(obj + 0x10, dir, 0x24, obj, 0) != 0 ||
            coll_test_point(dir, 0x24, obj, 1.5f) != 0) {
            total += step;
            continue;
        }
        goto found;
    } while (total < 6.283186f);
fallback:
    *(float *)(st + 0x12C) = mat_fast_helper_a(*(float *)(st + 0xE0) - *(float *)(obj + 0x10),
                                         *(float *)(st + 0xE4) - *(float *)(obj + 0x14));
}

/* Moves the object using its stored speed, pulls it down when it is high, and slows it after a bump. */
void actor_apply_fall_move(char *moby, char *vars, float f, float g, float h)
{
    char position[16];
    char *vars_alias = vars;

    if (*(float *)(*(char **)(vars + 0x11C)) - 0.3f < *(float *)(moby + 0x18)) {
        *(float *)(vars + 0xC8) -= 0.163333335f;
    }
    qcopy(position, moby + 0x10);
    math_step_value_toward_target(position + 8, vars_alias + 0xC8, *(float *)(vars_alias + 0x128), f, g, h);
    if (math_blend_scaled_count(moby, vars_alias + 0xC0, 0x400, 0x10, 1.0f, 0.0f) != 0) {
        FastVecScale(vars_alias + 0xC0, vars_alias + 0xC0, 0.5f);
    }
}

/* Speeds up or slows down the object depending on how closely it faces a direction; returns 1 when speeding up. */
int actor_adjust_speed_facing(char *moby, char *vars, float p1, float p2, float p3, float p4, float p5,
                      float p6, float p7)
{
    float speed = vec_length_xy(vars + 0xC0);
    float angle_diff = FastDiffRots(*(float *)(moby + 0xF8), p1);
    int speeding_up = 0;

    if (angle_diff < p2) {
        speed += p3;
        speeding_up = 1;
    } else if (p4 < angle_diff) {
        speed -= p5;
    }
    if (p6 < speed) {
        speed = p6;
    } else if (speed < p7) {
        speed = p7;
    }
    *(float *)(vars + 0xC0) = math_fast_sin_or_cos_a(*(float *)(moby + 0xF8)) * speed;
    *(float *)(vars + 0xC4) = math_fast_sin_or_cos_b(*(float *)(moby + 0xF8)) * speed;
    return speeding_up;
}

extern float moby_get_anim_value(char *);
extern void make_hit_descriptor(void *, char *, int, void *, float);
extern int coll_process_hit(void *, float, int, char *, void *);
extern void *g_hit_l06_result;

/* Runs the shared pickup test: when the object is in the given state and the draw is inside the window, aims at the target and, on a hit with the expected tag, hands over to the next state. */
void actor_try_pickup_transition(char *obj, float lo, char *self, float hi, int kind, int sub, float scale, float reach, float range,
                       int anim, int link, int next, void *tag)
{
    float dir[4] __attribute__((aligned(16)));
    char aim[0x30] __attribute__((aligned(16)));
    float probe[4] __attribute__((aligned(16)));
    float roll = moby_get_anim_value(obj);
    char *vec;

    if (*(u8 *)(obj + 0x20) == kind && *(u8 *)(obj + 0x42) == sub && lo < roll && roll < hi) {
        vec = self + 0xC0;
        vec_scale_to_length((char *)dir, vec, scale);
        dir[2] = 1.0f;
        make_hit_descriptor(aim, obj, 1, dir, reach);
        func_003514C8(obj, 0, probe);
        if (coll_process_hit(probe, range, 0x21, obj, aim) != 0 && g_hit_l06_result == tag) {
            FastVecScale(vec, vec, -1.0f);
            *(float *)(self + 0xC8) = -0.05f;
            if (*(u8 *)(obj + 0x43) != anim)
                anim_start_blended(obj, anim, link, 5);
            *(u8 *)(obj + 0x20) = next;
        }
    }
}

extern void func_003514C8(void *, int, void *);

extern int func_0031EBF8(f32, void *, int, void *);

extern void *g_hit_l06_result;

/* Checks whether a short probe from the object hits the given thing; returns 1 if it does. */
int actor_probe_hits_target(void *moby, void *expected, f32 reach) {
    char probe[16];
    int hit_result;

    func_003514C8(moby, 0, probe);
    hit_result = func_0031EBF8(reach, probe, 0x21, moby);
    if (hit_result != 0) {
        if (g_hit_l06_result == expected) {
            return 1;
        }
    }
    return 0;
}

/* Returns 1 if another object of the same group is in a state between the two given values. */
int group_is_member_in_state_range(char *moby, int min_state, int max_state)
{
    char *found = 0;

    if (GetFirstMobyInGroup(&found, *(unsigned char *)(moby + 0x21), 0, 0) != 0) {
        return 0;
    }
    while (found != 0) {
        if (found != moby) {
            int other_state = *(unsigned char *)(found + 0x20);

            if (other_state >= min_state) {
                if (other_state <= max_state) {
                    return 1;
                }
            }
        }
        if (GetNextMobyInGroup(&found, found, 0, 0) != 0) {
            return 0;
        }
    }
    return 0;
}

/* When hit, bursts into a spray of pieces and removes itself. */
void burst_on_hit_update(char *moby)
{
    char *hit;
    int count;

    if (*(unsigned char *)(moby + 0x20) == 0) {
        *(unsigned char *)(moby + 0x20) = 1;
        *(unsigned short *)(moby + 0x34) |= 0x800;
    }

    hit = (char *)func_0035CBA0(moby, 0x4010000, 0);
    if (hit != 0 && *(short *)(*(char **)(hit + 0x20) + 0xAA) != 0xFE5 /* moby class 4069 */) {
        count = 3;
        if (g_spark_burst_threshold < 0.8999999761581421f && g_level_float_param < 0.8999999761581421f)
            count = 0xE;

        func_L06_0045BE30(moby, count, 0.0f, 3.263000011444092f, 1.9739999771118164f,
                          0.11666667461395264f);
        func_003A0948(0, 0, moby);
        func_00350388(moby);
    } else {
        *(unsigned char *)(moby + 0xA8) = 0xFF;
    }
}

/* Waits until hit, then bursts into fragments and removes itself. */
void fragment_burst_update(unsigned char *moby)
{
    char *vars = *(char **)(moby + 0x68);

    switch (moby[0x20]) {
    case 0:
        *(unsigned short *)(moby + 0x34) |= 0x800;
        moby_set_state((char *)moby, 1, -1);
        break;
    case 1:
        if (part_find_owned_effect_slot((char *)moby, 0x4010000, 0) != 0) {
            if (*(int *)vars == 0) {
                moby_set_state((char *)moby, 2, -1);
            }
        }
        moby[0xA8] = 0xFF;
        break;
    case 2: {
        char offset[16];

        FastVecScale(offset, (char *)(moby + 0xD0), -0.033333335f);
        part_spawn_debris_mask((char *)moby, 3, offset, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
        PlayMobySound(0, 0, (char *)moby);
        part_spawn_scaled_bolts((char *)moby, 1, 0.0f);
        moby_mark_spawned((char *)moby);
        break;
    }
    }
}

/* Looks up the object bound to the given flags; unless the hit object's own field says
   0xFE5, it starts a smoke emitter, spawns one particle with the level's own callback
   and six more in a loop, then clears the object's byte at 0xA8. */
void debris_burst_on_hit(char *moby)
{
    char *hit;
    char *piece;
    float velocity[3];
    int i;

    hit = (char *)part_find_owned_effect_slot(moby, 0x4010001, 0);
    if (hit != 0 && *(short *)(*(char **)(hit + 0x20) + 0xAA) != 0xFE5 /* moby class 4069 */) {
        PlayMobySound(0, 0, moby);
        SpawnExplosionEffects(moby, moby + 0x10, 0, 10, 3, 9, -1, 1, 1, -1, 0, 0x810001,
                      0.0f, 0.0f, 4.0f, 2.0f, 9.0f, 0.0f, 15.0f);
        vec_random_direction(velocity, 0.0333333350718021392822265625f, 0.066666670143604278564453125f);
        velocity[2] = math_fabs(velocity[2]);
        piece = cam_moby_create(moby, 1, *(short *)(moby + 0xAA), 6, moby + 0x10, moby + 0xF0,
                          velocity, 1, math_random_signed_float_range(20.0f, 45.0f), 15.0f);
        if (piece != 0) {
            *(void (**)(void))(piece + 0x64) = (void (*)(void))flying_fragment_update;
        }
        for (i = 0; i < 6; i++) {
            vec_random_direction(velocity, 0.10000000894069671630859375f, 0.2000000178813934326171875f);
            velocity[2] = math_fabs(velocity[2]);
            cam_moby_create(moby, 2, *(short *)(moby + 0xAA), i, moby + 0x10, moby + 0xF0,
                          velocity, 0xFF, math_random_signed_float_range(20.0f, 45.0f),
                          math_random_float_range(15.0f, 25.0f));
        }
        PlayMobySound(1, 0, moby);
        part_spawn_scaled_bolts(moby, 1, 0.0f);
        moby_mark_spawned(moby);
    }
    *(unsigned char *)(moby + 0xA8) = 0xFF;
}

/* Updates a flying fragment: it flies until it lands, then fades out and disappears. */
void flying_fragment_update(unsigned char *moby)
{
    switch (moby[0x20]) {
    case 0:
        if (cam_moby_update((char *)moby) != 0) {
            moby_set_state((char *)moby, 1, -1);
            *(unsigned short *)(moby + 0x34) |= 0x2800;
        }
        break;
    case 1:
        cam_moby_update((char *)moby);
        if (moby[0x23] < 2) {
            moby_mark_spawned((char *)moby);
        } else {
            moby[0x23] -= 2;
        }
        break;
    }
}

/* Updates an emitter that rests, then spits particles while the hero is near, and bursts when hit. */
void particle_l06_emitter_update(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    char *hit;
    float pos[4];
    *(unsigned char *)(moby + 0x23) = 0x80;
    if (!vars) {
        return;
    }
    hit = (char *)func_0035CBA0(moby, 0x4010000, 0);
    if (hit && *(short *)(*(char **)(hit + 0x20) + 0xAA) != 0xFE5 /* moby class 4069 */) {
        if (*(unsigned char *)(moby + 0x20) == 1) {
            moby_set_byte_on_group(*(unsigned char *)(moby + 0x21), 0);
        }
        func_003A0948(1, 0, moby);
        *(NotakQuad *)pos = 0;
        pos[2] = 1.0f;
        FastVecAdd(pos, pos, moby + 0x10);
        SpawnExplosion(pos, 1, 25, 20, 20, 20, 45, 1, 1.25f, 20.0f, 1, 1, 0, 0);
        part_spawn_masked_debris(moby, 0x7F, g_effect_vector, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
        part_spawn_scaled_bolts(moby, 1, 0.0f);
        func_00350388(moby);
    }
    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        *(unsigned char *)(moby + 0x23) = 0x80;
        *(int *)vars = math_random_int_range(40, 250);
        moby[0x20] = 2;
        *(int *)(vars + 8) = -1;
        break;
    case 1:
        if (vec_distance_xy(moby + 0x10, g_hero_position) < 32.0f) {
            part_emit_facing(moby);
        }
        if (math_fast_float_d(vars + 4)) {
            *(int *)vars = math_random_int_range(200, 250);
            if (*(int *)(vars + 8) != -1) {
                char *sound = g_sound_state + *(int *)(vars + 8) * 0x70;
                if (*(char **)(sound + 0x88) == moby && *(unsigned char *)(sound + 0x74)) {
                    snd_stop_voice(*(int *)(vars + 8));
                }
            }
            *(int *)(vars + 8) = -1;
            moby[0x20] = 2;
            moby_set_byte_on_group(*(unsigned char *)(moby + 0x21), 0);
        }
        break;
    case 2:
        if (math_fast_float_d(vars) && *(unsigned char *)(moby + 0xBC) == 0) {
            char *sound;
            *(int *)(vars + 4) = math_random_int_range(200, 250);
            sound = g_sound_state + *(int *)(vars + 8) * 0x70;
            if (*(char **)(sound + 0x88) != moby || !*(unsigned char *)(sound + 0x74)) {
                *(int *)(vars + 8) = func_003A0948(0, 4, moby);
            }
            moby[0x20] = 1;
            moby_set_byte_on_group(*(unsigned char *)(moby + 0x21), 1);
        }
        break;
    }
    *(unsigned char *)(moby + 0xA8) = 0xFF;
}

/* func_L06_004621C8 is defined in L06_00458138-effect-g8.c. */

/* Waits for a linked object to reach state 2, then fires a trigger and follows that object's state. */
void linked_trigger_update(char *moby)
{
    char *vars = *(char **)(moby + 0x68);

    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        *(unsigned char *)(moby + 0x30) = 0xFF;
        *(unsigned char *)(moby + 0x20) = 1;
        break;
    case 1: {
        int i = *(int *)(vars + 4);
        char *base = (char *)g_moby_l06_table;
        char *p = (char *)(base + (i << 8));
        int t = *(unsigned char *)(p + 0x20);
        int j;
        char *q;

        if (t != 2) {
            break;
        }
        j = *(int *)(vars + 8);
        q = (char *)(base + (j << 8));
        if (q == 0) {
            break;
        }
        if (*(unsigned char *)(q + 0x20) == 0xFE) {
            break;
        }
        if (*(unsigned char *)(q + 0x20) == 0xFD) {
            break;
        }
        cam_lock_entry(*(int *)vars);
        *(unsigned char *)(moby + 0x20) = t;
        break;
    }
    case 2: {
        int i = *(int *)(vars + 4);
        char *p = (char *)(g_moby_l06_table + (i << 8));

        if (*(unsigned char *)(p + 0x20) != 2) {
            *(unsigned char *)(moby + 0x20) = 1;
        }
        break;
    }
    }
}

/* func_L06_004649F0 is defined in L06_004649F0-g8.c. */

/* func_L06_00464F40 is defined in L06_00464F40-g8.c. */


/* Stores two values in the settings block of the object of kind 5, finding that object first if needed. */
void object_set_kind_five_settings(float value_a, float value_b)
{
    char *first = g_camera_l06_state_ptr[0];
    char *target;
    char *settings;

    if (*(short *)(first + 0x86) != 5) {
        target = moby_find_record_by_handle_id(5);
    } else {
        target = first;
    }
    settings = *(char **)(target + 0x70) + 0xE0;
    *(float *)(settings + 0x44) = value_a;
    *(float *)(settings + 0x48) = value_b;
}


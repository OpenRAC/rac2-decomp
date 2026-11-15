#include "common.h"

extern void anim_start_immediate(void *, int, int);
extern char g_hero_position[];
extern unsigned char *D_L04_001B24E8 __attribute__((sda));

extern signed char *g_moby_l04_pool __attribute__((sda));
extern void racer_release_sound_handles(int, unsigned char *);
extern float func_0033BBE0(void);
extern float func_0033BB78(float, float);
extern void vec_build_spherical_offset(void *, float, float, float);
extern void add_vectors(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
/* Integer and float arguments keep their order within each EE register bank. */
extern void part_spawn_ground_effect(void *, int, unsigned int, int, int, void *, float, float, float, int);

extern void FastVecSub(void *, void *, void *);
extern float func_L00_002EE290(void *);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern unsigned char *g_route_path_table[];
extern float fast_vec_dist(void *, void *);
extern int D_L04_001B2008[] __attribute__((sda));
extern int D_00138320;
extern float D_L04_001BDC30;
extern float math_fast_sin_or_cos_b(float);
extern float math_fast_sin_or_cos_a(float);
extern float ApproachValue(void *, float, float);
extern int math_fast_float_d(void *);
extern int vec_fast_helper_a(void *);
extern void moby_update_transform_history_followers(void *, int);
extern void level_init_pending_slot(void *, void *);
extern void level_append_record_to_table(void *, float, int, int);
extern void level_release_slot_list(void *);
extern int snd_play_from_class_bank(int, int, void *, int);
extern int snd_is_voice_playing_for_owner(void *, int);
extern int PlayMobySound(int, int, void *);
extern int snd_set_slot_field(int, int);
extern void UpdateViewContext(void);
extern int GetFirstMobyInGroup(void *, int, int, int);
extern int GetNextMobyInGroup(void *, void *, int, int);
extern void set_identity_matrix(void *);
extern void matrix_from_basis_rows(void *, void *);
extern void transform_vector(void *, void *, void *);
typedef struct {
    unsigned char pad[0x1a8];
    int primary;
    int branches[4];
    int links[4];
    int parents[4];
} L04PathState;


/* Frozen Batch A A04-table-select-76; acknowledged claim 8c4d82cfbf43e138ed35e757fdaeee3e7c4651fa684549ba9d5e8ac22c56d111. */
typedef unsigned char BatchA_A04_u8;

typedef unsigned int BatchA_A04_u32;

extern BatchA_A04_u32 g_current_map_index[] __attribute__((sda));

extern BatchA_A04_u8 D_001395B8[];

extern void DrawOrientedQuadsAtPoints(void *a0, void *a1, int a2, unsigned int a3,
                              float f12, float f13, float f14, int t0, int t1);

/* Steps the record's phase at +0x1FC down by 0.1 (wrapping up by 8 once it reaches -8) and
   draws the effect with it. */
void bike_animate_boost_flame_streak(void *moby) {
    char *vars = *(char **)((char *)moby + 0x68);

    *(float *)(vars + 0x1FC) -= 0.1f;
    if (*(float *)(vars + 0x1FC) <= -8.0f)
        *(float *)(vars + 0x1FC) += 8.0f;
    DrawOrientedQuadsAtPoints(moby, vars + 0x200, 3, 0x60005AFF, 0.08f, 0.45f, *(float *)(vars + 0x1FC), 0xFF,
                      0x17);
}

typedef unsigned int B781AimQuad __attribute__((mode(TI)));
extern float math_fabs(float);
extern void math_approach_with_velocity(void *, void *, float, float, float, float, int);
extern void anim_start_blended(void *, int, int, int);
extern void func_002A05A8(void *);
extern void func_002A0F48(void *);
extern void *moby_spawn_at_parent_pose(void *, int, float);
extern int vec_apply_scaled_value(void *, float);
extern void gfx_add_draw_callback_third(void (*)(void *), void *);
extern void bike_animate_boost_flame_streak(void *);
extern void part_spawn_object_following_effect(void *, void *, unsigned int, float, int, int, float, int, int, int);
extern void FastVecSub(void *, void *, void *);
extern float func_L00_002EE290(void *);
extern void EmitTrailEffects(void *, void *, void *, float);
/* Animates the racer bike each frame: leans it into turns, keeps its child effect object in place and starts the spark effects when it is close to its target. */
void racer_update_bike_lean(unsigned char *moby, unsigned char *vars)
{
    float point[4];
    float end[4];
    float total = *(float *)(vars + 0x138) + *(float *)(vars + 0x13c);
    float a, b, c, angle, factor;
    if (total < 0.083333336f) total = 0.083333336f;
    a = *(float *)(vars + 0x130) * 13.750985f;
    b = total * 2.7088037f;
    c = *(float *)(vars + 0x130) * 28.647884f;
    a = a * math_fabs(a);
    c = 1.0f - (1.0f - c) * (1.0f - c);
    if (b > 1.0f) b = 1.0f;
    if (*(float *)(vars + 0x1f4) != 0.0f) {
        if (math_fabs(*(float *)(moby + 0xf0) - *(float *)(vars + 0x1f4)) < 0.003f) *(float *)(vars + 0x1f4) = 0.0f;
        factor = *(float *)(vars + 0x1f8);
        angle = *(float *)(vars + 0x1f4);
    } else {
        factor = 1.0f;
        angle = (factor - b) * a + b * c;
        if (angle > factor) angle = factor;
        if (angle < -1.0f) angle = -1.0f;
        angle *= -0.52359885f;
    }
    math_approach_with_velocity(moby + 0xf0, vars + 0x128, angle, factor * 0.035f, 0.45f, factor * 0.027634384f, 0);
    if (*(unsigned char **)(vars + 0x8c)) {
        unsigned char *child = *(unsigned char **)(vars + 0x8c);
        if ((child[0x60] & 2) && child[0x42]) anim_start_blended(child, 0, 0, 3);
        *(short *)(*(unsigned char **)(vars + 0x8c) + 0x32) = 30;
        (*(unsigned char **)(vars + 0x8c))[0x31] = 1;
        *(B781AimQuad *)(*(unsigned char **)(vars + 0x8c) + 0x10) = *(B781AimQuad *)(moby + 0x10);
        *(B781AimQuad *)(*(unsigned char **)(vars + 0x8c) + 0xf0) = *(B781AimQuad *)(moby + 0xf0);
        (*(unsigned char **)(vars + 0x8c))[0x30] = 0;
        func_002A05A8(*(void **)(vars + 0x8c));
        func_002A0F48(*(void **)(vars + 0x8c));
        *(unsigned short *)(*(unsigned char **)(vars + 0x8c) + 0x34) |= 6;
    } else *(void **)(vars + 0x8c) = moby_spawn_at_parent_pose(moby, MOBY_CLASS_ENEMY_HOVERBIKE_RACER, 0.25f);
    if ((*(unsigned char **)(vars + 0x164))[0xbc] == 5) {
        if (vec_apply_scaled_value(moby, 20.0f) != -1) {
            gfx_add_draw_callback_third(bike_animate_boost_flame_streak, moby);
            part_spawn_object_following_effect(vars + 0x200, moby, 0x3096ffff, 94500.0f, -1, 0, 0.01f, 2, 0, -1);
            part_spawn_object_following_effect(vars + 0x210, moby, 0x3096ffff, 94500.0f, -1, 0, 0.01f, 2, 0, -1);
            part_spawn_object_following_effect(vars + 0x220, moby, 0x3096ffff, 94500.0f, -1, 0, 0.01f, 2, 0, -1);
        }
    }
    if (*(int *)(vars + 0x244)) {
        FastVecSub(point, *(unsigned char **)(vars + 0x164) + 0x10, moby + 0x10);
        if (func_L00_002EE290(point) < 100.0f) {
            *(B781AimQuad *)(point) = *(B781AimQuad *)(moby + 0x10);
            point[2] -= 0.25f;
            *(B781AimQuad *)(end) = *(B781AimQuad *)(moby + 0x10);
            EmitTrailEffects(moby, end, vars + 0xd0, *(float *)(vars + 0x138) + *(float *)(vars + 0x13c));
        }
    }
}


/* func_L04_004045E0 is in L04_00402D90-follower.c. */

/* func_L04_00407078 is in L04_00402D90-debris.c. */

/* func_L04_004073E8 is in L04_00402D90-trail.c. */

extern int FastDecTimer(void *);
extern void gfx_add_draw_callback_third(void (*)(void *), void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void multiply_matrix3x3(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern void vec_fast_normalize(void *, void *, void *);
extern float FastVecDot(void *, void *);
extern float FastVecLength(void *);
extern int FloatToInt(float);
extern void euler_rotation_basis(void *, void *);
extern void part_l00_spawn_explosion_burst(void *, void *, float, float, int);
extern void SpawnExplosion(void *, float, float, int, int, int, int, int, int, int, int, int, int, int);
extern void moby_mark_spawned(void *);
extern int coll_test_point(void *, int, float, void *);
extern void math_build_axis_angle_quat(void *, void *, float);
extern void mat_from_rotation(void *, void *);
extern void mat_get_euler_angles(void *, void *);
extern float D_L04_001BFB00[];
extern void racer_draw_trail(void *);

/* Moves a flying debris piece, bounces it off the ground and removes it when its timer runs out. */
void debris_l04_piece_update(unsigned char *moby)
{
    float oldpoint[4];
    float rot[12];
    float point[4];
    float delta[4];
    float probe[4];
    float matrix[16];
    float bounce[4];
    float axis[4];
    unsigned char *vars = *(unsigned char **)(moby + 0x68);
    float speed, dot;
    float radius;
    *(unsigned short *)(vars + 0x32) += 1;
    switch (moby[0x20]) {
    case 1:
        if (FastDecTimer(vars + 0x30)) {
            moby[0x20] = (*(int *)(vars + 0x34) & 1) ? 3 : 2;
            *(short *)(vars + 0x30) = FloatToInt(10.0f);
            return;
        }
        if (*(int *)(vars + 0x34) & 4) gfx_add_draw_callback_third(racer_draw_trail, moby);
        break;
    case 2:
        matrix_mul_vec3(oldpoint, vars + 0x20, moby + 0xc0);
        FastVecAdd(oldpoint, oldpoint, moby + 0x10);
        if (*(int *)(vars + 0x34) & 2) part_l00_spawn_explosion_burst(moby, oldpoint, 0.3f, 10.0f, -1);
        else SpawnExplosion(moby + 0x10, 0.5f, 0.0f, 0, 25, 20, 20, 20, 45, 0, 0, 0, 0, 0);
        goto destroy;
    case 3:
        if (FastDecTimer(vars + 0x30)) {
        case 0:
        destroy:
            moby_mark_spawned(moby);
            return;
        }
        moby[0x23] = FloatToInt((float)*(short *)(vars + 0x30) * 12.8f);
        break;
    }
    euler_rotation_basis(rot, vars + 0x10);
    matrix_mul_vec3(oldpoint, vars + 0x20, moby + 0xc0);
    multiply_matrix3x3(moby + 0xc0, rot, moby + 0xc0);
    matrix_mul_vec3(point, vars + 0x20, moby + 0xc0);
    FastVecSub(delta, point, oldpoint);
    FastVecSub(moby + 0x10, moby + 0x10, delta);
    FastVecAdd(moby + 0x10, moby + 0x10, vars);
    *(float *)(vars + 8) -= *(float *)(vars + 0x38);
    radius = *(float *)(vars + 0x2c);
    matrix_mul_vec3(probe, vars + 0x20, moby + 0xc0);
    FastVecAdd(probe, probe, moby + 0x10);
    if (coll_test_point(probe, 0, radius, moby)) {
        vec_scale_to_length(D_L04_001BFB00, D_L04_001BFB00, 1.0f);
        speed = FastVecLength(vars);
        dot = FastVecDot(vars, D_L04_001BFB00);
        if (dot < 0.0f) {
            vec_fast_normalize(vars, vars, D_L04_001BFB00);
            vec_scale_to_length(bounce, D_L04_001BFB00, dot * 0.5f);
            FastVecAdd(vars, vars, bounce);
            vec_scale_to_length(vars, vars, speed);
            FastVecCross(axis, D_L04_001BFB00, vars);
            vec_scale_to_length(axis, axis, 1.0f);
            math_build_axis_angle_quat(axis, axis, FastVecLength(vars + 0x10));
            mat_from_rotation(axis, matrix);
            mat_get_euler_angles(matrix, vars + 0x10);
            if (*(short *)(vars + 0x32) >= 16) *(short *)(vars + 0x30) = 0;
        }
    }
}




/* A04-table-select-76 freshly exact-verified under family reservation */
/* Gets how many times the player has won the current course (the table depends on the level). */
BatchA_A04_u32 race_get_course_win_count(BatchA_A04_u8 *course_index) {
    BatchA_A04_u32 level = g_current_map_index[0];
    BatchA_A04_u32 count = 0;
    if (level == 4) count = D_001395B8[(BatchA_A04_u32)course_index + 0x4D];
    else if (level == 0xB) count = D_001395B8[(BatchA_A04_u32)course_index + 0x57];
    return count;
}

/* A04-table-select family, incrementing form: bumps the state-selected byte */
/* Adds one to the number of wins stored for this course. */
void race_increment_course_win_count(BatchA_A04_u8 *course_index)
{
    BatchA_A04_u32 level = g_current_map_index[0];

    if (level == 4) D_001395B8[(BatchA_A04_u32)course_index + 0x4D]++;
    else if (level == 0xB) D_001395B8[(BatchA_A04_u32)course_index + 0x57]++;
}

/* shared native body of family A04-table-select: reads the state-selected byte */
/* Gets how many times the player finished this course without winning. */
unsigned int race_get_course_finish_count(unsigned char *course_index)
{
    unsigned int level = g_current_map_index[0];
    unsigned int count = 0;

    if (level == 4) count = D_001395B8[(unsigned int)course_index + 0x52];
    else if (level == 0xB) count = D_001395B8[(unsigned int)course_index + 0x5C];
    return count;
}

/* A04-table-select family, incrementing form (second slot pair) */
/* Adds one to the number of non-winning finishes stored for this course. */
void race_increment_course_finish_count(BatchA_A04_u8 *course_index)
{
    BatchA_A04_u32 level = g_current_map_index[0];

    if (level == 4) D_001395B8[(BatchA_A04_u32)course_index + 0x52]++;
    else if (level == 0xB) D_001395B8[(BatchA_A04_u32)course_index + 0x5C]++;
}

extern BatchA_A04_u8 *D_001B26F0 __attribute__((sda));

extern void part_kill(void *);

/* Sweeps the 0x800 packed 64-byte records, redrawing the four live kinds */
/* Goes through all the effect records and refreshes the ones of four active kinds. */
void part_refresh_active_records(void)
{
    int i;

    for (i = 0; i < 0x800; i++) {
        BatchA_A04_u8 kind = *(BatchA_A04_u8 *)((i << 6) + (BatchA_A04_u32)D_001B26F0);

        if (kind == 0x4A || kind == 8 || kind == 0xB || kind == 0xF) {
            part_kill(D_001B26F0 + (i << 6));
        }
    }
}

/* Resets a racer to its starting state and removes leftover effect objects. When keep is set, the race progress is kept. */
void racer_reset_state(unsigned char *moby, int keep)
{
    unsigned char *vars = *(unsigned char **)(moby + 0x68), *other_moby;
    unsigned char *linked_racer;
    qzero(vars + 0x2b0);
    *(float *)(vars + 0x2b8) = 1.0f;
    qzero(vars + 0x290);
    qzero(vars + 0x2a0);
    qzero(vars + 0x2c0);
    qzero(vars + 0x6c0);
    *(B781AimQuad *)(moby + 0x10) = *(B781AimQuad *)g_hero_position;
    *(int *)(vars + 0x76c) = 0;
    *(int *)(vars + 0x718) = 0;
    *(short *)(vars + 0x274) = 0;
    vars[0x349] = 0;
    *(int *)(vars + 0x34c) = 0;
    *(int *)(vars + 0x354) = 0;
    *(int *)(vars + 0x358) = 0;
    *(int *)(vars + 0x278) = 0;
    *(int *)(vars + 0x27c) = 0;
    *(int *)(vars + 0x300) = 0;
    *(int *)(vars + 0x304) = 0;
    *(int *)(vars + 0x308) = 0;
    *(int *)(vars + 0x30c) = 0;
    *(int *)(vars + 0x280) = 0;
    *(int *)(vars + 0x288) = 0;
    *(int *)(vars + 0x750) = 0;
    *(int *)(vars + 0x738) = 0;
    *(int *)(vars + 0x724) = 0;
    *(float *)(vars + 0x28c) = 90.0f;
    racer_release_sound_handles((int)moby, vars);
    linked_racer = (unsigned char *)g_moby_l04_pool + (*(int *)(vars + 0x1dc) << 8);
    *(int *)(vars + 0x3a8) = 10;
    *(int *)(vars + 0x328) = -1;
    *(int *)(vars + 0x330) = -1;
    *(int *)(vars + 0x334) = -1;
    *(int *)(vars + 0x3bc) = -1;
    *(int *)(vars + 0x714) = -1;
    *(int *)(vars + 0x324) = 0;
    *(int *)(vars + 0x32c) = 0;
    *(int *)(vars + 0x33c) = 0;
    *(int *)(vars + 0x338) = 0;
    *(int *)(vars + 0x38c) = 0;
    *(int *)(vars + 0x390) = 0;
    *(int *)(vars + 0x4c4) = 0;
    *(int *)(vars + 0x3b0) = 0;
    *(int *)(vars + 0x3ac) = 0;
    *(int *)(vars + 0x3b4) = 0;
    *(int *)(vars + 0x360) = 0;
    *(int *)(vars + 0x364) = 0;
    *(int *)(vars + 0x368) = 0;
    *(int *)(vars + 0x4d8) = 0;
    *(int *)(vars + 0x4dc) = 0;
    if (linked_racer) anim_start_immediate(linked_racer, 0, 0);
    *(short *)(vars + 0x34a) = -1;
    *(int *)(vars + 0x36c) = 0;
    /* This cleared vector has no scalar consumers in the surrounding resets. */
    qzero_nc(vars + 0x2f0);
    *(int *)(vars + 0x64c) = 0;
    *(int *)(vars + 0x70c) = 0;
    if (!keep) {
        *(int *)(vars + 0x3a4) = 0;
        *(int *)(vars + 0x314) = -1;
        *(int *)(vars + 0x3b8) = 0;
        *(int *)(vars + 0x310) = 0;
        *(int *)(vars + 0x318) = 0;
    }
    for (other_moby = D_L04_001B24E8; other_moby; other_moby = *(unsigned char **)(other_moby + 0x28)) {
        unsigned short type = *(unsigned short *)(other_moby + 0xaa);
        if ((unsigned int)(type - 0xb3d /* moby classes 2877-2880 */) < 4 || (short)type == 0x27f /* moby class 639 */ ||
            (short)type == 0x70 /* moby class 112 */ || (short)type == 0x7a /* moby class 122 */) {
            moby_mark_spawned(other_moby);
        }
    }
    *(int *)(vars + 0x388) = 0;
}



/* func_L04_0040A628 is in L04_00402D90-racers-g8.c. */

/* func_L04_0040A958 is in L04_00402D90-reset-g8.c. */

extern signed char *g_moby_l04_pool __attribute__((sda));

extern void func_40E248(char *a0, char *a1);

/* Retail reaches its record base off $gp (a small-data symbol), and the three
   state words at 0x48 of the record and of the indexed record. */
/* Lets go of the racer sound handles and clears a state word on the racer and on the racer it is linked to. */
void racer_release_link_state(char *moby, char *vars)
{
    char *moby_copy = moby;
    char *vars_copy = vars;

    func_40E248(moby_copy, vars_copy);
    *(int *)(moby_copy + 0x48) = 0;
    if (*(int *)(vars_copy + 0x1DC) != -1) {
        *(int *)((*(int *)(vars_copy + 0x1DC) << 8) + (int)g_moby_l04_pool + 0x48) = 0;
    }
}

/* func_L04_0040AC98 reaches its global off $gp, so its body lives in
   L04_00402D90-g8.c. */

/* func_L04_0040ACA8 reaches one of its globals absolutely and another off $gp,
   so its body lives in L04_00402D90-g8.c. */


/* func_L04_0040AD28 is defined in L04_00402D90-results-g8.c. */

/* func_L04_0040BA68 reaches its small globals off $gp, so its body lives in
   L04_00402D90-select-g8.c. */

typedef unsigned int L04Quad __attribute__((mode(TI)));
extern int func_0030FF98(float);
extern int func_0033BA80(int);
extern float func_0033BB18(float, float);
extern void func_L04_003C4AF8(void *, float);
/* The EE assigns the point, parameter and mode to a0-a2, and the two
 * float arguments to f12-f13, independently of their C interleaving. */
extern void func_0035BF30(void *, float, float, void *, int);
/* Spawns a puff of smoke and a few small sparks at a position. Stronger hits make more of them. */
void part_spawn_impact_smoke_and_sparks(L04Quad *position, int count, float value, float intensity)
{
    float origin[4];
    float point[4];
    float parameter;
    float *base = origin;
    *(L04Quad *)origin = *position;
    parameter = value;
    if (intensity >= 0.12f) {
        if (!func_0033BA80(func_0030FF98(1.0f / intensity) + 1))
            func_L04_003C4AF8(origin, func_0033BB18(0.5f, 1.25f) * intensity * 9.0f);
    }
    if (intensity >= 0.1f) {
        if (count > 0) do {
            point[0] = base[0] + func_0033BB18(-0.3f, 0.3f);
            count--;
            point[1] = base[1] + func_0033BB18(-0.3f, 0.3f);
            point[2] = base[2];
            func_0035BF30(point, func_0033BB18(0.3f, 0.6f), 5250.0f, &parameter, -1);
        } while (count != 0);
    }
}




/* Throws a burst of small coloured particles from a point, flying roughly along a direction. */
void part_l04_spawn_burst(L04Quad *position, L04Quad *direction, int count, int mode)
{
    float velocity[4], point[4], scaled[4], result[4];
    float size, angle, pitch;
    int sign, i;
    for (i = 0; i < count; i++) {
        size = func_0033BB18(0.025f, 0.5f);
        sign = func_0033BA80(2);
        if (!sign) sign--;
        angle = func_0033BBE0();
        pitch = func_0033BB18(0.6981318f, 1.5358899f);
        vec_build_spherical_offset(velocity, func_0033BB18(0.012500001f, 0.025000002f), angle, pitch);
        *(L04Quad *)scaled = *direction;
        FastVecScale(scaled, direction, func_0033BB18(0.75f, 0.95f));
        if (mode) {
            velocity[0] *= 5.0f;
            velocity[1] *= 5.0f;
            size *= 3.0f;
        }
        add_vectors(result, velocity, scaled);
        qcopy(point, position);
        point[0] += func_0033BB78(0.0f, 0.0375f);
        point[1] += func_0033BB78(0.0f, 0.0375f);
        point[2] += func_0033BB78(0.0f, 0.0375f);
        part_spawn_ground_effect(point, 30, 0x7f207f7f, 0, sign, velocity, size * 0.1f, size, 0.003f, 0);
        part_spawn_ground_effect(point, 30, 0x7f7f7f7f, 1, -sign, velocity, size * 0.07f, size * 0.7f, 0.003f, 0);
    }
}

extern void DrawPulsingGlowSphere();

extern void racer_emit_exhaust_particles();

/* Draws the glow around a racer: the pulsing sphere when it has a shield, otherwise the normal flame effect. */
void racer_draw_glow_effects(unsigned char *moby)
{
    unsigned char *vars = *(unsigned char **)(moby + 0x68);

    if (*(unsigned int *)(vars + 0x4D8) != 0) {
        DrawPulsingGlowSphere(moby, -1);
    } else if (*(unsigned int *)(vars + 0x768) != 0) {
        DrawPulsingGlowSphere(moby, *(unsigned int *)(vars + 0x764));
    } else if (*(unsigned char *)(moby + 0xBC) != 6) {
        racer_emit_exhaust_particles(moby);
    }
}

extern void moby_transform_joint_to_world(void *, int, void *);

extern void FastVecScale(void *, void *, float);

extern void FastVecAdd(void *, void *, void *);

extern float IntToFloat(int);

/* The five floats come first and the two ints last: the floats then go to
   f12-f16 and the ints to a1 and a2, and the int argument is set up after
   the float ones, as the retail code has it. */
extern void gfx_draw_flash_quad(void *, float, float, float, float, float, int, int);

/* The emitter table the object points at: the slot id at 0x644, then the
   four rows of four heights from 0x660 on. */
typedef struct {
    char pad_000[0x644];
    int slot;
    char pad_648[0x18];
    float row660[4];
    float row670[4];
    float row680[4];
    float row690[4];
} L04_0040CE30_OBJ;

/* Walks the four rows of the emitter table: every row's height is lowered by
   the shared floor, the three threshold vectors are nudged by the row's share
   and handed to the particle scheduler, and a row that sinks too far is lifted
   back to the floor. */
void racer_emit_exhaust_particles(char *moby)
{
    L04_0040CE30_OBJ *emitters = *(L04_0040CE30_OBJ **)(moby + 0x68);
    float vec3[4];
    float vec4[4];
    float vec2[4];
    float tmp[4];
    char *dir = moby + 0xC0;
    int i;

    for (i = 0; i < 4; i++) {
        float row_fraction;
        float rise;
        float size;

        moby_transform_joint_to_world(moby, 2, vec2);
        moby_transform_joint_to_world(moby, 3, vec3);
        moby_transform_joint_to_world(moby, 4, vec4);

        emitters->row670[i] = emitters->row670[i] - emitters->row660[i];
        FastVecScale(tmp, dir, emitters->row670[i]);
        FastVecAdd(vec3, vec3, tmp);

        row_fraction = IntToFloat(i) * 0.25f;
        rise = row_fraction * 0.1f;
        vec3[2] = vec3[2] + rise;
        size = row_fraction * -0.025f + 0.05f;
        gfx_draw_flash_quad(vec3, size, 0.0f, 0.0f, 0.0f, 0.0025f, emitters->slot, 1);
        if (emitters->row670[i] < -0.2f) {
            emitters->row670[i] = -0.05f;
        }

        emitters->row680[i] = emitters->row680[i] - emitters->row660[i];
        FastVecScale(tmp, dir, emitters->row680[i]);
        FastVecAdd(vec2, vec2, tmp);
        vec2[2] = vec2[2] + rise;
        gfx_draw_flash_quad(vec2, size, 0.0f, 0.0f, 0.0f, 0.0025f, emitters->slot, 1);
        if (emitters->row680[i] < -0.2f) {
            emitters->row680[i] = -0.05f;
        }

        emitters->row690[i] = emitters->row690[i] - emitters->row660[i];
        FastVecScale(tmp, dir, emitters->row690[i]);
        FastVecAdd(vec4, vec4, tmp);
        vec4[2] = vec4[2] + rise;
        gfx_draw_flash_quad(vec4, row_fraction * -0.050000004f + 0.075f, 0.0f, 0.0f, 0.0f, 0.0025f, emitters->slot, 1);
        if (emitters->row690[i] < -0.19f) {
            emitters->row690[i] = -0.05f;
        }
    }
}

/* func_L04_0040DCA8 is defined in L04_0040DCA8-quad.c. */


extern BatchA_A04_u8 g_sound_state[];

extern void snd_stop_voice(int handle);

/* Releases the callback records this moby still holds: every handle slot that is set
   names a record of the callback table, and the one that belongs to this moby is
   handed to the release helper. Each slot is cleared afterwards. */
/* Stops the sounds this racer has started and clears the handles it kept for them. */
void racer_release_sound_handles(int moby_address, BatchA_A04_u8 *vars_arg)
{
    int id = moby_address;
    BatchA_A04_u8 *vars = vars_arg;
    int handle_index;
    BatchA_A04_u8 *record;

    handle_index = *(int *)(vars + 0x748);
    if (handle_index != -1) {
        record = g_sound_state + handle_index * 0x70;
        if (*(int *)(record + 0x88) == id && record[0x74] != 0) {
            snd_stop_voice(handle_index);
        }
    }
    *(int *)(vars + 0x748) = -1;

    handle_index = *(int *)(vars + 0x74C);
    if (handle_index != -1) {
        record = g_sound_state + handle_index * 0x70;
        if (*(int *)(record + 0x88) == id && record[0x74] != 0) {
            snd_stop_voice(handle_index);
        }
    }
    *(int *)(vars + 0x74C) = -1;

    handle_index = *(int *)(vars + 0x714);
    if (handle_index != -1) {
        record = g_sound_state + handle_index * 0x70;
        if (*(int *)(record + 0x88) == id && record[0x74] != 0) {
            snd_stop_voice(handle_index);
        }
    }
    *(int *)(vars + 0x714) = -1;

    handle_index = *(int *)(vars + 0x3BC);
    if (handle_index != -1) {
        record = g_sound_state + handle_index * 0x70;
        if (*(int *)(record + 0x88) == id && record[0x74] != 0) {
            snd_stop_voice(handle_index);
        }
    }
    *(int *)(vars + 0x3BC) = -1;

    handle_index = *(int *)(vars + 0x328);
    if (handle_index != -1) {
        record = g_sound_state + handle_index * 0x70;
        if (*(int *)(record + 0x88) == id && record[0x74] != 0) {
            snd_stop_voice(handle_index);
        }
    }
    *(int *)(vars + 0x328) = -1;

    handle_index = *(int *)(vars + 0x330);
    if (handle_index != -1) {
        record = g_sound_state + handle_index * 0x70;
        if (*(int *)(record + 0x88) == id && record[0x74] != 0) {
            snd_stop_voice(handle_index);
        }
    }
    *(int *)(vars + 0x330) = -1;

    handle_index = *(int *)(vars + 0x334);
    if (handle_index != -1) {
        record = g_sound_state + handle_index * 0x70;
        if (*(int *)(record + 0x88) == id && record[0x74] != 0) {
            snd_stop_voice(handle_index);
        }
    }
    *(int *)(vars + 0x32C) = 0;
    *(int *)(vars + 0x334) = -1;
    *(int *)(vars + 0x324) = 0;
}

/* Inlining puts the literal rate straight into $f12, so each call loads it again. */
static inline void CallL00_00322AC0(void *state, float rate, int level, int slot)
{
    level_append_record_to_table(state, rate, level, slot);
}

/* Updates the racer boost each frame: collects nearby boost pickups, charges the boost, and keeps the boost flame, sound and camera zoom going. */
void racer_update_boost(unsigned char *moby)
{
    float delta[4], rotation[16];
    unsigned char *pickup_moby, *boost_moby;
    int red, green, blue;
    int period = 50;
    int alpha = 128;
    unsigned char *vars = *(unsigned char **)(moby + 0x68);
    unsigned char *state;
    int *data;
    float wave, active, angle, sine, radius;
    unsigned int color;
    angle = IntToFloat(period);
    red = D_L04_001B2008[0] % period;
    {
        float phase = (float)red;
        wave = math_fast_sin_or_cos_b(((phase / angle) * 2.0f) * 3.1415927f + -3.1415927f);
    }
    red = FloatToInt(wave * 48.0f) + 104;
    green = FloatToInt(wave * 64.0f) + 208;
    blue = FloatToInt(wave * 24.0f) + 60;
    if (green > 255) green = 255;
    if (*(int *)(vars + 0x278)) {
        ApproachValue(vars + 0x27c, 0.16666669f, 0.00555555569008f);
        ApproachValue(vars + 0x28c, 97.0f, 0.5666667f);
        if (*(int *)(vars + 0x278)) math_fast_float_d(vars + 0x278);
        moby_update_transform_history_followers(vars + 0x4e0, 1);
        state = vars + 0x4e0;
    } else {
        if ((moby[0x20] == 3 || (D_00138320 & 10)) && *(int *)(vars + 0x338) < 30 && *(int *)(vars + 0x33c) > 0) {
            *(int *)(vars + 0x338) = 240;
            --*(int *)(vars + 0x33c);
            if (moby[0x20] != 3) snd_play_from_class_bank(0, 0, moby, 0x474);
            if (!snd_is_voice_playing_for_owner(moby, *(int *)(vars + 0x714))) {
                if (moby[0x20] != 3) *(int *)(vars + 0x714) = PlayMobySound(15, 4, moby);
                else {
                    *(int *)(vars + 0x714) = PlayMobySound(24, 5, moby);
                    snd_set_slot_field(*(int *)(vars + 0x714), 0x400);
                }
            }
            if (*(unsigned char **)(vars + 0x4c4)) {
                unsigned char *child = *(unsigned char **)(vars + 0x4c4);
                unsigned char *childState = *(unsigned char **)(child + 0x68);
                if (*(float *)(vars + 0x27c) <= 0.016666668f) *(int *)(childState + 0x1c0) = 0;
            }
            if (!*(int *)(vars + 0x640)) {
                level_init_pending_slot(moby, vars + 0x4e0);
                CallL00_00322AC0(vars + 0x4e0, -0.7f, 64, 1);
                CallL00_00322AC0(vars + 0x4e0, -0.7f, 48, 2);
                CallL00_00322AC0(vars + 0x4e0, -0.7f, 32, 3);
                CallL00_00322AC0(vars + 0x4e0, -0.7f, 16, 4);
                *(int *)(vars + 0x640) = 1;
            }
        }
        state = vars + 0x4e0;
        if (math_fast_float_d(vars + 0x338)) {
            active = 0.0f;
            level_release_slot_list(state);
            *(int *)(vars + 0x640) = 0;
        } else {
            active = 1.0f;
            moby_update_transform_history_followers(state, 1);
        }
        ApproachValue(vars + 0x27c, active * 0.10000001f, 0.00138888892252f);
        if (*(float *)(vars + 0x27c) < 0.0f) *(float *)(vars + 0x27c) = 0.0f;
        if (active > 0.5f) ApproachValue(vars + 0x28c, 97.0f, 0.5666667f);
        else ApproachValue(vars + 0x28c, 80.0f, 0.14166668f);
    }
    if (moby[0x20] != 3) {
        float viewAngle = *(float *)(vars + 0x28c);
        viewAngle *= 0.008726647f;
        sine = math_fast_sin_or_cos_b(viewAngle);
        sine /= math_fast_sin_or_cos_a(viewAngle);
        D_L04_001BDC30 = sine;
        UpdateViewContext();
    }
    if (*(int *)(vars + 0x25c) != -1) {
        GetFirstMobyInGroup(&pickup_moby, *(int *)(vars + 0x25c), 0, 0);
        if (pickup_moby) do {
            if (*(short *)(pickup_moby + 0xaa) == 0xa99 /* moby class 2713 */) {
                data = *(int **)(pickup_moby + 0x68);
                FastVecSub(delta, pickup_moby + 0x10, moby + 0x10);
                if (*data == 0 && *(int *)(vars + 0x33c) < 3 && func_L00_002EE290(delta) < 1.0f) {
                    ++*(int *)(vars + 0x33c);
                    if (moby[0x20] != 3) snd_play_from_class_bank(0, 0, moby, 0xa99);
                    part_l04_spawn_burst((L04Quad *)(pickup_moby + 0x10), (L04Quad *)(vars + 0x290), 8, 0);
                    *data = 300;
                }
            }
            GetNextMobyInGroup(&pickup_moby, pickup_moby, 0, 0);
        } while (pickup_moby);
    }
    if (*(int *)(vars + 0x254) != -1) {
        GetFirstMobyInGroup(&boost_moby, *(int *)(vars + 0x254), 0, 0);
        if (boost_moby) {
            /* One four-term OR would be rebalanced by fold, so the terms join in steps. */
            unsigned int high = (alpha << 24) | (blue << 16);
            high |= green << 8;
            color = high | red;
            do {
                if (*(short *)(boost_moby + 0xaa) == 0x474 /* moby class 1140 */) radius = 1.25f;
                else if (*(short *)(boost_moby + 0xaa) == 0xcef /* moby class 3311 */) radius = 3.75f;
                else goto next;
                *(unsigned short *)(boost_moby + 0x34) |= 16;
                *(unsigned int *)(boost_moby + 0x78) = color;
                if (!vec_fast_helper_a(boost_moby + 0xbc)) goto next;
                FastVecSub(delta, boost_moby + 0x10, g_hero_position);
                if (FastVecDot(delta, delta) > 20.0f) goto next;
                set_identity_matrix(rotation);
                matrix_from_basis_rows(rotation, boost_moby + 0xc0);
                transform_vector(delta, delta, rotation);
                if (!(math_fabs(delta[0]) < 2.8f) || !(math_fabs(delta[1]) < radius) || !(math_fabs(delta[2]) < 1.5f)) goto next;
                data = *(int **)(boost_moby + 0x68);
                *(int *)(vars + 0x278) += *data;
                if (!snd_is_voice_playing_for_owner(moby, *(int *)(vars + 0x714))) {
                    if (moby[0x20] != 3) *(int *)(vars + 0x714) = PlayMobySound(15, 4, moby);
                    else {
                        *(int *)(vars + 0x714) = PlayMobySound(24, 5, moby);
                        snd_set_slot_field(*(int *)(vars + 0x714), 0x400);
                    }
                }
                if (moby[0x20] != 3) PlayMobySound(12, 0, moby);
                *(int *)(vars + 0x650) = *data;
                boost_moby[0xbc] = 60;
                if (*(unsigned char **)(vars + 0x4c4)) {
                    unsigned char *child = *(unsigned char **)(vars + 0x4c4);
                    unsigned char *childState = *(unsigned char **)(child + 0x68);
                    if (*(float *)(vars + 0x27c) <= 0.016666668f) *(int *)(childState + 0x1c0) = 0;
                }
                if (!*(int *)(vars + 0x640)) {
                    level_init_pending_slot(moby, vars + 0x4e0);
                    CallL00_00322AC0(vars + 0x4e0, -0.7f, 64, 1);
                    CallL00_00322AC0(vars + 0x4e0, -0.7f, 48, 2);
                    CallL00_00322AC0(vars + 0x4e0, -0.7f, 32, 3);
                    CallL00_00322AC0(vars + 0x4e0, -0.7f, 16, 4);
                    *(int *)(vars + 0x640) = 1;
                }
next:
                GetNextMobyInGroup(&boost_moby, boost_moby, 0, 0);
            } while (boost_moby);
        }
    }
}

/* func_L04_0040EC80 is in L04_00402D90-aim.c. */

/* func_L04_0040EF50 is in L04_00402D90-g8.c. */

/* Measures the main route and its branch routes and works out where each branch joins and leaves the others. */
void race_recompute_branch_route_links(unsigned char *moby)
{
    float delta[4];
    L04PathState *vars = *(L04PathState **)(moby + 0x68);
    unsigned char *base, *path, *other;
    int i, j;
    float closest, index, distance;
    if (vars->primary == -1) return;
    base = g_route_path_table[vars->primary];
    if (*(int *)base < 3) {
        vars->primary = -1;
        return;
    }
    *(float *)(base + 0x1c) = fast_vec_dist(base + 0x10, base + 0x20);
    for (i = 0; i < 4; i++) {
        if (vars->branches[i] == -1) continue;
        path = g_route_path_table[vars->branches[i]];
        if (*(int *)path >= 4) {
            *(float *)(path + 0x1c) = fast_vec_dist(path + 0x10, path + 0x20);
            index = 0.0f;
            closest = 999999.0f;
            if (vars->parents[i] != -1) other = g_route_path_table[vars->branches[vars->parents[i]]];
            else other = base;
            for (j = 0; j < *(int *)other - 1; j++) {
                FastVecSub(delta, other + 0x10 + j * 16, path + 0x10);
                distance = func_L00_002EE290(delta);
                if (distance < closest) {
                    index = IntToFloat(j);
                    closest = distance;
                }
            }
            *(float *)(path + 0x2c) = index;
            *(float *)(path + 0x4c) = fast_vec_dist(other + 0x10 + FloatToInt(index) * 16, path + 0x10) + *(float *)(path + 0x2c) * *(float *)(other + 0x1c);
            index = 0.0f;
            closest = 999999.0f;
            if (vars->links[i] != -1) other = g_route_path_table[vars->branches[vars->links[i]]];
            else other = base;
            for (j = 0; j < *(int *)other - 1; j++) {
                FastVecSub(delta, other + 0x10 + j * 16, path + *(int *)path * 16);
                distance = func_L00_002EE290(delta);
                if (distance < closest) {
                    index = IntToFloat(j);
                    closest = distance;
                }
            }
            *(float *)(path + 0x3c) = index;
            *(float *)(path + 0x5c) = fast_vec_dist(other + 0x10 + FloatToInt(index) * 16, path + *(int *)path * 16) + *(float *)(path + 0x3c) * *(float *)(other + 0x1c);
        } else vars->branches[i] = -1;
    }
}

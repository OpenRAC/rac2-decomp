#include "common.h"

/* The actor object: position, stage and flags at fixed offsets, its state block behind `state`. */
typedef struct {
    u8 pad00[0x10];
    float position[4];
    u8 stage;
    u8 pad21[0x10];
    u8 active;
    u8 pad32[0x68 - 0x32];
    void *state;
    u8 pad6C[3];
    u8 f6F;
    u8 pad70[0xAA - 0x70];
    s16 id;
} JobaObject;

/* What func_002A9640 finds: the object that was hit, and a field cleared on it. */
typedef struct {
    u8 pad00[0x20];
    JobaObject *object;
    u8 pad24[8];
    s32 f2C;
} HitRecord;

/* State block of the main actor (offsets as the retail code reads them). */
typedef struct {
    u8 pad00[0x28];
    u8 f28;
    u8 f29;
    u8 pad2A[4];
    u8 f2E;
    u8 pad2F;
    float f30;
    u8 pad34[0x48 - 0x34];
    u8 f48;
    u8 pad49;
    u8 f4A;
    u8 pad4B[5];
    char contact[0x10];
    u8 f60;
    u8 pad61[0x80 - 0x61];
    float f80;
    float f84;
    u8 pad88[4];
    float f8C;
    u8 pad90[8];
    s32 f98;
    u8 pad9C[0xE0 - 0x9C];
    s32 fE0;
    float fE4;
    u8 padE8[0x100 - 0xE8];
    float f100;
    float f104;
    float f108;
    float f10C;
    float f110;
    u8 pad114[0x12C - 0x114];
    float f12C;
    float f130;
    float f134;
    u8 pad138[0x256 - 0x138];
    s16 f256;
} JobaActorState;

/* State block of the point-ring effect: up to eight 16-byte points, then its tuning values. */
typedef struct {
    float points[8][4];
    s32 count;
    float minRadius;
    float maxRadius;
    float maxElevation;
    float minElevation;
    float f94;
    float f98;
    float f9C;
    float fA0;
    float fA4;
} JobaRingState;

/* The resident player block: its position and the player object. */
typedef struct {
    u8 pad00[0x80];
    float position[4];
    u8 pad90[0x2290 - 0x90];
    JobaObject *player;
} PlayerBlock;

extern int coll_process_hit(int, int, void *, int, float);
extern void part_queue_impact_effect(void *, void *, int, float, float *, float *);
extern PlayerBlock g_hero_state;
extern JobaObject *g_damage_target_list[];
extern int FloatToInt(float);
extern HitRecord *part_find_owned_effect_slot(void *, int, int);
extern int moby_apply_damage_to_object(void *, void *, int);
extern float fast_vec_dist(void *, void *);
extern void moby_update_ground_check(void *);
extern char g_hero_l11_position[];
extern void vec_build_spherical_offset(void *, float, float, float);
extern void FastVecAdd(void *, void *, void *);
extern float fast_subtract_rotations(float, float);
extern float math_random_signed_float_range(float, float);
extern void gfx_add_draw_callback_third(void *, char *);

typedef int TI128 __attribute__((mode(TI)));


extern void func_00282D30_2(char *dst, char *src, float scale);
extern void moby_set_state(void *a0, int a1, int a2);
extern void gfx_update_color_fade(void *a0, void *a1);
extern void set_moby_color(void *a0, int a1, int a2, int a3);
extern int coll_sweep_from_object(void *a0, void *a1, int a2, float f12, float f13, float f14,
                          int a3, int t0, int t1);
extern void gfx_l11_draw_beam_strips();
extern void gfx_l11_draw_billboard_flare();
extern void joba_effect_spawn_quad();
extern float mat_fast_helper_a(float a, float b);
extern float math_random_float_range(float a, float b);
extern float math_fast_sin_or_cos_a(float x);
extern float math_fast_sin_or_cos_b(float x);

extern void anim_start_blended(void *a0, int a1, int a2, int a3);

extern void func_002A05A8(void *a0);

extern void arena_add_waiting_fighter(char *p, int id);

extern int arena_consume_waiting_fighter(char *p, int id);

extern int weapon_select_aim_target(void *a0, int a1, int a2, int a3, float f12, float f13);

extern void moby_set_controller_speed_limits(void *a0, float f12, float f13, float f14, float f15);

extern s32 math_random_int_range(int a0, int a1);

extern float math_random_angle(void);

extern void gfx_draw_billboard_quad(void *a0, void *a1, void *a2, float f12, float f13,
                          float f14, int a3);

extern int part_spawn_damage_debris(void *a0, void *a1, void *a2, int a3);

extern void func_002A0F48(void *a0);

extern void gfx_add_draw_callback_first(void *a0, void *a1);

extern char *CreateMoby(int);
extern void moby_init_child_from_parent(char *, char *);
extern int IsPointInCuboid(void *, int);
extern void moby_transform_joint_to_world(char *, int, void *);
extern void transform_vector(void *, void *, void *);
extern u8 *hoverbike_bomb_spawn(u8 *, u8 *, u8 *, float);
extern float FastAddRotations(float, float);
extern void FastVecScale(void *, void *, float);
extern void *part_spawn_object_relative_particle(char *, void *, void *, void *, int);
extern char g_hero_position[];
extern int g_l11_companion_record_index[] NOT_SDA __attribute__((sda));
/* 64-byte records indexed by D_L11_001B089C[0]. */
typedef struct { int unused; int flags; char pad[56]; } Entry61308;
extern Entry61308 g_carrier_entry_table[];
extern char *g_moby_l11_table[] NOT_SDA __attribute__((sda));
extern char *g_arena_camera_table[] NOT_SDA __attribute__((sda));
/* Lower and upper bound of a random value. */
extern float g_carrier_float_params[] NOT_SDA __attribute__((sda));
extern char g_carrier_particle_c[] NOT_SDA __attribute__((sda));
extern char g_carrier_particle_b[] NOT_SDA __attribute__((sda));
extern char g_carrier_particle_a[] SDATA(D_L11_001B2358);

extern void gfx_draw_spinning_glow_sprites(char *p);

extern int g_enemy_freeze_flag;

extern int g_pulse_last_value;

extern int g_arena_progress_level;

extern void part_draw_billboard_sprite(char *a0, void *a1, void *a2, int a3, int t0, float f12,
                              float f13);

/* The vector the aim helpers read, at 0x001BA780 in joba. */
typedef struct {
    char pad_000[0x140];
    float x_140;
    float y_144;
    float z_148;
} L11AimVector;

extern L11AimVector g_hero_l11_state_block;

extern void part_reset_quad_record_c(char *pkt);

extern long long GetEffectTextureDescriptor(char *p);

extern float vec_distance_xy(void *p, float *v);

extern void euler_to_matrix(float *matrix, float *quat);

extern void FastVecSub(float *out, float *a, float *b);

extern void vec_scale_to_length(float *dst, float *src, float scale);

extern void draw_world_quad(char *pkt, float *matrix, int mode);
extern void snd_stop_voice(int index);

extern int snd_play_from_class_bank(int index, int value, char *object, int kind);

extern char *SpawnExplosion(char *, int, int, int, int, int, int, int, float, float, int,
                         int, int, int);

extern void vec_clear_128(void *);

extern int moby_spawn_linked(char *, int, float, float);

extern char g_sound_state[];

extern void fighter_reset_to_idle(char *);
extern void fighter_update_lock_on(char *);
extern void joba_ring_effect_draw_sprites(void);

/* func_L11_00453358 lives in L11_00453358-state-g8.c. */

/* func_L11_00454508 lives in the sibling small-data unit (L11_00453358-g8.c). */

/* Keeps the actor's timer going: re-arms its effect once a timer reaches zero, and counts the frames it has lived. */
void drone_update_timer(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    unsigned short frame_count;

    gfx_update_color_fade(moby, vars + 0x50);
    if (*(short *)(vars + 0x50) == 0) {
        if (*(short *)(vars + 0x1FE) == 0) {
            set_moby_color(moby, *(int *)(vars + 0x1F0), *(int *)(vars + 0x1F4), *(int *)(vars + 0x1F8));
            *(short *)(vars + 0x1FE) = 1;
        }
    } else {
        *(short *)(vars + 0x1FE) = 0;
    }
    frame_count = *(unsigned short *)(moby + 0x96);
    if (frame_count <= 0xFFFE)
        *(unsigned short *)(moby + 0x96) = frame_count + 1;
}

extern void func_002A7750_4b60();
extern int func_002B3BA8_4b60(void *, u32, float, float, int, int);

/* Same body as func_L02_0040CF68, with this function's own callees. */
/* Checks whether the actor still has a target to lock on to, and sends it back to patrolling when it loses it. */
void drone_update_lock_on(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);

    if (moby[0x20] < 4) {
        *(u16 *)(vars + 0x1EC) = 0;
        *(s32 *)(vars + 0x1C4) = 0;
    } else {
        if (*(s16 *)(vars + 0x1EC) == 1) {
            *(s16 *)(vars + 0x1EA) = func_002B3BA8_4b60(moby, *(u32 *)(vars + 0x1E4), 100.0f, 100.0f, 0, 0);
            *(s32 *)(vars + 0x1C4) = *(s32 *)(vars + 0x160);
        } else {
            if (moby[0x31] != 0 && arena_consume_waiting_fighter(*(void **)(moby + 0xB8), *(s16 *)(moby + 0xAA)) != 0) {
                *(u16 *)(vars + 0x1EC) = 1;
                *(s16 *)(vars + 0x1EA) = func_002B3BA8_4b60(moby, *(u32 *)(vars + 0x1E4), 100.0f, 100.0f, 0, 0);
                *(s32 *)(vars + 0x1C4) = *(s32 *)(vars + 0x160);
            } else {
                *(u16 *)(vars + 0x1EC) = 0;
                if (moby[0x20] == 0xB || moby[0x20] == 8) {
                    if (*(s32 *)(vars + 0x1C0) != -1)
                        func_002A7750_4b60(moby, 7, 3);
                    else
                        func_002A7750_4b60(moby, 5, 2);
                }
            }
        }
    }
}


/* Aims the object's stage, re-arms its effect and stores the new heading. */
void drone_init_state(char *moby, int delay, int mode)
{
    char *vars = *(char **)(moby + 0x68);
    char *definition;
    unsigned short flags;
    int cache;
    float value;

    value = (float)*(short *)(vars + 0x24);
    *(short *)(vars + 0x1FC) = mode;
    *(short *)(vars + 0x1EC) = 0;
    *(unsigned char *)(vars + 0x2E) = 1;
    *(float *)(vars + 0x20) = value;
    if (*(unsigned char *)(moby + 0x43) != 0)
        anim_start_blended(moby, 0, 0, 10);
    flags = *(unsigned short *)(moby + 0x34);
    *(unsigned char *)(moby + 0x7F) = 0;
    *(unsigned short *)(moby + 0x34) = (flags | 0x1000) & 0xFFB9;
    definition = *(char **)(moby + 0x24);
    cache = *(int *)(definition + 0x10);
    *(int *)(moby + 0x98) = cache;
    if (*(short *)(vars + 0x1FC) != 0) {
        moby_set_state(moby, 7, 3);
        *(unsigned short *)(moby + 0x34) |= 0x100;
        moby_spawn_linked(moby, 0, 2.0f, 2.0f);
    } else {
        moby_set_state(moby, 3, 1);
        *(unsigned char *)(moby + 0x31) = 1;
        *(unsigned short *)(moby + 0x34) &= 0xFEFE;
    }
    vec_clear_128(vars + 0x1B0);
    value = math_random_float_range(20.0f, 30.0f) * 0.017453294f;
    *(short *)(vars + 0x1EE) = delay;
    *(float *)(vars + 0x1CC) = value;
    if (*(short *)(vars + 0x50) != 0) {
        *(short *)(vars + 0x50) = 0;
        set_moby_color(moby, *(int *)(vars + 0x1F0), *(int *)(vars + 0x1F4), *(int *)(vars + 0x1F8));
        *(short *)(vars + 0x52) = 1;
    }
}

/* Releases the object's slot in the shared table and drops it to the idle flag block. */
void drone_reset_to_idle(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    int slot = *(int *)(vars + 0x1DC);
    char *entry;

    if (slot != -1) {
        entry = g_sound_state + slot * 0x70;
        if (*(char **)(entry + 0x88) == moby && *(unsigned char *)(entry + 0x74) != 0)
            snd_stop_voice(slot);
    }
    *(int *)(vars + 0x1DC) = -1;
    if (*(short *)(vars + 0x1EC) == 1) {
        *(short *)(vars + 0x1EC) = 0;
        arena_add_waiting_fighter(*(char **)(moby + 0xB8), *(short *)(moby + 0xAA));
    }
    if (*(unsigned char *)(moby + 0x31) != 0) {
        SpawnExplosion(moby + 0x10, 0, 10, 30, 0, 10, 45, 1, 0.3f, 0.0f, 0, 0, 0, 0);
        snd_play_from_class_bank(0, 0, moby, 0xDF7);
    }
    anim_start_blended(moby, 0, 0, 3);
    func_002A05A8(moby);
    moby_set_state(moby, 1, 0);
    *(unsigned short *)(moby + 0x34) = (*(unsigned short *)(moby + 0x34) & 0xEFFF) | 0x47;
    *(int *)(moby + 0x98) = 0;
    *(unsigned char *)(moby + 0x31) = 0;
    *(short *)(vars + 0x1EC) = 0;
    *(int *)(vars + 0x1C4) = 0;
}

/* func_L11_00454F18 lives in L11_00454F18-g8.c. */

/* Sets up the actor's tuning on its first stage, handles contacts while active, and runs the
   attack-state update. */
void fighter_update_contacts(JobaObject *obj)
{
    JobaActorState *state = obj->state;
    HitRecord *hit;
    JobaObject *other;

    if (obj->stage == 0) {
        state->f48 = FloatToInt(15.0f);
        state->f4A = FloatToInt(12.0f);
        state->f80 = 0.5f;
        state->f84 = 0.5f;
        state->f108 = 0.5f;
        state->f256 = 0;
        state->f60 = 13;
        state->f98 = 4;
        state->f8C = 0.4f;
        state->f100 = 1.0f;
        state->f104 = 0.25f;
        state->f10C = 0.5f;
        state->f110 = 1.57079649f;
        state->f130 = 0.52359885f;
        state->f134 = 0.01f;
        state->f12C = 0.00555555569f;
        state->f28 = 3;
        state->f30 = 0.75f;
        state->f29 = 1;
        fighter_reset_to_idle((char *)obj);
    }

    if (obj->active) {
        if (obj->stage >= 3) {
            hit = part_find_owned_effect_slot(obj, 0x10000, 1);
            if (hit && (other = hit->object) && !obj->active) {
                if (other->id == 0xDF9 /* moby class 3577 */ || other->id == 0xB89 /* moby class 2953 */)
                    hit->f2C = 0;
            }
            if (moby_apply_damage_to_object(obj, state->contact, 0) == 5) {
                state->fE0 = 0;
                state->fE4 = 0.837758183f;
            }
        }
        if (obj->active && fast_vec_dist(obj->position, g_hero_l11_position) < 24.0f) {
            moby_update_ground_check(obj);
            obj->f6F = 22;
        }
    }

    if (obj->stage >= 2 && state->f2E == 2)
        fighter_reset_to_idle((char *)obj);
    fighter_update_lock_on((char *)obj);
}

/* Counts one more frame for the object and checks what it touches. */
void fighter_count_frame_check_contact(char *moby)
{
    unsigned short frame_count = *(unsigned short *)(moby + 0x96);

    if (frame_count < 0xFFFF)
        *(unsigned short *)(moby + 0x96) = frame_count + 1;
    coll_sweep_from_object(moby, moby + 0x10, 0x4000000, 1.6f, 1.0f, 1.0f, 0, 1, 0);
}

extern int func_002B3BA8_6378(char *, int, float, float, int, int);

/* Same body as func_L02_003F16F0, with this function's own callees. */
/* Starts or stops the lock-on on the target depending on the object's state. */
void fighter_update_lock_on(char *moby) {
    char *state = *(char **)(moby + 0x68);

    if (*(unsigned char *)(moby + 0x20) < 4) {
        *(int *)(state + 0x240) = 0;
        goto done;
    }

    if (*(short *)(state + 0x256) == 1) {
        *(short *)(state + 0x254) =
            func_002B3BA8_6378(moby, *(int *)(state + 0x24C), 100.0f, 100.0f, 0, 0);
        *(int *)(state + 0x240) = *(int *)(state + 0x220);
    } else {
        if (arena_consume_waiting_fighter(*(int *)(moby + 0xB8), *(short *)(moby + 0xAA)) == 0)
            goto done;
        *(short *)(state + 0x256) = 1;
        *(short *)(state + 0x254) =
            func_002B3BA8_6378(moby, *(int *)(state + 0x24C), 100.0f, 100.0f, 0, 0);
        *(int *)(state + 0x240) = *(int *)(state + 0x220);
    }
    return;

done:
    *(short *)(state + 0x256) = 0;
}


/* Retires the state's counter and drops the object to its idle flag block. */
void fighter_reset_to_idle(char *moby)
{
    char *vars = *(char **)(moby + 0x68);

    if (*(short *)(vars + 0x256) == 1) {
        arena_add_waiting_fighter(*(char **)(moby + 0xB8), 0xDF9 /* moby class 3577 */);
    }
    *(short *)(vars + 0x256) = 0;
    *(int *)(vars + 0x240) = 0;
    anim_start_blended(moby, 0, 0, 3);
    func_002A05A8(moby);
    moby_set_state(moby, 1, 0);
    *(int *)(moby + 0x98) = 0;
    *(unsigned short *)(moby + 0x34) = (*(unsigned short *)(moby + 0x34) & 0xEFFF) | 0x47;
    *(char *)(moby + 0x31) = 0;
}

/* Same body as func_L02_003F1A88, with this function's own callees. */
/* Picks a random goal spot about eight units from the target and stores it. */
void fighter_pick_goal_near_target(char *moby, char *target_pos) {
    char *state;
    float angle;
    float radius;

    angle = mat_fast_helper_a(*(float *)(moby + 0x10) - *(float *)target_pos,
                          *(float *)(moby + 0x14) - *(float *)(target_pos + 4));
    angle += math_random_float_range(-0.78539824f, 0.78539824f);
    radius = math_random_float_range(-2.0f, 2.0f) + 8.0f;
    state = *(char **)(moby + 0x68);
    qcopy(state + 0x230, target_pos);
    *(float *)(state + 0x230) += radius * math_fast_sin_or_cos_a(angle);
    *(float *)(state + 0x234) += radius * math_fast_sin_or_cos_b(angle);
}

/* func_L11_004566C0 lives in L11_00453358-aim-g8.c. */

/* Defined in L11_00453358-retreat-g8.c. */

/* Damages and knocks back every object within radius of the source, with separate damage,
   scale and lift for the player and for everything else. */
void joba_damage_objects_in_radius(JobaObject *source, int kind, float radius, float playerDamage,
                       float otherDamage, float playerScale, float otherScale, float playerZ,
                       float otherZ)
{
    float pos[4];           /* receives a copy of the target position that is not read again */
    float impulseStorage[4];
    float *impulse;
    int count = coll_process_hit(kind, 0, source, 0, radius);
    JobaObject **entry;
    PlayerBlock *resident;
    int remaining;
    JobaObject *target;
    float *point;
    float scale, z, damage;

    if (count != 0) {
        if (count > 0) {
            impulse = impulseStorage;
            resident = &g_hero_state;
            entry = g_damage_target_list;
            remaining = count;
            do {
                target = *entry;
                if (target == resident->player) {
                    if (playerDamage <= 0.0f)
                        goto next;
                    qcopy(pos, resident->position);
                    scale = playerScale;
                    z = playerZ;
                    damage = playerDamage;
                    point = target->position;
                } else {
                    if (target->id == 0xDF9 /* moby class 3577 */)
                        goto next;
                    qcopy_nc(pos, target->position);
                    point = target->position;
                    scale = otherScale;
                    z = otherZ;
                    damage = otherDamage;
                }
                FastVecSub(impulse, point, source->position);
                impulseStorage[2] = 0.0f;
                vec_scale_to_length(impulse, impulse, scale);
                impulseStorage[2] = z;
                impulseStorage[3] = 5627.925f;
                part_queue_impact_effect(target, source, 0x10001, damage, point, impulse);
            next:
                remaining--;
                entry++;
            } while (remaining != 0);
        }
    }
}

/* Keeps the ring's points inside the configured radial and angular limits. */
void joba_ring_effect_update(JobaObject *obj)
{
    JobaRingState *state = obj->state;
    float *point;
    int i, j;
    float scratch[4];
    float radius, azimuth, elevation, step;

    if (obj->stage == 0) {
        if (state->count > 8)
            state->count = 8;
        obj->stage = 1;
        for (i = 0; i < state->count; i++) {
            float newRadius, newAzimuth;

            newRadius = math_random_float_range(state->minRadius, state->maxRadius);
            newAzimuth = math_random_angle();
            vec_build_spherical_offset(state->points[i], newRadius, newAzimuth, math_random_angle());
            FastVecAdd(state->points[i], obj->position, state->points[i]);
        }
    }

    if (obj->stage == 1) {
        gfx_add_draw_callback_third(joba_ring_effect_draw_sprites, (char *)obj);
        for (j = 0; j < state->count; j++) {
            point = state->points[j];
            FastVecSub(scratch, obj->position, point);
            azimuth = mat_fast_helper_a(point[0] - obj->position[0], point[1] - obj->position[1]);
            elevation = mat_fast_helper_a(vec_distance_xy(obj->position, point),
                                      point[2] - obj->position[2]);
            azimuth = fast_subtract_rotations(azimuth, state->f9C * 0.017453294f);
            elevation = fast_subtract_rotations(elevation,
                                      math_random_signed_float_range(state->fA4, state->fA0) * 0.017453294f);
            if (state->maxElevation < elevation)
                elevation = state->maxElevation;
            if (elevation < state->minElevation)
                elevation = state->minElevation;

            radius = fast_vec_dist(obj->position, point);
            step = math_random_signed_float_range(state->f98 * 0.0166666675f, state->f94 * 0.0166666675f);
            radius += step;
            if (state->maxRadius < radius)
                radius = state->maxRadius;
            if (radius < state->minRadius)
                radius = state->minRadius;

            vec_build_spherical_offset(point, radius, azimuth, elevation);
            FastVecAdd(point, obj->position, point);
        }
    }
}

/* func_L11_00456EA0 lives in L11_00456EA0-g8.c. */

extern void path_measure_segments(int, void *, void *, void *, void *, void *);
extern char g_effect_path_origins_a[] __attribute__((sda));
extern char g_effect_path_origins_b[] __attribute__((sda));
extern char g_effect_path_origins_c[] __attribute__((sda));
extern char g_effect_path_origins_d[] __attribute__((sda));
extern char g_effect_path_origins_e[] __attribute__((sda));
extern char g_effect_path_origins_f[] __attribute__((sda));
extern char g_effect_path_origins_g[] __attribute__((sda));
extern char g_effect_path_origins_h[] __attribute__((sda));
extern char g_effect_path_origins_i[] __attribute__((sda));
extern char g_effect_path_origins_j[] __attribute__((sda));
extern char g_effect_path_velocities_a[] __attribute__((sda));
extern char g_effect_path_velocities_b[] __attribute__((sda));
extern char g_effect_path_velocities_c[] __attribute__((sda));
extern char g_effect_path_velocities_d[] __attribute__((sda));
extern char g_effect_path_velocities_e[] __attribute__((sda));
extern char g_effect_path_velocities_f[] __attribute__((sda));
extern char g_effect_path_velocities_g[] __attribute__((sda));
extern char g_effect_path_velocities_h[] __attribute__((sda));
extern char g_effect_path_durations_a[] __attribute__((sda));
extern char g_effect_path_durations_b[] __attribute__((sda));
extern char g_effect_path_durations_c[] __attribute__((sda));
extern char g_effect_path_durations_d[] __attribute__((sda));
extern char g_effect_path_durations_e[] __attribute__((sda));
extern char g_effect_path_durations_f[] __attribute__((sda));
extern char g_effect_path_durations_g[] __attribute__((sda));
extern char g_effect_path_durations_h[] __attribute__((sda));
extern char g_effect_path_durations_i[] __attribute__((sda));
extern char g_effect_path_durations_j[] __attribute__((sda));
extern char g_effect_path_starts_a[] __attribute__((sda));
extern char g_effect_path_starts_b[] __attribute__((sda));
extern char g_effect_path_starts_c[] __attribute__((sda));
extern char g_effect_path_starts_d[] __attribute__((sda));
extern char g_effect_path_starts_e[] __attribute__((sda));
extern char g_effect_path_starts_f[] __attribute__((sda));
extern char g_effect_path_starts_g[] __attribute__((sda));
extern char g_effect_path_starts_h[] __attribute__((sda));
extern char g_effect_path_starts_i[] __attribute__((sda));
extern char g_effect_path_starts_j[] __attribute__((sda));
extern char g_effect_path_total_a[] __attribute__((sda));
extern char g_effect_path_total_b[] __attribute__((sda));
extern char g_effect_path_total_c[] __attribute__((sda));
extern char g_effect_path_total_d[] __attribute__((sda));
extern char g_effect_path_total_e[] __attribute__((sda));
extern char g_effect_path_total_f[] __attribute__((sda));
extern char g_effect_path_total_g[] __attribute__((sda));
extern char g_effect_path_total_h[] __attribute__((sda));
extern char g_effect_path_total_i[] __attribute__((sda));
extern char g_effect_path_total_j[] __attribute__((sda));
extern char g_path_l11_segment_velocities[];
extern char g_path_l11_segment_velocities_2[];

/* Registers the ten groups of effect tables for this level with one shared helper. */
void joba_register_effect_tables(void) {
    path_measure_segments(4, g_effect_path_origins_a, g_effect_path_velocities_a, g_effect_path_durations_a, g_effect_path_starts_a, g_effect_path_total_a);
    path_measure_segments(2, g_effect_path_origins_b, g_effect_path_velocities_b, g_effect_path_durations_b, g_effect_path_starts_b, g_effect_path_total_b);
    path_measure_segments(4, g_effect_path_origins_c, g_effect_path_velocities_c, g_effect_path_durations_c, g_effect_path_starts_c, g_effect_path_total_c);
    {
        char *data = g_effect_path_velocities_d;
        path_measure_segments(2, g_effect_path_origins_d, data, g_effect_path_durations_d, g_effect_path_starts_d, g_effect_path_total_d);
    }
    path_measure_segments(6, g_effect_path_origins_e, g_path_l11_segment_velocities, g_effect_path_durations_e, g_effect_path_starts_e, g_effect_path_total_e);
    path_measure_segments(8, g_effect_path_origins_f, g_path_l11_segment_velocities_2, g_effect_path_durations_f, g_effect_path_starts_f, g_effect_path_total_f);
    path_measure_segments(2, g_effect_path_origins_g, g_effect_path_velocities_e, g_effect_path_durations_g, g_effect_path_starts_g, g_effect_path_total_g);
    path_measure_segments(4, g_effect_path_origins_h, g_effect_path_velocities_f, g_effect_path_durations_h, g_effect_path_starts_h, g_effect_path_total_h);
    path_measure_segments(4, g_effect_path_origins_i, g_effect_path_velocities_g, g_effect_path_durations_i, g_effect_path_starts_i, g_effect_path_total_i);
    path_measure_segments(2, g_effect_path_origins_j, g_effect_path_velocities_h, g_effect_path_durations_j, g_effect_path_starts_j, g_effect_path_total_j);
}


/* func_L11_004577F8 is defined in L11_00453358-curve.c. */

/* func_L11_004580E8 is defined in L11_004580E8-fighter-g8.c. */

/* func_L11_00458A98 is defined in L11_00453358-g8.c. */

/* func_L11_00458C38 lives in L11_00458C38-g8.c. */

/* Scales four consecutive 16-byte XYZ vectors in place by one scalar through a vector helper. */
void vec_l11_scale_four_2(char *vectors, float scale)
{
    func_00282D30_2(vectors, vectors, scale);
    func_00282D30_2(vectors + 16, vectors + 16, scale);
    func_00282D30_2(vectors + 32, vectors + 32, scale);
    func_00282D30_2(vectors + 48, vectors + 48, scale);
}

/* Switches the object off: clears its flags and puts it in the idle state. */
void moby_disable_to_idle(char *moby)
{
    *(int *)(moby + 0x98) = 0;
    *(unsigned short *)(moby + 0x34) = (*(unsigned short *)(moby + 0x34) | 0x41) & 0xEFFF;
    moby_set_state(moby, 1, -1);
}

/* func_L11_00458F90 is defined in L11_00458F90-qcopy-barrier-g8.c. */


/* func_L11_00459640 and func_L11_00459D48 live in the sibling small-data unit (L11_00453358-g8.c). */

/* Runs the effect's two update steps, then spawns five more particle quads. */
void joba_effect_update_particles(char *moby)
{
    int i;

    gfx_l11_draw_beam_strips(moby);
    gfx_l11_draw_billboard_flare(moby);
    for (i = 4; i >= 0; i--)
        joba_effect_spawn_quad(moby);
}

/* shared native body of family a04928c6 */
/* Fills a draw packet with a plain square that is four units wide. */
void gfx_init_square_packet(char *packet)
{
    *(long long *)(packet + 112) = 0LL;
    *(int *)(packet + 80) = 0;
    *(int *)(packet + 84) = 0;
    *(float *)(packet + 88) = 1.0f;
    *(int *)(packet + 92) = 0;
    *(int *)(packet + 96) = 0;
    *(float *)(packet + 100) = 1.0f;
    *(float *)(packet + 104) = 1.0f;
    *(float *)(packet + 108) = 1.0f;
    *(float *)(packet + 8) = -2.0f;
    *(float *)(packet + 24) = 2.0f;
    *(float *)(packet + 40) = -2.0f;
    *(float *)(packet + 56) = 2.0f;
    *(float *)(packet + 4) = -2.0f;
    *(float *)(packet + 36) = 2.0f;
    *(int *)(packet + 0) = 0;
    *(int *)(packet + 16) = 0;
    *(int *)(packet + 32) = 0;
    *(int *)(packet + 48) = 0;
    *(float *)(packet + 12) = 1.0f;
    *(float *)(packet + 28) = 1.0f;
    *(float *)(packet + 44) = 1.0f;
    *(long long *)(packet + 128) = 0x0000FF9000000260LL;
    *(float *)(packet + 20) = -2.0f;
    *(float *)(packet + 52) = 2.0f;
    *(float *)(packet + 60) = 1.0f;
}

/* Defined in L11_00459F30-g8.c. */

/* func_L11_0045A3C8 is defined in L11_0045A3C8-flags-g8.c. */

/* func_L11_0045A578 lives in the sibling small-data unit (L11_00453358-g8.c). */


/* Defined in L11_00453358-pulse.c. */

/* func_L11_0045B6C8 is defined in L11_0045B6C8-g64.c. */

/* func_L11_0045FA68 is in L11_0045FA68-g8.c. */

/* func_L11_0045FDB0 is defined in L11_00453358-spawn-g8.c. */

/* Scales four consecutive 16-byte XYZ vectors in place by one scalar through a vector helper. */
void vec_scale_four_alt(char *vectors, float scale)
{
    func_00282D30_2(vectors, vectors, scale);
    func_00282D30_2(vectors + 16, vectors + 16, scale);
    func_00282D30_2(vectors + 32, vectors + 32, scale);
    func_00282D30_2(vectors + 48, vectors + 48, scale);
}

/* Builds a 144-byte packet, aims a quaternion at the level's vector from pos through three
   float helpers, derives an offset basis by a fourth, writes the last matrix row from pos
   plus that offset, then dispatches the packet. */
void gfx_draw_aimed_packet(char *pos, int color_base, int alpha, char *texture, int blend_flags,
                       float scale, float roll, float offset_scale)
{
    char pkt[144];
    float m[16];
    float quat[4];
    float off[4];
    long long r;

    part_reset_quad_record_c(pkt);
    r = GetEffectTextureDescriptor(texture);

    *(long long *)(pkt + 136) = ((long long)blend_flags << 2) | 0x8000000040LL;
    *(long long *)(pkt + 128) = 280993940374112LL;
    *(int *)(pkt + 76) = color_base + (alpha << 24);
    *(int *)(pkt + 72) = color_base + (alpha << 24);
    *(int *)(pkt + 68) = color_base + (alpha << 24);
    *(int *)(pkt + 64) = color_base + (alpha << 24);
    *(long long *)(pkt + 112) = 0LL;
    *(long long *)(pkt + 120) = r;

    quat[3] = 0.0f;
    quat[2] = mat_fast_helper_a(g_hero_l11_state_block.x_140 - *(float *)(pos + 0),
                           g_hero_l11_state_block.y_144 - *(float *)(pos + 4));
    quat[1] = -mat_fast_helper_a(vec_distance_xy(pos, &g_hero_l11_state_block.x_140),
                             g_hero_l11_state_block.z_148 - *(float *)(pos + 8));
    quat[0] = roll;

    euler_to_matrix(m, quat);
    FastVecSub(off, &g_hero_l11_state_block.x_140, pos);
    vec_scale_to_length(off, off, offset_scale);

    m[12] = *(float *)(pos + 0) + off[0];
    m[13] = *(float *)(pos + 4) + off[1];
    m[14] = *(float *)(pos + 8) + off[2];
    m[15] = 1.0f;

    vec_scale_four_alt(pkt, scale);
    draw_world_quad(pkt, m, 0);
}

/* func_L11_00461308 lives in L11_00461308.c. */

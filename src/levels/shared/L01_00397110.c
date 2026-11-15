#include "common.h"


extern float math_random_float_range(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void matrix_mul_vec3(void *, void *, void *);
extern float FastVecLength(void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern int FloatToInt(float);
extern char *part_spawn_trail(void *, void *, void *, int, int, int, int, int, int);
extern int func_001163B0(void);






extern int g_current_map_index __attribute__((sda));

extern char D_0019B4A8[];

extern void moby_set_state_in_list(int, int);

extern void moby_set_state(char *, int, int);

/* Counts one more press on the saved switch counter for this moby, then moves it to its next state. */
void moby_increment_saved_switch_counter(char *moby)
{
    unsigned short index_word = *(unsigned short *)(moby + 0xB2);

    if (index_word & 1) {
        char *counter_ptr = (char *)(((short)index_word >> 1) + (g_current_map_index << 10)) + (int)D_0019B4A8;
        unsigned char counter_byte = *(unsigned char *)counter_ptr;

        if (((counter_byte >> 4) & 7) != 7)
            *(unsigned char *)counter_ptr = counter_byte + 0x10;
    } else {
        char *counter_ptr = (char *)(((short)index_word >> 1) + (g_current_map_index << 10)) + (int)D_0019B4A8;
        unsigned char counter_byte = *(unsigned char *)counter_ptr;

        if ((counter_byte & 7) != 7)
            *(unsigned char *)counter_ptr = counter_byte + 1;
    }

    if (*(unsigned char *)(moby + 0x21) != 0xFF)
        moby_set_state_in_list(*(unsigned char *)(moby + 0x21), 1);
    else
        moby_set_state(moby, 1, -1);
}

/* Hides a moby and its three linked parts. */
void moby_hide_with_linked_parts(char *moby)
{
    int i;
    char **part;

    *(unsigned short *)(moby + 0x34) |= 1;
    *(unsigned char *)(moby + 0x31) = 0;
    *(unsigned int *)(moby + 0x98) = 0;
    part = (char **)(*(char **)(moby + 0x68) + 0x14);
    for (i = 2; i >= 0; i--) {
        if (*part != 0) {
            *(unsigned short *)(*part + 0x34) |= 1;
            *(unsigned char *)(*part + 0x31) = 0;
        }
        part++;
    }
}



/* Spawns a burst of dust puffs around a point, flying outward and slightly up. */
void part_spawn_radial_dust_puffs(char *moby, void *position, int count,
                      float speed, float rise, float maxRadius, float minRadius,
                      float size, float endSize)
{
    float offset[4], velocity[4], accel[4];
    int life1, life2, life3;
    char *particle;

    {
        int i;
        for (i = 0; i < count; i++) {
            float x, y;
            x = math_fast_sin_or_cos_a(math_random_float_range(-3.1415927410125732f, 3.1415927410125732f));
            offset[0] = x * math_random_float_range(minRadius, maxRadius);
            y = math_fast_sin_or_cos_b(math_random_float_range(-3.1415927410125732f, 3.1415927410125732f));
            y *= math_random_float_range(minRadius, maxRadius);
            offset[1] = y;
            offset[2] = 0;
            matrix_mul_vec3(offset, offset, moby + 0xC0);
            {
                float range = speed * ((maxRadius - FastVecLength(offset)) * 0.01666666753590107f) / maxRadius;
                vec_scale_to_length(velocity, offset, math_random_float_range(range * 0.25f, range));
            }
            velocity[2] += math_random_float_range(rise * 0.25f, rise) * 0.01666666753590107f;
            qzero_nc(accel);
            FastVecAdd(offset, offset, position);
            velocity[3] = size;
            accel[3] = endSize;
            life1 = FloatToInt(math_random_float_range(15.0f, 25.0f));
            life2 = FloatToInt(math_random_float_range(20.0f, 40.0f));
            life3 = FloatToInt(math_random_float_range(30.0f, 60.0f));
            particle = part_spawn_trail(offset, velocity, accel, 0x50204050, 0x7F7F7F, life1, life2, life3, -1);
            if (particle && (func_001163B0() & 1))
                particle[3] = 0x48;
        }
    }
}





typedef union { int whole __attribute__((mode(TI))); float f[4]; } EffectVector;
extern void SpawnTintedEffects(void *, void *, float, int, int, void *, float, float, unsigned int, void *, float);

/* Spawns a ring of sparks around a moby that fly outward. */
void part_l01_spawn_ring_of_sparks(char *object, int count, float low, float high, float radius, float speed)
{
    EffectVector position, velocity;
    float angle;
    int i;
    position.whole = 0;
    velocity.whole = 0;
    for (i = 0; i < count; i++) {
        angle = math_random_float_range(-3.1415927410125732f, 3.1415927410125732f);
        position.f[0] = radius * math_fast_sin_or_cos_a(angle);
        position.f[1] = radius * math_fast_sin_or_cos_b(angle);
        position.f[2] = math_random_float_range(0.0f, 1.0f);
        vec_scale_to_length(&velocity, &position, math_random_float_range(speed * 0.75f, speed * 1.25f));
        position.f[2] = math_random_float_range(low, high);
        FastVecAdd(&position, object + 0x10, &position);
        SpawnTintedEffects(object, &position, 0.0f, 1, 1, &velocity, 0.0f, 1.0f,
                          0x50808040, 0, 5.5f);
    }
}


extern void *part_find_owned_effect_slot(char *, int, int);

extern void moby_set_byte_on_group(int, int);

/* revives the round a moby belongs to and drops what it was carrying */
void moby_release_and_reset_impact_slot(char *moby)
{
    char *owner = (char *)part_find_owned_effect_slot(moby, 0x10000, 0);

    if (owner != 0) {
        char *owner_target = *(char **)(owner + 0x20);

        if (owner_target != 0) {
            if (*(short *)(owner_target + 0xAA) == MOBY_CLASS_DYNAMO) {
                if (*(unsigned char *)(moby + 0x21) != 0xFF)
                    moby_set_byte_on_group(*(unsigned char *)(moby + 0x21), 2);
            }
        }
    }

    *(unsigned char *)(moby + 0xA8) = 0xFF;
}

extern void STUB_printf(void *, int);
extern void moby_mark_spawned(void *);
extern int coll_point_inside_region(void *, int);
extern void FadeToBlack(int);
extern void hero_reset_position_and_direction(void *, void *, int, int);
extern void load_scene_chunk(int, int);
extern int req_push_queue(void *, int);
extern s32 req_launch_queued(void *);
extern void game_set_slowdown_factor(void);
extern int game_is_either_mode_two(void);
extern void moby_mark_flag_and_append_to_list(int);
extern void snd_play_indexed(int);
extern void moby_mark_table_entry_flagged(int);
extern void level_capture_checkpoint_state(void *, void *);
extern void hero_start_move_state_walk_or_run(int);
extern s32 SetHeroMoveState(int, int);
extern void script_queue_keyed_request(int, int);
extern int MemcardSave(int, int);
extern unsigned char D_0019B2E8[];
extern char g_hero_position[];

/* Level data, at another address in each level that has this function. The trigger flag is
   read at an offset from its owner: retail never moves it into a delay slot. */
extern int ref_L01_003FFFE8_00[] __attribute__((sda));
extern char ref_L01_003FFFE8_01[];
extern char ref_L01_003FFFE8_02[];
extern char ref_L01_003FFFE8_03[];
extern char ref_L01_003FFFE8_04[];
extern char *ref_L01_003FFFE8_05 __attribute__((sda));
extern char ref_L01_003FFFE8_06[];
extern int ref_L01_003FFFE8_07 __attribute__((sda));

/* a trigger moby: reports bad setup, waits to be activated, plays its effects and removes itself */
void activation_trigger_update(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    int active;

    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        if (*(int *)vars == -1)
            STUB_printf(ref_L01_003FFFE8_01, *(short *)(moby + 0xB2));
        if (*(short *)(vars + 4) == -1)
            STUB_printf(ref_L01_003FFFE8_02, *(short *)(moby + 0xB2));
        if (*(int *)(vars + 8) == -1)
            STUB_printf(ref_L01_003FFFE8_03, *(short *)(moby + 0xB2));
        if (*(unsigned char *)(moby + 0xB0) != 255) {
            if (D_0019B2E8[*(unsigned char *)(moby + 0xB0) + (g_current_map_index << 4)] & 128) {
                moby_mark_spawned(moby);
                break;
            }
        } else
            STUB_printf(ref_L01_003FFFE8_04, *(short *)(moby + 0xB2));
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        active = 0;
        if (*(unsigned char *)(moby + 0xBC) ||
            (*(int *)vars != -1 && coll_point_inside_region(g_hero_position, *(int *)vars) &&
             (*(int *)(vars + 0x18) || *(int *)(g_hero_position + 0x2C0))))
            active = 1;
        if (active) {
            int ready;

            *(unsigned char *)(moby + 0x30) = 255;
            FadeToBlack(20);
            if (*(int *)(vars + 0xC) != -1) {
                char *entry = ref_L01_003FFFE8_05 + (*(int *)(vars + 0xC) << 7);

                hero_reset_position_and_direction(entry + 0x30, entry + 0x70, 0x6F, 1);
            }
            if (*(int *)(vars + 8) != -1)
                load_scene_chunk(*(int *)(vars + 8), 0);
            ready = 1;
            if (g_current_map_index == 8 && *(short *)(vars + 4) == 0) {
                if (req_push_queue(ref_L01_003FFFE8_06, 0x57)) {
                    req_push_queue(ref_L01_003FFFE8_06, 9);
                    req_push_queue(ref_L01_003FFFE8_06, 0x58);
                    req_launch_queued(ref_L01_003FFFE8_06);
                    game_set_slowdown_factor();
                    ref_L01_003FFFE8_07 = 1;
                } else
                    ready = 0;
            }
            if (ready)
                moby_set_state(moby, 3, -1);
        }
        break;
    case 3:
        ref_L01_003FFFE8_00[1] = 1;
        if (!game_is_either_mode_two()) {
            ref_L01_003FFFE8_00[1] = 0;
            if (*(short *)(vars + 6) != -1) {
                moby_mark_flag_and_append_to_list(*(short *)(vars + 6));
                snd_play_indexed(*(short *)(vars + 6));
            }
            moby_set_state(moby, 4, -1);
        }
        break;
    case 4:
        if (*(unsigned char *)(moby + 0xB0) != 255) {
            int n = *(unsigned char *)(moby + 0xB0);

            if (!(D_0019B2E8[n + (g_current_map_index << 4)] & 128)) {
                moby_mark_table_entry_flagged(n);
                level_capture_checkpoint_state(moby + 0x10, moby + 0xF0);
            }
        }
        hero_start_move_state_walk_or_run(0);
        SetHeroMoveState(0, 1);
        script_queue_keyed_request(*(int *)(vars + 0x14), *(int *)(vars + 0x10));
        MemcardSave(0, -1);
        moby_mark_spawned(moby);
        break;
    }
}

extern void moby_set_state(char *, int, int);

extern void math_store_angle_update_result(char *, char *, float, int, int);

extern int D_L01_001A8F40 __attribute__((sda));

/* Updates a TV Screens moby: starts it, then keeps its screen effect running. */
void tv_l01_screens_update(char *moby)
{
    unsigned char state = *(unsigned char *)(moby + 0x20);
    char *vars = *(char **)(moby + 0x68);

    switch (state) {
    case 0:
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        if (vars == 0)
            break;
        if (D_L01_001A8F40 == 2)
            math_store_angle_update_result(moby, vars + 0xC, 0.055268768f,
                              (int)0x80AABED2u, (int)0x80466464u);
        else
            math_store_angle_update_result(moby, vars + 0xC, 0.037815473f,
                              (int)0x8096AAAAu, (int)0x80466464u);
        break;
    }
}

extern void tracked_target_offsets_update(void *);
extern void ref_L01_004132D8_00(void (*)(void *), void *);
extern void tumbling_pieces_update(void *);
extern void set_moby_color(void *, int, int, int);
extern int FastTweenColor(int, int, float);
extern float math_fast_sin_or_cos_a(float);
extern void target_apply_slot_color(void *);
extern void vec_clear_128(void *);
extern void tumbling_piece_spawn(void *, void *, void *, void *, void *, int, int, int, void *, float);
extern int math_random_int_range(int, int);
extern void vec_build_spherical_offset(void *, float, float, float);
extern float math_random_angle(void);
extern float math_random_float_range(float, float);
extern int func_001163B0(void);
extern int coll_process_hit(void *, int, void *, int, float);
extern int vec_fast_helper_b(void *);
extern int math_fast_float_d(void *);
extern float FastAddRotations(float, float);
typedef struct {
    char data[0x18];
    char *target;
    char end[0x14];
} ParticleEffectSlot;
extern char g_hero_state[];
extern ParticleEffectSlot D_L01_00257920[];
extern char *D_L01_001C3980[];

/* Updates up to 30 glow effects attached to other mobys: pulses their colour, throws sparks near them and frees them when the target is gone. */
void part_update_attached_glow_effects(char *moby) {
    float spark_a[4], spark_b[4];
    int i;

    qcopy_nc(moby + 0x10, g_hero_state);
    for (i = 0; i < 30; i++) {
        char *slot;
        char *other;
        int dead;

        if (!D_L01_00257920[i].target)
            continue;
        slot = (char *)&D_L01_00257920[i];
        *(float *)(slot + 0xC) = FastAddRotations(*(float *)(slot + 0xC), 0.20943954586982727f);
        dead = 0;
        if (*(signed char *)(*(char **)(slot + 0x18) + 0x20) < 0)
            dead = 1;
        if (!*(int *)(*(char **)(slot + 0x18) + 0x98))
            dead = 1;
        if (math_fast_float_d(slot))
            dead = 1;
        if (vec_fast_helper_b(slot + 0x1C)) {
            int count, j;
            char *target = *(char **)(slot + 0x18);

            *(float *)(slot + 0x1C) = *(float *)(slot + 0x14);
            count = coll_process_hit(target + 0x10, 0, target, 0, 8.0f);
            for (j = 0; j < count; j++) {
                other = D_L01_001C3980[j];
                if ((*(unsigned short *)(other + 0x34) & 0x1000) && other &&
                    *(unsigned char *)(other + 0x20) != 254 && *(unsigned char *)(other + 0x20) != 253 &&
                    *(short *)(*(char **)(other + 0x24) + 0x46) == 5)
                    goto collide;
            }
        }
    random_particles:
        if (func_001163B0() % 11 == 0) {
            int j, count;

            {
                float scale = math_random_float_range(0.3f, 0.65f) * 0.0009764999849721789f;
                float x = *(float *)(*(char **)(slot + 0x18) + 0xC) * scale;
                float y = math_random_angle();
                float z = math_random_angle();

                vec_build_spherical_offset(spark_a, x, y, z);
            }
            {
                float scale = math_random_float_range(0.3f, 0.65f) * 0.0009764999849721789f;
                float x = *(float *)(*(char **)(slot + 0x18) + 0xC) * scale;
                float y = math_random_angle();
                float z = math_random_angle();

                vec_build_spherical_offset(spark_b, x, y, z);
            }
            j = math_random_int_range(5, 15);
            count = math_random_int_range(15, 30);
            tumbling_piece_spawn(moby, *(char **)(slot + 0x18), *(char **)(slot + 0x18), spark_a, spark_b, 0, j, count, slot, 0.0f);
        }
        if (dead) {
            target_apply_slot_color(slot);
            *(char **)(slot + 0x18) = 0;
            continue;
        }
        goto timer;
    collide:
        vec_clear_128(spark_a);
        tumbling_piece_spawn(moby, *(char **)(slot + 0x18), other, spark_a, spark_a, 1, 10, 30, slot, *(float *)(slot + 0x10));
        tumbling_piece_spawn(moby, *(char **)(slot + 0x18), other, spark_a, spark_a, 0, 10, 30, slot, 0.0f);
        goto random_particles;
    timer:
        if (*(int *)(slot + 0x24) == 0) {
            int c = FastTweenColor(*(int *)(slot + 4), *(int *)(slot + 8),
                                  (math_fast_sin_or_cos_a(*(float *)(slot + 0xC)) + 1.0f) * 0.5f);

            set_moby_color(*(char **)(slot + 0x18), c & 255, (c >> 8) & 255, (c >> 16) & 255);
        } else
            --*(int *)(slot + 0x24);
    }
    tumbling_pieces_update(moby);
    ref_L01_004132D8_00(tracked_target_offsets_update, moby);
}


extern char *D_001B9510;

extern float func_2E3618(char *);

extern char D_001B9380[];

extern char g_hero_position[];

extern void func_2CF938(char *, char *);

typedef int TI128 __attribute__((mode(TI)));


extern void func_2E34A0(void *, char *, char *);

extern void func_2E3918(void *, void *, char *);

extern float func_2E33E0(float);

extern void func_323310(int, int);



extern void func_002A6CF0(void *, void *);

extern int ref_L01_004480C8_00;

/* Passes the object to the shared resident handler. */
void load_run_resident_handler(void *object)
{
    func_002A6CF0(&ref_L01_004480C8_00, object);
}

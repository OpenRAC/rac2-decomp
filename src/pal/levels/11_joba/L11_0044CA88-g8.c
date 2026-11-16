#include "include_asm.h"

#include "common.h"
typedef float V4_L11_447018[4] __attribute__((aligned(16)));
typedef struct {
    float head[2];
    s32 flag;
    s32 pad;
    V4_L11_447018 pos;
} L11_447018_Spark;
extern char *arena_get_center_point(char *);
extern void vec_add_random_offset(void *, float);
extern void vec_clear_128(void *);
extern float math_random_float_range(float, float);
extern s32 math_random_int_below(s32);
extern s32 math_random_int_range(s32, s32);
extern void *enemy_spawn_record(void *, void *, void *, s32, s32);
extern s32 g_object_spark_chance __attribute__((sda));
extern s32 g_object_spark_type_min __attribute__((sda));
extern s32 g_object_spark_type_max __attribute__((sda));
extern float g_object_spark_speed_min __attribute__((sda));
extern float g_object_spark_speed_max __attribute__((sda));
extern float g_object_spark_pos_jitter __attribute__((sda));
extern float g_object_spark_height_offset __attribute__((sda));
extern char g_object_spark_record_name[8] __attribute__((sda));

/* Emits count sparks at the object, then one more unless the chance roll says no. */
void part_emit_object_sparks_pal(char *obj, s32 count)
{
    L11_447018_Spark spark;
    s32 i;

    for (i = 0; i < count; i++) {
        qcopy(spark.pos, arena_get_center_point(obj));
        vec_add_random_offset(spark.pos, g_object_spark_pos_jitter);
        spark.pos[2] += g_object_spark_height_offset;
        vec_clear_128(&spark);
        vec_add_random_offset(&spark, math_random_float_range(g_object_spark_speed_min, g_object_spark_speed_max) * 0.020000001f);
        spark.flag = 0;
        enemy_spawn_record(spark.pos, &spark, g_object_spark_record_name, math_random_int_below(2), math_random_int_range(g_object_spark_type_min, g_object_spark_type_max));
    }
    if (math_random_int_below(g_object_spark_chance) == 0) {
        qcopy(spark.pos, arena_get_center_point(obj));
        vec_add_random_offset(spark.pos, g_object_spark_pos_jitter);
        spark.pos[2] += g_object_spark_height_offset;
        vec_clear_128(&spark);
        vec_add_random_offset(&spark, math_random_float_range(g_object_spark_speed_min, g_object_spark_speed_max) * 0.020000001f);
        spark.flag = 0;
        enemy_spawn_record(spark.pos, &spark, g_object_spark_record_name, math_random_int_below(2), math_random_int_range(g_object_spark_type_min, g_object_spark_type_max));
    }
}

extern s32 FastDecTimer(void *);
extern u16 g_timed_effect_duration __attribute__((sda));
extern s32 g_timed_effect_chance __attribute__((sda));
extern s32 g_level_global_word __attribute__((sda));
extern s32 func_32CAB0(s32 a0);
extern s32 func_301700(float f12);
extern s32 func_3006B8(char *a0, s32 a1);
extern s32 func_338F10(char *a0, char *a1, s32 a2);
extern s32 func_4461C0(s32 a0, char *a1);
extern s32 func_448CE0(char *a0);
extern u8 *g_group_id_lists[];
extern u8 *g_moby_l11_table __attribute__((sda));
extern s32 g_scene_effect_param_a __attribute__((sda));
extern u8 g_scene_effect_param_bytes __attribute__((sda));
extern s32 g_scene_effect_param_b;
typedef struct JobObject JobObject;
typedef struct {
    u8 pad00[0x18];
    float *params;           
    u8 pad1C[4];
    float health;            
    u8 pad24[4];
    u8 f28;
    u8 f29;
    u8 pad2A[4];
    u8 f2E;
    u8 pad2F;
    float f30;
    u8 f34;
    u8 pad35[0x48 - 0x35];
    u8 f48;
    u8 pad49;
    u8 f4A;
    u8 pad4B[5];
    u8 hit_info[0x10];        
    u8 f60;
    u8 pad61[8];
    u8 f69;
    u8 pad6A[0x80 - 0x6A];
    float f80;
    float f84;
    u8 pad88[4];
    float f8C;
    u8 pad90[8];
    s32 f98;
    u8 pad9C[0xFC - 0x9C];
    float fFC;
    float param_block[5];     
    u8 pad114[0x12C - 0x114];
    float f12C;
    float f130;
    float f134;
    u8 pad138[0x1D4 - 0x138];
    float f1D4;
    u8 pad1D8[0x1E6 - 0x1D8];
    u8 f1E6;
    u8 pad1E7;
    u8 f1E8;
    u8 f1E9;
    u8 pad1EA[0x1FC - 0x1EA];
    u16 spawn_timer;          
    u8 pad1FE[0x2F0 - 0x1FE];
    float basis[12];         
    float anchor[4];         
    u8 pad330[0x354 - 0x330];
    JobObject *turret;       
    float turn_rate;          
    u8 pad35C[0x364 - 0x35C];
    s16 fire_timer;           
    u8 pad366[0x36E - 0x366];
    s16 f36E;
} JobState;
struct JobObject {
    u8 pad00[0x10];
    float position[4];       
    u8 stage;                
    u8 pad21[0x31 - 0x21];
    u8 f31;
    u8 pad32[2];
    u16 flags;               
    u8 pad36[0x68 - 0x36];
    JobState *state;         
    u8 pad6C[3];
    u8 f6F;
    u8 pad70[0x95 - 0x70];
    u8 f95;
    u8 pad96[0xB8 - 0x96];
    s32 fB8;
    u8 padBC[4];
    float rotation[12];      
};
extern s32 FloatToInt(float);
extern float fast_vec_dist(void *, void *);
extern void moby_update_ground_check(void *);
extern void *part_find_owned_effect_slot(void *, s32, s32);
extern s32 moby_apply_damage_to_object_pal(void *, void *, s32);
extern void matrix_from_basis_rows(void *, void *);
extern void cam_compute_view_direction(void *, void *, s32);
extern s32 arena_is_point_in_inner_zone(s32, void *);
extern void moby_set_state(void *, s32, s32);
extern char g_hero_l11_position[];
extern s32 g_enemy_ai_frozen;
extern void security_robot_deactivate(void *);
extern void security_robot_update_pairing(void *);
extern s32 security_robot_is_holding_item_attacking(void *, void *);
extern void part_spawn_dust_pairs_pal(void *, s32);
extern void security_robot_kill_pal(void *, s32, s32);

/* Per-frame update of a turret-like enemy: on its first frame it seeds its parameter block
   (including a random-sign turn rate of 10 to 30 degrees), then handles hits, firing, damage
   and the death sequence. The turn rate's sign is chosen in the store's own expression so the
   stored value does not cross the coin-flip call. */
void turret_enemy_update_pal(JobObject *object)
{
    JobState *state = object->state;
    void *hit;
    float speed;

    if (object->stage == 0) {
        state->params = state->param_block;
        state->f48 = FloatToInt(15.0f);
        state->f4A = FloatToInt(16.0f);
        speed = math_random_float_range(10.0f, 30.0f) * 0.01745329424738884f;
        state->turn_rate = math_random_int_below(2) ? -speed : speed;
        state->f80 = 1.3f;
        state->f84 = 1.3f;
        state->f69 = 2;
        state->f1E9 = 3;
        state->f1D4 = 0.5f;
        state->param_block[1] = 0.5f;
        state->param_block[2] = 0.5f;
        state->f60 = 16;
        state->f98 = 7;
        state->f8C = 0.4f;
        state->f1E6 = 5;
        state->f1E8 = 2;
        state->param_block[0] = 1.3f;
        state->param_block[3] = 0.5f;
        state->param_block[4] = 1.5707964897155762f;
        state->f130 = 0.523598849773407f;
        state->f134 = 0.01f;
        state->f12C = 0.008f;
        state->f28 = 3;
        state->f29 = 1;
        state->f30 = 0.75f;
        state->fire_timer = 0;
        if (!math_random_int_below(2))
            object->flags |= 0x8000;
        state->turret = 0;
        security_robot_deactivate(object);
    }
    if (state->f36E == 0 && object->stage != 18 && !g_enemy_ai_frozen) {
        object->flags |= 0x400;
        if (object->f31 && fast_vec_dist(object->position, g_hero_l11_position) < 24.0f) {
            moby_update_ground_check(object);
            object->f6F = 22;
        }
    } else {
        object->flags &= 0xFBFF;
    }
    if (object->stage >= 3) {
        state->fFC = 1.0f;
        hit = part_find_owned_effect_slot(object, 0x10000, 1);
        if (hit) {
            state->fFC = 1.0f;
            if (security_robot_is_holding_item_attacking(object, hit)) {
                state->f60 = 15;
                moby_apply_damage_to_object_pal(object, state->hit_info, 1);
                state->f60 = 16;
                if (state->turret && state->fire_timer == 0 && object->f31) {
                    part_spawn_dust_pairs_pal(state->turret->position, 2);
                    state->fire_timer = 50;
                }
            } else {
                moby_apply_damage_to_object_pal(object, state->hit_info, 0);
            }
        } else {
            moby_apply_damage_to_object_pal(object, state->hit_info, 0);
        }
        if (state->health <= 0.0f && object->f95 != 7 && object->f95 != 8)
            security_robot_kill_pal(object, 1, 0);
        if (state->f36E) {
            matrix_from_basis_rows(state->basis, object->rotation);
            cam_compute_view_direction(object->position, state->anchor, 0);
            if (!arena_is_point_in_inner_zone(object->fB8, object->position) && object->f95 != 8) {
                state->health = 0;
                moby_set_state(object, 18, 8);
            }
        }
        if (object->stage >= 2 && state->f2E == 2)
            security_robot_kill_pal(object, 1, 1);
        security_robot_update_pairing(object);
    }
}

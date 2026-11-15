#include "common.h"

typedef int Vec128 __attribute__((mode(TI)));

typedef struct {
    char pad0[0x46];
    short kind;
} Type2318;
typedef struct {
    char pad0[0x10];
    float pos[4];
    unsigned char state;
    char pad1[3];
    Type2318 *type;
    char pad2[0x34 - 0x28];
    unsigned short flags;
    char pad3[0x78 - 0x36];
    int colour;
    char pad4[0xc0 - 0x7c];
    float mat[16];
} Obj2318;

extern unsigned char D_001A7B00[] __attribute__((sda));
extern int math_fast_float_d(void *);
extern Obj2318 *D_L00_001FACE0[];
extern int moby_get_private_value_0(void *);
extern float vec_length_xy(void *);
typedef struct {
    char pad[9];
    unsigned char index;
} ItemSelector2318;
extern ItemSelector2318 g_item_slot_to_record;
extern unsigned char D_00139571;
typedef struct {
    char pad0[4];
    unsigned char flag;
    char pad1[0x58 - 5];
    int count;
    char pad2[224 - 0x5c];
} Record2318;
extern Record2318 g_weapon_l00_table[];
extern void clank_zapper_spawn(void *, int, void *, int);
extern float mat_fast_helper_a(float, float);
extern float FastDiffRots(float, float);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern float math_random_signed_float_range(float, float);
extern int FloatToInt(float);
typedef struct {
    char pad[0x64];
    unsigned char *owner;
} Owner2318;
extern Owner2318 D_L00_001FE940;
extern char D_L00_001A8F20[] MACRO_ADDR;
extern char *part_spawn_burst(void *, void *, int, int, int, int, float, float, float, float, float);

extern int hero_slot_item_id(int);
extern void FastVecSub(void *, void *, void *);
extern int CollLine(void *, void *, int, int, int);
typedef struct {
    char pad0[0x80]; float position[4];
    char pad1[0x98-0x90]; float heading;
    char pad2[0x1314-0x9c]; Obj2318 *weapon;
    char pad3[0x18d0-0x1318]; Obj2318 *target; int active, timer;
    char pad4[0x2010-0x18dc]; float point[4] __attribute__((aligned(16)));
    char pad5[0x2290-0x2020]; int owner;
    char pad6[0x22b4-0x2294]; unsigned char mode;
    char pad7[0x24fc-0x22b5]; short blocked;
} Hero2318;
extern Hero2318 g_hero_state;

/* Lets the hero lock onto a close enemy and fire the current weapon at it, with a burst of sparks. Counts down the weapon ammo and reloads when empty. */
void hero_update_lock_on_weapon_fire(void) {
    float scratch_vec[4] __attribute__((aligned(16)));
    float spark_a[4] __attribute__((aligned(16)));
    float spark_b[4] __attribute__((aligned(16)));
    float offset_a[4] __attribute__((aligned(16)));
    float offset_b[4] __attribute__((aligned(16)));
    float angle;
    int i;
    int j;
    int object_index;
    char *effect;
    Record2318 *record;

    if (g_hero_state.active && !g_hero_state.mode && (D_001A7B00[1] || D_001A7B00[0x41])) {
        if ((hero_slot_item_id(3) == 3 || hero_slot_item_id(3) == 2) && !g_hero_state.blocked) {
            if (math_fast_float_d(&g_hero_state.timer)) {
                Obj2318 *object;
                for (object_index = 0; (object = D_L00_001FACE0[object_index]) != 0; object_index++) {
                    if (object->type && object->type->kind == 5 && object && object->state != 254 && object->state != 253 && moby_get_private_value_0(object)) {
                        FastVecSub(scratch_vec, object->pos, g_hero_state.position);
                        if (!(16.0f < vec_length_xy(scratch_vec))) g_hero_state.target = object;
                    }
                }
                if (g_hero_state.target && g_hero_state.target->type->kind == 5 && g_hero_state.target->state != 254 && g_hero_state.target->state != 253
                    && CollLine(g_hero_state.point, g_hero_state.target->pos, 0, g_hero_state.owner, 0)) {
                    FastVecSub(scratch_vec, g_hero_state.target->pos, g_hero_state.position);
                    if (vec_length_xy(scratch_vec) < 16.0f) {
                        record = &g_weapon_l00_table[g_item_slot_to_record.index];
                        if (record->count > 0) {
                            if (record->flag) clank_zapper_spawn(g_hero_state.point, g_hero_state.owner, g_hero_state.target, 1);
                            else clank_zapper_spawn(g_hero_state.point, g_hero_state.owner, g_hero_state.target, 0);
                            { Record2318 *slot_record = &g_weapon_l00_table[g_item_slot_to_record.index];
                            g_hero_state.timer = 120;
                            slot_record->count--; }
                        } else {
                            g_hero_state.active = 0;
                            g_weapon_l00_table[g_item_slot_to_record.index].count = 30;
                        }
                    }
                }
            } else {
                angle = FastDiffRots(mat_fast_helper_a(g_hero_state.target->pos[0] - g_hero_state.position[0], g_hero_state.target->pos[1] - g_hero_state.position[1]), g_hero_state.heading);
                if (angle > 1.3962636f && g_weapon_l00_table[g_item_slot_to_record.index].flag) {
                    Obj2318 *weapon = g_hero_state.weapon;
                    weapon->colour = 0x800000ff;
                    weapon->flags |= 0x10;
                    qcopy(scratch_vec, g_hero_state.point);
                    moby_transform_joint_to_world(weapon, 6, spark_a);
                    moby_transform_joint_to_world(weapon, 7, spark_b);
                    *(Vec128 *)offset_a = 0;
                    *(Vec128 *)offset_b = 0;
                    offset_a[0] = -0.025f; offset_a[1] = 0.01f; offset_a[2] = 0.04f;
                    offset_b[0] = -0.025f; offset_b[1] = -0.01f; offset_b[2] = 0.04f;
                    matrix_mul_vec3(offset_a, offset_a, weapon->mat);
                    FastVecAdd(spark_a, spark_a, offset_a);
                    matrix_mul_vec3(offset_b, offset_b, weapon->mat);
                    FastVecAdd(spark_b, spark_b, offset_b);
                    for (i = 0; i < 30; i++) {
                        spark_a[0] += math_random_signed_float_range(0.0f, 0.004f);
                        spark_a[1] += math_random_signed_float_range(0.0f, 0.004f);
                        spark_a[2] += math_random_signed_float_range(0.0f, 0.004f);
                        spark_b[0] += math_random_signed_float_range(0.0f, 0.004f);
                        spark_b[1] += math_random_signed_float_range(0.0f, 0.004f);
                        spark_b[2] += math_random_signed_float_range(0.0f, 0.004f);
                        effect = part_spawn_burst(spark_a, D_L00_001A8F20, 2, 127, 0x2020ff, FloatToInt(math_random_signed_float_range(1.0f, -1.0f)), 25200.0f, 500.0f, 1.0f, 0.0f, 0.0f);
                        if (effect) effect[2] = *D_L00_001FE940.owner;
                        effect = part_spawn_burst(spark_b, D_L00_001A8F20, 2, 127, 0x2020ff, FloatToInt(math_random_signed_float_range(1.0f, -1.0f)), 25200.0f, 500.0f, 1.0f, 0.0f, 0.0f);
                        if (effect) effect[2] = *D_L00_001FE940.owner;
                    }
                }
                qcopy(scratch_vec, g_hero_state.point);
                if (angle < 1.3962636f) {
                    for (j = 0; j < 20; j++) {
                        spark_a[0] = scratch_vec[0] + math_random_signed_float_range(0.0f, 0.04f);
                        spark_a[1] = scratch_vec[1] + math_random_signed_float_range(0.0f, 0.04f);
                        spark_a[2] = scratch_vec[2] + math_random_signed_float_range(0.0f, 0.04f);
                        record = &g_weapon_l00_table[g_item_slot_to_record.index];
                        /* Identical arms: retail still reads this flag into $v0 and the next call clobbers it, the
                           dead load jump2's cross-jump leaves. One arm is 36 bytes short of retail. */
                        if (record->flag) {
                            effect = part_spawn_burst(spark_a, D_L00_001A8F20, 2, 127, 0x20ff20, FloatToInt(math_random_signed_float_range(1.0f, -1.0f)), 31500.002f, 500.0f, 1.0f, 0.0f, 0.0f);
                            if (effect) effect[2] = *D_L00_001FE940.owner;
                        } else {
                            effect = part_spawn_burst(spark_a, D_L00_001A8F20, 2, 127, 0x20ff20, FloatToInt(math_random_signed_float_range(1.0f, -1.0f)), 31500.002f, 500.0f, 1.0f, 0.0f, 0.0f);
                            if (effect) effect[2] = *D_L00_001FE940.owner;
                        }
                    }
                }
            }
        }
    }
}

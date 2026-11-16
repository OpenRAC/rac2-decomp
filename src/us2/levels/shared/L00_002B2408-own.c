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

extern unsigned char g_inventory_have_flags[] __attribute__((sda));
extern int math_fast_float_d(void *);
extern Obj2318 *g_target_l00_list[];
extern char *moby_get_private_value_0(void *);
extern float vec_length_xy(void *);
typedef struct {
    char pad[9];
    unsigned char index;
} ItemSelector2318;
extern ItemSelector2318 g_item_slot_to_record;
extern unsigned char g_weapon_misc_byte;
typedef struct {
    char pad0[4];
    unsigned char flag;
    char pad1[0x58 - 5];
    int count;
    char pad2[224 - 0x5c];
} Record2318;
extern Record2318 g_weapon_l00_table[];
extern void *clank_zapper_spawn(void *, int, void *, int);
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
extern Owner2318 g_effect_definitions;
extern char g_default_vector[] MACRO_ADDR;
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
    char pad5[0x2290-0x2020]; int owner; int weapon_id;
    char pad6[0x22b4-0x2298]; unsigned char mode;
    char pad7[0x24fc-0x22b5]; short blocked;
} Hero2318;
extern Hero2318 g_hero_state;

/* Clank zapper: picks a nearby target, fires the zapper at it on a timer, and spawns charging sparks around the weapon. */
void hero_update_zapper_us2(void) {
    float v[4] __attribute__((aligned(16)));
    float a[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    float c[4] __attribute__((aligned(16)));
    float d[4] __attribute__((aligned(16)));
    float angle;
    int i;
    int j;
    int k;
    char *effect;
    Record2318 *record;

    if (g_hero_state.weapon_id == 0x31) {
        g_hero_state.active = 0;
        g_hero_state.target = 0;
    }
    if (g_hero_state.active && !g_hero_state.mode && (g_inventory_have_flags[1] || g_inventory_have_flags[0x41])) {
        if ((hero_slot_item_id(3) == 3 || hero_slot_item_id(3) == 2) && !g_hero_state.blocked) {
            if (math_fast_float_d(&g_hero_state.timer)) {
                Obj2318 *object;
                for (k = 0; (object = g_target_l00_list[k]) != 0; k++) {
                    if (object->type && object->type->kind == 5 && object && object->state != 254 && object->state != 253 && moby_get_private_value_0(object)) {
                        FastVecSub(v, object->pos, g_hero_state.position);
                        if (!(16.0f < vec_length_xy(v))) g_hero_state.target = object;
                    }
                }
                if (g_hero_state.target && g_hero_state.target->type->kind == 5 && g_hero_state.target->state != 254 && g_hero_state.target->state != 253
                    && CollLine(g_hero_state.point, g_hero_state.target->pos, 0, g_hero_state.owner, 0)) {
                    FastVecSub(v, g_hero_state.target->pos, g_hero_state.position);
                    if (vec_length_xy(v) < 16.0f) {
                        record = &g_weapon_l00_table[g_item_slot_to_record.index];
                        if (record->count > 0) {
                            if (record->flag) clank_zapper_spawn(g_hero_state.point, g_hero_state.owner, g_hero_state.target, 1);
                            else clank_zapper_spawn(g_hero_state.point, g_hero_state.owner, g_hero_state.target, 0);
                            { Record2318 *r = &g_weapon_l00_table[g_item_slot_to_record.index];
                            g_hero_state.timer = 120;
                            r->count--; }
                        } else {
                            g_hero_state.active = 0;
                            g_weapon_l00_table[g_item_slot_to_record.index].count = 30;
                        }
                    }
                }
            } else if (g_hero_state.target) {
                angle = FastDiffRots(mat_fast_helper_a(g_hero_state.target->pos[0] - g_hero_state.position[0], g_hero_state.target->pos[1] - g_hero_state.position[1]), g_hero_state.heading);
                if (angle > 1.3962636f && g_weapon_l00_table[g_item_slot_to_record.index].flag) {
                    Obj2318 *weapon = g_hero_state.weapon;
                    weapon->colour = 0x800000ff;
                    weapon->flags |= 0x10;
                    qcopy(v, g_hero_state.point);
                    moby_transform_joint_to_world(weapon, 6, a);
                    moby_transform_joint_to_world(weapon, 7, b);
                    *(Vec128 *)c = 0;
                    *(Vec128 *)d = 0;
                    c[0] = -0.025f; c[1] = 0.01f; c[2] = 0.04f;
                    d[0] = -0.025f; d[1] = -0.01f; d[2] = 0.04f;
                    matrix_mul_vec3(c, c, weapon->mat);
                    FastVecAdd(a, a, c);
                    matrix_mul_vec3(d, d, weapon->mat);
                    FastVecAdd(b, b, d);
                    for (i = 0; i < 30; i++) {
                        a[0] += math_random_signed_float_range(0.0f, 0.004f);
                        a[1] += math_random_signed_float_range(0.0f, 0.004f);
                        a[2] += math_random_signed_float_range(0.0f, 0.004f);
                        b[0] += math_random_signed_float_range(0.0f, 0.004f);
                        b[1] += math_random_signed_float_range(0.0f, 0.004f);
                        b[2] += math_random_signed_float_range(0.0f, 0.004f);
                        effect = part_spawn_burst(a, g_default_vector, 2, 127, 0x2020ff, FloatToInt(math_random_signed_float_range(1.0f, -1.0f)), 25200.0f, 500.0f, 1.0f, 0.0f, 0.0f);
                        if (effect) effect[2] = *g_effect_definitions.owner;
                        effect = part_spawn_burst(b, g_default_vector, 2, 127, 0x2020ff, FloatToInt(math_random_signed_float_range(1.0f, -1.0f)), 25200.0f, 500.0f, 1.0f, 0.0f, 0.0f);
                        if (effect) effect[2] = *g_effect_definitions.owner;
                    }
                }
                qcopy(v, g_hero_state.point);
                if (angle < 1.3962636f) {
                    for (j = 0; j < 20; j++) {
                        a[0] = v[0] + math_random_signed_float_range(0.0f, 0.04f);
                        a[1] = v[1] + math_random_signed_float_range(0.0f, 0.04f);
                        a[2] = v[2] + math_random_signed_float_range(0.0f, 0.04f);
                        record = &g_weapon_l00_table[g_item_slot_to_record.index];
                        /* Identical arms: retail still reads this flag into $v0 and the next call clobbers it, the
                           dead load jump2's cross-jump leaves. One arm is 36 bytes short of retail. */
                        if (record->flag) {
                            effect = part_spawn_burst(a, g_default_vector, 2, 127, 0x20ff20, FloatToInt(math_random_signed_float_range(1.0f, -1.0f)), 31500.002f, 500.0f, 1.0f, 0.0f, 0.0f);
                            if (effect) effect[2] = *g_effect_definitions.owner;
                        } else {
                            effect = part_spawn_burst(a, g_default_vector, 2, 127, 0x20ff20, FloatToInt(math_random_signed_float_range(1.0f, -1.0f)), 31500.002f, 500.0f, 1.0f, 0.0f, 0.0f);
                            if (effect) effect[2] = *g_effect_definitions.owner;
                        }
                    }
                }
            }
        }
    }
}

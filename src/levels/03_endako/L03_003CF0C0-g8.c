#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef struct {
    char position[16];
    char pad10[0x25C];
    char *attached;
    char pad270[0x2024];
    int state;
} PlayerState;
extern PlayerState g_hero_state;
typedef struct {
    u8 header[0x464];
    u8 entries[0];
} TriggerTable;
extern TriggerTable g_trigger_l03_flags;
extern u8 g_moby_nibble_table[];
extern char g_effect_descriptor_default[] __attribute__((sda));
extern float g_target_approach_speed __attribute__((sda));
extern float g_target_height_speed __attribute__((sda));
extern float g_target_l03_angle_degrees __attribute__((sda));
extern char g_vec4_offset_table[] SDATA(D_L03_001B0470);
extern int g_current_map_index MACRO_ADDR;
extern int g_frame_l03_counter;
extern char *part_find_owned_effect_slot(char *, int, int);
extern void moby_set_state(char *, int, int);
extern void value_set_entry_by_index(int, int);
extern int PlayMobySound(int, int, char *);
extern void vec_copy_helper_a(void *);
extern void vec_fast_normalize_helper(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern void vec_set_direction_with_complement(void *, void *, float);
extern void cam_moby_init_tracking(char *, int, int, void *, void *, u8, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void mat_get_euler_angles(void *, void *);
extern void part_spawn_masked_debris(char *, int, void *, u8, float, float, float, float);
extern void vec_random_direction(void *, float, float);
extern void trash_can_debris_update(char *);
extern int math_random_int_below(int), cam_moby_update(char *);
extern char *cam_moby_create(char *, int, int, int, void *, void *, void *, u8, float, float);
extern float math_fast_sin_or_cos_b(float), FastVecDot(void *, void *), FastVecLength(void *);
extern float math_random_signed_float_range(float, float), math_random_float_range(float, float), math_random_angle(void);
/* Initializes the triggered motion, sheds debris while moving, and emits the
 * final twenty-object burst when the collision magnitude reaches its threshold. */
/* Per-frame update of moby class 2481 (Trash Can). */
void UpdateCollisionTriggeredSpawner(char *obj)
{
    float target[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    float velocity[4] __attribute__((aligned(16)));
    float temporary[4] __attribute__((aligned(16)));
    float angles[4] __attribute__((aligned(16)));
    char *vars = *(char **)(obj + 0x68);
    char *collision = part_find_owned_effect_slot(obj, 0x10000, 0);
    int i, dialogue;
    float value;

    switch (*(u8 *)(obj + 0x20)) {
    case 0:
        moby_set_state(obj, 1, -1);
        break;
    case 1:
        if (!collision && !(g_hero_state.state == 0x10 && g_hero_state.attached == obj))
            break;
        dialogue = *(int *)(vars + 0x84);
        if (dialogue >= 0) {
            u16 id = *(u16 *)(obj + 0xB2);
            if (!g_trigger_l03_flags.entries[(s16)id]) {
                int count = g_moby_nibble_table[((s16)id >> 1) + (g_current_map_index << 10)];
                if (!((id & 1) ? ((count >> 4) & 7) : (count & 7)))
                    value_set_entry_by_index(dialogue + 0x2F52, 0xB4);
            }
        }
        if (*(u16 *)(obj + 0xB2) & 1) {
            u8 *cell = g_moby_nibble_table +
                (((short)*(u16 *)(obj + 0xB2) >> 1) + (g_current_map_index << 10));
            if (((*cell >> 4) & 7) != 7)
                *cell += 16;
        } else {
            u8 *cell = g_moby_nibble_table +
                (((short)*(u16 *)(obj + 0xB2) >> 1) + (g_current_map_index << 10));
            if ((*cell & 7) != 7)
                ++*cell;
        }
        PlayMobySound(0, 0, obj);
        vec_copy_helper_a(velocity);
        if (collision)
            vec_fast_normalize_helper(target, collision + 0x10, g_target_approach_speed * 0.0166666675f);
        else
            vec_fast_normalize_helper(target, g_hero_state.position, g_target_approach_speed * 0.0166666675f);
        target[2] = g_target_height_speed * 0.0166666675f;
        FastVecCross(position, velocity, target);
        value = math_fast_sin_or_cos_b(g_target_l03_angle_degrees * 0.000290888245f);
        vec_set_direction_with_complement(position, position, value * 0.5f);
        cam_moby_init_tracking(obj, 0, -1, target, position, 255, 15.0f);
        *(int *)(obj + 0x98) = *(int *)(*(char **)(obj + 0x24) + 0x10);
        moby_set_state(obj, 2, -1);
        break;
    case 2:
        vec_copy_helper_a(target);
        value = FastVecDot(obj + 0xE0, target);
        if ((g_frame_l03_counter & 3) == (((int)obj >> 8) & 3) && value < 0.9f && value > 0.1f) {
            int kind;
            char *child;

            i = math_random_int_below(4);
            matrix_mul_vec3(position, g_vec4_offset_table + (i << 4), obj + 0xC0);
            FastVecAdd(position, position, obj + 0x10);
            kind = 0x9D7;
            if (math_random_int_below(2))
                kind = 0x9D4;
            *(Quad *)temporary = 0;
            temporary[0] = math_random_signed_float_range(0, 2);
            temporary[1] = math_random_signed_float_range(0, 2);
            temporary[2] = math_random_float_range(4, 8);
            *(Quad *)velocity = *(Quad *)temporary;
            value = FastVecLength(velocity);
            vec_scale_to_length(velocity, velocity, value * 0.0166666675f);
            matrix_mul_vec3(velocity, velocity, obj + 0xC0);
            *(Quad *)angles = 0;
            angles[0] = math_random_angle();
            angles[1] = math_random_angle();
            angles[2] = math_random_angle();
            *(Quad *)temporary = *(Quad *)angles;
            child = cam_moby_create(obj, 0, kind, -1, position, temporary, velocity, 255,
                math_random_signed_float_range(45, 180) * 0.000290888245f, 20.0f);
            if (child) {
                *(void (**)(char *))(child + 0x64) = trash_can_debris_update;
                PlayMobySound(1, 0, obj);
            }
        }
        if (cam_moby_update(obj))
            moby_set_state(obj, 3, -1);
        break;
    case 3:
        break;
    case 4:
        return;
    }
    if (collision && *(float *)(collision + 0x2C) >= 3.0f) {
        moby_set_state(obj, 4, -1);
        *(int *)(obj + 0x98) = 0;
        *(u16 *)(obj + 0x34) = (*(u16 *)(obj + 0x34) | 0x41) & ~0x1000;
        mat_get_euler_angles(obj + 0xC0, obj + 0xF0);
        part_spawn_masked_debris(obj, 0x1FF, g_effect_descriptor_default, 255, 3.0f, 5.0f, 5.0f, 10.0f);
        *(Quad *)target = 0;
        target[2] = 0.5f;
        matrix_mul_vec3(target, target, obj + 0xC0);
        FastVecAdd(target, target, obj + 0x10);
        for (i = 0x13; i >= 0; --i) {
            int kind;
            char *child;

            vec_random_direction(position, 0, 0.5f);
            FastVecAdd(position, position, target);
            *(Quad *)temporary = 0;
            temporary[0] = math_random_signed_float_range(0, 2);
            temporary[1] = math_random_signed_float_range(0, 2);
            temporary[2] = math_random_float_range(5, 12);
            *(Quad *)velocity = *(Quad *)temporary;
            value = FastVecLength(velocity);
            vec_scale_to_length(velocity, velocity, value * 0.0166666675f);
            kind = 0x9D7;
            if (math_random_int_below(2))
                kind = 0x9D4;
            *(Quad *)angles = 0;
            angles[0] = math_random_angle();
            angles[1] = math_random_angle();
            angles[2] = math_random_angle();
            *(Quad *)temporary = *(Quad *)angles;
            child = cam_moby_create(obj, 0, kind, -1, position, temporary, velocity, 255,
                math_random_signed_float_range(45, 180) * 0.000290888245f, 20.0f);
            if (child)
                *(void (**)(char *))(child + 0x64) = trash_can_debris_update;
        }
    }
}

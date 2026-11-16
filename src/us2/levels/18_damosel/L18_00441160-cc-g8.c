#include "names.h"
/* func_US2_L18_00441160, the USA v2.00 copy of func_L18_0043FC70: the same C, where rename func_002B0A18 becomes func_US2_002B1880; rename func_00288E18 becomes func_US2_00289840. */
#include "common.h"

extern u8 g_game_flag_table[], g_hero_position[];
/* Read as D_001A7AF8[0x37] (0x001A7B2F): an sda incomplete array with a nonzero
 * index gives retail's unsplit `lui; lbu` pair, kept out of the delay slot. */
extern u8 g_item_owned_flags[] __attribute__((sda));
extern u8 *g_moby_l18_table;
extern float FastAddRotations(float, float), math_random_float_range(float, float), math_random_angle(void), math_random_signed_float_range(float, float), vec_distance_xy(void *, void *);
extern int math_random_int_below(int);
extern void moby_set_state(void *, int, int);
extern void vec_build_spherical_offset(void *, float, float, float), moby_mark_spawned(void *), value_set_entry_by_index_us2(int, int);
extern int subtitle_request_voice_line_us2(int, int);
extern void *part_spawn_ground_effect(void *, int, int, int, int, void *, float, float, float, int);

/* State 0: unless already collected, spin and emit two particle pairs per frame;
 * within 1.5 units of D_00189EA0, set the collected flag and signal the linked
 * moby (or delete itself). Otherwise, once the linked moby is in state 0xFE/0xFD
 * (or there is none), wait 41 frames, make the two closing calls and delete itself. */
void ship_part_pickup_update_us2(u8 *obj) {
    float velocity[4] __attribute__((aligned(16)));
    float point[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(obj + 0x68);
    int i, sign, n;
    float size, angle, pitch;
    if (obj[0x20] == 0) {
        if (g_game_flag_table[0x86] || g_item_owned_flags[0x37]) {
            moby_mark_spawned(obj);
        } else {
            *(float *)(obj + 0xf8) = FastAddRotations(*(float *)(obj + 0xf8), 0.087266475f);
            for (i = 0; i < 2; i++) {
                size = math_random_float_range(2.0f, 5.0f);
                sign = math_random_int_below(2);
                if (!sign) sign--;
                angle = math_random_angle();
                pitch = math_random_float_range(0.3490659f, 1.5358898639678955f);
                vec_build_spherical_offset(velocity, math_random_float_range(0.05f, 0.1f), angle, pitch);
                qcopy(point, obj + 0x10);
                point[0] += math_random_signed_float_range(0.0f, 0.15f);
                point[1] += math_random_signed_float_range(0.0f, 0.15f);
                point[2] += math_random_signed_float_range(0.0f, 0.15f);
                part_spawn_ground_effect(point, 3, 0x208020ff, 0, sign, velocity, size * 0.1f, size, 0.006f, 0);
                part_spawn_ground_effect(point, 3, 0x20ffffff, 1, -sign, velocity, size * 0.03f, size * 0.3f, 0.006f, 0);
            }
            if (vec_distance_xy(obj + 0x10, g_hero_position) < 1.5f) {
                g_game_flag_table[0x86] = 1;
                if (*(int *)state != -1) {
                    g_moby_l18_table[(*(int *)state << 8) + 0xbc] = 1;
                    obj[0x31] = 0;
                    *(u16 *)(obj + 0x34) |= 1;
                    moby_set_state(obj, 1, -1);
                } else {
                    moby_mark_spawned(obj);
                }
            }
        }
    } else if (*(int *)state == -1 || g_moby_l18_table[(*(int *)state << 8) + 0x20] == 0xfe ||
               g_moby_l18_table[(*(int *)state << 8) + 0x20] == 0xfd) {
        u32 timer = *(u16 *)(obj + 0x96);
        u32 old = timer++;
        *(u16 *)(obj + 0x96) = timer;
        if (old > 40) {
            value_set_entry_by_index_us2(0x1293, 120);
            n = g_game_flag_table[0x86] ? 1 : 2;
            if (g_game_flag_table[0x89]) n--;
            if (n > 0) subtitle_request_voice_line_us2(0xa0f, 0x66);
            else subtitle_request_voice_line_us2(0xa10, 0x67);
            moby_mark_spawned(obj);
        }
    }
}

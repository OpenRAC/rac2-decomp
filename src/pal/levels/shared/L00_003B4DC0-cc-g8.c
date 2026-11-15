/* func_PAL_L00_003B4DC0, the PAL copy of func_L00_003B14D0: the same C, where expr 0.033333335f becomes 0.040000003f; expr 0.016666668f becomes 0.020000001f. */
/* func_L00_003A8E28: store a fresh trail sample in the source's slot (flags in config/cflags.txt). */
#include "common.h"
/* func_PAL_L00_003B4DC0: a burst of particles and glows where a consumed trail
 * group ends (flags in config/cflags.txt: the zeroed vectors are por/sq). */
typedef struct { float x, y, z, w; } Vec16_Fc936841d;
typedef int EffectQuad __attribute__((mode(TI)));
typedef struct { char pad[0x2290]; int owner; } EffectContext;
typedef struct { unsigned char pad[0x23]; unsigned char index; } EffectSelector;
typedef struct { unsigned int tag; unsigned char enabled; unsigned char tail[0xDB]; } EffectMaterial;
typedef struct { int v[6]; } EffectSix;

extern EffectContext g_hero_state __attribute__((nosda));
extern EffectSelector g_item_slot_to_record __attribute__((nosda));
extern EffectMaterial g_weapon_l00_table[] __attribute__((nosda));
extern char g_area_hit_targets[] __attribute__((nosda));
extern char g_camera_l00_position[] __attribute__((nosda));
extern EffectSix D_L00_001AF858 __attribute__((nosda));
extern EffectSix D_L00_001AF870 __attribute__((nosda));

extern void FastVecSub(void *, void *, void *);
extern float FastVecLength(void *);
extern int FloatToInt(float);
extern int coll_process_hit(void *, int, int, int, float);
extern void moby_queue_knockback_for_nodes(int, void *, void *, int, int, int, int, int, float, float, float);
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern int gfx_swap_packed_color_channels(unsigned int, int);
extern void swap_color_channel_words(int *, int *, int *, int);
extern char *part_spawn_firework_spark(void *, void *, int, int, float, int, int, float, int, int);
extern char *part_create_explosion(int, void *, void *, int, unsigned char, unsigned char,
                               unsigned char, unsigned char, float);

void func_PAL_L00_003B4DC0(float x, float y, float z)
{
    Vec16_Fc936841d p, v;
    Vec16_Fc936841d delta;
    EffectSix a, b;
    int c0, c1, c2, r, g, blue;
    /* The initial value only changes gcse's table size, which orders the three
       RGB pointer spills as retail has them; flow deletes the store. */
    int n = 0, ca, cb, t0, t1;
    float distance, fade, speed, one;

    *(EffectQuad *)&p = 0;
    p.x = x;
    p.y = y;
    p.z = z;
    n = coll_process_hit(&p, 16, g_hero_state.owner, 0, 3.0f);
    one = 1.0f;
    moby_queue_knockback_for_nodes(g_hero_state.owner, &p, g_area_hit_targets, n, 0, 0x830000, 2, 1, 8.0f, one, one);
    *(EffectQuad *)&v = 0;
    v.z = 0.040000003f;
    FastVecSub(&delta, g_camera_l00_position, &p);
    distance = FastVecLength(&delta);
    n = distance < 6.0f ? FloatToInt(distance) + 1 : 4;
    fade = 0.0f;
    if (distance < 7.0f)
        fade = 7.0f - distance;
    {
        int count;
        for (count = 0; count < n; count++) {
            speed = math_random_float_range(8.0f, 10.0f) * (0.020000001f);
            speed -= fade * (0.020000001f);
            a = D_L00_001AF858;
            b = D_L00_001AF870;
            {
                int choice = math_random_int_below(6);
                EffectMaterial *entry = g_weapon_l00_table + g_item_slot_to_record.index;
                ca = gfx_swap_packed_color_channels(a.v[choice], entry->enabled != 0);
                choice = math_random_int_below(6);
                entry = g_weapon_l00_table + g_item_slot_to_record.index;
                cb = gfx_swap_packed_color_channels(b.v[choice], entry->enabled != 0);
            }
            t0 = math_random_int_range(12, 17);
            t1 = math_random_int_range(21, 25);
            part_spawn_firework_spark(&p, &v, ca, cb, 400000.0f, t0, t1, speed, 0, 0);
        }
    }
    if (distance > 9.0f) {
        part_create_explosion(g_hero_state.owner, &p, &v, 12, 127, 127, 127, 32, one * 4.0f);
        r = 127;
        g = 32;
        blue = 0;
        swap_color_channel_words(&r, &g, &blue, g_weapon_l00_table[g_item_slot_to_record.index].enabled != 0);
        part_create_explosion(g_hero_state.owner, &p, &v, 20, r, g, blue, 32, one * 4.0f);
    }
    c0 = 127;
    c1 = 63;
    c2 = 0;
    swap_color_channel_words(&c0, &c1, &c2, g_weapon_l00_table[g_item_slot_to_record.index].enabled != 0);
    part_create_explosion(g_hero_state.owner, &p, &v, 17, c0, c1, c2, 48, one * 4.0f);
    c0 = 96;
    c1 = 16;
    c2 = 0;
    swap_color_channel_words(&c0, &c1, &c2, g_weapon_l00_table[g_item_slot_to_record.index].enabled != 0);
    part_create_explosion(g_hero_state.owner, &p, &v, 22, c0, c1, c2, 64, one * 3.5f);
    c0 = 32;
    c1 = 0;
    c2 = 0;
    swap_color_channel_words(&c0, &c1, &c2, g_weapon_l00_table[g_item_slot_to_record.index].enabled != 0);
    part_create_explosion(g_hero_state.owner, &p, &v, 24, c0, c1, c2, 32, one * 3.0f);
}

/* func_L00_003A8E28: store a fresh trail sample in the source's slot (flags in config/cflags.txt). */
#include "common.h"
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } Vec;

typedef struct {
    Vec pos;            /* 0x00 */
    Vec a;              /* 0x10 */
    Vec b;              /* 0x20 */
    Vec c;              /* 0x30 */
    Vec d;              /* 0x40 */
    short flag;         /* 0x50 */
    short count;        /* 0x52 */
    float t;            /* 0x54 */
    float u;            /* 0x58 */
    float rate;         /* 0x5C */
} Slot;

typedef struct {
    char pad0[0x18];
    short index;        /* 0x18 */
    short id;           /* 0x1A */
} Source;

typedef struct {
    char pad0[0x10];
    Vec pos;            /* 0x10 */
    char pad20[0x48];
    Source *source;     /* 0x68 */
} Actor;

extern int g_game_mode __attribute__((nosda));
extern int g_hero_locked_flag MACRO_ADDR;
extern short g_trail_sample_count __attribute__((sda));
extern char *level_get_slot_body(int, int);
extern int *level_get_slot_header(int, int);
extern void vec_scale_to_length(void *, void *, float);
extern void cam_compute_view_direction(void *, void *, int);
extern void FastVecCross(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);

/* Stores a new position sample for a trail in the slot that belongs to its source. */
void trail_store_sample(Actor *self)
{
    Slot *slots;
    Source *source;
    Vec m, dir, tmp;
    char *base;

    source = self->source;
    if (g_game_mode == 0x1D) return;
    base = level_get_slot_body(0x5CB, source->id);
    slots = (Slot *)(base + *level_get_slot_header(0x5CB, source->id));
    vec_scale_to_length(&m, source, 1.0f);
    dir.q = 0;
    dir.f[2] = 1.0f;
    dir.f[3] = 1.0f;
    if (g_hero_locked_flag) cam_compute_view_direction(&self->pos, &dir, 1);
    FastVecCross(&tmp, &m, &dir);
    vec_scale_to_length(&tmp, &tmp, 1.0f);
    FastVecCross(&slots[source->index].d, &tmp, &m);
    qcopy_nc(&slots[source->index].c, &m);
    qcopy_nc(&slots[source->index].pos, &self->pos);
    FastVecAdd(&slots[source->index].a, &self->pos, source);
    qcopy_nc(&slots[source->index].b, &slots[source->index].a);
    slots[source->index].count = g_trail_sample_count;
    slots[source->index].rate = 1.0f / slots[source->index].count;
    slots[source->index].t = 0;
    slots[source->index].u = 0;
    slots[source->index].flag = 1;
}

/* func_L00_003B14D0: a burst of particles and glows where a consumed trail
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
extern EffectSix g_burst_effect_a __attribute__((nosda));
extern EffectSix g_burst_effect_b __attribute__((nosda));

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

/* Makes a burst of sparks and glows where a group of trail points is used up. */
void trail_spawn_group_burst(float x, float y, float z)
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
    v.z = 1.0f / 30.0f;
    FastVecSub(&delta, g_camera_l00_position, &p);
    distance = FastVecLength(&delta);
    n = distance < 6.0f ? FloatToInt(distance) + 1 : 4;
    fade = 0.0f;
    if (distance < 7.0f)
        fade = 7.0f - distance;
    {
        int count;
        for (count = 0; count < n; count++) {
            speed = math_random_float_range(8.0f, 10.0f) * (1.0f / 60.0f);
            speed -= fade * (1.0f / 60.0f);
            a = g_burst_effect_a;
            b = g_burst_effect_b;
            {
                int choice = math_random_int_below(6);
                EffectMaterial *entry = g_weapon_l00_table + g_item_slot_to_record.index;
                ca = gfx_swap_packed_color_channels(a.v[choice], entry->enabled != 0);
                choice = math_random_int_below(6);
                entry = g_weapon_l00_table + g_item_slot_to_record.index;
                cb = gfx_swap_packed_color_channels(b.v[choice], entry->enabled != 0);
            }
            t0 = math_random_int_range(15, 20);
            t1 = math_random_int_range(25, 30);
            part_spawn_firework_spark(&p, &v, ca, cb, 400000.0f, t0, t1, speed, 0, 0);
        }
    }
    if (distance > 9.0f) {
        part_create_explosion(g_hero_state.owner, &p, &v, 15, 127, 127, 127, 32, one * 4.0f);
        r = 127;
        g = 32;
        blue = 0;
        swap_color_channel_words(&r, &g, &blue, g_weapon_l00_table[g_item_slot_to_record.index].enabled != 0);
        part_create_explosion(g_hero_state.owner, &p, &v, 24, r, g, blue, 32, one * 4.0f);
    }
    c0 = 127;
    c1 = 63;
    c2 = 0;
    swap_color_channel_words(&c0, &c1, &c2, g_weapon_l00_table[g_item_slot_to_record.index].enabled != 0);
    part_create_explosion(g_hero_state.owner, &p, &v, 20, c0, c1, c2, 48, one * 4.0f);
    c0 = 96;
    c1 = 16;
    c2 = 0;
    swap_color_channel_words(&c0, &c1, &c2, g_weapon_l00_table[g_item_slot_to_record.index].enabled != 0);
    part_create_explosion(g_hero_state.owner, &p, &v, 27, c0, c1, c2, 64, one * 3.5f);
    c0 = 32;
    c1 = 0;
    c2 = 0;
    swap_color_channel_words(&c0, &c1, &c2, g_weapon_l00_table[g_item_slot_to_record.index].enabled != 0);
    part_create_explosion(g_hero_state.owner, &p, &v, 29, c0, c1, c2, 32, one * 3.0f);
}

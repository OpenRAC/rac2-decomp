#include "include_asm.h"

#include "common.h"
typedef struct {
    unsigned char pad0[476];
    short f1dc;
    unsigned char pad1de[62];
    short f21c;
    unsigned char pad21e[1136];
    short f68e;
    unsigned char pad690[52];
    int f6c4;
    unsigned char pad6c8[3535];
    unsigned char f1497;
    unsigned char pad1498[104];
    int f1500;
    unsigned char pad1504[3468];
    char *f2290;
    int f2294;
    unsigned char pad2298[4];
    int f229c;
    unsigned char pad22a0[20];
    unsigned char f22b4;
    unsigned char pad22b5[487];
    char *f249c;
    unsigned char pad24a0[44];
    int f24cc;
} Root;
extern Root g_hero_state;
extern char g_grab_slot_table[];
extern int g_game_l00_mode __attribute__((sda));
extern unsigned char g_contact_hit_flag __attribute__((sda));
extern unsigned char g_bolt_multiplier __attribute__((sda));
extern float fade_get_value(void);
extern float fade_reduce_value_pal(float);
extern void hero_clear_tracked_slots(void);
extern void FastVecSub(void *, void *, void *);
extern void hero_build_relative_point(void *, int, float, float, float);
extern void ref_L00_002B2CC8_0(int, int);
extern void *part_find_owned_effect_slot(void *, int, int);
extern int FloatToInt(float);
extern void AdjustPlayerHealth_pal(int);
extern int hero_play_sound(int, int);
extern void hero_flatten_push_vector(void *, int, float, float);
extern void cam_scale_view_space_height(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
#define SI(o) (*(int *)(slot + (o)))
#define SF(o) (*(float *)(slot + (o)))

int hero_try_grab_object_pal(int apply)
{
    float v[4] __attribute__((aligned(16)));
    char *obj, *slot, *p;
    int special;
    float scale;

    if (g_hero_state.f229c == 20)
        return 0;
    if (g_hero_state.f229c == 7)
        return 0;
    if (g_hero_state.f2294 == 49)
        return 0;
    if (g_hero_state.f1dc)
        return 0;
    if (g_game_l00_mode)
        return 0;
    g_hero_state.f249c = 0;
    obj = g_hero_state.f2290;
    if ((unsigned char)obj[0xa8] == 255)
        return 0;
    slot = g_grab_slot_table + (unsigned char)obj[0xa8] * 64;
    if (*(char **)(slot + 0x38) != obj || !(SI(0x24) & 9))
        return 0;
    if (SF(0x2c) != 0.0f) {
        g_contact_hit_flag = 0;
        g_bolt_multiplier = 1;
    }
    if (fade_get_value() != 0.0f && !g_hero_state.f22b4) {
        SF(0x2c) = fade_reduce_value_pal(SF(0x2c));
        if (SF(0x2c) == 0.0f)
            return 0;
    }
    g_hero_state.f249c = SI(0x20);
    if (g_hero_state.f229c == 15) {
        g_hero_state.f6c4 = (int)slot;
        g_hero_state.f68e = 1;
        return 0;
    }
    if (!apply)
        return 1;
    hero_clear_tracked_slots();
    special = 0;
    if (SI(0x30) & 1) {
        qcopy(v, slot + 0x10);
        if (SF(0x1c) == 5627.925f)
            special = 1;
    } else if (SI(0x20)) {
        FastVecSub(v, (char *)&g_hero_state + 0x80,
                     *(char **)(slot + 0x20) + 0x10);
    } else {
        hero_build_relative_point(v, 0, -1.0f, 0.0f, 0.0f);
    }
    switch (g_hero_state.f22b4) {
    case 0: {
        p = g_hero_state.f249c;
        if (p && (*(short *)(p + 0xaa) == 1259 || *(short *)(p + 0xaa) == 1368)) {
            ref_L00_002B2CC8_0(125, 1);
            return 1;
        }
        if ((g_hero_state.f2294 == 1 || g_hero_state.f2294 == 29 || g_hero_state.f1500) &&
            !(SI(0x24) & 8)) {
            p = part_find_owned_effect_slot(g_hero_state.f2290, 1, 0);
            if (p)
                AdjustPlayerHealth_pal(FloatToInt(*(float *)(p + 0x2c)));
            if (!g_hero_state.f24cc)
                ref_L00_002B2CC8_0(22, 1);
            g_hero_state.f1dc = 64;
            if (!g_hero_state.f21c)
                g_hero_state.f21c = 15;
            hero_play_sound(20, 0);
            return 0;
        }
        if (g_hero_state.f229c == 18)
            ref_L00_002B2CC8_0(114, 1);
        else if (g_hero_state.f229c == 17)
            ref_L00_002B2CC8_0(115, 1);
        else if (SI(0x24) & 8)
            ref_L00_002B2CC8_0(140, 1);
        else
            ref_L00_002B2CC8_0(22, 1);
        if (g_hero_state.f2294 == 140) {
            qzero(v);
        } else {
            scale = 0.06600001f;
            if (g_hero_state.f1497)
                scale = 0.0f;
            hero_flatten_push_vector(v, special, scale, 0.034f);
            if (special && (unsigned char)slot[0x28] == 4)
                cam_scale_view_space_height(v, v, 2.0f);
        }
        break;
    }
    case 1: {
        ref_L00_002B2CC8_0(66, 1);
        hero_flatten_push_vector(v, special, 0.10000001f, 0.060000002f);
        break;
    }
    }
    FastVecAdd((char *)&g_hero_state + 0xf0, (char *)&g_hero_state + 0xf0, v);
    FastVecAdd((char *)&g_hero_state + 0x110, (char *)&g_hero_state + 0x110, v);
    return 1;
}



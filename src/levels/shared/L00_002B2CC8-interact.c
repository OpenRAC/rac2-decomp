#include "common.h"

typedef struct {
    unsigned char pad0[476];
    short timer;
    unsigned char pad1de[62];
    short sound_timer;
    unsigned char pad21e[1136];
    short f68e;
    unsigned char pad690[52];
    int f6c4;
    unsigned char pad6c8[3535];
    unsigned char f1497;
    unsigned char pad1498[104];
    int interrupted;
    unsigned char pad1504[3468];
    char *moby;
    int move_state;
    unsigned char pad2298[4];
    int control_mode;
    unsigned char pad22a0[20];
    unsigned char vehicle_mode;
    unsigned char pad22b5[487];
    char *contact;
    unsigned char pad24a0[44];
    int health;
} Root;

extern Root g_hero_state;
extern char D_L00_001C3480[];
extern int D_L00_001A8F00 __attribute__((sda));
extern unsigned char D_001A7A33 __attribute__((sda));
extern unsigned char g_bolt_multiplier __attribute__((sda));
extern float fade_get_value(void);
extern float fade_reduce_value(float);
extern void hero_clear_tracked_slots(void);
extern void FastVecSub(void *, void *, void *);
extern void hero_build_relative_point(void *, int, float, float, float);
extern void ref_L00_002B2CC8_0(int, int);
extern void *part_find_owned_effect_slot(void *, int, int);
extern int FloatToInt(float);
extern void AdjustPlayerHealth(int);
extern void hero_play_sound(int, int);
extern void hero_flatten_push_vector(void *, int, float, float);
extern void cam_scale_view_space_height(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);

#define SI(o) (*(int *)(slot + (o)))
#define SF(o) (*(float *)(slot + (o)))

/* Checks whether the hero can grab the object it is next to and, if asked, starts the grab and pushes the hero toward it. Returns 1 when a grab is possible. */
int hero_try_grab_object(int apply)
{
    float push_vec[4] __attribute__((aligned(16)));
    char *target_moby, *slot, *other;
    int special;
    float scale;

    if (g_hero_state.control_mode == 20)
        return 0;
    if (g_hero_state.control_mode == 7)
        return 0;
    if (g_hero_state.move_state == 49)
        return 0;
    if (g_hero_state.timer)
        return 0;
    if (D_L00_001A8F00)
        return 0;
    g_hero_state.contact = 0;
    target_moby = g_hero_state.moby;
    if ((unsigned char)target_moby[0xa8] == 255)
        return 0;
    slot = D_L00_001C3480 + (unsigned char)target_moby[0xa8] * 64;
    if (*(char **)(slot + 0x38) != target_moby || !(SI(0x24) & 9))
        return 0;
    if (SF(0x2c) != 0.0f) {
        D_001A7A33 = 0;
        g_bolt_multiplier = 1;
    }
    if (fade_get_value() != 0.0f && !g_hero_state.vehicle_mode) {
        SF(0x2c) = fade_reduce_value(SF(0x2c));
        if (SF(0x2c) == 0.0f)
            return 0;
    }
    g_hero_state.contact = SI(0x20);
    if (g_hero_state.control_mode == 15) {
        g_hero_state.f6c4 = (int)slot;
        g_hero_state.f68e = 1;
        return 0;
    }
    if (!apply)
        return 1;
    hero_clear_tracked_slots();
    special = 0;
    if (SI(0x30) & 1) {
        qcopy(push_vec, slot + 0x10);
        if (SF(0x1c) == 5627.925f)
            special = 1;
    } else if (SI(0x20)) {
        FastVecSub(push_vec, (char *)&g_hero_state + 0x80,
                     *(char **)(slot + 0x20) + 0x10);
    } else {
        hero_build_relative_point(push_vec, 0, -1.0f, 0.0f, 0.0f);
    }
    switch (g_hero_state.vehicle_mode) {
    case 0: {
        other = g_hero_state.contact;
        if (other && (*(short *)(other + 0xaa) == 1259 /* moby class 1259 */ || *(short *)(other + 0xaa) == 1368 /* moby class 1368 */)) {
            ref_L00_002B2CC8_0(125, 1);
            return 1;
        }
        if ((g_hero_state.move_state == 1 || g_hero_state.move_state == 29 || g_hero_state.interrupted) &&
            !(SI(0x24) & 8)) {
            other = part_find_owned_effect_slot(g_hero_state.moby, 1, 0);
            if (other)
                AdjustPlayerHealth(FloatToInt(*(float *)(other + 0x2c)));
            if (!g_hero_state.health)
                ref_L00_002B2CC8_0(22, 1);
            g_hero_state.timer = 77;
            if (!g_hero_state.sound_timer)
                g_hero_state.sound_timer = 18;
            hero_play_sound(20, 0);
            return 0;
        }
        if (g_hero_state.control_mode == 18)
            ref_L00_002B2CC8_0(114, 1);
        else if (g_hero_state.control_mode == 17)
            ref_L00_002B2CC8_0(115, 1);
        else if (SI(0x24) & 8)
            ref_L00_002B2CC8_0(140, 1);
        else
            ref_L00_002B2CC8_0(22, 1);
        if (g_hero_state.move_state == 140) {
            qzero(push_vec);
        } else {
            scale = 0.055000003f;
            if (g_hero_state.f1497)
                scale = 0.0f;
            hero_flatten_push_vector(push_vec, special, scale, 0.028333336f);
            if (special && (unsigned char)slot[0x28] == 4)
                cam_scale_view_space_height(push_vec, push_vec, 2.0f);
        }
        break;
    }
    case 1: {
        ref_L00_002B2CC8_0(66, 1);
        hero_flatten_push_vector(push_vec, special, 0.083333336f, 0.050000004f);
        break;
    }
    }
    FastVecAdd((char *)&g_hero_state + 0xf0, (char *)&g_hero_state + 0xf0, push_vec);
    FastVecAdd((char *)&g_hero_state + 0x110, (char *)&g_hero_state + 0x110, push_vec);
    return 1;
}

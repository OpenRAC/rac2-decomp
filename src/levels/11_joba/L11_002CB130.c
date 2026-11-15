/* Contact response: reads the hero's contact entry and pushes the hero along the contact direction. */
#include "common.h"

typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword word; float f[4]; } Vector;
/* Partial resident view. Field offsets and widths follow the retail accesses. */
typedef struct {
    u8 prefix[0x80];
    Vector position;
    u8 pad90[0xf0 - 0x90];
    Vector velocity, pad100, motion;
    u8 pad120[0x1dc - 0x120];
    short timer, inputLock;
    u8 pad1e0[0x21c - 0x1e0];
    short soundTimer;
    u8 pad21e[0x31c - 0x21e];
    float elapsed;
    u8 pad320[0x334 - 0x320];
    float jumpTime;
    u8 pad338[8];
    int busy;
    u8 pad344[4];
    short pendingJump;
    u8 pad34a[2];
    short jumpCount;
    u8 pad34e[0x49e - 0x34e];
    u8 animationDone;
    u8 pad49f[0x1490 - 0x49f];
    short command;
    u8 pad1492[3];
    u8 attack, jump, jumpPressed, pad1498[2], hover, cancel, pad149c, saved;
    u8 pad149e[0x1500 - 0x149e];
    int interrupted;
    u8 pad1504[0x2290 - 0x1504];
    u8 *object;
    int state, phase, movement;
    u8 pad22a0[0x22b4 - 0x22a0];
    u8 mode;
    u8 pad22b5[0x22b9 - 0x22b5];
    u8 request;
    u8 pad22ba[3];
    u8 disabled;
    u8 pad22be[0x249c - 0x22be];
    u8 *contact;
    u8 pad24a0[0x24cc - 0x24a0];
    int health;
} PlayerInputView;

typedef struct {
    u8 prefix[0x10];
    Vector direction;
    u8 *object;
    unsigned int flags;
    u8 kind, pad29[3];
    float strength;
    unsigned int directionFlags;
    u8 pad34[4];
    u8 *owner;
    u8 pad3c[4];
} ContactEntry;

extern PlayerInputView g_hero_state;
extern ContactEntry D_L11_001C4F80[];
extern int g_current_map_index __attribute__((sda));
extern int D_L11_001A9010 __attribute__((sda));
extern int D_L11_001A8F00 __attribute__((sda));
extern u8 D_001A7B0B __attribute__((sda));
extern u8 g_bolt_multiplier __attribute__((sda));
extern u8 D_001A7A33 __attribute__((sda));
extern void mem_fast_helper_b(void *, int);
extern float math_fabs(float);
extern int hero_l11_enter_state(int, int);
extern float fade_get_value(void);
extern float fade_reduce_value(float);
extern void hero_clear_tracked_slots(void);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void hero_build_relative_point(float *, int, float, float, float);
extern void *part_find_owned_effect_slot(void *, unsigned int, int);
extern int FloatToInt(float);
extern void AdjustPlayerHealth(long);
extern int hero_play_sound(int, int);
extern void hero_flatten_push_vector(int, int, float, float);
extern void cam_scale_view_space_height(char *, char *, float);

/* Checks whether the hero is being hit or pushed by something. If asked to apply it, it changes the hero state and knocks the hero away. */
int hero_handle_contact_hit(long apply)
{
    Vector direction;
    ContactEntry *entry;
    u8 *object, *contact;
    int special;
    if (g_hero_state.movement == 20 || g_hero_state.movement == 7) return 0;
    if (g_hero_state.state == 0x31) return 0;
    if (g_hero_state.timer) return 0;
    if (D_L11_001A8F00) return 0;
    g_hero_state.contact = 0;
    object = g_hero_state.object;
    if (object[0xa8] == 0xff) return 0;
    entry = &D_L11_001C4F80[object[0xa8]];
    if (entry->owner != object) return 0;
    if (!(entry->flags & 9)) return 0;
    if (entry->strength != 0.0f) {
        D_001A7A33 = 0; g_bolt_multiplier = 1;
    }
    if (fade_get_value() != 0.0f && !g_hero_state.mode) {
        entry->strength = fade_reduce_value(entry->strength);
        if (entry->strength == 0.0f) return 0;
    }
    g_hero_state.contact = entry->object;
    if (!apply) return 1;
    special = 0;
    hero_clear_tracked_slots();
    if (entry->directionFlags & 1) {
        direction.word = entry->direction.word;
        if (entry->direction.f[3] == 5627.9248046875f) special = 1;
    } else if (entry->object) {
        FastVecSub(&direction, &g_hero_state.position, entry->object+0x10);
    } else hero_build_relative_point((float *)&direction, 0, -1.0f, 0.0f, 0.0f);
    switch (g_hero_state.mode) {
    case 0:
        contact = g_hero_state.contact;
        if (contact && (*(short *)(contact+0xaa) == 0x4eb /* moby class 1259 */ || *(short *)(contact+0xaa) == 0x558 /* moby class 1368 */)) {
            hero_l11_enter_state(0x7d, 1); return 1;
        }
        if ((g_hero_state.state == 1 || g_hero_state.state == 0x1d || g_hero_state.interrupted) && !(entry->flags & 8)) {
            u8 *hit = part_find_owned_effect_slot(g_hero_state.object, 1, 0);
            if (hit) AdjustPlayerHealth(FloatToInt(*(float *)(hit+0x2c)));
            if (!g_hero_state.health) hero_l11_enter_state(0x16, 1);
            g_hero_state.timer = 0x4d;
            if (!g_hero_state.soundTimer) g_hero_state.soundTimer = 0x12;
            hero_play_sound(0x14, 0); return 0;
        }
        if (entry->flags & 8) hero_l11_enter_state(0x8c, 1);
        else hero_l11_enter_state(0x16, 1);
        if (g_hero_state.state == 0x8c) qzero(&direction);
        else {
            hero_flatten_push_vector((int)&direction, special, g_hero_state.jumpPressed ? 0.0f : 0.055000003f, 0.028333336f);
            if (special && entry->kind == 4) cam_scale_view_space_height((char *)&direction, (char *)&direction, 2.0f);
        }
        break;
    case 1:
        hero_l11_enter_state(0x42, 1);
        hero_flatten_push_vector((int)&direction, special, 0.083333336f, 0.050000004f);
        break;
    }
    FastVecAdd(&g_hero_state.velocity, &g_hero_state.velocity, &direction);
    FastVecAdd(&g_hero_state.motion, &g_hero_state.motion, &direction);
    return 1;
}

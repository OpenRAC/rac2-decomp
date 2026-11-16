#include "common.h"

#define FIELD(p, type, offset) (*(type *)((char *)(p) + (offset)))

typedef struct {
    char pad0000[0x1230];
    int input;
    char pad1234[0x1060];
    int state;
    char pad2298[0x24];
    unsigned char flag;
    char pad22BD[0x277];
    int timer;
} HeroInputState;

typedef struct {
    float v[4];
} InputVector __attribute__((aligned(16)));

extern HeroInputState g_hero_state;
extern int g_pad_held_flags;
extern void moby_transform_joint_to_world(void *, int, void *);
extern void CalculateAimedLaunchVelocity(void *, void *, int, int, float, float, float, float);
extern int coll_trace_projectile_to_impact(void *, void *, void *, void *, void *, int, int, float);
extern int math_fast_float_d(void *);
extern int weapon_spend_ammo(int, int);
extern void start_equipped_item_animation(void);
extern int PlayMobySound(int, int, void *);
extern char *megaturret_spawn_shot(void *, void *, void *);
extern void cancel_hero_item_animation(void);
extern void ref_L00_003C8828_00(void (*)(void *), void *);
extern void owner_effect_draw_active(void *);

/* Per-frame update of the Megaturret Glove weapon (moby class 2661). It aims, waits for the fire button, then after a short delay launches the turret and cools down. */
void megaturret_glove_update(char *owner)
{
    InputVector origin, target;
    InputVector *targetVector;
    char *context = FIELD(owner, char *, 0x68);
    int allowed;
    float radius;

    moby_transform_joint_to_world(owner, 0, &origin);
    targetVector = &target;
    radius = g_hero_state.state == 29 ? 11.0f : 4.5f;
    CalculateAimedLaunchVelocity(targetVector, &origin, 0, 0, 1.5f, radius, 0.25f, 0.0030555557f);
    allowed = 1;
    FIELD(context, int, 0x24) = coll_trace_projectile_to_impact(&origin, targetVector, context,
        context + 0x10, owner, 0, 0, 0.0030555557f);

    if (g_hero_state.state == 29) {
        if (!math_fast_float_d(&g_hero_state.timer))
            allowed = 0;
    } else {
        g_hero_state.timer = 40;
    }

    switch (FIELD(owner, unsigned char, 0x20)) {
    case 0:
        FIELD(owner, unsigned char, 0x20) = 1;
        FIELD(context, int, 0x24) = 0;
        /* Fall through. */
    case 1:
        if ((g_pad_held_flags & g_hero_state.input) && !g_hero_state.flag && allowed) {
            if (weapon_spend_ammo(-1, 1)) {
                start_equipped_item_animation();
                FIELD(owner, unsigned char, 0x20) = 2;
                FIELD(context, int, 0x20) = 20;
            } else {
                PlayMobySound(2, 0, owner);
            }
        }
        break;
    case 2:
        if (math_fast_float_d(context + 0x20)) {
            PlayMobySound(0, 0, owner);
            megaturret_spawn_shot(owner, &origin, targetVector);
            cancel_hero_item_animation();
            FIELD(owner, unsigned char, 0x20) = 3;
            FIELD(context, int, 0x20) = 10;
        }
        break;
    case 3:
        if (math_fast_float_d(context + 0x20))
            FIELD(owner, unsigned char, 0x20) = 1;
        break;
    }
    ref_L00_003C8828_00(owner_effect_draw_active, owner);
}

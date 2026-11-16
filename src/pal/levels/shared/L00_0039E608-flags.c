#include "include_asm.h"
#include "names.h"

typedef struct Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner {
    unsigned char prefix_00[0x68];
    void *context_68;
} Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner;
typedef struct {
    char prefix[0x760];
    float aimAxis[4];
    char pad770[0xAC0];
    unsigned int buttons;
    char pad1234[0xC];
    int resource;
    char pad1244[0x1050];
    int level;
    char pad2298[0x24];
    unsigned char busy;
    char pad22BD[0x277];
    int cooldown;
} LaunchHero;
extern LaunchHero g_hero_state;
extern unsigned int g_pad_pressed_flags;
extern void moby_transform_joint_to_world(char *, int, char *);
extern void CalculateAimedLaunchVelocity(void *, void *, void *, float, float, float, float, void *);
extern int coll_trace_projectile_to_impact_pal(void *, void *, void *, void *, void *, int, int, float);
extern int math_fast_float_d(int *), weapon_spend_ammo(int, int);
extern void cancel_hero_item_animation_pal(void), start_equipped_item_animation_pal(void);
extern int PlayMobySound(int, int, char *);
extern char *decoy_create_projectile(char *, char *);
extern void ref_L00_0039D110_00(void *, void *);
extern void decoy_glove_draw_projectile_pal(Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner *);

/* func_L00_0039B288 is defined in L00_0039B288-g8.c. */


/* Aims and launches the actor's projectile in response to the shared input gate. */
void UpdateProjectileLauncher_pal(char *actor)
{
    char *state = *(char **)(actor + 0x68);
    char position[16], direction[16];
    int ready;
    moby_transform_joint_to_world(actor, 0, position);
    CalculateAimedLaunchVelocity(direction, position, 0, 1.5f, g_hero_state.level == 29 ? 11.0f : 5.0f, 0.20000002f, 0.0044f, 0);
    ready = 1;
    *(int *)(state + 0x24) = coll_trace_projectile_to_impact_pal(position, direction, state, state + 0x10, actor, 0, 0, 0.0044f);
    if (g_hero_state.level == 29) {
        if (!math_fast_float_d(&g_hero_state.cooldown)) ready = 0;
    }
    else g_hero_state.cooldown = 33;
    switch (*(unsigned char *)(actor + 0x20)) {
    case 0:
        *(unsigned char *)(actor + 0x20) = 1;
        *(int *)(state + 0x24) = 0;
    case 1:
        if ((g_pad_pressed_flags & g_hero_state.buttons) == 0 || g_hero_state.busy || g_hero_state.resource < 8 || !ready) break;
        if (weapon_spend_ammo(-1, 1)) {
            start_equipped_item_animation_pal();
            *(unsigned char *)(actor + 0x20) = 2;
            *(int *)(state + 0x20) = 17;
            break;
        }
        PlayMobySound(2, 0, actor);
        break;
    case 2:
        if (!math_fast_float_d((int *)(state + 0x20))) break;
        *(char **)(decoy_create_projectile(position, direction) + 0xB8) = actor;
        cancel_hero_item_animation_pal();
        *(unsigned char *)(actor + 0x20) = 3;
        *(int *)(state + 0x20) = 8;
        break;
    case 3:
        if (math_fast_float_d((int *)(state + 0x20))) *(unsigned char *)(actor + 0x20) = 1;
        break;
    }
    ref_L00_0039D110_00(decoy_glove_draw_projectile_pal, actor);
}

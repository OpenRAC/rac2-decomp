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
extern unsigned int D_00138320;
extern void moby_transform_joint_to_world(char *, int, char *);
extern void CalculateAimedLaunchVelocity(void *, void *, void *, float, float, float, float, void *);
extern int func_PAL_002FF5F8(void *, void *, void *, void *, void *, int, int, float);
extern int math_fast_float_d(int *), weapon_spend_ammo(int, int);
extern void func_PAL_L00_002AF6C0(void), func_PAL_L00_002AF458(void);
extern int PlayMobySound(int, int, char *);
extern char *decoy_create_projectile(char *, char *);
extern void ref_L00_0039D110_00(void *, void *);
extern void func_PAL_L00_003A06F8(Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner *);

/* func_L00_0039B288 is defined in L00_0039B288-g8.c. */


/* Aims and launches the actor's projectile in response to the shared input gate. */
void func_PAL_L00_003A04C8(char *actor)
{
    char *state = *(char **)(actor + 0x68);
    char position[16], direction[16];
    int ready;
    moby_transform_joint_to_world(actor, 0, position);
    CalculateAimedLaunchVelocity(direction, position, 0, 1.5f, g_hero_state.level == 29 ? 11.0f : 5.0f, 0.20000002f, 0.0044f, 0);
    ready = 1;
    *(int *)(state + 0x24) = func_PAL_002FF5F8(position, direction, state, state + 0x10, actor, 0, 0, 0.0044f);
    if (g_hero_state.level == 29) {
        if (!math_fast_float_d(&g_hero_state.cooldown)) ready = 0;
    }
    else g_hero_state.cooldown = 33;
    switch (*(unsigned char *)(actor + 0x20)) {
    case 0:
        *(unsigned char *)(actor + 0x20) = 1;
        *(int *)(state + 0x24) = 0;
    case 1:
        if ((D_00138320 & g_hero_state.buttons) == 0 || g_hero_state.busy || g_hero_state.resource < 8 || !ready) break;
        if (weapon_spend_ammo(-1, 1)) {
            func_PAL_L00_002AF458();
            *(unsigned char *)(actor + 0x20) = 2;
            *(int *)(state + 0x20) = 17;
            break;
        }
        PlayMobySound(2, 0, actor);
        break;
    case 2:
        if (!math_fast_float_d((int *)(state + 0x20))) break;
        *(char **)(decoy_create_projectile(position, direction) + 0xB8) = actor;
        func_PAL_L00_002AF6C0();
        *(unsigned char *)(actor + 0x20) = 3;
        *(int *)(state + 0x20) = 8;
        break;
    case 3:
        if (math_fast_float_d((int *)(state + 0x20))) *(unsigned char *)(actor + 0x20) = 1;
        break;
    }
    ref_L00_0039D110_00(func_PAL_L00_003A06F8, actor);
}

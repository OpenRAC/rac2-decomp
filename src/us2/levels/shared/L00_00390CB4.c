#include "include_asm.h"

/* func_US2_L00_00390CB4, the v2.00 copy of func_L00_0038F8B8: the same C with one test added
 * after the level 111/98 gate, on D_US2_001B1860. */
#include "common.h"
/* Partial resident view: only fields observed by the launch gate are named. */
typedef struct { char pad00[0xA8]; u16 launches; char padAA[2]; u32 bestTime, mask; } LaunchStats;
typedef struct {
    char pad00[0x33C]; char *support; int grounded; char pad344[0x434]; float heading;
    char pad77C[0xAB4]; u32 buttons; char pad1234[0xC]; int resource;
    char pad1244[0x2BC]; int special; char pad1504[0xD90]; int level;
    char pad2298[4]; int state; char pad22A0[0x1C]; u8 busy; char pad22BD[0x22F];
    s16 platform; char pad24EE[0x46]; int cooldown; char pad2538[8];
} TetherLaunchHero;
extern TetherLaunchHero g_hero_state;
extern LaunchStats D_0018C360;
extern int D_L00_001A8F00[] __attribute__((sda)), D_L00_001A8F08[] __attribute__((sda));
typedef struct { char pad00[0x1A4]; u32 buttons; } LaunchInput;
extern LaunchInput g_pad_state;
extern u32 D_001A7390 MACRO_ADDR;
extern u32 g_current_map_index[] __attribute__((sda));
extern char *g_follow_camera_object;
extern float D_US2_001B1860 __attribute__((sda));
extern int math_fast_float_d(int *), weapon_spend_ammo(int, int);
extern float vec_length_xy(void *), mat_fast_helper_a(float, float);
extern void vec_build_spherical_offset(float *, float, float, float), FastVecAdd(void *, void *, void *);
extern void anim_start_blended(void *, int, int, int), level_start_timed_object_once(void);
extern char *visibomb_create_missile(char *, char *, float, float);
extern int PlayMobySound(int, int, char *);
/* Starts the tether when the shared input and movement gates permit it. */
void func_US2_L00_00390CB4(char *actor) {
    int *state;
    int ready;
    float point[4];
    float heading, pitch;
    u32 now;
    if (!actor) return;
    state = *(int **)(actor + 0x68);
    ready = 1;
    math_fast_float_d(state);
    if (g_hero_state.level == 29) { if (!math_fast_float_d(&g_hero_state.cooldown)) ready = 0; }
    else g_hero_state.cooldown = 40;
    if (D_L00_001A8F00[0] || D_L00_001A8F08[0] != -2 || !(g_pad_state.buttons & g_hero_state.buttons) || state[0] || state[1] || g_hero_state.busy) goto finish;
    if (g_hero_state.state == 7 || g_hero_state.state == 2 || g_hero_state.state == 3 || g_hero_state.state == 4 || g_hero_state.state == 5 || g_hero_state.state == 6 || g_hero_state.state == 16 || g_hero_state.state == 14 || g_hero_state.state == 9 || g_hero_state.state == 10 || g_hero_state.state == 11 || g_hero_state.state >= 13 || g_hero_state.level == 111 || g_hero_state.level == 98) goto finish;
    if (D_US2_001B1860 != 0.0f) goto finish;
    if ((g_follow_camera_object && *(short *)(g_follow_camera_object + 0x86) == 5) || !g_hero_state.grounded || g_hero_state.resource < 23) goto finish;
    if (g_hero_state.support && (*(short *)(g_hero_state.support + 0xAA) == 0x13E || *(short *)(g_hero_state.support + 0xAA) == 0x46F) && ready) goto finish;
    if (!weapon_spend_ammo(-1, 1)) goto denied;
    pitch = 0.0f;
    heading = g_hero_state.heading;
    if (g_hero_state.platform == 1 || g_hero_state.special) {
        pitch = mat_fast_helper_a(vec_length_xy(actor + 0xD0), *(float *)(actor + 0xD8));
        vec_build_spherical_offset(point, 0.6f, heading, -pitch);
        FastVecAdd(point, point, actor + 0x10);
    } else {
        vec_build_spherical_offset(point, 0.6f, heading, -pitch);
        FastVecAdd(point, point, actor + 0x10);
    }
    if (*(u8 *)(actor + 0x43) != 3) anim_start_blended(actor, 3, 0, 0);
    level_start_timed_object_once();
    *(char **)(state + 1) = visibomb_create_missile(actor, (char *)point, heading, pitch);
    if (D_0018C360.launches < 0xFFFF) D_0018C360.launches++;
    now = D_001A7390;
    if (D_0018C360.bestTime < now) D_0018C360.bestTime = now;
    D_0018C360.mask |= 1U << g_current_map_index[0];
    D_0018C360.mask |= 0x80000000;
    state[0] = 60;
    goto finish;
denied:
    if (g_pad_state.buttons & g_hero_state.buttons) PlayMobySound(0, 0, actor);
finish:
    if ((*(u8 *)(actor + 0x60) & 2) && *(u8 *)(actor + 0x43) != 1) anim_start_blended(actor, 1, 0, 0);
    *(u16 *)(actor + 0x34) |= 4;
}

#include "include_asm.h"
#include "names.h"

extern void miniturret_glove_draw(char *);
/* Partial resident state layout measured from this handler's accesses. */
typedef struct {
    char p0[0xBF8];
    int heldWeapon;
    char p1[0x1230 - 0xBFC];
    int buttonMask;
    char p2[0x1240 - 0x1234];
    int frameCount;
    char p3[0x1450 - 0x1244];
    int selectedWeapon;
    char p4[0x2294 - 0x1454];
    int mode;
    char p5[0x22BC - 0x2298];
    unsigned char locked;
    char p6[0x2534 - 0x22BD];
    int cooldown;
} HeroState;
extern HeroState g_hero_state;

extern char g_pad_state[];
extern void moby_transform_joint_to_world(char *, int, void *), CalculateAimedLaunchVelocity(void *, void *, float, float, float, float, int, int);
extern int coll_trace_projectile_to_impact(void *, void *, void *, void *, char *, int, int, float);
extern int math_fast_float_d(void *), weapon_spend_ammo(int, int);
extern void start_equipped_item_animation(void), PlayMobySound(int, int, char *), cancel_hero_item_animation(void), ref_L00_003EAA58_00(void *, char *);
extern char *miniturret_spawn_shot(void *, void *);
/* Updates the Miniturret Glove: it aims, then shoots a miniturret after a short wind-up. */
void miniturret_l00_glove_update(char *self)
{
    char muzzlePos[16], aimPos[16];
    char *aimPosPtr;
    char *vars = *(char **)(self + 0x68);
    int ready;
    float reach;
    char *shot;
    moby_transform_joint_to_world(self, 0, muzzlePos);
    aimPosPtr = aimPos;
    reach  =  g_hero_state.mode == 29 ? 11.0f : 4.5f;
    CalculateAimedLaunchVelocity(aimPosPtr, muzzlePos, 1.5f, reach, 0.25f, 0.003055555745959282f, 0, 0);
    *(int *)(vars + 0x24) = coll_trace_projectile_to_impact(muzzlePos, aimPosPtr, vars, vars + 0x10, self, 0, 0, 0.003055555745959282f);
    ready = 1;
    if (g_hero_state.mode == 29) {
        if (!math_fast_float_d(&g_hero_state.cooldown)) ready = 0;
    } else g_hero_state.cooldown = 40;
    switch (*(unsigned char *)(self + 0x20)) {
    case 0:
        self[0x20] = 1;
        *(int *)(vars + 0x24) = 0;
        /* Fall through. */
    case 1:
        if ((*(int *)(g_pad_state + 0x1A4) & g_hero_state.buttonMask) &&
            !g_hero_state.locked && ready) {
            if (weapon_spend_ammo(-1, 1)) {
                start_equipped_item_animation();
                self[0x20] = 2;
                *(int *)(vars + 0x20) = 20;
            } else PlayMobySound(2, 0, self);
        }
        break;
    case 2:
        if (math_fast_float_d(vars + 0x20)) {
            PlayMobySound(0, 0, self);
            shot = miniturret_spawn_shot(muzzlePos, aimPosPtr);
            *(char **)(shot + 0xB8) = self;
            cancel_hero_item_animation();
            self[0x20] = 3;
            *(int *)(vars + 0x20) = 10;
        }
        break;
    case 3:
        if (math_fast_float_d(vars + 0x20)) self[0x20] = 1;
        break;
    }
    ref_L00_003EAA58_00(miniturret_glove_draw, self);
}

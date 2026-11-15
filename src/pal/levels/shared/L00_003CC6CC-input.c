#include "include_asm.h"

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
extern int D_00138324;
extern void moby_transform_joint_to_world(void *, int, void *);
extern void CalculateAimedLaunchVelocity(void *, void *, int, int, float, float, float, float);
extern int func_PAL_002FF5F8(void *, void *, void *, void *, void *, int, int, float);
extern int math_fast_float_d(void *);
extern int weapon_spend_ammo(int, int);
extern void func_PAL_L00_002AF458(void);
extern int PlayMobySound(int, int, void *);
extern char *func_PAL_L00_0038D7E8(void *, void *, void *);
extern void func_PAL_L00_002AF6C0(void);
extern void ref_L00_003C8828_00(void (*)(void *), void *);
extern void func_PAL_L00_003CC908(void *);

void func_PAL_L00_003CC6CC(char *owner)
{
    InputVector origin, target;
    InputVector *targetVector;
    char *context = FIELD(owner, char *, 0x68);
    int allowed;
    float radius;

    moby_transform_joint_to_world(owner, 0, &origin);
    targetVector = &target;
    radius = g_hero_state.state == 29 ? 11.0f : 4.5f;
    CalculateAimedLaunchVelocity(targetVector, &origin, 0, 0, 1.5f, radius, 0.3f, 0.0044f);
    allowed = 1;
    FIELD(context, int, 0x24) = func_PAL_002FF5F8(&origin, targetVector, context,
        context + 0x10, owner, 0, 0, 0.0044f);

    if (g_hero_state.state == 29) {
        if (!math_fast_float_d(&g_hero_state.timer))
            allowed = 0;
    } else {
        g_hero_state.timer = 33;
    }

    switch (FIELD(owner, unsigned char, 0x20)) {
    case 0:
        FIELD(owner, unsigned char, 0x20) = 1;
        FIELD(context, int, 0x24) = 0;
        /* Fall through. */
    case 1:
        if ((D_00138324 & g_hero_state.input) && !g_hero_state.flag && allowed) {
            if (weapon_spend_ammo(-1, 1)) {
                func_PAL_L00_002AF458();
                FIELD(owner, unsigned char, 0x20) = 2;
                FIELD(context, int, 0x20) = 17;
            } else {
                PlayMobySound(2, 0, owner);
            }
        }
        break;
    case 2:
        if (math_fast_float_d(context + 0x20)) {
            PlayMobySound(0, 0, owner);
            func_PAL_L00_0038D7E8(owner, &origin, targetVector);
            func_PAL_L00_002AF6C0();
            FIELD(owner, unsigned char, 0x20) = 3;
            FIELD(context, int, 0x20) = 8;
        }
        break;
    case 3:
        if (math_fast_float_d(context + 0x20))
            FIELD(owner, unsigned char, 0x20) = 1;
        break;
    }
    ref_L00_003C8828_00(func_PAL_L00_003CC908, owner);
}

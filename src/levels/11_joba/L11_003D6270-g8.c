#include "include_asm.h"

#include "common.h"

extern void func_002A7750(u8 *arg0, s32 arg1, s32 arg2);

extern s32 func_002A77E0(s32 arg0);

extern s32 func_L11_00440C80(s32 arg0);

extern s32 D_L11_001B056C __attribute__((sda));

extern s32 D_L11_001B058C __attribute__((sda));

extern f32 D_L11_001B0670;

extern void func_L11_003F33E0(u8 *arg0);

extern void func_L00_002E6EF8(void *arg0, u8 *arg1);

extern void func_L11_003F3CB8(u8 *arg0);

extern void func_L11_003F4F30(u8 *arg0);

extern void func_002AB8C0(u8 *arg0, void *arg1);

extern void func_002A0488(u8 *arg0, u32 arg1, u32 arg2, u32 arg3);

extern void func_002B0990(u8 *arg0, void *arg1, f32 arg2, s32 arg3, s32 arg4);

extern u8 *func_002A9640(s32 arg0, s32 arg1, s32 arg2);

extern f32 func_002A96A0(u8 *arg0, u8 *arg1);

extern void func_002AB800(u8 *arg0, u8 *arg1);

/* The prototype returns a value: that keeps $v0 busy after the call, as the retail has it. */
extern s32 func_002B3380(u8 *arg0, u8 *arg1, u8 *arg2);

extern s32 func_002B3BA8(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, f32 arg5);

extern void func_L11_003F3098(u8 *arg0);

/* The 7.0 the timed effect is compared against, reached through $gp. */
extern f32 D_L11_001B0570 __attribute__((sda));

extern s32 D_L11_001FFA78[];

/* Runs the object's timer down, keeps the shared step counter in step with it, and retires
   the object when the timed effect is over. */
/* Applies damage to the enemy, adds to a score counter, and removes the enemy when it runs
   out of health. */
void func_L11_003F1DB0(u8 *mobyArg) {
    u8 *moby = mobyArg;
    u8 *vars;
    u8 *attacker;
    u8 *hitInfo;
    u32 tableOffset;
    f32 damage;

    if (*(u8 *)(moby + 0x20) == 0) {
        return;
    }
    vars = *(u8 **)(moby + 0x68);
    attacker = FindOwnedEffectSlot(moby, 0x10000, 0);
    damage = UpdateAimTargetStrength(moby, attacker);
    if (attacker != 0) {
        if (*(u8 *)(moby + 0x20) >= 3) {
            *(f32 *)(vars + 0x20) = *(f32 *)(vars + 0x20) - damage;
            /* The index is a byte offset into the table: keeping it in a variable leaves
               the constant out of the symbol's address, as the retail has it. */
            tableOffset = *(u8 *)(vars + 0x37) * 4 + 0xE0;
            *(s32 *)((u8 *)D_L11_001FFA78 + tableOffset) += (s32)(damage * 32.0f);
            if (*(f32 *)(attacker + 0x2C) != 0.0f) {
                hitInfo = vars + 0x70;
                StartColorFade(moby, hitInfo);
                if (*(f32 *)(attacker + 0x2C) >= D_L11_001B0570 || *(f32 *)(vars + 0x20) <= 0.0f) {
                    StartColorFade(moby, hitInfo);
                    SetMobyState(moby, 8, -1);
                }
            }
        }
    }
    *(u8 *)(moby + 0xA8) = 0xFF;
    SpawnDamageDebrisOnHealthLoss(moby, vars + 0x50, vars + 0x20);
    if (*(u8 *)(moby + 0x20) >= 2 && *(u8 *)(vars + 0x2E) == 2) {
        *(s32 *)(vars + 0x20) = 0;
        ResetJobaEnemy(moby);
    }
    *(s32 *)(vars + 0x258) = SelectAimTarget_002B3BA8(moby, *(s32 *)(vars + 0x25C), 0, 0, 200.0f, 200.0f);
}

/* Arms the object's two state records through two callbacks and the class setup, then, when
   the twin record is clear, starts the 0x2A0 animation. */

/* Retires the object and copies two measured state bytes into its state block. */
/* Once the enemy has no pending counters, picks its next state (6 or 7) with a random
   roll. */
void func_L11_003F2D38(u8 *mobyArg) {
    u8 *moby = mobyArg;
    s32 vars = *(s32 *)(moby + 0x68);
    if (*(u16 *)(vars + 0x278) >= 2)
        return;
    if (*(u16 *)(vars + 0x27A) >= 2)
        return;
    if (RandomIntBelow(D_L11_001B058C) != 0
        && GetArenaFighterCount(*(s32 *)(moby + 0xB8)) < D_L11_001B056C) {
        SetMobyState(moby, 7, -1);
    } else {
        SetMobyState(moby, 6, -1);
    }
}

extern void func_00283098(void *out, void *in, void *matrix);

extern void func_00282CC0(void *out, void *in, void *matrix);

extern f32 func_00283248(f32 a0, f32 a1);

extern void func_002833F0(void *a0, void *a1);

extern s32 func_00283CF0(f32 a0);

extern void func_L11_00436910(u8 *a0, s32 a1, s32 a2);

extern void func_L11_004496A0(u8 *a0, s32 a1, s32 a2);

extern void func_L11_0044C328(u8 *a0, s32 a1, s32 a2);

extern void func_L11_00452C58(u8 *a0, s32 a1, s32 a2);

extern void func_L11_00454C78(u8 *a0, s32 a1, s32 a2);

extern void func_L11_00456438(u8 *a0, s32 a1);

extern u32 D_L11_001B0D9C __attribute__((sda));

extern u8 D_00189E20[];

/* Places the measured point on the state's three vertices, then walks them: each one gets
   its angle to the shared origin and the class call its identifier names. */
/* Puts three child objects in place and turns each one toward the player. */
void func_L11_00417340(u8 *mobyArg) {
    u8 *moby = mobyArg;
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 *part;
    u8 *hero;
    f32 localPoint[4];
    s32 offsetTotal;
    s32 i;

    localPoint[0] = 0.0f;
    localPoint[1] = -9.0f;
    localPoint[2] = -3.0f;
    localPoint[3] = 0.0f;
    matrix_mul_vec3(localPoint, localPoint, moby + 0xC0);
    FastVecAdd(localPoint, localPoint, moby + 0x10);

    if (*(u8 **)(vars + 0x10) != 0) {
        *(f32 *)(*(u8 **)(vars + 0x10) + 0x10) = localPoint[0] - 2.0f;
        *(f32 *)(*(u8 **)(vars + 0x10) + 0x14) = localPoint[1];
        *(f32 *)(*(u8 **)(vars + 0x10) + 0x18) = localPoint[2];
        *(f32 *)(*(u8 **)(vars + 0x10) + 0x1C) = localPoint[3];
    }
    if (*(u8 **)(vars + 0x14) != 0) {
        *(f32 *)(*(u8 **)(vars + 0x14) + 0x10) = localPoint[0];
        *(f32 *)(*(u8 **)(vars + 0x14) + 0x14) = localPoint[1] + 1.0f;
        *(f32 *)(*(u8 **)(vars + 0x14) + 0x18) = localPoint[2];
        *(f32 *)(*(u8 **)(vars + 0x14) + 0x1C) = localPoint[3];
    }
    if (*(u8 **)(vars + 0x18) != 0) {
        *(f32 *)(*(u8 **)(vars + 0x18) + 0x10) = localPoint[0];
        *(f32 *)(*(u8 **)(vars + 0x18) + 0x14) = localPoint[1] - 1.0f;
        *(f32 *)(*(u8 **)(vars + 0x18) + 0x18) = localPoint[2];
        *(f32 *)(*(u8 **)(vars + 0x18) + 0x1C) = localPoint[3];
    }

    hero = gHeroState;
    part = *(u8 **)(vars + 0x10);
    offsetTotal = 0;
    for (i = 0; i < 3; i++) {
        if (i == 1) {
            part = *(u8 **)(vars + 0x14);
        }
        if (i == 2) {
            part = *(u8 **)(vars + 0x18);
        }
        if (part == 0) {
            continue;
        }
        *(s32 *)(part + 0xF0) = 0;
        *(f32 *)(part + 0xF4) = 0.0f;
        *(f32 *)(part + 0xF8) = FastMatrixHelperA(*(f32 *)(hero + 0x80) - *(f32 *)(part + 0x10),
                                          *(f32 *)(hero + 0x84) - *(f32 *)(part + 0x14));
        *(s32 *)(part + 0xFC) = 0;
        euler_rotation_basis(part + 0xC0, part + 0xF0);
        switch (*(s16 *)(part + 0xAA)) {
        case 0xD98: /* moby class 3480 */
            InitSecurityRobot(part, offsetTotal, 0);
            break;
        case 0xDCF: /* moby class 3535 */
            InitSmasherRobot(part, offsetTotal, 0);
            break;
        case 0xDF4: /* moby class 3572 */
            InitFlamethrowerRobot(part, offsetTotal, 0);
            break;
        case 0xDF7: /* moby class 3575 */
            *(f32 *)(part + 0x18) += 0.5f;
            InitJobaDroneState(part, FloatToInt((f32)offsetTotal * 0.16666667f), 0);
            break;
        case 0xDF9: /* moby class 3577 */
            ResetPathMoverMoby(part, offsetTotal);
            break;
        case 0xD37: /* moby class 3383 */
            InitEnemyState(part, offsetTotal, 0);
            break;
        }
        offsetTotal += D_L11_001B0D9C;
    }

    *(u8 **)(vars + 0x10) = 0;
    *(u8 **)(vars + 0x14) = 0;
    *(u8 **)(vars + 0x18) = 0;
}

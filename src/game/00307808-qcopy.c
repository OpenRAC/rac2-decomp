#include "include_asm.h"
#include "common.h"

typedef float V4_F307808[4] __attribute__((aligned(16)));

extern u8 D_00139568[];
extern char D_00239BA0[];
extern s32 D_001AEC68 __attribute__((sda));

extern void func_0029FCC0(char *, s32, void *);
extern void func_002FE8D8(char *, void *);
extern char *func_002AB1F0(char *);
extern void func_00282D30(void *, char *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_003001E0(void *, void *, void *);
extern s32 func_002E5DA0(s32, s32, char *, s32);
extern char *func_0031D3E0(void *, void *, float, float, float, float, unsigned char, unsigned char, unsigned char, unsigned char, unsigned short, void *);

#define ENTRY() (D_00239BA0 + D_00139568[0x29] * 0xE0)

/* One step of an object's launch routine: fires the pending shot and counts it down. */
void func_00307808(char *moby)
{
    V4_F307808 upDir, targetPos, shotVelocity, muzzlePos, targetMotion;
    char *vars = *(char **)(moby + 0x68);
    char *targetInfo;
    char *target;
    float speed;
    char *weaponDef;
    char *effect;

    TransformMobyJointToWorld(moby, 1, muzzlePos);
    GetObjectFacingDirection(moby + 0x10, upDir);
    if (*(float *)(vars + 0x5C) == 0.0f) {
        if (*(s32 *)(vars + 0x50) != 0) {
            if (*(char **)(vars + 0x64) != 0) {
                targetInfo = GetMobyPrivateValue0(*(char **)(vars + 0x64));
                target = *(char **)(vars + 0x64);
                qcopy(targetPos, target + 0x10);
                if (targetInfo != 0) {
                    FastVecScale(targetMotion, target + 0xE0, *(float *)(targetInfo + 0x10));
                    FastVecAdd(targetPos, targetPos, targetMotion);
                }
                weaponDef = ENTRY();
                speed = *(float *)(weaponDef + 0x50) * 0.016666668f;
                FastVecSub(shotVelocity, targetPos, muzzlePos);
                vec_scale_to_length(shotVelocity, shotVelocity, speed);
                PlaySoundFromClassBank(0, 0, moby, 0x1367 /* Megaturret */);
                effect = CreateShotMoby(muzzlePos, shotVelocity, 2.0f, 15.0f, 0.5f, 3.0f, 0x50, 0xC8, 1, 0, 0x10E, *(char **)(vars + 0x64));
                if (effect != 0)
                    *(s32 *)(effect + 0xB8) = *(s32 *)(vars + 0x68);
                *(s32 *)(vars + 0x40) = D_001AEC68;
                *(s32 *)(vars + 0x44) = 6;
                if (--*(s32 *)(vars + 0x60) <= 0)
                    *(u8 *)(moby + 0x20) = 8;
                *(float *)(vars + 0x5C) = 0.6666667f;
            }
        }
    }
}

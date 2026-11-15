#include "include_asm.h"
#include "common.h"

typedef float V4_F307808[4] __attribute__((aligned(16)));

extern u8 g_item_slot_to_record[];
extern char g_weapon_table[];
extern s32 D_001AEC68 __attribute__((sda));

extern void moby_transform_joint_to_world(char *, s32, void *);
extern void moby_get_facing_direction(char *, void *);
extern char *moby_get_private_value_0(char *);
extern void FastVecScale(void *, char *, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void vec_add_transformed_or_copy(void *, void *, void *);
extern s32 snd_play_from_class_bank(s32, s32, char *, s32);
extern char *shot_moby_create(void *, void *, float, float, float, float, unsigned char, unsigned char, unsigned char, unsigned char, unsigned short, void *);

#define ENTRY() (D_00239BA0 + D_00139568[0x29] * 0xE0)

/* One step of an object's launch routine: fires the pending shot and counts it down. */
void megaturret_fire_shot(char *moby)
{
    V4_F307808 upDir, targetPos, shotVelocity, muzzlePos, targetMotion;
    char *vars = *(char **)(moby + 0x68);
    char *targetInfo;
    char *target;
    float speed;
    char *weaponDef;
    char *effect;

    moby_transform_joint_to_world(moby, 1, muzzlePos);
    moby_get_facing_direction(moby + 0x10, upDir);
    if (*(float *)(vars + 0x5C) == 0.0f) {
        if (*(s32 *)(vars + 0x50) != 0) {
            if (*(char **)(vars + 0x64) != 0) {
                targetInfo = moby_get_private_value_0(*(char **)(vars + 0x64));
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
                snd_play_from_class_bank(0, 0, moby, 0x1367 /* Megaturret */);
                effect = shot_moby_create(muzzlePos, shotVelocity, 2.0f, 15.0f, 0.5f, 3.0f, 0x50, 0xC8, 1, 0, 0x10E, *(char **)(vars + 0x64));
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

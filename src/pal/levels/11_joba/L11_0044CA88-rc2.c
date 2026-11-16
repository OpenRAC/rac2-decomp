#include "include_asm.h"

#include "common.h"
extern s8 *ref_L11_00447360_00;
extern s8 ref_L11_00447360_01[];
extern void ref_L11_00447360_02(void *, s32, s32, void *, s8 *, f32);
extern void ref_L11_00447360_03(void *);
extern void ref_L11_00447360_04(void *);
extern void ref_L11_00447360_05(void *);
extern void ref_L11_00447360_06(void *);
extern void ref_L11_00447360_07(void *);
extern void ref_L11_00447360_08(void *);
extern void ref_L11_00447360_09(void *);
extern void ref_L11_00447360_10(void *);
extern void ref_L11_00447360_11(void *);
extern void ref_L11_00447360_12(void *);

/* Walks the level's moby list and calls the per-class special update for each class that has
   one (decoys, sheep, turrets, tesla barriers and so on). */
void moby_update_class_specials_pal(s32 effect_arg) {
    s8 *moby;
    s16 class_id;

    moby = ref_L11_00447360_00;
    if (moby != 0) {
        do {
            class_id = *(s16 *)(moby + 0xAA);
            switch (class_id) {
            case MOBY_CLASS_DECOY:
                ref_L11_00447360_02(moby, effect_arg, 0x10000, moby + 0x10, ref_L11_00447360_01, 100.0f);
                break;
            case MOBY_CLASS_SHEEP:
                ref_L11_00447360_11(moby);
                break;
            case MOBY_CLASS_DARK_SHEEP:
                ref_L11_00447360_12(moby);
                break;
            case MOBY_CLASS_SYNTHENOID:
                ref_L11_00447360_06(moby);
                break;
            case MOBY_CLASS_KILONOID:
                ref_L11_00447360_05(moby);
                break;
            case MOBY_CLASS_MINITURRET:
                ref_L11_00447360_07(moby);
                break;
            case MOBY_CLASS_MEGATURRET:
                ref_L11_00447360_08(moby);
                break;
            case 0x326:
                ref_L11_00447360_03(moby);
                break;
            case MOBY_CLASS_SHIELD_CHARGER:
            case MOBY_CLASS_TESLA_BARRIER:
                ref_L11_00447360_04(moby);
                break;
            case 0xE20:
                ref_L11_00447360_10(moby);
                break;
            case 0xAE0:
            case 0xAE1:
            case 0xAE2:
            case 0xAEC:
            case 0xB06:
            case 0xB09:
            case 0xCC0 ... 0xCC9:
            case MOBY_CLASS_AMMO:
                ref_L11_00447360_09(moby);
                break;
            default:
                break;
            }
            moby = *(s8 **)(moby + 0x28);
        } while (moby != 0);
    }
}

#include "include_asm.h"

#include "common.h"
extern void ref_L09_003F0378_00(void);
extern s32 ref_L09_003F0378_01(f32);
extern void ref_L09_003F0378_02(void *, s32, s32, s32);
extern void ref_L09_003F0378_03(void *, s32, s32);
extern s32 ref_L09_003F0378_04(void *, s32, s32);
extern f32 ref_L09_003F0378_05(void *, s32);
extern void ref_L09_003F0378_06(void *, void *);
extern void ref_L09_003F0378_07(void *, s32);
extern void ref_L09_003F0378_08(void *, s32, s32, s32, f32, f32);

void dobbo_handle_damage_pal(void *moby) {
    void *vars;
    s32 hit_flag;
    s32 hit_result;
    s32 is_dead ;
    void *hit_info;
    f32 new_health;
    f32 damage;

    vars = *(void **)((s8 *)moby + 0x68);
    if (*(u8 *)((s8 *)moby + 0x95) == 0) {
        hit_info = (s8 *)vars + 0x70;
        ref_L09_003F0378_00();
    } else {
        hit_info = (s8 *)vars + 0x70;
        hit_flag = 0;
        hit_result = ref_L09_003F0378_04(moby, 0x10000, 0);
        is_dead = *(s16 *)((s8 *)vars + 0x26) < 1;
        hit_flag = is_dead ? hit_result : hit_flag;
        damage = ref_L09_003F0378_05(moby, hit_flag);
        if (hit_flag != 0) {
            if (damage > 0.0f) {
                new_health = *(f32 *)((s8 *)vars + 0x20) - damage;
                *(f32 *)((s8 *)vars + 0x20) = new_health;
                if (new_health <= 0.0f) {
                    ref_L09_003F0378_03(moby, 6, 4);
                } else {
                    *(s8 *)((s8 *)vars + 0x77) = (s8)(ref_L09_003F0378_01(damage * 20.0f) + 0x64);
                    ref_L09_003F0378_06(moby, hit_info);
                    if (*(u8 *)((s8 *)moby + 0x43) != 4) {
                        ref_L09_003F0378_02(moby, 4, 0, 1);
                    }
                    ref_L09_003F0378_03(moby, 5, -1);
                }
            }
        }
        *(u8 *)((s8 *)moby + 0xA8) = 0xFF;
    }
    ref_L09_003F0378_07(moby, (s32)hit_info);
    ref_L09_003F0378_08(moby, *(s32 *)((s8 *)vars + 0x8C), 0, 0, 0.0f, 0.0f);
}

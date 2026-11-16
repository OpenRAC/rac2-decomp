#include "include_asm.h"

#include "common.h"
extern s32 g_guard_attack_sequence_value __attribute__((sda));
extern s32 path_is_entry_reachable_pal(void *, s32);
extern s32 enemy_select_path(void *, s32, s32);
extern s32 math_random_int_range(s32, s32);
extern void guard_switch_animation_pal(void *, s32, s32, s32);
extern void moby_set_state(void *, s32, s32);
extern s32 path_toggle_handle_cache(void *);
extern s32 func_001163B0(void);
extern void anim_start_blended_pal(void *, s32, s32, s32);

/* Runs the guard's attack animation sequence. When one animation finishes it picks the next,
   and it keeps the held partner object in the right pose (PAL: 50 Hz timings). */
void guard_update_attack_sequence_pal(u8 *self)
{
    u8 *vars=*(u8 **)(self+0x68);
    s32 ready=1;
    if (*(s32 *)(vars+0x2DC)!=-1) ready=path_is_entry_reachable_pal(self,*(s32 *)(vars+0x2DC))!=0;
    if (ready) {
        switch(self[0x95]) {
        case 3:
            *(s32 *)(vars+0x138)&=~4;
            if (vars[0x302]&2) vars[0x302]=0;
            enemy_select_path(self,*(s32 *)(vars+0x2BC),-1);
            if (vars[0x30E]) {
                guard_switch_animation_pal(self,4,0,math_random_int_range(7,12));
                moby_set_state(self,4,5);
            } else {
                guard_switch_animation_pal(self,12,0,math_random_int_range(7,12));
                moby_set_state(self,8,5);
            }
            break;
        case 4:
            enemy_select_path(self,*(s32 *)(vars+0x2B4),-1);
            moby_set_state(self,5,1);
            break;
        case 5: {
            s32 grab_done=path_toggle_handle_cache(self);
            if (!vars[0x303] || grab_done) {
                guard_switch_animation_pal(self,12,0,math_random_int_range(7,12));
                moby_set_state(self,8,5);
                *(u16 *)(vars+0x2E4)=((s32)(g_guard_attack_sequence_value) * 5 + 2) / 6;
            }
            break;
        }
        case 1:
        case 6:
            path_toggle_handle_cache(self);
            if(self[0x60]&2) {
                s32 side=func_001163B0()&1;
                guard_switch_animation_pal(self,side,0,math_random_int_range(10,20));
                moby_set_state(self,5,-1);
            }
            break;
        }
    } else if(vars[0x303] && self[0x95]==5) {
        u8 *helper=*(u8 **)(vars+0x2F8);
        if(helper && *(s16 *)(helper+0xAA)==0x114B /* moby class 4427 */ && helper[0x20]!=0xFE && helper[0x20]!=0xFD) {
            vars[0x30C]=0;
            vars[0x30D]=1;
            if(helper[0x42]==10) guard_aim_hand_helper_at_target_pal(self);
            else if(helper[0x43]!=10) anim_start_blended_pal(helper,10,0,10);
        }
    }
}

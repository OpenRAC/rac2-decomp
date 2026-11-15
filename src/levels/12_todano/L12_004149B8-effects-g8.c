#include "common.h"
extern s32 D_L12_001B1828 __attribute__((sda));

typedef struct { char pad[0x2F0]; u8 *slots[2]; } SlotVars;
extern s32 path_is_entry_reachable(void *, s32);
extern s32 enemy_select_path(void *, s32, s32);
extern s32 math_random_int_range(s32, s32);
extern void guard_switch_animation(void *, s32, s32, s32);
extern void moby_set_state(void *, s32, s32);
extern s32 path_toggle_handle_cache(void *);
extern s32 func_001163B0(void);
extern void anim_start_blended(void *, s32, s32, s32);
/* Runs the guard's attack animation sequence. When one animation finishes it picks the next,
   and it keeps the held partner object in the right pose. */
void guard_update_attack_sequence(u8 *moby)
{
    u8 *vars=*(u8 **)(moby+0x68);
    s32 ready=1;
    if (*(s32 *)(vars+0x2DC)!=-1) ready=path_is_entry_reachable(moby,*(s32 *)(vars+0x2DC))!=0;
    if (ready) {
        switch(moby[0x95]) {
        case 3:
            *(s32 *)(vars+0x138)&=~4;
            if (vars[0x302]&2) vars[0x302]=0;
            enemy_select_path(moby,*(s32 *)(vars+0x2BC),-1);
            if (vars[0x30E]) {
                guard_switch_animation(moby,4,0,math_random_int_range(7,12));
                moby_set_state(moby,4,5);
            } else {
                guard_switch_animation(moby,12,0,math_random_int_range(7,12));
                moby_set_state(moby,8,5);
            }
            break;
        case 4:
            enemy_select_path(moby,*(s32 *)(vars+0x2B4),-1);
            moby_set_state(moby,5,1);
            break;
        case 5: {
            s32 grabDone=path_toggle_handle_cache(moby);
            if (!vars[0x303] || grabDone) {
                guard_switch_animation(moby,12,0,math_random_int_range(7,12));
                moby_set_state(moby,8,5);
                *(u16 *)(vars+0x2E4)=D_L12_001B1828;
            }
            break;
        }
        case 1:
        case 6:
            path_toggle_handle_cache(moby);
            if(moby[0x60]&2) {
                s32 side=func_001163B0()&1;
                guard_switch_animation(moby,side,0,math_random_int_range(10,20));
                moby_set_state(moby,5,-1);
            }
            break;
        }
    } else if(vars[0x303] && moby[0x95]==5) {
        u8 *partner=*(u8 **)(vars+0x2F8);
        if(partner && *(s16 *)(partner+0xAA)==0x114B /* moby class 4427 */ && partner[0x20]!=0xFE && partner[0x20]!=0xFD) {
            vars[0x30C]=0;
            vars[0x30D]=1;
            if(partner[0x42]==10) guard_aim_hand_helper_at_target(moby);
            else if(partner[0x43]!=10) anim_start_blended(partner,10,0,10);
        }
    }
}

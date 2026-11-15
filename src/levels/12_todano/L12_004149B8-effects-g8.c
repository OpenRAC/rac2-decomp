#include "common.h"
extern s32 D_L12_001B1828 __attribute__((sda));

typedef struct { char pad[0x2F0]; u8 *slots[2]; } SlotVars;
extern s32 func_L09_003F7A88(void *, s32);
extern s32 func_L09_003F7C50(void *, s32, s32);
extern s32 func_002A7820(s32, s32);
extern void func_L12_00412E50(void *, s32, s32, s32);
extern void func_002A7750(void *, s32, s32);
extern s32 func_L09_003F9928(void *);
extern s32 func_001163B0(void);
extern void func_002A7470(void *, s32, s32, s32);
/* Runs the guard's attack animation sequence. When one animation finishes it picks the next,
   and it keeps the held partner object in the right pose. */
void func_L12_00414EB8(u8 *moby)
{
    u8 *vars=*(u8 **)(moby+0x68);
    s32 ready=1;
    if (*(s32 *)(vars+0x2DC)!=-1) ready=IsPathEntryReachable(moby,*(s32 *)(vars+0x2DC))!=0;
    if (ready) {
        switch(moby[0x95]) {
        case 3:
            *(s32 *)(vars+0x138)&=~4;
            if (vars[0x302]&2) vars[0x302]=0;
            SelectEnemyPath(moby,*(s32 *)(vars+0x2BC),-1);
            if (vars[0x30E]) {
                SwitchGuardAnimation(moby,4,0,RandomIntRange(7,12));
                SetMobyState(moby,4,5);
            } else {
                SwitchGuardAnimation(moby,12,0,RandomIntRange(7,12));
                SetMobyState(moby,8,5);
            }
            break;
        case 4:
            SelectEnemyPath(moby,*(s32 *)(vars+0x2B4),-1);
            SetMobyState(moby,5,1);
            break;
        case 5: {
            s32 grabDone=TogglePathHandleCache(moby);
            if (!vars[0x303] || grabDone) {
                SwitchGuardAnimation(moby,12,0,RandomIntRange(7,12));
                SetMobyState(moby,8,5);
                *(u16 *)(vars+0x2E4)=D_L12_001B1828;
            }
            break;
        }
        case 1:
        case 6:
            TogglePathHandleCache(moby);
            if(moby[0x60]&2) {
                s32 side=Rand()&1;
                SwitchGuardAnimation(moby,side,0,RandomIntRange(10,20));
                SetMobyState(moby,5,-1);
            }
            break;
        }
    } else if(vars[0x303] && moby[0x95]==5) {
        u8 *partner=*(u8 **)(vars+0x2F8);
        if(partner && *(s16 *)(partner+0xAA)==0x114B /* moby class 4427 */ && partner[0x20]!=0xFE && partner[0x20]!=0xFD) {
            vars[0x30C]=0;
            vars[0x30D]=1;
            if(partner[0x42]==10) AimGuardHandHelperAtTarget(moby);
            else if(partner[0x43]!=10) StartAnimationBlended(partner,10,0,10);
        }
    }
}

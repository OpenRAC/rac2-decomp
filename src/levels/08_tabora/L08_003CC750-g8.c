#include "common.h"
#define F(p,T,o) (*(T *)((char *)(p)+(o)))
typedef struct { char pad[0x2294]; int mode; int unused; int action; } Globals;
extern Globals D_00189E20;
typedef struct { char pad0[0x24]; char *descriptor; char pad1[4]; float scale; } ObjectView;
extern char D_00189EA0[], D_0019B2E8[], D_0019B4A8[];
extern u8 D_L08_001B2840[] MACRO_ADDR;
extern struct { char pad[0x464]; u8 flags[0]; } D_L08_0021DE80, D_L08_0021EAF0;
extern int D_001A79F0;
extern u16 D_001A7A1A;
extern u8 D_001A7A60[] MACRO_ADDR;
extern int D_L08_001A903C __attribute__((sda));
extern float D_L08_001AFED0 __attribute__((sda)), D_L08_001AFED4 __attribute__((sda)), D_L08_001AFED8 __attribute__((sda));
extern float D_L08_001AFEDC __attribute__((sda)), D_L08_001AFEE4 __attribute__((sda)), D_L08_001AFEE8 __attribute__((sda));
extern void func_002A7750(void *,int,int), func_002A7470(void *,int,int,int);
extern void func_L08_003CC4B8(void *);
extern float func_00282E80(void *,void *), func_00282E20(void *);
extern void func_00282CF0(void *,void *,void *), func_00282FB8(void *,void *,float), func_00282CC0(void *,void *,void *);
extern int func_002E5DA0(int,int,void *,int);
extern int func_002E5E58(int, int, void *);
extern void func_0029F338(void *), func_002B0A18(int, int);
extern int func_L08_00435938(void);
/* Collectible that waits until the hero is close, then flies to the hero, shrinks, and is collected with a sound and a saved flag. */
void func_L08_003CC750(char *moby) {
    char *vars;
    float toHero[4] __attribute__((aligned(16)));
    float heroDistance, flySpeed, arriveDistance;
    F(moby,u16,0x96)++;
    vars = F(moby,char *,0x68);
    switch (F(moby,u8,0x20)) {
    case 0:
        F(moby,u8,0x23) = 0x50;
        F(moby,u16,0x34) |= 0x800;
        SetMobyState(moby,1,-1);
        if (F(moby,u8,0x43)) StartAnimationBlended(moby,0,0,0);
        break;
    case 1:
        if (vec_distance_xy(moby+0x10,gHeroPosition) < D_L08_001AFED0) {
            F(vars,float,0) = D_L08_001AFEE4;
            if (F(moby,u8,0x43) != 1) StartAnimationBlended(moby,1,0,0x14);
            F(moby,float,0x48) = F(vars,float,0) + F(vars,float,0);
            SetMobyState(moby,2,-1);
        }
        if (F(moby,u8,0x31)) DrawGlowingSparkRings(moby);
        break;
    case 2:
        F(vars,float,0) += (1.0f - F(vars,float,0)) * D_L08_001AFEDC;
        F(moby,float,0x48) = F(vars,float,0) + F(vars,float,0);
        FastVecSub(toHero,gHeroPosition,moby+0x10);
        toHero[2] += 0.6f;
        heroDistance = vec_length_xy(toHero);
        arriveDistance = 0.12f;
        if (F(moby,u16,0x96) < 180) {
            if (F(gHeroPosition,int,0x2214) != 0x31)
                flySpeed = D_L08_001AFED4 * (F(vars,float,0) * 0.016666668f);
            else {
                flySpeed = D_L08_001AFED8 * (F(vars,float,0) * 0.016666668f);
                arriveDistance = 0.8f;
            }
        } else flySpeed = F(vars,float,0) + F(vars,float,0);
        FastVectorDivideHelper(toHero,toHero,flySpeed);
        FastVecAdd(moby+0x10,moby+0x10,toHero);
        if (((ObjectView *)moby)->scale > 0.1f || heroDistance < arriveDistance || heroDistance < flySpeed)
            ((ObjectView *)moby)->scale -= D_L08_001AFEE8 * F(((ObjectView *)moby)->descriptor,float,0x24);
        if ((heroDistance < flySpeed && ((ObjectView *)moby)->scale < F(((ObjectView *)moby)->descriptor,float,0x24)*0.01f) ||
            gHeroState.action == 0x14 || gHeroState.action == 0x19 ||
            gHeroState.mode == 0x39 || gHeroState.mode == 0x6F) {
            PlaySoundFromClassBank(3,0,moby,0x96A);
            D_001A7A1A++;
            if (F(vars,char *,4)) {
                D_L08_0021DE80.flags[F(F(vars,char *,4),short,0xB2)] = F(F(vars,char *,4),u8,0xB0)+2;
                if (F(F(vars,char *,4),u8,0xB0) == 0xFF ||
                    (!(D_L08_001B2840[F(F(vars,char *,4),u8,0xB0)] & 0x80) &&
                     (F(D_0019B2E8,u8,F(F(vars,char *,4),u8,0xB0)+(gCurrentMapIndex<<4)) & 0x80)))
                    D_L08_0021EAF0.flags[F(F(vars,char *,4),short,0xB2)] = F(F(vars,char *,4),u8,0xB0)+2;
                {
                    u16 flagIndex = F(F(vars,char *,4),u16,0xB2);
                    if (flagIndex & 1) {
                        u8 *flagBits = (u8 *)D_0019B4A8 + (((short)flagIndex >> 1) + (gCurrentMapIndex << 10));
                        if (((*flagBits >> 4) & 7) != 7) *flagBits += 0x10;
                    } else {
                        u8 *flagBits = (u8 *)D_0019B4A8 + (((short)flagIndex >> 1) + (gCurrentMapIndex << 10));
                        if ((*flagBits & 7) != 7) ++*flagBits;
                    }
                }
            }
            MarkMobySpawned(moby);
            if (!GetLevelSavedCount() && !D_001A7A60[5]) {
                D_001A7A60[5] = 1;
                PlaySoundFromGlobalBank(1,0,0);
                SetEntryValueByIndex(0x1233,-1);
                D_L08_001A903C = 1;
            }
        } else DrawGlowingSparkRings(moby);
        break;
    }
}

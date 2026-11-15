#include "common.h"

/* Ammo pickup physics and collection. The corresponding RAC1 body is
 * devestator_ammo_update in trespasser_and_throwing_gloves.c.
 * -G8 supplies the timestamp store; -g retains the division's label padding.
 */
typedef float VecE[4] __attribute__((aligned(16)));
extern VecE D_001BAFB0, D_001BAFA0;

typedef struct {
    u8 pad00[0x80]; VecE position; u8 pad90[0x50]; VecE pickup_target;
    u8 padF0[0x2290-0xF0]; void *moby;
    u8 pad2294[0x24A4-0x2294]; f32 reach_distance, reach_height;
    u8 pad24AC[0x20]; s32 health;
} AmmoHero;
extern AmmoHero D_00189E20;
typedef struct {
    u8 pad00[0x38]; s16 sound_multiple, sound_single;
    u8 pad3C[0x8E - 0x3C]; u16 max_ammo; u8 pad90[0x50];
} AmmoDef;
extern u8 D_00239BA0[];
extern u8 D_00139568[];
extern s32 D_00139688[];
extern void *D_0018C0B0 NOT_SDA;
extern s32 D_001B1688[] __attribute__((sda));
extern s32 D_001B24A8[] __attribute__((sda));
/* The sound timestamp is read absolutely and written through the SDA alias.
 * Both declarations bind to the same word in each program.
 */
extern s32 D_001B24A8_gp SDATA(D_001B24A8);
extern s32 func_00282948(s32 *);
extern u32 func_0026F740(s32, s32);
extern s32 func_002E5DA0(s32, s32, void *, s32);
extern f32 func_002AA2E8(f32 *, f32, f32);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282C88(void *);
extern void func_00282F20(void *, void *, f32);
extern void func_002B0A48(s32, s32, s32);
extern void func_0029F338(void *);
extern f32 func_00282DF0(void *);
extern f32 func_00282C48(f32);
extern f32 func_00282E80(void *, void *);
extern f32 func_002A0558(void *, void *);
extern f32 func_00282E48(void *, void *);
extern f32 func_00283180(f32);
extern s32 func_00277258(void *, s32, s32, f32);
extern s32 func_002761F8(void *, void *, s32, s32, s32);
extern s32 func_00283CF0(f32);
extern s32 func_00282C30(s32);

#define EF(p, n) (*(f32 *)((u8 *)(p) + (n)))
#define EI(p, n) (*(s32 *)((u8 *)(p) + (n)))

/* Updates an ammo pickup. It falls and bounces, fades in when it can be collected, flies to the player when picked up and adds the ammo. */
void func_0030ECC8(u8 *object)
{
    VecE start, next;
    f32 alpha;
    u8 *vars = *(u8 **)(object+0x68);
    FastFloatHelperD((s32 *)(vars+0x20));
    if (object[0x20] == 1 || object[0x20] == 4 || object[0x20] == 3) {
        if (FastVecLength(vars+0x10) != 0.0f) {
            qcopy(start, object+0x10);
            start[2] += 0.5f;
            if (TestPointAgainstCollision(start,2,0,0.4f)) {
                qcopy(object+0x10,D_001BAFB0);
                EF(object,0x18) -= 0.5f;
            }
        }
        EF(vars,0x18) -= 0.0013611112f;
        FastVecAdd(next,object+0x10,vars+0x10);
        EF(vars,0x18) -= 0.0013611112f;
        qcopy(start,object+0x10);
        start[2] += 0.1f;
        if (CollLine(start,next,2,0,0)) {
            ClearVector128(vars+0x10);
            qcopy(object+0x10,D_001BAFA0);
        } else qcopy(object+0x10,next);
    }
    switch (object[0x20]) {
    case 0:
        object[0x20]=1;
        break;
    case 1: {
        AmmoDef *entry, *defs;
        u8 *mapping;
        s32 *counts;
        s32 eligible, old, current, difference, item, sound_item, sound;
        s32 elapsed;
        alpha = (f32)object[0x23];
        ApproachValue(&alpha,128.0f,4.0f);
        object[0x23] = FloatToInt(alpha);
        if (EI(vars,0x20)>0) break;
        if (FastVecLength(vars+0x10) != 0.0f) break;
        eligible=1;
        if (FloatAbs(EF(object,0x18)-gHeroState.position[2]) > gHeroState.reach_height) eligible=0;
        else if (vec_distance_xy(object+0x10,gHeroState.position)>gHeroState.reach_distance) eligible=0;
        item=EI(vars,8);
        mapping=gItemSlotToRecord;
        counts=gItemAmmoCounts;
        defs=(AmmoDef *)gWeaponTable_00239BA0;
        entry=&defs[mapping[item]];
        old=counts[item];
        if (old >= entry->max_ammo) eligible=0;
        if (EF(object,0x18)<EF(vars,0x28)-2.0f) eligible=1;
        if (!gHeroState.health) eligible=0;
        if (eligible) {
            EmptyStubF740(item,EI(vars,0));
            sound_item=EI(vars,8);
            current=counts[sound_item];
            if (old<current) {
                difference=current-old;
                if (difference==1) sound=defs[mapping[sound_item]].sound_single;
                else sound=defs[mapping[sound_item]].sound_multiple;
                ForwardThreeArgumentCall(sound,difference,-1);
            }
            object[0x20]=2;
            EF(object,0x2C)*=1.2f;
            ClearVector128(vars+0x10);
            elapsed=gGameTime[0]-D_001B24A8[0];
            EF(vars,0x24)=0.13333334f;
            if (subtract_integer_with_clamp(elapsed)>=11) {
                PlaySoundFromClassBank(0,0,object,0xD5);
                /* Last pickup-sound frame. */
                D_001B24A8_gp=gGameTime[0];
            }
        } else {
            if (object[0x23]<255) object[0x23]++;
            if (func_002A0558(object,gHeroState.moby)<=-0.2f) {
                object[0x20]=3;
                *(s16 *)(vars+6)=60;
            }
        }
        break;
    }
    case 2: {
        f32 speed, factor;
        ApproachValue((f32 *)(vars+0x24),0.0f,0.006666667f);
        EF(object,0x18)+=EF(vars,0x24);
        speed=FastVecLength(vars+0x10);
        ApproachValue(&speed,1.0666667f,0.006666667f);
        FastVecSub(vars+0x10,gHeroState.pickup_target,object+0x10);
        if (EF(object,0x2C)==0.0f || FastVecLength(vars+0x10)<speed) { MarkMobySpawned(object); break; }
        vec_scale_to_length(vars+0x10,vars+0x10,speed);
        FastVecAdd(object+0x10,object+0x10,vars+0x10);
        factor=fast_vec_dist(object+0x10,gHeroState.pickup_target)/(speed*30.0f+0.01f);
        if (factor>1.0f) factor=1.0f;
        else if (factor<0.3f) factor=0.3f;
        ApproachValue((f32 *)(object+0x2C),EF(*(u8 **)(object+0x24),0x24)*factor,EF(*(u8 **)(object+0x24),0x24)*0.1f);
        break;
    }
    case 3: {
        f32 factor;
        s32 item, phase, pulse;
        AmmoDef *entry, *defs;
        u8 *mapping;
        s32 *counts;
        phase = gGameTime[0]%60;
        alpha=(f32)object[0x23];
        factor=FastSinOrCosA((f32)phase*0.104719676f-3.1415901f);
        pulse=FloatToInt(factor*5.0f+5.0f)+10;
        ApproachValue(&alpha,(f32)pulse,4.0f);
        object[0x23]=FloatToInt(alpha);
        if (func_002A0558(object,gHeroMoby_0018C0B0)>=0.0f) goto reactivate;
        item=EI(vars,8);
        mapping=gItemSlotToRecord;
        counts=gItemAmmoCounts;
        defs=(AmmoDef *)gWeaponTable_00239BA0;
        entry=&defs[mapping[item]];
        if (counts[item]>=entry->max_ammo) break;
    reactivate:
        object[0x20]=1;
        break;
    }
    case 4: {
        u8 *entry;
        entry=*(u8 **)(object+0x24);
        EF(object,0x2C)+=(EF(entry,0x24)-EF(object,0x2C))*0.03f;
        if ((EF(entry,0x24)-EF(object,0x2C))/EF(entry,0x24)<0.01f) {
            EF(object,0x2C)=EF(entry,0x24);
            object[0x20]=1;
            EI(object,0x98)=EI(entry,0x10);
        }
        break;
    }
    }
}

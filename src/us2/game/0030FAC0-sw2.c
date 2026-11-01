#include "include_asm.h"

#include "common.h"
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
extern s32 D_001B24A8_gp SDATA(D_001B24A8);
extern s32 func_00282948(s32 *);
extern u32 func_0026F748(s32, s32);
extern s32 func_002E5DA0(s32, s32, void *, s32);
extern f32 func_002AA2E8(f32 *, f32, f32);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282C88(void *);
extern void func_00282F20(void *, void *, f32);
extern void func_US2_002B18B0(s32, s32, s32);
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
extern u32 ref_US2_0030FAC0_00(s32, s32);

void func_US2_0030FAC0(u8 *object)
{
    VecE start, next;
    f32 alpha;
    u8 *state = *(u8 **)(object+0x68);
    func_00282948((s32 *)(state+0x20));
    if (object[0x20] == 1 || object[0x20] == 4 || object[0x20] == 3) {
        if (func_00282DF0(state+0x10) != 0.0f) {
            qcopy(start, object+0x10);
            start[2] += 0.5f;
            if (func_00277258(start,2,0,0.4f)) {
                qcopy(object+0x10,D_001BAFB0);
                EF(object,0x18) -= 0.5f;
            }
        }
        EF(state,0x18) -= 0.0013611112f;
        func_00282CC0(next,object+0x10,state+0x10);
        EF(state,0x18) -= 0.0013611112f;
        qcopy(start,object+0x10);
        start[2] += 0.1f;
        if (func_002761F8(start,next,2,0,0)) {
            func_00282C88(state+0x10);
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
        func_002AA2E8(&alpha,128.0f,4.0f);
        object[0x23] = func_00283CF0(alpha);
        if (EI(state,0x20)>0) break;
        if (func_00282DF0(state+0x10) != 0.0f) break;
        eligible=1;
        if (func_00282C48(EF(object,0x18)-D_00189E20.position[2]) > D_00189E20.reach_height) eligible=0;
        else if (func_00282E80(object+0x10,D_00189E20.position)>D_00189E20.reach_distance) eligible=0;
        item=EI(state,8);
        mapping=D_00139568;
        counts=D_00139688;
        defs=(AmmoDef *)D_00239BA0;
        entry=&defs[mapping[item]];
        old=counts[item];
        if (old >= entry->max_ammo) eligible=0;
        if (EF(object,0x18)<EF(state,0x28)-2.0f) eligible=1;
        if (!D_00189E20.health) eligible=0;
        if (eligible) {
            ref_US2_0030FAC0_00(item,EI(state,0));
            sound_item=EI(state,8);
            current=counts[sound_item];
            if (old<current) {
                difference=current-old;
                if (difference==1) sound=defs[mapping[sound_item]].sound_single;
                else sound=defs[mapping[sound_item]].sound_multiple;
                func_US2_002B18B0(sound,difference,-1);
            }
            object[0x20]=2;
            EF(object,0x2C)*=1.2f;
            func_00282C88(state+0x10);
            elapsed=D_001B1688[0]-D_001B24A8[0];
            EF(state,0x24)=0.13333334f;
            if (func_00282C30(elapsed)>=11) {
                func_002E5DA0(0,0,object,0xD5);
                /* Last pickup-sound frame. */
                D_001B24A8_gp=D_001B1688[0];
            }
        } else {
            if (object[0x23]<255) object[0x23]++;
            if (func_002A0558(object,D_00189E20.moby)<=-0.2f) {
                object[0x20]=3;
                *(s16 *)(state+6)=60;
            }
        }
        break;
    }
    case 2: {
        f32 speed, f;
        func_002AA2E8((f32 *)(state+0x24),0.0f,0.006666667f);
        EF(object,0x18)+=EF(state,0x24);
        speed=func_00282DF0(state+0x10);
        func_002AA2E8(&speed,1.0666667f,0.006666667f);
        func_00282CF0(state+0x10,D_00189E20.pickup_target,object+0x10);
        if (EF(object,0x2C)==0.0f || func_00282DF0(state+0x10)<speed) { func_0029F338(object); break; }
        func_00282F20(state+0x10,state+0x10,speed);
        func_00282CC0(object+0x10,object+0x10,state+0x10);
        f=func_00282E48(object+0x10,D_00189E20.pickup_target)/(speed*30.0f+0.01f);
        if (f>1.0f) f=1.0f;
        else if (f<0.3f) f=0.3f;
        func_002AA2E8((f32 *)(object+0x2C),EF(*(u8 **)(object+0x24),0x24)*f,EF(*(u8 **)(object+0x24),0x24)*0.1f);
        break;
    }
    case 3: {
        f32 f;
        s32 item, phase, pulse;
        AmmoDef *entry, *defs;
        u8 *mapping;
        s32 *counts;
        phase = D_001B1688[0]%60;
        alpha=(f32)object[0x23];
        f=func_00283180((f32)phase*0.104719676f-3.1415901f);
        pulse=func_00283CF0(f*5.0f+5.0f)+10;
        func_002AA2E8(&alpha,(f32)pulse,4.0f);
        object[0x23]=func_00283CF0(alpha);
        if (func_002A0558(object,D_0018C0B0)>=0.0f) goto reactivate;
        item=EI(state,8);
        mapping=D_00139568;
        counts=D_00139688;
        defs=(AmmoDef *)D_00239BA0;
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

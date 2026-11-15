#include "names.h"
/* func_PAL_L12_0042DB94, the PAL copy of func_L12_004285A8: the same C, where rename func_002A96A0 becomes func_PAL_002AA108; rename func_002AB800 becomes func_PAL_002AC290; rename func_002B0A18 becomes func_PAL_002B1588; rename func_0032C700 becomes func_PAL_L00_003FB330; rename func_L12_00429610 becomes func_PAL_L12_0042EC00; rename func_L12_004293A0 becomes func_PAL_L12_0042E990; rename func_L00_0032A258 becomes func_PAL_L00_0032C328; rename func_L00_00326110 becomes func_PAL_L00_003281C0; rename func_002B0A68 becomes func_PAL_002B15D8; rename func_002AB8C0 becomes func_PAL_002AC3C0. */
#include "common.h"
#define F(p,o) (*(f32 *)((u8 *)(p)+(o)))
#define I(p,o) (*(s32 *)((u8 *)(p)+(o)))
#define H(p,o) (*(u16 *)((u8 *)(p)+(o)))
#define P(p,o) (*(u8 **)((u8 *)(p)+(o)))
extern void timed_explosion_debris_update(void *);
extern void func_PAL_002B15D8(void *,s32,void *,f32,f32,f32,f32,s32);
extern f32 coll_probe_ground_height_below(void *, s32, f32);
extern void *part_find_owned_effect_slot(void *, u32, s32);
extern f32 func_PAL_002AA108(void *, void *);
extern void func_PAL_002AC290(void *, void *), func_PAL_002AC3C0(void *, void *);
extern void moby_set_state(void *, s32, s32);
extern s32 PlayMobySound(s32, s32, void *);
extern s32 snd_play_from_global_bank(s32, u32, void *);
extern void snd_stop_voice(s32);
extern void func_PAL_002B1588(s32, s32);
extern s32 flag_set_first_pending(void *), math_fast_float_d(void *);
extern void *func_PAL_L00_003FB330(void *,s32,s32,s32,s32,s32,s32,s32,f32,f32,s32,s32,s32,s32);
extern void moby_compute_local_point(void *,void *,f32,f32,f32);
extern s32 coll_sweep_from_object(void *,f32,void *,s32,f32,f32,s32,s32,s32);
extern void func_PAL_L12_0042E990(void *), func_PAL_L12_0042EC00(void *,s32);
extern f32 vec_distance_xy(void *,void *);
extern void moby_set_flag_bit(void *,s32);
extern void func_PAL_L00_0032C328(void *,void *,void *,void *,s32,s32,s32,s32,s32,s32,void *);
extern void func_PAL_L00_003281C0(void *,s32,f32);
extern void FastVecAdd(void *,void *,void *), FastVecScale(void *,void *,f32), euler_rotation_basis(void *,void *);
extern u8 *CreateMoby(s32);
extern void moby_mark_spawned(void *);
extern u8 g_sound_state[], g_hero_position[];
extern u8 D_001A7A60[] __attribute__((sda));
typedef struct {
    u8 pad[0x160];
    f32 value160;
    s32 value164, value168, value16c;
    u8 gap[0x10];
    f32 value180;
    s32 value184, value188;
} L12EffectState;
extern L12EffectState D_L12_001B9CC0;
extern s32 D_L12_001B3DB4, D_001A903C;
extern u8 *D_L12_001B2EA0, *D_L12_001B2E9C;
extern u8 D_L12_001B2290 __attribute__((sda)), D_L12_001B2288 __attribute__((sda)), D_L12_001B2280 __attribute__((sda));
extern s32 D_L12_001B22D0 __attribute__((sda));
extern f32 D_L12_001B2260[4] __attribute__((sda));
extern s32 D_L12_001B2270[4] __attribute__((sda));
typedef struct { u8 pad[0x74]; u8 active; u8 gap[0x13]; u8 *owner; } L12Sound;
void func_PAL_L12_0042DB94(u8 *self) {
    typedef u32 Q __attribute__((mode(TI)));
    union { Q q; f32 f[4]; } posv, vecv;
#define pos posv.f
#define vec vecv.f
    u8 *st = P(self,0x68), *p;
    f32 damage;
    s32 count;
    switch (self[0x20]) {
    case 0:
        H(st,0x24)=100;
        F(st,0x20)=100.0f;
        F(st,0x70)=F(self,0x18)+50.0f;
        F(st,0x7c)=coll_probe_ground_height_below(self+0x10,0,0.5f);
        I(st,0x80)=-1;
        D_L12_001B3DB4=0;
        moby_set_state(self,1,-1);
        break;
    case 1: {
        s32 i;
        damage=func_PAL_002AA108(self,part_find_owned_effect_slot(self,0x230000,0));
        if (damage>0.0f) {
            st[0x57]=255; st[0x58]=128; st[0x59]=128;
            func_PAL_002AC290(self,st+0x50);
            F(st,0x20)-=damage;
        }
        if (F(st,0x20)<0.0f) {
            u8 *p;
            count=0;
            for (p=D_L12_001B2E9C;p<D_L12_001B2EA0;p+=0x100)
                if (*(s16 *)(p+0xaa)==*(s16 *)(self+0xaa) && p[0x20]<2 && p!=self) count++;
            if (!count && !D_001A7A60[9]) {
                D_001A7A60[9]=1;
                snd_play_from_global_bank(1,0,0);
                func_PAL_002B1588(0x1233,-1);
                D_001A903C=1;
            }
            i=D_L12_001B3DB4;
            if (i==0) moby_set_state(self,2,-1);
            else if (i==1) moby_set_state(self,7,-1);
            else if (i==2) moby_set_state(self,3,-1);
            else if (i==3) moby_set_state(self,4,-1);
            else moby_set_state(self,7,-1);
            D_L12_001B3DB4++;
        }
        self[0xa8]=255;
        break;
    }
    case 2: {
        s32 i;
        if (flag_set_first_pending(self)) {
            I(self,0x98)=0;
            func_PAL_L00_003FB330(self+0x10,1,20,20,20,20,20,0,2.5f,20.0f,1,1,1,0);
            PlayMobySound(0,0,self);
        }
        F(self,0xf0)+=F(st,0x64);
        F(st,0x64)+=0.00031415932f;
        if (F(self,0xf0)>0.7853982448577881f) {
            for (i=0;i<8;i++) {
                moby_compute_local_point(self,pos,0.0f,0.0f,(f32)i*2.033750057220459f);
                coll_sweep_from_object(self,1.2f,pos,0x30008,12.0f,1.0f,0,1,0);
            }
        }
        if (F(self,0xf0)>1.431170105934143f) {
            D_L12_001B9CC0.value180=0.2f; D_L12_001B9CC0.value188=75;
            D_L12_001B9CC0.value160=0.2f; D_L12_001B9CC0.value168=50; D_L12_001B9CC0.value16c=0;
            moby_set_state(self,8,-1);
        }
        break;
    }
    case 4:
        if (flag_set_first_pending(self)) {
            I(st,0x68)=217; I(st,0x6c)=0;
            D_L12_001B9CC0.value180=0.1f; D_L12_001B9CC0.value188=75;
            D_L12_001B9CC0.value160=0.2f; D_L12_001B9CC0.value168=50; D_L12_001B9CC0.value16c=0;
            self[0x30]=255;
        }
        func_PAL_L12_0042EC00(self,0);
        {
            L12Sound *slot=(L12Sound *)(g_sound_state+I(st,0x80)*0x70);
            if (slot->owner!=self || !slot->active) I(st,0x80)=PlayMobySound(3,4,self);
        }
        if (!math_fast_float_d(st+0x68) && I(st,0x68)<183) func_PAL_L12_0042E990(self);
        F(self,0x18)+=F(st,0x6c); F(st,0x6c)+=0.00032000002f;
        if (F(self,0x18)>F(st,0x70) && !self[0x31]) {
            if (I(st,0x80)!=-1) {
                {
                    L12Sound *slot=(L12Sound *)(g_sound_state+I(st,0x80)*0x70);
                    if (slot->owner==self && slot->active) snd_stop_voice(I(st,0x80));
                }
            }
            I(st,0x80)=-1;
            moby_set_state(self,5,-1);
        }
        break;
    case 3:
        if (flag_set_first_pending(self)) {
            I(st,0x68)=150; I(st,0x6c)=0;
            D_L12_001B9CC0.value180=0.1f; D_L12_001B9CC0.value188=75;
            D_L12_001B9CC0.value160=0.2f; D_L12_001B9CC0.value168=50; D_L12_001B9CC0.value16c=0;
        }
        if (I(st,0x68)) {
            {
                L12Sound *slot=(L12Sound *)(g_sound_state+I(st,0x80)*0x70);
                if (slot->owner!=self || !slot->active) I(st,0x80)=PlayMobySound(3,4,self);
            }
            func_PAL_L12_0042EC00(self,0);
            if (!math_fast_float_d(st+0x68) && I(st,0x68)<117) func_PAL_L12_0042E990(self);
            F(self,0x18)+=F(st,0x6c); F(st,0x6c)+=0.00032000002f;
        } else {
            if (I(st,0x80)!=-1) {
                {
                    L12Sound *slot=(L12Sound *)(g_sound_state+I(st,0x80)*0x70);
                    if (slot->owner==self && slot->active) snd_stop_voice(I(st,0x80));
                }
            }
            I(st,0x80)=-1;
            F(self,0x18)+=F(st,0x6c); F(st,0x6c)-=0.00392f;
            if (F(self,0x18)<F(st,0x7c)) moby_set_state(self,8,-1);
        }
        break;
    case 5: {
        u8 *p;
        p=D_L12_001B2E9C+(I(st,0x74)<<8);
        if (p && p[0x20]!=254 && p[0x20]!=253) {
            if (vec_distance_xy(p+0x10,g_hero_position)<45.0f && p[0x31]) {
                H(self,0x34)=(H(self,0x34)&0xffbe)|0x1000;
                I(self,0x98)=I(P(self,0x24),0x10);
                F(st,0x78)=F(p,0x18);
                qcopy(self+0x10,p+0x10);
                F(self,0x18)+=60.0f; F(self,0xf0)=3.1415927410125732f;
                F(st,0x6c)=-0.3f;
                moby_set_flag_bit(p,1);
                moby_set_state(self,6,-1);
                break;
            }
        }
        I(self,0x98)=0;
        H(self,0x34)=(H(self,0x34)|0x41)&0xefff;
        break;
    }
    case 6:
        vecv.q=0; vec[0]=F(self,0x10); vec[1]=F(self,0x14); vec[2]=F(st,0x78);
        posv.q=vecv.q;
        F(self,0x18)+=F(st,0x6c);
        {
            L12Sound *slot=(L12Sound *)(g_sound_state+I(st,0x80)*0x70);
            if (slot->owner!=self || !slot->active) I(st,0x80)=PlayMobySound(3,4,self);
        }
        if (F(self,0x18)<F(st,0x78)+6.44f && (H(self,0x7c)&4)) {
            if (I(st,0x80)!=-1) {
                {
                    L12Sound *slot=(L12Sound *)(g_sound_state+I(st,0x80)*0x70);
                    if (slot->owner==self && slot->active) snd_stop_voice(I(st,0x80));
                }
            }
            I(st,0x80)=-1;
            func_PAL_L00_003FB330(pos,1,25,20,20,20,45,1,1.0f,20.0f,1,1,0,0);
            func_PAL_L00_0032C328(self,&D_L12_001B2290,&D_L12_001B2288,&D_L12_001B2280,255,-1,D_L12_001B22D0,15,4,255,timed_explosion_debris_update);
            func_PAL_L00_003281C0(self,25,0.0f);
            moby_mark_spawned(self);
            return;
        }
        if (F(self,0x18)<F(st,0x78)+11.2f && (H(self,0x7c)&2)) {
            func_PAL_L00_003FB330(pos,1,25,20,20,20,45,1,2.0f,20.0f,1,1,0,0);
            func_PAL_L00_0032C328(self,&D_L12_001B2290,&D_L12_001B2288,&D_L12_001B2280,255,-1,D_L12_001B22D0,15,2,255,timed_explosion_debris_update);
            H(self,0x7c)=0x8004;
        } else if (F(self,0x18)<F(st,0x78)+16.27f && !H(self,0x7c)) {
            PlayMobySound(1,0,self);
            func_PAL_L00_003FB330(pos,1,25,20,20,20,45,1,3.0f,20.0f,1,1,0,0);
            func_PAL_L00_0032C328(self,&D_L12_001B2290,&D_L12_001B2288,&D_L12_001B2280,255,-1,D_L12_001B22D0,15,1,255,timed_explosion_debris_update);
            H(self,0x7c)=0x8006;
        } else {
        vecv.q=0; vec[2]=-12.27f;
        FastVecAdd(vec,self+0x10,vec);
        coll_sweep_from_object(self,4.0f,vec,0x10000,1000.0f,1.0f,0,1,0);
        }
        func_PAL_L12_0042EC00(self,1);
        break;
    case 7:
        if (flag_set_first_pending(self)) PlayMobySound(4,0,self);
        qcopy(pos,self+0x10);
        func_PAL_L00_003FB330(pos,1,25,20,20,20,45,1,4.0f,20.0f,1,1,0,0);
        func_PAL_L00_0032C328(self,&D_L12_001B2290,&D_L12_001B2288,&D_L12_001B2280,255,-1,D_L12_001B22D0,15,255,255,timed_explosion_debris_update);
        func_PAL_L00_003281C0(self,25,0.0f);
        moby_mark_spawned(self);
        return;
    case 8: {
        s32 i; u8 *p;
        for (i=0;i<3;i++) {
            p=CreateMoby(0x12e2-i);
            if (p) {
                FastVecScale(p+0x10,self+0xe0,D_L12_001B2260[i]);
                FastVecAdd(p+0x10,p+0x10,self+0x10);
                qcopy_nc(p+0xf0,self+0xf0);
                euler_rotation_basis(p+0xc0,self+0xf0);
                F(p,0x2c)=F(P(p,0x24),0x24)*(F(self,0x2c)/F(P(self,0x24),0x24));
                posv.q=0; pos[2]=0.16000001f;
                func_PAL_002B15D8(p,D_L12_001B2270[i],pos,6.0f,12.0f,6.0f,12.0f,255);
                func_PAL_L00_003FB330(p+0x10,0,25,20,20,20,45,1,1.0f,20.0f,1,1,0,0);
                moby_mark_spawned(p);
            }
        }
        func_PAL_L00_003281C0(self,25,0.0f);
        PlayMobySound(1,0,self);
        moby_mark_spawned(self);
        return;
    }
    }
    func_PAL_002AC3C0(self,st+0x50);
}

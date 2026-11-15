#include "include_asm.h"

#include "common.h"
#define B(p,o) (*(unsigned char *)((char *)(p)+(o)))
#define U(p,o) (*(unsigned short *)((char *)(p)+(o)))
#define W(p,o) (*(int *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
extern int D_L12_001A79F0 MACRO_ADDR;
extern int D_L12_001A8F00 MACRO_ADDR;
struct L12GlobalState {
    char pad0[0x24]; int f24;
    char pad28[0x40]; int f68; short f6C;
    char pad6E[4]; short f72;
};
extern struct L12GlobalState D_L12_001A63A8;
extern char *D_L12_001FEAC0[];
extern void func_PAL_L12_0041F568(void *);
extern int moby_dispatch_action_by_kind(void *,void *);
extern void moby_mark_spawned(void *);
extern void moby_set_state(void *,int,int);
extern int math_random_int_below(int);
extern void func_PAL_002A7E68(void *,int,int,int);
extern int enemy_claim_attack_turn(void *,int);
extern int func_PAL_002B5E30(void *,float);
extern s32 snd_resume_music_stream(void);
extern void tourist_increment_counters(int);
extern int path_find_next_stop_point(void *,int);
extern int func_PAL_L12_0041F710(void *);
extern float FastAddRotations(float,float);
extern int math_fast_float_d(void *);
extern int flag_set_first_pending(void *);
extern void func_PAL_L02_003CDF48(void *);
extern void enemy_tick_timers_age(void *);

void func_PAL_L12_0041F0F0(char *obj) {
    char *s=P(obj,0x68);
    int r;
    if(D_L12_001A79F0==13) {
        if(D_L12_001A8F00!=2) {
            U(obj,0x34)=(U(obj,0x34)&0xFFBE)|0x1000;
            W(obj,0x98)=W(P(obj,0x24),0x10);
        } else {
            W(obj,0x98)=0;
            U(obj,0x34)=(U(obj,0x34)|0x41)&0xEFFF;
        }
        return;
    }
    func_PAL_L12_0041F568(obj);
    switch(B(obj,0x95)) {
    case 1:
        { int flags=moby_dispatch_action_by_kind(obj,s+0x60);
        if(flags&1) {moby_mark_spawned(obj);return;}
        if(flags&2) moby_set_state(obj,4,0); }
        break;
    case 0: break;
    }
    switch(B(obj,0x20)) {
    case 2:
        if((B(obj,0x60)&2) && enemy_claim_attack_turn(obj,W(s,0x11C))) {
            moby_set_state(obj,8,-1);
            r=math_random_int_below(4);
            if(r==W(s,0x258)) {if(r!=3) r++; else r=0;}
            goto set_attack_animation;
        }
        break;
    case 8:
        func_PAL_002B5E30(obj,F(s,0x228));
        if(D_L12_001A63A8.f72==3 && D_L12_001A63A8.f6C<6000) {
            snd_resume_music_stream(); moby_set_state(obj,5,-1);
        }
        break;
    case 5:
        if(!D_L12_001A63A8.f68 && D_L12_001A63A8.f24==-1) {
            tourist_increment_counters(W(s,0x114));
            moby_set_state(obj,6,-1);
            if(B(obj,0x43)) func_PAL_002A7E68(obj,0,0,17);
            W(s,0x220)=path_find_next_stop_point(obj,W(s,0x224));
        } else if(B(obj,0x60)&2) {
            r=math_random_int_below(4);
            if(r==W(s,0x258)) {if(r!=3)r++;else r=0;}
            if(B(obj,0x43)!=r+1) func_PAL_002A7E68(obj,r+1,0,17);
            W(s,0x258)=r;
        }
        break;
    case 6:
        if(func_PAL_L12_0041F710(obj)) {
            if(W(s,0x220)==W(D_L12_001FEAC0[W(s,0x110)],0)-1) {
                moby_set_state(obj,3,-1);
                if(B(obj,0x43)!=9)func_PAL_002A7E68(obj,9,0,17);
            } else {
                moby_set_state(obj,7,-1);
                if(B(obj,0x43))func_PAL_002A7E68(obj,0,0,17);
                W(s,0x22C)=100;
                F(s,0x228)=FastAddRotations(F(obj,0xF8),3.141590118408203f);
            }
        }
        break;
    case 7:
        func_PAL_002B5E30(obj,F(s,0x228));
        if(math_fast_float_d(s+0x22C) && enemy_claim_attack_turn(obj,W(s,0x11C))) {
            moby_set_state(obj,8,-1);
            r=math_random_int_below(4);
            if(r==W(s,0x258)){if(r!=3)r++;else r=0;}
set_attack_animation:
            if(B(obj,0x43)!=r+1)func_PAL_002A7E68(obj,r+1,0,17);
            W(s,0x258)=r;
            W(s,0x11C)++;
        }
        break;
    case 3:
        if(B(obj,0x60)&2) {
            W(s,0x220)=0; W(s,0x224)=0; W(s,0x11C)=0;
            moby_set_state(obj,10,-1);
        }
        break;
    case 10:
        if(flag_set_first_pending(obj)) {
            W(s,0x25C)=21; W(obj,0x98)=0;
            U(obj,0x34)=(U(obj,0x34)|0x41)&0xEFFF;
        }
        if(math_fast_float_d(s+0x25C)) {
            moby_set_state(obj,1,-1);
            qcopy(obj+0x10,s+0x210);
        }
        func_PAL_L02_003CDF48(obj);
        break;
    case 1:
        W(obj,0x98)=0; U(obj,0x34)=(U(obj,0x34)|0x41)&0xEFFF;
        break;
    }
    enemy_tick_timers_age(obj);
}

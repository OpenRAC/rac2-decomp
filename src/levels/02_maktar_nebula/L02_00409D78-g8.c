#include "names.h"
/* Per-frame update of a Maktar Nebula object. State 0 sets up its timers; state 1 runs a
   series of tests on its state record and two global records, calling func_0028A180,
   func_00288E18 and func_L01_002EABA8 with the ids listed below.

   `base` is one local for the flags record and the first two blocks on D_0018C958. Holding
   several values gives it the references and live length that win $s0 over `s`; separate
   locals, or one local holding one address throughout, leave `s` in $s0. */
#include "common.h"
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define B(p,o) (*(u8 *)((char *)(p)+(o)))
extern char g_hero_position[], D_L02_0027FD48[];
typedef struct HintFlags { u8 pad[0x75]; u8 intro, timers; u8 pad77[5]; u8 hint; } HintFlags;
extern HintFlags D_001395B8;
typedef struct HintHistory {
    char pad0[0xf0];
    u16 countF0; char padF2[2]; u32 timeF4; u32 levelsF8;
    char padFC[0x24];
    u16 count120; char pad122[2]; u32 time124;
    char pad128[0x10]; u16 count138;
    char pad13A[0x18]; u16 count152; u32 time154; s32 flags158; u16 count15C;
    char pad15E[0x162]; s32 value2C0;
    char pad2C4[0x358]; u32 time61C;
} HintHistory;
typedef struct PlayerHistory {
    char pad0[0x54]; u16 count54;
    char pad56[0x9a]; u16 countF0; char padF2[2]; u32 timeF4;
    char padF8[0xb0]; u32 time1A8;
    char pad1AC[0x10]; u16 count1BC; char pad1BE[2]; u32 time1C0;
    char pad1C4[4]; u16 count1C8; char pad1CA[2]; u32 time1CC;
} PlayerHistory;
typedef struct HintState {
    char pad0[0x10];
    s32 value10;
    s32 value14;
    char pad18[0x8];
    s32 value20;
    s32 value24;
    s32 value28;
    s32 value2C;
    s32 value30;
    s32 value34;
    s32 value38;
    s32 value3C;
    char pad40[0x4];
    s32 value44;
    char pad48[0x4];
    s32 value4C;
    s32 value50;
    char pad54[0xc];
    s32 value60;
    s32 value64;
    s32 value68;
    s32 value6C;
    char pad70[0x8];
    s32 value78;
    s32 value7C;
    s32 value80;
    s32 value84;
    s32 value88;
    char pad8C[0x4];
    s32 value90;
    s32 value94;
    s32 value98;
    s32 value9C;
} HintState;
extern HintHistory g_subtitle_history;
extern PlayerHistory g_progress_statistics;
extern u32 g_current_map_index[] __attribute__((sda));
extern u32 D_001A7390[] __attribute__((sda));
extern u32 timer_sda SDATA(D_001A7390);
extern u8 g_item_owned_flags[] MACRO_ADDR;
extern int D_L02_001A8FF0 MACRO_ADDR;
extern int unlock_sda SDATA(D_L02_001A9010);
extern char *g_moby_l02_pool MACRO_ADDR;
extern char *objects_sda SDATA(D_L02_001B359C);
extern char *D_L02_001B368C MACRO_ADDR;
extern int g_frame_l02_counter MACRO_ADDR;
extern void moby_set_state(void *,int,int);
extern int level_get_table_entry_short(int),IsPointInCuboid(void *,int);
extern void hud_queue_hint_message(int,int),subtitle_request_voice_line(int,int),TriggerSubtitleInCuboid(int,int,int,int,int);
extern int arena_is_challenge_running(void *),math_fast_float_d(void *),chainblade_is_state_active(void *),flag_is_third_pending_set(void *);
extern void state_set_flag_one(void),hero_reset_position_and_direction(void *,void *,int,int);
/* Watches how the player is doing and shows a help hint or message when the player seems stuck and has not seen it recently. Update handler of moby class 3108. */
void hint_trigger_update(char *moby) {
    HintState *hints=*(HintState **)(moby+0x68);

    switch(B(moby,0x20)) { default: return; case 0: {
        B(moby,0x30)=255; hints->value60=0;hints->value64=0;hints->value50=0;hints->value90=0;
        hints->value94=1200;hints->value2C=180;hints->value98=600;
        moby_set_state(moby,1,-1);
    break; } case 1: {
        HintHistory *base;
        int mode=level_get_table_entry_short(2);
        if(mode==2 && level_get_table_entry_short(0)!=mode) {
            base=(HintHistory *)&D_001395B8;
            if(!(((HintFlags *)base)->intro&4) && IsPointInCuboid(g_hero_position,hints->value9C) && (D_001A7390[0]-g_progress_statistics.time1CC>432000 || !g_progress_statistics.count1C8)) {
                ((HintFlags *)base)->intro|=4;hud_queue_hint_message(0xa3c,0x93);
            }
        }
        base=&g_subtitle_history;
        if(base->countF0<65535) {
            if(g_item_owned_flags[0x2E]) base->countF0=65535;
            else if(IsPointInCuboid(g_hero_position,I(hints,0))) {
                if(base->countF0) {
                    if(timer_sda-base->timeF4>1080 || !base->timeF4)subtitle_request_voice_line(0x9bd,0x14);
                    else if(base->timeF4<timer_sda)base->timeF4=timer_sda;
                } else {
                    base->countF0++; if(base->timeF4<timer_sda)base->timeF4=timer_sda;
                    base->levelsF8=(base->levelsF8|(1<<g_current_map_index[0]))|0x80000000;
                }
            }
        }
        if(D_L02_001A8FF0 && !I(D_L02_0027FD48,0) && I(D_L02_0027FD48,0x24)==-1) {
            base=&g_subtitle_history;
            if(base->flags158>=0)subtitle_request_voice_line(0x9c5,0x1c);
            if(base->time154+base->count152>=D_001A7390[0]-2) {
                int count = base->count152+1;
                base->count152=count;
                if((count&0xffff)>=3600){subtitle_request_voice_line(0x9c5,0x1c);base->count152=0;}
            } else {if(base->time154<D_001A7390[0])base->time154=D_001A7390[0];base->count152=0;}
        }
        TriggerSubtitleInCuboid(0x9bf,0x16,2,hints->value10,hints->value14);
        if(g_subtitle_history.count120<65535) {
            if(g_progress_statistics.count54>=3 || IsPointInCuboid(g_hero_position,hints->value24))g_subtitle_history.count120=65535;
            else if(IsPointInCuboid(g_hero_position,hints->value20)) {
                if(timer_sda-g_subtitle_history.time124>1080 || !g_subtitle_history.time124)subtitle_request_voice_line(0x9c1,0x18);
                else if(g_subtitle_history.time124<timer_sda)g_subtitle_history.time124=timer_sda;
            }
        }
        TriggerSubtitleInCuboid(0x9c2,0x19,1,hints->value30,hints->value34);
        if(!g_subtitle_history.count138) {
            if(!hints->value3C && unlock_sda)hints->value3C=1;
            if(g_item_owned_flags[0x26])g_subtitle_history.count138=65535;
            if(hints->value3C && IsPointInCuboid(g_hero_position,hints->value38))subtitle_request_voice_line(0x9c3,0x1a);
        }
        TriggerSubtitleInCuboid(0x9c4,0x1b,0,hints->value44,-1);
        if(arena_is_challenge_running(g_moby_l02_pool+(hints->value68<<8))) {
            if(math_fast_float_d(&hints->value94) && (((D_001395B8.timers>>g_current_map_index[0])^1)&1)) {
                if(!g_progress_statistics.countF0 || D_001A7390[0]-g_progress_statistics.timeF4>42000)hud_queue_hint_message(0x9c9,0x20);
                D_001395B8.timers|=1<<g_current_map_index[0];
            }
            if(chainblade_is_state_active(g_moby_l02_pool+(hints->value6C<<8)) && (!g_progress_statistics.count1BC || D_001A7390[0]-g_progress_statistics.time1C0>72000) && math_fast_float_d(&hints->value98) && g_subtitle_history.value2C0>=0)subtitle_request_voice_line(0x9e3,0x3a);
        }
        if(D_L02_001A8FF0) {
            if(IsPointInCuboid(g_hero_position,hints->value4C) && !g_subtitle_history.count15C) {hud_queue_hint_message(0x9c6,0x1d);hints->value90=216000;}
            if(math_fast_float_d(&hints->value90)){hud_queue_hint_message(0x9c6,0x1d);hints->value90=216000;}
            if(D_001A7390[0]-g_progress_statistics.time1A8<60)hints->value90=216000;
        }
        if(IsPointInCuboid(g_hero_position,hints->value78) && (!g_progress_statistics.count1BC || D_001A7390[0]-g_progress_statistics.time1C0>72000) && !D_001395B8.hint && g_subtitle_history.value2C0>=0)subtitle_request_voice_line(0x9e3,0x3a);
        if(IsPointInCuboid(g_hero_position,hints->value38))D_001395B8.hint=1;
        if(g_item_owned_flags[0x2E])TriggerSubtitleInCuboid(0x9f1,0x48,2,hints->value7C,-1);
        if(g_frame_l02_counter<3 && g_item_owned_flags[0x26] && !flag_is_third_pending_set(objects_sda+(hints->value88<<8)) && IsPointInCuboid(g_hero_position,hints->value80)) {
            char *q;
            state_set_flag_one();q=D_L02_001B368C+(hints->value84<<7);hero_reset_position_and_direction(q+0x30,q+0x70,0,1);
        }
        if(IsPointInCuboid(g_hero_position,hints->value28)) {
            if(D_001A7390[0]-g_subtitle_history.time61C>120 || !g_subtitle_history.time61C)subtitle_request_voice_line(0xa2b,0x82);
            else if(g_subtitle_history.time61C<D_001A7390[0])g_subtitle_history.time61C=D_001A7390[0];
        }
    }
    }
}

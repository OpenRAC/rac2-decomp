#include "names.h"
/* Per-frame update of a Maktar Nebula object. State 0 sets up its timers; state 1 runs a
   series of tests on its state record and two global records, calling func_0028A180,
   func_PAL_00289730 and func_PAL_L01_002EBFB8 with the ids listed below.

   `base` is one local for the flags record and the first two blocks on D_0018C958. Holding
   several values gives it the references and live length that win $s0 over `s`; separate
   locals, or one local holding one address throughout, leave `s` in $s0.

   func_PAL_L02_0040E800, the PAL copy of func_L02_00409D78: the same C, where every frame
   count read from D_001A7390 is scaled to 50 Hz, ((s32)(x) * 5 + 2) / 6, including the
   values stored back, and the frame limits shrink to 5/6 (1080 to 900, 120 to 100, 1200 to
   1000, 180 to 150, 600 to 500, 3600 to 3000, 432000 to 360000, 42000 to 35000, 72000 to
   60000, 216000 to 180000; the 60 of the time1A8 test stays). Retail reads the counter through $gp (timer_sda) except in the
   countF0 and count152 blocks and the time1A8 test, which use the lui form: there it is the
   plain scalar D_001A7390, whose fixed-scalar MEM lets sched1 lift the countF0 == 0 arm's
   load above the countF0 store (an array element, D_001A7390[0], is in-struct and stays
   behind it). */
#include "common.h"
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define B(p,o) (*(u8 *)((char *)(p)+(o)))
extern char g_hero_position[], g_hero_state_ptr[];
typedef struct HintFlags { u8 pad[0x75]; u8 intro, timers; u8 pad77[5]; u8 hint; } HintFlags;
extern HintFlags g_game_flag_table;
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
extern u32 g_frame_counter MACRO_ADDR;
extern u32 timer_sda SDATA(D_001A7390);
extern u8 g_item_owned_flags[] MACRO_ADDR;
extern int g_tether_lock_active MACRO_ADDR;
extern int unlock_sda SDATA(D_L02_001A9010);
extern char *g_moby_l02_pool MACRO_ADDR;
extern char *objects_sda SDATA(D_L02_001B359C);
extern char *g_matrix_l02_record_table MACRO_ADDR;
extern int g_frame_l02_counter MACRO_ADDR;
extern void moby_set_state(void *,int,int);
extern int level_get_table_entry_short(int),IsPointInCuboid(void *,int);
extern void hud_queue_hint_message(int,int), func_PAL_L01_002EBFB8(int,int,int,int,int);
extern int func_PAL_00289730(int,int);
extern int arena_is_challenge_running(void *),math_fast_float_d(void *),chainblade_is_state_active(void *),flag_is_third_pending_set(void *);
extern void state_set_flag_one(void),hero_reset_position_and_direction_pal(void *,void *,int,int);
void func_PAL_L02_0040E800(char *e) {
    HintState *s=*(HintState **)(e+0x68);

    switch(B(e,0x20)) { default: return; case 0: {
        B(e,0x30)=255; s->value60=0;s->value64=0;s->value50=0;s->value90=0;
        s->value94=1000;s->value2C=150;s->value98=500;
        moby_set_state(e,1,-1);
    break; } case 1: {
        HintHistory *base;
        int mode=level_get_table_entry_short(2);
        if(mode==2 && level_get_table_entry_short(0)!=mode) {
            base=(HintHistory *)&g_game_flag_table;
            if(!(((HintFlags *)base)->intro&4) && IsPointInCuboid(g_hero_position,s->value9C) && ((((int)(timer_sda) * 5 + 2) / 6)-g_progress_statistics.time1CC>360000 || !g_progress_statistics.count1C8)) {
                ((HintFlags *)base)->intro|=4;hud_queue_hint_message(0xa3c,0x93);
            }
        }
        base=&g_subtitle_history;
        if(base->countF0<65535) {
            if(g_item_owned_flags[0x2E]) base->countF0=65535;
            else if(IsPointInCuboid(g_hero_position,I(s,0))) {
                if(base->countF0) {
                    if((((int)(g_frame_counter) * 5 + 2) / 6)-base->timeF4>900 || !base->timeF4)func_PAL_00289730(0x9bd,0x14);
                    else if(base->timeF4<(((int)(g_frame_counter) * 5 + 2) / 6))base->timeF4=(((int)(g_frame_counter) * 5 + 2) / 6);
                } else {
                    base->countF0++; if(base->timeF4<(((int)(g_frame_counter) * 5 + 2) / 6))base->timeF4=(((int)(g_frame_counter) * 5 + 2) / 6);
                    base->levelsF8=(base->levelsF8|(1<<g_current_map_index[0]))|0x80000000;
                }
            }
        }
        if(g_tether_lock_active && !I(g_hero_state_ptr,0) && I(g_hero_state_ptr,0x24)==-1) {
            base=&g_subtitle_history;
            if(base->flags158>=0)func_PAL_00289730(0x9c5,0x1c);
            if(base->time154+base->count152>=(((int)(g_frame_counter) * 5 + 2) / 6)-2) {
                int count = base->count152+1;
                base->count152=count;
                if((count&0xffff)>=3000){func_PAL_00289730(0x9c5,0x1c);base->count152=0;}
            } else {if(base->time154<(((int)(g_frame_counter) * 5 + 2) / 6))base->time154=(((int)(g_frame_counter) * 5 + 2) / 6);base->count152=0;}
        }
        func_PAL_L01_002EBFB8(0x9bf,0x16,2,s->value10,s->value14);
        if(g_subtitle_history.count120<65535) {
            if(g_progress_statistics.count54>=3 || IsPointInCuboid(g_hero_position,s->value24))g_subtitle_history.count120=65535;
            else if(IsPointInCuboid(g_hero_position,s->value20)) {
                if((((int)(timer_sda) * 5 + 2) / 6)-g_subtitle_history.time124>900 || !g_subtitle_history.time124)func_PAL_00289730(0x9c1,0x18);
                else if(g_subtitle_history.time124<(((int)(timer_sda) * 5 + 2) / 6))g_subtitle_history.time124=(((int)(timer_sda) * 5 + 2) / 6);
            }
        }
        func_PAL_L01_002EBFB8(0x9c2,0x19,1,s->value30,s->value34);
        if(!g_subtitle_history.count138) {
            if(!s->value3C && unlock_sda)s->value3C=1;
            if(g_item_owned_flags[0x26])g_subtitle_history.count138=65535;
            if(s->value3C && IsPointInCuboid(g_hero_position,s->value38))func_PAL_00289730(0x9c3,0x1a);
        }
        func_PAL_L01_002EBFB8(0x9c4,0x1b,0,s->value44,-1);
        if(arena_is_challenge_running(g_moby_l02_pool+(s->value68<<8))) {
            if(math_fast_float_d(&s->value94) && (((g_game_flag_table.timers>>g_current_map_index[0])^1)&1)) {
                if(!g_progress_statistics.countF0 || (((int)(timer_sda) * 5 + 2) / 6)-g_progress_statistics.timeF4>35000)hud_queue_hint_message(0x9c9,0x20);
                g_game_flag_table.timers|=1<<g_current_map_index[0];
            }
            if(chainblade_is_state_active(g_moby_l02_pool+(s->value6C<<8)) && (!g_progress_statistics.count1BC || (((int)(timer_sda) * 5 + 2) / 6)-g_progress_statistics.time1C0>60000) && math_fast_float_d(&s->value98) && g_subtitle_history.value2C0>=0)func_PAL_00289730(0x9e3,0x3a);
        }
        if(g_tether_lock_active) {
            if(IsPointInCuboid(g_hero_position,s->value4C) && !g_subtitle_history.count15C) {hud_queue_hint_message(0x9c6,0x1d);s->value90=180000;}
            if(math_fast_float_d(&s->value90)){hud_queue_hint_message(0x9c6,0x1d);s->value90=180000;}
            if((((int)(g_frame_counter) * 5 + 2) / 6)-g_progress_statistics.time1A8<60)s->value90=180000;
        }
        if(IsPointInCuboid(g_hero_position,s->value78) && (!g_progress_statistics.count1BC || (((int)(timer_sda) * 5 + 2) / 6)-g_progress_statistics.time1C0>60000) && !g_game_flag_table.hint && g_subtitle_history.value2C0>=0)func_PAL_00289730(0x9e3,0x3a);
        if(IsPointInCuboid(g_hero_position,s->value38))g_game_flag_table.hint=1;
        if(g_item_owned_flags[0x2E])func_PAL_L01_002EBFB8(0x9f1,0x48,2,s->value7C,-1);
        if(g_frame_l02_counter<3 && g_item_owned_flags[0x26] && !flag_is_third_pending_set(objects_sda+(s->value88<<8)) && IsPointInCuboid(g_hero_position,s->value80)) {
            char *q;
            state_set_flag_one();q=g_matrix_l02_record_table+(s->value84<<7);hero_reset_position_and_direction_pal(q+0x30,q+0x70,0,1);
        }
        if(IsPointInCuboid(g_hero_position,s->value28)) {
            if((((int)(timer_sda) * 5 + 2) / 6)-g_subtitle_history.time61C>100 || !g_subtitle_history.time61C)func_PAL_00289730(0xa2b,0x82);
            else if(g_subtitle_history.time61C<(((int)(timer_sda) * 5 + 2) / 6))g_subtitle_history.time61C=(((int)(timer_sda) * 5 + 2) / 6);
        }
    }
    }
}

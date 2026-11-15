#include "common.h"
extern int g_player_bolts[] __attribute__((sda));
extern int g_current_map_index MACRO_ADDR;
extern int D_L00_001A903C MACRO_ADDR;
extern unsigned char D_001A7A70[] __attribute__((sda));
extern unsigned int g_equipment_bits MACRO_ADDR;
typedef struct {
 char pad0[0x18c];
 unsigned short f18c;
 char pad18e[0x14e];
 unsigned short f2dc;
 char pad2de[0x142];
 unsigned short f420;
 char pad422[0x22];
 unsigned short f444;
 char pad446[0x172];
 unsigned short f5b8;
 char pad5ba[0xb2];
 unsigned short f66c;
} State_flags;
extern State_flags g_subtitle_history;
typedef struct {
 char pad0[0xfc]; unsigned short ffc; char padfe[0xbe];
 unsigned short f1bc;
 char pad1be[0x2];
 unsigned int f1c0;
 unsigned int f1c4;
 char pad1c8[0xc];
 unsigned short f1d4;
 char pad1d6[0xa];
 unsigned short f1e0;
 char pad1e2[0x2];
 unsigned int f1e4;
 unsigned int f1e8;
} State_stats;
extern State_stats g_progress_statistics;
extern unsigned short D_0018C84C[];
typedef struct {
 char pad0[0xfc]; unsigned short ffc; char padfe[0xbe];
 int f1bc;
 char pad1c0[0x3e];
 short f1fe;
 char pad200[0x20];
 short f220;
 char pad222[0x55e];
 int f780;
 int f784;
 int f788;
 int f78c;
 char pad790[0xab8];
 int f1248;
 char pad124c[0x208];
 short f1454;
 char pad1456[0xe3a];
 char * f2290;
 int f2294;
 char pad2298[0x4];
 int f229c;
 char pad22a0[0x25c];
 short f24fc;
} State_b;
extern State_b g_hero_state;

extern unsigned char D_001A7A80[] __attribute__((sda));
extern unsigned char g_item_owned_flags[] __attribute__((sda));


extern unsigned int D_001A7390 MACRO_ADDR;
extern int D_001B19C8 MACRO_ADDR;
typedef struct { char pad[0x100]; float x,y; } InputState;
extern InputState g_pad_state;
extern unsigned char g_item_slot_to_record[];
typedef struct { char pad[12]; int kind; char rest[0xd0]; } CountedEntry;
extern CountedEntry g_weapon_l00_table[];
extern int snd_play_from_global_bank(int,int,void *);
extern void value_set_entry_by_index(int,int);
extern float math_fabs(float);
extern int subtitle_request_voice_line(int,int);
extern int menu_update_entry_states(void);
extern void level_advance_checked_cursor(void);
void func_US2_L00_002A67F8(void)
{
    float v[4], mag;
    int sign,i,count;
    State_b *state;
    if((g_equipment_bits&0xbb50)==0xbb50 && !D_001A7A70[0xD]) {
        D_001A7A70[0xD]=1;
        (void)snd_play_from_global_bank(1,0,0);
        value_set_entry_by_index(0x1233,-1);
        D_L00_001A903C=1;
    }
    if(!g_subtitle_history.f18c && g_current_map_index<5 && !g_progress_statistics.f1d4 && g_hero_state.f2294!=1 && g_hero_state.f2294!=29) {
        qzero_nc(v);
        v[0]=g_pad_state.x;
        v[1]=g_pad_state.y;
        mag=math_fabs(v[0]);
        sign=v[0]<0.0f;
        state=&g_hero_state;
        switch(state->f780) {
        case 0:
            if(mag>0.8f) {
                state->f784=sign;
                state->f780=1;
                state->f788=0;
                state->f78c=0;
            }
            break;
        case 1:
            ++state->f788;
            if(mag<0.2f) {
                if(state->f788>=11) { state->f78c=0; state->f780=2; } else
                state->f780=0;
            } else if(state->f784!=sign) {
                if(state->f788>=11) { state->f78c=0; state->f780=3; } else
                state->f780=0;
            }
            break;
        case 2:
            ++state->f78c;
            if(mag>0.8f && sign!=state->f784) {
                state->f78c=0; state->f780=3;
                break;
            }
            if(g_hero_state.f78c>120) g_hero_state.f780=0;
            break;
        case 3:
            ++state->f78c;
            if(state->f78c>40 && state->f78c>state->f788+20) {
                if(g_progress_statistics.f1e0<65535) ++g_progress_statistics.f1e0;
                if(D_001A7390>g_progress_statistics.f1e4) g_progress_statistics.f1e4=D_001A7390;
                { unsigned int bit = 1u << g_current_map_index; g_progress_statistics.f1e8=(g_progress_statistics.f1e8|bit)|0x80000000u; }
                if(g_progress_statistics.f1e0>=2) subtitle_request_voice_line(0x9ca,0x21);
                state->f780=0;
            } else if(mag<0.2f || sign==g_hero_state.f784) g_hero_state.f780=0;
            break;
        }
    }
    if(D_001B19C8>0 && (D_001B19C8&127)==0) {
        if(!g_subtitle_history.f2dc && !D_0018C84C[0]) {
            unsigned char *map=g_item_slot_to_record;
            CountedEntry *entries=g_weapon_l00_table;
            count=0;
            for(i=0;i<56;i++) {
                if(!entries[*(unsigned char *)(i+(unsigned int)map)].kind && i!=10 && g_item_owned_flags[i]) count++;
            }
            if(count>=9) subtitle_request_voice_line(0x9e6,0x3d);
        }
        if(g_hero_state.f229c==17 && g_hero_state.f1bc>300 && !g_hero_state.f24fc && !g_subtitle_history.f5b8 && !g_hero_state.f1fe && *(int *)(*(char **)(g_hero_state.f2290+0x24)+0x134)) subtitle_request_voice_line(0xa23,0x7a);
        if(g_player_bolts[2]==80 && !g_subtitle_history.f66c) {
            if(!D_001A7A70[7]) {
                D_001A7A70[7]=1;
                (void)snd_play_from_global_bank(1,0,0);
                value_set_entry_by_index(0x1233,-1);
                D_L00_001A903C=1;
            }
            subtitle_request_voice_line(0xa32,0x89);
        }
        if(!g_subtitle_history.f420) {
            State_b *hero=&g_hero_state;
            unsigned char *items=D_001A7A80;
            if(items[hero->f1248]&32) subtitle_request_voice_line(0xa01,0x58);
        }
        if(g_current_map_index==5) g_subtitle_history.f444=65535;
    }
    if(!g_hero_state.f1454) g_hero_state.f220=0;
    else if(g_hero_state.f2294) ++g_hero_state.f220;
    if(g_hero_state.f220>90) {
        if(g_progress_statistics.f1bc<65535) ++g_progress_statistics.f1bc;
        if(D_001A7390>g_progress_statistics.f1c0) g_progress_statistics.f1c0=D_001A7390;
        { unsigned int bit = 1u << g_current_map_index; g_progress_statistics.f1c4=(g_progress_statistics.f1c4|bit)|0x80000000u; }
    }
    if(D_001B19C8<5 || (D_001B19C8&511)==21) menu_update_entry_states();
    level_advance_checked_cursor();
}

#include "include_asm.h"
#include "names.h"

extern char g_hero_position[];
typedef struct { char pad[0x2290]; unsigned char *moby; char pad2[0x238]; int count; } TutorialPlayer;
extern TutorialPlayer g_hero_state;
extern unsigned short g_subtitle_history[];
extern unsigned short D_0018C840[],D_0018C7B0[],D_0018C828[];
extern int D_001A7A00 __attribute__((sda)),D_001A7398 __attribute__((sda));
extern unsigned char *D_L00_001B1EA8 __attribute__((sda));
typedef struct {int active;char pad[0x20];int id;} TutorialPromptState;
extern TutorialPromptState D_L00_0027D848;
extern float fast_vec_dist(void *,void *);
extern int moby_is_state_one(void *);
extern void subtitle_request_voice_line(int,int);
extern int IsPointInCuboid(void *,int);
extern int moby_count_group_not_in_state(int,int),flag_is_byte_set(void),GetLocalizedString(int);
extern void settings_store_four(int,int,int,int),menu_set_size_limits(int,int),request_begin_slot(int,int,int,int,int);
extern int IsPointInCuboid(void *a0, int a1);
extern char g_hero_position[];

void func_US2_L00_003E8BE8(unsigned char *object) {
    int *state=*(int **)(object+0x68);
    unsigned char *other;
    switch(object[0x20]) {
    case 0:
        object[0x30]=255; object[0x20]=1; break;
    case 1:
        if(!g_subtitle_history[0x48/2]) {
            for(other=D_L00_001B1EA8;other;other=*(unsigned char **)(other+0x28)) {
                if(*(short *)(other+0xaa)==0x326 && fast_vec_dist(other+0x10,g_hero_position)<10.0f && !D_L00_0027D848.active && D_L00_0027D848.id==-1 && !g_subtitle_history[0x48/2] && !moby_is_state_one(other)) {
                    if(g_hero_state.count<D_001A7A00) subtitle_request_voice_line(0x9af,6);
                    else if(fast_vec_dist(other+0x10,g_hero_position)<1.0f && !g_subtitle_history[0x2e8/2]) subtitle_request_voice_line(0x9e7,0x3e);
                }
            }
        }
        if(IsPointInCuboid(g_hero_position,state[0]) && !D_L00_0027D848.active && D_L00_0027D848.id==-1 && !g_subtitle_history[0x18/2]) subtitle_request_voice_line(0x9ab,2);
        if(IsPointInCuboid(g_hero_position,state[1]) && !D_L00_0027D848.active && D_L00_0027D848.id==-1 && !g_subtitle_history[0x24/2] && !g_subtitle_history[0x30/2]) {
            if(D_001A7398==30) subtitle_request_voice_line(0x9ac,3);
            else if(D_001A7398==42) subtitle_request_voice_line(0x9ad,4);
        }
        if(IsPointInCuboid(g_hero_position,state[3]) && !D_L00_0027D848.active && D_L00_0027D848.id==-1 && !g_subtitle_history[0x54/2] && !g_subtitle_history[0x60/2] && !g_subtitle_history[0x6c/2] && moby_count_group_not_in_state(state[5],-1)) {
            if(D_001A7398==42) subtitle_request_voice_line(0x9b0,7);
            else if(D_0018C840[0]) subtitle_request_voice_line(0x9b1,8);
            else subtitle_request_voice_line(0x9b2,9);
        }
        if(IsPointInCuboid(g_hero_position,state[2]) && !D_L00_0027D848.active && D_L00_0027D848.id==-1) {
            if(flag_is_byte_set() && !g_subtitle_history[0x5a0/2]) {
                int first,second;
                g_subtitle_history[0x5a0/2]=1;
                first=GetLocalizedString(0x31B7);second=GetLocalizedString(0xa21);
                settings_store_four(first,0,second,1);menu_set_size_limits(0x40,0);request_begin_slot(4,1,10,0,0);
            } else if(!flag_is_byte_set() && !g_subtitle_history[0x3c/2] && !D_0018C7B0[0]) subtitle_request_voice_line(0x9ae,5);
        }
        if(IsPointInCuboid(g_hero_position,state[4]) && !D_0018C828[0] && !D_L00_0027D848.active && D_L00_0027D848.id==-1 && !g_subtitle_history[0x78/2]) subtitle_request_voice_line(0x9b3,10);
        break;
    }
    g_hero_state.moby[0x7e]|=1;
    { unsigned char *scan; for(scan=D_L00_001B1EA8;scan;scan=*(unsigned char **)(scan+0x28)) if(*(short *)(scan+0xaa)==0xac1) scan[0x7e]|=1; }
    if(IsPointInCuboid(g_hero_position,state[6]) || IsPointInCuboid(g_hero_position,state[7])) g_hero_position[0x2470]=1;
    else g_hero_position[0x2470]=0;
}


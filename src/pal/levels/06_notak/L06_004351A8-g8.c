#include "names.h"
/* func_PAL_L06_004351A8, the PAL copy of func_L06_00430C60: the same C, where the frame counter is
   scaled to 50 Hz at each use and the limits become 900, 200 and 270000. */
#include "common.h"
#define I(p,o) (*(int *)((p)+(o)))
#define B(p,o) (*(unsigned char *)((p)+(o)))
#define F(p,o) (*(float *)((p)+(o)))
extern char g_skill_point_state[], g_level_collected_flags[], g_progress_statistics[];
extern unsigned char g_moby_nibble_table[][0x400];
typedef struct { char pad[0x70]; unsigned int timestamp; } L06Session;

typedef struct { char padding[0x464]; unsigned char flag[0]; } L06TriggerFlags;

typedef struct {
    char pad0[0x80];
    float position[4];
    char pad90[0x2294-0x90];
    int mode2294;
    char pad2298[4];
    int mode229C;
    char pad22A0[0x24B4-0x22A0];
    int mode24B4;
} L06HeroState;
typedef struct {
    unsigned short count;
    unsigned short unknown;
    unsigned int timestamp;
    unsigned int levels;
} L06StatRow;
extern L06StatRow g_subtitle_history[];
extern L06HeroState g_hero_state;

extern unsigned char g_skill_point_zone_flag;
extern unsigned int g_frame_counter MACRO_ADDR;
extern int g_current_map_index MACRO_ADDR;
extern char *g_moby_l06_list_head;
extern int g_skill_point_zone_entered __attribute__((sda));
extern int IsPointInCuboid(char *, int);
extern int func_PAL_00289730(int, int);
extern float fast_vec_dist(void *, void *);
static __inline__ unsigned int L06StatLevelMask(unsigned int flags, int level)
{
    return flags & (1U << level);
}

void func_PAL_L06_004351A8(char *obj)
{
    char *s = *(char **)(obj+0x68), *p;
    unsigned short idx;
    int value;
    switch (B(obj,0x20)) {
    case 0:
        B(obj,0x30)=255; B(obj,0x20)=1;
        I(s,0x10)=0; I(s,0x2c)=0;
        break;
    case 1:
        if (IsPointInCuboid((char *)(&g_hero_state)->position,I(s,0)) && !I(g_skill_point_state,0) && I(g_skill_point_state,0x24)==-1 && !g_skill_point_zone_flag) {
            if (((s32)g_frame_counter * 5 + 2) / 6-g_subtitle_history[54].timestamp>900 || !g_subtitle_history[54].timestamp) func_PAL_00289730(0x9df,0x36);
            else if (g_subtitle_history[54].timestamp<((s32)g_frame_counter * 5 + 2) / 6) g_subtitle_history[54].timestamp=((s32)g_frame_counter * 5 + 2) / 6;
        }
        if (IsPointInCuboid((char *)(&g_hero_state)->position,I(s,0))) {
            idx=*(unsigned short *)(obj+0xb2);
            if (!((L06TriggerFlags *)g_level_collected_flags)->flag[(short)idx]) {
                value=g_moby_nibble_table[g_current_map_index][(short)idx>>1];
                if (!((idx&1) ? (value>>4)&7 : value&7)) {
                    if((&g_hero_state)->mode24B4==0x27) {
                        unsigned short slot;
                        I(s,0x30)=1;
                        slot=*(unsigned short *)(obj+0xb2);
                        if(slot&1) {
                            if(((g_moby_nibble_table[g_current_map_index][(short)slot>>1]>>4)&7)!=7) g_moby_nibble_table[g_current_map_index][(short)slot>>1]+=16;
                        } else {
                            if((g_moby_nibble_table[g_current_map_index][(short)slot>>1]&7)!=7) g_moby_nibble_table[g_current_map_index][(short)slot>>1]+=1;
                        }
                    }
                    if(!I(g_skill_point_state,0) && I(g_skill_point_state,0x24)==-1 && !I(s,0x30)) {
                        if(g_subtitle_history[55].count) {
                            if(((s32)g_frame_counter * 5 + 2) / 6-g_subtitle_history[55].timestamp>900 || !g_subtitle_history[55].timestamp) func_PAL_00289730(0x9e0,0x37);
                            else if(g_subtitle_history[55].timestamp<((s32)g_frame_counter * 5 + 2) / 6) g_subtitle_history[55].timestamp=((s32)g_frame_counter * 5 + 2) / 6;
                        } else {
                            g_subtitle_history[55].count++;
                            if(g_subtitle_history[55].timestamp<((s32)g_frame_counter * 5 + 2) / 6) g_subtitle_history[55].timestamp=((s32)g_frame_counter * 5 + 2) / 6;
                            g_subtitle_history[55].levels|=(1<<g_current_map_index);
                            g_subtitle_history[55].levels|=0x80000000u;
                        }
                    }
                }
            }
        }
        if(IsPointInCuboid((char *)(&g_hero_state)->position,I(s,8))) {
            if((&g_hero_state)->mode2294==0x37) I(s,0x2c)=1;
            if(I(s,0x2c) && (&g_hero_state)->mode2294!=0x37) {
                for(p=g_moby_l06_list_head;p;p=*(char **)(p+0x28)) {
                    if(*(short *)(p+0xaa)==0xb57 && fast_vec_dist(p+0x10,(char *)(&g_hero_state)->position)<3.0f && F(*(char **)(p+0x68),0)!=1.0f && I(s,0x2c)) {
                        I(s,0x2c)=0;
                        I(s,0x10)++;
                        if(I(s,0x10)==3 || I(s,0x10)==6) func_PAL_00289730(0x9e2,0x39);
                    }
                }
            }
        }
        if((&g_hero_state)->mode229C==0x12 && !I(g_skill_point_state,0) && I(g_skill_point_state,0x24)==-1 && IsPointInCuboid((char *)(&g_hero_state)->position,I(s,4))) {
            I(s,0x14)++;
            if(IsPointInCuboid((char *)(&g_hero_state)->position,I(s,4)) && I(s,0x14)>200 && !g_subtitle_history[50].count) func_PAL_00289730(0x9db,0x32);
        } else {
            if((&g_hero_state)->mode229C==0x11) g_subtitle_history[50].count=65535;
            else I(s,0x14)=0;
        }
        if(IsPointInCuboid((char *)(&g_hero_state)->position,I(s,0x18))) g_skill_point_zone_entered=1;
        if(IsPointInCuboid((char *)(&g_hero_state)->position,I(s,0x1c)) && !I(g_skill_point_state,0) && I(g_skill_point_state,0x24)==-1 && g_skill_point_zone_entered) {
            if(g_subtitle_history[56].count) func_PAL_00289730(0x9e1,0x38);
            else {
                g_subtitle_history[56].count++;
                if(g_subtitle_history[56].timestamp<((s32)g_frame_counter * 5 + 2) / 6) g_subtitle_history[56].timestamp=((s32)g_frame_counter * 5 + 2) / 6;
                g_subtitle_history[56].levels|=(1<<g_current_map_index);
                g_subtitle_history[56].levels|=0x80000000u;
            }
        }
        if(((s32)g_frame_counter * 5 + 2) / 6-((L06Session *)g_progress_statistics)->timestamp>270000 && IsPointInCuboid((char *)(&g_hero_state)->position,I(s,0x34)) && !L06StatLevelMask(g_subtitle_history[12].levels, g_current_map_index)) func_PAL_00289730(0x9b5,0xc);
        break;
    }
}

#include "common.h"
#define I(p,o) (*(int *)((p)+(o)))
#define B(p,o) (*(unsigned char *)((p)+(o)))
#define F(p,o) (*(float *)((p)+(o)))
extern char D_L06_00287AC8[], D_L06_0021E830[], g_progress_statistics[];
extern unsigned char D_0019B4A8[][0x400];
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
#define HERO (&D_00189E20)

extern unsigned char D_001A7B1F;
extern unsigned int D_001A7390;
extern int g_current_map_index;
extern char *D_L06_001B2828;
extern int D_L06_001B0BB8 __attribute__((sda));
extern unsigned int L06FrameSda SDATA(D_001A7390);
extern int L06LevelSda SDATA(D_001A79F0);
extern int IsPointInCuboid(char *, int);
extern int subtitle_request_voice_line(int, int);
extern float fast_vec_dist(void *, void *);
static __inline__ unsigned int L06StatLevelMask(unsigned int flags, int level)
{
    return flags & (1U << level);
}

/* Watches the hero inside the Notak trigger zones and awards the matching skill point or stat when its conditions are met. */
void skill_point_zone_update(char *obj)
{
    char *vars = *(char **)(obj+0x68), *other;
    unsigned short slotIndex;
    int slotBits;
    unsigned int now;
    switch (B(obj,0x20)) {
    case 0:
        B(obj,0x30)=255; B(obj,0x20)=1;
        I(vars,0x10)=0; I(vars,0x2c)=0;
        break;
    case 1:
        if (IsPointInCuboid((char *)HERO->position,I(vars,0)) && !I(D_L06_00287AC8,0) && I(D_L06_00287AC8,0x24)==-1 && !D_001A7B1F) {
            now=D_001A7390;
            if (now-g_subtitle_history[54].timestamp>1080 || !g_subtitle_history[54].timestamp) subtitle_request_voice_line(0x9df,0x36);
            else if (g_subtitle_history[54].timestamp<now) g_subtitle_history[54].timestamp=now;
        }
        if (IsPointInCuboid((char *)HERO->position,I(vars,0))) {
            slotIndex=*(unsigned short *)(obj+0xb2);
            if (!((L06TriggerFlags *)D_L06_0021E830)->flag[(short)slotIndex]) {
                slotBits=D_0019B4A8[g_current_map_index][(short)slotIndex>>1];
                if (!((slotIndex&1) ? (slotBits>>4)&7 : slotBits&7)) {
                    if(HERO->mode24B4==0x27) {
                        unsigned short slot;
                        I(vars,0x30)=1;
                        slot=*(unsigned short *)(obj+0xb2);
                        if(slot&1) {
                            if(((D_0019B4A8[L06LevelSda][(short)slot>>1]>>4)&7)!=7) D_0019B4A8[L06LevelSda][(short)slot>>1]+=16;
                        } else {
                            if((D_0019B4A8[L06LevelSda][(short)slot>>1]&7)!=7) D_0019B4A8[L06LevelSda][(short)slot>>1]+=1;
                        }
                    }
                    if(!I(D_L06_00287AC8,0) && I(D_L06_00287AC8,0x24)==-1 && !I(vars,0x30)) {
                        if(g_subtitle_history[55].count) {
                            now=L06FrameSda;
                            if(now-g_subtitle_history[55].timestamp>1080 || !g_subtitle_history[55].timestamp) subtitle_request_voice_line(0x9e0,0x37);
                            else if(g_subtitle_history[55].timestamp<now) g_subtitle_history[55].timestamp=now;
                        } else {
                            now=L06FrameSda;
                            g_subtitle_history[55].count++;
                            if(g_subtitle_history[55].timestamp<now) g_subtitle_history[55].timestamp=now;
                            g_subtitle_history[55].levels|=(1<<g_current_map_index);
                            g_subtitle_history[55].levels|=0x80000000u;
                        }
                    }
                }
            }
        }
        if(IsPointInCuboid((char *)HERO->position,I(vars,8))) {
            if(HERO->mode2294==0x37) I(vars,0x2c)=1;
            if(I(vars,0x2c) && HERO->mode2294!=0x37) {
                for(other=D_L06_001B2828;other;other=*(char **)(other+0x28)) {
                    if(*(short *)(other+0xaa)==0xb57 /* moby class 2903 */ && fast_vec_dist(other+0x10,(char *)HERO->position)<3.0f && F(*(char **)(other+0x68),0)!=1.0f && I(vars,0x2c)) {
                        I(vars,0x2c)=0;
                        I(vars,0x10)++;
                        if(I(vars,0x10)==3 || I(vars,0x10)==6) subtitle_request_voice_line(0x9e2,0x39);
                    }
                }
            }
        }
        if(HERO->mode229C==0x12 && !I(D_L06_00287AC8,0) && I(D_L06_00287AC8,0x24)==-1 && IsPointInCuboid((char *)HERO->position,I(vars,4))) {
            I(vars,0x14)++;
            if(IsPointInCuboid((char *)HERO->position,I(vars,4)) && I(vars,0x14)>240 && !g_subtitle_history[50].count) subtitle_request_voice_line(0x9db,0x32);
        } else {
            if(HERO->mode229C==0x11) g_subtitle_history[50].count=65535;
            else I(vars,0x14)=0;
        }
        if(IsPointInCuboid((char *)HERO->position,I(vars,0x18))) D_L06_001B0BB8=1;
        if(IsPointInCuboid((char *)HERO->position,I(vars,0x1c)) && !I(D_L06_00287AC8,0) && I(D_L06_00287AC8,0x24)==-1 && D_L06_001B0BB8) {
            if(g_subtitle_history[56].count) subtitle_request_voice_line(0x9e1,0x38);
            else {
                now=D_001A7390;
                g_subtitle_history[56].count++;
                if(g_subtitle_history[56].timestamp<now) g_subtitle_history[56].timestamp=now;
                g_subtitle_history[56].levels|=(1<<g_current_map_index);
                g_subtitle_history[56].levels|=0x80000000u;
            }
        }
        if(D_001A7390-((L06Session *)g_progress_statistics)->timestamp>324000 && IsPointInCuboid((char *)HERO->position,I(vars,0x34)) && !L06StatLevelMask(g_subtitle_history[12].levels, g_current_map_index)) subtitle_request_voice_line(0x9b5,0xc);
        break;
    }
}

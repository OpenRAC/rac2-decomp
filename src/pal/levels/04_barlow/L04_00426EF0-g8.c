#include "names.h"
/* func_PAL_L04_00426EF0, the PAL copy of func_L04_00422318: Barlow level object update (hint
 * triggers and the vendor checks). The same C, where the time is scaled to 50 Hz at each read and
 * the intervals become 250, 900, 200, 360000, 60000 and 90000. Each repeated division is merged
 * by cse but keeps its divide-by-zero trap, so the reads stay written out. Record 52 reads
 * maximum directly: an `old` local there moves the load ahead of the division.
 *
 * -G8 because the short globals below are gp-relative. -frac2-gcse-unsplit-edges keeps the
 * q->active read at the join after the call test: with split edges PRE inserts it on the
 * critical edge instead. Retail reads q->active three times; thread_jumps sends the nonzero
 * first test to a fresh label, so cse1 does not know the value at the D_L04_001B0D00 test,
 * and PRE turns the else-if read into a copy.
 * D_001A7AF8[0x27] is an unsplit address (MACRO_ADDR) because retail loads it with its own
 * lui at each of its two tests, while the neighbouring flags are gp-relative.
 * Statistic record 52 uses the same saturating update as the other hint records
 * (see func_00289178 and L12_00398E50-g8.c): the test folds, and the time is read again.
 */
#include "common.h"
typedef struct { unsigned short count, pad; unsigned int maximum; int levels; } Statistics;
typedef struct { unsigned char b[0x76]; } HintFlags;
typedef union { char b[0x2600]; int i[0x980]; char *p[0x980]; } HeroState;
extern HeroState g_hero_state;
extern char g_hero_position[];
extern Statistics g_subtitle_history[], g_progress_statistics[], D_0018C360[];
extern HintFlags D_001395B8;
extern char D_L04_00296748[];
extern unsigned char D_001A7AFA, D_001A7B05;
extern unsigned char g_item_owned_flags[] MACRO_ADDR;
extern int g_current_map_index;
extern unsigned int D_001A7390;
extern char *g_moby_l04_pool __attribute__((sda));
extern int D_L04_001B0CFC __attribute__((sda));
extern int D_L04_001B0D00 __attribute__((sda));

typedef struct { void *object; int state; float intensity; } HintFlare;
extern HintFlare g_lens_flare;
extern int IsPointInCuboid(void *,int);
extern int subtitle_request_voice_line(int,int);
extern void hud_queue_hint_message(int,int);
extern void lens_flare_reset_light_position(void *);
extern void sparkle_init_table(void *);
extern float screen_query_point_value(void *);
extern void gfx_l04_draw_lens_flare(void);
extern void gfx_add_draw_callback_first(void *,void *);
#define I(p,o) (*(int *)((p)+(o)))
#define U(p,o) (*(unsigned int *)((p)+(o)))
#define H(p,o) (*(unsigned short *)((p)+(o)))
#define B(p,o) (*(unsigned char *)((p)+(o)))
static __inline__ unsigned int BarlowLevelBit(int level) { return 1U << level; }

static __inline__ unsigned int BarlowHintPlayed(Statistics *hint, int level) { return hint->levels & BarlowLevelBit(level); }

typedef struct { char pad[0x14]; unsigned char active; } BarlowVendor;

void func_PAL_L04_00426EF0(char *m)
{
    char *p=*(char **)(m+0x68);
    BarlowVendor *q;
    unsigned int old;
    switch(B(m,0x20)) {
    case 0:
        B(m,0x30)=255; I(p,0x10)=2400; B(m,0x20)=1;
        lens_flare_reset_light_position(m);
        sparkle_init_table(m);
        break;
    case 1:
        if (IsPointInCuboid(g_hero_position,I(p,0)) && !I(D_L04_00296748,0) && I(D_L04_00296748,0x24)==-1 && !g_subtitle_history[2519].count && !D_0018C360[115].count) {
            subtitle_request_voice_line(0x9D7,0x2E); g_subtitle_history[46].count=65535;
        }
        if (IsPointInCuboid(g_hero_position,I(p,0xC)) && !I(D_L04_00296748,0) && I(D_L04_00296748,0x24)==-1 && !D_001A7AFA) {
            if (++I(p,0x10)>1200) { subtitle_request_voice_line(0x9DE,0x35); I(p,0x10)=0; }
        }
        if (IsPointInCuboid(g_hero_position,I(p,0x28)) && !I(D_L04_00296748,0) && I(D_L04_00296748,0x24)==-1 && D_001A7AFA && (I(g_hero_position,0x2214)==0 || I(g_hero_position,0x2214)==2) && (((D_001395B8.b[116]>>g_current_map_index)^1)&1)) {
            old=g_subtitle_history[35].maximum;
            if(((s32)(D_001A7390) * 5 + 2) / 6-old>250 || !old) subtitle_request_voice_line(0x9CC,0x23);
            else if(old<((s32)(D_001A7390) * 5 + 2) / 6) g_subtitle_history[35].maximum=((s32)(D_001A7390) * 5 + 2) / 6;
        }
        if(IsPointInCuboid(g_hero_position,I(p,0x40))) D_001395B8.b[116]|=BarlowLevelBit(g_current_map_index);
        if(IsPointInCuboid(g_hero_position,I(p,8)) && !I(D_L04_00296748,0) && I(D_L04_00296748,0x24)==-1 && !D_001A7B05 && g_subtitle_history[49].levels>=0) subtitle_request_voice_line(0x9DA,0x31);
        if(g_hero_state.i[2215]==18 && !I(D_L04_00296748,0) && I(D_L04_00296748,0x24)==-1 && IsPointInCuboid(g_hero_state.b+0x80,I(p,0x14))) {
                ++I(p,0x18);
                if(IsPointInCuboid(g_hero_state.b+0x80,I(p,0x14)) && I(p,0x18)>200) {
                    old=g_subtitle_history[50].maximum;
                    if(((s32)(D_001A7390) * 5 + 2) / 6-old>900 || !old) subtitle_request_voice_line(0x9DB,0x32);
                    else if(old<((s32)(D_001A7390) * 5 + 2) / 6) g_subtitle_history[50].maximum=((s32)(D_001A7390) * 5 + 2) / 6;
                }
        } else {
            if(g_hero_state.i[2215]==17) g_subtitle_history[50].count=65535;
            else I(p,0x18)=0;
        }
        if(!(D_001395B8.b[117]&16) && IsPointInCuboid(g_hero_position,I(p,0x44)) && *(short *)(g_hero_position+0x247C) && (((s32)(D_001A7390) * 5 + 2) / 6-g_progress_statistics[38].maximum>360000 || !g_progress_statistics[38].count)) {
            D_001395B8.b[117]|=16; hud_queue_hint_message(0xA3C,0x93);
        }
        if(IsPointInCuboid(g_hero_position,I(p,0x48)) && ((s32)(D_001A7390) * 5 + 2) / 6-g_progress_statistics[20].maximum>60000 && !(BarlowHintPlayed(&g_subtitle_history[32], g_current_map_index))) subtitle_request_voice_line(0x9C9,0x20);
        if(g_item_owned_flags[0x27] && IsPointInCuboid(g_hero_position,I(p,0x2C))) {
            old=g_subtitle_history[51].maximum;
            if(((s32)(D_001A7390) * 5 + 2) / 6-old>900 || !old) subtitle_request_voice_line(0x9DC,0x33);
            else if(old<((s32)(D_001A7390) * 5 + 2) / 6) g_subtitle_history[51].maximum=((s32)(D_001A7390) * 5 + 2) / 6;
            if(g_hero_state.i[1170]==39 && g_hero_state.p[0x1220/4]) {
                char *vehicle=*(char **)(g_hero_state.p[0x1220/4]+0x68);
                if(I(vehicle,0x54) && !I(vehicle,0x5C)) g_subtitle_history[51].count=65535;
            }
        }
        if(I(p,0x1C)!=-1 && g_item_owned_flags[0x27]) {
            q=*(BarlowVendor **)(g_moby_l04_pool+(I(p,0x1C)<<8)+0x68);
            if(IsPointInCuboid(g_hero_position,I(p,0x20))) {
                if(!q->active && !D_L04_001B0CFC) {
                    if(g_subtitle_history[52].count) {
                        if(((s32)(D_001A7390) * 5 + 2) / 6-g_subtitle_history[52].maximum>900 || !g_subtitle_history[52].maximum) subtitle_request_voice_line(0x9DD,0x34);
                        else if(g_subtitle_history[52].maximum<((s32)(D_001A7390) * 5 + 2) / 6) g_subtitle_history[52].maximum=((s32)(D_001A7390) * 5 + 2) / 6;
                        return;
                    }
                    if(g_subtitle_history[52].count<65535) g_subtitle_history[52].count++;
                    if(g_subtitle_history[52].maximum<((s32)(D_001A7390) * 5 + 2) / 6) g_subtitle_history[52].maximum=((s32)(D_001A7390) * 5 + 2) / 6;
                    g_subtitle_history[52].levels = (g_subtitle_history[52].levels | BarlowLevelBit(g_current_map_index)) | 0x80000000;
                    return;
                }
            }
            if(q->active && D_L04_001B0D00) { D_L04_001B0CFC=1; g_subtitle_history[52].count=65535; }
            else if(!q->active) D_L04_001B0D00=1;
        }
        if(IsPointInCuboid(g_hero_position,I(p,4)) && ((s32)(D_001A7390) * 5 + 2) / 6-g_progress_statistics[9].maximum>90000 && !(BarlowHintPlayed(&g_subtitle_history[12], g_current_map_index))) subtitle_request_voice_line(0x9B5,12);
        break;
    }
    g_lens_flare.intensity=screen_query_point_value(m);
    gfx_add_draw_callback_first(gfx_l04_draw_lens_flare,m);
}

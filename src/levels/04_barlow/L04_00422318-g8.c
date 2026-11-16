#include "names.h"
/* func_L04_00422318: Barlow level object update (hint triggers and the vendor checks).
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
extern Statistics g_subtitle_history[], g_progress_statistics[], g_statistics_table[];
extern HintFlags g_game_flag_table;
extern char g_barlow_hint_state[];
extern unsigned char g_barlow_hint_inside_flag, g_barlow_hint_seen_flag;
extern unsigned char g_item_owned_flags[] MACRO_ADDR;
extern int g_current_map_index;
extern unsigned int g_frame_counter;
extern char *g_moby_l04_pool __attribute__((sda));
extern int g_barlow_vendor_hint_done __attribute__((sda));
extern int g_barlow_vendor_seen_inactive __attribute__((sda));

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

/* Watches the player's progress on this level and shows the right hint messages, and also checks on the vendor. */
void barlow_hint_triggers_update(char *moby)
{
    char *vars=*(char **)(moby+0x68);
    BarlowVendor *vendor;
    unsigned int now, old;
    switch(B(moby,0x20)) {
    case 0:
        B(moby,0x30)=255; I(vars,0x10)=2400; B(moby,0x20)=1;
        lens_flare_reset_light_position(moby);
        sparkle_init_table(moby);
        break;
    case 1:
        if (IsPointInCuboid(g_hero_position,I(vars,0)) && !I(g_barlow_hint_state,0) && I(g_barlow_hint_state,0x24)==-1 && !g_subtitle_history[2519].count && !g_statistics_table[115].count) {
            subtitle_request_voice_line(0x9D7,0x2E); g_subtitle_history[46].count=65535;
        }
        if (IsPointInCuboid(g_hero_position,I(vars,0xC)) && !I(g_barlow_hint_state,0) && I(g_barlow_hint_state,0x24)==-1 && !g_barlow_hint_inside_flag) {
            if (++I(vars,0x10)>1200) { subtitle_request_voice_line(0x9DE,0x35); I(vars,0x10)=0; }
        }
        if (IsPointInCuboid(g_hero_position,I(vars,0x28)) && !I(g_barlow_hint_state,0) && I(g_barlow_hint_state,0x24)==-1 && g_barlow_hint_inside_flag && (I(g_hero_position,0x2214)==0 || I(g_hero_position,0x2214)==2) && (((g_game_flag_table.b[116]>>g_current_map_index)^1)&1)) {
            now=g_frame_counter; old=g_subtitle_history[35].maximum;
            if(now-old>300 || !old) subtitle_request_voice_line(0x9CC,0x23);
            else if(old<now) g_subtitle_history[35].maximum=now;
        }
        if(IsPointInCuboid(g_hero_position,I(vars,0x40))) g_game_flag_table.b[116]|=BarlowLevelBit(g_current_map_index);
        if(IsPointInCuboid(g_hero_position,I(vars,8)) && !I(g_barlow_hint_state,0) && I(g_barlow_hint_state,0x24)==-1 && !g_barlow_hint_seen_flag && g_subtitle_history[49].levels>=0) subtitle_request_voice_line(0x9DA,0x31);
        if(g_hero_state.i[2215]==18 && !I(g_barlow_hint_state,0) && I(g_barlow_hint_state,0x24)==-1 && IsPointInCuboid(g_hero_state.b+0x80,I(vars,0x14))) {
                ++I(vars,0x18);
                if(IsPointInCuboid(g_hero_state.b+0x80,I(vars,0x14)) && I(vars,0x18)>240) {
                    now=g_frame_counter; old=g_subtitle_history[50].maximum;
                    if(now-old>1080 || !old) subtitle_request_voice_line(0x9DB,0x32);
                    else if(old<now) g_subtitle_history[50].maximum=now;
                }
        } else {
            if(g_hero_state.i[2215]==17) g_subtitle_history[50].count=65535;
            else I(vars,0x18)=0;
        }
        if(!(g_game_flag_table.b[117]&16) && IsPointInCuboid(g_hero_position,I(vars,0x44)) && *(short *)(g_hero_position+0x247C) && (g_frame_counter-g_progress_statistics[38].maximum>432000 || !g_progress_statistics[38].count)) {
            g_game_flag_table.b[117]|=16; hud_queue_hint_message(0xA3C,0x93);
        }
        if(IsPointInCuboid(g_hero_position,I(vars,0x48)) && g_frame_counter-g_progress_statistics[20].maximum>72000 && !(BarlowHintPlayed(&g_subtitle_history[32], g_current_map_index))) subtitle_request_voice_line(0x9C9,0x20);
        if(g_item_owned_flags[0x27] && IsPointInCuboid(g_hero_position,I(vars,0x2C))) {
            now=g_frame_counter; old=g_subtitle_history[51].maximum;
            if(now-old>1080 || !old) subtitle_request_voice_line(0x9DC,0x33);
            else if(old<now) g_subtitle_history[51].maximum=now;
            if(g_hero_state.i[1170]==39 && g_hero_state.p[0x1220/4]) {
                char *vehicle=*(char **)(g_hero_state.p[0x1220/4]+0x68);
                if(I(vehicle,0x54) && !I(vehicle,0x5C)) g_subtitle_history[51].count=65535;
            }
        }
        if(I(vars,0x1C)!=-1 && g_item_owned_flags[0x27]) {
            vendor=*(BarlowVendor **)(g_moby_l04_pool+(I(vars,0x1C)<<8)+0x68);
            if(IsPointInCuboid(g_hero_position,I(vars,0x20))) {
                if(!vendor->active && !g_barlow_vendor_hint_done) {
                    if(g_subtitle_history[52].count) {
                        old=g_subtitle_history[52].maximum;
                        if(g_frame_counter-old>1080 || !old) subtitle_request_voice_line(0x9DD,0x34);
                        else if(old<g_frame_counter) g_subtitle_history[52].maximum=g_frame_counter;
                        return;
                    }
                    if(g_subtitle_history[52].count<65535) g_subtitle_history[52].count++;
                    if(g_subtitle_history[52].maximum<g_frame_counter) g_subtitle_history[52].maximum=g_frame_counter;
                    g_subtitle_history[52].levels = (g_subtitle_history[52].levels | BarlowLevelBit(g_current_map_index)) | 0x80000000;
                    return;
                }
            }
            if(vendor->active && g_barlow_vendor_seen_inactive) { g_barlow_vendor_hint_done=1; g_subtitle_history[52].count=65535; }
            else if(!vendor->active) g_barlow_vendor_seen_inactive=1;
        }
        if(IsPointInCuboid(g_hero_position,I(vars,4)) && g_frame_counter-g_progress_statistics[9].maximum>108000 && !(BarlowHintPlayed(&g_subtitle_history[12], g_current_map_index))) subtitle_request_voice_line(0x9B5,12);
        break;
    }
    g_lens_flare.intensity=screen_query_point_value(moby);
    gfx_add_draw_callback_first(gfx_l04_draw_lens_flare,moby);
}

#include "common.h"

/* func_PAL_L09_003E76B0, the PAL copy of func_L09_003E3288: the same C, where the clock is scaled
   for 50 Hz and its limit goes from 432000 to 360000 frames. In a unit of its own for the same
   reason as the template: retail'vars gcse ran on the unsplit flow graph here
   (-frac2-gcse-unsplit-edges, config/cflags.txt), so PRE puts the moby'vars state-byte load at the
   end of the 0xD0F test, where the class is still live in $v0, and the byte takes $v1. */

extern unsigned char g_game_flag_table[];
typedef struct { char pad[0x1bc]; unsigned short flag; char pad2[2]; unsigned int time; } DobboClock;
extern DobboClock g_progress_statistics;
typedef struct { char pad[0x2c0]; int first; char pad2[0x11c]; int second; char pad3[0x20]; int third; char pad4[0x24]; unsigned short flag; } DobboDialogue;
extern DobboDialogue g_subtitle_history;
typedef struct { char pad[0x80]; char position[0x10]; char pad2[0x128]; int field1b8; char pad3[0x20d8]; int field2294; } DobboPlayer;
extern DobboPlayer g_hero_state;
extern int g_subtitle_pending_word;
extern unsigned char g_item_enabled_flags[] __attribute__((sda)), g_status_flag_b[] __attribute__((sda));
extern short g_player_state_shorts[] __attribute__((sda));
extern unsigned int g_frame_counter MACRO_ADDR;
extern int g_release_busy_flag[] __attribute__((sda)), g_region_scan_flag[] __attribute__((sda));
typedef struct {
    int region[4];
    int entered;
    int hint14;
    int hint18;
    int hint1c;
    char pad20[0xc];
    int f2c;
    char pad30[0x28];
    int scan;
    int count;
} RegionState;
typedef struct { char pad[0x3d6]; short busy; } ScanVars;
typedef struct {
    char pad00[0x20];
    unsigned char state;
    char pad21[0xf];
    unsigned char alpha;
    char pad31[0x37];
    ScanVars *vars;
    char pad6c[0x3e];
    short oClass;
    char padac[0x54];
} ScanMoby;
extern ScanMoby *g_moby_record_table MACRO_ADDR, *g_moby_record_table_end MACRO_ADDR;
extern int IsPointInCuboid(void *, int);
extern int subtitle_request_voice_line_pal(int, int);
extern void value_set_entry_by_index_pal(int, int);
extern int snd_play_from_global_bank(int, int, void *);

/* Scans the nearby objects of this region and reacts to the ones it finds (PAL: 50 Hz clock). */
void region_scan_objects_pal(unsigned char *moby)
{
    RegionState *vars = *(RegionState **)(moby + 0x68);
    ScanMoby *scan_moby;
    int i;

    if (!moby[0x20]) {
        moby[0x20] = 1;
        moby[0x30] = 255;
        vars->entered = 0;
        if (g_game_flag_table[0x7a] >= 126)
            g_game_flag_table[0x7a] = 125;
        if (g_game_flag_table[0x79] >= 126)
            g_game_flag_table[0x79] = 125;
        vars->f2c = 0;
    }
    if (moby[0x20] != 1)
        return;

    /* Scan 40 mobys a frame, counting those of five classes whose state byte is non-negative
       (a busy 0xD30 or an 0xD0F in state 5 is skipped). A full pass that counts none sets the
       done flag once and makes the two calls. The regions below are point-in-cuboid tests on the
       player'vars position that play hint lines. */
    if (g_release_busy_flag[0] && !g_item_enabled_flags[12]) {
        for (i = 0; i < 40; i++) {
            scan_moby = &g_moby_record_table[vars->scan];
            if (scan_moby->oClass == 0xd0f || scan_moby->oClass == 0xd57 || scan_moby->oClass == 0xd30 ||
                scan_moby->oClass == 0xcbc || scan_moby->oClass == 0xd90) {
                if (scan_moby->oClass == 0xd30 && scan_moby->vars->busy) {
                    vars->scan++;
                    continue;
                }
                if (scan_moby->oClass == 0xd0f) {
                    int state = scan_moby->state;
                    if (state == 5) {
                        vars->scan++;
                        continue;
                    }
                }
                {
                    int state = scan_moby->state;
                    if ((signed char)state >= 0)
                        vars->count++;
                }
            }
            vars->scan++;
            if (&g_moby_record_table[vars->scan] >= g_moby_record_table_end) {
                if (!vars->count && !g_item_enabled_flags[12]) {
                    g_item_enabled_flags[12] = 1;
                    snd_play_from_global_bank(1, 0, 0);
                    value_set_entry_by_index_pal(0x1233, -1);
                    g_region_scan_flag[0] = 1;
                }
                vars->scan = 0;
                vars->count = 0;
            }
        }
    }

    if (!g_subtitle_history.flag && g_subtitle_pending_word < 0 && !g_status_flag_b[5]) {
        if (IsPointInCuboid(g_hero_state.position, vars->region[0]))
            subtitle_request_voice_line_pal(0xa02, 0x59);
    }
    if (IsPointInCuboid(g_hero_state.position, vars->region[1]))
        vars->entered = 1;
    if (g_hero_state.field2294 == 0x39 && !g_hero_state.field1b8 && vars->entered)
        g_game_flag_table[0x7a]++;
    if (g_player_state_shorts[4] <= 0 && IsPointInCuboid(g_hero_state.position, vars->region[1])) {
        if (g_game_flag_table[0x7a] % 5 == 4 && !vars->hint1c && g_hero_state.field2294 != 0x39) {
            if (g_subtitle_history.second >= 0)
                subtitle_request_voice_line_pal(0x9fb, 0x52);
            vars->hint1c = 1;
            g_game_flag_table[0x7a]++;
        }
    }
    if (IsPointInCuboid(g_hero_state.position, vars->region[2])) {
        if (g_hero_state.field2294 == 0x39 && !g_hero_state.field1b8)
            g_game_flag_table[0x79]++;
    }
    if (!g_status_flag_b[7] && IsPointInCuboid(g_hero_state.position, vars->region[2])) {
        if (g_game_flag_table[0x79] % 5 == 4 && !vars->hint18 && g_hero_state.field2294 != 0x39) {
            if (g_subtitle_history.third >= 0)
                subtitle_request_voice_line_pal(0x9fe, 0x55);
            vars->hint18 = 1;
            g_game_flag_table[0x79]++;
        }
    }
    if (IsPointInCuboid(g_hero_state.position, vars->region[3])) {
        if ((!g_progress_statistics.flag || (((int)(g_frame_counter) * 5 + 2) / 6) - g_progress_statistics.time > 360000) &&
            g_game_flag_table[0x7d] < 3 && !vars->hint14) {
            if (g_subtitle_history.first >= 0)
                subtitle_request_voice_line_pal(0x9e3, 0x3a);
            g_game_flag_table[0x7d]++;
            vars->hint14 = 1;
        }
    }
}

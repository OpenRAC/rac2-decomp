#include "common.h"

typedef struct {
    int state, timer, width, height, y, x, drawWidth, drawHeight;
    int entry, pending, selection, unk2C, enabled, wait;
    short flag38, flag3A;
    int countdown, offset, shake, duration;
} SubtitleStateUpdate;

typedef struct {
    int text, unk04, id, unk0C;
} SubtitleEntryUpdate;

typedef struct {
    unsigned short count, pad;
    unsigned int time, levels;
} SubtitleHistory;

typedef struct {
    char pad00[0x24];
    int key, selection;
    char pad2C[0x3C];
    int active;
    short id;
    char pad6E[4];
    short state;
} SubtitleOwnerUpdate;

/* GCC's zero-length tail describes the voice table following the TOC header. */
typedef struct {
    char pad[0x2A20];
    int audio[0];
} SubtitleDiscToc;

extern SubtitleStateUpdate g_subtitle_state;
extern SubtitleEntryUpdate *g_subtitle_entries[] __attribute__((sda));
extern SubtitleHistory g_subtitle_history[];
extern SubtitleOwnerUpdate g_music_state;
extern SubtitleDiscToc g_copy_setup_data;
extern unsigned short D_001A7B94 MACRO_ADDR;
extern int g_current_map_index[] __attribute__((sda));
extern int g_current_game_mode[] __attribute__((sda));
extern unsigned int D_00138320;
extern unsigned int D_00138324;
extern unsigned int D_001A7390[] __attribute__((sda));

extern int math_fast_float_d(int *);
extern void subtitle_init_state(void);
extern void text_mark_entry_recent(int);
extern void ForceClaimNotice(int, int, int);
extern void snd_resume_music_stream(void);
extern int Help_FindIndex(int);

#define SUBTITLES_OPTION (*(unsigned char *)&D_001A7B94)
#define SUBTITLE_VOICE_ID (D_001B1840[0][D_00254E78.entry].id)
#define HAS_AUDIO(id) (D_0014B540.audio[id])
#define RECORD_SUBTITLE_TIME() { \
    if (D_0018C958[D_00254E78.selection].count < 65535) \
        D_0018C958[D_00254E78.selection].count++; \
    if (D_0018C958[D_00254E78.selection].time < D_001A7390[0]) \
        D_0018C958[D_00254E78.selection].time = D_001A7390[0]; \
}
#define RECORD_SUBTITLE_LEVEL() \
    (D_0018C958[D_00254E78.selection].levels = \
        (D_0018C958[D_00254E78.selection].levels | (1u << D_001A79F0[0])) | 0x80000000u)

/* Per-frame update of the subtitle box. It steps through waiting, fading in, showing and fading out, and records which lines the player has seen. */
void subtitle_update_state_machine(void)
{
    if (!g_subtitle_state.enabled) {
        if (g_current_map_index[0] >= 0) {
            g_subtitle_state.enabled = 1;
            g_subtitle_state.wait = 120;
        } else {
            if (!g_subtitle_state.wait && (D_00138320 & 0xF000))
                g_subtitle_state.wait = 1;
            if (g_subtitle_state.wait) {
                g_subtitle_state.wait++;
                if (g_subtitle_state.wait >= 120)
                    g_subtitle_state.enabled = 1;
            }
        }
    }
    if ((g_current_game_mode[0] != 0 && g_current_game_mode[0] != 7) || !g_subtitle_state.enabled) {
        g_subtitle_state.pending = -1;
        g_subtitle_state.state = 0;
        g_subtitle_state.timer = 0;
        return;
    }
    g_subtitle_state.timer++;
    if (!SUBTITLES_OPTION) {
        if (SUBTITLE_VOICE_ID == g_music_state.id - 6000 &&
            (unsigned short)(g_music_state.state - 6) > 1)
            g_music_state.state = 5;
    }
    switch (g_subtitle_state.state) {
    case 8:
        if (g_subtitle_state.flag38)
            return;
        if (g_subtitle_state.entry >= 0) {
            if (!g_subtitle_state.flag3A) {
                if (!math_fast_float_d(&g_subtitle_state.countdown))
                    return;
                subtitle_init_state();
                g_subtitle_state.flag3A++;
                return;
            }
            if (g_subtitle_history[g_subtitle_state.selection].count < 65535)
                g_subtitle_history[g_subtitle_state.selection].count++;
        }
        if (g_subtitle_history[g_subtitle_state.selection].time < D_001A7390[0])
            g_subtitle_history[g_subtitle_state.selection].time = D_001A7390[0];
        g_subtitle_state.entry = -1;
        g_subtitle_state.state = 0;
        g_subtitle_state.flag3A = 0;
        RECORD_SUBTITLE_LEVEL();
        break;
    case 0:
        if (g_subtitle_state.pending < 0)
            return;
        g_subtitle_state.entry = Help_FindIndex(g_subtitle_state.pending);
        text_mark_entry_recent(g_subtitle_state.pending);
        g_subtitle_state.pending = -1;
        if (g_subtitle_state.entry >= 0)
            subtitle_init_state();
        break;
    case 1:
    case 2:
        if (SUBTITLES_OPTION) {
            if (SUBTITLE_VOICE_ID != -1 && HAS_AUDIO(SUBTITLE_VOICE_ID) &&
                !g_music_state.active && g_music_state.key == -1) {
                g_music_state.selection = 0;
                g_music_state.key = g_subtitle_state.selection + 6000;
            }
        }
        if (D_00138324 & 16) {
            RECORD_SUBTITLE_TIME();
            g_subtitle_state.state = 7;
            g_subtitle_state.timer = 0;
            RECORD_SUBTITLE_LEVEL();
            return;
        }
        if (g_subtitle_state.timer <= 0)
            return;
        if ((g_music_state.state == 3 && g_music_state.id >= 6000) ||
            SUBTITLE_VOICE_ID == -1 || !HAS_AUDIO(SUBTITLE_VOICE_ID) ||
            SUBTITLE_VOICE_ID != g_music_state.id - 6000) {
            g_subtitle_state.state = 3;
            g_subtitle_state.timer = 0;
        }
        break;
    case 3:
        ForceClaimNotice(5, 0, 1);
        if (D_00138324 & 16) {
            RECORD_SUBTITLE_TIME();
            g_subtitle_state.state = 7;
            g_subtitle_state.timer = 0;
            RECORD_SUBTITLE_LEVEL();
            return;
        }
        if (g_subtitle_state.timer >= 8) {
            g_subtitle_state.timer = 0;
            g_subtitle_state.state = 4;
        }
        break;
    case 4: {
        int subtitles;
        ForceClaimNotice(5, 0, 1);
        if (D_00138324 & 16) {
            RECORD_SUBTITLE_TIME();
            RECORD_SUBTITLE_LEVEL();
            g_subtitle_state.state = 6;
            g_subtitle_state.timer = 4 - g_subtitle_state.timer;
            return;
        }
        if (g_subtitle_state.timer < 4)
            return;
        subtitles = SUBTITLES_OPTION;
        if (SUBTITLE_VOICE_ID != -1 && HAS_AUDIO(SUBTITLE_VOICE_ID) &&
            SUBTITLE_VOICE_ID != g_music_state.id - 6000 && subtitles)
            goto next_phase;
        if (SUBTITLE_VOICE_ID != -1 && HAS_AUDIO(SUBTITLE_VOICE_ID) &&
            (g_music_state.state != 3 || g_music_state.id < 6000) && subtitles)
            return;
        if (subtitles && SUBTITLE_VOICE_ID == g_music_state.id - 6000)
            snd_resume_music_stream();
        g_subtitle_state.state = 5;
        g_subtitle_state.timer = 0;
        break;
    next_phase:
        g_subtitle_state.timer = 0;
        g_subtitle_state.state = 5;
        break;
    }
    case 5:
        ForceClaimNotice(5, 0, 1);
        if (g_subtitle_state.timer >= g_subtitle_state.duration) {
            /* Retail reloads this option again below, without an intervening store. */
            if (SUBTITLE_VOICE_ID == -1 || !HAS_AUDIO(SUBTITLE_VOICE_ID) ||
                !*(volatile unsigned char *)&D_001A7B94)
                goto close;
        }
        if (*(volatile unsigned char *)&D_001A7B94) {
            if (SUBTITLE_VOICE_ID != -1 && HAS_AUDIO(SUBTITLE_VOICE_ID) &&
                SUBTITLE_VOICE_ID != g_music_state.id - 6000)
                goto close;
        }
        if (!(D_00138324 & 16))
            return;
    close:
        RECORD_SUBTITLE_TIME();
        g_subtitle_state.state = 6;
        g_subtitle_state.timer = 0;
        RECORD_SUBTITLE_LEVEL();
        break;
    case 6:
        if (D_001A7B94 && g_subtitle_state.timer < 4 && !(D_00138324 & 16))
            return;
        g_subtitle_state.state = 7;
        g_subtitle_state.timer = 0;
        break;
    case 7:
        ForceClaimNotice(5, 0, 1);
        if (SUBTITLE_VOICE_ID == g_music_state.id - 6000 &&
            (unsigned short)(g_music_state.state - 6) > 1)
            g_music_state.state = 5;
        if (g_subtitle_state.timer < 8)
            return;
        if (g_subtitle_state.flag38) {
            g_subtitle_state.state = 8;
        } else {
            g_subtitle_state.state = 0;
            g_subtitle_state.entry = -1;
        }
        g_subtitle_state.timer = 0;
        break;
    }
}

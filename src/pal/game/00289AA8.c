#include "include_asm.h"
#include "common.h"

/*
 * func_PAL_00289AA8, the PAL copy of func_00289178: the same C, where the
 * 120-frame start-up wait becomes 100, and the subtitle duration and the
 * recorded play times are scaled to 50 Hz. The subtitle setting is read
 * from the settings block D_001A7B90 at +4, as the subtitle renderer
 * (00288D88-render.c) reads it.
 */

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
/* The settings block func_00298E08 copies. Retail reads its subtitle halfword and byte at +4
 * at an offset from the block (lui and a tied %lo load, never moved into a delay slot). */
extern unsigned char g_is_pal_video[] __attribute__((sda));
extern int g_current_map_index[] __attribute__((sda));
extern int g_current_game_mode[] __attribute__((sda));
extern unsigned int g_pad_pressed_flags;
extern unsigned int g_pad_held_flags;
extern unsigned int g_frame_counter[] __attribute__((sda));

extern int math_fast_float_d(int *);
extern void subtitle_init_state(void);
extern void text_mark_entry_recent(int);
extern int ForceClaimNotice(int, int, int);
extern s32 snd_resume_music_stream(void);
extern int Help_FindIndex(int);

#define RECORD_SUBTITLE_TIME() { \
    if (D_0018C958[D_00254E78.selection].count < 65535) \
        D_0018C958[D_00254E78.selection].count++; \
    if (((s32)(D_001A7390[0]) * 5 + 2) / 6 > D_0018C958[D_00254E78.selection].time) \
        D_0018C958[D_00254E78.selection].time = ((s32)(D_001A7390[0]) * 5 + 2) / 6; \
}
#define RECORD_SUBTITLE_LEVEL() \
    (D_0018C958[D_00254E78.selection].levels = \
        (D_0018C958[D_00254E78.selection].levels | (1u << D_001A79F0[0])) | 0x80000000u)

void func_PAL_00289AA8(void)
{
    if (!g_subtitle_state.enabled) {
        if (g_current_map_index[0] >= 0) {
            g_subtitle_state.enabled = 1;
            g_subtitle_state.wait = 100;
        } else {
            if (!g_subtitle_state.wait && (g_pad_pressed_flags & 0xF000))
                g_subtitle_state.wait = 1;
            if (g_subtitle_state.wait) {
                g_subtitle_state.wait++;
                if (g_subtitle_state.wait >= 100)
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
    if (!g_is_pal_video[4]) {
        if (g_subtitle_entries[0][g_subtitle_state.entry].id == g_music_state.id - 6000 &&
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
        if (((s32)(g_frame_counter[0]) * 5 + 2) / 6 > g_subtitle_history[g_subtitle_state.selection].time)
            g_subtitle_history[g_subtitle_state.selection].time = ((s32)(g_frame_counter[0]) * 5 + 2) / 6;
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
        if (g_is_pal_video[4]) {
            if (g_subtitle_entries[0][g_subtitle_state.entry].id != -1 && g_copy_setup_data.audio[g_subtitle_entries[0][g_subtitle_state.entry].id] &&
                !g_music_state.active && g_music_state.key == -1) {
                g_music_state.selection = 0;
                g_music_state.key = g_subtitle_state.selection + 6000;
            }
        }
        if (g_pad_held_flags & 16) {
            RECORD_SUBTITLE_TIME();
            g_subtitle_state.state = 7;
            g_subtitle_state.timer = 0;
            RECORD_SUBTITLE_LEVEL();
            return;
        }
        if (g_subtitle_state.timer <= 0)
            return;
        if ((g_music_state.state == 3 && g_music_state.id >= 6000) ||
            g_subtitle_entries[0][g_subtitle_state.entry].id == -1 || !g_copy_setup_data.audio[g_subtitle_entries[0][g_subtitle_state.entry].id] ||
            g_subtitle_entries[0][g_subtitle_state.entry].id != g_music_state.id - 6000) {
            g_subtitle_state.state = 3;
            g_subtitle_state.timer = 0;
        }
        break;
    case 3:
        ForceClaimNotice(5, 0, 1);
        if (g_pad_held_flags & 16) {
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
        if (g_pad_held_flags & 16) {
            RECORD_SUBTITLE_TIME();
            RECORD_SUBTITLE_LEVEL();
            g_subtitle_state.state = 6;
            g_subtitle_state.timer = 4 - g_subtitle_state.timer;
            return;
        }
        if (g_subtitle_state.timer < 4)
            return;
        subtitles = g_is_pal_video[4];
        if (g_subtitle_entries[0][g_subtitle_state.entry].id != -1 && g_copy_setup_data.audio[g_subtitle_entries[0][g_subtitle_state.entry].id] &&
            g_subtitle_entries[0][g_subtitle_state.entry].id != g_music_state.id - 6000 && subtitles)
            goto next_phase;
        if (g_subtitle_entries[0][g_subtitle_state.entry].id != -1 && g_copy_setup_data.audio[g_subtitle_entries[0][g_subtitle_state.entry].id] &&
            (g_music_state.state != 3 || g_music_state.id < 6000) && subtitles)
            return;
        if (subtitles && g_subtitle_entries[0][g_subtitle_state.entry].id == g_music_state.id - 6000)
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
        if (g_subtitle_state.timer >= ((s32)(g_subtitle_state.duration) * 5 + 2) / 6) {
            if (g_subtitle_entries[0][g_subtitle_state.entry].id == -1 || !g_copy_setup_data.audio[g_subtitle_entries[0][g_subtitle_state.entry].id] ||
                !g_is_pal_video[4])
                goto close;
        }
        if (g_is_pal_video[4]) {
            if (g_subtitle_entries[0][g_subtitle_state.entry].id != -1 && g_copy_setup_data.audio[g_subtitle_entries[0][g_subtitle_state.entry].id] &&
                g_subtitle_entries[0][g_subtitle_state.entry].id != g_music_state.id - 6000)
                goto close;
        }
        if (!(g_pad_held_flags & 16))
            return;
    close:
        RECORD_SUBTITLE_TIME();
        g_subtitle_state.state = 6;
        g_subtitle_state.timer = 0;
        RECORD_SUBTITLE_LEVEL();
        break;
    case 6:
        if (*(unsigned short *)&g_is_pal_video[4] && g_subtitle_state.timer < 4 && !(g_pad_held_flags & 16))
            return;
        g_subtitle_state.state = 7;
        g_subtitle_state.timer = 0;
        break;
    case 7:
        ForceClaimNotice(5, 0, 1);
        if (g_subtitle_entries[0][g_subtitle_state.entry].id == g_music_state.id - 6000 &&
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

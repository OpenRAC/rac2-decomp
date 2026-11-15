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

extern SubtitleStateUpdate D_00254E78;
extern SubtitleEntryUpdate *D_001B1840[] __attribute__((sda));
extern SubtitleHistory D_0018C958[];
extern SubtitleOwnerUpdate D_001A63A8;
extern SubtitleDiscToc D_0014B540;
extern unsigned short D_001A7B94 MACRO_ADDR;
extern int D_001A79F0[] __attribute__((sda));
extern int D_001A8BB0[] __attribute__((sda));
extern unsigned int D_00138320;
extern unsigned int D_00138324;
extern unsigned int D_001A7390[] __attribute__((sda));

extern int func_00282948(int *);
extern void func_00289020(void);
extern void func_0028A030(int);
extern void func_002B0CE0(int, int, int);
extern void func_002B6D28(void);
extern int func_00288F48(int);

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
void func_00289178(void)
{
    if (!gSubtitleState.enabled) {
        if (gCurrentMapIndex[0] >= 0) {
            gSubtitleState.enabled = 1;
            gSubtitleState.wait = 120;
        } else {
            if (!gSubtitleState.wait && (D_00138320 & 0xF000))
                gSubtitleState.wait = 1;
            if (gSubtitleState.wait) {
                gSubtitleState.wait++;
                if (gSubtitleState.wait >= 120)
                    gSubtitleState.enabled = 1;
            }
        }
    }
    if ((gCurrentGameMode[0] != 0 && gCurrentGameMode[0] != 7) || !gSubtitleState.enabled) {
        gSubtitleState.pending = -1;
        gSubtitleState.state = 0;
        gSubtitleState.timer = 0;
        return;
    }
    gSubtitleState.timer++;
    if (!SUBTITLES_OPTION) {
        if (SUBTITLE_VOICE_ID == gMusicState.id - 6000 &&
            (unsigned short)(gMusicState.state - 6) > 1)
            gMusicState.state = 5;
    }
    switch (gSubtitleState.state) {
    case 8:
        if (gSubtitleState.flag38)
            return;
        if (gSubtitleState.entry >= 0) {
            if (!gSubtitleState.flag3A) {
                if (!FastFloatHelperD(&gSubtitleState.countdown))
                    return;
                InitSubtitleBoxState();
                gSubtitleState.flag3A++;
                return;
            }
            if (gSubtitleHistory[gSubtitleState.selection].count < 65535)
                gSubtitleHistory[gSubtitleState.selection].count++;
        }
        if (gSubtitleHistory[gSubtitleState.selection].time < D_001A7390[0])
            gSubtitleHistory[gSubtitleState.selection].time = D_001A7390[0];
        gSubtitleState.entry = -1;
        gSubtitleState.state = 0;
        gSubtitleState.flag3A = 0;
        RECORD_SUBTITLE_LEVEL();
        break;
    case 0:
        if (gSubtitleState.pending < 0)
            return;
        gSubtitleState.entry = Help_FindIndex(gSubtitleState.pending);
        MarkTextEntryRecent(gSubtitleState.pending);
        gSubtitleState.pending = -1;
        if (gSubtitleState.entry >= 0)
            InitSubtitleBoxState();
        break;
    case 1:
    case 2:
        if (SUBTITLES_OPTION) {
            if (SUBTITLE_VOICE_ID != -1 && HAS_AUDIO(SUBTITLE_VOICE_ID) &&
                !gMusicState.active && gMusicState.key == -1) {
                gMusicState.selection = 0;
                gMusicState.key = gSubtitleState.selection + 6000;
            }
        }
        if (D_00138324 & 16) {
            RECORD_SUBTITLE_TIME();
            gSubtitleState.state = 7;
            gSubtitleState.timer = 0;
            RECORD_SUBTITLE_LEVEL();
            return;
        }
        if (gSubtitleState.timer <= 0)
            return;
        if ((gMusicState.state == 3 && gMusicState.id >= 6000) ||
            SUBTITLE_VOICE_ID == -1 || !HAS_AUDIO(SUBTITLE_VOICE_ID) ||
            SUBTITLE_VOICE_ID != gMusicState.id - 6000) {
            gSubtitleState.state = 3;
            gSubtitleState.timer = 0;
        }
        break;
    case 3:
        ForceClaimNotice(5, 0, 1);
        if (D_00138324 & 16) {
            RECORD_SUBTITLE_TIME();
            gSubtitleState.state = 7;
            gSubtitleState.timer = 0;
            RECORD_SUBTITLE_LEVEL();
            return;
        }
        if (gSubtitleState.timer >= 8) {
            gSubtitleState.timer = 0;
            gSubtitleState.state = 4;
        }
        break;
    case 4: {
        int subtitles;
        ForceClaimNotice(5, 0, 1);
        if (D_00138324 & 16) {
            RECORD_SUBTITLE_TIME();
            RECORD_SUBTITLE_LEVEL();
            gSubtitleState.state = 6;
            gSubtitleState.timer = 4 - gSubtitleState.timer;
            return;
        }
        if (gSubtitleState.timer < 4)
            return;
        subtitles = SUBTITLES_OPTION;
        if (SUBTITLE_VOICE_ID != -1 && HAS_AUDIO(SUBTITLE_VOICE_ID) &&
            SUBTITLE_VOICE_ID != gMusicState.id - 6000 && subtitles)
            goto next_phase;
        if (SUBTITLE_VOICE_ID != -1 && HAS_AUDIO(SUBTITLE_VOICE_ID) &&
            (gMusicState.state != 3 || gMusicState.id < 6000) && subtitles)
            return;
        if (subtitles && SUBTITLE_VOICE_ID == gMusicState.id - 6000)
            ResumeMusicStream();
        gSubtitleState.state = 5;
        gSubtitleState.timer = 0;
        break;
    next_phase:
        gSubtitleState.timer = 0;
        gSubtitleState.state = 5;
        break;
    }
    case 5:
        ForceClaimNotice(5, 0, 1);
        if (gSubtitleState.timer >= gSubtitleState.duration) {
            /* Retail reloads this option again below, without an intervening store. */
            if (SUBTITLE_VOICE_ID == -1 || !HAS_AUDIO(SUBTITLE_VOICE_ID) ||
                !*(volatile unsigned char *)&D_001A7B94)
                goto close;
        }
        if (*(volatile unsigned char *)&D_001A7B94) {
            if (SUBTITLE_VOICE_ID != -1 && HAS_AUDIO(SUBTITLE_VOICE_ID) &&
                SUBTITLE_VOICE_ID != gMusicState.id - 6000)
                goto close;
        }
        if (!(D_00138324 & 16))
            return;
    close:
        RECORD_SUBTITLE_TIME();
        gSubtitleState.state = 6;
        gSubtitleState.timer = 0;
        RECORD_SUBTITLE_LEVEL();
        break;
    case 6:
        if (D_001A7B94 && gSubtitleState.timer < 4 && !(D_00138324 & 16))
            return;
        gSubtitleState.state = 7;
        gSubtitleState.timer = 0;
        break;
    case 7:
        ForceClaimNotice(5, 0, 1);
        if (SUBTITLE_VOICE_ID == gMusicState.id - 6000 &&
            (unsigned short)(gMusicState.state - 6) > 1)
            gMusicState.state = 5;
        if (gSubtitleState.timer < 8)
            return;
        if (gSubtitleState.flag38) {
            gSubtitleState.state = 8;
        } else {
            gSubtitleState.state = 0;
            gSubtitleState.entry = -1;
        }
        gSubtitleState.timer = 0;
        break;
    }
}

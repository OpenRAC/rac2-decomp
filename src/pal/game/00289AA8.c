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

extern SubtitleStateUpdate D_00254E78;
extern SubtitleEntryUpdate *D_001B1840[] __attribute__((sda));
extern SubtitleHistory D_0018C958[];
extern SubtitleOwnerUpdate D_001A63A8;
extern SubtitleDiscToc D_0014B540;
/* The settings block func_00298E08 copies. Retail reads its subtitle halfword and byte at +4
 * at an offset from the block (lui and a tied %lo load, never moved into a delay slot). */
extern unsigned char D_001A7B90[] __attribute__((sda));
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
    if (!D_00254E78.enabled) {
        if (D_001A79F0[0] >= 0) {
            D_00254E78.enabled = 1;
            D_00254E78.wait = 100;
        } else {
            if (!D_00254E78.wait && (D_00138320 & 0xF000))
                D_00254E78.wait = 1;
            if (D_00254E78.wait) {
                D_00254E78.wait++;
                if (D_00254E78.wait >= 100)
                    D_00254E78.enabled = 1;
            }
        }
    }
    if ((D_001A8BB0[0] != 0 && D_001A8BB0[0] != 7) || !D_00254E78.enabled) {
        D_00254E78.pending = -1;
        D_00254E78.state = 0;
        D_00254E78.timer = 0;
        return;
    }
    D_00254E78.timer++;
    if (!D_001A7B90[4]) {
        if (D_001B1840[0][D_00254E78.entry].id == D_001A63A8.id - 6000 &&
            (unsigned short)(D_001A63A8.state - 6) > 1)
            D_001A63A8.state = 5;
    }
    switch (D_00254E78.state) {
    case 8:
        if (D_00254E78.flag38)
            return;
        if (D_00254E78.entry >= 0) {
            if (!D_00254E78.flag3A) {
                if (!func_00282948(&D_00254E78.countdown))
                    return;
                func_00289020();
                D_00254E78.flag3A++;
                return;
            }
            if (D_0018C958[D_00254E78.selection].count < 65535)
                D_0018C958[D_00254E78.selection].count++;
        }
        if (((s32)(D_001A7390[0]) * 5 + 2) / 6 > D_0018C958[D_00254E78.selection].time)
            D_0018C958[D_00254E78.selection].time = ((s32)(D_001A7390[0]) * 5 + 2) / 6;
        D_00254E78.entry = -1;
        D_00254E78.state = 0;
        D_00254E78.flag3A = 0;
        RECORD_SUBTITLE_LEVEL();
        break;
    case 0:
        if (D_00254E78.pending < 0)
            return;
        D_00254E78.entry = func_00288F48(D_00254E78.pending);
        func_0028A030(D_00254E78.pending);
        D_00254E78.pending = -1;
        if (D_00254E78.entry >= 0)
            func_00289020();
        break;
    case 1:
    case 2:
        if (D_001A7B90[4]) {
            if (D_001B1840[0][D_00254E78.entry].id != -1 && D_0014B540.audio[D_001B1840[0][D_00254E78.entry].id] &&
                !D_001A63A8.active && D_001A63A8.key == -1) {
                D_001A63A8.selection = 0;
                D_001A63A8.key = D_00254E78.selection + 6000;
            }
        }
        if (D_00138324 & 16) {
            RECORD_SUBTITLE_TIME();
            D_00254E78.state = 7;
            D_00254E78.timer = 0;
            RECORD_SUBTITLE_LEVEL();
            return;
        }
        if (D_00254E78.timer <= 0)
            return;
        if ((D_001A63A8.state == 3 && D_001A63A8.id >= 6000) ||
            D_001B1840[0][D_00254E78.entry].id == -1 || !D_0014B540.audio[D_001B1840[0][D_00254E78.entry].id] ||
            D_001B1840[0][D_00254E78.entry].id != D_001A63A8.id - 6000) {
            D_00254E78.state = 3;
            D_00254E78.timer = 0;
        }
        break;
    case 3:
        func_002B0CE0(5, 0, 1);
        if (D_00138324 & 16) {
            RECORD_SUBTITLE_TIME();
            D_00254E78.state = 7;
            D_00254E78.timer = 0;
            RECORD_SUBTITLE_LEVEL();
            return;
        }
        if (D_00254E78.timer >= 8) {
            D_00254E78.timer = 0;
            D_00254E78.state = 4;
        }
        break;
    case 4: {
        int subtitles;
        func_002B0CE0(5, 0, 1);
        if (D_00138324 & 16) {
            RECORD_SUBTITLE_TIME();
            RECORD_SUBTITLE_LEVEL();
            D_00254E78.state = 6;
            D_00254E78.timer = 4 - D_00254E78.timer;
            return;
        }
        if (D_00254E78.timer < 4)
            return;
        subtitles = D_001A7B90[4];
        if (D_001B1840[0][D_00254E78.entry].id != -1 && D_0014B540.audio[D_001B1840[0][D_00254E78.entry].id] &&
            D_001B1840[0][D_00254E78.entry].id != D_001A63A8.id - 6000 && subtitles)
            goto next_phase;
        if (D_001B1840[0][D_00254E78.entry].id != -1 && D_0014B540.audio[D_001B1840[0][D_00254E78.entry].id] &&
            (D_001A63A8.state != 3 || D_001A63A8.id < 6000) && subtitles)
            return;
        if (subtitles && D_001B1840[0][D_00254E78.entry].id == D_001A63A8.id - 6000)
            func_002B6D28();
        D_00254E78.state = 5;
        D_00254E78.timer = 0;
        break;
    next_phase:
        D_00254E78.timer = 0;
        D_00254E78.state = 5;
        break;
    }
    case 5:
        func_002B0CE0(5, 0, 1);
        if (D_00254E78.timer >= ((s32)(D_00254E78.duration) * 5 + 2) / 6) {
            if (D_001B1840[0][D_00254E78.entry].id == -1 || !D_0014B540.audio[D_001B1840[0][D_00254E78.entry].id] ||
                !D_001A7B90[4])
                goto close;
        }
        if (D_001A7B90[4]) {
            if (D_001B1840[0][D_00254E78.entry].id != -1 && D_0014B540.audio[D_001B1840[0][D_00254E78.entry].id] &&
                D_001B1840[0][D_00254E78.entry].id != D_001A63A8.id - 6000)
                goto close;
        }
        if (!(D_00138324 & 16))
            return;
    close:
        RECORD_SUBTITLE_TIME();
        D_00254E78.state = 6;
        D_00254E78.timer = 0;
        RECORD_SUBTITLE_LEVEL();
        break;
    case 6:
        if (*(unsigned short *)&D_001A7B90[4] && D_00254E78.timer < 4 && !(D_00138324 & 16))
            return;
        D_00254E78.state = 7;
        D_00254E78.timer = 0;
        break;
    case 7:
        func_002B0CE0(5, 0, 1);
        if (D_001B1840[0][D_00254E78.entry].id == D_001A63A8.id - 6000 &&
            (unsigned short)(D_001A63A8.state - 6) > 1)
            D_001A63A8.state = 5;
        if (D_00254E78.timer < 8)
            return;
        if (D_00254E78.flag38) {
            D_00254E78.state = 8;
        } else {
            D_00254E78.state = 0;
            D_00254E78.entry = -1;
        }
        D_00254E78.timer = 0;
        break;
    }
}

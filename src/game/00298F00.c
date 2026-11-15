/* func_00298F00 (7,840 bytes, boot + 27 levels): the memory-card state machine, the same
 * engine routine as rac1-decomp's memcard_update_state grown to two cards and 28 states (rac1
 * used for reference only). Default -G0 profile, no cflags line. Matched by Opus big6, big11,
 * big14 and closer3.
 *
 * What it takes:
 *   - The directory loop reads the slot digit as entry->name[4] from the entry pointer
 *     (lbu 0x24(entry)); that needs a compiler without giv recombination, as retail's
 *     (tools/compiler/transformers/no_recombine_givs.py, docs/build/compiler-notes.md).
 *   - Error chains: sched1 puts the last of a run of independent zero stores first, so the
 *     source order is state, cur, busy (state 3's chain is err, state, cur, busy), which makes
 *     the state-25 reset block the cross-jump target.
 *   - State 10/21 and state 23/8's func_0029B628 arm write state, then cur, so both cross-jump
 *     onto 16/10's cur, state tail as in retail (a goto reset_state lands on the wrong one).
 *   - State 27 is if (result >= 0x2800) {...sub++} else sub = (sub/5+1)*5, then the shared
 *     state = 25; busy = 0; state 26's else is state = 25; sub = ...; busy = 0. Its flags go
 *     through a prev copy (prev | 0x80, prev | 0x81); the record advance is
 *     p + (((p[1] + 3) / 4) * 4 + 8).
 *   - The flags word is the player-stats word D_001A7A00[8] with D_001A7A00 an sda incomplete
 *     array: the (const (plus sym 0x20)) form keeps retail's unsplit lui $at store out of a
 *     delay slot (lead's ruling: one real name in its base-plus-offset form, not an alias).
 *   - func_00288970 returns int (0 / -1), which moves x340 into $v1 in 16/3 and 17.
 *   - 16/6-16/7: x28 + 8 + index * x2C, and finished_card set before the compare in 16/7.
 *   - 10/19: D_001A79F0 is an sda int (as in src/game/00298E08.c); size before buf.
 *   - The save size in 20/1 is x28 + x2C * 0x1C + 8, as in 10/19.
 */
#include "common.h"

/* The memory-card state machine: the same engine routine as rac1-decomp's
 * memcard_update_state (src/game/memcard.c), grown to two cards and 28 states. */

typedef struct McSave_298F00 {
    s32 x0;
    u8 pad4[0x18];
} McSave_298F00;

typedef struct McCard_298F00 {
    s32 port;           /* 0x00 */
    s32 slot;           /* 0x04 */
    s32 type;           /* 0x08 */
    s32 free;           /* 0x0C */
    s32 result;         /* 0x10 */
    s32 format;         /* 0x14 */
    s16 status;         /* 0x18 */
    s16 tries;          /* 0x1A */
    s32 x1C;            /* 0x1C */
    s32 used_blocks;    /* 0x20 */
    s32 x24;            /* 0x24 */
    s32 x28;            /* 0x28 */
    s32 x2C;            /* 0x2C */
    McSave_298F00 save[4]; /* 0x30 */
} McCard_298F00;

typedef struct McState_298F00 {
    McCard_298F00 card[2]; /* 0x000 */
    s32 cmd;            /* 0x140 */
    s32 result;         /* 0x144 */
    s32 x148;
    s32 cur;            /* 0x14C */
    s32 index;          /* 0x150 */
    s32 busy;           /* 0x154 */
    s32 fd;             /* 0x158 */
    s32 state;          /* 0x15C */
    s32 sub;            /* 0x160 */
    s32 next_state;     /* 0x164 */
    s32 next_card;      /* 0x168 */
    s32 err;            /* 0x16C */
    s32 err_card;       /* 0x170 */
    void *buf;          /* 0x174 */
    s32 size;           /* 0x178 */
    s32 x17C;
    s32 probe;          /* 0x180 */
    s32 retry;          /* 0x184 */
} McState_298F00;

typedef struct { u8 pad[0x10]; u32 size; u8 pad14[0xC]; char name[0x20]; } McDirEntry_298F00;

typedef struct McChunk_298F00 {
    s32 x0;
    s32 x4;
    s32 x8;
    s32 xC;
    s32 x10;
} McChunk_298F00;

extern McState_298F00 D_001393E0;
extern McDirEntry_298F00 D_001C5280[];
extern char D_001C52A0[];
extern char D_001A7930[];
extern char D_001A7948[];
extern char D_001A7960[];
extern char D_001A7975[];
extern char D_001A7980[];
extern char D_001A7995[];
extern char D_001A79A0[];
extern char D_001A79B5[];
extern char D_001A79D0[];
extern s32 D_001A79F0 __attribute__((sda));
extern char D_001A9988[];
extern char D_001A9990[];
extern char D_001A9998[];
extern char D_001A99A0[];
extern char D_001A99B0[];
extern char D_001A99C8[];
extern char D_001A99E8[];
extern char D_001A9A08[];
extern char D_001A2BA8[];
extern s32 D_001A2BB0[];
extern char D_001A53A8[];
extern int D_00256138[];
extern int D_00256368[];
extern s16 D_001A63AC;
extern s32 D_001A7A00[] __attribute__((sda));
extern s32 D_0014B884;
extern struct { u8 pad[0x32C]; s32 x32C; u8 pad330[0x10]; s32 x340; s32 x344; } D_0014B540;


extern int func_00127B88(int, int *, int *);
extern int func_00127CC0(int port, int slot, int *type, int *free, int *format);
extern int func_00127F98(int, int);
extern int func_00128180(int, int);
extern int func_00127E48(int, int, char *, int, int, void *);
extern int func_00115484(void *, int, int);
extern int func_00115544(const char *, const char *);
extern int func_001158F8(const char *, const char *, int);
extern int func_00115DA8(char *, char *, ...);
extern int func_00115690(char *, const char *);
extern int func_00127508(int, int, char *, int);
extern int func_00127888(int fd, void *buf, int nbyte);
extern int func_0029AE78(int *);
extern int func_00127668(int);
extern int func_00127630(int, int, char *);
extern int func_00288970(int, void *);
extern int func_002B7B18(int, int, int);
extern int func_001279A0(int fd, void *buffer, int size);
extern int func_00128068(int port, int slot, char *fname);
extern void func_0026FEB8(void *, ...);
extern void func_00282A28(void);
extern void func_0029B0B0(char *, int, int);
extern int func_0029B168(char *, int, int *);
extern void func_0029B628(void);
extern int func_00127720(int, int, int);
extern int func_0029AF58(void *);

/* Runs one step of the memory card state machine: checks cards, reads the directory, loads, saves and formats files. */
void func_00298F00(void)
{
    union {
        char name[0x40];
        struct {
            s32 seen[4];
            char name[0x40];
        } directory;
    } workspace;
    McState_298F00 *finished_card;

    if (gMemcardState.busy) {
        gMemcardState.busy = SceMcSync(1, &gMemcardState.cmd, &gMemcardState.result) == 0;
        return;
    }
    gMemcardState.busy = 1;

    switch (gMemcardState.state) {
    case 0:
        if ((u32)gMemcardState.probe >= 2)
            gMemcardState.probe = 0;
        if (SceMcGetInfo(gMemcardState.card[gMemcardState.probe].port, gMemcardState.card[gMemcardState.probe].slot,
                          &gMemcardState.card[gMemcardState.probe].type, &gMemcardState.card[gMemcardState.probe].free,
                          &gMemcardState.card[gMemcardState.probe].format) == 0)
            gMemcardState.state = 1;
        break;

    case 1:
        if (gMemcardState.result != 0) {
            gMemcardState.card[gMemcardState.probe].status = -4;
            gMemcardState.card[gMemcardState.probe].result = gMemcardState.result;
            gMemcardState.card[gMemcardState.probe].x24 = -1;
            gMemcardState.card[gMemcardState.probe].used_blocks = 0;
            gMemcardState.card[gMemcardState.probe].save[0].x0 = -1;
            gMemcardState.card[gMemcardState.probe].save[1].x0 = -1;
            gMemcardState.card[gMemcardState.probe].save[2].x0 = -1;
            gMemcardState.card[gMemcardState.probe].save[3].x0 = -1;
            gMemcardState.card[gMemcardState.probe].x1C = 0;
        }
        if (gMemcardState.next_card < ++gMemcardState.probe && gMemcardState.next_state >= 0) {
            gMemcardState.state = 2;
            if (gMemcardState.next_card >= 0) {
                if (gMemcardState.card[gMemcardState.next_card].result == 0 || gMemcardState.next_state == 0x18) {
                    gMemcardState.cur = gMemcardState.next_card;
                    gMemcardState.state = gMemcardState.next_state;
                    gMemcardState.err = 0;
                } else {
                    gMemcardState.err = 0x271A;
                }
            } else {
                gMemcardState.err = 0x271A;
            }
            gMemcardState.next_state = -1;
            gMemcardState.next_card = -1;
            break;
        }
        if (gMemcardState.probe < 2)
            gMemcardState.state = 0;
        else
            gMemcardState.state = 2;
        gMemcardState.busy = 0;
        break;

    case 2:
        gMemcardState.retry++;
        if (gMemcardState.next_state >= 0 || gMemcardState.retry >= 11) {
            gMemcardState.retry = 0;
            gMemcardState.probe = 0;
            gMemcardState.state = 0;

        }

        gMemcardState.busy = 0;
        break;

    case 3:
        if (gMemcardState.card[gMemcardState.cur].format == 0) {
            if (func_00127F98(gMemcardState.card[gMemcardState.cur].port, gMemcardState.card[gMemcardState.cur].slot) == 0) {
                gMemcardState.state = 4;
            }
            break;
        }
        gMemcardState.busy = 0;
        gMemcardState.state = 2;
        break;

    case 4:
        if (gMemcardState.result != 0) {
            gMemcardState.err = 1;
            gMemcardState.err_card = gMemcardState.cur;
        }
        gMemcardState.state = 0;
        gMemcardState.cur = 0;
        gMemcardState.busy = 0;
        break;

    case 5:
        if (gMemcardState.card[gMemcardState.cur].format == 0) {
            if (SceMcUnformat(gMemcardState.card[gMemcardState.cur].port, gMemcardState.card[gMemcardState.cur].slot) == 0) {
                gMemcardState.state = 6;
            }
            break;
        }
        gMemcardState.busy = 0;
        gMemcardState.state = 2;
        break;

    case 6:
        if (gMemcardState.result != 0) {
            gMemcardState.err = 2;
            gMemcardState.err_card = gMemcardState.cur;
        }
        gMemcardState.state = 0;
        gMemcardState.cur = 0;
        gMemcardState.busy = 0;
        break;

    case 7:
        if (func_00127E48(gMemcardState.card[gMemcardState.cur].port, gMemcardState.card[gMemcardState.cur].slot,
                          D_001A7948, 0, 11, D_001C5280) == 0) {
            gMemcardState.sub = 0;
            gMemcardState.state = 8;
        }
        break;

    case 8:
        switch (gMemcardState.sub) {
        case 0:
            if (gMemcardState.result > 0) {
                s32 icon0;
                s32 icon1;
                s32 icon2;
                s32 i;
                s32 blocks;
                icon0 = 0;
                memset(workspace.directory.seen, 0, 16);
                icon1 = 0;
                icon2 = 0;
                blocks = 0;
                for (i = 0; i < gMemcardState.result; i++) {
                    McDirEntry_298F00 *entry = &D_001C5280[i];
                    char *filename = (char *)((s32)D_001C5280 + i * 64 + 32);
                    s32 slot;
                    blocks += (entry->size + 1023U) >> 10;
                    if (strcmp_00115544(filename, D_001A7975) == 0) icon0 = 1;
                    if (strcmp_00115544(filename, D_001A7995) == 0) icon1 = 1;
                    if (strcmp_00115544(filename, D_001A79B5) == 0) icon2 = 1;
                    if (func_001158F8(filename, D_001A9988, 4) == 0 &&
                        func_001158F8(filename + 5, D_001A9990, 4) == 0) {
                        slot = (u8)entry->name[4] - '0';
                        if (slot < 0) continue;
                        if (slot < 4) workspace.directory.seen[slot] = 1;
                    }
                }
                blocks += (gMemcardState.result + 2) / 2;
                if ((u32)(blocks - 0x1DB) < 2 && gMemcardState.result == 9 && icon0 && icon1 && icon2 &&
                    workspace.directory.seen[0] && workspace.directory.seen[1] && workspace.directory.seen[2] && workspace.directory.seen[3]) {
                    gMemcardState.card[gMemcardState.cur].used_blocks = 0;
                    gMemcardState.card[gMemcardState.cur].status = -1;
                    gMemcardState.sub = 1;
                    gMemcardState.busy = 0;
                } else {
                    gMemcardState.card[gMemcardState.cur].used_blocks = blocks;
                    gMemcardState.card[gMemcardState.cur].status = -2;
                    goto reset_request;
                }
            } else {
                gMemcardState.card[gMemcardState.cur].status = -2;
                if (gMemcardState.result == -2) {
                    gMemcardState.err = 3;
                    gMemcardState.err_card = gMemcardState.cur;
                } else if (gMemcardState.result >= 0) {
                    gMemcardState.card[gMemcardState.cur].status = -2;
                } else if (gMemcardState.result != -4) {
                    gMemcardState.err = 4;
                    gMemcardState.err_card = gMemcardState.cur;
                }
                gMemcardState.state = 0;
                gMemcardState.cur = 0;
                gMemcardState.busy = 0;
            }
            break;
        case 1:
            Sprintf(workspace.directory.name, D_001A79D0, 0);
            if (SceMcOpen(gMemcardState.card[gMemcardState.cur].port, gMemcardState.card[gMemcardState.cur].slot, workspace.directory.name, 1) == 0) {
                gMemcardState.sub++;
            }
            break;
        case 2:
            if (gMemcardState.result >= 0) {
                gMemcardState.fd = gMemcardState.result;
                gMemcardState.sub = 3;
            } else {
                gMemcardState.card[gMemcardState.cur].status = -2;
                gMemcardState.err_card = gMemcardState.cur;
                if (gMemcardState.result == -7) {
                    gMemcardState.err = 0x2710;
                } else if (gMemcardState.result == -5) {
                    gMemcardState.err = 0x2711;
                } else if (gMemcardState.result == -4) {
                    gMemcardState.err = 0x2712;
                } else if (gMemcardState.result == -3) {
                    gMemcardState.err = 0x2713;
                } else if (gMemcardState.result == -2) {
                    gMemcardState.err = 3;
                } else {
                    gMemcardState.err = 4;
                }
                gMemcardState.state = 0;
                gMemcardState.cur = 0;
            }
            gMemcardState.busy = 0;
            break;
        case 3:
            gMemcardState.size = 8;
            if (SceMcRead(gMemcardState.fd, &gMemcardState.card[gMemcardState.cur].x28, 8) == 0) {
                gMemcardState.sub = 4;
            }
            break;
        case 4:
            if (gMemcardState.result == gMemcardState.size) {
                gMemcardState.card[gMemcardState.cur].x24 = 0;
                if (gMemcardState.card[gMemcardState.cur].x28 != memcard_GetDataSize(D_00256138)) {
                    gMemcardState.card[gMemcardState.cur].x24++;
                }
                if (gMemcardState.card[gMemcardState.cur].x2C != memcard_GetDataSize(D_00256368)) {
                    gMemcardState.card[gMemcardState.cur].x24++;
                }
                gMemcardState.busy = 0;
                gMemcardState.sub = 5;
            } else {
                gMemcardState.card[gMemcardState.cur].status = -2;
                gMemcardState.err_card = gMemcardState.cur;
                if (gMemcardState.result >= 0) {
                    gMemcardState.err = 0x2716;
                    if (SceMcClose(gMemcardState.fd) == 0) {
                        gMemcardState.state = 0;
                        gMemcardState.cur = 0;
                        gMemcardState.busy = 0;
                    }
                    break;
                }
                if (gMemcardState.result == -5) {
                    gMemcardState.err = 0x2711;
                } else if (gMemcardState.result == -4) {
                    gMemcardState.err = 0x2714;
                } else if (gMemcardState.result == -3) {
                    gMemcardState.err = 0x2715;
                } else if (gMemcardState.result == -2) {
                    gMemcardState.err = 3;
                } else {
                    gMemcardState.err = 4;
                }
                gMemcardState.state = 0;
                gMemcardState.cur = 0;
                gMemcardState.busy = 0;
            }
            break;
        case 5:
            if (SceMcClose(gMemcardState.fd) == 0) {
                gMemcardState.busy = 0;
                gMemcardState.state = 21;
            }
            break;
        }
        break;

    case 9:
        gMemcardState.state = 10;
        gMemcardState.sub = 0;
        gMemcardState.card[gMemcardState.cur].status = 0;
    case 10:
        switch (gMemcardState.sub) {
        case 0:
            if (gMemcardState.card[gMemcardState.cur].free + gMemcardState.card[gMemcardState.cur].used_blocks >= 0x1DB) {
                gMemcardState.sub = 1;
            } else {
                gMemcardState.err = 7;
                gMemcardState.err_card = gMemcardState.cur;
                gMemcardState.state = 0;
                gMemcardState.cur = 0;
            }
            gMemcardState.busy = 0;
            break;
        case 1:
            if (SceMcMkdir(gMemcardState.card[gMemcardState.cur].port, gMemcardState.card[gMemcardState.cur].slot, D_001A7930) == 0) {
                gMemcardState.sub = 2;
            }
            break;
        case 2:
            if (gMemcardState.result == 0 || gMemcardState.result == -4) {
                gMemcardState.sub = 3;
                break;
            }
            gMemcardState.err_card = gMemcardState.cur;
            if (gMemcardState.result == -3) {
                gMemcardState.err = 7;
            } else if (gMemcardState.result == -2) {
                gMemcardState.err = 6;
            } else {
                gMemcardState.err = 0xD;
            }
            gMemcardState.state = 0;
            gMemcardState.cur = 0;
            gMemcardState.busy = 0;
            break;
        case 3: {
            McChunk_298F00 *chunk;

            ComputeSizedOffset(gCopySetupData.x344 << 11, &chunk);
            StartDiscRead((s32)chunk, gCopySetupData.x340 + gCopySetupData.x32C, gCopySetupData.x344);
            gMemcardState.sub = 4;
            gMemcardState.busy = 0;
            break;
        }
        case 4:
            if (D_001A63AC == 0) {
                gMemcardState.sub = 5;
            }
            gMemcardState.busy = 0;
            break;
        case 5:
        case 9:
        case 13:
        case 18:
            switch (gMemcardState.sub) {
            case 5:
                strcpy(workspace.name, D_001A7960);
                break;
            case 9:
                strcpy(workspace.name, D_001A7980);
                break;
            case 18:
                strcpy(workspace.name, D_001A79A0);
                break;
            case 13:
                Sprintf(workspace.name, D_001A79D0, gMemcardState.card[gMemcardState.cur].status);
                break;
            }
            if (SceMcOpen(gMemcardState.card[gMemcardState.cur].port, gMemcardState.card[gMemcardState.cur].slot, workspace.name, 0x203) == 0) {
                gMemcardState.fd = -1;
                gMemcardState.sub++;
            }
            break;
        case 6:
        case 10:
        case 14:
        case 19: {
            McChunk_298F00 *chunk;

            if (gMemcardState.result >= 0) {
                if (gMemcardState.fd < 0) {
                    gMemcardState.fd = gMemcardState.result;
                }
                ComputeSizedOffset(D_0014B884 << 11, &chunk);
                switch (gMemcardState.sub) {
                case 6:
                    gMemcardState.size = 0x3C4;
                    gMemcardState.buf = (u8 *)chunk + chunk->x0;
                    break;
                case 10:
                    gMemcardState.size = chunk->xC;
                    gMemcardState.buf = (u8 *)chunk + chunk->x8;
                    break;
                case 19:
                    gMemcardState.size = 0xD804;
                    gMemcardState.buf = &gCurrentMapIndex;
                    break;
                case 14: {
                    s32 n = memcard_GetDataSize(D_00256138);
                    gMemcardState.size = n + memcard_GetDataSize(D_00256368) * 0x1C + 8;
                    gMemcardState.buf = (u8 *)chunk + chunk->x10;
                    break;
                }
                }
                if (SceMcWrite(gMemcardState.fd, gMemcardState.buf, gMemcardState.size) == 0) {
                    gMemcardState.sub++;
                }
            } else {
                gMemcardState.err = 0xA;
                gMemcardState.err_card = gMemcardState.cur;
                gMemcardState.state = 0;
                gMemcardState.cur = 0;
                gMemcardState.busy = 0;
            }
            break;
        }
        case 7:
        case 11:
        case 15:
        case 20:
            if (gMemcardState.result == gMemcardState.size) {
                if (SceMcClose(gMemcardState.fd) == 0) {
                    gMemcardState.sub++;
                }
                break;
            }
            gMemcardState.err_card = gMemcardState.cur;
            if (gMemcardState.result >= 0) {
                finished_card = &gMemcardState;
                finished_card->err = 0xB;
                if (SceMcClose(finished_card->fd) == 0) {
                    finished_card->busy = 0;
                    goto reset_state;
                }
                break;
            }
            if (gMemcardState.result == -4) {
                gMemcardState.err = 8;
            } else if (gMemcardState.result == -3) {
                gMemcardState.err = 7;
            } else if (gMemcardState.result == -2) {
                gMemcardState.err = 6;
            } else {
                gMemcardState.err = 0xD;
            }
            gMemcardState.state = 0;
            gMemcardState.cur = 0;
            gMemcardState.busy = 0;
            break;
        case 8:
        case 12:
        case 16:
            if (gMemcardState.result == 0) {
                gMemcardState.sub++;
            } else {
                gMemcardState.err = 0xC;
                gMemcardState.err_card = gMemcardState.cur;
                gMemcardState.state = 0;
                gMemcardState.cur = 0;
            }
            gMemcardState.busy = 0;
            break;
        case 17:
            if (++gMemcardState.card[gMemcardState.cur].status < 4) {
                gMemcardState.sub = 13;
            } else {
                gMemcardState.sub++;
            }
            gMemcardState.busy = 0;
            break;
        case 21:
            gMemcardState.card[gMemcardState.cur].x28 = memcard_GetDataSize(D_00256138);
            gMemcardState.card[gMemcardState.cur].x2C = memcard_GetDataSize(D_00256368);
            gMemcardState.card[gMemcardState.cur].status = -1;
            gMemcardState.card[gMemcardState.cur].x24 = 0;
            gMemcardState.state = 0;
            gMemcardState.cur = 0;
            break;
        }
        break;

    case 11:
        gMemcardState.state = 12;
        gMemcardState.sub = 0;
        gMemcardState.card[gMemcardState.cur].status = -2;
    case 12:
        switch (gMemcardState.sub) {
        case 0:
            if (func_00127E48(gMemcardState.card[gMemcardState.cur].port, gMemcardState.card[gMemcardState.cur].slot, D_001A7948, 0, 1, D_001C5280) == 0) {
                gMemcardState.sub = 1;
            }
            break;
        case 1:
            if (gMemcardState.result == 1) {
                Sprintf(workspace.name, D_001A9998, D_001A7930, D_001C52A0);
                STUB_printf(D_001A99A0, workspace.name);
                if (SceMcDelete(gMemcardState.card[gMemcardState.cur].port, gMemcardState.card[gMemcardState.cur].slot, workspace.name) == 0) {
                    gMemcardState.sub = 2;
                }
            } else {
                if (gMemcardState.result == 0) {
                    gMemcardState.sub = 3;
                } else {
                    gMemcardState.err_card = gMemcardState.cur;
                    if (gMemcardState.result == -5) {
                        gMemcardState.err = 0x10;
                    } else if (gMemcardState.result == -4) {
                        gMemcardState.err = 0xF;
                    } else if (gMemcardState.result == -2) {
                        gMemcardState.err = 0xE;
                    } else {
                        gMemcardState.err = 0x12;
                    }
                    gMemcardState.state = 0;
                    gMemcardState.cur = 0;
                }
                gMemcardState.busy = 0;
            }
            break;
        case 2:
            if (func_00127E48(gMemcardState.card[gMemcardState.cur].port, gMemcardState.card[gMemcardState.cur].slot, D_001A7948, 1, 1, D_001C5280) == 0) {
                gMemcardState.sub = 1;
            }
            break;
        case 3:
            if (SceMcDelete(gMemcardState.card[gMemcardState.cur].port, gMemcardState.card[gMemcardState.cur].slot, D_001A7930) == 0) {
                STUB_printf(D_001A99B0, D_001A7930);
                gMemcardState.sub = 4;
            }
            break;
        case 4:
            if (gMemcardState.result != 0) {
                gMemcardState.err_card = gMemcardState.cur;
                if (gMemcardState.result == -6) {
                    gMemcardState.err = 0x11;
                } else if (gMemcardState.result == -5) {
                    gMemcardState.err = 0x10;
                } else if (gMemcardState.result == -4) {
                    gMemcardState.err = 0xF;
                } else if (gMemcardState.result == -2) {
                    gMemcardState.err = 0xE;
                } else {
                    gMemcardState.err = 0x12;
                }
            }
            gMemcardState.state = 0;
            gMemcardState.cur = 0;
            gMemcardState.busy = 0;
            break;
        }
        break;

    case 21:
        gMemcardState.state = 22;
        gMemcardState.card[gMemcardState.cur].tries = -1;
        gMemcardState.index = 0;
        break;

    case 22:
        gMemcardState.card[gMemcardState.cur].tries++;
        if (gMemcardState.card[gMemcardState.cur].tries < 4) {
            gMemcardState.sub = 0;
            gMemcardState.state = 23;
        } else {
            gMemcardState.state = 0;
            gMemcardState.cur = 0;
            gMemcardState.busy = 0;
        }
        break;
    case 13:
        if (gMemcardState.card[gMemcardState.cur].status < 0) {
            gMemcardState.err = 0x13;
            gMemcardState.state = 0;
            gMemcardState.cur = 0;
            gMemcardState.busy = 0;
            break;
        }
        gMemcardState.index = 0;
        gMemcardState.sub = 0;
        gMemcardState.state = 14;
    case 14:
    case 23:
        switch (gMemcardState.sub) {
        case 0:
            if (gMemcardState.state == 23) {
                Sprintf(workspace.name, D_001A79D0, gMemcardState.card[gMemcardState.cur].tries);
            } else {
                Sprintf(workspace.name, D_001A79D0, gMemcardState.card[gMemcardState.cur].status);
            }
            if (SceMcOpen(gMemcardState.card[gMemcardState.cur].port, gMemcardState.card[gMemcardState.cur].slot, workspace.name, 1) == 0) {
                gMemcardState.sub++;
            }
            break;
        case 1:
            if (gMemcardState.result >= 0) {
                gMemcardState.fd = gMemcardState.result;
                gMemcardState.sub = 2;
            } else {
                gMemcardState.err_card = gMemcardState.cur;
                if (gMemcardState.result == -7) {
                    gMemcardState.err = 0x14;
                } else if (gMemcardState.result == -5) {
                    gMemcardState.err = 0x15;
                } else if (gMemcardState.result == -4) {
                    gMemcardState.err = 0x16;
                } else if (gMemcardState.result == -3) {
                    gMemcardState.err = 0x17;
                } else if (gMemcardState.result == -2) {
                    gMemcardState.err = 0x18;
                } else {
                    gMemcardState.err = 0x1C;
                }
                gMemcardState.state = 0;
                gMemcardState.cur = 0;
            }
            gMemcardState.busy = 0;
            break;
        case 2:
            gMemcardState.size = 8;
            if (SceMcRead(gMemcardState.fd, &gMemcardState.card[gMemcardState.cur].x28, 8) == 0) {
                gMemcardState.sub = 3;
            }
            break;
        case 3:
            if (gMemcardState.result == gMemcardState.size) {
                gMemcardState.busy = 0;
                gMemcardState.sub = 4;
                break;
            }
            gMemcardState.err_card = gMemcardState.cur;
            if (gMemcardState.result >= 0) {
                gMemcardState.err = 0x1B;
                if (SceMcClose(gMemcardState.fd) == 0) {
                    gMemcardState.state = 0;
                    gMemcardState.cur = 0;
                    gMemcardState.busy = 0;
                }
                break;
            }
            if (gMemcardState.result == -5) {
                gMemcardState.err = 0x15;
            } else if (gMemcardState.result == -4) {
                gMemcardState.err = 0x19;
            } else if (gMemcardState.result == -3) {
                gMemcardState.err = 0x1A;
            } else if (gMemcardState.result == -2) {
                gMemcardState.err = 0x18;
            } else {
                gMemcardState.err = 0x1C;
            }
            gMemcardState.state = 0;
            gMemcardState.cur = 0;
            gMemcardState.busy = 0;
            break;
        case 4:
            gMemcardState.size = gMemcardState.card[gMemcardState.cur].x28;
            if (gMemcardState.size > 0x2800) {
                TrapAlways();
            }
            if (SceMcRead(gMemcardState.fd, D_001A2BA8, gMemcardState.size) == 0) {
                gMemcardState.sub = 5;
            }
            break;
        case 5:
            if (gMemcardState.result == gMemcardState.size) {
                if (gMemcardState.state == 23) {
                    FillSaveSlotInfo(D_001A2BA8, gMemcardState.cur, gMemcardState.card[gMemcardState.cur].tries);
                    gMemcardState.sub = 8;
                } else {
                    gMemcardState.card[gMemcardState.cur].x24 = MemcardRestoreData(D_001A2BA8, 0, D_00256138);
                    gMemcardState.sub = 6;
                }
                gMemcardState.busy = 0;
                break;
            }
            gMemcardState.err_card = gMemcardState.cur;
            if (gMemcardState.result >= 0) {
                gMemcardState.err = 0x1B;
                if (SceMcClose(gMemcardState.fd) == 0) {
                    gMemcardState.state = 0;
                    gMemcardState.cur = 0;
                    gMemcardState.busy = 0;
                }
                break;
            }
            if (gMemcardState.result == -5) {
                gMemcardState.err = 0x15;
            } else if (gMemcardState.result == -4) {
                gMemcardState.err = 0x19;
            } else if (gMemcardState.result == -3) {
                gMemcardState.err = 0x1A;
            } else if (gMemcardState.result == -2) {
                gMemcardState.err = 0x18;
            } else {
                gMemcardState.err = 0x1C;
            }
            gMemcardState.state = 0;
            gMemcardState.cur = 0;
            gMemcardState.busy = 0;
            break;
        case 6:
            gMemcardState.size = gMemcardState.card[gMemcardState.cur].x2C;
            if (gMemcardState.size > 0x1000) {
                TrapAlways();
            }
            if (SceMcRead(gMemcardState.fd, D_001A53A8, gMemcardState.size) == 0) {
                gMemcardState.sub = 7;
            }
            break;
        case 7:
            if (gMemcardState.result == gMemcardState.size) {
                gMemcardState.card[gMemcardState.cur].x24 += MemcardRestoreData(D_001A53A8, gMemcardState.index, D_00256368);
                if (++gMemcardState.index < 0x1C) {
                    gMemcardState.sub = 6;
                } else {
                    gMemcardState.sub = 8;
                }
                gMemcardState.busy = 0;
                break;
            }
            gMemcardState.err_card = gMemcardState.cur;
            if (gMemcardState.result >= 0) {
                gMemcardState.err = 0x1B;
                if (SceMcClose(gMemcardState.fd) == 0) {
                    gMemcardState.state = 0;
                    gMemcardState.cur = 0;
                    gMemcardState.busy = 0;
                }
                break;
            }
            if (gMemcardState.result == -5) {
                gMemcardState.err = 0x15;
            } else if (gMemcardState.result == -4) {
                gMemcardState.err = 0x19;
            } else if (gMemcardState.result == -3) {
                gMemcardState.err = 0x1A;
            } else if (gMemcardState.result == -2) {
                gMemcardState.err = 0x18;
            } else {
                gMemcardState.err = 0x1C;
            }
        reset_request:
            gMemcardState.state = 0;
            gMemcardState.cur = 0;
            gMemcardState.busy = 0;
            break;
        case 8:
            if (SceMcClose(gMemcardState.fd) == 0) {
                if (gMemcardState.state == 23) {
                    gMemcardState.busy = 0;
                    gMemcardState.state = 22;
                } else {
                    finished_card = &gMemcardState;
                    ResetSaveSlotIds();
                    finished_card->state = 0;
                    finished_card->cur = 0;
                }
            }
            break;
        }
        break;

    case 15:
        if (gMemcardState.card[gMemcardState.cur].x24 != 0) {
            gMemcardState.busy = 0;
            gMemcardState.state = 0;
            gMemcardState.cur = 0;
            gMemcardState.err = 0x2717;
            break;
        }
        if (gMemcardState.card[gMemcardState.cur].status < 0) {
            gMemcardState.busy = 0;
            gMemcardState.state = 0;
            gMemcardState.cur = 0;
            gMemcardState.err = 0x1D;
            break;
        }
        gMemcardState.sub = 0;
        gMemcardState.state = 16;
    case 16:
        switch (gMemcardState.sub) {
        case 0:
            Sprintf(workspace.name, D_001A79D0, gMemcardState.card[gMemcardState.cur].status);
            if (SceMcOpen(gMemcardState.card[gMemcardState.cur].port, gMemcardState.card[gMemcardState.cur].slot, workspace.name, 2) == 0) {
                gMemcardState.sub = 1;
            }
            break;
        case 1:
            if (gMemcardState.result >= 0) {
                gMemcardState.fd = gMemcardState.result;
                gMemcardState.sub = 2;
            } else {
                gMemcardState.err_card = gMemcardState.cur;
                if (gMemcardState.result == -7) {
                    gMemcardState.err = 0x1E;
                } else if (gMemcardState.result == -5) {
                    gMemcardState.err = 0x1F;
                } else if (gMemcardState.result == -4) {
                    gMemcardState.err = 0x20;
                } else if (gMemcardState.result == -3) {
                    gMemcardState.err = 0x21;
                } else if (gMemcardState.result == -2) {
                    gMemcardState.err = 0x22;
                } else {
                    gMemcardState.err = 0x26;
                }
                gMemcardState.state = 0;
                gMemcardState.cur = 0;
            }
            gMemcardState.busy = 0;
            break;
        case 2:
            if (SceMcSeek(gMemcardState.fd, 8, 0) == 0) {
                gMemcardState.sub = 3;
            }
            break;
        case 3:
            if (gMemcardState.result >= 0) {
                gMemcardState.sub = 4;
            } else if (SceMcClose(gMemcardState.fd) == 0) {
                gMemcardState.err = 0x26;
                gMemcardState.state = 0;
                gMemcardState.cur = 0;
                gMemcardState.busy = 0;
            }
            break;
        case 4:
            if (SceMcWrite(gMemcardState.fd, D_001A2BA8, memcard_GetDataSize(D_00256138)) == 0) {
                gMemcardState.sub = 5;
            }
            break;
        case 5:
            if (gMemcardState.result == memcard_GetDataSize(D_00256138)) {
                gMemcardState.sub = 6;
                break;
            }
            gMemcardState.err_card = gMemcardState.cur;
            if (gMemcardState.result >= 0) {
                finished_card = &gMemcardState;
                finished_card->err = 0x25;
                if (SceMcClose(finished_card->fd) == 0) {
                    finished_card->busy = 0;
                    goto reset_state;
                }
                break;
            }
            if (gMemcardState.result == -5) {
                gMemcardState.err = 0x1F;
            } else if (gMemcardState.result == -4) {
                gMemcardState.err = 0x23;
            } else if (gMemcardState.result == -3) {
                gMemcardState.err = 0x24;
            } else if (gMemcardState.result == -2) {
                gMemcardState.err = 0x22;
            } else {
                gMemcardState.err = 0x26;
            }
            gMemcardState.state = 0;
            gMemcardState.cur = 0;
            gMemcardState.busy = 0;
            break;
        case 6:
            if (SceMcSeek(gMemcardState.fd, gMemcardState.card[0].x28 + 8 + gMemcardState.index * gMemcardState.card[0].x2C, 0) == 0) {
                gMemcardState.sub = 7;
            }
            break;
        case 7:
            finished_card = &gMemcardState;
            if (gMemcardState.result == gMemcardState.card[0].x28 + 8 + gMemcardState.index * gMemcardState.card[0].x2C) {
                gMemcardState.sub = 8;
            } else {
                if (SceMcClose(finished_card->fd) == 0) {
                    finished_card->busy = 0;
                    goto reset_state;
                }
            }
            break;
        case 8:
            if (SceMcWrite(gMemcardState.fd, D_001A53A8, memcard_GetDataSize(D_00256368)) == 0) {
                gMemcardState.sub = 9;
            }
            break;
        case 9:
            if (gMemcardState.result == memcard_GetDataSize(D_00256368)) {
                gMemcardState.sub = 10;
                break;
            }
            gMemcardState.err_card = gMemcardState.cur;
            if (gMemcardState.result >= 0) {
                finished_card = &gMemcardState;
                finished_card->err = 0x25;
                if (SceMcClose(finished_card->fd) == 0) {
                    finished_card->busy = 0;
                reset_state:
                    finished_card->cur = 0;
                    finished_card->state = 0;
                }
                break;
            }
            if (gMemcardState.result == -5) {
                gMemcardState.err = 0x1F;
            } else if (gMemcardState.result == -4) {
                gMemcardState.err = 0x23;
            } else if (gMemcardState.result == -3) {
                gMemcardState.err = 0x24;
            } else if (gMemcardState.result == -2) {
                gMemcardState.err = 0x18;
            } else {
                gMemcardState.err = 0x1C;
            }
            gMemcardState.state = 0;
            gMemcardState.cur = 0;
            gMemcardState.busy = 0;
            break;
        case 10:
            finished_card = &gMemcardState;
            if (SceMcClose(finished_card->fd) == 0) {
                finished_card->state = 0;
                finished_card->cur = 0;
            }
            break;
        }
        break;

    case 17: {
        McChunk_298F00 *chunk;
        ComputeSizedOffset(gCopySetupData.x344 << 11, &chunk);
        StartDiscRead((s32)chunk, gCopySetupData.x340 + gCopySetupData.x32C,
                      gCopySetupData.x344);
        gMemcardState.sub = 18;
        gMemcardState.busy = 0;
        break;
    }

    case 18:
        if (D_001A63AC == 0) {
            McChunk_298F00 *chunk;
            ComputeSizedOffset(D_0014B884 << 11, &chunk);
            gMemcardState.sub = 19;
            gMemcardState.buf = (u8 *)chunk + chunk->x10;
        }
        gMemcardState.busy = 0;
        break;

    case 19:
        if (gMemcardState.card[gMemcardState.cur].x24 != 0) {
            gMemcardState.busy = 0;
            gMemcardState.state = 0;
            gMemcardState.cur = 0;
            gMemcardState.err = 0x2718;
            break;
        }
        if (gMemcardState.card[gMemcardState.cur].status < 0) {
            gMemcardState.busy = 0;
            gMemcardState.state = 0;
            gMemcardState.cur = 0;
            gMemcardState.err = 0x27;
            break;
        }
        gMemcardState.index = 0;
        gMemcardState.sub = 0;
        gMemcardState.state = 20;
    case 20:
        switch (gMemcardState.sub) {
        case 0:
            Sprintf(workspace.name, D_001A79D0, gMemcardState.card[gMemcardState.cur].status);
            if (SceMcOpen(gMemcardState.card[gMemcardState.cur].port, gMemcardState.card[gMemcardState.cur].slot, workspace.name, 2) == 0) {
                gMemcardState.sub = 1;
            }
            break;
        case 1:
            if (gMemcardState.result >= 0) {
                s32 n;

                gMemcardState.fd = gMemcardState.result;
                n = memcard_GetDataSize(D_00256138);
                gMemcardState.size = n + memcard_GetDataSize(D_00256368) * 0x1C + 8;
                if (SceMcWrite(gMemcardState.fd, gMemcardState.buf, gMemcardState.size) == 0) {
                    gMemcardState.sub = 2;
                }
                break;
            }
            gMemcardState.err = 0x2B;
            gMemcardState.err_card = gMemcardState.cur;
            gMemcardState.state = 0;
            gMemcardState.cur = 0;
            gMemcardState.busy = 0;
            break;
        case 2:
            if (gMemcardState.result == gMemcardState.size) {
                if (SceMcClose(gMemcardState.fd) == 0) {
                    gMemcardState.sub = 3;
                }
                break;
            }
            gMemcardState.err_card = gMemcardState.cur;
            if (gMemcardState.result >= 0) {
                gMemcardState.err = 0xB;
                if (SceMcClose(gMemcardState.fd) == 0) {
                    gMemcardState.state = 0;
                    gMemcardState.cur = 0;
                    gMemcardState.busy = 0;
                }
                break;
            }
            if (gMemcardState.result == -4) {
                gMemcardState.err = 0x28;
            } else if (gMemcardState.result == -3) {
                gMemcardState.err = 0x29;
            } else if (gMemcardState.result == -2) {
                gMemcardState.err = 0x2A;
            } else {
                gMemcardState.err = 0x2D;
            }
            gMemcardState.state = 0;
            gMemcardState.cur = 0;
            gMemcardState.busy = 0;
            break;
        case 3:
            if (gMemcardState.result != 0) {
                gMemcardState.err = 0x2C;
                gMemcardState.err_card = gMemcardState.cur;
            }
            gMemcardState.state = 0;
            gMemcardState.cur = 0;
            gMemcardState.busy = 0;
            break;
        }
        break;
    case 24:
        gMemcardState.state = 25;
        gMemcardState.sub = 0;
        gMemcardState.card[gMemcardState.cur].x1C = 1;
    case 25:
        switch (gMemcardState.sub / 5) {
        case 0:
            Sprintf(workspace.name, D_001A99C8, gMemcardState.sub % 5);
            break;
        case 1:
            Sprintf(workspace.name, D_001A99E8, gMemcardState.sub % 5);
            break;
        case 2:
            Sprintf(workspace.name, D_001A9A08, gMemcardState.sub % 5);
            break;
        case 3:
            workspace.name[0] = 0;
            break;
        }
        if ((u8)workspace.name[0] == 0) {
            gMemcardState.state = 0;
            gMemcardState.cur = 0;
            gMemcardState.busy = 0;
            break;
        }

        if (SceMcOpen(gMemcardState.card[gMemcardState.cur].port, gMemcardState.card[gMemcardState.cur].slot,
                          workspace.name, 1) == 0)
            gMemcardState.state = 26;
        break;

    case 26:
        if (gMemcardState.result >= 0) {
            gMemcardState.fd = gMemcardState.result;
            if (SceMcRead(gMemcardState.result, D_001A2BA8, 0x2800) == 0)
                gMemcardState.state = 27;
        } else {
            gMemcardState.state = 25;
            gMemcardState.sub = (gMemcardState.sub / 5 + 1) * 5;
            gMemcardState.busy = 0;
        }
        break;

    case 27:
        if (gMemcardState.result >= 0x2800) {
            if (SceMcClose(gMemcardState.fd) != 0)
                break;
            if (VerifySaveBlockChecksum(D_001A2BB0) != 0) {
                s32 *p = D_001A2BB0 + 2;
                if (*p != -1) {
                    s32 flags = D_001A7A00[8];
                    do {
                        if (p[0] == 0xA) {
                            u8 *b = (u8 *)(p + 2);
                            s32 prev = flags;
                            flags = prev | 0x80;
                            if (b[0xA] != 0) {
                                flags = prev | 0x81;
                                gMemcardState.card[gMemcardState.cur].x1C++;
                            }
                            if (b[0x12] != 0) {
                                flags |= 2;
                                gMemcardState.card[gMemcardState.cur].x1C++;
                            }
                            if (b[0x19] != 0) {
                                flags |= 4;
                                gMemcardState.card[gMemcardState.cur].x1C++;
                            }
                            if (b[0xD] != 0) {
                                flags |= 8;
                                gMemcardState.card[gMemcardState.cur].x1C++;
                            }
                            if (b[0x13] != 0) {
                                flags |= 0x10;
                                gMemcardState.card[gMemcardState.cur].x1C++;
                            }
                            break;
                        }
                        p = (s32 *)((u8 *)p + (((p[1] + 3) / 4) * 4 + 8));
                    } while (*p != -1);
                    D_001A7A00[8] = flags;
                }
            }
            gMemcardState.sub++;
        } else {
            gMemcardState.sub = (gMemcardState.sub / 5 + 1) * 5;
        }
        gMemcardState.state = 25;
        gMemcardState.busy = 0;
        break;
    }
}

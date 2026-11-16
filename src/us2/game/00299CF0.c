/* func_US2_00299CF0 (7,840 bytes, boot + 27 levels): USA v2.00's memory-card state machine,
 * v1.01's func_00298F00 (src/game/00298F00.c, where its notes are) with one constant changed:
 * the directory check accepts 474 or 475 used blocks (blocks - 0x1DA < 2) where v1.01 accepts
 * 475 or 476. The full-card test (>= 0x1DB) is unchanged. Default -G0 profile, no cflags line.
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

extern McState_298F00 g_memcard_state;
extern McDirEntry_298F00 g_memcard_dir_entries[];
extern char g_memcard_save_name[];
extern char g_save_name_source[];
extern char g_save_name_title[];
extern char g_save_name_header[];
extern char g_str_save_icon_normal[];
extern char g_save_name_icon[];
extern char g_str_save_icon_copy[];
extern char g_save_name_data[];
extern char g_str_save_icon_delete[];
extern char g_save_name_format[];
extern s32 g_current_map_index __attribute__((sda));
extern char g_str_memcard_magic_a[];
extern char g_str_memcard_magic_b[];
extern char g_str_memcard_name_format[];
extern char g_str_memcard_name_message[];
extern char g_str_memcard_dir_message[];
extern char g_str_memcard_slot_format_a[];
extern char g_str_memcard_slot_format_b[];
extern char g_str_memcard_slot_format_c[];
extern char g_memcard_save_buffer[];
extern s32 g_memcard_checked_block[];
extern char g_memcard_slot_buffer[];
extern int g_save_record_layout_main[];
extern int g_save_record_layout_slot[];
extern s16 g_sequence_active_flag;
extern s32 g_player_stats[] __attribute__((sda));
extern s32 g_mc_chunk_size_shift;
extern struct { u8 pad[0x32C]; s32 x32C; u8 pad330[0x10]; s32 x340; s32 x344; } g_copy_setup_data;


extern int sceMcSync(int, int *, int *);
extern int sceMcGetInfo(int port, int slot, int *type, int *free, int *format);
extern int func_00127F98(int, int);
extern int sceMcUnformat(int, int);
extern int func_00127E48(int, int, char *, int, int, void *);
extern void *memset(void *, int, int);
extern int func_00115544(const char *, const char *);
extern int func_001158F8(const char *, const char *, int);
extern int sprintf(char *, char *, ...);
extern char *strcpy(char *, const char *);
extern int sceMcOpen(int, int, char *, int);
extern int sceMcRead(int fd, void *buf, int nbyte);
extern int memcard_GetDataSize(int *);
extern int sceMcClose(int);
extern int sceMcMkdir(int, int, char *);
extern int mem_compute_sized_offset(int, void *);
extern int load_start_disc_read(int, int, int);
extern int sceMcWrite(int fd, void *buffer, int size);
extern int sceMcDelete(int port, int slot, char *fname);
extern void STUB_printf(void *, ...);
extern void math_trap_always(void);
extern void FillSaveSlotInfo(char *, int, int);
extern int MemcardRestoreData(char *, int, int *);
extern void save_reset_slot_ids(void);
extern int sceMcSeek(int, int, int);
extern int save_verify_block_checksum(void *);

void mc_update_state_us2(void)
{
    union {
        char name[0x40];
        struct {
            s32 seen[4];
            char name[0x40];
        } directory;
    } workspace;
    McState_298F00 *finished_card;

    if (g_memcard_state.busy) {
        g_memcard_state.busy = sceMcSync(1, &g_memcard_state.cmd, &g_memcard_state.result) == 0;
        return;
    }
    g_memcard_state.busy = 1;

    switch (g_memcard_state.state) {
    case 0:
        if ((u32)g_memcard_state.probe >= 2)
            g_memcard_state.probe = 0;
        if (sceMcGetInfo(g_memcard_state.card[g_memcard_state.probe].port, g_memcard_state.card[g_memcard_state.probe].slot,
                          &g_memcard_state.card[g_memcard_state.probe].type, &g_memcard_state.card[g_memcard_state.probe].free,
                          &g_memcard_state.card[g_memcard_state.probe].format) == 0)
            g_memcard_state.state = 1;
        break;

    case 1:
        if (g_memcard_state.result != 0) {
            g_memcard_state.card[g_memcard_state.probe].status = -4;
            g_memcard_state.card[g_memcard_state.probe].result = g_memcard_state.result;
            g_memcard_state.card[g_memcard_state.probe].x24 = -1;
            g_memcard_state.card[g_memcard_state.probe].used_blocks = 0;
            g_memcard_state.card[g_memcard_state.probe].save[0].x0 = -1;
            g_memcard_state.card[g_memcard_state.probe].save[1].x0 = -1;
            g_memcard_state.card[g_memcard_state.probe].save[2].x0 = -1;
            g_memcard_state.card[g_memcard_state.probe].save[3].x0 = -1;
            g_memcard_state.card[g_memcard_state.probe].x1C = 0;
        }
        if (g_memcard_state.next_card < ++g_memcard_state.probe && g_memcard_state.next_state >= 0) {
            g_memcard_state.state = 2;
            if (g_memcard_state.next_card >= 0) {
                if (g_memcard_state.card[g_memcard_state.next_card].result == 0 || g_memcard_state.next_state == 0x18) {
                    g_memcard_state.cur = g_memcard_state.next_card;
                    g_memcard_state.state = g_memcard_state.next_state;
                    g_memcard_state.err = 0;
                } else {
                    g_memcard_state.err = 0x271A;
                }
            } else {
                g_memcard_state.err = 0x271A;
            }
            g_memcard_state.next_state = -1;
            g_memcard_state.next_card = -1;
            break;
        }
        if (g_memcard_state.probe < 2)
            g_memcard_state.state = 0;
        else
            g_memcard_state.state = 2;
        g_memcard_state.busy = 0;
        break;

    case 2:
        g_memcard_state.retry++;
        if (g_memcard_state.next_state >= 0 || g_memcard_state.retry >= 11) {
            g_memcard_state.retry = 0;
            g_memcard_state.probe = 0;
            g_memcard_state.state = 0;

        }

        g_memcard_state.busy = 0;
        break;

    case 3:
        if (g_memcard_state.card[g_memcard_state.cur].format == 0) {
            if (func_00127F98(g_memcard_state.card[g_memcard_state.cur].port, g_memcard_state.card[g_memcard_state.cur].slot) == 0) {
                g_memcard_state.state = 4;
            }
            break;
        }
        g_memcard_state.busy = 0;
        g_memcard_state.state = 2;
        break;

    case 4:
        if (g_memcard_state.result != 0) {
            g_memcard_state.err = 1;
            g_memcard_state.err_card = g_memcard_state.cur;
        }
        g_memcard_state.state = 0;
        g_memcard_state.cur = 0;
        g_memcard_state.busy = 0;
        break;

    case 5:
        if (g_memcard_state.card[g_memcard_state.cur].format == 0) {
            if (sceMcUnformat(g_memcard_state.card[g_memcard_state.cur].port, g_memcard_state.card[g_memcard_state.cur].slot) == 0) {
                g_memcard_state.state = 6;
            }
            break;
        }
        g_memcard_state.busy = 0;
        g_memcard_state.state = 2;
        break;

    case 6:
        if (g_memcard_state.result != 0) {
            g_memcard_state.err = 2;
            g_memcard_state.err_card = g_memcard_state.cur;
        }
        g_memcard_state.state = 0;
        g_memcard_state.cur = 0;
        g_memcard_state.busy = 0;
        break;

    case 7:
        if (func_00127E48(g_memcard_state.card[g_memcard_state.cur].port, g_memcard_state.card[g_memcard_state.cur].slot,
                          g_save_name_title, 0, 11, g_memcard_dir_entries) == 0) {
            g_memcard_state.sub = 0;
            g_memcard_state.state = 8;
        }
        break;

    case 8:
        switch (g_memcard_state.sub) {
        case 0:
            if (g_memcard_state.result > 0) {
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
                for (i = 0; i < g_memcard_state.result; i++) {
                    McDirEntry_298F00 *entry = &g_memcard_dir_entries[i];
                    char *filename = (char *)((s32)g_memcard_dir_entries + i * 64 + 32);
                    s32 slot;
                    blocks += (entry->size + 1023U) >> 10;
                    if (func_00115544(filename, g_str_save_icon_normal) == 0) icon0 = 1;
                    if (func_00115544(filename, g_str_save_icon_copy) == 0) icon1 = 1;
                    if (func_00115544(filename, g_str_save_icon_delete) == 0) icon2 = 1;
                    if (func_001158F8(filename, g_str_memcard_magic_a, 4) == 0 &&
                        func_001158F8(filename + 5, g_str_memcard_magic_b, 4) == 0) {
                        slot = (u8)entry->name[4] - '0';
                        if (slot < 0) continue;
                        if (slot < 4) workspace.directory.seen[slot] = 1;
                    }
                }
                blocks += (g_memcard_state.result + 2) / 2;
                if ((u32)(blocks - 0x1DA) < 2 && g_memcard_state.result == 9 && icon0 && icon1 && icon2 &&
                    workspace.directory.seen[0] && workspace.directory.seen[1] && workspace.directory.seen[2] && workspace.directory.seen[3]) {
                    g_memcard_state.card[g_memcard_state.cur].used_blocks = 0;
                    g_memcard_state.card[g_memcard_state.cur].status = -1;
                    g_memcard_state.sub = 1;
                    g_memcard_state.busy = 0;
                } else {
                    g_memcard_state.card[g_memcard_state.cur].used_blocks = blocks;
                    g_memcard_state.card[g_memcard_state.cur].status = -2;
                    goto reset_request;
                }
            } else {
                g_memcard_state.card[g_memcard_state.cur].status = -2;
                if (g_memcard_state.result == -2) {
                    g_memcard_state.err = 3;
                    g_memcard_state.err_card = g_memcard_state.cur;
                } else if (g_memcard_state.result >= 0) {
                    g_memcard_state.card[g_memcard_state.cur].status = -2;
                } else if (g_memcard_state.result != -4) {
                    g_memcard_state.err = 4;
                    g_memcard_state.err_card = g_memcard_state.cur;
                }
                g_memcard_state.state = 0;
                g_memcard_state.cur = 0;
                g_memcard_state.busy = 0;
            }
            break;
        case 1:
            sprintf(workspace.directory.name, g_save_name_format, 0);
            if (sceMcOpen(g_memcard_state.card[g_memcard_state.cur].port, g_memcard_state.card[g_memcard_state.cur].slot, workspace.directory.name, 1) == 0) {
                g_memcard_state.sub++;
            }
            break;
        case 2:
            if (g_memcard_state.result >= 0) {
                g_memcard_state.fd = g_memcard_state.result;
                g_memcard_state.sub = 3;
            } else {
                g_memcard_state.card[g_memcard_state.cur].status = -2;
                g_memcard_state.err_card = g_memcard_state.cur;
                if (g_memcard_state.result == -7) {
                    g_memcard_state.err = 0x2710;
                } else if (g_memcard_state.result == -5) {
                    g_memcard_state.err = 0x2711;
                } else if (g_memcard_state.result == -4) {
                    g_memcard_state.err = 0x2712;
                } else if (g_memcard_state.result == -3) {
                    g_memcard_state.err = 0x2713;
                } else if (g_memcard_state.result == -2) {
                    g_memcard_state.err = 3;
                } else {
                    g_memcard_state.err = 4;
                }
                g_memcard_state.state = 0;
                g_memcard_state.cur = 0;
            }
            g_memcard_state.busy = 0;
            break;
        case 3:
            g_memcard_state.size = 8;
            if (sceMcRead(g_memcard_state.fd, &g_memcard_state.card[g_memcard_state.cur].x28, 8) == 0) {
                g_memcard_state.sub = 4;
            }
            break;
        case 4:
            if (g_memcard_state.result == g_memcard_state.size) {
                g_memcard_state.card[g_memcard_state.cur].x24 = 0;
                if (g_memcard_state.card[g_memcard_state.cur].x28 != memcard_GetDataSize(g_save_record_layout_main)) {
                    g_memcard_state.card[g_memcard_state.cur].x24++;
                }
                if (g_memcard_state.card[g_memcard_state.cur].x2C != memcard_GetDataSize(g_save_record_layout_slot)) {
                    g_memcard_state.card[g_memcard_state.cur].x24++;
                }
                g_memcard_state.busy = 0;
                g_memcard_state.sub = 5;
            } else {
                g_memcard_state.card[g_memcard_state.cur].status = -2;
                g_memcard_state.err_card = g_memcard_state.cur;
                if (g_memcard_state.result >= 0) {
                    g_memcard_state.err = 0x2716;
                    if (sceMcClose(g_memcard_state.fd) == 0) {
                        g_memcard_state.state = 0;
                        g_memcard_state.cur = 0;
                        g_memcard_state.busy = 0;
                    }
                    break;
                }
                if (g_memcard_state.result == -5) {
                    g_memcard_state.err = 0x2711;
                } else if (g_memcard_state.result == -4) {
                    g_memcard_state.err = 0x2714;
                } else if (g_memcard_state.result == -3) {
                    g_memcard_state.err = 0x2715;
                } else if (g_memcard_state.result == -2) {
                    g_memcard_state.err = 3;
                } else {
                    g_memcard_state.err = 4;
                }
                g_memcard_state.state = 0;
                g_memcard_state.cur = 0;
                g_memcard_state.busy = 0;
            }
            break;
        case 5:
            if (sceMcClose(g_memcard_state.fd) == 0) {
                g_memcard_state.busy = 0;
                g_memcard_state.state = 21;
            }
            break;
        }
        break;

    case 9:
        g_memcard_state.state = 10;
        g_memcard_state.sub = 0;
        g_memcard_state.card[g_memcard_state.cur].status = 0;
    case 10:
        switch (g_memcard_state.sub) {
        case 0:
            if (g_memcard_state.card[g_memcard_state.cur].free + g_memcard_state.card[g_memcard_state.cur].used_blocks >= 0x1DB) {
                g_memcard_state.sub = 1;
            } else {
                g_memcard_state.err = 7;
                g_memcard_state.err_card = g_memcard_state.cur;
                g_memcard_state.state = 0;
                g_memcard_state.cur = 0;
            }
            g_memcard_state.busy = 0;
            break;
        case 1:
            if (sceMcMkdir(g_memcard_state.card[g_memcard_state.cur].port, g_memcard_state.card[g_memcard_state.cur].slot, g_save_name_source) == 0) {
                g_memcard_state.sub = 2;
            }
            break;
        case 2:
            if (g_memcard_state.result == 0 || g_memcard_state.result == -4) {
                g_memcard_state.sub = 3;
                break;
            }
            g_memcard_state.err_card = g_memcard_state.cur;
            if (g_memcard_state.result == -3) {
                g_memcard_state.err = 7;
            } else if (g_memcard_state.result == -2) {
                g_memcard_state.err = 6;
            } else {
                g_memcard_state.err = 0xD;
            }
            g_memcard_state.state = 0;
            g_memcard_state.cur = 0;
            g_memcard_state.busy = 0;
            break;
        case 3: {
            McChunk_298F00 *chunk;

            mem_compute_sized_offset(g_copy_setup_data.x344 << 11, &chunk);
            load_start_disc_read((s32)chunk, g_copy_setup_data.x340 + g_copy_setup_data.x32C, g_copy_setup_data.x344);
            g_memcard_state.sub = 4;
            g_memcard_state.busy = 0;
            break;
        }
        case 4:
            if (g_sequence_active_flag == 0) {
                g_memcard_state.sub = 5;
            }
            g_memcard_state.busy = 0;
            break;
        case 5:
        case 9:
        case 13:
        case 18:
            switch (g_memcard_state.sub) {
            case 5:
                strcpy(workspace.name, g_save_name_header);
                break;
            case 9:
                strcpy(workspace.name, g_save_name_icon);
                break;
            case 18:
                strcpy(workspace.name, g_save_name_data);
                break;
            case 13:
                sprintf(workspace.name, g_save_name_format, g_memcard_state.card[g_memcard_state.cur].status);
                break;
            }
            if (sceMcOpen(g_memcard_state.card[g_memcard_state.cur].port, g_memcard_state.card[g_memcard_state.cur].slot, workspace.name, 0x203) == 0) {
                g_memcard_state.fd = -1;
                g_memcard_state.sub++;
            }
            break;
        case 6:
        case 10:
        case 14:
        case 19: {
            McChunk_298F00 *chunk;

            if (g_memcard_state.result >= 0) {
                if (g_memcard_state.fd < 0) {
                    g_memcard_state.fd = g_memcard_state.result;
                }
                mem_compute_sized_offset(g_mc_chunk_size_shift << 11, &chunk);
                switch (g_memcard_state.sub) {
                case 6:
                    g_memcard_state.size = 0x3C4;
                    g_memcard_state.buf = (u8 *)chunk + chunk->x0;
                    break;
                case 10:
                    g_memcard_state.size = chunk->xC;
                    g_memcard_state.buf = (u8 *)chunk + chunk->x8;
                    break;
                case 19:
                    g_memcard_state.size = 0xD804;
                    g_memcard_state.buf = &g_current_map_index;
                    break;
                case 14: {
                    s32 n = memcard_GetDataSize(g_save_record_layout_main);
                    g_memcard_state.size = n + memcard_GetDataSize(g_save_record_layout_slot) * 0x1C + 8;
                    g_memcard_state.buf = (u8 *)chunk + chunk->x10;
                    break;
                }
                }
                if (sceMcWrite(g_memcard_state.fd, g_memcard_state.buf, g_memcard_state.size) == 0) {
                    g_memcard_state.sub++;
                }
            } else {
                g_memcard_state.err = 0xA;
                g_memcard_state.err_card = g_memcard_state.cur;
                g_memcard_state.state = 0;
                g_memcard_state.cur = 0;
                g_memcard_state.busy = 0;
            }
            break;
        }
        case 7:
        case 11:
        case 15:
        case 20:
            if (g_memcard_state.result == g_memcard_state.size) {
                if (sceMcClose(g_memcard_state.fd) == 0) {
                    g_memcard_state.sub++;
                }
                break;
            }
            g_memcard_state.err_card = g_memcard_state.cur;
            if (g_memcard_state.result >= 0) {
                finished_card = &g_memcard_state;
                finished_card->err = 0xB;
                if (sceMcClose(finished_card->fd) == 0) {
                    finished_card->busy = 0;
                    goto reset_state;
                }
                break;
            }
            if (g_memcard_state.result == -4) {
                g_memcard_state.err = 8;
            } else if (g_memcard_state.result == -3) {
                g_memcard_state.err = 7;
            } else if (g_memcard_state.result == -2) {
                g_memcard_state.err = 6;
            } else {
                g_memcard_state.err = 0xD;
            }
            g_memcard_state.state = 0;
            g_memcard_state.cur = 0;
            g_memcard_state.busy = 0;
            break;
        case 8:
        case 12:
        case 16:
            if (g_memcard_state.result == 0) {
                g_memcard_state.sub++;
            } else {
                g_memcard_state.err = 0xC;
                g_memcard_state.err_card = g_memcard_state.cur;
                g_memcard_state.state = 0;
                g_memcard_state.cur = 0;
            }
            g_memcard_state.busy = 0;
            break;
        case 17:
            if (++g_memcard_state.card[g_memcard_state.cur].status < 4) {
                g_memcard_state.sub = 13;
            } else {
                g_memcard_state.sub++;
            }
            g_memcard_state.busy = 0;
            break;
        case 21:
            g_memcard_state.card[g_memcard_state.cur].x28 = memcard_GetDataSize(g_save_record_layout_main);
            g_memcard_state.card[g_memcard_state.cur].x2C = memcard_GetDataSize(g_save_record_layout_slot);
            g_memcard_state.card[g_memcard_state.cur].status = -1;
            g_memcard_state.card[g_memcard_state.cur].x24 = 0;
            g_memcard_state.state = 0;
            g_memcard_state.cur = 0;
            break;
        }
        break;

    case 11:
        g_memcard_state.state = 12;
        g_memcard_state.sub = 0;
        g_memcard_state.card[g_memcard_state.cur].status = -2;
    case 12:
        switch (g_memcard_state.sub) {
        case 0:
            if (func_00127E48(g_memcard_state.card[g_memcard_state.cur].port, g_memcard_state.card[g_memcard_state.cur].slot, g_save_name_title, 0, 1, g_memcard_dir_entries) == 0) {
                g_memcard_state.sub = 1;
            }
            break;
        case 1:
            if (g_memcard_state.result == 1) {
                sprintf(workspace.name, g_str_memcard_name_format, g_save_name_source, g_memcard_save_name);
                STUB_printf(g_str_memcard_name_message, workspace.name);
                if (sceMcDelete(g_memcard_state.card[g_memcard_state.cur].port, g_memcard_state.card[g_memcard_state.cur].slot, workspace.name) == 0) {
                    g_memcard_state.sub = 2;
                }
            } else {
                if (g_memcard_state.result == 0) {
                    g_memcard_state.sub = 3;
                } else {
                    g_memcard_state.err_card = g_memcard_state.cur;
                    if (g_memcard_state.result == -5) {
                        g_memcard_state.err = 0x10;
                    } else if (g_memcard_state.result == -4) {
                        g_memcard_state.err = 0xF;
                    } else if (g_memcard_state.result == -2) {
                        g_memcard_state.err = 0xE;
                    } else {
                        g_memcard_state.err = 0x12;
                    }
                    g_memcard_state.state = 0;
                    g_memcard_state.cur = 0;
                }
                g_memcard_state.busy = 0;
            }
            break;
        case 2:
            if (func_00127E48(g_memcard_state.card[g_memcard_state.cur].port, g_memcard_state.card[g_memcard_state.cur].slot, g_save_name_title, 1, 1, g_memcard_dir_entries) == 0) {
                g_memcard_state.sub = 1;
            }
            break;
        case 3:
            if (sceMcDelete(g_memcard_state.card[g_memcard_state.cur].port, g_memcard_state.card[g_memcard_state.cur].slot, g_save_name_source) == 0) {
                STUB_printf(g_str_memcard_dir_message, g_save_name_source);
                g_memcard_state.sub = 4;
            }
            break;
        case 4:
            if (g_memcard_state.result != 0) {
                g_memcard_state.err_card = g_memcard_state.cur;
                if (g_memcard_state.result == -6) {
                    g_memcard_state.err = 0x11;
                } else if (g_memcard_state.result == -5) {
                    g_memcard_state.err = 0x10;
                } else if (g_memcard_state.result == -4) {
                    g_memcard_state.err = 0xF;
                } else if (g_memcard_state.result == -2) {
                    g_memcard_state.err = 0xE;
                } else {
                    g_memcard_state.err = 0x12;
                }
            }
            g_memcard_state.state = 0;
            g_memcard_state.cur = 0;
            g_memcard_state.busy = 0;
            break;
        }
        break;

    case 21:
        g_memcard_state.state = 22;
        g_memcard_state.card[g_memcard_state.cur].tries = -1;
        g_memcard_state.index = 0;
        break;

    case 22:
        g_memcard_state.card[g_memcard_state.cur].tries++;
        if (g_memcard_state.card[g_memcard_state.cur].tries < 4) {
            g_memcard_state.sub = 0;
            g_memcard_state.state = 23;
        } else {
            g_memcard_state.state = 0;
            g_memcard_state.cur = 0;
            g_memcard_state.busy = 0;
        }
        break;
    case 13:
        if (g_memcard_state.card[g_memcard_state.cur].status < 0) {
            g_memcard_state.err = 0x13;
            g_memcard_state.state = 0;
            g_memcard_state.cur = 0;
            g_memcard_state.busy = 0;
            break;
        }
        g_memcard_state.index = 0;
        g_memcard_state.sub = 0;
        g_memcard_state.state = 14;
    case 14:
    case 23:
        switch (g_memcard_state.sub) {
        case 0:
            if (g_memcard_state.state == 23) {
                sprintf(workspace.name, g_save_name_format, g_memcard_state.card[g_memcard_state.cur].tries);
            } else {
                sprintf(workspace.name, g_save_name_format, g_memcard_state.card[g_memcard_state.cur].status);
            }
            if (sceMcOpen(g_memcard_state.card[g_memcard_state.cur].port, g_memcard_state.card[g_memcard_state.cur].slot, workspace.name, 1) == 0) {
                g_memcard_state.sub++;
            }
            break;
        case 1:
            if (g_memcard_state.result >= 0) {
                g_memcard_state.fd = g_memcard_state.result;
                g_memcard_state.sub = 2;
            } else {
                g_memcard_state.err_card = g_memcard_state.cur;
                if (g_memcard_state.result == -7) {
                    g_memcard_state.err = 0x14;
                } else if (g_memcard_state.result == -5) {
                    g_memcard_state.err = 0x15;
                } else if (g_memcard_state.result == -4) {
                    g_memcard_state.err = 0x16;
                } else if (g_memcard_state.result == -3) {
                    g_memcard_state.err = 0x17;
                } else if (g_memcard_state.result == -2) {
                    g_memcard_state.err = 0x18;
                } else {
                    g_memcard_state.err = 0x1C;
                }
                g_memcard_state.state = 0;
                g_memcard_state.cur = 0;
            }
            g_memcard_state.busy = 0;
            break;
        case 2:
            g_memcard_state.size = 8;
            if (sceMcRead(g_memcard_state.fd, &g_memcard_state.card[g_memcard_state.cur].x28, 8) == 0) {
                g_memcard_state.sub = 3;
            }
            break;
        case 3:
            if (g_memcard_state.result == g_memcard_state.size) {
                g_memcard_state.busy = 0;
                g_memcard_state.sub = 4;
                break;
            }
            g_memcard_state.err_card = g_memcard_state.cur;
            if (g_memcard_state.result >= 0) {
                g_memcard_state.err = 0x1B;
                if (sceMcClose(g_memcard_state.fd) == 0) {
                    g_memcard_state.state = 0;
                    g_memcard_state.cur = 0;
                    g_memcard_state.busy = 0;
                }
                break;
            }
            if (g_memcard_state.result == -5) {
                g_memcard_state.err = 0x15;
            } else if (g_memcard_state.result == -4) {
                g_memcard_state.err = 0x19;
            } else if (g_memcard_state.result == -3) {
                g_memcard_state.err = 0x1A;
            } else if (g_memcard_state.result == -2) {
                g_memcard_state.err = 0x18;
            } else {
                g_memcard_state.err = 0x1C;
            }
            g_memcard_state.state = 0;
            g_memcard_state.cur = 0;
            g_memcard_state.busy = 0;
            break;
        case 4:
            g_memcard_state.size = g_memcard_state.card[g_memcard_state.cur].x28;
            if (g_memcard_state.size > 0x2800) {
                math_trap_always();
            }
            if (sceMcRead(g_memcard_state.fd, g_memcard_save_buffer, g_memcard_state.size) == 0) {
                g_memcard_state.sub = 5;
            }
            break;
        case 5:
            if (g_memcard_state.result == g_memcard_state.size) {
                if (g_memcard_state.state == 23) {
                    FillSaveSlotInfo(g_memcard_save_buffer, g_memcard_state.cur, g_memcard_state.card[g_memcard_state.cur].tries);
                    g_memcard_state.sub = 8;
                } else {
                    g_memcard_state.card[g_memcard_state.cur].x24 = MemcardRestoreData(g_memcard_save_buffer, 0, g_save_record_layout_main);
                    g_memcard_state.sub = 6;
                }
                g_memcard_state.busy = 0;
                break;
            }
            g_memcard_state.err_card = g_memcard_state.cur;
            if (g_memcard_state.result >= 0) {
                g_memcard_state.err = 0x1B;
                if (sceMcClose(g_memcard_state.fd) == 0) {
                    g_memcard_state.state = 0;
                    g_memcard_state.cur = 0;
                    g_memcard_state.busy = 0;
                }
                break;
            }
            if (g_memcard_state.result == -5) {
                g_memcard_state.err = 0x15;
            } else if (g_memcard_state.result == -4) {
                g_memcard_state.err = 0x19;
            } else if (g_memcard_state.result == -3) {
                g_memcard_state.err = 0x1A;
            } else if (g_memcard_state.result == -2) {
                g_memcard_state.err = 0x18;
            } else {
                g_memcard_state.err = 0x1C;
            }
            g_memcard_state.state = 0;
            g_memcard_state.cur = 0;
            g_memcard_state.busy = 0;
            break;
        case 6:
            g_memcard_state.size = g_memcard_state.card[g_memcard_state.cur].x2C;
            if (g_memcard_state.size > 0x1000) {
                math_trap_always();
            }
            if (sceMcRead(g_memcard_state.fd, g_memcard_slot_buffer, g_memcard_state.size) == 0) {
                g_memcard_state.sub = 7;
            }
            break;
        case 7:
            if (g_memcard_state.result == g_memcard_state.size) {
                g_memcard_state.card[g_memcard_state.cur].x24 += MemcardRestoreData(g_memcard_slot_buffer, g_memcard_state.index, g_save_record_layout_slot);
                if (++g_memcard_state.index < 0x1C) {
                    g_memcard_state.sub = 6;
                } else {
                    g_memcard_state.sub = 8;
                }
                g_memcard_state.busy = 0;
                break;
            }
            g_memcard_state.err_card = g_memcard_state.cur;
            if (g_memcard_state.result >= 0) {
                g_memcard_state.err = 0x1B;
                if (sceMcClose(g_memcard_state.fd) == 0) {
                    g_memcard_state.state = 0;
                    g_memcard_state.cur = 0;
                    g_memcard_state.busy = 0;
                }
                break;
            }
            if (g_memcard_state.result == -5) {
                g_memcard_state.err = 0x15;
            } else if (g_memcard_state.result == -4) {
                g_memcard_state.err = 0x19;
            } else if (g_memcard_state.result == -3) {
                g_memcard_state.err = 0x1A;
            } else if (g_memcard_state.result == -2) {
                g_memcard_state.err = 0x18;
            } else {
                g_memcard_state.err = 0x1C;
            }
        reset_request:
            g_memcard_state.state = 0;
            g_memcard_state.cur = 0;
            g_memcard_state.busy = 0;
            break;
        case 8:
            if (sceMcClose(g_memcard_state.fd) == 0) {
                if (g_memcard_state.state == 23) {
                    g_memcard_state.busy = 0;
                    g_memcard_state.state = 22;
                } else {
                    finished_card = &g_memcard_state;
                    save_reset_slot_ids();
                    finished_card->state = 0;
                    finished_card->cur = 0;
                }
            }
            break;
        }
        break;

    case 15:
        if (g_memcard_state.card[g_memcard_state.cur].x24 != 0) {
            g_memcard_state.busy = 0;
            g_memcard_state.state = 0;
            g_memcard_state.cur = 0;
            g_memcard_state.err = 0x2717;
            break;
        }
        if (g_memcard_state.card[g_memcard_state.cur].status < 0) {
            g_memcard_state.busy = 0;
            g_memcard_state.state = 0;
            g_memcard_state.cur = 0;
            g_memcard_state.err = 0x1D;
            break;
        }
        g_memcard_state.sub = 0;
        g_memcard_state.state = 16;
    case 16:
        switch (g_memcard_state.sub) {
        case 0:
            sprintf(workspace.name, g_save_name_format, g_memcard_state.card[g_memcard_state.cur].status);
            if (sceMcOpen(g_memcard_state.card[g_memcard_state.cur].port, g_memcard_state.card[g_memcard_state.cur].slot, workspace.name, 2) == 0) {
                g_memcard_state.sub = 1;
            }
            break;
        case 1:
            if (g_memcard_state.result >= 0) {
                g_memcard_state.fd = g_memcard_state.result;
                g_memcard_state.sub = 2;
            } else {
                g_memcard_state.err_card = g_memcard_state.cur;
                if (g_memcard_state.result == -7) {
                    g_memcard_state.err = 0x1E;
                } else if (g_memcard_state.result == -5) {
                    g_memcard_state.err = 0x1F;
                } else if (g_memcard_state.result == -4) {
                    g_memcard_state.err = 0x20;
                } else if (g_memcard_state.result == -3) {
                    g_memcard_state.err = 0x21;
                } else if (g_memcard_state.result == -2) {
                    g_memcard_state.err = 0x22;
                } else {
                    g_memcard_state.err = 0x26;
                }
                g_memcard_state.state = 0;
                g_memcard_state.cur = 0;
            }
            g_memcard_state.busy = 0;
            break;
        case 2:
            if (sceMcSeek(g_memcard_state.fd, 8, 0) == 0) {
                g_memcard_state.sub = 3;
            }
            break;
        case 3:
            if (g_memcard_state.result >= 0) {
                g_memcard_state.sub = 4;
            } else if (sceMcClose(g_memcard_state.fd) == 0) {
                g_memcard_state.err = 0x26;
                g_memcard_state.state = 0;
                g_memcard_state.cur = 0;
                g_memcard_state.busy = 0;
            }
            break;
        case 4:
            if (sceMcWrite(g_memcard_state.fd, g_memcard_save_buffer, memcard_GetDataSize(g_save_record_layout_main)) == 0) {
                g_memcard_state.sub = 5;
            }
            break;
        case 5:
            if (g_memcard_state.result == memcard_GetDataSize(g_save_record_layout_main)) {
                g_memcard_state.sub = 6;
                break;
            }
            g_memcard_state.err_card = g_memcard_state.cur;
            if (g_memcard_state.result >= 0) {
                finished_card = &g_memcard_state;
                finished_card->err = 0x25;
                if (sceMcClose(finished_card->fd) == 0) {
                    finished_card->busy = 0;
                    goto reset_state;
                }
                break;
            }
            if (g_memcard_state.result == -5) {
                g_memcard_state.err = 0x1F;
            } else if (g_memcard_state.result == -4) {
                g_memcard_state.err = 0x23;
            } else if (g_memcard_state.result == -3) {
                g_memcard_state.err = 0x24;
            } else if (g_memcard_state.result == -2) {
                g_memcard_state.err = 0x22;
            } else {
                g_memcard_state.err = 0x26;
            }
            g_memcard_state.state = 0;
            g_memcard_state.cur = 0;
            g_memcard_state.busy = 0;
            break;
        case 6:
            if (sceMcSeek(g_memcard_state.fd, g_memcard_state.card[0].x28 + 8 + g_memcard_state.index * g_memcard_state.card[0].x2C, 0) == 0) {
                g_memcard_state.sub = 7;
            }
            break;
        case 7:
            finished_card = &g_memcard_state;
            if (g_memcard_state.result == g_memcard_state.card[0].x28 + 8 + g_memcard_state.index * g_memcard_state.card[0].x2C) {
                g_memcard_state.sub = 8;
            } else {
                if (sceMcClose(finished_card->fd) == 0) {
                    finished_card->busy = 0;
                    goto reset_state;
                }
            }
            break;
        case 8:
            if (sceMcWrite(g_memcard_state.fd, g_memcard_slot_buffer, memcard_GetDataSize(g_save_record_layout_slot)) == 0) {
                g_memcard_state.sub = 9;
            }
            break;
        case 9:
            if (g_memcard_state.result == memcard_GetDataSize(g_save_record_layout_slot)) {
                g_memcard_state.sub = 10;
                break;
            }
            g_memcard_state.err_card = g_memcard_state.cur;
            if (g_memcard_state.result >= 0) {
                finished_card = &g_memcard_state;
                finished_card->err = 0x25;
                if (sceMcClose(finished_card->fd) == 0) {
                    finished_card->busy = 0;
                reset_state:
                    finished_card->cur = 0;
                    finished_card->state = 0;
                }
                break;
            }
            if (g_memcard_state.result == -5) {
                g_memcard_state.err = 0x1F;
            } else if (g_memcard_state.result == -4) {
                g_memcard_state.err = 0x23;
            } else if (g_memcard_state.result == -3) {
                g_memcard_state.err = 0x24;
            } else if (g_memcard_state.result == -2) {
                g_memcard_state.err = 0x18;
            } else {
                g_memcard_state.err = 0x1C;
            }
            g_memcard_state.state = 0;
            g_memcard_state.cur = 0;
            g_memcard_state.busy = 0;
            break;
        case 10:
            finished_card = &g_memcard_state;
            if (sceMcClose(finished_card->fd) == 0) {
                finished_card->state = 0;
                finished_card->cur = 0;
            }
            break;
        }
        break;

    case 17: {
        McChunk_298F00 *chunk;
        mem_compute_sized_offset(g_copy_setup_data.x344 << 11, &chunk);
        load_start_disc_read((s32)chunk, g_copy_setup_data.x340 + g_copy_setup_data.x32C,
                      g_copy_setup_data.x344);
        g_memcard_state.sub = 18;
        g_memcard_state.busy = 0;
        break;
    }

    case 18:
        if (g_sequence_active_flag == 0) {
            McChunk_298F00 *chunk;
            mem_compute_sized_offset(g_mc_chunk_size_shift << 11, &chunk);
            g_memcard_state.sub = 19;
            g_memcard_state.buf = (u8 *)chunk + chunk->x10;
        }
        g_memcard_state.busy = 0;
        break;

    case 19:
        if (g_memcard_state.card[g_memcard_state.cur].x24 != 0) {
            g_memcard_state.busy = 0;
            g_memcard_state.state = 0;
            g_memcard_state.cur = 0;
            g_memcard_state.err = 0x2718;
            break;
        }
        if (g_memcard_state.card[g_memcard_state.cur].status < 0) {
            g_memcard_state.busy = 0;
            g_memcard_state.state = 0;
            g_memcard_state.cur = 0;
            g_memcard_state.err = 0x27;
            break;
        }
        g_memcard_state.index = 0;
        g_memcard_state.sub = 0;
        g_memcard_state.state = 20;
    case 20:
        switch (g_memcard_state.sub) {
        case 0:
            sprintf(workspace.name, g_save_name_format, g_memcard_state.card[g_memcard_state.cur].status);
            if (sceMcOpen(g_memcard_state.card[g_memcard_state.cur].port, g_memcard_state.card[g_memcard_state.cur].slot, workspace.name, 2) == 0) {
                g_memcard_state.sub = 1;
            }
            break;
        case 1:
            if (g_memcard_state.result >= 0) {
                s32 n;

                g_memcard_state.fd = g_memcard_state.result;
                n = memcard_GetDataSize(g_save_record_layout_main);
                g_memcard_state.size = n + memcard_GetDataSize(g_save_record_layout_slot) * 0x1C + 8;
                if (sceMcWrite(g_memcard_state.fd, g_memcard_state.buf, g_memcard_state.size) == 0) {
                    g_memcard_state.sub = 2;
                }
                break;
            }
            g_memcard_state.err = 0x2B;
            g_memcard_state.err_card = g_memcard_state.cur;
            g_memcard_state.state = 0;
            g_memcard_state.cur = 0;
            g_memcard_state.busy = 0;
            break;
        case 2:
            if (g_memcard_state.result == g_memcard_state.size) {
                if (sceMcClose(g_memcard_state.fd) == 0) {
                    g_memcard_state.sub = 3;
                }
                break;
            }
            g_memcard_state.err_card = g_memcard_state.cur;
            if (g_memcard_state.result >= 0) {
                g_memcard_state.err = 0xB;
                if (sceMcClose(g_memcard_state.fd) == 0) {
                    g_memcard_state.state = 0;
                    g_memcard_state.cur = 0;
                    g_memcard_state.busy = 0;
                }
                break;
            }
            if (g_memcard_state.result == -4) {
                g_memcard_state.err = 0x28;
            } else if (g_memcard_state.result == -3) {
                g_memcard_state.err = 0x29;
            } else if (g_memcard_state.result == -2) {
                g_memcard_state.err = 0x2A;
            } else {
                g_memcard_state.err = 0x2D;
            }
            g_memcard_state.state = 0;
            g_memcard_state.cur = 0;
            g_memcard_state.busy = 0;
            break;
        case 3:
            if (g_memcard_state.result != 0) {
                g_memcard_state.err = 0x2C;
                g_memcard_state.err_card = g_memcard_state.cur;
            }
            g_memcard_state.state = 0;
            g_memcard_state.cur = 0;
            g_memcard_state.busy = 0;
            break;
        }
        break;
    case 24:
        g_memcard_state.state = 25;
        g_memcard_state.sub = 0;
        g_memcard_state.card[g_memcard_state.cur].x1C = 1;
    case 25:
        switch (g_memcard_state.sub / 5) {
        case 0:
            sprintf(workspace.name, g_str_memcard_slot_format_a, g_memcard_state.sub % 5);
            break;
        case 1:
            sprintf(workspace.name, g_str_memcard_slot_format_b, g_memcard_state.sub % 5);
            break;
        case 2:
            sprintf(workspace.name, g_str_memcard_slot_format_c, g_memcard_state.sub % 5);
            break;
        case 3:
            workspace.name[0] = 0;
            break;
        }
        if ((u8)workspace.name[0] == 0) {
            g_memcard_state.state = 0;
            g_memcard_state.cur = 0;
            g_memcard_state.busy = 0;
            break;
        }

        if (sceMcOpen(g_memcard_state.card[g_memcard_state.cur].port, g_memcard_state.card[g_memcard_state.cur].slot,
                          workspace.name, 1) == 0)
            g_memcard_state.state = 26;
        break;

    case 26:
        if (g_memcard_state.result >= 0) {
            g_memcard_state.fd = g_memcard_state.result;
            if (sceMcRead(g_memcard_state.result, g_memcard_save_buffer, 0x2800) == 0)
                g_memcard_state.state = 27;
        } else {
            g_memcard_state.state = 25;
            g_memcard_state.sub = (g_memcard_state.sub / 5 + 1) * 5;
            g_memcard_state.busy = 0;
        }
        break;

    case 27:
        if (g_memcard_state.result >= 0x2800) {
            if (sceMcClose(g_memcard_state.fd) != 0)
                break;
            if (save_verify_block_checksum(g_memcard_checked_block) != 0) {
                s32 *p = g_memcard_checked_block + 2;
                if (*p != -1) {
                    s32 flags = g_player_stats[8];
                    do {
                        if (p[0] == 0xA) {
                            u8 *b = (u8 *)(p + 2);
                            s32 prev = flags;
                            flags = prev | 0x80;
                            if (b[0xA] != 0) {
                                flags = prev | 0x81;
                                g_memcard_state.card[g_memcard_state.cur].x1C++;
                            }
                            if (b[0x12] != 0) {
                                flags |= 2;
                                g_memcard_state.card[g_memcard_state.cur].x1C++;
                            }
                            if (b[0x19] != 0) {
                                flags |= 4;
                                g_memcard_state.card[g_memcard_state.cur].x1C++;
                            }
                            if (b[0xD] != 0) {
                                flags |= 8;
                                g_memcard_state.card[g_memcard_state.cur].x1C++;
                            }
                            if (b[0x13] != 0) {
                                flags |= 0x10;
                                g_memcard_state.card[g_memcard_state.cur].x1C++;
                            }
                            break;
                        }
                        p = (s32 *)((u8 *)p + (((p[1] + 3) / 4) * 4 + 8));
                    } while (*p != -1);
                    g_player_stats[8] = flags;
                }
            }
            g_memcard_state.sub++;
        } else {
            g_memcard_state.sub = (g_memcard_state.sub / 5 + 1) * 5;
        }
        g_memcard_state.state = 25;
        g_memcard_state.busy = 0;
        break;
    }
}

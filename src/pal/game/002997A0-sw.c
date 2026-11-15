#include "include_asm.h"

#include "common.h"
typedef struct McSave_298F00 {
    s32 x0;
    u8 pad4[0x18];
} McSave_298F00;
typedef struct McCard_298F00 {
    s32 port;            
    s32 slot;            
    s32 type;            
    s32 free;            
    s32 result;          
    s32 format;          
    s16 status;          
    s16 tries;           
    s32 x1C;             
    s32 used_blocks;     
    s32 x24;             
    s32 x28;             
    s32 x2C;             
    McSave_298F00 save[4];  
} McCard_298F00;
typedef struct McState_298F00 {
    McCard_298F00 card[2];  
    s32 cmd;             
    s32 result;          
    s32 x148;
    s32 cur;             
    s32 index;           
    s32 busy;            
    s32 fd;              
    s32 state;           
    s32 sub;             
    s32 next_state;      
    s32 next_card;       
    s32 err;             
    s32 err_card;        
    void *buf;           
    s32 size;            
    s32 x17C;
    s32 probe;           
    s32 retry;           
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
extern s32 g_current_map_index __attribute__((sda));
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
extern struct { u8 pad[0x32C]; s32 x32C; u8 pad330[0x10]; s32 x340; s32 x344; } g_copy_setup_data;
extern int sceMcSync(int, int *, int *);
extern int sceMcGetInfo(int port, int slot, int *type, int *free, int *format);
extern int sceMcFormat(int, int);
extern int sceMcUnformat(int, int);
extern int sceMcSetFileInfo(int, int, char *, int, int, void *);
extern int memset(void *, int, int);
extern int func_00115544(const char *, const char *);
extern int func_001158F8(const char *, const char *, int);
extern int sprintf(char *, char *, ...);
extern int strcpy(char *, const char *);
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

void func_PAL_00299898(void)
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
            if (sceMcFormat(g_memcard_state.card[g_memcard_state.cur].port, g_memcard_state.card[g_memcard_state.cur].slot) == 0) {
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
        if (sceMcSetFileInfo(g_memcard_state.card[g_memcard_state.cur].port, g_memcard_state.card[g_memcard_state.cur].slot,
                          D_001A7948, 0, 11, D_001C5280) == 0) {
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
                    McDirEntry_298F00 *entry = &D_001C5280[i];
                    char *filename = (char *)((s32)D_001C5280 + i * 64 + 32);
                    s32 slot;
                    blocks += (entry->size + 1023U) >> 10;
                    if (func_00115544(filename, D_001A7975) == 0) icon0 = 1;
                    if (func_00115544(filename, D_001A7995) == 0) icon1 = 1;
                    if (func_00115544(filename, D_001A79B5) == 0) icon2 = 1;
                    if (func_001158F8(filename, D_001A9988, 4) == 0 &&
                        func_001158F8(filename + 5, D_001A9990, 4) == 0) {
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
            sprintf(workspace.directory.name, D_001A79D0, 0);
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
                if (g_memcard_state.card[g_memcard_state.cur].x28 != memcard_GetDataSize(D_00256138)) {
                    g_memcard_state.card[g_memcard_state.cur].x24++;
                }
                if (g_memcard_state.card[g_memcard_state.cur].x2C != memcard_GetDataSize(D_00256368)) {
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
            if (sceMcMkdir(g_memcard_state.card[g_memcard_state.cur].port, g_memcard_state.card[g_memcard_state.cur].slot, D_001A7930) == 0) {
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
            if (D_001A63AC == 0) {
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
                strcpy(workspace.name, D_001A7960);
                break;
            case 9:
                strcpy(workspace.name, D_001A7980);
                break;
            case 18:
                strcpy(workspace.name, D_001A79A0);
                break;
            case 13:
                sprintf(workspace.name, D_001A79D0, g_memcard_state.card[g_memcard_state.cur].status);
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
                mem_compute_sized_offset(D_0014B884 << 11, &chunk);
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
                    g_memcard_state.size = 0xD800;
                    g_memcard_state.buf = &g_current_map_index;
                    break;
                case 14: {
                    s32 n = memcard_GetDataSize(D_00256138);
                    g_memcard_state.size = n + memcard_GetDataSize(D_00256368) * 0x1C + 8;
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
            g_memcard_state.card[g_memcard_state.cur].x28 = memcard_GetDataSize(D_00256138);
            g_memcard_state.card[g_memcard_state.cur].x2C = memcard_GetDataSize(D_00256368);
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
            if (sceMcSetFileInfo(g_memcard_state.card[g_memcard_state.cur].port, g_memcard_state.card[g_memcard_state.cur].slot, D_001A7948, 0, 1, D_001C5280) == 0) {
                g_memcard_state.sub = 1;
            }
            break;
        case 1:
            if (g_memcard_state.result == 1) {
                sprintf(workspace.name, D_001A9998, D_001A7930, D_001C52A0);
                STUB_printf(D_001A99A0, workspace.name);
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
            if (sceMcSetFileInfo(g_memcard_state.card[g_memcard_state.cur].port, g_memcard_state.card[g_memcard_state.cur].slot, D_001A7948, 1, 1, D_001C5280) == 0) {
                g_memcard_state.sub = 1;
            }
            break;
        case 3:
            if (sceMcDelete(g_memcard_state.card[g_memcard_state.cur].port, g_memcard_state.card[g_memcard_state.cur].slot, D_001A7930) == 0) {
                STUB_printf(D_001A99B0, D_001A7930);
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
                sprintf(workspace.name, D_001A79D0, g_memcard_state.card[g_memcard_state.cur].tries);
            } else {
                sprintf(workspace.name, D_001A79D0, g_memcard_state.card[g_memcard_state.cur].status);
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
            if (sceMcRead(g_memcard_state.fd, D_001A2BA8, g_memcard_state.size) == 0) {
                g_memcard_state.sub = 5;
            }
            break;
        case 5:
            if (g_memcard_state.result == g_memcard_state.size) {
                if (g_memcard_state.state == 23) {
                    FillSaveSlotInfo(D_001A2BA8, g_memcard_state.cur, g_memcard_state.card[g_memcard_state.cur].tries);
                    g_memcard_state.sub = 8;
                } else {
                    g_memcard_state.card[g_memcard_state.cur].x24 = MemcardRestoreData(D_001A2BA8, 0, D_00256138);
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
            if (sceMcRead(g_memcard_state.fd, D_001A53A8, g_memcard_state.size) == 0) {
                g_memcard_state.sub = 7;
            }
            break;
        case 7:
            if (g_memcard_state.result == g_memcard_state.size) {
                g_memcard_state.card[g_memcard_state.cur].x24 += MemcardRestoreData(D_001A53A8, g_memcard_state.index, D_00256368);
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
            sprintf(workspace.name, D_001A79D0, g_memcard_state.card[g_memcard_state.cur].status);
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
            if (sceMcWrite(g_memcard_state.fd, D_001A2BA8, memcard_GetDataSize(D_00256138)) == 0) {
                g_memcard_state.sub = 5;
            }
            break;
        case 5:
            if (g_memcard_state.result == memcard_GetDataSize(D_00256138)) {
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
            if (sceMcWrite(g_memcard_state.fd, D_001A53A8, memcard_GetDataSize(D_00256368)) == 0) {
                g_memcard_state.sub = 9;
            }
            break;
        case 9:
            if (g_memcard_state.result == memcard_GetDataSize(D_00256368)) {
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
        if (D_001A63AC == 0) {
            McChunk_298F00 *chunk;
            mem_compute_sized_offset(D_0014B884 << 11, &chunk);
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
            sprintf(workspace.name, D_001A79D0, g_memcard_state.card[g_memcard_state.cur].status);
            if (sceMcOpen(g_memcard_state.card[g_memcard_state.cur].port, g_memcard_state.card[g_memcard_state.cur].slot, workspace.name, 2) == 0) {
                g_memcard_state.sub = 1;
            }
            break;
        case 1:
            if (g_memcard_state.result >= 0) {
                s32 n;

                g_memcard_state.fd = g_memcard_state.result;
                n = memcard_GetDataSize(D_00256138);
                g_memcard_state.size = n + memcard_GetDataSize(D_00256368) * 0x1C + 8;
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
            sprintf(workspace.name, D_001A99C8, g_memcard_state.sub % 5);
            break;
        case 1:
            sprintf(workspace.name, D_001A99E8, g_memcard_state.sub % 5);
            break;
        case 2:
            sprintf(workspace.name, D_001A9A08, g_memcard_state.sub % 5);
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
            if (sceMcRead(g_memcard_state.result, D_001A2BA8, 0x2800) == 0)
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
            if (save_verify_block_checksum(D_001A2BB0) != 0) {
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
                    D_001A7A00[8] = flags;
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

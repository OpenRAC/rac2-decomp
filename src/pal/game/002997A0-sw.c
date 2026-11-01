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
extern int func_00127F90(int, int);
extern int func_00128180(int, int);
extern int func_00127E40(int, int, char *, int, int, void *);
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

    if (D_001393E0.busy) {
        D_001393E0.busy = func_00127B88(1, &D_001393E0.cmd, &D_001393E0.result) == 0;
        return;
    }
    D_001393E0.busy = 1;

    switch (D_001393E0.state) {
    case 0:
        if ((u32)D_001393E0.probe >= 2)
            D_001393E0.probe = 0;
        if (func_00127CC0(D_001393E0.card[D_001393E0.probe].port, D_001393E0.card[D_001393E0.probe].slot,
                          &D_001393E0.card[D_001393E0.probe].type, &D_001393E0.card[D_001393E0.probe].free,
                          &D_001393E0.card[D_001393E0.probe].format) == 0)
            D_001393E0.state = 1;
        break;

    case 1:
        if (D_001393E0.result != 0) {
            D_001393E0.card[D_001393E0.probe].status = -4;
            D_001393E0.card[D_001393E0.probe].result = D_001393E0.result;
            D_001393E0.card[D_001393E0.probe].x24 = -1;
            D_001393E0.card[D_001393E0.probe].used_blocks = 0;
            D_001393E0.card[D_001393E0.probe].save[0].x0 = -1;
            D_001393E0.card[D_001393E0.probe].save[1].x0 = -1;
            D_001393E0.card[D_001393E0.probe].save[2].x0 = -1;
            D_001393E0.card[D_001393E0.probe].save[3].x0 = -1;
            D_001393E0.card[D_001393E0.probe].x1C = 0;
        }
        if (D_001393E0.next_card < ++D_001393E0.probe && D_001393E0.next_state >= 0) {
            D_001393E0.state = 2;
            if (D_001393E0.next_card >= 0) {
                if (D_001393E0.card[D_001393E0.next_card].result == 0 || D_001393E0.next_state == 0x18) {
                    D_001393E0.cur = D_001393E0.next_card;
                    D_001393E0.state = D_001393E0.next_state;
                    D_001393E0.err = 0;
                } else {
                    D_001393E0.err = 0x271A;
                }
            } else {
                D_001393E0.err = 0x271A;
            }
            D_001393E0.next_state = -1;
            D_001393E0.next_card = -1;
            break;
        }
        if (D_001393E0.probe < 2)
            D_001393E0.state = 0;
        else
            D_001393E0.state = 2;
        D_001393E0.busy = 0;
        break;

    case 2:
        D_001393E0.retry++;
        if (D_001393E0.next_state >= 0 || D_001393E0.retry >= 11) {
            D_001393E0.retry = 0;
            D_001393E0.probe = 0;
            D_001393E0.state = 0;

        }

        D_001393E0.busy = 0;
        break;

    case 3:
        if (D_001393E0.card[D_001393E0.cur].format == 0) {
            if (func_00127F90(D_001393E0.card[D_001393E0.cur].port, D_001393E0.card[D_001393E0.cur].slot) == 0) {
                D_001393E0.state = 4;
            }
            break;
        }
        D_001393E0.busy = 0;
        D_001393E0.state = 2;
        break;

    case 4:
        if (D_001393E0.result != 0) {
            D_001393E0.err = 1;
            D_001393E0.err_card = D_001393E0.cur;
        }
        D_001393E0.state = 0;
        D_001393E0.cur = 0;
        D_001393E0.busy = 0;
        break;

    case 5:
        if (D_001393E0.card[D_001393E0.cur].format == 0) {
            if (func_00128180(D_001393E0.card[D_001393E0.cur].port, D_001393E0.card[D_001393E0.cur].slot) == 0) {
                D_001393E0.state = 6;
            }
            break;
        }
        D_001393E0.busy = 0;
        D_001393E0.state = 2;
        break;

    case 6:
        if (D_001393E0.result != 0) {
            D_001393E0.err = 2;
            D_001393E0.err_card = D_001393E0.cur;
        }
        D_001393E0.state = 0;
        D_001393E0.cur = 0;
        D_001393E0.busy = 0;
        break;

    case 7:
        if (func_00127E40(D_001393E0.card[D_001393E0.cur].port, D_001393E0.card[D_001393E0.cur].slot,
                          D_001A7948, 0, 11, D_001C5280) == 0) {
            D_001393E0.sub = 0;
            D_001393E0.state = 8;
        }
        break;

    case 8:
        switch (D_001393E0.sub) {
        case 0:
            if (D_001393E0.result > 0) {
                s32 icon0;
                s32 icon1;
                s32 icon2;
                s32 i;
                s32 blocks;
                icon0 = 0;
                func_00115484(workspace.directory.seen, 0, 16);
                icon1 = 0;
                icon2 = 0;
                blocks = 0;
                for (i = 0; i < D_001393E0.result; i++) {
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
                blocks += (D_001393E0.result + 2) / 2;
                if ((u32)(blocks - 0x1DA) < 2 && D_001393E0.result == 9 && icon0 && icon1 && icon2 &&
                    workspace.directory.seen[0] && workspace.directory.seen[1] && workspace.directory.seen[2] && workspace.directory.seen[3]) {
                    D_001393E0.card[D_001393E0.cur].used_blocks = 0;
                    D_001393E0.card[D_001393E0.cur].status = -1;
                    D_001393E0.sub = 1;
                    D_001393E0.busy = 0;
                } else {
                    D_001393E0.card[D_001393E0.cur].used_blocks = blocks;
                    D_001393E0.card[D_001393E0.cur].status = -2;
                    goto reset_request;
                }
            } else {
                D_001393E0.card[D_001393E0.cur].status = -2;
                if (D_001393E0.result == -2) {
                    D_001393E0.err = 3;
                    D_001393E0.err_card = D_001393E0.cur;
                } else if (D_001393E0.result >= 0) {
                    D_001393E0.card[D_001393E0.cur].status = -2;
                } else if (D_001393E0.result != -4) {
                    D_001393E0.err = 4;
                    D_001393E0.err_card = D_001393E0.cur;
                }
                D_001393E0.state = 0;
                D_001393E0.cur = 0;
                D_001393E0.busy = 0;
            }
            break;
        case 1:
            func_00115DA8(workspace.directory.name, D_001A79D0, 0);
            if (func_00127508(D_001393E0.card[D_001393E0.cur].port, D_001393E0.card[D_001393E0.cur].slot, workspace.directory.name, 1) == 0) {
                D_001393E0.sub++;
            }
            break;
        case 2:
            if (D_001393E0.result >= 0) {
                D_001393E0.fd = D_001393E0.result;
                D_001393E0.sub = 3;
            } else {
                D_001393E0.card[D_001393E0.cur].status = -2;
                D_001393E0.err_card = D_001393E0.cur;
                if (D_001393E0.result == -7) {
                    D_001393E0.err = 0x2710;
                } else if (D_001393E0.result == -5) {
                    D_001393E0.err = 0x2711;
                } else if (D_001393E0.result == -4) {
                    D_001393E0.err = 0x2712;
                } else if (D_001393E0.result == -3) {
                    D_001393E0.err = 0x2713;
                } else if (D_001393E0.result == -2) {
                    D_001393E0.err = 3;
                } else {
                    D_001393E0.err = 4;
                }
                D_001393E0.state = 0;
                D_001393E0.cur = 0;
            }
            D_001393E0.busy = 0;
            break;
        case 3:
            D_001393E0.size = 8;
            if (func_00127888(D_001393E0.fd, &D_001393E0.card[D_001393E0.cur].x28, 8) == 0) {
                D_001393E0.sub = 4;
            }
            break;
        case 4:
            if (D_001393E0.result == D_001393E0.size) {
                D_001393E0.card[D_001393E0.cur].x24 = 0;
                if (D_001393E0.card[D_001393E0.cur].x28 != func_0029AE78(D_00256138)) {
                    D_001393E0.card[D_001393E0.cur].x24++;
                }
                if (D_001393E0.card[D_001393E0.cur].x2C != func_0029AE78(D_00256368)) {
                    D_001393E0.card[D_001393E0.cur].x24++;
                }
                D_001393E0.busy = 0;
                D_001393E0.sub = 5;
            } else {
                D_001393E0.card[D_001393E0.cur].status = -2;
                D_001393E0.err_card = D_001393E0.cur;
                if (D_001393E0.result >= 0) {
                    D_001393E0.err = 0x2716;
                    if (func_00127668(D_001393E0.fd) == 0) {
                        D_001393E0.state = 0;
                        D_001393E0.cur = 0;
                        D_001393E0.busy = 0;
                    }
                    break;
                }
                if (D_001393E0.result == -5) {
                    D_001393E0.err = 0x2711;
                } else if (D_001393E0.result == -4) {
                    D_001393E0.err = 0x2714;
                } else if (D_001393E0.result == -3) {
                    D_001393E0.err = 0x2715;
                } else if (D_001393E0.result == -2) {
                    D_001393E0.err = 3;
                } else {
                    D_001393E0.err = 4;
                }
                D_001393E0.state = 0;
                D_001393E0.cur = 0;
                D_001393E0.busy = 0;
            }
            break;
        case 5:
            if (func_00127668(D_001393E0.fd) == 0) {
                D_001393E0.busy = 0;
                D_001393E0.state = 21;
            }
            break;
        }
        break;

    case 9:
        D_001393E0.state = 10;
        D_001393E0.sub = 0;
        D_001393E0.card[D_001393E0.cur].status = 0;
    case 10:
        switch (D_001393E0.sub) {
        case 0:
            if (D_001393E0.card[D_001393E0.cur].free + D_001393E0.card[D_001393E0.cur].used_blocks >= 0x1DB) {
                D_001393E0.sub = 1;
            } else {
                D_001393E0.err = 7;
                D_001393E0.err_card = D_001393E0.cur;
                D_001393E0.state = 0;
                D_001393E0.cur = 0;
            }
            D_001393E0.busy = 0;
            break;
        case 1:
            if (func_00127630(D_001393E0.card[D_001393E0.cur].port, D_001393E0.card[D_001393E0.cur].slot, D_001A7930) == 0) {
                D_001393E0.sub = 2;
            }
            break;
        case 2:
            if (D_001393E0.result == 0 || D_001393E0.result == -4) {
                D_001393E0.sub = 3;
                break;
            }
            D_001393E0.err_card = D_001393E0.cur;
            if (D_001393E0.result == -3) {
                D_001393E0.err = 7;
            } else if (D_001393E0.result == -2) {
                D_001393E0.err = 6;
            } else {
                D_001393E0.err = 0xD;
            }
            D_001393E0.state = 0;
            D_001393E0.cur = 0;
            D_001393E0.busy = 0;
            break;
        case 3: {
            McChunk_298F00 *chunk;

            func_00288970(D_0014B540.x344 << 11, &chunk);
            func_002B7B18((s32)chunk, D_0014B540.x340 + D_0014B540.x32C, D_0014B540.x344);
            D_001393E0.sub = 4;
            D_001393E0.busy = 0;
            break;
        }
        case 4:
            if (D_001A63AC == 0) {
                D_001393E0.sub = 5;
            }
            D_001393E0.busy = 0;
            break;
        case 5:
        case 9:
        case 13:
        case 18:
            switch (D_001393E0.sub) {
            case 5:
                func_00115690(workspace.name, D_001A7960);
                break;
            case 9:
                func_00115690(workspace.name, D_001A7980);
                break;
            case 18:
                func_00115690(workspace.name, D_001A79A0);
                break;
            case 13:
                func_00115DA8(workspace.name, D_001A79D0, D_001393E0.card[D_001393E0.cur].status);
                break;
            }
            if (func_00127508(D_001393E0.card[D_001393E0.cur].port, D_001393E0.card[D_001393E0.cur].slot, workspace.name, 0x203) == 0) {
                D_001393E0.fd = -1;
                D_001393E0.sub++;
            }
            break;
        case 6:
        case 10:
        case 14:
        case 19: {
            McChunk_298F00 *chunk;

            if (D_001393E0.result >= 0) {
                if (D_001393E0.fd < 0) {
                    D_001393E0.fd = D_001393E0.result;
                }
                func_00288970(D_0014B884 << 11, &chunk);
                switch (D_001393E0.sub) {
                case 6:
                    D_001393E0.size = 0x3C4;
                    D_001393E0.buf = (u8 *)chunk + chunk->x0;
                    break;
                case 10:
                    D_001393E0.size = chunk->xC;
                    D_001393E0.buf = (u8 *)chunk + chunk->x8;
                    break;
                case 19:
                    D_001393E0.size = 0xD800;
                    D_001393E0.buf = &D_001A79F0;
                    break;
                case 14: {
                    s32 n = func_0029AE78(D_00256138);
                    D_001393E0.size = n + func_0029AE78(D_00256368) * 0x1C + 8;
                    D_001393E0.buf = (u8 *)chunk + chunk->x10;
                    break;
                }
                }
                if (func_001279A0(D_001393E0.fd, D_001393E0.buf, D_001393E0.size) == 0) {
                    D_001393E0.sub++;
                }
            } else {
                D_001393E0.err = 0xA;
                D_001393E0.err_card = D_001393E0.cur;
                D_001393E0.state = 0;
                D_001393E0.cur = 0;
                D_001393E0.busy = 0;
            }
            break;
        }
        case 7:
        case 11:
        case 15:
        case 20:
            if (D_001393E0.result == D_001393E0.size) {
                if (func_00127668(D_001393E0.fd) == 0) {
                    D_001393E0.sub++;
                }
                break;
            }
            D_001393E0.err_card = D_001393E0.cur;
            if (D_001393E0.result >= 0) {
                finished_card = &D_001393E0;
                finished_card->err = 0xB;
                if (func_00127668(finished_card->fd) == 0) {
                    finished_card->busy = 0;
                    goto reset_state;
                }
                break;
            }
            if (D_001393E0.result == -4) {
                D_001393E0.err = 8;
            } else if (D_001393E0.result == -3) {
                D_001393E0.err = 7;
            } else if (D_001393E0.result == -2) {
                D_001393E0.err = 6;
            } else {
                D_001393E0.err = 0xD;
            }
            D_001393E0.state = 0;
            D_001393E0.cur = 0;
            D_001393E0.busy = 0;
            break;
        case 8:
        case 12:
        case 16:
            if (D_001393E0.result == 0) {
                D_001393E0.sub++;
            } else {
                D_001393E0.err = 0xC;
                D_001393E0.err_card = D_001393E0.cur;
                D_001393E0.state = 0;
                D_001393E0.cur = 0;
            }
            D_001393E0.busy = 0;
            break;
        case 17:
            if (++D_001393E0.card[D_001393E0.cur].status < 4) {
                D_001393E0.sub = 13;
            } else {
                D_001393E0.sub++;
            }
            D_001393E0.busy = 0;
            break;
        case 21:
            D_001393E0.card[D_001393E0.cur].x28 = func_0029AE78(D_00256138);
            D_001393E0.card[D_001393E0.cur].x2C = func_0029AE78(D_00256368);
            D_001393E0.card[D_001393E0.cur].status = -1;
            D_001393E0.card[D_001393E0.cur].x24 = 0;
            D_001393E0.state = 0;
            D_001393E0.cur = 0;
            break;
        }
        break;

    case 11:
        D_001393E0.state = 12;
        D_001393E0.sub = 0;
        D_001393E0.card[D_001393E0.cur].status = -2;
    case 12:
        switch (D_001393E0.sub) {
        case 0:
            if (func_00127E40(D_001393E0.card[D_001393E0.cur].port, D_001393E0.card[D_001393E0.cur].slot, D_001A7948, 0, 1, D_001C5280) == 0) {
                D_001393E0.sub = 1;
            }
            break;
        case 1:
            if (D_001393E0.result == 1) {
                func_00115DA8(workspace.name, D_001A9998, D_001A7930, D_001C52A0);
                func_0026FEB8(D_001A99A0, workspace.name);
                if (func_00128068(D_001393E0.card[D_001393E0.cur].port, D_001393E0.card[D_001393E0.cur].slot, workspace.name) == 0) {
                    D_001393E0.sub = 2;
                }
            } else {
                if (D_001393E0.result == 0) {
                    D_001393E0.sub = 3;
                } else {
                    D_001393E0.err_card = D_001393E0.cur;
                    if (D_001393E0.result == -5) {
                        D_001393E0.err = 0x10;
                    } else if (D_001393E0.result == -4) {
                        D_001393E0.err = 0xF;
                    } else if (D_001393E0.result == -2) {
                        D_001393E0.err = 0xE;
                    } else {
                        D_001393E0.err = 0x12;
                    }
                    D_001393E0.state = 0;
                    D_001393E0.cur = 0;
                }
                D_001393E0.busy = 0;
            }
            break;
        case 2:
            if (func_00127E40(D_001393E0.card[D_001393E0.cur].port, D_001393E0.card[D_001393E0.cur].slot, D_001A7948, 1, 1, D_001C5280) == 0) {
                D_001393E0.sub = 1;
            }
            break;
        case 3:
            if (func_00128068(D_001393E0.card[D_001393E0.cur].port, D_001393E0.card[D_001393E0.cur].slot, D_001A7930) == 0) {
                func_0026FEB8(D_001A99B0, D_001A7930);
                D_001393E0.sub = 4;
            }
            break;
        case 4:
            if (D_001393E0.result != 0) {
                D_001393E0.err_card = D_001393E0.cur;
                if (D_001393E0.result == -6) {
                    D_001393E0.err = 0x11;
                } else if (D_001393E0.result == -5) {
                    D_001393E0.err = 0x10;
                } else if (D_001393E0.result == -4) {
                    D_001393E0.err = 0xF;
                } else if (D_001393E0.result == -2) {
                    D_001393E0.err = 0xE;
                } else {
                    D_001393E0.err = 0x12;
                }
            }
            D_001393E0.state = 0;
            D_001393E0.cur = 0;
            D_001393E0.busy = 0;
            break;
        }
        break;

    case 21:
        D_001393E0.state = 22;
        D_001393E0.card[D_001393E0.cur].tries = -1;
        D_001393E0.index = 0;
        break;

    case 22:
        D_001393E0.card[D_001393E0.cur].tries++;
        if (D_001393E0.card[D_001393E0.cur].tries < 4) {
            D_001393E0.sub = 0;
            D_001393E0.state = 23;
        } else {
            D_001393E0.state = 0;
            D_001393E0.cur = 0;
            D_001393E0.busy = 0;
        }
        break;
    case 13:
        if (D_001393E0.card[D_001393E0.cur].status < 0) {
            D_001393E0.err = 0x13;
            D_001393E0.state = 0;
            D_001393E0.cur = 0;
            D_001393E0.busy = 0;
            break;
        }
        D_001393E0.index = 0;
        D_001393E0.sub = 0;
        D_001393E0.state = 14;
    case 14:
    case 23:
        switch (D_001393E0.sub) {
        case 0:
            if (D_001393E0.state == 23) {
                func_00115DA8(workspace.name, D_001A79D0, D_001393E0.card[D_001393E0.cur].tries);
            } else {
                func_00115DA8(workspace.name, D_001A79D0, D_001393E0.card[D_001393E0.cur].status);
            }
            if (func_00127508(D_001393E0.card[D_001393E0.cur].port, D_001393E0.card[D_001393E0.cur].slot, workspace.name, 1) == 0) {
                D_001393E0.sub++;
            }
            break;
        case 1:
            if (D_001393E0.result >= 0) {
                D_001393E0.fd = D_001393E0.result;
                D_001393E0.sub = 2;
            } else {
                D_001393E0.err_card = D_001393E0.cur;
                if (D_001393E0.result == -7) {
                    D_001393E0.err = 0x14;
                } else if (D_001393E0.result == -5) {
                    D_001393E0.err = 0x15;
                } else if (D_001393E0.result == -4) {
                    D_001393E0.err = 0x16;
                } else if (D_001393E0.result == -3) {
                    D_001393E0.err = 0x17;
                } else if (D_001393E0.result == -2) {
                    D_001393E0.err = 0x18;
                } else {
                    D_001393E0.err = 0x1C;
                }
                D_001393E0.state = 0;
                D_001393E0.cur = 0;
            }
            D_001393E0.busy = 0;
            break;
        case 2:
            D_001393E0.size = 8;
            if (func_00127888(D_001393E0.fd, &D_001393E0.card[D_001393E0.cur].x28, 8) == 0) {
                D_001393E0.sub = 3;
            }
            break;
        case 3:
            if (D_001393E0.result == D_001393E0.size) {
                D_001393E0.busy = 0;
                D_001393E0.sub = 4;
                break;
            }
            D_001393E0.err_card = D_001393E0.cur;
            if (D_001393E0.result >= 0) {
                D_001393E0.err = 0x1B;
                if (func_00127668(D_001393E0.fd) == 0) {
                    D_001393E0.state = 0;
                    D_001393E0.cur = 0;
                    D_001393E0.busy = 0;
                }
                break;
            }
            if (D_001393E0.result == -5) {
                D_001393E0.err = 0x15;
            } else if (D_001393E0.result == -4) {
                D_001393E0.err = 0x19;
            } else if (D_001393E0.result == -3) {
                D_001393E0.err = 0x1A;
            } else if (D_001393E0.result == -2) {
                D_001393E0.err = 0x18;
            } else {
                D_001393E0.err = 0x1C;
            }
            D_001393E0.state = 0;
            D_001393E0.cur = 0;
            D_001393E0.busy = 0;
            break;
        case 4:
            D_001393E0.size = D_001393E0.card[D_001393E0.cur].x28;
            if (D_001393E0.size > 0x2800) {
                func_00282A28();
            }
            if (func_00127888(D_001393E0.fd, D_001A2BA8, D_001393E0.size) == 0) {
                D_001393E0.sub = 5;
            }
            break;
        case 5:
            if (D_001393E0.result == D_001393E0.size) {
                if (D_001393E0.state == 23) {
                    func_0029B0B0(D_001A2BA8, D_001393E0.cur, D_001393E0.card[D_001393E0.cur].tries);
                    D_001393E0.sub = 8;
                } else {
                    D_001393E0.card[D_001393E0.cur].x24 = func_0029B168(D_001A2BA8, 0, D_00256138);
                    D_001393E0.sub = 6;
                }
                D_001393E0.busy = 0;
                break;
            }
            D_001393E0.err_card = D_001393E0.cur;
            if (D_001393E0.result >= 0) {
                D_001393E0.err = 0x1B;
                if (func_00127668(D_001393E0.fd) == 0) {
                    D_001393E0.state = 0;
                    D_001393E0.cur = 0;
                    D_001393E0.busy = 0;
                }
                break;
            }
            if (D_001393E0.result == -5) {
                D_001393E0.err = 0x15;
            } else if (D_001393E0.result == -4) {
                D_001393E0.err = 0x19;
            } else if (D_001393E0.result == -3) {
                D_001393E0.err = 0x1A;
            } else if (D_001393E0.result == -2) {
                D_001393E0.err = 0x18;
            } else {
                D_001393E0.err = 0x1C;
            }
            D_001393E0.state = 0;
            D_001393E0.cur = 0;
            D_001393E0.busy = 0;
            break;
        case 6:
            D_001393E0.size = D_001393E0.card[D_001393E0.cur].x2C;
            if (D_001393E0.size > 0x1000) {
                func_00282A28();
            }
            if (func_00127888(D_001393E0.fd, D_001A53A8, D_001393E0.size) == 0) {
                D_001393E0.sub = 7;
            }
            break;
        case 7:
            if (D_001393E0.result == D_001393E0.size) {
                D_001393E0.card[D_001393E0.cur].x24 += func_0029B168(D_001A53A8, D_001393E0.index, D_00256368);
                if (++D_001393E0.index < 0x1C) {
                    D_001393E0.sub = 6;
                } else {
                    D_001393E0.sub = 8;
                }
                D_001393E0.busy = 0;
                break;
            }
            D_001393E0.err_card = D_001393E0.cur;
            if (D_001393E0.result >= 0) {
                D_001393E0.err = 0x1B;
                if (func_00127668(D_001393E0.fd) == 0) {
                    D_001393E0.state = 0;
                    D_001393E0.cur = 0;
                    D_001393E0.busy = 0;
                }
                break;
            }
            if (D_001393E0.result == -5) {
                D_001393E0.err = 0x15;
            } else if (D_001393E0.result == -4) {
                D_001393E0.err = 0x19;
            } else if (D_001393E0.result == -3) {
                D_001393E0.err = 0x1A;
            } else if (D_001393E0.result == -2) {
                D_001393E0.err = 0x18;
            } else {
                D_001393E0.err = 0x1C;
            }
        reset_request:
            D_001393E0.state = 0;
            D_001393E0.cur = 0;
            D_001393E0.busy = 0;
            break;
        case 8:
            if (func_00127668(D_001393E0.fd) == 0) {
                if (D_001393E0.state == 23) {
                    D_001393E0.busy = 0;
                    D_001393E0.state = 22;
                } else {
                    finished_card = &D_001393E0;
                    func_0029B628();
                    finished_card->state = 0;
                    finished_card->cur = 0;
                }
            }
            break;
        }
        break;

    case 15:
        if (D_001393E0.card[D_001393E0.cur].x24 != 0) {
            D_001393E0.busy = 0;
            D_001393E0.state = 0;
            D_001393E0.cur = 0;
            D_001393E0.err = 0x2717;
            break;
        }
        if (D_001393E0.card[D_001393E0.cur].status < 0) {
            D_001393E0.busy = 0;
            D_001393E0.state = 0;
            D_001393E0.cur = 0;
            D_001393E0.err = 0x1D;
            break;
        }
        D_001393E0.sub = 0;
        D_001393E0.state = 16;
    case 16:
        switch (D_001393E0.sub) {
        case 0:
            func_00115DA8(workspace.name, D_001A79D0, D_001393E0.card[D_001393E0.cur].status);
            if (func_00127508(D_001393E0.card[D_001393E0.cur].port, D_001393E0.card[D_001393E0.cur].slot, workspace.name, 2) == 0) {
                D_001393E0.sub = 1;
            }
            break;
        case 1:
            if (D_001393E0.result >= 0) {
                D_001393E0.fd = D_001393E0.result;
                D_001393E0.sub = 2;
            } else {
                D_001393E0.err_card = D_001393E0.cur;
                if (D_001393E0.result == -7) {
                    D_001393E0.err = 0x1E;
                } else if (D_001393E0.result == -5) {
                    D_001393E0.err = 0x1F;
                } else if (D_001393E0.result == -4) {
                    D_001393E0.err = 0x20;
                } else if (D_001393E0.result == -3) {
                    D_001393E0.err = 0x21;
                } else if (D_001393E0.result == -2) {
                    D_001393E0.err = 0x22;
                } else {
                    D_001393E0.err = 0x26;
                }
                D_001393E0.state = 0;
                D_001393E0.cur = 0;
            }
            D_001393E0.busy = 0;
            break;
        case 2:
            if (func_00127720(D_001393E0.fd, 8, 0) == 0) {
                D_001393E0.sub = 3;
            }
            break;
        case 3:
            if (D_001393E0.result >= 0) {
                D_001393E0.sub = 4;
            } else if (func_00127668(D_001393E0.fd) == 0) {
                D_001393E0.err = 0x26;
                D_001393E0.state = 0;
                D_001393E0.cur = 0;
                D_001393E0.busy = 0;
            }
            break;
        case 4:
            if (func_001279A0(D_001393E0.fd, D_001A2BA8, func_0029AE78(D_00256138)) == 0) {
                D_001393E0.sub = 5;
            }
            break;
        case 5:
            if (D_001393E0.result == func_0029AE78(D_00256138)) {
                D_001393E0.sub = 6;
                break;
            }
            D_001393E0.err_card = D_001393E0.cur;
            if (D_001393E0.result >= 0) {
                finished_card = &D_001393E0;
                finished_card->err = 0x25;
                if (func_00127668(finished_card->fd) == 0) {
                    finished_card->busy = 0;
                    goto reset_state;
                }
                break;
            }
            if (D_001393E0.result == -5) {
                D_001393E0.err = 0x1F;
            } else if (D_001393E0.result == -4) {
                D_001393E0.err = 0x23;
            } else if (D_001393E0.result == -3) {
                D_001393E0.err = 0x24;
            } else if (D_001393E0.result == -2) {
                D_001393E0.err = 0x22;
            } else {
                D_001393E0.err = 0x26;
            }
            D_001393E0.state = 0;
            D_001393E0.cur = 0;
            D_001393E0.busy = 0;
            break;
        case 6:
            if (func_00127720(D_001393E0.fd, D_001393E0.card[0].x28 + 8 + D_001393E0.index * D_001393E0.card[0].x2C, 0) == 0) {
                D_001393E0.sub = 7;
            }
            break;
        case 7:
            finished_card = &D_001393E0;
            if (D_001393E0.result == D_001393E0.card[0].x28 + 8 + D_001393E0.index * D_001393E0.card[0].x2C) {
                D_001393E0.sub = 8;
            } else {
                if (func_00127668(finished_card->fd) == 0) {
                    finished_card->busy = 0;
                    goto reset_state;
                }
            }
            break;
        case 8:
            if (func_001279A0(D_001393E0.fd, D_001A53A8, func_0029AE78(D_00256368)) == 0) {
                D_001393E0.sub = 9;
            }
            break;
        case 9:
            if (D_001393E0.result == func_0029AE78(D_00256368)) {
                D_001393E0.sub = 10;
                break;
            }
            D_001393E0.err_card = D_001393E0.cur;
            if (D_001393E0.result >= 0) {
                finished_card = &D_001393E0;
                finished_card->err = 0x25;
                if (func_00127668(finished_card->fd) == 0) {
                    finished_card->busy = 0;
                reset_state:
                    finished_card->cur = 0;
                    finished_card->state = 0;
                }
                break;
            }
            if (D_001393E0.result == -5) {
                D_001393E0.err = 0x1F;
            } else if (D_001393E0.result == -4) {
                D_001393E0.err = 0x23;
            } else if (D_001393E0.result == -3) {
                D_001393E0.err = 0x24;
            } else if (D_001393E0.result == -2) {
                D_001393E0.err = 0x18;
            } else {
                D_001393E0.err = 0x1C;
            }
            D_001393E0.state = 0;
            D_001393E0.cur = 0;
            D_001393E0.busy = 0;
            break;
        case 10:
            finished_card = &D_001393E0;
            if (func_00127668(finished_card->fd) == 0) {
                finished_card->state = 0;
                finished_card->cur = 0;
            }
            break;
        }
        break;

    case 17: {
        McChunk_298F00 *chunk;
        func_00288970(D_0014B540.x344 << 11, &chunk);
        func_002B7B18((s32)chunk, D_0014B540.x340 + D_0014B540.x32C,
                      D_0014B540.x344);
        D_001393E0.sub = 18;
        D_001393E0.busy = 0;
        break;
    }

    case 18:
        if (D_001A63AC == 0) {
            McChunk_298F00 *chunk;
            func_00288970(D_0014B884 << 11, &chunk);
            D_001393E0.sub = 19;
            D_001393E0.buf = (u8 *)chunk + chunk->x10;
        }
        D_001393E0.busy = 0;
        break;

    case 19:
        if (D_001393E0.card[D_001393E0.cur].x24 != 0) {
            D_001393E0.busy = 0;
            D_001393E0.state = 0;
            D_001393E0.cur = 0;
            D_001393E0.err = 0x2718;
            break;
        }
        if (D_001393E0.card[D_001393E0.cur].status < 0) {
            D_001393E0.busy = 0;
            D_001393E0.state = 0;
            D_001393E0.cur = 0;
            D_001393E0.err = 0x27;
            break;
        }
        D_001393E0.index = 0;
        D_001393E0.sub = 0;
        D_001393E0.state = 20;
    case 20:
        switch (D_001393E0.sub) {
        case 0:
            func_00115DA8(workspace.name, D_001A79D0, D_001393E0.card[D_001393E0.cur].status);
            if (func_00127508(D_001393E0.card[D_001393E0.cur].port, D_001393E0.card[D_001393E0.cur].slot, workspace.name, 2) == 0) {
                D_001393E0.sub = 1;
            }
            break;
        case 1:
            if (D_001393E0.result >= 0) {
                s32 n;

                D_001393E0.fd = D_001393E0.result;
                n = func_0029AE78(D_00256138);
                D_001393E0.size = n + func_0029AE78(D_00256368) * 0x1C + 8;
                if (func_001279A0(D_001393E0.fd, D_001393E0.buf, D_001393E0.size) == 0) {
                    D_001393E0.sub = 2;
                }
                break;
            }
            D_001393E0.err = 0x2B;
            D_001393E0.err_card = D_001393E0.cur;
            D_001393E0.state = 0;
            D_001393E0.cur = 0;
            D_001393E0.busy = 0;
            break;
        case 2:
            if (D_001393E0.result == D_001393E0.size) {
                if (func_00127668(D_001393E0.fd) == 0) {
                    D_001393E0.sub = 3;
                }
                break;
            }
            D_001393E0.err_card = D_001393E0.cur;
            if (D_001393E0.result >= 0) {
                D_001393E0.err = 0xB;
                if (func_00127668(D_001393E0.fd) == 0) {
                    D_001393E0.state = 0;
                    D_001393E0.cur = 0;
                    D_001393E0.busy = 0;
                }
                break;
            }
            if (D_001393E0.result == -4) {
                D_001393E0.err = 0x28;
            } else if (D_001393E0.result == -3) {
                D_001393E0.err = 0x29;
            } else if (D_001393E0.result == -2) {
                D_001393E0.err = 0x2A;
            } else {
                D_001393E0.err = 0x2D;
            }
            D_001393E0.state = 0;
            D_001393E0.cur = 0;
            D_001393E0.busy = 0;
            break;
        case 3:
            if (D_001393E0.result != 0) {
                D_001393E0.err = 0x2C;
                D_001393E0.err_card = D_001393E0.cur;
            }
            D_001393E0.state = 0;
            D_001393E0.cur = 0;
            D_001393E0.busy = 0;
            break;
        }
        break;
    case 24:
        D_001393E0.state = 25;
        D_001393E0.sub = 0;
        D_001393E0.card[D_001393E0.cur].x1C = 1;
    case 25:
        switch (D_001393E0.sub / 5) {
        case 0:
            func_00115DA8(workspace.name, D_001A99C8, D_001393E0.sub % 5);
            break;
        case 1:
            func_00115DA8(workspace.name, D_001A99E8, D_001393E0.sub % 5);
            break;
        case 2:
            func_00115DA8(workspace.name, D_001A9A08, D_001393E0.sub % 5);
            break;
        case 3:
            workspace.name[0] = 0;
            break;
        }
        if ((u8)workspace.name[0] == 0) {
            D_001393E0.state = 0;
            D_001393E0.cur = 0;
            D_001393E0.busy = 0;
            break;
        }

        if (func_00127508(D_001393E0.card[D_001393E0.cur].port, D_001393E0.card[D_001393E0.cur].slot,
                          workspace.name, 1) == 0)
            D_001393E0.state = 26;
        break;

    case 26:
        if (D_001393E0.result >= 0) {
            D_001393E0.fd = D_001393E0.result;
            if (func_00127888(D_001393E0.result, D_001A2BA8, 0x2800) == 0)
                D_001393E0.state = 27;
        } else {
            D_001393E0.state = 25;
            D_001393E0.sub = (D_001393E0.sub / 5 + 1) * 5;
            D_001393E0.busy = 0;
        }
        break;

    case 27:
        if (D_001393E0.result >= 0x2800) {
            if (func_00127668(D_001393E0.fd) != 0)
                break;
            if (func_0029AF58(D_001A2BB0) != 0) {
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
                                D_001393E0.card[D_001393E0.cur].x1C++;
                            }
                            if (b[0x12] != 0) {
                                flags |= 2;
                                D_001393E0.card[D_001393E0.cur].x1C++;
                            }
                            if (b[0x19] != 0) {
                                flags |= 4;
                                D_001393E0.card[D_001393E0.cur].x1C++;
                            }
                            if (b[0xD] != 0) {
                                flags |= 8;
                                D_001393E0.card[D_001393E0.cur].x1C++;
                            }
                            if (b[0x13] != 0) {
                                flags |= 0x10;
                                D_001393E0.card[D_001393E0.cur].x1C++;
                            }
                            break;
                        }
                        p = (s32 *)((u8 *)p + (((p[1] + 3) / 4) * 4 + 8));
                    } while (*p != -1);
                    D_001A7A00[8] = flags;
                }
            }
            D_001393E0.sub++;
        } else {
            D_001393E0.sub = (D_001393E0.sub / 5 + 1) * 5;
        }
        D_001393E0.state = 25;
        D_001393E0.busy = 0;
        break;
    }
}

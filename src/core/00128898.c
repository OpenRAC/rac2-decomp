#include "common.h"
#include "structs.h"

 /* exit */
extern void debug_print_stub(void *, ...);

/*
 * Reverted: size mismatch (ours=72, retail=60 -- 12 bytes over).
 *
 *   extern int r1_D_00132ED0;
 *   extern char r1_D_0015B640_b[] __asm__("r1_D_0015B640");
 *
 *   int func_001288C0(void) {
 *       int p = (int)r1_D_0015B640_b;
 *       int end = p + 0x3300;
 *       r1_D_00132ED0 = 1;
 *       do {
 *           *(int *)(p + 0) = 0;
 *           *(int *)(p + 4) = 0;
 *           *(int *)(p + 8) = 0;
 *           p += 0x330;
 *       } while (p < end);
 *       return 1;
 *   }
 *
 * Zeroes the +0x00/+0x04/+0x08 fields of all 16 entries in the
 * 0x330-stride table r1_D_0015B640, then marks it initialized. Semantics
 * certain; retail's loop is a plain ascending `bnez` with the
 * comparison as `slt` (signed) and no duplicated body. Because
 * end-start (0x3300) is an exact multiple of the stride (0x330) --
 * always 16 iterations -- this compiler can prove the trip count at
 * compile time and reverses the loop into a `bnezl`-based down-count
 * with the first store duplicated as the branch's delay-slot
 * instruction, regardless of whether the cursor is typed `int`,
 * `unsigned int`, or `char *` (tried all three; `int` at least
 * recovers retail's `slt`, but the reversal itself doesn't go away).
 * A different case from the established "unsigned loop counter blocks
 * reversal" lever ([[rac1-64bit-field-type]]'s sibling precedent,
 * e.g. r1_func_0011DCB8) -- that lever stops reversal driven by a small
 * loop-counter comparison, not one driven by a statically-divisible
 * address range.
 */
extern int r1_D_00132ED0;

typedef struct {
    char unk_00[4];
    int  is_linked;
    int  link_handle;
    char *dma_buffer;
    char button_slots[0x320];
} Ent330;

extern Ent330 r1_D_0015B640[];

extern void r1_func_001153FC(void *, int, int);

extern void *memcpy(void *, const void *, unsigned int);

extern int sceDbcCreateSocket(void *, int, int);

extern char r1_D_0015B640_b[] __asm__("r1_D_0015B640");

typedef struct {
    int w0;
    int mode;
    int w2;
    int w3;
    int w4;
    char name[16];
} Pad2SockParam;

extern int scePad2LinkDriver(int);

extern int pad_expand_button_mask(unsigned char *, int *);

/* The command word, built as bitfields of an `unsigned long` union: the
   union stays in a register, each insert is a 64-bit and/or, and the
   int view is the dsll32/dsra32 truncation retail passes in $a1. */
typedef union {
    struct {
        unsigned long f0 : 14;
        unsigned long f1 : 2;
        unsigned long f2 : 8;
        unsigned long f3 : 8;
    } b;
    int i;
} McCmd;

extern void *pad_select_newer_buffer(int);

extern int scePad2CheckDma(int);

/* A single stack-resident local shared by both call paths below: its
   byte 0 is the state code every path eventually returns (retail's two
   "side" sub-paths converge on one `sb`/`lbu` round trip through it,
   and the RPC path stages its return through the same byte), and the
   word at +4 is the uninitialised in/out count func_001287A8 wants. */
typedef struct {
    unsigned char state;
    char pad[3];
    int result;
} Pad2Buf;

/* rac1-decomp src/core/001236F0.c: func_00124B60 */
/* The library's debug print, compiled out to an empty varargs function.
   Only Sony's 2.9-ee gives retail's shape, spilling $5-$11 and no FP
   argument registers; the game's 2.95.3 also saves $f12-$f18. That is
   how this file was found to be built with 2.9-ee (Makefile.sn). */
/* Debug print that does nothing in the final game. */
void debug_print_stub(void *fmt, ...) {
}

/* rac1-decomp src/core/001236F0.c: func_00124B88 */
/* Clears the table of controller ports and marks it ready. */
int pad_init_socket_table(void) {
    int p;
    int end;

    r1_D_00132ED0 = 1;
    p = (int)r1_D_0015B640;
    end = p + 0x3300;
    do {
        *(int *)(p + 0) = 0;
        *(int *)(p + 4) = 0;
        *(int *)(p + 8) = 0;
        p += 0x330;
    } while (p < end);
    return 1;
}

/* rac1-decomp src/core/001236F0.c: func_00124BC8 */
/* scePad2CreateSocket(param, buf). c5: `desc.w0 = 0` moved inside the
   else (null) block instead of shared before the if, probing the last
   1-byte beqz/beql (branch-likely) difference from c4. */
/* Creates a controller socket and sets up its two data buffers. Returns the socket number or a negative error. */
int scePad2CreateSocket(void *param, char *buf) {
    Pad2SockParam desc;
    int socket_id;
    int i;
    char *slot_buf;

    if (((int)buf & 0x3F) != 0) {
        return -1;
    }
    if (param != 0) {
        int *src = (int *)param;
        desc.w0 = src[0];
        desc.w2 = src[1];
        desc.w3 = src[2];
        desc.w4 = src[3];
        memcpy(desc.name, (char *)param + 0x10, 16);
    } else {
        desc.w0 = 0;
        desc.w2 = 0;
        desc.w3 = 0;
        desc.w4 = 0;
        desc.name[0] = 0;
    }
    desc.w0 |= 1;
    desc.mode = 1;
    socket_id = sceDbcCreateSocket(&desc, (int)buf, (int)buf + 0x80);
    if (socket_id < 0) {
        return socket_id;
    }
    *(int *)(r1_D_0015B640_b + socket_id * 0x330) = 1;
    *(char **)(r1_D_0015B640_b + socket_id * 0x330 + 0xC) = buf;
    slot_buf = buf;
    for (i = 1; i >= 0; i--) {
        slot_buf[0] = 0;
        *(int *)(slot_buf + 0x7C) = 0;
        slot_buf[1] = 0;
        slot_buf[3] = 0;
        slot_buf[2] = 0;
        *(int *)(slot_buf + 4) = 0;
        r1_func_001153FC(slot_buf + 0x1C, 0xFF, 0x20);
        slot_buf += 0x80;
    }
    return socket_id;
}

extern char r1_D_0015B650[];

extern int scePad2LinkDriver(int);

extern void *pad_select_newer_buffer(int);

extern int pad_expand_button_mask(unsigned char *, int *);

extern void *func_001153D4(void *, const void *, unsigned int);

/* Read entry id's current record into dst: open the entry if it is not
   (func_00128D58), fetch the record (func_00128DB0), copy its p[2]-byte
   payload from +0x1C and hand the bytes after it to func_00128E98 with
   the entry's slot array. Returns the length, or -1. */
/* Reads the latest data record for a controller port into a buffer. Returns the length, or -1. */
int pad_read_record(int id, void *dst) {
    unsigned char *record;

    if (*(int *)((char *)r1_D_0015B640 + id * 0x330) == 0) {
        return -1;
    }
    if (r1_D_0015B640[id].is_linked == 0) {
        if (scePad2LinkDriver(id) < 0) {
            return -1;
        }
    }
    record = (unsigned char *)pad_select_newer_buffer(id);
    if (record[2] != 0) {
        unsigned char *src = record + 0x1C;

        if (src != 0) {
            func_001153D4(dst, src, record[2]);
            pad_expand_button_mask(record + 0x1C + record[2], (int *)(r1_D_0015B650 + id * 0x330));
        }
    }
    if (*(int *)(record + 4) == 0) {
        return -1;
    }
    return record[2];
}

/* rac1-decomp src/core/001236F0.c: func_00124DF0 */
/* Opens entry `port` of the table if it is not (func_00128D58), sends
   command {2, 3, 2, 1} through func_001287A8, expands the 40-bit mask it
   returns into the entry's slots (func_00128E98) and returns the result
   word func_001287A8 filled in. */
/* Reads which buttons a controller has and fills in the port's button slots. */
int pad_read_button_mask(int port, void *reply_bytes) {
    McCmd cmd;
    int result;
    int status;

    if (r1_D_0015B640[port].is_linked == 0) {
        if (scePad2LinkDriver(port) < 0) {
            return -1;
        }
    }
    cmd.b.f0 = 2;
    cmd.b.f1 = 3;
    cmd.b.f2 = 2;
    cmd.b.f3 = 1;
    status = dbc_send_command(port, cmd.i, &result, reply_bytes);
    if (status < 0) {
        return status;
    }
    pad_expand_button_mask(reply_bytes, (int *)r1_D_0015B640[port].button_slots);
    return result;
}

/* rac1-decomp src/core/001236F0.c: func_00124EE0 */
/* scePad2GetState(port): link the pad if needed (func_00128D58), then
   ask func_00128E18 (scePad2CheckDma) whether new data has arrived.
   If so, fetch the active "side" struct (func_00128DB0) and take its
   state byte directly if it looks initialised (+0x4 != 0); otherwise
   try one more relink and use it anyway on success, else forget this
   port's link and return 0. If CheckDma says nothing changed, build
   the RPC command word (the same McCmd bitfield union as
   func_00128B28's {2,3,2,1}, here {0xC,2,1,1}) and round-trip it
   through func_001287A8; return its state byte on success, 0 on
   failure. */
/* Gets the current state of the controller on a port, and returns 0 if it is not available. */
int scePad2GetState(int port) {
    Pad2Buf buf;
    char *side;
    McCmd cmd;

    if (r1_D_0015B640[port].is_linked == 0) {
        if (scePad2LinkDriver(port) < 0) {
            return 0;
        }
    }
    if (scePad2CheckDma(port) != 0) {
        side = pad_select_newer_buffer(port);
        if (*(int *)(side + 0x4) != 0) {
            buf.state = side[0];
        } else if (scePad2LinkDriver(port) >= 0) {
            buf.state = side[0];
        } else {
            r1_D_0015B640[port].is_linked = 0;
            return 0;
        }
        return buf.state;
    }
    cmd.b.f0 = 0xC;
    cmd.b.f1 = 2;
    cmd.b.f2 = 1;
    cmd.b.f3 = 1;
    if (dbc_send_command(port, cmd.i, &buf.result, (char *)&buf) < 0) {
        return 0;
    }
    return buf.state;
}

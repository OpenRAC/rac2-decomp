#include "common.h"
#include "structs.h"

typedef struct {
    char unk_00[4];
    int  is_linked;
    int  link_handle;
    char *dma_buffer;
    char button_slots[0x320];
} Ent330;

extern Ent330 r1_D_0015B640[];

extern int scePad2LinkDriver(int);

extern int sceDbcGetDepNumber(int);

extern void r1_func_00119288(void *, void *);

extern void *pad_select_newer_buffer(int);

extern void r1_func_00119288(void *a, void *b);

extern int scePad2CheckDma(int);

extern int r1_D_00132ED8[];

extern int pad_expand_button_mask(unsigned char *, int *);

/* rac1-decomp src/core/001236F0.c: func_00125020 */
/* scePad2LinkDriver(port): opens the link driver for `port` and, on
   success, records the handle in its table entry. The failure path needs
   its own early return: with one shared `return t` the compiler moves the
   result copy to the end of the function. */
/* Links the driver to a controller port and remembers the handle. */
int scePad2LinkDriver(int port) {
    int handle = sceDbcGetDepNumber(port);
    if (handle < 0) {
        return handle;
    }
    r1_D_0015B640[port].link_handle = handle;
    r1_D_0015B640[port].is_linked = 1;
    return handle;
}

/* rac1-decomp src/core/001236F0.c: func_00125078 */
/*
 * Close, not exact (3/100), same size. Logic confirmed: take entry
 * arg0 of the 0x330-stride table r1_D_0015B640, follow its +0xC pointer,
 * record that pointer and pointer+0x80 in a two-slot stack array, call
 * r1_func_00119288(p, p+0x100), then return whichever slot has the smaller
 * +0x7C field -- retail indexes the array with the `slt` result
 * directly, which plain C reproduces.
 *
 * The three differing bytes were one instruction: retail forms the entry
 * address as `addu $2,$2,$4` (base, index) where we emitted
 * `addu $a0,$a0,$v0` (index, base). Writing the addition the other way
 * round changes nothing -- GCC canonicalises the PLUS -- and this was
 * recorded here as "the allocator's destination choice, not operand
 * order", which was wrong. It is operand order, and it is steerable:
 * give the table a real element type and index it. See Ent330 above.
 */
/* Returns whichever of the two controller data buffers was written most recently. */
void *pad_select_newer_buffer(int port) {
    char *pad_buf = r1_D_0015B640[port].dma_buffer;
    char *slot[2];

    slot[0] = pad_buf;
    slot[1] = pad_buf + 0x80;
    r1_func_00119288(pad_buf, pad_buf + 0x100);
    return slot[*(int *)(slot[0] + 0x7C) < *(int *)(slot[1] + 0x7C)];
}

/* rac1-decomp src/core/001236F0.c: func_001250E0 */
/* Has entry arg0's current pair changed? Follow entry arg0 of the
   0x330-stride table to its buffer p; the pair is p+0x7C and p+0x80+0x7C.
   If the first is zero, or both equal the cached pair r1_D_00132ED8[0..1],
   report 0; otherwise cache them and report 1. The two-slot stack array
   is retail's (the same idiom as func_00128DB0). Exact under this file's
   2.9-ee; under 2.95.3 it was a word long. */
/* The old note's decode, exact since 001236F0.c builds with 2.9-ee. */
/* Returns 1 if the controller data has changed since the last check, otherwise 0. */
int scePad2CheckDma(int port) {
    char *pad_buf = r1_D_0015B640[port].dma_buffer;
    char *slot[2];

    slot[0] = pad_buf;
    slot[1] = pad_buf + 0x80;
    if (*(int *)(pad_buf + 0x7C) == 0 ||
        (r1_D_00132ED8[0] == *(int *)(pad_buf + 0x7C) &&
         r1_D_00132ED8[1] == *(int *)(slot[1] + 0x7C))) {
        return 0;
    }
    r1_D_00132ED8[0] = *(int *)(slot[0] + 0x7C);
    r1_D_00132ED8[1] = *(int *)(slot[1] + 0x7C);
    return 1;
}

/* rac1-decomp src/core/001236F0.c: func_00125160 */
/* Expand a 40-bit mask into 40 four-word slots. For each set bit, record
   slot type 1 plus the running (a, b) pair; entries 0x10..0x1F and
   0x23..0x26 are "wide" (size 8) and only advance a, everything else is
   size 1 and advances b, rolling a over every eighth. Clear bits zero
   the slot's type and both counters. Initialising b before the loop
   sets i gives i the shorter live range, so this file's compiler
   (2.9-ee) allocates it first, as retail. */
/* Turns a bit mask of buttons into a list of button slots. */
int pad_expand_button_mask(unsigned char *src, int *out) {
    int bit;
    int a;
    int i;
    int b;

    bit = 0;
    a = 0;
    b = 0;
    for (i = 0; i < 0x28; i++) {
        if (((*src >> bit) & 1) != 0) {
            out[0] = 1;
            out[2] = a;
            out[3] = b;
            if ((i >= 0x10 && i < 0x20) || (i >= 0x23 && i < 0x27)) {
                out[1] = 8;
                a++;
            } else {
                b++;
                out[1] = 1;
                if ((b & 7) == 0) {
                    a++;
                    b = 0;
                }
            }
        } else {
            out[0] = 0;
            out[2] = 0;
            out[3] = 0;
        }
        bit++;
        if ((bit & 7) == 0) {
            src++;
            bit = 0;
        }
        out += 4;
    }
    return 1;
}

typedef struct {
    unsigned long a : 14;
    unsigned long b : 2;
    unsigned long c : 8;
    unsigned long d : 8;
} Mode128F48;

extern int r1_func_00124A70(int, Mode128F48, int *, int);

/* rac1-decomp src/core/00125218.c: func_00125218 */
/* Builds a mode word from bitfields and runs the r1_func_00124A70 round
   trip. The fields are 64-bit, so each insert is a doubleword and/or,
   and the struct is passed by value. `if (r >= 0) return out;` keeps
   retail's two returns; an `r = out` spelling becomes slt/movz. */
/* Sends a command to a controller port and returns the result value. */
int pad_send_command(int port, int dst) {
    Mode128F48 m;
    int out;
    int status;

    m.a = 2;
    m.b = 2;
    m.c = 3;
    m.d = 1;
    status = r1_func_00124A70(port, m, &out, dst);
    if (status >= 0) {
        return out;
    }
    return status;
}

extern void *func_001153D4(void *, const void *, unsigned int);

/* libvib's command to the dbc send call, passed by value like
   func_00128F48's: retail moves the whole 64-bit register into $a1
   (daddu), where an int view of it would be truncated (dsll32/dsra32,
   as libpad2's func_00128B28 shows). */
extern int dbc_send_vibration_command(int, Mode128F48, int *, unsigned char *);

/* The libvib sibling of func_00128F48: build command {0xB, 1, 3, 1}, pack
   both sizes and the two blocks (first, then second) into one packet and
   send it through func_001286C8 with a 0x28-byte size word. Initialising
   `result` before the bitfields gives retail's insert schedule; adding the
   packet's address to first_size gives retail's second destination. */
int sceVibSetActParam(int port, int second_size, void *second, int first_size, void *first) {
    Mode128F48 m;
    struct {
        int sizes[2];
        unsigned char buffer[0x28];
    } packet;
    int result;

    result = 0x28;
    m.a = 0xB;
    m.b = 1;
    m.c = 3;
    m.d = 1;
    packet.sizes[1] = first_size;
    func_001153D4(packet.buffer, first, first_size);
    packet.sizes[0] = second_size;
    first_size += (int)&packet;
    func_001153D4((void *)(first_size + 8), second, second_size);
    return dbc_send_vibration_command(port, m, &result, (unsigned char *)&packet);
}

ASM_FUNC("asm/core", func_001290BC);

ASM_FUNC("asm/core", func_00129120);

ASM_FUNC("asm/core", func_00129160);

ASM_FUNC("asm/core", func_001291A0);

ASM_FUNC("asm/core", func_00129218);

ASM_FUNC("asm/core", func_001292C0);

ASM_FUNC("asm/core", func_00129368);

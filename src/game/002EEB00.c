#include "include_asm.h"
#include "names.h"

extern int moby_get_motion_data();

extern int follower_get_state();

extern float func_00282E48_4();

extern int func_00282948_1();

/* Append one 16-byte record to the level's queue at 0x226150 and submit it
   through the DMA helper func_0011AFE0.  The four queue globals live in a
   0x38-byte state block based at 0x1A7240; because they are reached with a
   constant offset from that base (a CONST address), cc1 gives the store a
   two-instruction length and refuses to drop it into the branch delay slot,
   which is what the retail body does as well.  */

typedef struct {
    int start;      /* +0x00 -> 0x1A7240 */
    int end;        /* +0x04 -> 0x1A7244 */
    int pad[10];    /* +0x08 .. +0x2F */
    int cursor;     /* +0x30 -> 0x1A7270 */
    int count;      /* +0x34 -> 0x1A7274 */
} LevelQueue5a29d35d;

extern LevelQueue5a29d35d D_001A7240 __attribute__((sda));

extern char D_L03_00226150[];

extern int sceSifSetDma(int *dma, int flag);

/* v2: guard reads p->count, loop counter is a second read (CSE -> copy). */
struct Elem {
    unsigned int f0;
    unsigned char pad0[31];
    unsigned char f35;
    unsigned char pad1[12];
    unsigned int f48;
    unsigned char pad2[28];
};

struct Node {
    struct Elem *elems;
    int count;
};

extern struct Node D_L05_00226A00 __attribute__((nosda));

extern short D_L05_00226700[][2];

/* Apply nonzero signed halfword overrides to indexed rows of selected objects. */
typedef struct {
    unsigned int first;
    unsigned char reserved04[0x1c];
    unsigned int second;
    unsigned char reserved24[0x0f];
    unsigned char key;
    unsigned char reserved34[0x1c];
} ListOverrideRow;

typedef struct {
    unsigned char reserved00[0x0f];
    unsigned char count;
    unsigned char reserved10[0x0c];
    ListOverrideRow *rows;
} ListOverrideObject;

typedef struct { short first; short second; } ListOverridePair;

extern int D_L00_0022DC00[];

extern ListOverrideObject *D_L00_00226700[];

extern ListOverridePair D_L00_0022D600[];

/* Picks a float threshold (1.0 or 8.0) from a callee status code, compares a probed float against it, and returns a boolean that also latches a trailing probe. */
/* Checks if the follower has reached its target (closer than 1.0, or 8.0 in state 2) and is not dying; returns 1 if so. */
int follower_has_reached_target(int *owner)
{
    int result = 0;
    int vars = moby_get_motion_data(owner);
    float threshold = 1.0f;

    if (follower_get_state(owner) == 2)
        threshold = 8.0f;

    if (vars != 0) {
        if (func_00282E48_4((char *)owner + 16, (char *)vars + 96) < threshold)
            result = follower_get_state(owner) != 8;

        result = func_00282948_1((char *)vars + 304) != 0 ? 1 : result;
    }

    return result;
}


/* Empties the table of 64 buffer slots and resets the buffer cursor. */
void gfx_reset_buffer_slot_table(void)
{
    int i;
    D_001A7240.cursor = D_001A7240.start;
    D_001A7240.count = 0;
    for (i = 0; i < 64; i++) {
        *(int *)(D_L03_00226150 + i * 16) = 0;
        *(int *)(D_L03_00226150 + i * 16 + 4) = 0;
    }
}

/* shared native body of family 5a29d35dd7a7809a */
/* Sends some 16-byte records to the buffer, and stores a new slot that reserves room for the records. Returns the slot number, or a negative error if there is no room. */
int gfx_alloc_buffer_slot(int tag, int sendCount, int recordCount, int label)
{
    int request[4];
    int slot, index;

    if (D_001A7240.end - (D_001A7240.cursor - D_001A7240.start) < recordCount * 16)
        return -1;
    if (D_001A7240.count == 64)
        return -2;

    request[0] = tag;
    request[1] = D_001A7240.cursor;
    request[2] = sendCount * 16;
    request[3] = 0;
    sceSifSetDma(request, 1);

    slot = D_001A7240.count;
    index = slot;
    slot = slot + 1;
    D_001A7240.count = slot;
    *(int *)(D_L03_00226150 + index * 16) = D_001A7240.cursor;
    *(int *)(D_L03_00226150 + index * 16 + 4) = recordCount;
    *(int *)(D_L03_00226150 + index * 16 + 8) = label;
    D_001A7240.cursor = D_001A7240.cursor + recordCount * 16;
    return index;
}

typedef struct { int address, count, reserved[2]; } TransferRow16;
extern TransferRow16 D_L00_002254D0[];

/* Sends part of an already reserved buffer slot. Returns 0 on success or a negative error code. */
int gfx_send_buffer_slot_records(int tag, unsigned int slot, int firstRecord, int count)
{
    int request[4];
    if (slot >= 64 || D_L00_002254D0[slot].count == 0)
        return -3;
    if (D_L00_002254D0[slot].count < firstRecord + count)
        return -1;
    request[0] = tag;
    request[1] = D_L00_002254D0[slot].address + firstRecord * 16;
    request[2] = count * 16;
    request[3] = 0;
    sceSifSetDma(request, 1);
    return 0;
}


typedef struct StashBlock_r002EEFE0 {
    /* 0x00 */ int   ram;      /* IOP stash RAM address */
    /* 0x04 */ int   qwc;      /* quadword count (16 bytes per unit) */
    /* 0x08 */ int   comment;  /* char* debug comment / tag */
    /* 0x0C */ int   pad;
} StashBlock_r002EEFE0;

extern StashBlock_r002EEFE0 r1_D_001DD568[];

extern int gfx_get_buffer_slot_record_count(unsigned int);

/* rac1-decomp src/game/stash.c: func_00234350 */
/* Returns how many 16-byte records the given buffer slot holds, or -3 if the slot number is out of range. */
int gfx_get_buffer_slot_record_count(unsigned int slot) {
    if (slot >= 0x40) {
        return -3;
    }
    return r1_D_001DD568[slot].qwc;
}


/* func_002EF1E8 is in 002EEB00-g8.c. */

/* shared native body of family 9328256ba62fe2c4 */
/* Walks every terrain draw list and patches the drawing settings of each entry with the override values for its type. */
void PatchTfragGifs(void)
{
    struct Node *table = &D_L05_00226A00;

    if (table->elems != 0) {
        do {
            struct Elem *elem = table->elems;

            if (table->count > 0) {
                int remaining = table->count;

                do {
                    short *override = D_L05_00226700[elem->f35];
                    if (override[0] != 0) elem->f0 = (elem->f0 & 0xFFFFC000u) | (unsigned int)override[0];
                    if (override[1] != 0) elem->f48 = (elem->f48 & 0xFFFFC000u) | (unsigned int)override[1];
                    elem++;
                } while (--remaining);
            }
            table++;
        } while (table->elems != 0);
    }
}

/* func_002EF3B0 is matched in its own unit, 002EF3B0.c. */

ASM_FUNC("asm/game", func_002EF480);

ASM_FUNC("asm/game", func_002F00A8);

ASM_FUNC("asm/game", func_002F0218);

ASM_FUNC("asm/game", func_002F0468);

/* Original assembly: lqc2/qmtc2/qmfc2 VU0 ops, $at as a working register and trapping addi. */
ASM_FUNC("asm/game", func_002F0B78);

/* Original assembly: $at as a working register and trapping add/addi; the compiler cannot emit them. */
ASM_FUNC("asm/game", func_002F0D00);

/* Runs one set of render steps for the level using the current list position. */
void gfx_run_level_render_step(void)
{
    extern int D_001A72D0 __attribute__((sda));
    extern void func_002F3300(int);
    extern void gfx_append_vu1_preset_a(void);
    func_002F3300(D_001A72D0);
    gfx_append_vu1_preset_a();
}

/* apply nonzero signed halfword overrides to selected object rows; observed count0F, rows1C, stride50 and key33 */
void gfx_apply_object_row_overrides(void)
{
    int *selected = D_L00_0022DC00;
    while (*selected >= 0) {
        ListOverrideObject *object = D_L00_00226700[*selected];
        int i = 0;
        ListOverrideRow *row = object->rows;
        while (i < object->count) {
            ListOverridePair *pair = &D_L00_0022D600[row->key];
            if (pair->first != 0)
                row->first = (row->first & 0xffffc000u) | pair->first;
            if (pair->second != 0)
                row->second = (row->second & 0xffffc000u) | pair->second;
            i++;
            row++;
        }
        selected++;
    }
}

/* func_002F0EF8 is in 002EEB00-flags.c (-mno-split-addresses). */



ASM_FUNC("asm/game", func_002F1010);

ASM_FUNC("asm/game", func_002F1E60);

ASM_FUNC("asm/game", func_002F1E88);

ASM_FUNC("asm/game", func_002F2610);

/* Original assembly: lqc2/qmtc2/qmfc2 VU0 macro ops, $at as a working register and trapping addi. */
ASM_FUNC("asm/game", func_002F2758);

ASM_FUNC("asm/game", func_002F29E4);

ASM_FUNC("asm/game", func_002F2A0C);

ASM_FUNC("asm/game", func_002F2A38);

ASM_FUNC("asm/game", func_002F32AC);

ASM_FUNC("asm/game", func_002F32D4);

/* Original assembly: $at as a working register and trapping add/addi; the compiler cannot emit them. */
ASM_FUNC("asm/game", func_002F3300);

ASM_FUNC("asm/game", func_002F35B0);

/* Original assembly: $at as a working register (lw $at,off($a0)); the compiler cannot emit it. */
ASM_FUNC("asm/game", func_002F3CF8);

/* Original assembly: qmtc2 VU0 ops, $at as a working register and trapping addi/add. */
ASM_FUNC("asm/game", func_002F3D20);

/* Original assembly: qmtc2 VU0 op and trapping addi; the compiler cannot emit them. */
ASM_FUNC("asm/game", func_002F3E40);

ASM_FUNC("asm/game", func_002F3E78);

ASM_FUNC("asm/game", func_002F4F78);

ASM_FUNC("asm/game", func_002F4FA0);

/* Original assembly: $at as a working register and trapping add/addi; the compiler cannot emit them. */
ASM_FUNC("asm/game", func_002F5118);

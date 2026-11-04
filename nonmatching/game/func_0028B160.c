/* 4 November 2026 current-RAC1 source trials; retained, not linked.
 * Six actual size/upload/bound-read groups, a page helper and loop-profile trials do not match.
 * The size-only group plus no-strength-reduce gives 292/292 bytes, 0/28 USA, first +0xA8: the
 * full prologue and shift-base/immediate registers agree, but call setup and the shift delay slot
 * differ. Other new forms are 288/292, 300/292, or retain the original register swap. Current
 * RAC1 ui/hud.c uses the same ordinary bank loop. The older best body is retained with complete
 * declarations; the new size-group source remains a diagnostic, not a qualified profile.
 */
/* func_0028B160 - Opus 5.5 xhigh, v1749: 292/292 bytes, 0/28 USA v1.01 places, first mismatch
 * +0x14, under the unit's -O2 -G0 -ffunction-sections (src/game/00288D88.c). Only six words
 * differ, all one swap: retail keeps immediate in $s7 and the hoisted constant 1 in $s6.
 * The same six words remain under -mno-split-addresses, -g, -fno-sched-interblock, -fno-regmove,
 * -fno-sched-spec, -frac2-keep-block-order and -frac2-gcse-unsplit-edges; a single-pointer
 * spelling of the header and offset gives them too.
 *
 * Allocator evidence (tools/regalloc.py): both pseudos have refs 3, but immediate has live
 * length 47 and the constant 48 (24 doubled: it carries a REG_EQUIV note, as GCC's
 * update_equiv_regs does for a constant), so immediate is allocated first and takes $s6. Retail needs immediate at 49 or more
 * (48 ties, and the lower pseudo number wins). Each instruction removed from the loop lowers the
 * constant by 2 and immediate by 1, each added before the loop raises immediate by 1: two such
 * steps are needed, and the loop has no spare instruction. They must be RTL insns alive at sched1
 * that are gone from the final code.
 *
 * Measured dead ends: repeating the end read in both arms of the first-index test reaches 49 and
 * the right registers, but sched1 orders the arms differently, cross-jumping fails, and it is 8
 * bytes long. Moving the header load and offset shift into both arms of the first if is undone by
 * cse (no second shift, 308 bytes). A plain extern for D_001B1888 reaches 48 but keeps %hi in a
 * saved register, or breaks the tied lui/lw in the first block when only that read is split. The
 * explicit `one` local is worse: the constant is set before the guard, live length 52. Without
 * the else arm the first shift is reused (saved in $s1), apparently cse-skip-blocks.
 *
 * Untried: a second name for D_001B1888 could put the header load in both arms of the first if
 * (one step, a tie at 48), which still leaves one step to find. No linked build was run.
 *
 * Declarations: struct HudTexCounts, HudTexPage and HudState with D_001B1870 sda, and
 * func_0028AE88, as above func_0028ACB0 in src/game/00288D88.c. Marker restored in src/.
 */
#include "common.h"

struct HudTexCounts {
    unsigned char pad0[0x14];
    int mid_ends[8];
    int ends[16];
    int loaded[16];
};
struct HudBank {
    int unk0;
    int off4;
    int off8;
    int offC;
    int off10;
    unsigned char pad14[0x40];
    int has54;
    int size58;
    int has5C;
    int has60;
    int has64;
    unsigned char pad68[0x2C];
    int unk94;
    int unk98;
    int unk9C;
    int unkA0;
    int unkA4;
};
struct HudTexPage {
    unsigned int source_address;
    unsigned short gs_block_offset;
    unsigned char width_log2;
    unsigned char height_log2;
};
struct HudState {
    int serial;
    int unk4;
    int unk8;
    int z;
    int heap_cur;
    int heap_end;
    union {
        struct HudTexCounts *counts;
        struct HudBank *bank;
    } header;
    void *anim_defs;
    void *frame_refs;
    struct HudTexPage *image_pages;
    struct HudTexPage *palette_pages;
};
extern struct HudState D_001B1870 __attribute__((sda));
extern void func_0028AE88(int, int);

extern int D_001A7308 __attribute__((section(".sdata")));
extern void func_0028F948(unsigned int, int, int, int, int, int);

/* Uploads the image pages of one HUD bank to GS memory, from the depth buffer address up, and
 * records each page's block offset. Carried from rac1-decomp (src/game/hud.c,
 * Hud_SendResidentBank). */
void func_0028B160(int bank, int base, int immediate)
{
    struct HudTexCounts *counts;
    int address;
    int bank_offset;
    int first;
    int end;
    int i;
    int page;
    int width_log2;
    int height_log2;
    int size;

    if (D_001B1870.header.counts->loaded[bank] == 0) {
        func_0028AE88(0, base);
        address = D_001A7308;
    } else {
        address = D_001A7308;
    }
    counts = D_001B1870.header.counts;
    bank_offset = bank << 2;
    first = bank == 0 ? 0 : counts->ends[bank - 1];
    i = first;
    end = *(int *)((unsigned char *)D_001B1870.header.counts + bank_offset + 0x34); /* ends[bank] */
    for (; i < end; i++) {
        page = address >> 8;
        width_log2 = D_001B1870.image_pages[i].width_log2;
        height_log2 = D_001B1870.image_pages[i].height_log2;
        size = 1 << (width_log2 + height_log2);
        func_0028F948(D_001B1870.image_pages[i].source_address, page, 0x1B, width_log2,
                      height_log2, immediate);
        address += size * 4;
        D_001B1870.image_pages[i].gs_block_offset = page;
    }
}

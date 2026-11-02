/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
#include "include_asm.h"

/* func_00294C40 (boot 0x00294C40, 320 bytes, 28 places): opus-1, Claude Opus 5.5.
 * Best check.py: 320/320 bytes, 0/28 places, 38 of 80 rows differ.  Default profile
 * (-O2 -G0 -ffunction-sections), compiled in place in src/game/00294BC8.c.
 *
 * The body is RAC1 load_texture_file (src/game/map.c, types TexSlot and TexDesc)
 * with TEX0 built term by term, as in RAC1's effect texture code in draw.c.  The two
 * globals are incomplete `sda` arrays, which gives retail's tied macro load and
 * `lui $at; sw`.  This wording gives the frame, stack slots, record stores, the
 * register of every TEX0 accumulator and the width and palette terms.
 *
 * What still differs: local-alloc serves the height term's group
 * (`daddu; dsll 30`) before the clutSize group (`lw 0x14($sp); addiu 0x20`), so the
 * height term takes $a1 and clutSize $a2.  Retail has height $a2, clutSize $a1 and
 * 0x1300000 in $a1.  The 0x1300000 constant then falls to $t0, and that pushes the
 * constant 1, count, tbp and cbp one register along (retail t0, t2, t3, t4).  The
 * remaining order differences (the `sllv`/`addu` of the cursor) look like sched2's
 * anti-dependence on $t0, which retail reuses for the final value, so they should
 * follow once the allocation is right.  In sched1's order the two groups are close:
 * height spans 9 insns, clutSize 10, both 4 refs.
 *
 * Tried without getting closer: first scheduler off (70 rows differ), -fno-gcse,
 * -fno-expensive-optimizations, -fno-strength-reduce, -fno-regmove,
 * -mno-split-addresses, one shared term variable, moving the cursor, count and pix
 * statements, a separate variable for each term, and computing the height term
 * earlier (worse).
 */
extern int func_00282A18(int);

extern int D_001A72D0[] __attribute__((sda));

extern int D_001B15FC[] __attribute__((sda));

typedef struct {
    int addr;
    short unk4;
    short cbp;
    int unk8;
    unsigned char tw;
    unsigned char th;
    short tbp;
} TexSlot;

extern TexSlot D_001B9340[];

typedef struct {
    char *clut;
    char *pix;
    char pad08[0xC];
    int clutSize;
    char pad18[0x34];
    int tw;
    int th;
    char pad54[0xC];
} TexDesc;

/* Loads a 256-colour texture file p (width at +8, height at +0xC, CLUT at +0x20,
   pixels after it): the CLUT and the pixels take the next VRAM space, the texture
   is queued in the 64-entry upload table and its GS TEX0 value returned. */
long long func_00294C40(char *p)
{
    TexDesc t;
    int w;
    int cbp;
    int tbp;
    int addr;
    int count;
    long long reg;
    long long tex;
    long long width_bits;
    long long palette_bits;

    t.clut = p + 0x20;
    t.clutSize = 0x400;
    t.tw = func_00282A18(*(int *)(p + 8));
    t.th = func_00282A18(*(int *)(p + 0xC));
    addr = D_001A72D0[0];
    cbp = addr >> 8;
    addr += 0x400;
    tbp = addr >> 8;
    D_001A72D0[0] = addr + (1 << (t.tw + t.th));
    w = t.tw - 6;
    if (w < 0) {
        w = 0;
    }
    w = 1 << w;
    tex = (long long)tbp | ((long long)w << 14);
    width_bits = (long long)t.tw << 26;
    width_bits |= 0x1300000;
    tex |= width_bits;
    tex |= (long long)t.th << 30;
    palette_bits = (long long)cbp << 37;
    palette_bits |= (long long)1 << 34;
    tex |= palette_bits;
    reg = tex | ((long long)4 << 61);
    t.pix = p + 0x20 + t.clutSize;
    count = D_001B15FC[0];
    if (count < 0x40) {
        D_001B9340[count].addr = (int)t.clut;
        D_001B9340[count].cbp = cbp;
        D_001B9340[count].unk4 = 0;
        D_001B9340[count].unk8 = (int)t.pix;
        D_001B9340[count].tw = t.tw;
        D_001B9340[count].th = t.th;
        D_001B9340[count].tbp = tbp;
        D_001B15FC[0] = count + 1;
    }
    return reg;
}

/* functional: high. Near-miss draft within a few instructions of retail: differences are register allocation, scheduling and instruction shape. */
/*
 * func_L00_002A9460 (412 bytes, 27 places). Claude Opus 5.5 (opus-1), task v1533,
 * 29 October 2026. Best: 412/412 bytes, 0/27 USA places (tools/check.py);
 * only one delay slot differs. Profile: its own unit, -O2 -G0 -ffunction-sections,
 * approved qcopy from common.h. Remove the INCLUDE_ASM marker from
 * src/levels/shared/L00_002A6420.c when trying it.
 *
 * Counterpart of RAC1's update_hero_moby (src/overlays/shared/hero_idle_and_animation.c).
 * The identical-arm test of moby->pclass byte 6 is what retail shows: jump2's
 * cross-jumping merges the arms after flow, leaving the dead `lw 0x24; lbu 6` (no
 * volatile needed), and its join restarts cse, so the second half rebuilds the
 * D_00189E20 base from the shared %hi (gcse PRE) as retail's $s1 does.
 *
 * Remaining difference: `addiu $s1,$s1,%lo(D_00189E20)` (block after the join) fills
 * the delay slot of the first call (ref_00) here, of the second call (ref_01) in
 * retail. reorg's forward search from ref_00 passes the second qcopy asm (volatile:
 * needed.volatil = 1), but this tree's resource.c assigns `res->volatil =
 * MEM_VOLATILE_P (x)` at every later MEM, so the next ordinary load clears it and the
 * addiu is accepted. Retail behaves as if the flag stayed set (GCC 2.95's `|=`):
 * the search from ref_00 stops, the one from ref_01 (no asm in between) takes it.
 * With `=` both searches see the same state at the addiu, so no source wording
 * with this block structure can separate them; the old orch/main
 * -frac2-sticky-volatile-refs modelled exactly this and is not upstream.
 * Tried: -frac2-qcopy (+barrier) grouped copies instead of the asm (same slot),
 * the branch polarity (same).
 */
#include "common.h"

/* Its first two callees differ by level (ref_ names); func_L00_002ADF80 is C in
   L00_002A6420.c with the same 27 places. */

typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    char pad000[0x80];
    TI128 position;
    TI128 unk90;
    char padA0[0x150];
    short unk1F0;
    char pad1F2[0x5E];
    float unk250;
    float unk254;
    char pad258[0xC];
    float unk264;
    char pad268[0x2028];
    unsigned char *moby;
    char pad2294[0x8];
    int unk229C;
} HeroView_L00_002A9460;

extern char D_00189E20[];
extern void func_L00_002A75D8(void);
extern void func_L00_002A76B8(void);
extern void func_00282AB0(void *, void *, int);
extern void func_002A0F48(void *);
extern void func_L00_002D3778(void *, void *, float);
extern void func_L00_00310748(void *, int, void *, float, float);
extern int func_L00_002ADF80(void);

#define HERO ((HeroView_L00_002A9460 *)D_00189E20)

void func_L00_002A9460(void)
{
    float v[4] __attribute__((aligned(16)));
    float t, gap;
    unsigned char *m;

    HERO->moby[0xA8] = 0xFF;
    qcopy(HERO->moby + 0x10, &HERO->position);
    func_L00_002A75D8();
    qcopy(HERO->moby + 0xF0, &HERO->unk90);
    func_L00_002A76B8();
    func_00282AB0(HERO->moby + 0xC0, D_00189E20, 0x30);
    func_002A0F48(HERO->moby);
    m = HERO->moby;
    if ((*(unsigned char **)(m + 0x24))[6] != 0)
        m[0x63] = 0x10;
    else
        m[0x63] = 0x10;
    if (HERO->unk1F0 != 0 || *(int *)(HERO->moby + 0x98) == 0)
        return;
    qcopy(v, &HERO->position);
    func_L00_002D3778(v, v, HERO->unk254);
    gap = HERO->unk250 - HERO->unk254;
    if (gap < 0.05f)
        gap = 0.05f;
    func_L00_00310748(HERO->moby, 0, v, HERO->unk264, gap);
    t = HERO->unk264 + 0.05f;
    if (HERO->unk229C == 4)
        t += 0.15f;
    if (func_L00_002ADF80() != 0)
        t = HERO->unk254;
    qcopy(v, &HERO->position);
    func_L00_002D3778(v, v, t);
    gap = HERO->unk250 - t;
    if (gap < 0.05f)
        gap = 0.05f;
    func_L00_00310748(HERO->moby, 1, v, HERO->unk264, gap);
}

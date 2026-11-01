/* functional: high. Near-miss draft within a few instructions of retail: differences are register allocation, scheduling and instruction shape. */
#include "common.h"
/* Claude Opus 5.5 xhigh, v2031: 196/196 bytes, 0/2 places as written below; only
 * +0x2C/+0x30 differ (retail a3=0 then a0=s0, this C a0=s0 then a3=0).
 * -O2 -G8 -ffunction-sections (name the unit <file>-g8.c).
 *
 * EXACT-BYTES FORM, NOT LANDED: wrapping the random test in a do/while(0) gives
 * 2 of 2 places (us), 2 of 2 (us2), neither catalogue (pal):
 *     func_002AFDD8(a0, block, block, 0);
 *     do {
 *         if (func_002A77E0(2) != 0)
 *             s1->angle = 1.5707964f;
 *         else
 *             s1->angle = -1.5707964f;
 *     } while (0);
 * WORKER2 forbids that wrapper until the maintainers rule on it, since its only
 * effect is on scheduling. The rest of the wording here is already exact.
 *
 * Why it works (dumps with -fsched-verbose-5): all four argument moves have
 * priority 5 in sched2; a1/a2 read sp and so have a data link on the first call
 * (class 1), and a0/a3 are class 2. The tie-break is the forward dependent count:
 * a0=s0 has {call, a0=2, random} because the call only clobbers a0, so the next
 * explicit set in the block links back to it; a3=0 has {call, random}. So a0 issues
 * first, though sched1's birthing boost put a3 first (lowest LUID). A LOOP_BEG note
 * before a0=2 makes that insn a barrier in sched_analyze_insn: every earlier set
 * links to it, the counts tie, and LUID picks a3.
 *
 * Other sites of this retail idiom have a3 first because no explicit a0 set follows
 * in the block (the next call takes f12/f13). A plain block boundary after the call
 * does not explain this one: it removes the a3 boost, which needs a later call in the
 * same block (a0,a1,a2,[jal],a3). Tied: int return on func_002AFDD8, long long fourth
 * argument (false prototype anyway), local pointer, structured vector, pointer fourth
 * argument. Next: a real construct leaving a loop note there, or a maintainers' ruling.
 */

#include "include_asm.h"


extern void func_00282CF0(float *, void *, void *);
extern void func_002AFDD8(void *, void *, void *, int);
extern int func_002A77E0(int);
extern float func_00283248(float, float);
extern float func_00283B98(float, float);
typedef struct { u8 pad[0xB0]; f32 angle; u8 gap[8]; f32 bc, c0; int c4; } AimCtl;

extern char D_L22_001B9C80[];
extern f32 D_L22_001B0A1C __attribute__((sda));
extern f32 D_L22_001B0A14 __attribute__((sda));

void func_L22_003F54B8(u8 *a0)
{
    f32 block[4];
    AimCtl *s1;

    s1 = *(AimCtl **)(a0 + 0x68);
    func_00282CF0(block, D_L22_001B9C80, a0 + 0x10);
    func_002AFDD8(a0, block, block, 0);
    if (func_002A77E0(2) != 0)
        s1->angle = 1.5707964f;
    else
        s1->angle = -1.5707964f;
    s1->angle = func_00283B98(s1->angle,
                                      func_00283248(block[0], block[1]));
    s1->c0 = D_L22_001B0A1C * 0.000290888245f;
    s1->bc = D_L22_001B0A14;
    s1->c4 = 0;
}

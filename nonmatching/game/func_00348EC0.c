/* 6 November 2026: retained source below unchanged (644/644, 0/28 USA, 25 words).
 * Retail loads D_001AE5F0 ($gp), D_001B23A4 and the count, then D_001A7344 last; this
 * source loads D_001B23A4 first and D_001A7344 before the count. No change from: count
 * read before sp, a `half` or `scale` local, menu->count in place of n, swapped product
 * operands; a one-pass group around sp or start gives 23-26 words.
 */
/* 4 November 2026 actual-contract review; retained near miss, not linked.
 * USA v1.01 check.py: 644/644 bytes, 0/28 placements; first difference 0x98.
 * Profile: -O2 -G8 -ffunction-sections.
 * Stored-address getters follow their matched signed32 return contracts, with explicit pointer
 * casts at the actual uses. Physical EE widths and argument-bank order are preserved; this
 * repair leaves the retained allocation/scheduling residual unchanged.
 * Earlier measurements below are historical where superseded by this note.
 */
/* 3 November 2026: retained near miss, not linked.
 * Profile: -O2 -G8 -ffunction-sections.
 * Current size: 644/644 bytes; US 0/28, US2 absent, PAL absent.
 * Complete 72-byte text typing preserves the true 64-bit style. Reusing the descriptor address
 * shortened the body to 628 bytes; preserving its separately formed address retains the 27-word
 * centering/setup residual.
 * Reopen on a real additional lifetime or source/control-flow witness for the centering block;
 * owner typing and widget-address capture did not resolve it.
 * Earlier measurements below are historical where this note supersedes them.
 */
/* opus-1 (v1334): -O2 -G8 -ffunction-sections (a *-g8.c unit); 644/644 bytes, 0/28 places.
 * The whole loop body, the prologue/epilogue and the frame match retail. Two source facts
 * recovered that: the coordinate stores go through a struct view of the rectangle returned
 * by func_00335E10 (MEM_IN_STRUCT stores do not conflict with the scalar sda tuning loads, so
 * those loads schedule above the first store as retail does), and the highlight colour is
 * computed into a local before the func_00335E20 call.
 * Still different: the 28 instructions of the centring computation between the fifth
 * func_00336320 call and the count test (+0x8C..+0xF8). Retail allocates count=a1,
 * spacing=a0, height=v0, 5F0=f0, 23A4=f2, 0.5=f1, (float)count=f3; cc1 gives count=v1,
 * spacing=v0 (and f0/f3/f4 for the floats), so sched2 orders the block differently.
 * A local-alloc model of this block shows retail's GPR assignment needs one more GPR
 * quantity live across the spacing conversion than this dataflow has. Tried without
 * success: statement order/separate variables, float variable reuse, 0.5 hoisted to a
 * variable (takes f20), split-address D_001A7344 (count moves to a0), -g,
 * -fno-sched-interblock, -fno-sched-spec, -ffast-math, -fno-schedule-insns (breaks the
 * loop), a for loop nested in the count test (count becomes global, spacing v1, but a
 * second blez stays). Next: find what natural source adds a GPR value in that block.
 * Declarations below are standalone; the D_ addresses are the boot's (gp 0x001AEFF0).
 */
#include "common.h"

extern int func_002A9588(int, int, int, int, int);
extern void func_00336320(char *);
extern int func_00335E10(char *);
extern int func_00335E20(char *);
extern float D_001AE5F0 __attribute__((sda));
extern float D_001B23A4[] MACRO_ADDR;
extern int D_001A7344[] MACRO_ADDR;
extern float D_001AE5D0 __attribute__((sda));
extern float D_001AE5D4[] MACRO_ADDR;
extern float D_001AE5D8 __attribute__((sda));
extern float D_001AE5E0 __attribute__((sda));
extern float D_001AE5E4[] MACRO_ADDR;
extern float D_001AE5E8 __attribute__((sda));

typedef struct { float x, y, w, h; } ListRect;
typedef struct {
    char pad[0x434];
    ListRect *origin;
    int unknown438;
    int selected;
    int enabled;
    int count;
    int showSpecial;
} ListMenu;
typedef struct { short pad[4]; short offset; short pad2; void (*call)(char *); } ListVtable;
typedef struct {
    ListRect *position;
    ListRect *scale;
    void *parameter08;
    unsigned int *colors;
    float *visibility;
    char lifetime[0x1C];
    ListVtable *table;
    void *metrics;
    unsigned long style;
    char *text;
    int alignment;
} ListSlot;

void func_00348EC0(char *o)
{
    int color = func_002A9588(0x20FFFEED, 0x70FFFEED, 20, 0, 0);
    int start, i, n, sp;
    ListMenu *menu = (ListMenu *)o;

    if (menu->enabled) {
        func_00336320(o);
        func_00336320(o + 0x130);
        func_00336320(o + 0x4C);
        func_00336320(o + 0x98);
        func_00336320(o + 0xE4);
        sp = (int)(D_001AE5F0 * D_001B23A4[0] + 0.5f);
        n = menu->count;
        start = (int)((float)(D_001A7344[0] >> 1) - (float)sp * ((float)n * 0.5f));
        if (n > 0) {
        i = 0;
        do {
            ListRect *p;
            char *slot;
            ListVtable *v;
            int c;

            if (i == 7 && !menu->showSpecial)
                continue;
            p = (ListRect *)((float *)func_00335E10(o + 0x17C));
            p->x = D_001AE5D0 + menu->origin->x;
            p->y = (D_001AE5D4[0] + (float)i * D_001AE5D8) + (float)start;
            c = i == menu->selected ? color : 0x55F0C070;
            *((int *)func_00335E20(o + 0x1C8)) = c;
            func_00336320(o + 0x17C);
            p = (ListRect *)((float *)func_00335E10(o + 0x1C8));
            p->x = D_001AE5D0 + menu->origin->x;
            p->y = (D_001AE5D4[0] + (float)i * D_001AE5D8) + (float)start;
            func_00336320(o + 0x1C8);
            slot = (char *)&((ListSlot *)(o + 0x218))[i];
            p = (ListRect *)((float *)func_00335E10(slot));
            p->x = D_001AE5E0 + menu->origin->x;
            p->y = (D_001AE5E4[0] + (float)i * D_001AE5E8) + (float)start;
            v = *(ListVtable **)(o + i * 72 + 0x248);
            v->call(slot + v->offset);
        } while (++i < menu->count);
        }
    }
}

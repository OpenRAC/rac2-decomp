/* Closer C, 1 November 2026: the tail is exact with the store order below; 3 rows off, all at +0x38.
 * sched2 (BUF_LEN 4096 cc1, -dR -fsched-verbose-4): t8 ready 38[p6] 20[p9], so addu a1 (20) goes first.
 * Retail's order needs insn 20 at t9, one cycle after the mult's latency allows, though nothing else
 * feeds it. Same symptom as func_0027BA68 item 2 and func_L03_003C1BF0. -g, -G8, gcse, sched flags,
 * nine spellings of the table access and inline-free offsets all tie.
 */
/* func_0032D758 - 756 bytes, boot + 27 levels. Tier: opus-1 (Claude Opus 5.5), task v1660.
 * Best tools/check.py: 756/756 bytes, 0/28 USA v1.01 places (first difference +0x38).
 * Profile: default -O2 -G0 -ffunction-sections; place it in 00327038.c in place of the
 * INCLUDE_ASM marker (it calls func_0032D700 there, same catalogue places).
 * Declarations: put the block below "Declarations" after the existing
 * `extern NativeObjectSearchRecord32 D_L00_002533B0[];` of 00327038.c (it reuses that
 * table: its field14 is the slot's object pointer, the Slot of L00_003F87B0.c).
 *
 * What now agrees: the whole slot loop (counter t1, slot pointer a3 copied to s0, a
 * separate field pointer t0 = a3+0x14 for the test, both effect-parameter addresses
 * hoisted, 60 and 1/60 left in the body), the frame and every register outside the tail.
 * How: the test reads D_L00_002533B0[i].field14 directly (an array access, so its
 * address is (D+0x14)+i*32) and the slot pointer is taken after the test. loop.c then
 * reduces both as separate DEST_REG givs once D+0x14 is hoisted, which happens in the
 * second loop pass only when the loop has at most threshold (61 here) real insns: the
 * flag word read into a widened local (`flags = *(unsigned short *)(self + 0x34)`)
 * removes the HImode AND/zero_extend pair and brings the count from 62 to 61; with
 * 62 the test stays i<<5 + base and 60/1/60 placement or the givs come out wrong.
 *
 * Still different (two small clusters, everything else identical):
 *  +0x38..+0x44 entry: retail `addiu v1,lo(D_001A7A80); addu a1,a1,a3; daddu t2,v0;
 *    lh a2,0x4C(a1)`, ours `addu a1; addiu v1; lh; daddu t2` (sched2 ranks the
 *    critical-path addu/lh first; retail does not). An inline redirect helper and the
 *    `kind = index; if (D[index].kind) ...` wording do not help (the helper is worse).
 *  +0x284..+0x2A8 tail: retail loads 0x8000 into a2 before 1 into a0 and r into a1;
 *    ours loads 1 first and gives r a0, 1 a1 (local-alloc ranks r's shorter life
 *    first). Statement orders tried: color/active/flags (this one), flags before
 *    active (constants in retail order but then the stores swap and the registers
 *    stay wrong), constants before color (same as this one).
 * Contract: retail returns 1 when D_001A7A80[kind] & 8 is clear (+0x5C branches to the
 * shared return-1 exit), so `alternate` (s3, cleared at +0x88) is always defined where
 * the slot loop uses it; this control flow replaces the old draft's defaulted bank.
 * Earlier: orch/main sol-high integ draft (explicit scan pointer, offset precomputed)
 * 756/756 with the loop wrong; the previously retained draft here compiled 716 bytes.
 */
#include "common.h"

/* Declarations */
typedef struct { u8 field00[0x14]; void *field14; u8 field18[8]; } NativeObjectSearchRecord32;
extern NativeObjectSearchRecord32 D_L00_002533B0[];
extern s32 func_0032D700(void *object);
/* func_0032D758's effect type rows, kind flags and per-bank effect parameters. */
typedef struct { int active; unsigned char type; char pad[0x47]; short kind; char tail[0x92]; } EffectType;
extern EffectType D_00239BA0[];
extern unsigned char D_001A7A80[], D_00139568[];
typedef struct { float scale; int ticks; char pad[8]; } EffectParams;
extern EffectParams D_00236510[2][119];
extern float *func_002AB1F0(void *);
typedef struct { int remaining, color, flags, elapsed; float rate; char *object; int tag, active; } EffectSlot;
extern void func_002A04B8(void *, int *, int *, int *);

static __inline__ int EffectAlternate(int kind)
{
    EffectType *type = &D_00239BA0[D_00139568[kind]];
    if (type->active) {
        if (type->type == 2) return 1;
        if (type->type == 1) {
            int selected = 0;
            switch (kind) {
            case 12: case 14: case 17: case 18: case 53: selected = 1; break;
            }
            if (selected) return 1;
        }
    }
    return 0;
}

static __inline__ int EffectThird(int kind)
{
    EffectType *type = &D_00239BA0[D_00139568[kind]];
    int result = 0;
    if (type->active) result = type->type == 3;
    return result;
}

int func_0032D758(char *self, int index, int arg)
{
    int kind = D_00239BA0[index].kind;
    int result = 1, alternate;
    int i, r, g, b;
    char *p;
    float *health;
    if (!kind) kind = index;
    if (!(D_001A7A80[kind] & 8)) return result;
    alternate = 0;
    if (EffectAlternate(kind) || EffectThird(kind)) alternate = 1;
    if (*(short *)(*(char **)(self + 0x24) + 0x46) != 5) return 1;
    if (!(*(unsigned short *)(self + 0x34) & 0x1000)) return 1;
    if (*(signed char *)(self + 0x20) < 0) return 1;
    if (!*(int *)(self + 0x98)) return 1;
    health = func_002AB1F0(self);
    if (!health || *health <= 0.0f) return 1;
    if (func_0032D700(self) != -1) return 1;
    for (i = 0; i < 30; i++) {
        EffectSlot *slot;
        int found;
        unsigned int flags;
        if (D_L00_002533B0[i].field14)
            continue;
        slot = (EffectSlot *)&D_L00_002533B0[i];
        found = 0;
        slot->object = self;
        slot->remaining = D_00236510[alternate][index].ticks * 60;
        slot->rate = D_00236510[alternate][index].scale * 0.01666667f;
        flags = *(unsigned short *)(self + 0x34);
        if (flags & 0x20) {
            char *colour = *(char **)(*(char **)(self + 0x68) + 0x10);
            if (colour && *(short *)colour) {
                r = *(unsigned char *)(colour + 4);
                g = *(unsigned char *)(colour + 5);
                b = *(unsigned char *)(colour + 6);
                found = 1;
            }
        }
        if (!found) func_002A04B8(slot->object, &r, &g, &b);
        slot->elapsed = 0;
        slot->flags = 0x8000;
        slot->color = (b << 16) + (g << 8) + r;
        slot->tag = arg;
        slot->active = 1;
        result = 0;
        break;
    }
    return result;
}

/* Retained meaningful C; not matching. 2026-10-28 game -O2 -G0
 * -ffunction-sections -g: 568/568 bytes in both US placements. Remaining
 * difference: initial record pointer and missing-value sentinel use a2/a1,
 * while retail uses a1/a2 (first+0x60). Reversing the two independent
 * distance reads fixes their order. Typed record prefix and incoming FP-bank
 * interleaving tie; -fno-regmove also ties. No volatile or raw aliases used.
 * Callees: vector difference writes a16-byte destination, squared distance
 * returns float, diagnostic output is variadic void. Local vectors are fully
 * initialized by those observed quadword operations before being read.
 * Reopen with a measured scratch-GPR lifetime witness. No strict-build claim.
 */
#include "common.h"
typedef unsigned int SoundVectorQuad __attribute__((mode(TI)));
typedef union { SoundVectorQuad q; float f[4]; } SoundVector;
struct SoundRecordView { char unknown0[0x7e]; short id; char unknown80[4]; int level; void *owner; };
extern unsigned char D_00188660[];
extern const char D_L08_001AA400[];
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_0026FEB8(const char *, ...);
/* The sound table owner has unknown complete extent. Retail indexes 112-byte
 * records and accesses halfword +0x7e and words +0x84/+0x88 of that address view.
 * The two local vectors and the state's first vector are 16-byte aligned by the
 * retail lq/sq contract; no extra object extent or zero initialization is assumed. */
int func_L08_00339220(unsigned char *owner, unsigned char *state, int low, int high, float distance)
{
    SoundVector position;
    SoundVector difference;
    struct SoundRecordView *record;
    unsigned char *definition;
    int id, current, value;
    float near_distance, far_distance;
    if (*(void **)(state + 0x1c) != owner) return -1;
    record = (struct SoundRecordView *)(D_00188660 + *(int *)(state + 0x20) * 0x70);
    if (record->owner != owner) return -1;
    id = record->id;
    if (id != *(int *)(state + 0x18)) return -1;
    definition = *(unsigned char **)(*(unsigned char **)(owner + 0x24) + 0x28) + id * 32;
    if (low == -100000) low = *(int *)(definition + 0x10);
    if (high == -100000) high = *(int *)(definition + 0x14);
    current = record->level;
    far_distance = *(float *)(state + 0x14);
    near_distance = *(float *)(state + 0x10);
    if (distance < -999.0f) {
        func_00282CF0(&difference, owner + 0x10, state);
        position.q = difference.q;
        distance = func_00282DF0(&position);
    }
    value = (int)(((float)(high - low) / (far_distance - near_distance)) * (distance - near_distance) + (float)low);
    *(SoundVectorQuad *)state = *(SoundVectorQuad *)(owner + 0x10);
    if (current < value && current < high) {
        int delta = value - current;
        int step = delta < 251 ? delta : 250;
        int next;
        if (step < 50) step = delta;
        record = (struct SoundRecordView *)(D_00188660 + *(int *)(state + 0x20) * 0x70);
        next = record->level + step;
        if (next < high) record->level = next;
        else record->level = high;
        return 1;
    }
    if (value < current && low < current) {
        int delta = current - value;
        int step = delta < 251 ? delta : 250;
        int next;
        if (step < 50) step = delta;
        record = (struct SoundRecordView *)(D_00188660 + *(int *)(state + 0x20) * 0x70);
        next = record->level - step;
        if (next > low) record->level = next;
        else record->level = low;
        func_0026FEB8(D_L08_001AA400, value);
        return 2;
    }
    return 0;
}

/* func_L08_00339220 - 568 bytes, 2 place(s), level 08_tabora, retail at
   0x00339220. Screened with tools/w10_screen.py: 3 call(s)
   [func_00282CF0@003392F4, func_00282DF0@00339304, func_0026FEB8@00339410];
   data addresses materialised [0x190000, 0xfffe0000, 0xc4790000, 0x1b0000];
   float constants [-]; $gp-relative small data: no   saves: -; callee-saved
   registers saved [-]; words plain C cannot emit [LQ/SQ 7BA20010@0x00dc,
   LQ/SQ 7FA20000@0x00e8, COP1 46800020@0x0100, LQ/SQ 7A620010@0x0104, COP1
   468010A0@0x0114, LQ/SQ 7E020000@0x0118, COP1 46000064@0x0130]. Head:
   addiu $sp, $sp, -0x80 ; sd $s0, 0x20($sp) ; sd $s2, 0x30($sp) ; daddu
   $s0, $a1, $zero ; sd $s3, 0x38($sp) ; daddu $s2, $a2, $zero. Not matched
   in this wave: the 128-bit copy needs an `lq`/`sq` pair; plain C reaches
   it only through a `mode(TI)` local, and this cc1 folds the destination
   offset into the `sq` where retail materialises the pointer first. What
   would unblock it: the exact source expression tree, so this cc1 picks the
   same registers in the same order. */

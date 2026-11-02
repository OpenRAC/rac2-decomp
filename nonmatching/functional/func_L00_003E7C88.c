/* functional: high. Same walk over the fade records, calls and compaction as retail; only register allocation and instruction order differ. */
/*
 * Retained manual C reconstruction; not linked or counted.
 * Profile: -O2 -G8 -ffunction-sections, as its own unit
 * src/levels/shared/L00_003E7C88-g8.c (take the marker out of L00_003E3258.c).
 * Retail: 436 bytes; compiled: 412 bytes.
 * Coverage: us: 0/27 (tools/check.py, 28 October 2026, master 85614b41).
 *
 * Fades the 32-byte records of the table at 0x24EFC0: a fading record advances and is
 * drawn; a finished one runs its completion callback (or frees its object) and is
 * replaced by the last record.
 *
 * The record count at 0x1B2B60 is one plain extern: the assembler reaches it through
 * $gp in branch delay slots and absolutely elsewhere, exactly as retail does. The
 * 0x1B0648 address needs the SDATA view. What differs is the loop: retail keeps
 * separate induction registers (record pointer, &fade, i * 32, the table base and
 * base - 0x20 for the last record) in all of $s0-$s7, and with no registers left
 * it does not hoist 1/60 or 0x80; cc1 builds fewer induction variables and hoists
 * those constants (24 bytes shorter).
 * Tried: 1/60 as a division with and without -ffast-math; all 256 combinations of
 * pointer and indexed spellings of the eight record accesses (all tie at 108 lines).
 * Next: a loop shape that makes loop.c keep i * 32 as its own induction variable.
 */
#include "common.h"

extern char D_L00_0024EFC0[];
extern int D_L00_001B2B60;

/* One 32-byte record of the table at D_L00_0024EFC0. */
typedef struct {
    char *object;
    unsigned char rgb[4];
    int pad8;
    float fade;
    void (*done)(char *);
    int pad14[3];
} FadeRec_3E7C88;

extern float D_L00_001B065C_gp SDATA(D_L00_001B065C);
extern char D_L00_001B0648[] SDATA(D_L00_001B0648);
extern char *D_L00_001B0650;

extern float func_002AA2E8(float *, float, float);
extern void func_L00_003E7E40(char *, char *, float);
extern void func_L00_003E80A8(int, char *);
extern void func_002A0488(void *, int, int, int);
extern void func_0029F338(void *);

void func_L00_003E7C88(void)
{
    FadeRec_3E7C88 *recs;
    char *object;
    int i;

    if (D_L00_001B2B60 <= 0)
        return;
    recs = (FadeRec_3E7C88 *)D_L00_0024EFC0;

    for (i = 0; i < D_L00_001B2B60; i++) {
        object = recs[i].object;
        if (recs[i].fade != 0.0f) {
            func_002AA2E8(&recs[i].fade, 0.0f, D_L00_001B065C_gp * 0.016666668f);
            func_L00_003E7E40(object, D_L00_001B0648, recs[i].fade);
            func_L00_003E80A8(i, D_L00_001B0650);
        } else {
            if (recs[i].done != 0) {
                func_002A0488(object, recs[i].rgb[0], recs[i].rgb[1], recs[i].rgb[2]);
                object[0x23] = 0x80;
                *(unsigned short *)(object + 0x34) &= ~2;
                recs[i].done(object);
            } else {
                func_0029F338(object);
            }
            D_L00_001B2B60--;
            recs[i] = recs[D_L00_001B2B60];
        }
    }
}

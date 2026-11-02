/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/* func_0033A520 (360 bytes, boot + 27 levels, src/game/003399B0.c, default -G0) - near miss.
   Opus 5.5 xhigh (opus-1), 31 October 2026: EXACT BYTES IN USA v1.01, NOT CLAIMED AS A MATCH, not
   integrated. Two things stop it landing: a do/while (0) wrapper (below), and PAL and v2.00.

   Best check.py results:
   - The form below, with the wrapper: 360/360 bytes, 28 of 28 USA v1.01 places. PAL and v2.00: 0 of
     28 each, 8 words differ, all field offsets (0x1F8, 0x1FC, 0x200, 0x204 are +0x10 there, 0x134 and
     0x170 are not). One definition cannot give both; the function needs carry.py --demote or a ruling.
     No linked build was run.
   - The plain C at the end of this file, which breaks no rule: 360/360 bytes, 0 of 28 places, 25 of
     the 90 words differ, all in +0x58..+0xBC, with relocated halves and call targets masked (cdiff.py
     shows 34 rows, 8 of them calls; earlier records counted 26).

   The exact form, in place of the INCLUDE_ASM line in src/game/003399B0.c (the file already declares
   the typedefs, func_00335F88 and D_001ADC88):

   extern void func_00336710(void *a0, void *a1, void *a2);
   extern int *func_00335E20(void *a0);
   extern void func_003369A8(void *a0, void *a1, void *a2);
   extern int *func_00336DA8(int a0, int a1);
   extern int func_00336E40(void *a0);
   extern const f32 D_001B23A4 __attribute__((sda));

   void func_0033A520(unsigned char *obj, void *arg)
   {
       float v;
       float *p;
       char *text;

       *(int *)(obj + 0x1F8) = 0;
       *(void **)(obj + 0x200) = arg;
       if (arg != 0) {
           int *alloc = func_00336DA8(16, func_00336E40(arg));
           *(int **)(obj + 0x1FC) = alloc;
           alloc[1] = 0;
           alloc[2] = 0;
           alloc[3] = 0;
           alloc[0] = 0;
       }
       do {
           v = (float)(int)(D_001B23A4 * 300.0f + 0.5f);
           p = *(float **)(obj + 0x1FC);
           p[0] = 70.0f;
       } while (0);
       text = D_001ADC88;
       p = *(float **)(obj + 0x1FC);
       p[1] = v;
       func_00336710(obj + 0x134, text, *(void **)(obj + 0x200));
       func_00335F88(obj + 0x134, 24.0f, 24.0f, 0.0f, 0.0f);
       *func_00335E20(obj + 0x134) = 0x60F0F0B0;
       v = 65.0f;
       *(float *)(obj + 0x204) = v;
       func_003369A8(obj + 0x170, text, *(void **)(obj + 0x200));
       *func_00335E20(obj + 0x170) = 0x80F0F0F0;
       func_00335F88(obj + 0x170, 0.7f, 0.7f, 0.0f, 0.0f);
   }

   What each part of that form does. The byte effects were measured by taking each part away from the
   exact form; the reasons come from the scheduler and allocator dumps and recalled GCC behaviour, as
   no compiler source is at hand:
   - The wrapper. The LOOP_END note makes `lui $s1` a scheduling barrier, so the argument set-up stays
     after the conversion chain and block B comes out as retail's. Without it, 25 words differ. WORKER2.md
     rules this wrapper out until the maintainers answer the question in MATCHING-BLOCKERS.md, and no
     other construct found gives the same barrier.
   - `const` on D_001B23A4. An unchanging read has no anti-dependence on the later store to p[0], so
     300.0f goes first by insn order. Plain `extern float` with a store in the same block loads D first;
     scratch compiles of small functions show the same flip. D_001B23A4 is not really constant: 0x335DE0
     writes it. The const is a read-only view in this unit, and a reviewer has to accept that. The sda
     attribute stays, for the `lui $at` form at -G0.
   - One variable p for both reloads. Two deaths make it a global pseudo, so it is not kept off $v0 by
     local-alloc's false-dependency rule at the fix insn. Separate reloads put alloc in $v1 (2 words).
   - v reused for 65.0f. Again two deaths, so global, and it gets $f0. Otherwise $f1 (3 words).
   - -G8 is not needed: the form also matches 28 of 28 in the -g8 sibling, but no $gp access calls for it.

   This corrects the earlier record, which asked for a real block boundary after the rounding. With const
   and both reused variables, `if (obj) { A } else { A }` makes block A exact but leaves 7 words of block B
   wrong ($v0 reload before `lui $s1`, then the argument moves). A do/while (0) around an if on the
   rounded int, whose loop-end note then sits just before the join label, leaves block B wrong too; the
   note seems to count only inside a block. Retail looks like a loop note, not a merged branch. That
   rests on these measurements, not on the original source. Plain struct fields (mem/s) do not help: the load order and
   interleaving stay, and the clears lose their retail order. Inline helpers with a float parameter give
   the same bytes as a direct expression.

   Reopen with a ruling on non-empty do/while (0) wrappers, or evidence of the original construct. */

typedef float f32;
typedef unsigned char u8;
typedef int s32;
extern void func_00336710(void *a0, void *a1, void *a2);
extern void func_00335F88(void *a0, f32 a1, f32 a2, f32 a3, f32 a4);
extern int *func_00335E20(void *a0);
extern void func_003369A8(void *a0, void *a1, void *a2);
extern int *func_00336DA8(int a0, int a1);
extern int func_00336E40(void *a0);
extern char D_001ADC88[];
extern f32 D_001B23A4 __attribute__((sda));

void func_0033A520(u8 *obj, void *arg)
{
    f32 v;
    char *text;

    *(s32 *)(obj + 0x1F8) = 0;
    *(void **)(obj + 0x200) = arg;
    if (arg != 0) {
        s32 *alloc = func_00336DA8(16, func_00336E40(arg));
        *(s32 **)(obj + 0x1FC) = alloc;
        alloc[1] = 0;
        alloc[2] = 0;
        alloc[3] = 0;
        alloc[0] = 0;
    }
    v = (f32)(s32)(D_001B23A4 * 300.0f + 0.5f);
    ((f32 *)*(s32 **)(obj + 0x1FC))[0] = 70.0f;
    text = D_001ADC88;
    ((f32 *)*(s32 **)(obj + 0x1FC))[1] = v;
    func_00336710(obj + 0x134, text, *(void **)(obj + 0x200));
    func_00335F88(obj + 0x134, 24.0f, 24.0f, 0.0f, 0.0f);
    *func_00335E20(obj + 0x134) = 0x60F0F0B0;
    *(f32 *)(obj + 0x204) = 65.0f;
    func_003369A8(obj + 0x170, text, *(void **)(obj + 0x200));
    *func_00335E20(obj + 0x170) = 0x80F0F0F0;
    func_00335F88(obj + 0x170, 0.7f, 0.7f, 0.0f, 0.0f);
}

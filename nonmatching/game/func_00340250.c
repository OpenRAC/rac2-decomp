/* func_00340250 - 584 bytes.  Worker attempt, 27 October 2026 (draft below).

   596 B vs 584 (pointer-walk loops 604). Whole body decoded and matches in
   order: menu draw (func_336320 on parts, negate two floats via func_335E18
   twice, two 8-iteration jalr loops over 0x4C- and 0x3C-byte parts, footer
   color 0x80FFDE8D, func_34E2E0(D_001A8CFC+0x36F28,0xF3,0x2B,0x70)).
   Diff: gcc hoists the loop-2 address setup (self+0x61C into fp, self+0x5EC
   to the stack) above the earlier calls, so mine saves 9 regs (fp) and is
   longer; retail saves s0-s7 and sets s0/s1/s2 right before loop 2. Tried
   function-level vars, block-scoped vars, indexed loops, inline address
   exprs. */

/* in src/game/0033F030.c replacing the INCLUDE_ASM (D_00138344 may clash with a decl in the file) */
typedef struct {
    char pad00[8];
    short offset;
    short pad0A;
    void (*update)(void *);
} Part340250;

extern int D_00138344;
extern char *D_001A8CFC;
extern int func_002A9588(int, int, int, int, int);
extern int *func_00335E20(char *);
extern float *func_00335E18(char *);
extern void func_00336320(char *);
extern void func_00336A78(char *);
extern void func_00335E68(char *, int);
extern void func_00340638(char *);
extern void func_00340498(char *);
extern void func_0034E2E0(char *, int, int, int);

void func_00340250(char *self)
{
    float *p;

    if (*(int *)(self + 0xA58) == 0)
        return;
    if (D_00138344 & 0xF000)
        func_002A9588(0, 0, 1, 1, 1);
    *func_00335E20((self + 0x214)) = func_002A9588(0x60442D00, 0x70FFFEED, 0x14, 1, 0);
    func_00336320(self);
    func_00336320(self + 0x4C);
    func_00336320(self + 0xE4);
    func_00336320(self + 0x130);
    func_00336A78(self + 0x828);
    func_00336A78(self + 0x8B8);
    func_00336A78(self + 0x900);
    func_00336A78(self + 0x948);
    func_00336A78(self + 0x990);
    func_00335E68(self + 0x870, 0);
    func_00340638(self);
    func_00340498(self);
    func_00336320((self + 0x214));
    func_00336320((self + 0x2A8));
    func_00336320((self + 0x2F4));
    p = func_00335E18((self + 0x2A8));
    *p = -*p;
    p = func_00335E18((self + 0x2F4));
    *p = -*p;
    func_00336320((self + 0x2A8));
    func_00336320((self + 0x2F4));
    p = func_00335E18((self + 0x2A8));
    *p = -*p;
    p = func_00335E18((self + 0x2F4));
    *p = -*p;
    {
        int i;

        for (i = 0; i < 8; i++) {
            Part340250 *part = *(Part340250 **)(self + 0x370 + i * 0x4C);
            part->update(self + 0x340 + i * 0x4C + part->offset);
        }
        for (i = 0; i < 8; i++) {
            Part340250 *part = *(Part340250 **)(self + 0x61C + i * 0x3C);
            part->update(self + 0x5EC + i * 0x3C + part->offset);
        }
    }
    func_00336320((self + 0x5A0));
    *func_00335E20((self + 0x5A0)) = 0x80FFDE8D;
    func_0034E2E0(D_001A8CFC + 0x36F28, 0xF3, 0x2B, 0x70);
}

/* functional: high. Same averaging and radius pass over the three record groups as retail; the base pointer is formed differently. */
/* func_L07_0040F8F8 - 408 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   Best draft: 424 bytes vs 408, 71 masked diff lines. Control flow and the
   unreduced i*0x120 multiplies match.
   Differs: retail holds the array base in s6 (lui; addiu 0x100) and copies it
   to s5 (daddu s5,s6,zero), then uses
   lwc1 0xC($reg) offsets; mine folds +0xC into the symbol (separate lui/addiu
   for D+0xC) and keeps one base.
   Tried: Row[3][18] typed 2D array (432B), local Row(*)[18] pointer (380B),
   Group struct (376B), u8 byte macros (424B), local u8 *b copy. */

/* goes in L07_003F4578-g8.c (needs -G8; qzero from common.h, func_2E44D0 declared there) */
extern u8 D_L07_002A0100[];
extern void func_2E4310(void *a, void *b, u8 *c);
extern void func_2E4398(u8 *a, u8 *b, f32 c);
extern f32 func_2E44D0(u8 *a, u8 *b);

#define REC(i) (D_L07_002A0100 + (i) * 0x120)
#define REC2(i) (b + (i) * 0x120)
#define W(p) (*(f32 *)((p) + 0xC))

void func_L07_0040F8F8(void)
{
    f32 sum[4] __attribute__((aligned(16)));
    s32 i, n, k;
    u8 *b = D_L07_002A0100;

    for (i = 0; i < 3; i++) {
        n = 0;
        qzero(sum);
        if (W(REC(i)) == 1.0f) {
            do {
                func_2E4310(sum, sum, REC2(i) + n * 0x10);
                n++;
            } while (W(REC(i) + n * 0x10) == 1.0f);
        }
        func_2E4398(REC(i) + n * 0x10, REC(i) + n * 0x10, 1.0f / n);
        W(REC(i) + n * 0x10) = 0.0f;
        for (k = 0; k < n; k++) {
            f32 d = func_2E44D0(REC2(i) + k * 0x10, REC2(i) + n * 0x10) + 4.0f;
            if (W(REC2(i) + n * 0x10) < d)
                W(REC2(i) + n * 0x10) = d;
        }
    }
}

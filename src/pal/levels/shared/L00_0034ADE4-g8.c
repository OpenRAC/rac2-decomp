#include "common.h"

extern void func_0027C540(int);
extern void func_PAL_L00_0030F458(void);
extern s32 func_00288FB8(s32);
extern void func_0027F980(int, int, u64, u8 *, int);
extern void func_0027C660(void);
extern int ref_PAL_L00_0034ADE4_00 __attribute__((sda));
extern int ref_PAL_L00_0034ADE4_01[] __attribute__((sda));

/* func_PAL_L00_0034ADE4, the PAL copy of func_002CF2B8: the same C, where the
 * text position comes from two PAL words in place of 0x1A5 and the scaled 256,
 * the string id becomes 0xB60, and the draw call is func_0027F980. Retail reads
 * the first word through $gp and the second through lui, hence the two
 * declaration forms, as in func_PAL_002CE388. */
int func_PAL_L00_0034ADE4(void)
{
    func_0027C540(0);
    func_PAL_L00_0030F458();
    func_0027F980(ref_PAL_L00_0034ADE4_00, ref_PAL_L00_0034ADE4_01[0], 0x80F0F0F0ULL,
                  (u8 *)func_00288FB8(0xB60), -1);
    func_0027C660();
    return 0;
}

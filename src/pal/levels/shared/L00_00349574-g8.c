#include "common.h"

extern void SetupGifPaging(int);
extern void DoGifPaging(void);
extern char *GetLocalizedString(s32);
extern void func_PAL_L00_0030F3E8(void);
extern int D_PAL_001ABD48 __attribute__((sda));
extern int D_PAL_001ABD4C[] __attribute__((sda));

extern void text_draw_right_aligned_small(int, int, u64, char *, int);

/* func_PAL_L00_00349574, the PAL copy of func_002CDA20: the same shape, where the
 * text position comes from two PAL words in place of 0x1A5 and the scaled 293,
 * the string id becomes 0xB60, the second call is the PAL level's own
 * func_PAL_L00_0030F3E8 and the draw call is func_0027F980. As in
 * func_PAL_002CE388, retail reads the first word through $gp and the second
 * through lui, hence the two declaration forms and the -G8 unit. */
int func_PAL_L00_00349574(void)
{
    SetupGifPaging(0);
    func_PAL_L00_0030F3E8();
    text_draw_right_aligned_small(D_PAL_001ABD48, D_PAL_001ABD4C[0], 0x80F0F0F0ULL, (char *)GetLocalizedString(0xB60), -1);
    DoGifPaging();
    return 0;
}

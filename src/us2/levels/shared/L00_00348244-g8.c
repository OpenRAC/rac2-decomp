#include "include_asm.h"
#include "names.h"

extern void SetupGifPaging(int);
extern void func_US2_L00_0030E7E0(void);
extern char *GetLocalizedString(int);
extern void text_draw_right_aligned_small(int, int, unsigned long long, unsigned char *, int);
extern void DoGifPaging(void);
extern int D_US2_L00_001ABD20 __attribute__((sda));
extern int D_US2_L00_001ABD24;

/* func_US2_L00_00348244, the USA v2.00 relative of func_002CDA20: the same draw sequence,
   with the text id 0x2BE5, the position read from a level pair (not the boot unit's D_001ABA90 pair) and func_0027F980 drawing it. */
int func_US2_L00_00348244(void)
{
    SetupGifPaging(0);
    func_US2_L00_0030E7E0();
    text_draw_right_aligned_small(D_US2_L00_001ABD20, D_US2_L00_001ABD24, 0x80F0F0F0ULL, (unsigned char *)GetLocalizedString(0x2BE5), -1);
    DoGifPaging();
    return 0;
}

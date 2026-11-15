#include "include_asm.h"

#include "common.h"

/* func_US2_002D6024, the v2.00 copy of func_002D53F0: a text draw whose y also moves in display mode 1. */
extern float D_001B23A4[] __attribute__((sda));
extern int D_001B23A0[] __attribute__((sda));
extern void SetupGifPaging(long);
extern void func_US2_0029D368(void);
extern s32 GetLocalizedString(s32);
extern void text_draw_right_aligned_small(int, int, u64, u8 *, int);
extern void DoGifPaging(void);

static __inline__ int scaled_screen_coord(float value, float offset)
{
    float scaled = value * D_001B23A4[0] + 0.5f;
    if (D_001B23A0[0] == 1)
        return (int)(scaled + offset);
    return (int)scaled;
}

int func_US2_002D6024(void)
{
    int y;

    SetupGifPaging(0);
    func_US2_0029D368();
    y = scaled_screen_coord(329.0f, -36.0f);
    text_draw_right_aligned_small(0x1C7, y, 0x80F0F0F0ULL, (u8 *)GetLocalizedString(0x2BE5), -1);
    DoGifPaging();
    return 0;
}

extern char *D_001A8CFC[] __attribute__((sda));
extern char *D_001A8CFC[] __attribute__((sda));
extern char *D_001A8CFC[] __attribute__((sda));
extern void menu_clear_counter(void);
extern void func_US2_00342450(char *, char *, char *, char *);
extern void func_US2_00342520(char *, int);
extern char D_002615F8[], D_00261698[], D_00261750[];

int func_US2_002D60E8(void)
{
    menu_clear_counter();
    if (D_001A8CFC[0] != 0) {
        func_US2_00342450(D_001A8CFC[0] + 0x3C160, D_002615F8, D_00261698, D_00261750);
        func_US2_00342520(D_001A8CFC[0] + 0x3C160, 1);
    }
    return 0;
}


extern int D_00138344;
extern int D_00138344;
extern void func_US2_0029DD40(int);

/* func_002D2918 is built from 002D2918-g8.c. */

int func_US2_002D6158(void) {
    func_US2_0029DD40(D_00138344);
    return 0;
}


/* func_002D2918 is built from 002D2918-g8.c. */

int func_US2_002D6180(void) {
    func_US2_0029DD40(D_00138344);
    return 0;
}


#include "common.h"
extern void SetupGifPaging(long);
extern void func_US2_0029DD10(void);
extern void DoGifPaging(void);

int func_US2_002D61A8(void)
{
  SetupGifPaging(0);
  func_US2_0029DD10();
  DoGifPaging();
  return 0;
}



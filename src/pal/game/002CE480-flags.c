#include "include_asm.h"
#include "names.h"
extern void SetupGifPaging(long);
extern void DoGifPaging(void);
unsigned long long menu_draw_page_style_a(void);
extern void func_0029C1D8(void);
void SetupGifPaging(long);
void DoGifPaging(void);
extern void SetupGifPaging(long arg0);
extern void SetupGifPaging(long param_1);

/* Draws a menu page of the first style between SetupGifPaging and DoGifPaging (PAL). */
unsigned long long menu_draw_page_style_a_pal(void)
{
  SetupGifPaging(0);
  func_0029C1D8();
  DoGifPaging();
  return 0;
}

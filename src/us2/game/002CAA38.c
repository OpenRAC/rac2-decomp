#include "include_asm.h"
#include "names.h"

extern char *g_resident_data_base[] __attribute__((sda));
extern void popup_set_box_value(void *, int);
extern char *g_resident_data_base[] __attribute__((sda));
extern void popup_set_box_value(void *, int);
extern char *func_00288FB8_1 ();
extern void text_draw_medium (int v, int p7, long k, int r, int m1);
extern void text_draw_right_aligned_medium (int v, int p7, long k, int r, int m1);
extern void SetupGifPaging(long);
extern void DoGifPaging(void);

int menu_disable_subsystem_us2(void) {
    if (g_resident_data_base[0] != 0)
        popup_set_box_value(g_resident_data_base[0] + 0x3CEA0, 0);
    return 0;
}

int menu_enable_subsystem_us2(void) {
    if (g_resident_data_base[0] != 0)
        popup_set_box_value(g_resident_data_base[0] + 0x3CEA0, 1);
    return 0;
}

/* func_US2_002CAAA8, a v2.00 copy of func_002C9B88: the same two draw calls with string ids 12744
   and 12740, bracketed by func_0027C540(0) and func_0027C660(). */
int func_US2_002CAAA8 (int *p)
{
  int a;
  int t;
  int diff;
  int sum;
  int r;

  SetupGifPaging (0);
  a = p[6];
  t = p[8] >> 1;
  diff = a - t;
  sum = a + t;

  r = func_00288FB8_1 (12744);
  text_draw_medium (diff, p[7], (long) 0x80f0f0f0, r, -1);
  r = func_00288FB8_1 (12740);
  text_draw_right_aligned_medium (sum, p[7], (long) 0x80f0f0f0, r, -1);
  DoGifPaging ();
  return 0;
}

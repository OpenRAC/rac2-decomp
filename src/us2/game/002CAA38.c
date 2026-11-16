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

/* Tells the sound or menu system to turn off, then returns 0. */
int menu_disable_subsystem_us2(void) {
    if (g_resident_data_base[0] != 0)
        popup_set_box_value(g_resident_data_base[0] + 0x3CEA0, 0);
    return 0;
}

/* Tells the sound or menu system to turn on, then returns 0. */
int menu_enable_subsystem_us2(void) {
    if (g_resident_data_base[0] != 0)
        popup_set_box_value(g_resident_data_base[0] + 0x3CEA0, 1);
    return 0;
}

/* func_US2_002CAAA8, a v2.00 copy of func_002C9B88: the same two draw calls with string ids 12744
   and 12740, bracketed by func_0027C540(0) and func_0027C660(). */
/* Draws two small text labels on either side of a menu item. Returns 0. */
int menu_draw_item_side_icons_us2 (int *item)
{
  int center_x;
  int half_width;
  int left_x;
  int right_x;
  int text;

  SetupGifPaging (0);
  center_x = item[6];
  half_width = item[8] >> 1;
  left_x = center_x - half_width;
  right_x = center_x + half_width;

  text = func_00288FB8_1 (12744);
  text_draw_medium (left_x, item[7], (long) 0x80f0f0f0, text, -1);
  text = func_00288FB8_1 (12740);
  text_draw_right_aligned_medium (right_x, item[7], (long) 0x80f0f0f0, text, -1);
  DoGifPaging ();
  return 0;
}

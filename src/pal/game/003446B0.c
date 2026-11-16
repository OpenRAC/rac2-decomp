#include "include_asm.h"
#include "names.h"

void option_list_draw_rows(int);
void option_list_draw_rows(int param_1);

void list_menu_draw_scroller_pal(int param_1)
{
  option_list_draw_rows(param_1 + 0x188);
  return;
}


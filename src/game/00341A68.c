#include "include_asm.h"
#include "names.h"

void option_list_draw_rows(int);

void option_list_draw_rows(int param_1);

/* Draws the scrolling list part of the tabbed menu. */
void tab_menu_draw_list(int object)
{
  option_list_draw_rows(object + 0x228);
  return;
}

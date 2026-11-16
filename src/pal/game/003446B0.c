#include "include_asm.h"
#include "names.h"

void option_list_draw_rows(int);
void option_list_draw_rows(int param_1);

/* Draws the rows of the list menu's child list. */
void list_menu_draw_scroller_pal(int menu)
{
  option_list_draw_rows(menu + 0x188);
  return;
}


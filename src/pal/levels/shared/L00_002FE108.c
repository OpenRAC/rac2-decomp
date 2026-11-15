#include "include_asm.h"
#include "names.h"

void gfx_call_sync_helper(void);

void func_PAL_L00_002FE108(void)
{
  cam_init_scene_state();
  return;
}


void func_PAL_L00_002FE128(void)
{
  gfx_restore_draw_position();
  return;
}


void func_PAL_L00_002FE148(void)
{
  func_PAL_00278E60();
  return;
}


void func_PAL_L00_002FE168(void)
{
  text_draw_screen_wipe();
  return;
}


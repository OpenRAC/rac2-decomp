#include "include_asm.h"
#include "names.h"

void gfx_call_sync_helper(void);

/* Calls cam_init_scene_state. */
void level_call_cam_init_scene_state_pal(void)
{
  cam_init_scene_state();
  return;
}


/* Calls gfx_restore_draw_position. */
void level_call_gfx_restore_draw_position_pal(void)
{
  gfx_restore_draw_position();
  return;
}


/* Calls the PAL disc player sequence update. */
void level_call_seq_update_disc_player_pal(void)
{
  seq_update_disc_player_pal();
  return;
}


/* Calls text_draw_screen_wipe. */
void level_call_text_draw_screen_wipe_pal(void)
{
  text_draw_screen_wipe();
  return;
}


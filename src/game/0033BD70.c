#include "names.h"


#ifndef RAC2_T_S32_F09F721E0
#define RAC2_T_S32_F09F721E0
typedef int s32_F09f721e0;
#endif

#ifndef RAC2_T_F32_F09F721E0
#define RAC2_T_F32_F09F721E0
typedef float f32_F09f721e0;
#endif

extern void *pool_alloc_cell (s32_F09f721e0, s32_F09f721e0);

extern void *ui_return_second_arg (s32_F09f721e0, s32_F09f721e0);

extern void prompt_bar_init (s32_F09f721e0, s32_F09f721e0, const void *);

extern char *GetLocalizedString (s32_F09f721e0);

extern void prompt_bar_set_texts (s32_F09f721e0, s32_F09f721e0, s32_F09f721e0, s32_F09f721e0);

extern void prompt_bar_set_text_offsets (s32_F09f721e0, f32_F09f721e0, f32_F09f721e0, f32_F09f721e0, f32_F09f721e0, f32_F09f721e0, f32_F09f721e0);

extern void prompt_bar_set_spacing (s32_F09f721e0, f32_F09f721e0);

extern int screen_adjust_menu_update (s32_F09f721e0, s32_F09f721e0);

extern s32_F09f721e0 g_screen_adjust_prompt_data __attribute__ ((sda));

/* Sets up the screen-adjust menu: its button prompt bar, labels and position. */
void screen_adjust_menu_init (s32_F09f721e0 self, s32_F09f721e0 arg)
{
  s32_F09f721e0 prompt;
  s32_F09f721e0 allocation;
  s32_F09f721e0 textA, textB;
  *(s32_F09f721e0 *) self = arg;
  if (arg != 0)
    {
      allocation = ui_return_second_arg (16, pool_alloc_cell (arg, arg));
      *(s32_F09f721e0 *) (self + 684) = allocation;
      ((s32_F09f721e0 *) allocation)[1] = 0;
      ((s32_F09f721e0 *) allocation)[2] = 0;
      ((s32_F09f721e0 *) allocation)[3] = 0;
      ((s32_F09f721e0 *) allocation)[0] = 0;
    }
  prompt = self + 8;
  ((f32_F09f721e0 *) *(s32_F09f721e0 *) (self + 684))[0] = 255.0f;
  ((f32_F09f721e0 *) *(s32_F09f721e0 *) (self + 684))[1] = 195.0f;
  prompt_bar_init (prompt, arg, &g_screen_adjust_prompt_data);
  textA = GetLocalizedString (12773);
  textB = GetLocalizedString (11598);
  prompt_bar_set_texts (prompt, textA, textB, GetLocalizedString (11599));
  prompt_bar_set_text_offsets (prompt, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
  prompt_bar_set_spacing (prompt, 0.65f);
  *(s32_F09f721e0 *) (self + 680) = 0;
  *(s32_F09f721e0 *) (prompt + 668) = 0;
  screen_adjust_menu_update (self, 0);
}

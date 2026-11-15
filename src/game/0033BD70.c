#include "names.h"


#ifndef RAC2_T_S32_F09F721E0
#define RAC2_T_S32_F09F721E0
typedef int s32_F09f721e0;
#endif

#ifndef RAC2_T_F32_F09F721E0
#define RAC2_T_F32_F09F721E0
typedef float f32_F09f721e0;
#endif

extern s32_F09f721e0 func_00336E40 (s32_F09f721e0, s32_F09f721e0);

extern s32_F09f721e0 func_00336DA8 (s32_F09f721e0, s32_F09f721e0);

extern void func_0033ABD8 (s32_F09f721e0, s32_F09f721e0, const void *);

extern s32_F09f721e0 func_00288FB8 (s32_F09f721e0);

extern void func_0033B050 (s32_F09f721e0, s32_F09f721e0, s32_F09f721e0, s32_F09f721e0);

extern void func_0033B030 (s32_F09f721e0, f32_F09f721e0, f32_F09f721e0, f32_F09f721e0, f32_F09f721e0, f32_F09f721e0, f32_F09f721e0);

extern void func_0033B0A8 (s32_F09f721e0, f32_F09f721e0);

extern void func_0033BE98 (s32_F09f721e0, s32_F09f721e0);

extern s32_F09f721e0 D_L04_001AE040 __attribute__ ((sda));

/* Sets up the screen-adjust menu: its button prompt bar, labels and position. */
void func_0033BD70 (s32_F09f721e0 self, s32_F09f721e0 arg)
{
  s32_F09f721e0 prompt;
  s32_F09f721e0 allocation;
  s32_F09f721e0 textA, textB;
  *(s32_F09f721e0 *) self = arg;
  if (arg != 0)
    {
      allocation = ReturnSecondArgument (16, AllocPoolCell (arg, arg));
      *(s32_F09f721e0 *) (self + 684) = allocation;
      ((s32_F09f721e0 *) allocation)[1] = 0;
      ((s32_F09f721e0 *) allocation)[2] = 0;
      ((s32_F09f721e0 *) allocation)[3] = 0;
      ((s32_F09f721e0 *) allocation)[0] = 0;
    }
  prompt = self + 8;
  ((f32_F09f721e0 *) *(s32_F09f721e0 *) (self + 684))[0] = 255.0f;
  ((f32_F09f721e0 *) *(s32_F09f721e0 *) (self + 684))[1] = 195.0f;
  InitButtonPromptBar (prompt, arg, &D_L04_001AE040);
  textA = GetLocalizedString (12773);
  textB = GetLocalizedString (11598);
  SetButtonPromptTexts (prompt, textA, textB, GetLocalizedString (11599));
  SetButtonPromptTextOffsets (prompt, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
  SetButtonPromptSpacing (prompt, 0.65f);
  *(s32_F09f721e0 *) (self + 680) = 0;
  *(s32_F09f721e0 *) (prompt + 668) = 0;
  UpdateScreenAdjustMenu (self, 0);
}

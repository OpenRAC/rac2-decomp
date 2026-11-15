#include "names.h"


#ifndef RAC2_T_S32_FEE27D7BC
#define RAC2_T_S32_FEE27D7BC
typedef int s32_Fee27d7bc;
#endif

#ifndef RAC2_T_F32_FEE27D7BC
#define RAC2_T_F32_FEE27D7BC
typedef float f32_Fee27d7bc;
#endif

extern s32_Fee27d7bc func_00336E40_2 (s32_Fee27d7bc, s32_Fee27d7bc);

extern s32_Fee27d7bc func_00336DA8_2 (s32_Fee27d7bc, s32_Fee27d7bc);

extern void func_0033ABD8_2 (s32_Fee27d7bc, s32_Fee27d7bc, const void *);

extern void func_0033B030_2 (s32_Fee27d7bc, f32_Fee27d7bc, f32_Fee27d7bc, f32_Fee27d7bc, f32_Fee27d7bc, f32_Fee27d7bc, f32_Fee27d7bc);

extern void func_003361E0 (s32_Fee27d7bc, const void *, s32_Fee27d7bc);

extern s32_Fee27d7bc func_00335E20_2 (s32_Fee27d7bc);

extern void func_00336390 (s32_Fee27d7bc, const void *, s32_Fee27d7bc);

extern void func_00339798 (s32_Fee27d7bc);

extern char D_L04_001ADF08[];

extern s32_Fee27d7bc D_L04_001A904C;

extern s32_Fee27d7bc D_L04_001ADEF8 __attribute__ ((sda));

/* Sets up a small pop-up message box at the lower middle of the screen with its title text. */
void func_00339630 (s32_Fee27d7bc popup, s32_Fee27d7bc parent)
{
  s32_Fee27d7bc cell;
  *(s32_Fee27d7bc *) popup = parent;
  if (parent != 0)
    {
      cell = func_00336DA8_2 (16, func_00336E40_2 (parent, parent));
      *(s32_Fee27d7bc *) (popup + 756) = cell;
      ((s32_Fee27d7bc *) cell)[1] = 0;
      ((s32_Fee27d7bc *) cell)[2] = 0;
      ((s32_Fee27d7bc *) cell)[3] = 0;
      ((s32_Fee27d7bc *) cell)[0] = 0;
    }
  ((f32_Fee27d7bc *) *(s32_Fee27d7bc *) (popup + 756))[0] = 256.0f;
  ((f32_Fee27d7bc *) *(s32_Fee27d7bc *) (popup + 756))[1] = 212.0f;
  *(s32_Fee27d7bc *) (popup + 760) = 0;
  func_0033ABD8_2 (popup + 8, parent, &D_L04_001ADEF8);
  func_0033B030_2 (popup + 8, 64.0f, -164.0f, 10.0f, 136.0f, 10.0f, 99.0f);
  InitDerivedArrays (popup + 680, D_L04_001ADF08, parent);
  cell = func_00335E20_2 (popup + 680);
  *(s32_Fee27d7bc *) cell = 0x70FFFEED;
  SetFieldAt40 (popup + 680, D_L04_001A904C + 0x8710, 214);
  InitPopupTextsHidden (popup);
  *(s32_Fee27d7bc *) (popup + 768) = 0;
}

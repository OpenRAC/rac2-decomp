#include "include_asm.h"
#include "names.h"

extern void func_0027C540_2(long);
extern void module_l00_call_handler_4(void);
extern void func_0027C660_2(void);

/* Run the three measured setup calls with an explicit long zero, then return the defined integer zero. */
int level_l00_run_setup_return_zero_pal(void)
{
  func_0027C540_2(0);
  module_l00_call_handler_4();
  func_0027C660_2();
  return 0;
}


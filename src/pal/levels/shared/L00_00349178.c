#include "include_asm.h"
#include "names.h"

unsigned long long level_l00_run_setup_return_zero_long(void);
extern void func_0027C540_9(long);
extern void module_l00_call_handler_6(void);
extern void func_0027C660_9(void);

/* Run the three measured setup calls with an explicit long zero, then return the defined integer zero. */
unsigned long long level_l00_run_setup_return_zero_long_pal(void)
{
  func_0027C540_9(0);
  module_l00_call_handler_6();
  func_0027C660_9();
  return 0;
}


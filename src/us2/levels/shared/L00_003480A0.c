#include "include_asm.h"
#include "names.h"

extern int D_L00_001A904C_3 __attribute__((sda));
extern int grid_menu_get_selected_text_id(int x);

/* When the global is set, derives a pointer from it plus a fixed offset, runs it through a callee and stores the result into a field of the argument. */
int level_l00_store_table_entry_in_object_us2(int *obj)
{
    if (D_L00_001A904C_3 != 0)
        obj[13] = grid_menu_get_selected_text_id(D_L00_001A904C_3 + 0x3A000);
    return 0;
}

extern void func_0027C540_7(long);
extern void module_l00_call_handler_11(void);
extern void func_0027C660_7(void);

/* Run the three measured setup calls with an explicit long zero, then return the defined integer zero. */
long long level_l00_run_setup_return_zero_long_2_us2(void)
{
    func_0027C540_7(0LL);
    module_l00_call_handler_11();
    func_0027C660_7();
    return 0LL;
}


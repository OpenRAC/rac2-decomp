#include "include_asm.h"
#include "names.h"
extern int D_L01_001A8F40;
extern char D_L01_001A90C8 __attribute__((sda));
extern int D_L01_001A90D0 __attribute__((sda));
extern int math_fast_float_d(char *);
extern void level_clear_table_entry(int);

int func_PAL_L01_002F2BD8(void) {
    if (D_L01_001A8F40 == 0) {
        if (math_fast_float_d(&D_L01_001A90C8))
            level_clear_table_entry(0);
    }
    return D_L01_001A90D0;
}

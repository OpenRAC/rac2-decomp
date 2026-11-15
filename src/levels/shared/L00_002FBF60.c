#include "include_asm.h"
#include "names.h"

extern int ref_L00_002FBF60_00;

extern int ref_L00_002FC008_00;

extern int ref_L00_002FC018_00;

extern int ref_L00_002FC020_00;

extern int ref_L00_002FC028_00;

/* Turns a flag on. */
void level_set_flag_c_true(void)
{
    ref_L00_002FBF60_00 = 1;
}

/* Turns a flag on. */
void level_set_flag_d_true(void)
{
    ref_L00_002FC008_00 = 1;
}

/* Gets a stored flag value. */
int level_get_flag_d(void)
{
    return ref_L00_002FC018_00;
}

/* Turns a flag off. */
void level_clear_flag_e(void)
{
    ref_L00_002FC020_00 = 0;
}

/* Turns a flag off. */
void level_clear_flag_f(void)
{
    ref_L00_002FC028_00 = 0;
}




extern int r1_func_0011CC38_002FC588();

/* rac1-decomp src/core/00119D88.c: func_0011CCB0 */
/* Returns its callee's value: retail keeps the frame and calls, and
   2.9-ee would tail-call it (a bare `j`) if it were void. */
int level_call_helper_b(void) {
    return r1_func_0011CC38_002FC588();
}

extern int r1_func_0011CC38_002FC5A8();

/* rac1-decomp src/core/00119D88.c: func_0011CCB0 */
/* Returns its callee's value: retail keeps the frame and calls, and
   2.9-ee would tail-call it (a bare `j`) if it were void. */
int level_call_helper_c(void) {
    return r1_func_0011CC38_002FC5A8();
}

extern int r1_func_0011CC38_002FC5C8();

/* rac1-decomp src/core/00119D88.c: func_0011CCB0 */
/* Returns its callee's value: retail keeps the frame and calls, and
   2.9-ee would tail-call it (a bare `j`) if it were void. */
int level_call_helper_d(void) {
    return r1_func_0011CC38_002FC5C8();
}

extern int r1_func_0011CC38_002FC5E8();

/* rac1-decomp src/core/00119D88.c: func_0011CCB0 */
/* Returns its callee's value: retail keeps the frame and calls, and
   2.9-ee would tail-call it (a bare `j`) if it were void. */
int level_call_helper_e(void) {
    return r1_func_0011CC38_002FC5E8();
}


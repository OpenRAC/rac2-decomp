#include "names.h"
/* func_L00_00403CB8 in its own unit (default flags): it registers arg in the
   first free one of the 16 slots at 0x001B2C30 or, when func_L00_00403C30 says
   the table is busy, evicts a random slot (both release hooks see it) and puts
   arg there. The plain indexed loop is what gives retail its second walking
   pointer and the copy in the beqz delay slot. */
#include "common.h"
extern int *g_sheep_active_list[] MACRO_ADDR;
extern int sheep_is_active_list_full(void);
extern int math_random_int_below(int n);
extern void func_L00_00403900(int *v);
extern void func_L00_00403C68(int *v);

/* Adds a sheep to the list of 16 active sheep. If the list is full, a random old sheep is removed to make room. */
void sheep_add_to_active_list(int *arg)
{
    if (sheep_is_active_list_full() == 0) {
        int i;
        for (i = 0; i < 16; i++) {
            if (g_sheep_active_list[i] == 0) {
                g_sheep_active_list[i] = arg;
                return;
            }
        }
    } else {
        int **slot = &g_sheep_active_list[math_random_int_below(16)];
        func_L00_00403900(*slot);
        func_L00_00403C68(*slot);
        *slot = arg;
    }
}

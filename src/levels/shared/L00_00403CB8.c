/* func_L00_00403CB8 in its own unit (default flags): it registers arg in the
   first free one of the 16 slots at 0x001B2C30 or, when func_L00_00403C30 says
   the table is busy, evicts a random slot (both release hooks see it) and puts
   arg there. The plain indexed loop is what gives retail its second walking
   pointer and the copy in the beqz delay slot. */
#include "common.h"
extern int *D_L00_001B2C30[] MACRO_ADDR;
extern int func_L00_00403C30(void);
extern int func_002A77E0(int n);
extern void func_L00_00403900(int *v);
extern void func_L00_00403C68(int *v);

/* Adds a sheep to the list of 16 active sheep. If the list is full, a random old sheep is removed to make room. */
void func_L00_00403CB8(int *arg)
{
    if (IsActiveSheepListFull() == 0) {
        int i;
        for (i = 0; i < 16; i++) {
            if (D_L00_001B2C30[i] == 0) {
                D_L00_001B2C30[i] = arg;
                return;
            }
        }
    } else {
        int **slot = &D_L00_001B2C30[RandomIntBelow(16)];
        func_L00_00403900(*slot);
        func_L00_00403C68(*slot);
        *slot = arg;
    }
}

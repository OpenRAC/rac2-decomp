#include "include_asm.h"

extern unsigned char D_0019B278[28][4];

extern int func_US2_002B1C90(int index);

extern int D_US2_00258CF0[21];

/* Sums the counts of every entry but 26, and clamps the total to 0..40. */
int func_US2_002B1C20(void)
{
    int count = 0;
    int i;

    for (i = 0; i < 28; i++) {
        if (i != 26) {
            count += func_US2_002B1C90(i);
        }
    }
    if (count < 0) {
        count = 0;
    }
    if (count > 40) {
        count = 40;
    }
    return count;
}

/* Counts the non-zero bytes of a 4-byte table entry, entry 2 also counting entry 26, and clamps
   the count to 0..40. */
int func_US2_002B1C90(int index)
{
    int count = 0;
    int i;
    int j;

    for (i = 0; i < 4; i++) {
        if (D_0019B278[index][i] != 0) {
            count++;
        }
    }
    if (index == 2) {
        for (j = 0; j < 4; j++) {
            if (D_0019B278[26][j] != 0) {
                count++;
            }
        }
    }
    if (count < 0) {
        count = 0;
    }
    if (count > 40) {
        count = 40;
    }
    return count;
}

/* Entry of a 21-entry table, 0 past its end. */
int func_US2_002B1D18(unsigned int index)
{
    if (index < 21) {
        return D_US2_00258CF0[index];
    }
    return 0;
}

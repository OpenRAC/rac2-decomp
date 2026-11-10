/* func_002F7320: needs -frac2-keep-block-zero-copy (cse keeps `i = result`); see docs/build/compiler-notes.md. */
#include "common.h"

typedef struct {
    int key;
    int values[3];
} Func_002F7320Row;

extern Func_002F7320Row ref_L00_002F7320_00[];

int func_002F7320(int value, int key, int field)
{
    int result = 0;
    int i = result;

    while (ref_L00_002F7320_00[i].key != 0 && i < 56 && key != ref_L00_002F7320_00[i].key)
        i++;
    if (ref_L00_002F7320_00[i].key != 0)
        result = value == ref_L00_002F7320_00[i].values[field];
    return result;
}

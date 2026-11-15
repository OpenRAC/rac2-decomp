#include "names.h"


extern int ref_L00_002F0E20_00 __attribute__((sda));

extern int ref_L00_002F0E20_01 __attribute__((sda));

extern int ref_L00_002F0E20_02 __attribute__((sda));

extern int ref_L00_002F0E20_03;

/* Stores four numbers into four global settings. */
void settings_store_four(int first, int second, int third, int fourth)
{
    ref_L00_002F0E20_00 = first;
    ref_L00_002F0E20_01 = second;
    ref_L00_002F0E20_02 = third;
    ref_L00_002F0E20_03 = fourth;
}

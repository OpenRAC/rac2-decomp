#include "names.h"
typedef int TI128 __attribute__((mode(TI)));

extern TI128 D_L00_001B1D20 __attribute__((sda));
extern TI128 D_L00_001B1D30 __attribute__((sda));
extern TI128 D_L00_001B1D40 __attribute__((sda));
extern TI128 D_L00_001B1D50 __attribute__((sda));
extern TI128 *D_L00_001B1D60 __attribute__((sda));

/* Copies four 16-byte blocks into global storage and remembers where the data after them starts. */
void level_load_quadword_block(TI128 *src) {
    D_L00_001B1D20 = *src++;
    D_L00_001B1D30 = *src++;
    D_L00_001B1D40 = *src++;
    D_L00_001B1D50 = *src++;
    D_L00_001B1D60 = src;
}

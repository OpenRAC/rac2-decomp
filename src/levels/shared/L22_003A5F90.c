#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef float f32;

extern int func_002A77E0(int);
extern int D_L22_001B2AA8;
extern int *D_L22_001B2AB4;

/* Restores one of three stats on the object, picking one at random and topping up the first one that is below its maximum. */
void func_L22_003A5F90(u8 *obj)
{
    u8 *vars = *(u8 **)(obj + 0x68);
    int choice = RandomIntBelow(3);
    int limit = D_L22_001B2AA8;
    int *stats;
    int limitCopy;
    int startChoice;

    if ((f32)(limit / 6) >= *(f32 *)(vars + 0x20)) {
        choice = 0;
    }
    stats = D_L22_001B2AB4;
    limitCopy = limit;
    startChoice = choice;
    do {
        if (choice == 0) {
            if (*(f32 *)(vars + 0x20) < (f32)(limitCopy / 3)) {
                *(f32 *)(vars + 0x20) = *(f32 *)(vars + 0x20) + (f32)*(short *)(vars + 0x322);
                return;
            }
        } else if (choice == 1) {
            if (stats[2] < *(short *)(vars + 0x32A)) {
                stats[2] = stats[2] + *(short *)(vars + 0x32A) / 2;
                if (stats[2] > *(short *)(vars + 0x32A)) {
                    stats[2] = *(short *)(vars + 0x32A);
                }
                return;
            }
        } else if (choice == 2) {
            if (stats[3] < *(short *)(vars + 0x32E)) {
                stats[3] = stats[3] + *(short *)(vars + 0x32E) / 2;
                if (stats[3] > *(short *)(vars + 0x32E)) {
                    stats[3] = *(short *)(vars + 0x32E);
                }
                return;
            }
        }
        choice = (choice + 1) % 3;
    } while (choice != startChoice);
}


#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef float f32;

extern int math_random_int_below(int);
extern int g_space_ship_max_health;
extern int *g_space_ship_pickup_slots;

/* Restores one of three stats on the object, picking one at random and topping up the first one that is below its maximum. */
void stat_restore_random(u8 *obj)
{
    u8 *vars = *(u8 **)(obj + 0x68);
    int choice = math_random_int_below(3);
    int limit = g_space_ship_max_health;
    int *stats;
    int limitCopy;
    int startChoice;

    if ((f32)(limit / 6) >= *(f32 *)(vars + 0x20)) {
        choice = 0;
    }
    stats = g_space_ship_pickup_slots;
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


#include "common.h"

extern int D_L09_00255E90[];
extern int D_L09_001B35E0[] MACRO_ADDR;
extern int D_L09_001B36E0[] MACRO_ADDR;
extern int D_L09_001B3720[] MACRO_ADDR;

extern void func_00291450(int);

/* Frees the beam link slot that holds this id and stops its two sounds. Returns 1 if a slot was freed, else 0. */
int func_L09_003FB788(int id) {
    int i;
    for (i = 0; i < 16; i++) {
        if (D_L09_00255E90[i * 2] == id || D_L09_00255E90[i * 2 + 1] == id) {
            D_L09_001B35E0[i] = 0;
            D_L09_00255E90[i * 2] = 0;
            D_L09_00255E90[i * 2 + 1] = 0;
            if (D_L09_001B36E0[i] != -1) {
                FreePointLight(D_L09_001B36E0[i]);
                D_L09_001B36E0[i] = -1;
            }
            if (D_L09_001B3720[i] != -1) {
                FreePointLight(D_L09_001B3720[i]);
                D_L09_001B3720[i] = -1;
            }
            return 1;
        }
    }
    return 0;
}

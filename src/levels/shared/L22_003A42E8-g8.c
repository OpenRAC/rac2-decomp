#include "include_asm.h"
#include "names.h"

extern char g_hero_state[];

extern int D_L22_001B2AC8 __attribute__((sda));

extern int D_L22_001B2AC8_2;

extern int D_L22_001B2ACC __attribute__((sda));

extern int D_L22_001B2ACC_2;

extern int D_L22_001B2AD0;

extern int D_L22_001AF384 __attribute__((sda));

extern char D_L22_001B1910[];

/* Raises one of three level values by its step and clamps it to its limit. Retail reads the
 * entry word again after the stores to the globals; built with -fno-gcse, as here, this cc1
 * does too (gcse otherwise keeps the earlier load across those stores). The stores through
 * $gp and through $at are retail's two forms of the same globals. */
/* Gives the ship the effect of a pickup: more health, more ammo for one side, or more of the third value. Returns 1 when something was raised. */
int pickup_apply_to_ship(char *obj, int unused, int mode, int flag) {
    char *state = *(char **)(obj + 0x68);
    char *entry = D_L22_001B1910 + flag * 16;
    int result = 0;

    switch (mode) {
    case 0:
        if (flag) {
            char *g = g_hero_state;

            if (*(int *)(g + 0x1874) < *(short *)(state + 0x324)) {
                *(int *)(g + 0x1874) = *(int *)(g + 0x1874) + *(short *)(state + 0x320);
                if (*(short *)(state + 0x324) < *(int *)(g + 0x1874))
                    *(int *)(g + 0x1874) = *(short *)(state + 0x324);
                result = 1;
                D_L22_001B2AC8 = 0;
            }
        } else {
            float lim = (float)*(short *)(state + 0x24);

            if (*(float *)(state + 0x20) < lim) {
                *(float *)(state + 0x20) = *(float *)(state + 0x20) + (float)*(short *)(state + 0x322);
                if (lim < *(float *)(state + 0x20))
                    *(float *)(state + 0x20) = lim;
                result = 1;
            }
        }
        break;
    case 1: {
        int lim = *(short *)(state + 0x32A);
        if (*(int *)(entry + 8) < lim) {
            if (flag) {
                int step = *(short *)(state + 0x328);
                D_L22_001B2AC8 = 1;
                if (lim < *(int *)(entry + 8) + step)
                    D_L22_001B2ACC = lim - *(int *)(entry + 8);
                else
                    D_L22_001B2ACC_2 = step;
            }
            *(int *)(entry + 8) = *(int *)(entry + 8) + *(short *)(state + 0x328);
            if (*(short *)(state + 0x32A) < *(int *)(entry + 8))
                *(int *)(entry + 8) = *(short *)(state + 0x32A);
            result = 1;
        }
        break;
    }
    case 2:
        if (*(int *)(entry + 12) < *(short *)(state + 0x32E)) {
            *(int *)(entry + 12) = *(int *)(entry + 12) + *(short *)(state + 0x32C);
            if (*(short *)(state + 0x32E) < *(int *)(entry + 12))
                *(int *)(entry + 12) = *(short *)(state + 0x32E);
            result = 1;
            if (flag)
                D_L22_001B2AC8_2 = 2;
        }
        break;
    }
    if (result)
        D_L22_001B2AD0 = D_L22_001AF384;
    return result;
}

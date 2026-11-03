#include "common.h"

/* Built with -frac2-keep-block-order: the two mode cases stay separate
   switch arms, so cse does not carry the dispatch's base address into
   the default arm and each block re-adds %lo(D_00189E20), as in retail. */

extern char D_00189E20[];
extern unsigned char D_00139568[];
extern char D_L22_002645F0[];
extern int func_L00_002ADEA0(int index);

typedef struct {
    char pad_0[0x1492];
    unsigned char field_1492;
    char pad_1493[0x22B4 - 0x1493];
    unsigned char mode;
    char pad_22B5[0x22BA - 0x22B5];
    unsigned char field_22BA;
    char pad_22BB[0x24CC - 0x22BB];
    int field_24CC;
    char pad_24D0[0x24EC - 0x24D0];
    short field_24EC;
} State_002A8CE0;

typedef struct {
    char pad_0[0x28];
    int value;
    char pad_2C[0xE0 - 0x2C];
} Entry_002A8CE0;

#define STATE ((State_002A8CE0 *)D_00189E20)

/* Picks the shop entry the level's table names for the current progress state. */
int func_L22_002A8CE0(int check)
{
    switch (STATE->mode) {
    case 1:
        return 0;
    case 2:
        return 0;
    default:
        if (check && STATE->field_22BA && !STATE->field_24EC) {
            int index = func_L00_002ADEA0(0);

            return ((Entry_002A8CE0 *)D_L22_002645F0)[D_00139568[index]].value;
        }
        if (STATE->field_24CC != 1) {
            return STATE->field_1492 ? 0x67 : 0;
        }
        return 0x51;
    }
}

#undef STATE

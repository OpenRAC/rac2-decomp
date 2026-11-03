#include "common.h"

typedef struct {
    unsigned short id, kind;
    void *descriptor;
    unsigned short value, reserved;
} MenuEntry;
typedef struct { unsigned short id, reserved, value; char rest[6]; } SourceEntry;
extern int D_00139948[];
extern SourceEntry D_00262BE0[];
extern char D_0025E680[];
extern MenuEntry D_00210AF0[];
/* Retail rereads the list pointer at each search step. */
extern int * volatile D_001AA4F0 __attribute__((sda));
extern struct { char unknown00[0x230]; int selected; } D_001C4FA0;

int func_002DB988(char *object)
{
    int i, entry;
    int *list;
    for (i = 0; i < 28 && D_00139948[i]; i++) {
        D_00210AF0[i].kind = 3;
        D_00210AF0[i].descriptor = D_0025E680;
        D_00210AF0[i].id = D_00262BE0[D_00139948[i]].id;
        D_00210AF0[i].value = D_00262BE0[D_00139948[i]].value;
    }
    list = D_001AA4F0;
    D_00210AF0[i].id = 0;
    *(int *)(object + 0x40) = 0;
    *(unsigned int *)(object + 0x30) |= 0x8000;
    for (i = 0, entry = list[0]; entry; entry = D_001AA4F0[++i]) {
        if (D_001C4FA0.selected == entry) {
            *(int *)(object + 0x40) = i;
            break;
        }
    }
    return 0;
}

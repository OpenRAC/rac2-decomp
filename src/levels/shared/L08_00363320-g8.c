#include "include_asm.h"

typedef struct { unsigned short id, kind; void *callback; unsigned short value, pad; } InitEntry12;
extern int D_00139948[];
typedef struct { unsigned short id, pad, value; char rest[6]; } SourceEntry12;
extern SourceEntry12 D_L08_00295D20[];
extern char D_L08_002917E0[];
extern InitEntry12 D_L08_0021DC30[];
/* Reloaded at each search step in retail. */
extern int * volatile D_L08_001AA830 __attribute__((sda));
extern struct { char pad[0x230]; int selected; } D_L08_001CA0E0;

int func_L08_00363320(char *obj) {
    int i, entry;
    int *list;
    for (i = 0; i < 28 && D_00139948[i]; i++) {
        D_L08_0021DC30[i].kind = 3;
        D_L08_0021DC30[i].callback = D_L08_002917E0;
        D_L08_0021DC30[i].id = D_L08_00295D20[D_00139948[i]].id;
        D_L08_0021DC30[i].value = D_L08_00295D20[D_00139948[i]].value;
    }
    list = D_L08_001AA830;
    D_L08_0021DC30[i].id = 0;
    *(int *)(obj + 0x40) = 0;
    *(unsigned int *)(obj + 0x30) |= 0x8000;
    for (i = 0, entry = list[0]; entry; entry = D_L08_001AA830[++i]) {
        if (D_L08_001CA0E0.selected == entry) {
            *(int *)(obj + 0x40) = i;
            break;
        }
    }
    return 0;
}

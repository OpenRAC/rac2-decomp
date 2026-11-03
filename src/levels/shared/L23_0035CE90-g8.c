/* Initialization-table relative of func_L00_00354DF8. The measured entry
 * correction leaves the preceding function's tail in assembly. */
#include "include_asm.h"

typedef struct { unsigned short id, kind; void *callback; unsigned short value, pad; } InitEntry12;
extern int D_00139948[];
typedef struct { unsigned short id, pad, value; char rest[6]; } SourceEntry12;
extern SourceEntry12 D_L23_0028FA20[];
extern char D_L23_0028B4E0[];
extern InitEntry12 D_L23_0021E770[];
/* Reloaded at each search step in retail. */
extern int * volatile D_L23_001AA770 __attribute__((sda));
extern struct { char pad[0x230]; int selected; } D_L23_001CAC20;

int func_L23_0035CE90(char *obj) {
    int i, entry;
    int *list;
    for (i = 0; i < 28 && D_00139948[i]; i++) {
        D_L23_0021E770[i].kind = 3;
        D_L23_0021E770[i].callback = D_L23_0028B4E0;
        D_L23_0021E770[i].id = D_L23_0028FA20[D_00139948[i]].id;
        D_L23_0021E770[i].value = D_L23_0028FA20[D_00139948[i]].value;
    }
    list = D_L23_001AA770;
    D_L23_0021E770[i].id = 0;
    *(int *)(obj + 0x40) = 0;
    *(unsigned int *)(obj + 0x30) |= 0x8000;
    for (i = 0, entry = list[0]; entry; entry = D_L23_001AA770[++i]) {
        if (D_L23_001CAC20.selected == entry) {
            *(int *)(obj + 0x40) = i;
            break;
        }
    }
    return 0;
}

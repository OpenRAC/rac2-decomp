/* Build the menu rows in level order and select the current owner entry.
 * The +4 row field holds the level menu-data descriptor.
 * The list-pointer word is reloaded on every search step, as in retail.
 */
#include "include_asm.h"

typedef struct { unsigned short id, kind; void *payload; unsigned short value, pad; } InitEntry12;
extern int D_00139948[];
typedef struct { unsigned short id, pad, value; char rest[6]; } SourceEntry12;
extern SourceEntry12 D_L15_002A0020[];
extern char D_L15_0029BAC0[];
extern InitEntry12 D_L15_0021D8F0[];
/* Reloaded at each search step in retail. */
extern int * volatile D_L15_001AA7F0 __attribute__((sda));
extern struct { char pad[0x230]; int selected; } D_L15_001C9DA0;

int func_L15_0036DAB0(char *obj) {
    int i, entry;
    int *list;
    for (i = 0; i < 28 && D_00139948[i]; i++) {
        D_L15_0021D8F0[i].kind = 3;
        D_L15_0021D8F0[i].payload = D_L15_0029BAC0;
        D_L15_0021D8F0[i].id = D_L15_002A0020[D_00139948[i]].id;
        D_L15_0021D8F0[i].value = D_L15_002A0020[D_00139948[i]].value;
    }
    list = D_L15_001AA7F0;
    D_L15_0021D8F0[i].id = 0;
    *(int *)(obj + 0x40) = 0;
    *(unsigned int *)(obj + 0x30) |= 0x8000;
    for (i = 0, entry = list[0]; entry; entry = D_L15_001AA7F0[++i]) {
        if (D_L15_001C9DA0.selected == entry) {
            *(int *)(obj + 0x40) = i;
            break;
        }
    }
    return 0;
}

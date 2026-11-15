/* Initialization-table relative of func_L00_00354DF8. The measured current
 * correction leaves the preceding function's tail in assembly. */
#include "include_asm.h"
#include "names.h"

typedef struct { unsigned short id, kind; void *callback; unsigned short value, pad; } InitEntry12;
extern int D_00139948[];
typedef struct { unsigned short id, pad, value; char rest[6]; } SourceEntry12;
extern SourceEntry12 D_L23_0028FA20[];
extern char D_L23_0028B4E0[];
extern InitEntry12 D_L23_0021E770[];
/* Reloaded at each search step in retail. */
extern int * volatile D_L23_001AA770 __attribute__((sda));
extern struct { char pad[0x230]; int selected; } D_L23_001CAC20;

/* Fills the menu entry table from the list of item ids, then finds which entry is currently selected and stores its index in the menu object. */
int menu_init_entry_table(char *obj) {
    int i, current;
    int *select_list;
    for (i = 0; i < 28 && D_00139948[i]; i++) {
        D_L23_0021E770[i].kind = 3;
        D_L23_0021E770[i].callback = D_L23_0028B4E0;
        D_L23_0021E770[i].id = D_L23_0028FA20[D_00139948[i]].id;
        D_L23_0021E770[i].value = D_L23_0028FA20[D_00139948[i]].value;
    }
    select_list = D_L23_001AA770;
    D_L23_0021E770[i].id = 0;
    *(int *)(obj + 0x40) = 0;
    *(unsigned int *)(obj + 0x30) |= 0x8000;
    for (i = 0, current = select_list[0]; current; current = D_L23_001AA770[++i]) {
        if (D_L23_001CAC20.selected == current) {
            *(int *)(obj + 0x40) = i;
            break;
        }
    }
    return 0;
}

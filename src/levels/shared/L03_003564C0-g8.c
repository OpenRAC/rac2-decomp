/* Initialization-table relative of func_L00_00354DF8. The measured entry
 * correction leaves the preceding function's tail in assembly. */
#include "include_asm.h"
#include "names.h"

typedef struct { unsigned short id, kind; void *callback; unsigned short value, pad; } InitEntry12;
extern int D_00139948[];
typedef struct { unsigned short id, pad, value; char rest[6]; } SourceEntry12;
extern SourceEntry12 D_L03_0028FD60[];
extern char D_L03_0028B810[];
extern InitEntry12 D_L03_0021DB70[];
/* Reloaded at each search step in retail. */
extern int * volatile D_L03_001AA7B0 __attribute__((sda));
extern struct { char pad[0x230]; int selected; } D_L03_001CA020;

/* Fills the menu choice table from the list of unlocked entries and puts the cursor on the one currently selected. */
int menu_fill_choice_table(char *menu) {
    int i, value;
    int *idList;
    for (i = 0; i < 28 && D_00139948[i]; i++) {
        D_L03_0021DB70[i].kind = 3;
        D_L03_0021DB70[i].callback = D_L03_0028B810;
        D_L03_0021DB70[i].id = D_L03_0028FD60[D_00139948[i]].id;
        D_L03_0021DB70[i].value = D_L03_0028FD60[D_00139948[i]].value;
    }
    idList = D_L03_001AA7B0;
    D_L03_0021DB70[i].id = 0;
    *(int *)(menu + 0x40) = 0;
    *(unsigned int *)(menu + 0x30) |= 0x8000;
    for (i = 0, value = idList[0]; value; value = D_L03_001AA7B0[++i]) {
        if (D_L03_001CA020.selected == value) {
            *(int *)(menu + 0x40) = i;
            break;
        }
    }
    return 0;
}

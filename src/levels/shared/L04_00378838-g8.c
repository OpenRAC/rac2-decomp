/* func_L04_00378838, in levels 4 and 10, is a copy of func_L00_00354DF8 (L00_002FC7A8-g8.c)
 * with the levels' own tables, named here by level 4's addresses. Its catalogue entry starts
 * at 0x00378848 in level 4 and 0x00369160 in level 10, after the previous body's 16-byte tail
 * (FUNCTION_ENTRY_OFFSETS); the words at 04:0029FE90 and 10:0029F960 point there.
 */
#include "include_asm.h"

typedef struct { unsigned short id, kind; void *callback; unsigned short value, pad; } InitEntry12;
extern int D_00139948[];
typedef struct { unsigned short id, pad, value; char rest[6]; } SourceEntry12;
extern SourceEntry12 D_L04_002A4420[];
extern char D_L04_0029FEE0[];
extern InitEntry12 D_L04_0021D7B0[];
/* Reloaded at each search step in retail. */
extern int * volatile D_L04_001AA770 __attribute__((sda));
extern struct { char pad[0x230]; int selected; } D_L04_001C9C60;

int func_L04_00378838(char *obj) {
    int i, entry;
    int *list;
    for (i = 0; i < 28 && D_00139948[i]; i++) {
        D_L04_0021D7B0[i].kind = 3;
        D_L04_0021D7B0[i].callback = D_L04_0029FEE0;
        D_L04_0021D7B0[i].id = D_L04_002A4420[D_00139948[i]].id;
        D_L04_0021D7B0[i].value = D_L04_002A4420[D_00139948[i]].value;
    }
    list = D_L04_001AA770;
    D_L04_0021D7B0[i].id = 0;
    *(int *)(obj + 0x40) = 0;
    *(unsigned int *)(obj + 0x30) |= 0x8000;
    for (i = 0, entry = list[0]; entry; entry = D_L04_001AA770[++i]) {
        if (D_L04_001C9C60.selected == entry) {
            *(int *)(obj + 0x40) = i;
            break;
        }
    }
    return 0;
}

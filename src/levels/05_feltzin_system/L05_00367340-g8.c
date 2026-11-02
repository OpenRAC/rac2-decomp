/* func_L05_00367340 is the level 5 copy of func_L00_00354DF8 (L00_002FC7A8-g8.c), with the
 * level's own tables. Its catalogue entry starts at 0x00367350, after the previous body's
 * 16-byte tail (FUNCTION_ENTRY_OFFSETS); the word at 05:0029D4F0 points there.
 */
#include "include_asm.h"

typedef struct { unsigned short id, kind; void *callback; unsigned short value, pad; } InitEntry12;
extern int D_00139948[];
typedef struct { unsigned short id, pad, value; char rest[6]; } SourceEntry12;
extern SourceEntry12 D_L05_002A1AA0[];
extern char D_L05_0029D540[];
extern InitEntry12 D_L05_0021D7F0[];
/* Reloaded at each search step in retail. */
extern int * volatile D_L05_001AA770 __attribute__((sda));
extern struct { char pad[0x230]; int selected; } D_L05_001C9CA0;

int func_L05_00367340(char *obj) {
    int i, entry;
    int *list;
    for (i = 0; i < 28 && D_00139948[i]; i++) {
        D_L05_0021D7F0[i].kind = 3;
        D_L05_0021D7F0[i].callback = D_L05_0029D540;
        D_L05_0021D7F0[i].id = D_L05_002A1AA0[D_00139948[i]].id;
        D_L05_0021D7F0[i].value = D_L05_002A1AA0[D_00139948[i]].value;
    }
    list = D_L05_001AA770;
    D_L05_0021D7F0[i].id = 0;
    *(int *)(obj + 0x40) = 0;
    *(unsigned int *)(obj + 0x30) |= 0x8000;
    for (i = 0, entry = list[0]; entry; entry = D_L05_001AA770[++i]) {
        if (D_L05_001C9CA0.selected == entry) {
            *(int *)(obj + 0x40) = i;
            break;
        }
    }
    return 0;
}

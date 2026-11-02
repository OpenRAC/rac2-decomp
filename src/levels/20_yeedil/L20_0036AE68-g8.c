/* func_L20_0036AE68 is the level 20 copy of func_L00_00354DF8 (L00_002FC7A8-g8.c), with the
 * level's own tables. Its catalogue entry starts at 0x0036AE78, after the previous body's
 * 16-byte tail (FUNCTION_ENTRY_OFFSETS); the word at 20:00292390 points there.
 */
#include "include_asm.h"

typedef struct { unsigned short id, kind; void *callback; unsigned short value, pad; } InitEntry12;
extern int D_00139948[];
typedef struct { unsigned short id, pad, value; char rest[6]; } SourceEntry12;
extern SourceEntry12 D_L20_00296920[];
extern char D_L20_002923E0[];
extern InitEntry12 D_L20_0021E0F0[];
/* Reloaded at each search step in retail. */
extern int * volatile D_L20_001AA7F0 __attribute__((sda));
extern struct { char pad[0x230]; int selected; } D_L20_001CA5A0;

int func_L20_0036AE68(char *obj) {
    int i, entry;
    int *list;
    for (i = 0; i < 28 && D_00139948[i]; i++) {
        D_L20_0021E0F0[i].kind = 3;
        D_L20_0021E0F0[i].callback = D_L20_002923E0;
        D_L20_0021E0F0[i].id = D_L20_00296920[D_00139948[i]].id;
        D_L20_0021E0F0[i].value = D_L20_00296920[D_00139948[i]].value;
    }
    list = D_L20_001AA7F0;
    D_L20_0021E0F0[i].id = 0;
    *(int *)(obj + 0x40) = 0;
    *(unsigned int *)(obj + 0x30) |= 0x8000;
    for (i = 0, entry = list[0]; entry; entry = D_L20_001AA7F0[++i]) {
        if (D_L20_001CA5A0.selected == entry) {
            *(int *)(obj + 0x40) = i;
            break;
        }
    }
    return 0;
}

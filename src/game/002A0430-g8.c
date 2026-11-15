#include "include_asm.h"
#include "names.h"

extern short D_00264630[64][12];

/* Partial view of the resident global at D_001A7A00. Its fields are reached as
   symbol+offset with the section-only small-data model: the assembler expands
   each access to an absolute lui pair ($at for stores), and the compiler keeps
   them out of delay slots. */
typedef struct {
    unsigned char pad0[0x0A];
    unsigned char enabled; /* 0x0A */
    unsigned char pad0B[0x27];
    unsigned char limit; /* 0x32 */
    unsigned char count; /* 0x33 */
} Global001A7A00;
extern Global001A7A00 D_001A7A00 __attribute__((section(".sdata")));

extern int D_001A9E70;
extern unsigned short D_00188510[][2];
extern void level_forward_value(int);

/* Finds the row of D_00264630 whose first four ids hold the object's id at +0xAA,
   then counts it in column `type` of D_00188510 (capped at 9999). */
void moby_count_kill_or_event(char *moby, int type)
{
    int found = -1, i, j;
    int id = *(short *)(moby + 0xAA);

    for (i = 0; i < 64; i++) {
        for (j = 0; j < 4; j++) {
            if (id == D_00264630[i][j]) {
                found = i;
                break;
            }
        }
        if (found != -1) goto found_it;
    }
    if (found == -1) return;
found_it:
    if (D_001A7A00.enabled && D_001A9E70 == -1 && D_001A7A00.limit < 20) {
        D_001A7A00.count++;
        if (D_001A7A00.count * 2 >= D_001A7A00.limit) {
            level_forward_value(180);
            D_001A7A00.count = 0;
            D_001A7A00.limit++;
        }
    }
    if (type == 0) {
        if (D_00188510[found][0] < 9999) D_00188510[found][0]++;
    } else if (type == 1) {
        if (D_00188510[found][1] < 9999) D_00188510[found][1]++;
    }
}


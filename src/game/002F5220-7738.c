#include "common.h"

typedef struct { int value[36]; } Table36_7738;
typedef struct { int value[38]; } Table38_7738;
typedef struct { int value[13]; } Table13_7738;
extern Table36_7738 ref_L00_002F7738_00, ref_L00_002F7738_01;
extern Table36_7738 ref_L00_002F7738_02, ref_L00_002F7738_03;
extern Table36_7738 ref_L00_002F7738_04, ref_L00_002F7738_07;
extern Table38_7738 ref_L00_002F7738_05;
extern Table13_7738 ref_L00_002F7738_06;
typedef struct { int a, b, mask, expected, extra; char *text; int id; } Entry_7738;
typedef struct { char pad[0x140]; Entry_7738 entries[54]; char tail[24]; int count; } State_7738;
extern State_7738 ref_L00_002F7738_08;
extern unsigned int D_001A7AF0 MACRO_ADDR;
extern int func_002B0E90(void);
extern char *func_00288FB8(int);
/* The initial values of i, j and k are dead; they set gcse's hash table size, which
 * orders the spilled frame addresses in their retail stack slots. */
void func_002F7738(void)
{
    Table36_7738 ids = ref_L00_002F7738_00;
    Table36_7738 extra = ref_L00_002F7738_01;
    Table36_7738 masks = ref_L00_002F7738_02;
    Table36_7738 expected = ref_L00_002F7738_03;
    Table36_7738 a = ref_L00_002F7738_04;
    Table38_7738 limits = ref_L00_002F7738_05;
    Table13_7738 special = ref_L00_002F7738_06;
    Table36_7738 b = ref_L00_002F7738_07;
    int selected[20];
    int count = 0, i = 0, k = 0;
    int progress = func_002B0E90();
    if (((D_001A7AF0 & masks.value[0]) >> 4) == 0) selected[count++] = 0;
    if (((D_001A7AF0 & masks.value[2]) >> 6) == 0) selected[count++] = 2;
    switch ((D_001A7AF0 & masks.value[3]) >> 7) {
    case 0: selected[count++] = 3; break;
    case 1: selected[count++] = 4; break;
    }
    if (((D_001A7AF0 & masks.value[5]) >> 9) == 0) selected[count++] = 6;
    switch ((D_001A7AF0 & masks.value[7]) >> 10) {
    case 0: selected[count++] = 7; break;
    case 1: selected[count++] = 8; break;
    }
    switch ((D_001A7AF0 & masks.value[9]) >> 14) {
    case 0: selected[count++] = 9; break;
    case 1: selected[count++] = 10; break;
    }
    if (((D_001A7AF0 & masks.value[11]) >> 12) == 0) selected[count++] = 11;
    if (((D_001A7AF0 & masks.value[12]) >> 13) == 0) selected[count++] = 12;
    ref_L00_002F7738_08.count = 0;
    for (i = 0; i < count; i++) {
        k = selected[i];
        ref_L00_002F7738_08.entries[ref_L00_002F7738_08.count].b = b.value[k];
        ref_L00_002F7738_08.entries[ref_L00_002F7738_08.count].a = a.value[k];
        ref_L00_002F7738_08.entries[ref_L00_002F7738_08.count].text = GetLocalizedString(ids.value[k]);
        ref_L00_002F7738_08.entries[ref_L00_002F7738_08.count].id = extra.value[k];
        ref_L00_002F7738_08.entries[ref_L00_002F7738_08.count].mask = masks.value[k];
        ref_L00_002F7738_08.entries[ref_L00_002F7738_08.count].expected = expected.value[k];
        ref_L00_002F7738_08.entries[ref_L00_002F7738_08.count].extra = special.value[k];
        ref_L00_002F7738_08.count++;
    }
    {
        int j = 0;
        for (j = 13; j < 36; j++) {
            if ((masks.value[j] & D_001A7AF0) != expected.value[j] && progress >= limits.value[j]) {
                ref_L00_002F7738_08.entries[ref_L00_002F7738_08.count].b = b.value[j];
                ref_L00_002F7738_08.entries[ref_L00_002F7738_08.count].a = a.value[j];
                ref_L00_002F7738_08.entries[ref_L00_002F7738_08.count].text = GetLocalizedString(ids.value[j]);
                ref_L00_002F7738_08.entries[ref_L00_002F7738_08.count].id = ids.value[j];
                ref_L00_002F7738_08.entries[ref_L00_002F7738_08.count].mask = masks.value[j];
                ref_L00_002F7738_08.entries[ref_L00_002F7738_08.count].expected = expected.value[j];
                ref_L00_002F7738_08.count++;
            }
        }
    }
}

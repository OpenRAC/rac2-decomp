#include "common.h"
#include "include_asm.h"

extern int D_L00_001A903C;
extern int D_L00_001A7F8C __attribute__((sda));
extern u8 D_001A7BE0;
extern u8 D_001A7A60[] __attribute__((sda));
extern int math_fast_float_d(char *);
extern int save_count_nonzero_flags(void);
extern int level_get_resident_byte(void);
extern void value_set_entry_by_index(int, int);

/* Once the wait timer ends, picks a voice line to play from the current progress step, then restarts the timer. */
void hero_play_voice_line_for_progress(void)
{
    int count;
    int selector;
    int flag;

    if (D_L00_001A903C == 0)
        return;
    if (math_fast_float_d((char *)&D_L00_001A7F8C) == 0)
        return;
    count = save_count_nonzero_flags();
    selector = level_get_resident_byte();
    flag = D_001A7BE0;
    if (flag != 0 || selector > 0) {
        if (count == 3 || count == 10 || count == 15 || count == 19 || count == 25 || count == 29)
            value_set_entry_by_index(0x1B8C, -1);
        else if (count == 18 || count == 26)
            value_set_entry_by_index(0x1B8D, -1);
    }
    if (count == 7 || count == 20 || count == 30)
        value_set_entry_by_index(0x1B8F, -1);
    if (D_001A7A60[0] != 0)
        value_set_entry_by_index(0x1B8F, -1);
    D_L00_001A903C = 0;
    D_L00_001A7F8C = 300;
}

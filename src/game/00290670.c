#include "common.h"
#include "structs.h"

   /* current buffer */
extern short r1_D_0015EDC4;
extern void func_00290670(void);
extern int D_001A9018 __attribute__((sda));

/* Asks for the screen bars at the top to grow. */
void func_00290670(void) {
    gLetterboxGrowFlag = 1;
}


extern int D_001A9014 __attribute__((sda));
extern int D_001A9018 __attribute__((sda));
extern void func_0027DDC0(int, int, int, int);

/* Moves the screen bar level up or down by one step and draws the bar at its current height. */
void func_00290680(void)
{
    int level;
    int barHeight;

    if (gLetterboxGrowFlag != 0) {
        gLetterboxGrowFlag = 0;
        level = gLetterboxLevel + 1;
        gLetterboxLevel = level;
        if (level >= 11)
            gLetterboxLevel = 10;
    } else {
        level = gLetterboxLevel - 1;
        gLetterboxLevel = level;
        if (level < 0)
            gLetterboxLevel = 0;
    }
    barHeight = (int)((float)gLetterboxLevel * 0.1f * 48.0f);
    if (barHeight != 0)
        SetClearColorPacket(0, 0, 0, barHeight);
}

extern int D_001A901C __attribute__((sda));

/* Clears a HUD flag. */
void func_00290720(void) {
    D_001A901C = 0;
}

extern int D_001A9020 __attribute__((sda));

/* Clears a second HUD flag. */
void func_00290728(void) {
    D_001A9020 = 0;
}

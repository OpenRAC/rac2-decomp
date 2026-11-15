#include "include_asm.h"
#include "names.h"

extern float func_00283CE0_6(int a0);

extern int func_00283CF0_9(float x);

typedef int s32;

typedef unsigned char u8;

/* func_002EE6A8: owner ABI/declaration review retained. */
extern int moby_get_motion_data(unsigned char *owner);

/* func_002ED870: owner ABI/declaration review retained. */
extern unsigned int D_00214FCC;

/* Decomposes a float returned by a bound producer into hours, minutes and hundredths written through three pointer arguments, rounding each step with a bound helper and clamping the last field at 99. */
int math_split_time_into_parts(int value, int *outHours, int *outMinutes, int *outHundredths)
{
    float remaining;
    int hours;
    int hourSeconds;
    int minutes;
    int minuteSeconds;
    int hundredths;

    remaining = func_00283CE0_6(value);
    hours = func_00283CF0_9(remaining * (1.0f / 3600.0f));
    *outHours = hours;
    hourSeconds = func_00283CF0_9((float)hours * 3600.0f);
    remaining = remaining - (float)hourSeconds;
    minutes = func_00283CF0_9(remaining * 0.01666667f);
    *outMinutes = minutes;
    minuteSeconds = func_00283CF0_9((float)minutes * 60.0f);
    remaining = remaining - (float)minuteSeconds;
    hundredths = func_00283CF0_9(remaining * (5.0f / 3.0f));
    hundredths = hundredths > 99 ? 0 : hundredths;
    *outHundredths = hundredths;
    return hundredths;
}


/* Returns the object-specific data pointer of an object, or nothing if it has none. */
s32 moby_get_motion_data(u8 *a0) {
 if((*(unsigned short *)(a0+0x34)&0x20)==0) return 0;
 return (*(s32 **)(a0+0x68))[5];
}

/* func_002ED6B0 is in 002ED6B0.c: its call to func_002ED870 has to be an external one. */

/* Returns a saved scene setting. */
unsigned int scene_get_state_word(void)
{
    return D_00214FCC;
}



extern int D_00214F90[];

/* Frees an object's motion slot if it was in use. */
void moby_release_motion_slot(unsigned char *owner)
{
    char *data = (char *)moby_get_motion_data(owner);
    if (data != 0 && *(int *)(data + 0x118) == 1) {
        *(int *)(data + 0x118) = 0;
        D_00214F90[3]--;
    }
}

/* func_002EDA10 is in 002EDA10.c. */

/* func_002EE000 is in 002ED578-g8.c. */

/* func_002EE3B0 is in 002EE3B0-g8.c. */

#include "include_asm.h"
#include "names.h"

extern float func_00283CE0_6(int a0);

extern int func_00283CF0_9(float x);

typedef int s32;

typedef unsigned char u8;

/* func_002EE6A8: owner ABI/declaration review retained. */
extern int func_002ED688(unsigned char *owner);

/* func_002ED870: owner ABI/declaration review retained. */
extern unsigned int D_00214FCC;

/* Decomposes a float returned by a bound producer into hours, minutes and hundredths written through three pointer arguments, rounding each step with a bound helper and clamping the last field at 99. */
int func_002ED578(int value, int *outHours, int *outMinutes, int *outHundredths)
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
s32 func_002ED688(u8 *a0) {
 if((*(unsigned short *)(a0+0x34)&0x20)==0) return 0;
 return (*(s32 **)(a0+0x68))[5];
}

/* func_002ED6B0 is in 002ED6B0.c: its call to func_002ED870 has to be an external one. */

/* Returns a saved scene setting. */
unsigned int func_002ED870(void)
{
    return D_00214FCC;
}



extern int D_00214F90[];

/* Frees an object's motion slot if it was in use. */
void func_002ED9C0(unsigned char *owner)
{
    char *data = (char *)GetMobyMotionData(owner);
    if (data != 0 && *(int *)(data + 0x118) == 1) {
        *(int *)(data + 0x118) = 0;
        D_00214F90[3]--;
    }
}

/* func_002EDA10 is in 002EDA10.c. */

/* func_002EE000 is in 002ED578-g8.c. */

/* func_002EE3B0 is in 002EE3B0-g8.c. */

/* Reconstructed from retail; standalone all-placement checks pass in both USA releases (canonical name absent in PAL).
 * The lead must still verify strict linked builds. */
#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern char *func_0029EFD0(int);
extern float func_002A7878(float,float);
extern int func_002FED90(char *,int,float,float,float);
extern void func_002A0F48(char *);

/* Creates a Gravity Bomb projectile at the given position with the given direction and random spin. */
char *func_L00_003EED10(int owner, char *position, char *direction)
{
    char *object = CreateMoby(0xce4 /* moby class 3300 */);
    char *state;
    float first,second;
    unsigned char stamp;
    if (object != 0) {
        state = *(char **)(object + 0x68);
        stamp = 0xff;
        *(short *)(object + 0x32) = stamp;
        object[0x30] = stamp;
        object[0x20] = 0;
        *(TI128 *)(object + 0x10) = *(TI128 *)position;
        *(TI128 *)state = *(TI128 *)direction;
        *(float *)(object + 0x2c) = 0.01f;
        first = RandomFloatRange(0.052359886f,0.10471977f);
        *(float *)(state + 0x10) = first;
        second = RandomFloatRange(0.052359886f,0.10471977f);
        *(int *)(state + 0x30) = owner;
        *(int *)(state + 0x18) = 0;
        *(float *)(state + 0x14) = second;
        *(int *)(state + 0x34) = AllocEffectSlot_002FED90(object,0,1.0f,1.0f,1.0f);
        func_002A0F48(object);
    }
    return object;
}

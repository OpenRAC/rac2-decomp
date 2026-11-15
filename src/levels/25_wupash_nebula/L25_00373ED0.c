#include "include_asm.h"
#include "names.h"

/* func_L25_003752D8, func_L25_00376FE0 and func_L25_00377608 live in the sibling
   small-data unit (L25_00373ED0-g8.c): their loop counts are read through $gp. */


/* func_L25_0040CDA0 is in L25_00373ED0-mission-g8.c. */

/* func_L25_0040D208 is in L25_00373ED0-hud-g8.c. */

extern char *func_002A9640(char *a0, int a1, int a2);

extern void func_002AB8C0(char *a0, char *a1);

extern void func_002AB800(char *a0, char *a1);

extern int func_002E5DA0(int index, int value, char *object, int kind);

extern void func_L05_00424990(void *a0, void *a1, int a2, int a3, int a4, int a5, int a6, int a7,
                              int a8, int a9, int a10, float f12);

extern void func_L05_00421908(char *a0, int a1, int a2);

extern int func_L05_0037BBB8(char *a0);

extern void func_L05_0037BE98(char *a0);

extern void func_L05_0037AE40(char *a0);

/* The moby's death timer: it ticks the stored time down and, once it reaches zero,
   fires the object's effect and takes the moby down, which it reports. */
int func_L25_0040DCD0(char *objectMoby, int flag)
{
    char *effectLink;
    float *timerPtr;
    char *frameInfo;
    char *vars;
    int ret = 0;

    frameInfo = FindOwnedEffectSlot(objectMoby, 0x230000, 0);
    *(unsigned char *)(objectMoby + 0xA8) = 0xFF;
    vars = *(char **)(objectMoby + 0x68);
    effectLink = *(char **)(vars + 0x10);
    timerPtr = *(float **)(vars + 0x0);
    if (effectLink != 0) {
        UpdateColorFade(objectMoby, effectLink);
    }
    if (frameInfo != 0) {
        if (effectLink != 0) {
            *(unsigned char *)(effectLink + 7) = 0xFF;
            StartColorFade(objectMoby, effectLink);
        }
        *timerPtr = *timerPtr - *(float *)(frameInfo + 0x2C);
        if (*(short *)(objectMoby + 0xAA) != 0xB73 /* moby class 2931 */) {
            PlaySoundFromClassBank(2, 0, objectMoby, 0x957);
        }
        if (*timerPtr <= 0.0f) {
            *timerPtr = 0.0f;
            SpawnShockwaveBurst(objectMoby + 0x10, 0, 0x32, 0x1E, 0x1E, 0x1E, 0x28, 1, 1, 0, 0, 0.5f);
            func_L05_00421908(objectMoby, 1, 0x19);
            if (IsObjectInUse(objectMoby)) {
                ReleaseObjectFromGroup(objectMoby);
            }
            if (flag == 0) {
                ResetObjectActionState(objectMoby);
            }
            ret = 1;
        }
    }
    return ret;
}

/* func_L25_0040DE40 is defined in L25_00373ED0-fade-g8.c. */

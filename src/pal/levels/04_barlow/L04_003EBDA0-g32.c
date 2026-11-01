#include "include_asm.h"

typedef struct {
    char reserved00[0x1830];
    char *player;
    char reserved1834[0xA60];
    int mode;
} L04DispatchGlobals;
extern L04DispatchGlobals D_00189E20;
extern int D_L04_001AFFA0[8] __attribute__((sda));
extern short D_L04_001AFFC0[10] __attribute__((sda));
extern int D_L04_001AFFD4 __attribute__((sda));
extern int D_L04_001AFFD8 __attribute__((sda));
extern char D_L04_002AF6C0[], D_L04_002405C0[], D_L04_00240660[], D_L04_002BA660[];
extern void func_L04_003E7FE8(void);
extern void func_L00_002E6EF8(void);
extern void func_PAL_L04_003A47C0(void *);
extern void func_PAL_L04_003A49E0(void *);
extern void func_L04_003A1FA0(void *);
extern void func_L04_003A1FE0(void *);
extern void func_L04_003A5C08(void *, float);

void func_PAL_L04_003EBDA0(char *object)
{
    char *state;
    L04DispatchGlobals *globals = &D_00189E20;
    char *player = globals->player;
    if (player && *(short *)(player + 0xAA) == 0x45 &&
        (unsigned char)player[0x20] != 0xFE && (unsigned char)player[0x20] != 0xFD &&
        globals->mode == 0x31) return;
    state = *(char **)(object + 0x68);
    if (state) {
        int index = *(int *)(state + 0x18);
        int increment = 1;
        if (index != -1) increment = D_L04_001AFFA0[index];
        {
            int args[13];
            increment += *(int *)(state + 0x10);
            args[0] = 10;
            args[1] = increment;
            args[8] = (int)&D_L04_001AFFD4;
            args[9] = (int)&D_L04_001AFFD8;
            args[2] = (int)D_L04_002AF6C0;
            args[3] = (int)D_L04_002405C0;
            args[4] = (int)D_L04_001AFFC0;
            args[5] = (int)D_L04_001AFFA0;
            args[6] = (int)D_L04_00240660;
            args[7] = (int)D_L04_002BA660;
            args[11] = (int)func_L04_003E7FE8;
            args[12] = (int)func_L00_002E6EF8;
            args[10] = (int)object;
            switch ((unsigned char)object[0x20]) {
            case 0:
                func_PAL_L04_003A47C0(args);
                func_L04_003A5C08(object, *(float *)(state + 0x28));
                /* Fall through. */
            case 1:
                func_PAL_L04_003A49E0(args);
                break;
            case 2:
                func_L04_003A1FA0(args);
                break;
            }
            func_L04_003A1FE0(args);
        }
    }
}

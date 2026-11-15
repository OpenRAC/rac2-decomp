#include "include_asm.h"
#include "names.h"

/* The shared state record supplies the active player and current mode. */
typedef struct {
    char reserved00[0x1830];
    char *player;
    char reserved1834[0xA60];
    int mode;
} L04DispatchGlobals;
extern L04DispatchGlobals D_00189E20;

/* Eight group counts and ten signed slot indices, addressed through $gp. */
extern int D_L04_001AFFA0[8] __attribute__((sda));
extern short D_L04_001AFFC0[10] __attribute__((sda));
extern int D_L04_001AFFD4 __attribute__((sda));
extern int D_L04_001AFFD8 __attribute__((sda));
extern char D_L04_002AF6C0[], D_L04_002405C0[], D_L04_00240660[], D_L04_002BA660[];
extern void func_L04_003E7FE8(void);
extern void func_L00_002E6EF8(void);
extern void func_L04_003A1A78(void *);
extern void func_L04_003A1C98(void *);
extern void func_L04_003A1FA0(void *);
extern void func_L04_003A1FE0(void *);
extern void func_L04_003A5C08(void *, float);

/* Runs the shared per-frame code for an object that belongs to a group, calling a different routine for each of its states. */
void func_L04_003E7E68(char *moby)
{
    char *vars;
    L04DispatchGlobals *globals = &gHeroState;
    char *player = globals->player;
    if (player && *(short *)(player + 0xAA) == 0x45 &&
        (unsigned char)player[0x20] != 0xFE && (unsigned char)player[0x20] != 0xFD &&
        globals->mode == 0x31) return;
    vars = *(char **)(moby + 0x68);
    if (vars) {
        int groupIndex = *(int *)(vars + 0x18);
        int slotCount = 1;
        if (groupIndex != -1) slotCount = D_L04_001AFFA0[groupIndex];
        {
            int callArgs[13];
            slotCount += *(int *)(vars + 0x10);
            callArgs[0] = 10;
            callArgs[1] = slotCount;
            callArgs[8] = (int)&D_L04_001AFFD4;
            callArgs[9] = (int)&D_L04_001AFFD8;
            callArgs[2] = (int)D_L04_002AF6C0;
            callArgs[3] = (int)D_L04_002405C0;
            callArgs[4] = (int)D_L04_001AFFC0;
            callArgs[5] = (int)D_L04_001AFFA0;
            callArgs[6] = (int)D_L04_00240660;
            callArgs[7] = (int)D_L04_002BA660;
            callArgs[11] = (int)RunSharedGroupRoutine;
            callArgs[12] = (int)AddDrawCallbackToList3;
            callArgs[10] = (int)moby;
            switch ((unsigned char)moby[0x20]) {
            case 0:
                InitWaterObject(callArgs);
                AddWaterSplashEntry(moby, *(float *)(vars + 0x28));
                /* Fall through. */
            case 1:
                UpdateWaterController(callArgs);
                break;
            case 2:
                AdvanceWaterControllerState(callArgs);
                break;
            }
            UpdateWaterRipplePatches_L04(callArgs);
        }
    }
}

#include "common.h"

extern char D_00189EA0[];
typedef struct { char pad[28]; char *st; } L06TriggerEntry;
extern char *D_L06_001FE500[];
extern s32 D_L06_001B9890;
extern L06TriggerEntry *D_L06_001B21C4[] __attribute__((sda));
extern int D_0018C0BC, D_0018C2C0;
extern int func_002ACBC8(void *, int);
extern int func_L00_003206B8(void *, int);
extern int func_002ACCA8(void *, int);
extern int func_002A8AF0(void *, void *, int);

/* Tells whether the hero is inside the camera volume of this camera moby. */
int func_L06_0047A268(char *moby) {
    int force = 0;
    char *cameraState = (char *)D_L06_001B9890;
    int idx = *(s16 *)(moby + 0x84);
    char *volume = D_L06_001B21C4[0][idx].st;
    int disabled = *(s16 *)(cameraState + 0x86);
    if (disabled) return 0;
    if (*(s16 *)(volume+0x2C)==2 && D_0018C0BC==26 && *(s16 *)(volume+0x2E)>0) force=1;
    else if (*(s16 *)(volume+0x2C)==4 && D_0018C2C0==3) force=*(s16 *)(volume+0x2E)>0;
    if (*(int *)(volume+0xC)>=0 && (force || IsPointInCuboid(gHeroPosition,*(int *)(volume+0xC)))) return 1;
    if (*(int *)(volume+0x4C)>=0 && (force || IsPointInCuboid(gHeroPosition,*(int *)(volume+0x4C)))) return 1;
    if (*(int *)(volume+0x10)>=0 && (force || IsPointInsideRecordVolume(gHeroPosition,*(int *)(volume+0x10)))) return 1;
    if (*(int *)(volume+8)>=0 && (force || IsPointInsideUnitSphereOfRecord(gHeroPosition,*(int *)(volume+8)))) return 1;
    if (*(int *)(volume+0x14)>=0) {
        if (force || point_in_path_xy(gHeroPosition,
            gPathList[*(int *)(volume+0x14)]+16,
            *(int *)gPathList[*(int *)(volume+0x14)])) return 1;
    }
    return 0;
}

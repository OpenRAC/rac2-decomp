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

int func_L06_0047A268(char *moby) {
    int force = 0;
    char *g = (char *)D_L06_001B9890;
    int idx = *(s16 *)(moby + 0x84);
    char *st = D_L06_001B21C4[0][idx].st;
    int disabled = *(s16 *)(g + 0x86);
    if (disabled) return 0;
    if (*(s16 *)(st+0x2C)==2 && D_0018C0BC==26 && *(s16 *)(st+0x2E)>0) force=1;
    else if (*(s16 *)(st+0x2C)==4 && D_0018C2C0==3) force=*(s16 *)(st+0x2E)>0;
    if (*(int *)(st+0xC)>=0 && (force || IsPointInCuboid(D_00189EA0,*(int *)(st+0xC)))) return 1;
    if (*(int *)(st+0x4C)>=0 && (force || IsPointInCuboid(D_00189EA0,*(int *)(st+0x4C)))) return 1;
    if (*(int *)(st+0x10)>=0 && (force || func_L00_003206B8(D_00189EA0,*(int *)(st+0x10)))) return 1;
    if (*(int *)(st+8)>=0 && (force || func_002ACCA8(D_00189EA0,*(int *)(st+8)))) return 1;
    if (*(int *)(st+0x14)>=0) {
        if (force || point_in_path_xy(D_00189EA0,
            D_L06_001FE500[*(int *)(st+0x14)]+16,
            *(int *)D_L06_001FE500[*(int *)(st+0x14)])) return 1;
    }
    return 0;
}

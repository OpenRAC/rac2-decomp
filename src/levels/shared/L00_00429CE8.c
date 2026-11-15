/* Test the camera trigger volumes, marking the descriptor done when none apply. */
#include "common.h"
extern char *D_L00_001B1844 __attribute__((section(".sdata")));
extern char *D_L00_001B8E10;
extern char D_00189EA0[];
extern float func_00282C48(float);
extern float func_00282E80(char *, char *);
extern int func_002ACBC8(char *, int);
extern int func_L00_003206B8(char *, int);
extern int func_002ACCA8(char *, int);
typedef struct { char pad[0x30]; char pos[16]; char rest[0x40]; } Entry_b0898;
extern Entry_b0898 *D_L00_001B1F8C __attribute__((section(".sdata")));
typedef struct {
 char pad[0x80]; char position[16]; char pad90[0x174-0x90]; float speed; char pad178[0x2294-0x178]; int mode;
 char pad2298[0x22B4-0x2298]; unsigned char flag;
} Global_b0898;
extern Global_b0898 D_00189E20_b0898;
int func_L00_00429CE8(char *a)
{
    char *owner = D_L00_001B8E10;
    char *sub = *(char **)(owner + 0x70);
    char *move = sub + 0x160;
    char *rot = sub + 0x1C0;
    char *p = *(char **)(D_L00_001B1844 + *(short *)(a + 0x84) * 32 + 28);
    unsigned int mode;
    if (*(short *)(owner + 0x86) != 0) return 0;
    mode = D_00189E20_b0898.flag - 1U < 2U;
    if (*(short *)(p + 0x4A) && !mode) return 0;
    if (*(short *)(p + 0x48) && mode) return 0;
    if (*(int *)(p + 0x34)) {
        if (func_00282C48(*(float *)(move + 0x34)) > 0.01f) return 0;
        if (func_00282C48(*(float *)(rot + 8)) > 0.01f) return 0;
    }
    if ((unsigned int)(D_00189E20_b0898.mode - 0x62) >= 2 && D_00189E20_b0898.speed > 0.016666668f) return 0;
    if (*(int *)(p + 0xC) >= 0) {
        if (D_00189E20_b0898.mode == 0x62 && vec_distance_xy(D_00189E20_b0898.position, D_L00_001B1F8C[*(int *)(p + 0xC)].pos) < 3.0f) return 1;
        if (IsPointInCuboid(D_00189EA0, *(int *)(p + 0xC))) return 1;
    }
    if (*(int *)(p + 0x10) >= 0) {
        if (D_00189E20_b0898.mode == 0x62 && vec_distance_xy(D_00189E20_b0898.position, D_L00_001B1F8C[*(int *)(p + 0x10)].pos) < 3.0f) return 1;
        if (func_L00_003206B8(D_00189EA0, *(int *)(p + 0x10))) return 1;
    }
    if (*(int *)(p + 8) >= 0) {
        if (D_00189E20_b0898.mode == 0x62 && vec_distance_xy(D_00189E20_b0898.position, D_L00_001B1F8C[*(int *)(p + 8)].pos) < 3.0f) return 1;
        if (func_002ACCA8(D_00189EA0, *(int *)(p + 8))) return 1;
    }
    *(short *)(p + 0x26) = 1;
    return 0;
}

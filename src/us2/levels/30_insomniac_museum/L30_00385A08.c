#include "include_asm.h"
#include "names.h"

extern char D_001AEC98[];
extern char D_00295BF0[];
extern int func_2FB3C8(int);
extern void func_3132D8(void *, unsigned int, int, int, int, int, int, int, int, int);
typedef struct {
    float x;
    float y;
    float z;
    float u;
    float v;
    float w;
} Vec6;
typedef struct {
    unsigned char pad[0x1E0];
    unsigned short mode;
    unsigned char pad2[0x1FB0 - 0x1E2];
    float f1FB0;
    float f1FB4;
    unsigned char pad3[0x22BC - 0x1FB8];
    unsigned char flag;
} D00189E20_View;
extern D00189E20_View g_hero_state;

void func_US2_L30_00385A08(char *a0) {
    char *st = *(char **)(a0 + 0x68);
    Vec6 buf;
    int v;

    g_hero_state.mode = 5;
    g_hero_state.flag = 1;
    buf = *(Vec6 *)D_001AEC98;
    v = func_2FB3C8(*(int *)(D_00295BF0 + *(int *)(st + 0x144) * 4));
    func_3132D8(&buf, 0x80F0F0F0, v, 1, 0, -1, 0, 0, 0, 0);
}


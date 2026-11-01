#include "include_asm.h"

#include "common.h"
typedef struct {
    s32 v[8];
} IdTable_1AB938;
typedef struct {
    s32 v[7];
} StringTable_1AB958;
typedef struct {
    int value;
    int id;
    int a;
    int b;
    int c;
} CheatEntry_25FC90;
extern IdTable_1AB938 D_001AB938;
extern StringTable_1AB958 D_001AB958;
extern char D_001A7A40[] __attribute__((sda));
extern unsigned char D_001A7A50[] __attribute__((sda));
extern CheatEntry_25FC90 D_0025FC90[];

int func_PAL_002CD3C0(void)
{
    IdTable_1AB938 ids = D_001AB938;
    StringTable_1AB958 strings = D_001AB958;
    int count = 0;
    int i;

    for (i = 0; i < 12; i++) {
        if (ids.v[i] == -1)
            break;
        if (D_001A7A50[ids.v[i]] != 0) {
            D_0025FC90[count].value = strings.v[i];
            D_0025FC90[count].id = (int)(D_001A7A40 + ids.v[i]);
            D_0025FC90[count].a = 0xBD7;
            D_0025FC90[count].b = 0xBD8;
            D_0025FC90[count].c = 0;
            count++;
        }
    }
    D_0025FC90[count].value = 0;
    return 0;
}


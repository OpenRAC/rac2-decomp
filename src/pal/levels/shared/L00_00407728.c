#include "include_asm.h"

#include "common.h"
extern void func_002FDBD8(void *obj, float f, void *p, void *q);
typedef struct __attribute__((packed)) { unsigned char b[8]; } Blob8;
extern Blob8 D_L00_001B0DB8 __attribute__((nosda));

void func_PAL_L00_00407728(char *arg)
{
    int *o = *(int **)(arg + 104);
    if (o[9] != 0) {
        if (o[11] == 0) {
            func_002FDBD8(o, 1.0f, (char *)o + 16, 0);
        } else {
            Blob8 tmp = D_L00_001B0DB8;
            func_002FDBD8(o, 1.0f, (char *)o + 16, &tmp);
        }
    }
}


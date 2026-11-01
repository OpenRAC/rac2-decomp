#include "include_asm.h"

typedef struct {
    char pad00[0x80];
    int index;
    int state;
    char pad88[0xBC];
    struct { int first; int limit; int third; int fourth; } cells[0];  
} LimitModel;
extern LimitModel D_L00_0022F7C0;
extern int D_L00_001AD7A0 __attribute__((sda));
extern int D_L00_001AD7A4;
extern int func_002B0D70(void);
extern unsigned char *func_00288FB8(int);
extern int func_0027FB40(int, int, long, unsigned char *, int);

void func_US2_L00_0037A218(void)
{
    LimitModel *base = &D_L00_0022F7C0;
    int index;
    int limit;
    int r;

    if (base->state == 0)
        return;
    index = base->index;
    limit = base->cells[index].limit;
    r = func_002B0D70();
    if (r >= limit)
        func_0027FB40(D_L00_001AD7A0, D_L00_001AD7A4, 0x80F0F0F0, func_00288FB8(0x31B5), -1);
    else
        func_0027FB40(D_L00_001AD7A0, D_L00_001AD7A4, 0x80F0F0F0, func_00288FB8(0x31B4), -1);
}

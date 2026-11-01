#include "include_asm.h"

typedef struct {
    char reserved00[0x14];
    char *source;
    int value;
    char reserved1c[0x118];
    int fallback;
} CallbackState;
extern CallbackState D_001F2840;
extern int D_00138344;
extern int D_00138344;
extern void func_PAL_0029D1D8(int);

int func_PAL_002D40C8(void) {
    int result = 0;
    int flags = D_00138344;
    if (flags & 0x10) {
        int value = *(int *)(D_001F2840.source + 0xE0);
        if (value != 0)
            D_001F2840.value = value;
        else if (D_001F2840.fallback == 0) {
            value = -1;
            goto return_value;
        }
        value = 0;
return_value:
        return value;
    }
    if (flags & 0x900)
        result = 1;
    else
        func_PAL_0029D1D8(flags);
    return result;
}


#include "common.h"
extern void func_0027C540(long);
extern void func_PAL_0029D218(void);
extern void func_0027C660(void);

int func_PAL_002D4150(void)
{
  func_0027C540(0);
  func_PAL_0029D218();
  func_0027C660();
  return 0;
}


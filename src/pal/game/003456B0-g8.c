#include "include_asm.h"

typedef unsigned char u8;

extern void func_00335E68(u8 *, int);
extern void func_00335E38(void *, float, float, float, float);
extern const char *func_00288FB8(int);
extern void func_00115DA8(char *, const char *, ...);
extern unsigned int func_001157AC(const char *);
extern void func_00115AC0(void *, int, int);
extern char D_001ADBC8[];
extern float D_001AE218 __attribute__((sda));
extern float D_001AE21C;

/* func_PAL_003456B0, the PAL copy of func_00343638: the same C, where the selector field moves, the
   text ids change and each case formats one string through D_001ADBC8 instead of two. */
void func_PAL_003456B0(char *object)
{
    char buffer[256];
    float *position;
    func_00335E68((u8 *)object + 0x1B0, 1);
    switch (*(int *)(object + 0x2C4)) {
    case 0:
        func_00115DA8(buffer, D_001ADBC8, func_00288FB8(0xB62));
        break;
    case 2:
        func_00115DA8(buffer, D_001ADBC8, func_00288FB8(0xB65));
        break;
    case 1:
        func_00115DA8(buffer, D_001ADBC8, func_00288FB8(0xB63));
        break;
    }
    if (func_001157AC(buffer) >= 49)
        func_00115DA8(object + 0x120, D_001ADBC8, func_00288FB8(0));
    else
        func_00115AC0(object + 0x120, (int)buffer, 49);
    position = *(float **)(object + 0x2B8);
    func_00335E38(object + 0x1B0, D_001AE218 + position[0], D_001AE21C + position[1], 0.0f, 0.0f);
}

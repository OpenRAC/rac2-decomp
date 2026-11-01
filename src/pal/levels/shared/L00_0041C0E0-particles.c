#include "include_asm.h"

extern char D_L00_0025A920[];
extern void ref_L00_00417700_00(void *, void *);
extern float func_002A7878(float, float);
extern void func_00281EB8(void *, int, int, int, float, float, float);

void func_PAL_L00_0041C878(char *object)
{
    int address = (int)D_L00_0025A920;
    char *pos = (char *)(address + 0x30);
    char *base = (char *)address;
    int i;
    for (i = 0; i < 24; i++, base += 0xB0, pos += 0xB0) {
        if (*(char **)(pos + 0x6C) == object) {
            ref_L00_00417700_00(object, base);
            if (*(int *)(pos + 0x70) == 0) {
                func_00281EB8(pos, 0x31, 0x3F7F0000, 1, func_002A7878(0.125f, 0.25f) * 5.0f, 1.25f, 0.0f);
                func_00281EB8(pos, 0x31, 0x5F7F7F7F, 1, func_002A7878(0.0625f, 0.125f) * 5.0f, 1.24f, 0.0f);
                func_00281EB8(pos, 0xB, 0x103F0000, 1, func_002A7878(0.15f, 0.35f) * 5.0f, 1.23f, 0.0f);
            }
        }
    }
}

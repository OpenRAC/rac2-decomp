#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;

extern void object_set_flag_value(u8 *, int);
extern void object_set_first_float4(void *, float, float, float, float);
extern const char *GetLocalizedString(int);
extern void sprintf(char *, const char *, ...);
extern unsigned int func_001157AC(const char *);
extern void strncpy(void *, int, int);
extern char D_001ADBC8[];
extern float D_001AE218 __attribute__((sda));
extern float D_001AE21C;

/* func_PAL_003456B0, the PAL copy of func_00343638: the same C, where the selector field moves, the
   text ids change and each case formats one string through D_001ADBC8 instead of two. */
void func_PAL_003456B0(char *object)
{
    char buffer[256];
    float *position;
    object_set_flag_value((u8 *)object + 0x1B0, 1);
    switch (*(int *)(object + 0x2C4)) {
    case 0:
        sprintf(buffer, D_001ADBC8, GetLocalizedString(0xB62));
        break;
    case 2:
        sprintf(buffer, D_001ADBC8, GetLocalizedString(0xB65));
        break;
    case 1:
        sprintf(buffer, D_001ADBC8, GetLocalizedString(0xB63));
        break;
    }
    if (func_001157AC(buffer) >= 49)
        sprintf(object + 0x120, D_001ADBC8, GetLocalizedString(0));
    else
        strncpy(object + 0x120, (int)buffer, 49);
    position = *(float **)(object + 0x2B8);
    object_set_first_float4(object + 0x1B0, D_001AE218 + position[0], D_001AE21C + position[1], 0.0f, 0.0f);
}

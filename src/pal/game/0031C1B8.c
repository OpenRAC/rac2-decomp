#include "include_asm.h"

INCLUDE_ASM("asm/pal/game", func_PAL_0031C1B8);

INCLUDE_ASM("asm/pal/game", func_PAL_0031D2E8);

#include "common.h"
extern float func_00283B98(float, float);
extern float func_00282C48(float);
extern void func_002AB668(void *, void *, float);
extern void func_002ACDE8(void *, void *, void *);
extern int func_002A77E0(int);
extern int D_001AFAFC SDATA(D_001AFAFC);
extern void func_PAL_0031E690(void *, int);
extern int func_002E59B0(void *, int);
extern int func_002E5CF8(int, int, void *);
extern void func_002E59F8(int);
extern void func_PAL_002AC3C0(void *, void *);
extern int func_00282978(void *);
extern char D_00188660[];

void func_PAL_0031DAB8(char *object)
{
    float axis[4];
    char *state = *(char **)(object + 0x68);
    if (*(unsigned char *)(object + 0x95) != 0 &&
        *(unsigned char *)(object + 0x20) != 3 &&
        *(unsigned char *)(object + 0x95) != 5 &&
        *(int *)(state + 0x294) == 0) {
        *(float *)(state + 0x27C) = func_00283B98(*(float *)(state + 0x27C), 0.3141593039035797f);
        if (0.00001f <= func_00282C48(*(float *)(state + 0x27C))) {
            char *target;
            target = *(char **)(state + 0x270);
            func_002AB668(axis, target + 0xE0, *(float *)(state + 0x27C));
            { char *row = *(char **)(state + 0x270) + 0xC0;
                func_002ACDE8(row, row, axis); }
            { char *row = *(char **)(state + 0x270) + 0xD0;
                func_002ACDE8(row, row, axis); }
            target = *(char **)(state + 0x274);
            func_002AB668(axis, target + 0xE0, *(float *)(state + 0x27C));
            { char *row = *(char **)(state + 0x274) + 0xC0;
                func_002ACDE8(row, row, axis); }
            { char *row = *(char **)(state + 0x274) + 0xD0;
                func_002ACDE8(row, row, axis); }
            target = *(char **)(state + 0x278);
            func_002AB668(axis, target + 0xE0, *(float *)(state + 0x27C));
            { char *row = *(char **)(state + 0x278) + 0xC0;
                func_002ACDE8(row, row, axis); }
            { char *row = *(char **)(state + 0x278) + 0xD0;
                func_002ACDE8(row, row, axis); }
        }
        /* Each snapshot is consumed by the immediately following opaque call;
         * no C memory access crosses the non-clobbering transfer. */
        if (func_002A77E0(D_001AFAFC) == 1) {
            qcopy_nc(axis, *(char **)(state + 0x270) + 0x10);
            func_PAL_0031E690(axis, 1);
        }
        if (func_002A77E0(D_001AFAFC) == 1) {
            qcopy_nc(axis, *(char **)(state + 0x274) + 0x10);
            func_PAL_0031E690(axis, 1);
        }
        if (func_002A77E0(D_001AFAFC) == 1) {
            qcopy_nc(axis, *(char **)(state + 0x278) + 0x10);
            func_PAL_0031E690(axis, 1);
        }
        if (!func_002E59B0(*(void **)(state + 0x278), *(int *)(state + 0x290)))
            *(int *)(state + 0x290) = func_002E5CF8(0, 4, *(void **)(state + 0x278));
    } else {
        int handle = *(int *)(state + 0x290);
        if (handle != -1) {
            char *sound = D_00188660 + handle * 112;
            if (*(char **)(sound + 0x88) == *(char **)(state + 0x278) &&
                *(unsigned char *)(sound + 0x74) != 0)
                func_002E59F8(handle);
        }
        *(int *)(state + 0x290) = -1;
    }
    func_PAL_002AC3C0(object, state + 0x50);
    func_00282978(state + 0x240);
    func_00282978(state + 0x242);
    if (*(unsigned short *)(object + 0x96) < 0xFFFF)
        *(unsigned short *)(object + 0x96) += 1;
}


/* Complete C near miss; NOT linked and no exact-C credit.
 * Measured source unit: src/levels/shared/L01_00390A50.c
 * Game profile: -O2 -G0 -ffunction-sections
 * Compiled/retail bytes: 520/528. US: 0/6; US2: 0/6; PAL: 0/6.
 * Residual and reopening condition: The state/flag saved registers, boolean selection and short-loop padding differ. The three walks and transition condition are complete; scoped flag initialization and G8 tied. Reopen with measured state/flag lifetimes and inline call contracts.
 * Field views describe only measured prefixes, not complete game-object extents.
 */

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern char D_L01_001B94C0[];
extern char D_00189EA0[];
extern char *D_L01_001FE180[];
extern float func_00282E48(void *a, void *b);
extern int func_002A8AF0(float *point, float *points, int count);
extern int func_002ACBC8(void *point, int index);
extern void func_L01_003909E0(void *object, void *state, int index, int enabled);
extern void func_L01_003907B8(int index, void *state, int enabled);

void func_L01_00390A50(unsigned char *object)
{
    char *state = *(char **)(object + 0x68);
    float point[4] __attribute__((aligned(16)));
    char *source;
    char *path;
    int enabled;
    int i;
    int remaining;
    int *entry;
    int *second;
    object[0x30] = 255;
    if ((signed char)state[0x7E])
        source = D_L01_001B94C0;
    else
        source = D_00189EA0;
    *(Quad *)point = *(Quad *)source;
    enabled = 0;
    if (object[0x95] == 0) {
        if (0.0f < *(float *)(state + 4) && func_00282E48(object + 0x10, point) < *(float *)(state + 4))
            enabled = 1;
        if (!enabled && *(int *)state != -1) {
            path = D_L01_001FE180[*(int *)state];
            enabled = func_002A8AF0(point, (float *)(path + 0x10), *(int *)path) != 0;
        }
        if (!enabled) {
            for (i = 0; i < 6; i++) {
                int index = ((int *)(state + 8))[i];
                if (index != -1 && func_002ACBC8(point, index)) {
                    enabled = 1;
                    break;
                }
            }
        }
    } else {
        if (object[0x95] == 1)
            enabled = 1;
    }
    if ((enabled && !object[0xBC]) || (!enabled && object[0xBC]) || !object[0x20]) {
        if (enabled)
            object[0xBC] = 1;
        else
            object[0xBC] = 0;
        second = (int *)(state + 0x50);
        object[0x20] = object[0xBC] + 1;
        entry = (int *)(state + 0x20);
        remaining = 11;
        do {
            if (*entry != -1)
                func_L01_003909E0(object, state, *entry, enabled);
            remaining--;
            entry++;
        } while (remaining >= 0);
        entry = second;
        remaining = 10;
        do {
            if (*entry != -1)
                func_L01_003907B8(*entry, state, enabled);
            remaining--;
            entry++;
        } while (remaining >= 0);
    }
}

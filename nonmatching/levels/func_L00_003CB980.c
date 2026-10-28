/* Nonmatching C reconstruction.
 * Profile: -O2 -G8 -ffunction-sections.
 * Emitted/retail size: 592/588 bytes.
 * us: 0 of 27 places match.
 * pal: ABSENT.
 * us2: 0 of 27 places match.
 * No strict linked build was run for this draft.
 * The compiler duplicates the 255 marker across byte/halfword stores, and permutes the object, slot and loop-counter registers. A positive allocation guard removes the earlier extra branch. Reopen with a measured object/header view and allocator evidence.
 */
#include "common.h"
extern int func_L00_003CBBD0(void);
extern char *func_0029EFD0(int);
extern int func_002FED90(char *, void *, float, float, float);
extern void func_00282F20(void *, void *, float);
extern int func_L00_00329FF0(int);
extern void func_L00_003CB538(void *);
extern char D_L00_002472C0[];
extern char D_00189EA0[];
extern int D_L00_001B0138 __attribute__((sda));
extern int D_L00_001B013C __attribute__((sda));
extern char *D_L00_001B2AD4 __attribute__((sda));
extern char *D_L00_001B2AD8 __attribute__((sda));
extern char *D_L00_001B2AD4_1[] MACRO_ADDR;
extern char *D_L00_001B2AD8_1[] MACRO_ADDR;

char *func_L00_003CB980(char *owner, int value, void *position, void *direction)
{
    int saved[4] __attribute__((aligned(16)));
    char *object, *state, *entry;
    int slot;
    int i;
    if (func_L00_003CBBD0())
        return 0;
    slot = 0;
    while (slot < 5 && *(int *)(D_L00_002472C0 + slot * 16) != 0)
        ++slot;
    object = func_0029EFD0(0xa9b);
    if (object != 0) {
        state = *(char **)(object + 0x68);
        ((unsigned char *)object)[0x30] = 0xff;
        *(short *)(object + 0x32) = 0xff;
        object[0x20] = 0;
        qcopy(object + 0x10, position);
        qcopy(saved, object + 0x10);
        qcopy(object + 0x10, D_00189EA0);
        *(int *)(state + 0x44) = func_002FED90(object, 0, 1.0f, 1.0f, 1.0f);
        qcopy(object + 0x10, saved);
        func_00282F20(state, direction, 1.0f);
        *(int *)(state + 0x10) = 160;
        *(int *)(state + 0x30) = 20;
        *(int *)(state + 0x14) = slot;
        *(char **)(D_L00_002472C0 + slot * 16) = object;
        D_L00_001B0138 += 1;
        *(float *)(state + 0x18) = 2.5f;
        *(int *)(state + 0x3c) = value;
        *(int *)(state + 0x1c) = 0;
        *(int *)(state + 0x34) = 0;
        *(int *)(state + 0x38) = 0;
        *(int *)(state + 0x40) = *(short *)(owner + 0xaa);
        if (!D_L00_001B013C) {
            D_L00_001B2AD4 = (char *)*(int *)(*(char **)(owner + 0x68) + 8);
            D_L00_001B2AD8 = (char *)func_L00_00329FF0((int)D_L00_001B2AD4 + 0xc00);
            func_L00_00329FF0((int)D_L00_001B2AD8 + 0x780);
            D_L00_001B013C = 1;
            entry = D_L00_001B2AD4_1[0] + 0xbe0;
            for (i = 63; i >= 0; --i) {
                *(int *)entry = 0;
                entry -= 0x30;
            }
            entry = D_L00_001B2AD8_1[0] + 0x8c;
            for (i = 11; i >= 0; --i) {
                *(int *)entry = 0;
                entry += 0xa0;
            }
        }
        for (i = 19; i >= 0; --i)
            func_L00_003CB538(object);
    }
    return object;
}

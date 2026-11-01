#include "include_asm.h"

#include "common.h"
typedef int Vec128_L11 __attribute__((mode(TI)));
extern int D_001A79F0;
extern char D_00189EA0[];
extern int D_L11_001B25A0 __attribute__((sda));
extern char *D_L11_001FF580[];
extern char D_L11_00264760[];
extern int func_002A77E0(int);
extern void func_00282CC0(void *, void *, void *);
extern void func_L11_0046BC08(void *);
extern void func_L11_0046BD18(char *);
extern void func_PAL_L11_00472280(char *);
extern void func_L00_002E6EF8(void (*)(char *), void *);
extern int func_00291308(void *, int, float, float);

/* Advances the object's state and refreshes the last four points of its row in the level's
 * table of 640-byte entries, then registers the callback that draws them. */
void func_PAL_L11_00471B58(char *object)
{
    float position[4] __attribute__((aligned(16)));
    char *state = *(char **)(object + 0x68);
    char *source;
    int count;
    int i;

    if (*(int *)(state + 0x38) >= 20) *(int *)(state + 0x3c) = 1;
    if (*(int *)(state + 0x3c) || D_001A79F0 == 4 || D_001A79F0 == 11) {
        if (*(int *)(state + 0x38) >= 20 && 85.0f < *(float *)(D_00189EA0 + 8)) return;
        qcopy(state, object + 0x10);
        qcopy(state + 0x10, state);
        *(float *)(state + 0x20) += (6.0f - *(float *)(state + 0x20)) * 0.08400001f + 12.0f;
        position[0] = 0.0f;
        position[1] = *(float *)(state + 0x20);
        position[2] = 0.0f;
        func_00282CC0(state + 0x10, state, position);
        qcopy(position, state + 0x10);
        if (D_001A79F0 != 4 && D_001A79F0 != 11) D_L11_001B25A0 = func_002A77E0(20);
        else D_L11_001B25A0 = 20;
        func_L11_0046BC08(object);
        func_L11_0046BD18(object);
        source = D_L11_001FF580[*(int *)(state + 0x34)];
        count = D_L11_001B25A0;
        /* The table is not read back here, so the row's base can stay out of the loop. */
        for (i = count - 4; i < count; i++) {
            qcopy_nc(&((Vec128_L11 *)(D_L11_00264760 + *(int *)(state + 0x38) * 640))[i], &((Vec128_L11 *)source)[i + 1]);
        }
        func_L00_002E6EF8(func_PAL_L11_00472280, object);
        if (!*(unsigned char *)(object + 0x20)) {
            *(int *)(state + 0x24) = func_00291308(state, 0, 0.0f, 0.0f);
            object[0x20] = 1;
            *(int *)(state + 0x2c) = D_L11_001B25A0;
            *(int *)(state + 0x30) = -1;
        }
    }
}

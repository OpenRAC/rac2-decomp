#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));
extern void moby_set_state(char *, int, int);
extern void *part_find_owned_effect_slot(void *, int, int);
extern void mat_apply_offset_to_object(void *, float, float, float);
extern void func_PAL_002B15D8(char *, int, char *, float, float, float, float, int);
extern int PlayMobySound(int, int, char *);
extern void moby_mark_spawned(char *);

void func_PAL_L06_0045C220(char *a0)
{
    int state = *(unsigned char *)(a0 + 0x20);
    char *o = *(char **)(a0 + 0x68);
    float vec[4];
    char *p;
    char *m;

    switch (state) {
    case 0:
        *(int *)(o + 4) = 0;
        moby_set_state(a0, 1, -1);
        break;
    case 1:
        mat_apply_offset_to_object(a0, 0.0f, 0.0f, -(*(float *)o * 0.0003490659f));
        p = part_find_owned_effect_slot(a0, 0x4010000, 0);
        if (p != 0) {
            m = *(char **)(p + 0x20);
            if (m != 0 && *(short *)(m + 0xAA) == 0x12C4) {
                *(int *)(o + 4) = state;
            }
            moby_set_state(a0, 2, -1);
        }
        *(unsigned char *)(a0 + 0xA8) = 0xFF;
        break;
    case 2:
        *(TI128 *)vec = 0;
        if (*(int *)(o + 4) != 0) {
            vec[0] = -0.20000002f;
        } else {
            vec[0] = 0.20000002f;
        }
        func_PAL_002B15D8(a0, 0x1FE, (char *)vec, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);
        PlayMobySound(0, 0, a0);
        moby_mark_spawned(a0);
        break;
    }
}

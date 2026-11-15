#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef struct __attribute__((packed)) { int values[2]; } Pair;

/* An incomplete array: retail builds this address with lui + addiu into a register of its own. */
extern Pair D_L00_001B1458[];
extern int D_L00_001B1464 __attribute__((sda));
extern void func_00282F20(void *, void *, float);
extern float func_002A7878(float, float);
extern void *func_L00_003411A0(void *, void *, int, float);

void func_L00_0041AD40(char *self, void *position, Quad *src)
{
    struct { Quad local; Pair choices; } temp;
    char *state = *(char **)(self + 0x68);
    float size;
    int *selected;

    temp.local = *src;
    vec_scale_to_length(&temp.local, &temp.local, 0.05f);
    temp.choices = D_L00_001B1458[0];
    selected = temp.choices.values;
    size = func_002A7878(0.05f, 0.1f);
    selected += D_L00_001B1464 % 2;
    CreateType6DObject(position, &temp.local, *selected,
                       size * *(float *)(state + 0x50) * 0.1f);
    D_L00_001B1464 += 1;
}

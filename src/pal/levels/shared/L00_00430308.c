/* func_PAL_L00_00430308, the PAL copy of func_L00_0042AD98: the same C with the seconds-to-frames
   factor 60 becomes 50. */
/* Clamp the listener position to the emitter box and update its sound slot. */
#include "common.h"
extern char D_L00_001B8C80_1[];
extern void func_00282CF0(char *, char *, char *);
extern void func_00282CC0_4(char *, char *, char *);
extern float func_00282C48(float);
extern void func_00283098(char *, char *, char *);
extern int func_00282948(char *);
extern int func_L00_0035F640(int, int, char *, int);
extern int func_002A77E0(int);
extern char D_00188660[];
extern char (*D_L00_001B19EC)[32] __attribute__((section(".sdata")));
void func_PAL_L00_00430308(char *a)
{
    float v[4] __attribute__((aligned(16)));
    float local[4] __attribute__((aligned(16)));
    int *state = *(int **)(a + 8);
    int kind = 8;
    char *sound;
    func_00282CF0((char *)v, D_L00_001B8C80_1 + 0x140, a + 0x40);
    v[3] = 0;
    func_00283098((char *)local, (char *)v, a + 0x50);
    if (func_00282C48(local[0]) <= 1.0f && func_00282C48(local[1]) <= 1.0f && func_00282C48(local[2]) <= 1.0f) {
        qcopy(v, D_L00_001B8C80_1 + 0x140);
    } else {
        if (local[0] > 1.0f) local[0] = 1.0f;
        else if (local[0] < -1.0f) local[0] = -1.0f;
        if (local[1] > 1.0f) local[1] = 1.0f;
        else if (local[1] < -1.0f) local[1] = -1.0f;
        if (local[2] > 1.0f) local[2] = 1.0f;
        else if (local[2] < -1.0f) local[2] = -1.0f;
        func_00283098((char *)v, (char *)local, a + 0x10);
        func_00282CC0_4((char *)v, (char *)v, a + 0x40);
    }
    sound = D_00188660 + state[4] * 0x70;
    if (*(unsigned char *)(D_L00_001B19EC[state[0]] + 0x18)) kind = 12;
    if (*(char **)(sound + 0x8C) != a || *(unsigned char *)(sound + 0x74) == 0) {
        if (func_00282948((char *)&state[3])) {
            state[4] = func_L00_0035F640(state[0], kind, a, 0x400);
            if (state[2] > 0) state[3] = (int)((state[1] + func_002A77E0(state[2] - state[1])) * 50.0f);
        } else state[4] = -1;
    }
    if (state[4] != -1) qcopy(D_00188660 + 0x90 + state[4]*0x70, v);
}

#include "include_asm.h"
#include "names.h"

typedef int TI16 __attribute__((mode(TI)));
extern float D_L23_001AFA10 __attribute__((sda));
extern TI16 D_L23_001C0AA0;
extern void func_PAL_L23_003C3868(char *arg0, int arg1, int arg2, int arg3, int arg4, float arg5);
extern void mothership_project_point_onto_surface(TI16 *, float);
extern int CollLine(TI16 *, TI16 *, int, int, int);

void func_PAL_L23_003C3AA0(char *arg0, int arg1) {
    TI16 a;
    TI16 b;
    TI16 *p;

    if ((unsigned char)(*(unsigned char *)(arg0 + 0x43) - 5) >= 2 && *(unsigned char *)(arg0 + 0x20) != 2)
        func_PAL_L23_003C3868(arg0, 5, 0, 5, 1, D_L23_001AFA10);
    if (arg1 != 0) {
        TI16 *pos = (TI16 *)(arg0 + 0x10);

        /* b's address is formed between the two copies, where retail has it. */
        p = &a;
        a = *pos;
        arg0 = (char *)&b;
        b = *pos;
        mothership_project_point_onto_surface((TI16 *)arg0, -2.0f);
        mothership_project_point_onto_surface(p, 0.1f);
        if (CollLine((TI16 *)arg0, p, 0x12, 0, 0) != 0)
            *pos = D_L23_001C0AA0;
    }
}

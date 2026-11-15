/* func_002E35E0 in its own unit (flags in config/cflags.txt: -O2 -G8 -ffunction-sections
 * -fmove-all-movables). The loop's first pass needs the constant 3 and the copy addresses hoisted
 * together: with the default heuristic the 56-insn loop leaves 3 for the second pass, which gives
 * it the shortest life and $s1 instead of the copy source.
 */
#include "common.h"

extern char *ref_L00_002E35E0_00;
extern char ref_L00_002E35E0_01[] __attribute__((sda));
extern char ref_L00_002E35E0_02[] __attribute__((sda));
extern char ref_L00_002E35E0_03[] __attribute__((sda));
extern float ref_L00_002E35E0_04 __attribute__((sda));
extern int D_001A72E0;
extern void func_002E37B0(void);
extern void func_00283388(void *);
extern void func_00282C88(void *);
extern float func_00283B98(float, float);
extern void func_00283430(void *, void *);
extern void func_002E3940(int);
extern void func_002E3820(void);
extern void func_002FC560(int, unsigned long long);

void func_002E35E0(void)
{
    float vec[4];
    int i = 0;

    func_002E37B0();
    *(short *)(ref_L00_002E35E0_00 + 4) = 0;
    set_identity_matrix(ref_L00_002E35E0_01);
    func_00282C88(vec);
    for (; i < *(short *)(ref_L00_002E35E0_00 + 6); i++) {
        switch (i) {
        case 0:
            vec[1] = 0;
            vec[2] = ref_L00_002E35E0_04;
        case 1:
            vec[1] = 0;
            vec[2] = FastAddRotations(ref_L00_002E35E0_04, 0);
            break;
        case 2:
            vec[1] = -0.075f;
            vec[2] = FastAddRotations(ref_L00_002E35E0_04, -0.15f);
            break;
        case 3:
            vec[0] = -0.06f;
            vec[1] = 0.05f;
            vec[2] = FastAddRotations(ref_L00_002E35E0_04, 0.125f);
            break;
        }
        func_00283430(ref_L00_002E35E0_01, vec);
        qcopy(ref_L00_002E35E0_03, ref_L00_002E35E0_02);
        func_002E3940(i);
    }
    func_002E3820();
    VU1_addGSregister(0x47, 0x5360B);
    VU1_addGSregister(0x4E, 0x1000000 | (D_001A72E0 >> 13));
}

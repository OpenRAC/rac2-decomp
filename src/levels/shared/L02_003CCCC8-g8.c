#include "common.h"
extern float func_00283B98(float, float);
extern float func_00283198(float);
extern int func_00283D38(int, int, float);
extern int func_L01_0031BC68(int, int, float);
extern int func_00282978(void *);
extern void func_002AEC48(void *, void *, int, float, float);
extern void func_002B0990(void *, float *, float, int, int);
extern float D_L02_001B00BC __attribute__((sda));
extern float D_L02_001B00B8 __attribute__((sda));
extern int D_L02_001B00B0[] __attribute__((sda));
extern int D_L02_001B00A8[] __attribute__((sda));
extern int D_L02_001A8F00[] __attribute__((sda));
extern char D_00189E20[];
void func_L02_003CCCC8(unsigned char *object)
{
    char *state = *(char **)(object + 0x68);
    float phase;
    if (object[0x31]) {
        *(float *)(state + 0x38c) = func_00283B98(*(float *)(state + 0x38c), D_L02_001B00BC * 0.0002908882452175021f);
        phase = func_00283198(*(float *)(state + 0x38c)) * 4.0f + 4.0f;
        if (phase > 1.0f)
            phase = 1.0f;
        else if (phase < 0.0f)
            phase = 0.0f;
        *(int *)(object + 0x78) = func_00283D38(D_L02_001B00B0[0], D_L02_001B00B0[1], phase);
        if (*(char **)(state + 0x370)) {
            *(float *)(state + 0x388) = func_00283B98(*(float *)(state + 0x388), D_L02_001B00B8 * 0.0002908882452175021f);
            *(int *)(*(char **)(state + 0x370) + 0x78) = func_L01_0031BC68(D_L02_001B00A8[0], D_L02_001B00A8[1], *(float *)(state + 0x388));
        }
    }
    func_00282978(state + 0x386);
    func_00282978(state + 0x374);
    func_00282978(state + 0x376);
    func_00282978(state + 0x378);
    if (*(unsigned short *)(object + 0x96) < 65535)
        ++*(unsigned short *)(object + 0x96);
    if (D_L02_001A8F00[0] != 2 || *(int *)(D_00189E20 + 0x2294) == 0x6f)
        *(short *)(state + 0x386) = 0;
    func_002AEC48(object, state + 0x210, 1, 0.03f, 0.3f);
    func_002AEC48(object, state + 0x290, 2, 0.03f, 0.3f);
    func_002B0990(object, (float *)(state + 0x290), 2.5f, 2, 1);
}

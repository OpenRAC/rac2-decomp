#include "include_asm.h"

#include "common.h"
typedef int Vector __attribute__((mode(TI)));
extern int D_L02_001B0344 __attribute__((sda));
extern float D_L02_001B0338 __attribute__((sda));
extern float D_L02_001B033C __attribute__((sda));
extern float D_L02_001B0340 __attribute__((sda));
extern float D_L02_001B0350 __attribute__((sda));
extern float D_L02_001B0354;
extern float D_L02_001B0358;
extern float D_L02_001B0360 __attribute__((sda));
extern float D_L02_001B0364;
extern float D_L02_001B0368;
extern Vector D_L02_00241290[];
extern Vector D_L02_002415B0[];
extern void func_0029FCC0(char *, int, char *);
extern void func_0029FC20(char *, int, char *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_00282E48(void *, void *);
extern float func_002AA548(void *, void *, float, float, float, float);
extern float func_00282C48(float);

/* Only table-row stores use the non-clobbering copy: the surrounding scalar
 * accesses and live stack vectors occupy distinct storage. */
void func_PAL_L02_003DA778(char *self, int joint) {
    float origin[4] __attribute__((aligned(16)));
    float endpoint[4] __attribute__((aligned(16)));
    float matrix[16] __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    float previous_end[4] __attribute__((aligned(16)));
    float previous_origin[4] __attribute__((aligned(16)));
    float error;
    int sample;
    if (D_L02_001B0344 >= 50)
        return;
    func_0029FCC0(self, joint, (char *)origin);
    func_0029FC20(self, joint, (char *)matrix);
    qcopy(direction, matrix);
    error = 100.0f;
    func_00282F20(direction, direction, 5.3f);
    func_00282CC0(endpoint, origin, direction);
    sample = D_L02_001B0344;
    if (sample > 0) {
        qcopy(previous_end, &D_L02_00241290[sample]);
        qcopy(previous_origin, &D_L02_002415B0[sample]);
        error = func_00282E48(previous_end, endpoint);
        error += func_00282E48(previous_origin, origin);
        if (error > 0.01f) {
            do {
                int next;
                error = func_00282C48(func_002AA548(previous_end, &D_L02_001B0350, endpoint[0],
                    D_L02_001B0338 * 0.00040000002f, D_L02_001B033C * 0.00040000002f, D_L02_001B0340 * 0.020000001f));
                error += func_00282C48(func_002AA548(previous_end + 1, &D_L02_001B0354, endpoint[1],
                    D_L02_001B0338 * 0.00040000002f, D_L02_001B033C * 0.00040000002f, D_L02_001B0340 * 0.020000001f));
                error += func_00282C48(func_002AA548(previous_end + 2, &D_L02_001B0358, endpoint[2],
                    D_L02_001B0338 * 0.00040000002f, D_L02_001B033C * 0.00040000002f, D_L02_001B0340 * 0.020000001f));
                qcopy_nc(D_L02_00241290 + 1 + D_L02_001B0344, previous_end);
                error += func_00282C48(func_002AA548(previous_origin, &D_L02_001B0360, origin[0],
                    D_L02_001B0338 * 0.00040000002f, D_L02_001B033C * 0.00040000002f, D_L02_001B0340 * 0.020000001f));
                error += func_00282C48(func_002AA548(previous_origin + 1, &D_L02_001B0364, origin[1],
                    D_L02_001B0338 * 0.00040000002f, D_L02_001B033C * 0.00040000002f, D_L02_001B0340 * 0.020000001f));
                error += func_00282C48(func_002AA548(previous_origin + 2, &D_L02_001B0368, origin[2],
                    D_L02_001B0338 * 0.00040000002f, D_L02_001B033C * 0.00040000002f, D_L02_001B0340 * 0.020000001f));
                qcopy_nc(D_L02_002415B0 + 1 + D_L02_001B0344, previous_origin);
                next = D_L02_001B0344;
                if (next >= 50)
                    return;
                D_L02_001B0344 = next + 1;
            } while (error > 0.01f);
        }
    }
    if (error > 0.01f) {
        qcopy_nc(D_L02_00241290 + 1 + D_L02_001B0344, endpoint);
        qcopy_nc(D_L02_002415B0 + 1 + D_L02_001B0344, origin);
        D_L02_001B0344++;
    }
}

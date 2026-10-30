/* Retained complete C reconstruction, 30 October 2026. NOT MATCHING.
 * Profile: -O2 -G0 -ffunction-sections.
 * us: 09_dobbo: 448 bytes, expected 452; us2: 09_dobbo: 448 bytes, expected 452; pal: 09_dobbo: 448 bytes, expected 452.
 * The four complete vectors and int/float outputs now occupy one naturally aligned frame.
 * Current matched func_L09_0033E8B0 proves an int return, not the old short declaration;
 * func_L00_00341FA8 also returns int. Shortening candidate pointer scopes ties. Allocation and
 * initial float-output/copy scheduling remain.
 * Reopen: Independent outgoing-value alias/lifetime witness; do not restore the false short
 * return.
 * Local placement checks only; no strict linked or native-runtime claim.
 */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float func_00282E48(TI128 *, TI128 *);
extern int func_L00_00341FA8(void *, TI128 *, TI128 *, int *, float *, int, float, float, float);
extern int func_L09_0033E8B0(char *, int, TI128 *, int, int, float);
extern void func_L09_003E9E60(char *, TI128 *, float);
extern void *D_L09_001FE6C0[];

void func_L09_003EA108(char *arg0, int arg1)
{
    char *st = *(char **)(arg0 + 0x68);
    struct {
        TI128 v0, v1, v2, v3;
        int entry;
        float value;
    } frame;
    TI128 *pos = (TI128 *)(st + 0x140);

    frame.entry = -1;
    frame.value = 0.0f;
    func_L00_00341FA8(D_L09_001FE6C0[arg1], pos, &frame.v0, &frame.entry, &frame.value, 0, 100000.0f, 1.0f, 0.0f);
    if (func_00282E48(&frame.v0, (TI128 *)(arg0 + 0x10)) > 2.0f) {
        TI128 *q2 = &frame.v2;
        int a = func_L09_0033E8B0(arg0, arg1, q2, *(short *)(st + 0x118), 1, *(float *)(st + 0x78) * 10.0f);
        TI128 *q3 = &frame.v3;
        int b = func_L09_0033E8B0(arg0, arg1, q3, *(short *)(st + 0x118), -1, *(float *)(st + 0x78) * 10.0f);
        float d;

        func_00282E48(pos, q2);
        func_00282E48(pos, q3);
        d = func_00282E48(&frame.v0, q2);
        if (d < func_00282E48(&frame.v0, q3)) {
            qcopy(&frame.v1, q2);
            *(short *)(st + 0x118) = a;
        } else {
            qcopy(&frame.v1, q3);
            *(short *)(st + 0x118) = b;
        }
    } else {
        qcopy(&frame.v1, &frame.v0);
    }
    func_L09_003E9E60(arg0, &frame.v1, func_00282E48((TI128 *)(arg0 + 0x10), &frame.v0));
}

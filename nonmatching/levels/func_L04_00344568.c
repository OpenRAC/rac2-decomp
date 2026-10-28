/* Nonmatching reconstruction. Profile: -O2 -G0 -ffunction-sections -frac2-qcopy.
 * Compiled 316 bytes; retail 316 bytes.
 * USA v1.01, PAL and USA v2.00: 0/2 places per release; no carrying absence.
 * No strict linked qualification. The grouped copies and complete matrix workspace have the right size, but frame and scalar-store ordering differ. The distinct-buffer qcopy_nc variant and explicit real input read lifetimes tied. Reopen with measured allocator evidence.
 */
#include "common.h"
extern void func_00283788(void *, void *, void *);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_L03_002EFB60(void *, void *, float);
extern void func_L04_0030FA30(void *, void *, void *);
extern void func_00283388(void *);
extern void func_002AB6D8(void *, void *);

void func_L04_00344568(void *axis, void *rotation, float angle)
{
    float input[4] __attribute__((aligned(16)));
    float output[4] __attribute__((aligned(16)));
    float skew[16] __attribute__((aligned(16)));
    float square[16] __attribute__((aligned(16)));
    float sine[16] __attribute__((aligned(16)));
    float cosine[16] __attribute__((aligned(16)));
    float result[16] __attribute__((aligned(16)));
    float x, y, z;
    qcopy(input, axis);
    z = input[2];
    y = input[1];
    x = input[0];
    qcopy_nc(output, rotation);
    skew[1] = z;
    skew[4] = -z;
    skew[9] = -x;
    skew[2] = -y;
    skew[6] = x;
    skew[8] = y;
    skew[0] = 0;
    skew[12] = 0;
    skew[5] = 0;
    skew[13] = 0;
    skew[10] = 0;
    skew[14] = 0;
    skew[3] = 0;
    skew[7] = 0;
    skew[11] = 0;
    skew[15] = 0;
    func_00283788(square, skew, skew);
    func_L03_002EFB60(cosine, square, 1.0f - func_00283180(angle));
    func_L03_002EFB60(sine, skew, func_00283198(angle));
    func_L04_0030FA30(sine, sine, cosine);
    func_00283388(cosine);
    func_L04_0030FA30(result, sine, cosine);
    func_002AB6D8(result, output);
}

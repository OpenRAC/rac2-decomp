/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/* GPT-6.1 Sol (high), v0775; default game -O2 -G0.
 * Best check: 372/372 bytes, 0/27 places; eight instructions differ.
 * A null selection restores both the saved angle and the saved vector, as
 * does a rejected selection. Keeping the fallback pointer local to that arm
 * reproduces the retail saved high address and all floating register choices.
 * Remaining differences are the threshold branch target/delay slot, target
 * and active stores, and adjacent argument moves. Reversing the field stores
 * ties. A typed quadword copy is shorter; volatile fields are not retained.
 * The interleaved selector declaration preserves both EE argument banks.
 * Required declarations and the common qcopy helper are included below.
 */
#include "common.h"
typedef struct {
    unsigned char pad[0xBE4];
    char *target;
    int active;
    unsigned char rest[0x24BC - 0xBEC];
} HeroTargetState;
extern HeroTargetState D_00189E20_target;
extern void func_L00_002B39F0(int, float);
extern char *func_L00_002AE888(float, float, float, float, char *, int, int);
extern float func_00283248(float, float);
extern void func_00282CF0(char *, char *, char *);
extern void func_L00_002D3B58(char *, char *, float);

void func_L00_002B75A0(float a, float b, float c)
{
    char *p = (char *)(&D_00189E20_target);
    char *result;
    float x;
    float y;
    float scale;
    float vector[4];

    if (*(int *)(p + 0x1248) == 0x20 || ((HeroTargetState *)p)->active != 0)
        return;
    scale = *(float *)(p + 0x98);
    qcopy(vector,p);
    if (0.5f < *(float *)(p + 0x24B8)) {
        func_L00_002B39F0(0,1.0f);
        scale=*(float *)(p+0x1a0);
        qcopy(vector,p+0x190);
    }
    ((HeroTargetState *)p)->active = 1;
    ((HeroTargetState *)p)->target = 0;
    result = func_L00_002AE888(a, scale, b, c, (char *)vector, -1, 0);
    {
        if (result == 0) goto fallback;
        if (((HeroTargetState *)p)->target == 0 || ((HeroTargetState *)p)->active != 0) {
            x = func_00283248(*(float *)(result + 0x10) - *(float *)(p + 0x80),
                              *(float *)(result + 0x14) - *(float *)(p + 0x84));
            *(float *)(p + 0xBEC) = x;
            func_00282CF0(p + 0xBC0, result + 0x10, p + 0x80);
            ((HeroTargetState *)p)->target=result;
        } else {
fallback:
            { char *q=(char *)(&D_00189E20_target);
            *(float *)(q + 0xBEC) = scale;
            qcopy(q+0xbc0,vector);
            }
        }
    }
    func_L00_002D3B58((char *)(&D_00189E20_target)+0xbc0, (char *)(&D_00189E20_target)+0xbc0, 0.0f);
}

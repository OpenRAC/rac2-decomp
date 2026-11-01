#include "include_asm.h"

#include "common.h"
extern int func_00277F48(float, void *, int, int, int);
extern int func_002AAE98(float, float, float, float);
void func_002B9180(void *);
int func_00282978(short *);
typedef int V4_Fc3cb9262 __attribute__((mode(TI)));
extern float func_00283CE0(int);
extern void func_002C96F8(float, float, void *, int *, float *, void *);
extern int func_00277F48(float, void *, int, int, int);
extern float func_00283CE0(int);
extern int func_002AAE98(float, float, float, float);
typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec16_F5621621c;
extern void func_002A9850(void *a0, Vec16_F5621621c *src, int *p, int n, int t0, int t1, int t2, int t3, float f1, float f2, float f3);
extern int D_001BF000[];
extern float func_00283CE0(int);

/* Updates one object: it copies its vector into a local, adds the two motion
   floats and hands the result with the motion's third float to a helper, then
   bails out through the second helper when the halfword at offset 10 is
   taken. Otherwise it packs a colour from the halfword and pushes the object
   through a vector helper with the table at D_001BF000. The two words the
   first helper writes (n and f) are the retail's scratch out-parameters: it
   never reads them back. The words at offsets 0x20 and 0x34 are 32-bit in the
   object and the helpers take them as pointers, so they are cast on the way
   out. */
void func_PAL_002C3368(char *obj)
{
    char *motion = obj + 0x20;
    char *vec = obj + 0x10;
    V4_Fc3cb9262 local[2];
    int n;
    float f;
    int count;

    local[0] = *(V4_Fc3cb9262 *)(obj + 0x10);
    *(float *)(motion + 4) = *(float *)(motion + 4) + *(float *)(motion + 8);
    func_002C96F8(*(float *)(motion + 4), *(float *)(motion + 0xC),
                  (void *)*(int *)(obj + 0x20), &n, &f, vec);

    if (func_00282978((short *)(obj + 0xA)) != 0) {
        func_002B9180(obj);
        return;
    }

    {
        int index = *(short *)(obj + 0xA);

        if ((float)index < 6.25f)
            *(int *)(obj + 4) = func_002AAE98(0.7f, 0.7f, 0.7f,
                                             func_00283CE0(index) * 0.0128f);
    }

    count = func_00277F48(0.15f, vec, 16, *(int *)(motion + 0x14), 0);
    local[1] = *(V4_Fc3cb9262 *)(obj + 0x10);
    func_002A9850((void *)*(int *)(motion + 0x14), (Vec16_F5621621c *)&local[1],
                   D_001BF000, count, 0, 0x810001, 2, 1, 2.0f, 1.0f, 1.0f);
}

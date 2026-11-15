#include "common.h"

typedef int Quad __attribute__((mode(TI)));

extern int func_002761F8(void *, void *, int, void *, int);
extern char *func_002AD0B0(char *);
extern void func_00282CF0(void *, void *, void *);
extern void func_002AFDD8(void *, void *, void *, int);
extern void func_002AD5F8(void *, void *, void *, void *, void *, void *);
extern void func_002AD470(void *, void *, void *, void *, void *, void *);
extern void func_002AD0E0(void *, void *, void *, void *, void *, void *);
extern void func_002833F0(void *, void *);
extern void func_002B0408(void *, void *, int);
extern void func_002AB6D8(void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_002A8F70(void *, int, int, void *, void *, float);

/* The last collision probe's result; +0x18 is the object it hit. */
typedef struct { char pad[24]; char *object; } Collision;
extern Collision D_L07_001BF640;
extern int D_0018C0B0;
/* `sda` on an incomplete array: the one-instruction address the assembler expands absolute. */
extern char D_L07_001A8F20[] __attribute__((sda));

/* With no platform recorded at +0x314, probe from 2 above to 3 below the object and record a hit
   object whose flags have bit 1; otherwise carry the object along with its platform (states 7 and
   11 use func_002AD470) and, in mode 3, recompute its height on it. In that branch the position
   and +0xF0 vector are written `arg + 0x10` / `arg + 0xF0` at each use, without a variable:
   gcse then shares them through the copies retail has. */
void func_L07_003EB838(char *arg)
{
    char *o = *(char **)(arg + 0x68);
    float a[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    float c[4] __attribute__((aligned(16)));
    char *platform = *(char **)(o + 0x314);
    char *pos;

    if (platform == 0) {
        pos = arg + 0x10;
        *(Quad *)a = *(Quad *)pos;
        *(Quad *)b = *(Quad *)pos;
        a[2] += 2.0f;
        b[2] -= 3.0f;
        if (CollLine(a, b, 0, arg, 0) && D_L07_001BF640.object != 0) {
            if (*(int *)(func_002AD0B0(D_L07_001BF640.object) + 0x3C) & 2) {
                *(char **)(o + 0x314) = D_L07_001BF640.object;
                FastVecSub(c, pos, *(char **)(o + 0x314) + 0x10);
                func_002AFDD8(*(char **)(o + 0x314), c, c, 0);
                *(float *)(o + 0x318) = c[2] - 1.0f;
                func_002AD5F8(arg, *(char **)(o + 0x314), pos, arg + 0xF0, o + 0x2F0, o + 0x300);
            }
            *(int *)(o + 0x88) |= 0x100;
        }
    } else {
        *(Quad *)(o + 0x2E0) = *(Quad *)(arg + 0x10);
        if (*(unsigned char *)(arg + 0x20) == 7 || *(unsigned char *)(arg + 0x20) == 11)
            func_002AD470(arg, platform, o + 0x2F0, o + 0x300, arg + 0x10, arg + 0xF0);
        else
            func_002AD0E0(arg, platform, arg + 0x10, arg + 0xF0, arg + 0x10, arg + 0xF0);
        euler_rotation_basis(arg + 0xC0, arg + 0xF0);
        func_002B0408(arg + 0xC0, *(char **)(o + 0x314) + 0xE0, 0);
        func_002AB6D8(arg + 0xC0, arg + 0xF0);
        if (*(unsigned char *)(arg + 0x95) == 3) {
            FastVecSub(a, arg + 0x10, *(char **)(o + 0x314) + 0x10);
            func_002AFDD8(*(char **)(o + 0x314), a, a, 0);
            a[2] = *(float *)(o + 0x318);
            matrix_mul_vec3(a, a, *(char **)(o + 0x314) + 0xC0);
            *(float *)(o + 0x180) = a[2] + *(float *)(*(char **)(o + 0x314) + 0x18);
            if (*(float *)(arg + 0x18) < *(float *)(o + 0x180))
                func_002A8F70(arg, D_0018C0B0, 0x10000, arg + 0x10, D_L07_001A8F20, 7.0f);
        }
    }
}

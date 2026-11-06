/* func_PAL_L19_003ED868, the PAL copy of func_L19_003E9400: the same C, where rename func_00288E18 becomes func_PAL_00289730; scale D_001A7390[0]. */
#include "common.h"
extern u8 D_00189EA0[];
extern u8 D_0019B2E8[];
extern int D_001A79F0 __attribute__((sda));
extern u8 D_001A7B2F[1] __attribute__((sda));
extern unsigned int D_001A7390[1] __attribute__((sda));
extern unsigned int D_0018CE48[1];
extern u8 *D_L19_001B2B0C __attribute__((sda));
extern u8 *D_L19_001B2A1C __attribute__((sda));
extern float D_L19_001B2628 __attribute__((sda));
extern int D_L19_001C9FC0;
extern int func_002ACBC8(void *, int);
extern void func_002A7750(void *, int, int);
extern void func_PAL_00289730(int,int);
extern int func_002B3868(void *);
extern float func_00283248(float,float);
extern float func_00283198(float);
extern void func_00282CF0(void *,void *,void *);
extern void func_00282D30(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
extern int func_00282948(void *);
extern void func_0029B3E0(int,int);
#define I(p,o) (*(int *)((p)+(o)))
#define F(p,o) (*(float *)((p)+(o)))
void func_PAL_L19_003ED868(u8 *obj)
{
    float start[4] __attribute__((aligned(16)));
    float end[4] __attribute__((aligned(16)));
    u8 *s = *(u8 **)(obj + 0x68);
    u8 *other, *os;
    if (I(s,0x38) > 0 && func_002ACBC8(D_00189EA0,I(s,0x38))) {
        D_L19_001B2628 = F((u8 *)((I(s,0x38) << 7) + (int)D_L19_001B2B0C),0x38);
    } else {
        if (*(float *)((int)s + (D_L19_001C9FC0 << 2)) > 0.0f)
            D_L19_001B2628 = *(float *)((int)s + (D_L19_001C9FC0 << 2));
    }
    switch (obj[0x20]) {
    case 0:
        obj[0x30] = 0xFF;
        I(s,0x24) = (D_0019B2E8[I(s,0x20) + D_001A79F0 * 16] >> 7) ^ 1;
        func_002A7750(obj,1,-1);
        break;
    case 1:
        if (!D_001A7B2F[0] && func_002ACBC8(D_00189EA0,I(s,0x10)) &&
            (((int)(D_001A7390[0]) * 5 + 2) / 6) - D_0018CE48[0] > 3000)
            func_PAL_00289730(0xA12,0x69);
        if (D_0019B2E8[I(s,0x20) + D_001A79F0 * 16] & 0x80) {
            if (I(s,0x24)) func_002A7750(obj,2,-1);
        }
        break;
    case 2:
        other = D_L19_001B2A1C + (I(s,0x14) << 8);
        os = 0;
        if (other) os = *(u8 **)(other + 0x68);
        if (func_002B3868(obj)) {
            I(s,0x24) = 0;
            if (I(s,0x18) < 0 || I(s,0x1C) < 0 || I(s,0x14) < 0) {
                func_002A7750(obj,1,-1);
                break;
            }
            other[0xBC] = 1;
            I(s,0x28) = I(s,0x2C) = I(os,0x2C);
        }
        qcopy_nc(start,(u8 *)((I(s,0x18) << 8) + (int)D_L19_001B2A1C) + 0x10);
        start[2] += F(s,0x30);
        qcopy_nc(end,(u8 *)((I(s,0x1C) << 8) + (int)D_L19_001B2A1C) + 0x10);
        end[2] += F(s,0x34);
        F(os,0x18) = func_00283248(end[0]-start[0],end[1]-start[1]);
        func_00282CF0(end,end,start);
        {
            float ratio = (float)I(s,0x2C) / (float)I(s,0x28);
            float t = func_00283198((1.0f - ratio) * 3.1415927f + -1.5707964f);
            func_00282D30(end,end,t * 0.45f + 0.45f);
        }
        func_00282CC0(os,start,end);
        if (func_00282948(s + 0x2C)) {
            func_0029B3E0(0,-1);
            func_002A7750(obj,1,-1);
        }
        break;
    }
}

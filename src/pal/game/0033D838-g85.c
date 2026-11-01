#include "include_asm.h"

typedef int s32_F09f721e0;
typedef float f32_F09f721e0;
extern s32_F09f721e0 func_00336E40 (s32_F09f721e0, s32_F09f721e0);
extern s32_F09f721e0 func_00336DA8 (s32_F09f721e0, s32_F09f721e0);
extern void func_PAL_0033CB00 (s32_F09f721e0, s32_F09f721e0, const void *);
extern s32_F09f721e0 func_00288FB8 (s32_F09f721e0);
extern void func_PAL_0033CF78 (s32_F09f721e0, s32_F09f721e0, s32_F09f721e0, s32_F09f721e0);
extern void func_PAL_0033CF58 (s32_F09f721e0, f32_F09f721e0, f32_F09f721e0, f32_F09f721e0, f32_F09f721e0, f32_F09f721e0, f32_F09f721e0);
extern void func_PAL_0033CFD0 (s32_F09f721e0, f32_F09f721e0);
extern void func_PAL_0033DDC0 (s32_F09f721e0, s32_F09f721e0);
extern s32_F09f721e0 D_L04_001AE040 __attribute__ ((sda));

void func_PAL_0033DC98 (s32_F09f721e0 self, s32_F09f721e0 arg)
{
  s32_F09f721e0 q;
  s32_F09f721e0 p;
  s32_F09f721e0 a, b;
  *(s32_F09f721e0 *) self = arg;
  if (arg != 0)
    {
      p = func_00336DA8 (16, func_00336E40 (arg, arg));
      *(s32_F09f721e0 *) (self + 732) = p;
      ((s32_F09f721e0 *) p)[1] = 0;
      ((s32_F09f721e0 *) p)[2] = 0;
      ((s32_F09f721e0 *) p)[3] = 0;
      ((s32_F09f721e0 *) p)[0] = 0;
    }
  q = self + 8;
  ((f32_F09f721e0 *) *(s32_F09f721e0 *) (self + 732))[0] = 255.0f;
  ((f32_F09f721e0 *) *(s32_F09f721e0 *) (self + 732))[1] = 195.0f;
  func_PAL_0033CB00 (q, arg, &D_L04_001AE040);
  a = func_00288FB8 (7027);
  b = func_00288FB8 (2911);
  func_PAL_0033CF78 (q, a, b, func_00288FB8 (2912));
  func_PAL_0033CF58 (q, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 125.0f);
  func_PAL_0033CFD0 (q, 0.65f);
  *(s32_F09f721e0 *) (self + 728) = 0;
  *(s32_F09f721e0 *) (q + 716) = 0;
  func_PAL_0033DDC0 (self, 0);
}

extern void func_PAL_0033CD50(void *);
extern void func_0033B018(void *, float, float);
extern void func_00335E38(void *, float, float, float, float);
extern int func_002E5E58(int, int, void *);
extern void func_00132938(int);
extern void func_00336B98(void *, int);
extern void func_002E4860(void);
extern unsigned char D_001A7B94[] __attribute__((sda));
extern struct { int w0, w1, w2; } D_00138340;
extern float D_L00_001AE198 __attribute__((sda));
extern float D_L00_001AE1A0 __attribute__((sda));
extern float D_L00_001AE19C, D_L00_001AE1A4;

int func_PAL_0033EEF8(char *object, int flags)
{
    char *p = object + 8;
    float *vec;

    func_PAL_0033CD50(p);
    vec = *(float **)(object + 0x36C);
    func_0033B018(p, vec[0], vec[1]);
    vec = *(float **)(object + 0x36C);
    func_00335E38(object + 0x2DC, vec[0] + D_L00_001AE198,
                 vec[1] + D_L00_001AE19C, 0.0f, 0.0f);
    vec = *(float **)(object + 0x36C);
    func_00335E38(object + 0x324, vec[0] + D_L00_001AE1A0,
                 vec[1] + D_L00_001AE1A4, 0.0f, 0.0f);
    if (flags & 0x1000) {
        func_002E5E58(3, 0, 0);
        *(int *)(object + 0x2D8) = (*(int *)(object + 0x2D8) + 2) % 3;
    } else if (flags & 0x4000) {
        func_002E5E58(3, 0, 0);
        *(int *)(object + 0x2D8) = (*(int *)(object + 0x2D8) + 1) % 3;
    } else if (D_00138340.w0 & 0x8000) {
        switch (*(int *)(object + 0x2D8)) {
        case 0: {
            int value = *(int *)(D_001A7B94 + 12) - 3;
            *(int *)(D_001A7B94 + 12) = value < 0 ? 0 : value;
            break;
        }
        case 1: {
            int value = *(int *)(D_001A7B94 + 8) - 3;
            *(int *)(D_001A7B94 + 8) = value < 0 ? 0 : value;
            break;
        }
        }
    } else if (D_00138340.w0 & 0x2000) {
        switch (*(int *)(object + 0x2D8)) {
        case 0: {
            int value = *(int *)(D_001A7B94 + 12) + 3;
            *(int *)(D_001A7B94 + 12) = value > 1024 ? 1024 : value;
            break;
        }
        case 1: {
            int value = *(int *)(D_001A7B94 + 8) + 3;
            *(int *)(D_001A7B94 + 8) = value > 1024 ? 1024 : value;
            break;
        }
        }
    } else if (flags & 0x40) {
        if (*(int *)(object + 0x2D8) == 2) {
            int value;
            func_002E5E58(4, 0, 0);
            value = *(int *)(D_001A7B94 + 4) == 0;
            *(int *)(D_001A7B94 + 4) = value;
            func_00132938(!value);
        } else {
            func_002E5E58(5, 0, 0);
        }
    }
    func_00336B98(object + 0x324, *(int *)(D_001A7B94 + 8));
    func_00336B98(object + 0x2DC, *(int *)(D_001A7B94 + 12));
    func_002E4860();
    return (flags >> 6) & 1;
}

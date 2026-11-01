#include "include_asm.h"

#include "common.h"
extern void func_0027C540(long);
extern void func_PAL_L00_0030FA48(void);
extern void func_0027C660(void);

int func_PAL_L00_00350EA8(void)
{
  func_0027C540(0);
  func_PAL_L00_0030FA48();
  func_0027C660();
  return 0;
}



extern void func_PAL_L00_0030F9D8(void);

int func_PAL_L00_00351000(void)
{
  func_0027C540(0);
  func_PAL_L00_0030F9D8();
  func_0027C660();
  return 0;
}


extern int D_00138344;
extern void func_L00_0030E010(int a);

extern void func_PAL_L00_0030F2C8(int a);
extern void ref_PAL_L00_00351088_00(int a);

int func_PAL_L00_00351088(void)
{
    ref_PAL_L00_00351088_00(D_00138344);
    return 0;
}


extern void func_0027C540_1(long);
extern void func_L00_0030DFE0(void);
extern void func_0027C660_1(void);

/* Run the three measured setup calls with an explicit long zero, then return the defined integer zero. */
long long func_PAL_L00_003510B0(void)
{
    func_0027C540_1(0);
    func_L00_0030DFE0();
    func_0027C660_1();
    return 0;
}

extern int D_001C51D4;

int func_PAL_L00_003510E0(void) {
    D_001C51D4 = -1;
    return 0;
}


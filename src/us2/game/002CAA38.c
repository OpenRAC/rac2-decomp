#include "include_asm.h"

extern char *D_001A8CFC[] __attribute__((sda));
extern void func_00339770(void *, int);
extern char *D_001A8CFC[] __attribute__((sda));
extern void func_00339770(void *, int);
extern int func_00288FB8_1 ();
extern void func_0027F5B8 (int v, int p7, long k, int r, int m1);
extern void func_0027FA10 (int v, int p7, long k, int r, int m1);
extern void func_0027C540(long);
extern void func_0027C660(void);

int func_US2_002CAA38(void) {
    if (D_001A8CFC[0] != 0)
        func_00339770(D_001A8CFC[0] + 0x3CEA0, 0);
    return 0;
}

int func_US2_002CAA70(void) {
    if (D_001A8CFC[0] != 0)
        func_00339770(D_001A8CFC[0] + 0x3CEA0, 1);
    return 0;
}

/* func_US2_002CAAA8, a v2.00 copy of func_002C9B88: the same two draw calls with string ids 12744
   and 12740, bracketed by func_0027C540(0) and func_0027C660(). */
int func_US2_002CAAA8 (int *p)
{
  int a;
  int t;
  int diff;
  int sum;
  int r;

  func_0027C540 (0);
  a = p[6];
  t = p[8] >> 1;
  diff = a - t;
  sum = a + t;

  r = func_00288FB8_1 (12744);
  func_0027F5B8 (diff, p[7], (long) 0x80f0f0f0, r, -1);
  r = func_00288FB8_1 (12740);
  func_0027FA10 (sum, p[7], (long) 0x80f0f0f0, r, -1);
  func_0027C660 ();
  return 0;
}

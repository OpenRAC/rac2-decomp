#include "include_asm.h"

INCLUDE_ASM("asm/us2/game", func_US2_002D6024);

extern char *D_001A8CFC[] __attribute__((sda));
extern char *D_001A8CFC[] __attribute__((sda));
extern char *D_001A8CFC[] __attribute__((sda));
extern void func_00287E80(void);
extern void func_US2_00342450(char *, char *, char *, char *);
extern void func_US2_00342520(char *, int);
extern char D_002615F8[], D_00261698[], D_00261750[];

int func_US2_002D60E8(void)
{
    func_00287E80();
    if (D_001A8CFC[0] != 0) {
        func_US2_00342450(D_001A8CFC[0] + 0x3C160, D_002615F8, D_00261698, D_00261750);
        func_US2_00342520(D_001A8CFC[0] + 0x3C160, 1);
    }
    return 0;
}


extern int D_00138344;
extern int D_00138344;
extern void func_US2_0029DD40(int);

/* func_002D2918 is built from 002D2918-g8.c. */

int func_US2_002D6158(void) {
    func_US2_0029DD40(D_00138344);
    return 0;
}


/* func_002D2918 is built from 002D2918-g8.c. */

int func_US2_002D6180(void) {
    func_US2_0029DD40(D_00138344);
    return 0;
}


#include "common.h"
extern void func_0027C540(long);
extern void func_US2_0029DD10(void);
extern void func_0027C660(void);

int func_US2_002D61A8(void)
{
  func_0027C540(0);
  func_US2_0029DD10();
  func_0027C660();
  return 0;
}



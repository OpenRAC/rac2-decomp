#include "include_asm.h"
#include "names.h"

extern int D_00138344;
extern int D_00138344;
extern void func_US2_L00_0030F258(int);

/* func_002D2918 is built from 002D2918-g8.c. */

int func_US2_L00_0034F9C8(void) {
    func_US2_L00_0030F258(D_00138344);
    return 0;
}


/* func_002D2918 is built from 002D2918-g8.c. */

int func_US2_L00_0034F9F0(void) {
    func_US2_L00_0030F258(D_00138344);
    return 0;
}


#include "common.h"
extern void SetupGifPaging(long);
extern void func_US2_L00_0030F228(void);
extern void DoGifPaging(void);

int func_US2_L00_0034FA18(void)
{
  SetupGifPaging(0);
  func_US2_L00_0030F228();
  DoGifPaging();
  return 0;
}


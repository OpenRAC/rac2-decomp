#include "include_asm.h"
#include "names.h"

extern void SetupGifPaging(long);
extern void DoGifPaging(void);
extern void SetupGifPaging(long arg0);
extern void SetupGifPaging(long param_1);
extern void func_0029C610(void);
void SetupGifPaging(long);
void DoGifPaging(void);

int func_PAL_002D3B38(void) {
    SetupGifPaging(0);
    func_0029C610();
    DoGifPaging();
    return 0;
}


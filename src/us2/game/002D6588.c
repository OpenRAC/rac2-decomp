#include "include_asm.h"
#include "names.h"

extern void SetupGifPaging(long);
extern void DoGifPaging(void);
void SetupGifPaging(long);
void DoGifPaging(void);
extern void SetupGifPaging(long arg0);
extern void SetupGifPaging(long param_1);
extern void func_0029C370(void);

int func_US2_002D6588(void) {
    SetupGifPaging(0);
    func_0029C370();
    DoGifPaging();
    return 0;
}


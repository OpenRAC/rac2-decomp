#include "include_asm.h"
#include "names.h"

extern void SetupGifPaging(long);
extern void DoGifPaging(void);
extern void SetupGifPaging(long arg0);
extern void SetupGifPaging(long param_1);
extern void func_0029C610(void);
void SetupGifPaging(long);
void DoGifPaging(void);

int menu_draw_screen_via_helper_b_us2(void) {
    SetupGifPaging(0);
    func_0029C610();
    DoGifPaging();
    return 0;
}


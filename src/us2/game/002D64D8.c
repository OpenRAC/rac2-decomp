#include "include_asm.h"
#include "names.h"

extern void SetupGifPaging(long);
extern void DoGifPaging(void);
void SetupGifPaging(long);
void DoGifPaging(void);
extern void SetupGifPaging(long arg0);
extern void SetupGifPaging(long param_1);
extern void func_0029CAB0(void);

int menu_page_draw_third_us2(void) {
    SetupGifPaging(0);
    func_0029CAB0();
    DoGifPaging();
    return 0;
}


#include "include_asm.h"
#include "names.h"

void value_set_entry_by_index_us2(int first, int second)
{
    extern char *GetLocalizedString(int);
    extern void func_0029CC98(int, int);
    func_0029CC98(GetLocalizedString(first), second);
}

extern void func_0029CC50(int, int, int);

void value_forward_three_args_us2(int first, int second, int third) {
    func_0029CC50(first, second, third);
}


#include "include_asm.h"
#include "names.h"

/* Looks up an entry by index and passes it on with one more value. */
void value_set_entry_by_index_us2(int string_id, int value)
{
    extern char *GetLocalizedString(int);
    extern void func_0029CC98(int, int);
    func_0029CC98(GetLocalizedString(string_id), value);
}

extern void func_0029CC50(int, int, int);

/* Passes three values on to another routine. */
void value_forward_three_args_us2(int string_id, int value, int extra) {
    func_0029CC50(string_id, value, extra);
}


#include "include_asm.h"
#include "names.h"

extern int D_00138344;
typedef struct {
    char reserved00[0x14];
    char *source;
    int value;
    char reserved1c[0x118];
    int fallback;
} CallbackStateL001FEC40;
extern CallbackStateL001FEC40 D_L00_001FEC40;
extern void module_l00_call_handler_with_arg_16(int);

/* Guarded callback update: with the pending-input bit set, refreshes the value from its source and reports it (or the fallback's -1), otherwise reports a configured input or runs the setup call. */
int func_US2_L00_0034D450(void)
{
    int result = 0;
    int flags = D_00138344;
    if (flags & 0x10) {
        int value = *(int *)(D_L00_001FEC40.source + 0xE0);
        if (value != 0)
            D_L00_001FEC40.value = value;
        else if (D_L00_001FEC40.fallback == 0) {
            value = -1;
            goto return_value;
        }
        value = 0;
return_value:
        return value;
    }
    if (flags & 0x900)
        result = 1;
    else
        module_l00_call_handler_with_arg_16(flags);
    return result;
}

extern void func_0027C540_6(long);
extern void module_l00_call_handler_16(void);
extern void func_0027C660_6(void);

/* Run the three measured setup calls with an explicit long zero, then return the defined integer zero. */
int func_US2_L00_0034D4D8(void)
{
    func_0027C540_6(0);
    module_l00_call_handler_16();
    func_0027C660_6();
    return 0;
}


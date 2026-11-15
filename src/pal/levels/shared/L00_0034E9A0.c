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
extern void module_l00_call_handler_with_arg_18(int);

/* Guarded callback update: with the pending-input bit set, refreshes the value from its source and reports it (or the fallback's -1), otherwise reports a configured input or runs the setup call. */
int func_PAL_L00_0034E9A0(void)
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
        module_l00_call_handler_with_arg_18(flags);
    return result;
}

extern void func_0027C540_4(long arg0);
extern void module_l00_call_handler_18(void);
extern void func_0027C660_4(void);

/* Run the three measured setup calls with an explicit long zero, then return the defined integer zero. */
unsigned long long func_PAL_L00_0034EA28(void)
{
    func_0027C540_4(0);
    module_l00_call_handler_18();
    func_0027C660_4();
    return 0;
}

extern void module_l00_call_handler_with_arg_19(int);

/* Guarded callback update: with the pending-input bit set, refreshes the value from its source and reports it (or the fallback's -1), otherwise reports a configured input or runs the setup call. */
int func_PAL_L00_0034EA58(void)
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
        module_l00_call_handler_with_arg_19(flags);
    return result;
}

extern void SetupGifPaging(int a);
extern void DoGifPaging(void);
extern void module_l00_call_handler_19(void);

int func_PAL_L00_0034EAE0(void)
{
    SetupGifPaging(0);
    module_l00_call_handler_19();
    DoGifPaging();
    return 0;
}

extern void level_l00_call_module_handler_with_arg_4(int);

/* Guarded callback update: with the pending-input bit set, refreshes the value from its source and reports it (or the fallback's -1), otherwise reports a configured input or runs the setup call. */
int func_PAL_L00_0034EB10(void)
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
        level_l00_call_module_handler_with_arg_4(flags);
    return result;
}

extern void level_l00_call_module_handler_5(void);

/* Run the three measured setup calls with an explicit long zero, then return the defined integer zero. */
int func_PAL_L00_0034EB98(void)
{
    SetupGifPaging(0);
    level_l00_call_module_handler_5();
    DoGifPaging();
    return 0;
}

extern void level_l00_call_module_handler_with_arg_3(int);

/* Guarded callback update: with the pending-input bit set, refreshes the value from its source and reports it (or the fallback's -1), otherwise reports a configured input or runs the setup call. */
int func_PAL_L00_0034EBC8(void)
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
        level_l00_call_module_handler_with_arg_3(flags);
    return result;
}

extern void level_l00_call_module_handler_4(void);

/* Run the three measured setup calls with an explicit long zero, then return the defined integer zero. */
int func_PAL_L00_0034EC50(void)
{
    SetupGifPaging(0);
    level_l00_call_module_handler_4();
    DoGifPaging();
    return 0;
}


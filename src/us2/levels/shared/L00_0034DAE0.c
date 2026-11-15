#include "include_asm.h"
#include "names.h"

extern int D_L00_001A904C_3 __attribute__((sda));
typedef struct {
    char reserved00[0x14];
    char *source;
    int value;
    char reserved1c[0x118];
    int fallback;
} CallbackStateL001FEC40;
extern CallbackStateL001FEC40 D_L00_001FEC40;
extern int g_pad_state[];
extern int level_l00_call_module_handler_with_arg_2(int);
extern int list_page_get_selected_record(int);
extern void menu_start_action(int);

/* The same guarded callback update with its own setup call and pending-request reader. */
int func_US2_L00_0034DAE0(void)
{
    int result = 0;
    int *state = g_pad_state;
    int flags = state[0x1C4 / 4];

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
    else {
        level_l00_call_module_handler_with_arg_2(flags);
        if ((state[0x1C4 / 4] & 0x40) && D_L00_001A904C_3) {
            char *entry = (char *)list_page_get_selected_record(D_L00_001A904C_3 + 0x3F3F0);
            struct { short unused; unsigned short id; int value; } request;

            request.id = *(unsigned short *)(entry + 8);
            request.value = *(int *)(entry + 12);
            menu_start_action((int)&request);
        }
    }
    return result;
}

extern void func_0027C540_8(long param_1);
extern void func_0027C660_8(void);
extern void level_l00_call_module_handler_3(void);

/* Run the three measured setup calls with an explicit long zero, then return the defined integer zero. */
/* Candidate function: FUN_002d3390 */
unsigned long long func_US2_L00_0034DBB0(void)
{
    func_0027C540_8(0);
    level_l00_call_module_handler_3();
    func_0027C660_8();
    return 0;
}

extern void SetupGifPaging(int a);
extern void DoGifPaging(void);
extern void module_l00_call_handler_14(void);

/* Run the three measured setup calls with an explicit long zero, then return the defined integer zero. */
int func_US2_L00_0034DCA8(void)
{
    SetupGifPaging(0);
    module_l00_call_handler_14();
    DoGifPaging();
    return 0;
}

extern void *tab_menu_get_selected_value(int x);

/* When a global flag is set, derives a pointer from that global plus a fixed offset, runs it through one callee and stores the callee result into a field of the argument. */
int func_US2_L00_0034F738(int *obj)
{
    if (D_L00_001A904C_3 != 0)
        obj[13] = tab_menu_get_selected_value(D_L00_001A904C_3 + 0x3C160);
    return 0;
}


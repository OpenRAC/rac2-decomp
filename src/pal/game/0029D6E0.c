#include "include_asm.h"
#include "names.h"

extern char D_001BAEC0[];
extern int g_pad_state[];
extern int g_current_map_index __attribute__((sda));
extern int g_is_pal_video[] __attribute__((sda));
extern char *D_001A8CFC __attribute__((sda));
extern void *memset(void *, int, int);
extern void func_0029CD20(int);
extern int *ui_return_second_arg(int, int);
extern char *func_PAL_003507A8(int *, int);
extern void func_0029C0D0(void);
extern void func_PAL_0029CAA0(void);
extern void func_PAL_0029CA70(void);
extern void func_0029CD18(void);
typedef struct { char pad[0x7A84]; void *cb1; void *cb2; } SubBf;

void func_PAL_0029D6E0(void)
{
    char *state = D_001BAEC0;
    char *obj;

    memset(*(void **)(state + 0x80), 0xCD, 0x40000);
    g_pad_state[104] = 0;
    g_pad_state[105] = 0;
    g_pad_state[106] = 0;
    g_pad_state[107] = 0;
    g_pad_state[108] = 0;
    g_pad_state[109] = 0;
    g_pad_state[110] = 0;
    g_pad_state[111] = 0;
    g_pad_state[112] = 0;
    g_pad_state[113] = 0;
    g_pad_state[114] = 0;
    g_pad_state[115] = 0;
    func_0029CD20(g_is_pal_video[0]);
    obj = func_PAL_003507A8(ui_return_second_arg(0x3FBD0, *(int *)(state + 0x80)), 0x40000);
    D_001A8CFC = obj;
    if (g_current_map_index == 0x1F5) {
        ((SubBf *)(obj + 0x38000))->cb1 = func_0029C0D0;
        ((SubBf *)(obj + 0x38000))->cb2 = func_0029CD18;
    } else {
        ((SubBf *)(obj + 0x38000))->cb1 = func_PAL_0029CAA0;
        ((SubBf *)(obj + 0x38000))->cb2 = func_PAL_0029CA70;
    }
}



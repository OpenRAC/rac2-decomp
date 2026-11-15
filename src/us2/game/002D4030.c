#include "include_asm.h"
#include "names.h"

typedef struct {
    char reserved00[0x14];
    char *source;
    int value;
    char reserved1c[0x118];
    int fallback;
} CallbackState;
extern CallbackState g_pause_menu_state;
extern int D_00138344;
extern void func_0029C990(int);

int func_US2_002D4030(void) {
    int result = 0;
    int flags = D_00138344;
    if (flags & 0x10) {
        int value = *(int *)(g_pause_menu_state.source + 0xE0);
        if (value != 0)
            g_pause_menu_state.value = value;
        else if (g_pause_menu_state.fallback == 0) {
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
        func_0029C990(flags);
    return result;
}

extern void SetupGifPaging(long);
extern void DoGifPaging(void);
void SetupGifPaging(long);
void DoGifPaging(void);
extern void SetupGifPaging(long arg0);
extern void SetupGifPaging(long param_1);
extern void func_0029C9D0(void);

int func_US2_002D40B8(void) {
    SetupGifPaging(0);
    func_0029C9D0();
    DoGifPaging();
    return 0;
}

extern int func_0029C840(int);
extern void menu_process_request(short, int, int *);

int func_US2_002D40E8(void) {
    int result = 0;
    int flags = D_00138344;
    if (flags & 0x10) {
        int value = *(int *)(g_pause_menu_state.source + 0xE0);
        if (value != 0)
            g_pause_menu_state.value = value;
        else if (g_pause_menu_state.fallback == 0) {
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
    {
        int request;
        if (func_0029C840(flags)) {
            request = 0;
            menu_process_request(13, 0, &request);
        }
    }
    return result;
}

extern void func_0029C880(void);

int func_US2_002D4188(void) {
    SetupGifPaging(0);
    func_0029C880();
    DoGifPaging();
    return 0;
}

extern void func_0029C8B0(int);

int func_US2_002D41B8(void) {
    int result = 0;
    int flags = D_00138344;
    if (flags & 0x10) {
        int value = *(int *)(g_pause_menu_state.source + 0xE0);
        if (value != 0)
            g_pause_menu_state.value = value;
        else if (g_pause_menu_state.fallback == 0) {
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
        func_0029C8B0(flags);
    return result;
}

extern void func_0029C8F0(void);

/* Implementation matching decompiled output */
long func_US2_002D4240(void)
{
  SetupGifPaging(0);
  func_0029C8F0();
  DoGifPaging();
  return 0;
}


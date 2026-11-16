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
extern int g_menu_input_flags;
extern int func_0029C990(int);

/* Handles button input for a menu page: reports cancel or accept, and otherwise passes the buttons to the page handler. (USA v2.00) */
int menu_page_update_4_us2(void) {
    int result = 0;
    int flags = g_menu_input_flags;
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

/* Draws one menu page by calling its page-specific draw routine between the common start and end of menu drawing. (USA v2.00) */
int menu_page_draw_6_us2(void) {
    SetupGifPaging(0);
    func_0029C9D0();
    DoGifPaging();
    return 0;
}

extern int func_0029C840(int);
extern int menu_process_request(short, int, int *);

/* Handles button input for a menu page and, when the page handler says so, sends a menu request message. (USA v2.00) */
int menu_page_update_send_request_us2(void) {
    int result = 0;
    int flags = g_menu_input_flags;
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

/* Draws one menu page by calling its page-specific draw routine between the common start and end of menu drawing. (USA v2.00) */
int menu_page_draw_7_us2(void) {
    SetupGifPaging(0);
    func_0029C880();
    DoGifPaging();
    return 0;
}

extern int func_0029C8B0(int);

/* Handles button input for a menu page: reports cancel or accept, and otherwise passes the buttons to the page handler. (USA v2.00) */
int menu_page_update_5_us2(void) {
    int result = 0;
    int flags = g_menu_input_flags;
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
/* Draws one menu page by calling its page-specific draw routine between the common start and end of menu drawing. (USA v2.00) */
long menu_page_draw_8_us2(void)
{
  SetupGifPaging(0);
  func_0029C8F0();
  DoGifPaging();
  return 0;
}


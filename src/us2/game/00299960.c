#include "include_asm.h"
#include "names.h"

extern int g_menu_mode __attribute__((sda));

extern int g_pending_request_flag __attribute__((sda));

int func_US2_00299960(void) {
    return g_pending_request_flag;
}




int func_US2_00299968(void) {
    int value = g_pending_request_flag;

    g_pending_request_flag = 0;
    return value != 0;
}



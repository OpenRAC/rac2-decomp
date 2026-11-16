#include "include_asm.h"

#include "common.h"
extern int g_current_map_index;
extern int TryClaimNotice(int, int, int);

void hud_show_event_notice_us2(char *moby, unsigned event) {
    char *st=*(char **)(moby+0x68);
    switch(event) {
    case 0:
        if(g_current_map_index==13) {
            if(!*(int *)(st+0x100)) TryClaimNotice(8,0x1336,1);
            else TryClaimNotice(8,0x12E5,1);
        } else if(g_current_map_index==18) {
            if(!*(int *)(st+0x100)) TryClaimNotice(8,0x1339,1);
            else TryClaimNotice(8,0x12E5,1);
        } else TryClaimNotice(8,0x12E5,1);
        break;
    case 1:
        if(g_current_map_index==9) TryClaimNotice(8,0x131C,1);
        else if(g_current_map_index==18) {
            if(!*(int *)(st+0x100)) TryClaimNotice(8,0x1339,1);
            else TryClaimNotice(8,0x134F,1);
        } else if(g_current_map_index==12) TryClaimNotice(8,0x12EE,1);
        else if(g_current_map_index==13) {
            if(!*(int *)(st+0x100)) TryClaimNotice(8,0x12E5,1);
            else TryClaimNotice(8,0x1337,1);
        } else if(g_current_map_index!=11) TryClaimNotice(8,0x130C,1);
        else {
            if(*(int *)(st+0x100)) TryClaimNotice(8,0x1314,1);
            else TryClaimNotice(8,0x1315,1);
        }
        break;
    case 2:
        if(g_current_map_index==11) TryClaimNotice(8,0x12E5,1);
        else if(g_current_map_index==18) {
            if(!*(int *)(st+0x100)) TryClaimNotice(8,0x12E5,1);
            else TryClaimNotice(8,0x1339,1);
        }
        break;
    case 3:
        if(g_current_map_index==18) {
            if(!*(int *)(st+0x100)) TryClaimNotice(8,0x1339,1);
            else TryClaimNotice(8,0x12E5,1);
        }
        break;
    case 4:
        if(g_current_map_index==18 && *(int *)(st+0x100)==1) TryClaimNotice(8,0x1339,1);
        break;
    default:
        TryClaimNotice(8,0x12E5,1);
        break;
    }
}

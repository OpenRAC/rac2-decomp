#include "common.h"

extern int g_current_map_index;
extern int TryClaimNotice(int, int, int);

/* Picks the message to show for an event (0 to 4), depending on the current level and a value in the moby data. */
void hud_show_event_notice(char *moby, unsigned event) {
    char *vars=*(char **)(moby+0x68);
    switch(event) {
    case 0:
        if(g_current_map_index==13) {
            if(!*(int *)(vars+0x100)) TryClaimNotice(8,0x27E4,1);
            else TryClaimNotice(8,0x2793,1);
        } else if(g_current_map_index==18) {
            if(!*(int *)(vars+0x100)) TryClaimNotice(8,0x27E7,1);
            else TryClaimNotice(8,0x2793,1);
        } else TryClaimNotice(8,0x2793,1);
        break;
    case 1:
        if(g_current_map_index==9) TryClaimNotice(8,0x27CA,1);
        else if(g_current_map_index==18) {
            if(!*(int *)(vars+0x100)) TryClaimNotice(8,0x27E7,1);
            else TryClaimNotice(8,0x27FD,1);
        } else if(g_current_map_index==12) TryClaimNotice(8,0x279C,1);
        else if(g_current_map_index==13) {
            if(!*(int *)(vars+0x100)) TryClaimNotice(8,0x2793,1);
            else TryClaimNotice(8,0x27E5,1);
        } else if(g_current_map_index!=11) TryClaimNotice(8,0x27BA,1);
        else {
            if(*(int *)(vars+0x100)) TryClaimNotice(8,0x27C2,1);
            else TryClaimNotice(8,0x27C3,1);
        }
        break;
    case 2:
        if(g_current_map_index==11) TryClaimNotice(8,0x2793,1);
        else if(g_current_map_index==18) {
            if(!*(int *)(vars+0x100)) TryClaimNotice(8,0x2793,1);
            else TryClaimNotice(8,0x27E7,1);
        }
        break;
    case 3:
        if(g_current_map_index==18) {
            if(!*(int *)(vars+0x100)) TryClaimNotice(8,0x27E7,1);
            else TryClaimNotice(8,0x2793,1);
        }
        break;
    case 4:
        if(g_current_map_index==18 && *(int *)(vars+0x100)==1) TryClaimNotice(8,0x27E7,1);
        break;
    default:
        TryClaimNotice(8,0x2793,1);
        break;
    }
}

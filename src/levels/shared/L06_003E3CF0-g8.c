#include "common.h"

extern int D_001A79F0;
extern int func_002B0C28(int, int, int);

/* Picks the message to show for an event (0 to 4), depending on the current level and a value in the moby data. */
void func_L06_003E3CF0(char *moby, unsigned event) {
    char *vars=*(char **)(moby+0x68);
    switch(event) {
    case 0:
        if(gCurrentMapIndex==13) {
            if(!*(int *)(vars+0x100)) TryClaimNotice(8,0x27E4,1);
            else TryClaimNotice(8,0x2793,1);
        } else if(gCurrentMapIndex==18) {
            if(!*(int *)(vars+0x100)) TryClaimNotice(8,0x27E7,1);
            else TryClaimNotice(8,0x2793,1);
        } else TryClaimNotice(8,0x2793,1);
        break;
    case 1:
        if(gCurrentMapIndex==9) TryClaimNotice(8,0x27CA,1);
        else if(gCurrentMapIndex==18) {
            if(!*(int *)(vars+0x100)) TryClaimNotice(8,0x27E7,1);
            else TryClaimNotice(8,0x27FD,1);
        } else if(gCurrentMapIndex==12) TryClaimNotice(8,0x279C,1);
        else if(gCurrentMapIndex==13) {
            if(!*(int *)(vars+0x100)) TryClaimNotice(8,0x2793,1);
            else TryClaimNotice(8,0x27E5,1);
        } else if(gCurrentMapIndex!=11) TryClaimNotice(8,0x27BA,1);
        else {
            if(*(int *)(vars+0x100)) TryClaimNotice(8,0x27C2,1);
            else TryClaimNotice(8,0x27C3,1);
        }
        break;
    case 2:
        if(gCurrentMapIndex==11) TryClaimNotice(8,0x2793,1);
        else if(gCurrentMapIndex==18) {
            if(!*(int *)(vars+0x100)) TryClaimNotice(8,0x2793,1);
            else TryClaimNotice(8,0x27E7,1);
        }
        break;
    case 3:
        if(gCurrentMapIndex==18) {
            if(!*(int *)(vars+0x100)) TryClaimNotice(8,0x27E7,1);
            else TryClaimNotice(8,0x2793,1);
        }
        break;
    case 4:
        if(gCurrentMapIndex==18 && *(int *)(vars+0x100)==1) TryClaimNotice(8,0x27E7,1);
        break;
    default:
        TryClaimNotice(8,0x2793,1);
        break;
    }
}

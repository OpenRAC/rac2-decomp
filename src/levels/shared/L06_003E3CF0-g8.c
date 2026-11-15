#include "common.h"

extern int D_001A79F0;
extern int func_002B0C28(int, int, int);

void func_L06_003E3CF0(char *moby, unsigned event) {
    char *st=*(char **)(moby+0x68);
    switch(event) {
    case 0:
        if(D_001A79F0==13) {
            if(!*(int *)(st+0x100)) TryClaimNotice(8,0x27E4,1);
            else TryClaimNotice(8,0x2793,1);
        } else if(D_001A79F0==18) {
            if(!*(int *)(st+0x100)) TryClaimNotice(8,0x27E7,1);
            else TryClaimNotice(8,0x2793,1);
        } else TryClaimNotice(8,0x2793,1);
        break;
    case 1:
        if(D_001A79F0==9) TryClaimNotice(8,0x27CA,1);
        else if(D_001A79F0==18) {
            if(!*(int *)(st+0x100)) TryClaimNotice(8,0x27E7,1);
            else TryClaimNotice(8,0x27FD,1);
        } else if(D_001A79F0==12) TryClaimNotice(8,0x279C,1);
        else if(D_001A79F0==13) {
            if(!*(int *)(st+0x100)) TryClaimNotice(8,0x2793,1);
            else TryClaimNotice(8,0x27E5,1);
        } else if(D_001A79F0!=11) TryClaimNotice(8,0x27BA,1);
        else {
            if(*(int *)(st+0x100)) TryClaimNotice(8,0x27C2,1);
            else TryClaimNotice(8,0x27C3,1);
        }
        break;
    case 2:
        if(D_001A79F0==11) TryClaimNotice(8,0x2793,1);
        else if(D_001A79F0==18) {
            if(!*(int *)(st+0x100)) TryClaimNotice(8,0x2793,1);
            else TryClaimNotice(8,0x27E7,1);
        }
        break;
    case 3:
        if(D_001A79F0==18) {
            if(!*(int *)(st+0x100)) TryClaimNotice(8,0x27E7,1);
            else TryClaimNotice(8,0x2793,1);
        }
        break;
    case 4:
        if(D_001A79F0==18 && *(int *)(st+0x100)==1) TryClaimNotice(8,0x27E7,1);
        break;
    default:
        TryClaimNotice(8,0x2793,1);
        break;
    }
}

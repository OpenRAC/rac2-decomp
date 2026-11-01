#include "include_asm.h"

#include "common.h"
extern int D_001A79F0;
extern int func_002B0C28(int, int, int);

void func_PAL_L06_003E7350(char *moby, unsigned event) {
    char *st=*(char **)(moby+0x68);
    switch(event) {
    case 0:
        if(D_001A79F0==13) {
            if(!*(int *)(st+0x100)) func_002B0C28(8,0x1336,1);
            else func_002B0C28(8,0x12E5,1);
        } else if(D_001A79F0==18) {
            if(!*(int *)(st+0x100)) func_002B0C28(8,0x1339,1);
            else func_002B0C28(8,0x12E5,1);
        } else func_002B0C28(8,0x12E5,1);
        break;
    case 1:
        if(D_001A79F0==9) func_002B0C28(8,0x131C,1);
        else if(D_001A79F0==18) {
            if(!*(int *)(st+0x100)) func_002B0C28(8,0x1339,1);
            else func_002B0C28(8,0x134F,1);
        } else if(D_001A79F0==12) func_002B0C28(8,0x12EE,1);
        else if(D_001A79F0==13) {
            if(!*(int *)(st+0x100)) func_002B0C28(8,0x12E5,1);
            else func_002B0C28(8,0x1337,1);
        } else if(D_001A79F0!=11) func_002B0C28(8,0x130C,1);
        else {
            if(*(int *)(st+0x100)) func_002B0C28(8,0x1314,1);
            else func_002B0C28(8,0x1315,1);
        }
        break;
    case 2:
        if(D_001A79F0==11) func_002B0C28(8,0x12E5,1);
        else if(D_001A79F0==18) {
            if(!*(int *)(st+0x100)) func_002B0C28(8,0x12E5,1);
            else func_002B0C28(8,0x1339,1);
        }
        break;
    case 3:
        if(D_001A79F0==18) {
            if(!*(int *)(st+0x100)) func_002B0C28(8,0x1339,1);
            else func_002B0C28(8,0x12E5,1);
        }
        break;
    case 4:
        if(D_001A79F0==18 && *(int *)(st+0x100)==1) func_002B0C28(8,0x1339,1);
        break;
    default:
        func_002B0C28(8,0x12E5,1);
        break;
    }
}

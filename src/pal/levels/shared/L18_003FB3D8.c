#include "include_asm.h"

#include "common.h"

int func_PAL_L18_003FB3D8(void *arg0) {
    int var_a2;
    void *temp_a1;

    var_a2 = 0;
    temp_a1 = *(void **)((unsigned char *)arg0 + 0x68);
    if (((unsigned short) (*(unsigned short *)((unsigned char *)arg0 + 0x96)) >= 0xC9U) || ((*(short *)((unsigned char *)temp_a1 + 0x294)) >= (*(short *)((unsigned char *)temp_a1 + 0x2A4)))) {
        var_a2 = 1;
    }
    return var_a2;
}


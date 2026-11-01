#include "include_asm.h"

typedef unsigned int undefined4;
extern undefined4 func_002DE618(undefined4);
typedef struct {
    char reserved[0x44];
    int state;
    unsigned int first, second;
    int index, pending;
} Handles_2DCB28;
extern void func_002B7CE0(int);

int func_PAL_002DAFF0(Handles_2DCB28 *object) {
    object->first = func_002DE618(object->first);
    object->second = func_002DE618(object->second);
    object->index = -1;
    object->pending = -1;
    object->state = -1;
    func_002B7CE0(1);
    return 0;
}


INCLUDE_ASM("asm/pal/game", func_PAL_002DB6C8);

INCLUDE_ASM("asm/pal/game", func_PAL_002DBA38);

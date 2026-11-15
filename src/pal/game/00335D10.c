#include "include_asm.h"
#include "names.h"

extern void part_draw_spinning_billboard_pair(void *, void *, int, float);

void func_PAL_00335D10(char *object)
{
    char *data = *(char **)(object + 0x68);
    unsigned int mode = *(unsigned char *)(object + 0x20);
    if (mode - 2 < 2 && *(int *)(data + 0x40) != 0)
        part_draw_spinning_billboard_pair(data + 0x10, data + 0x20, 0, 1.0f);
}


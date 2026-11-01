#include "include_asm.h"

#include "common.h"
extern void func_PAL_002AC3C0(char *, char *);
extern int func_00282978(void *);
extern void func_002AEC48(void *, void *, int, float, float);
extern void func_PAL_002B14F8(char *, char *, int, int, float);

void func_PAL_00323538(char *object)
{
    char *data = *(char **)(object + 0x68);
    char *first;
    func_PAL_002AC3C0(object, data + 0x50);
    first = data + 0x3D0;
    func_00282978(data + 0x270);
    func_00282978(data + 0x272);
    func_002AEC48(object, first, 5, 0.0432f, 0.43200004f);
    func_002AEC48(object, data + 0x450, 6, 0.0432f, 0.43200004f);
    if (*(unsigned short *)(object + 0x96) < 65535)
        (*(unsigned short *)(object + 0x96))++;
    func_PAL_002B14F8(object, first, 5, 1, 2.5f);
}


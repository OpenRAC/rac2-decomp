#include "include_asm.h"

#include "common.h"
extern void func_PAL_002AC3C0(char *, char *);
extern int FastDecTimer(void *);
extern void moby_update_eased_node(void *, void *, int, float, float);
extern void func_PAL_002B14F8(char *, char *, int, int, float);

void robot_update_timers_limbs_pal(char *object)
{
    char *data = *(char **)(object + 0x68);
    char *first;
    func_PAL_002AC3C0(object, data + 0x50);
    first = data + 0x3D0;
    FastDecTimer(data + 0x270);
    FastDecTimer(data + 0x272);
    moby_update_eased_node(object, first, 5, 0.0432f, 0.43200004f);
    moby_update_eased_node(object, data + 0x450, 6, 0.0432f, 0.43200004f);
    if (*(unsigned short *)(object + 0x96) < 65535)
        (*(unsigned short *)(object + 0x96))++;
    func_PAL_002B14F8(object, first, 5, 1, 2.5f);
}


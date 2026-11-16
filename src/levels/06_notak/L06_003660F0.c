#include "include_asm.h"
#include "names.h"

extern unsigned char g_smooth_value_flag;
extern void AttachManipulator(unsigned char *, unsigned int, unsigned char *);
extern void moby_detach_manipulator(char *, char *);

/* The initializer receives all three unchanged integer arguments from this caller. */
/* Starts or stops an attached effect depending on a global switch, and sets its three size values while it is on. */
void part_update_attached_scale(unsigned char *object, unsigned int index,
                       unsigned char *node, float value)
{
    if (g_smooth_value_flag != 0) {
        if (node[1] == 0)
            AttachManipulator(object, index, node);
        *(float *)(node + 0x20) = value;
        *(float *)(node + 0x24) = value;
        *(float *)(node + 0x28) = value;
    } else if (node[1] != 0) {
        moby_detach_manipulator((char *)object, (char *)node);
    }
}

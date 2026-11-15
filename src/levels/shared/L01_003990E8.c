#include "names.h"
/* Clears the visible flag of an object and of its three linked parts, and copies each
   present part's 64-bit word at 0x38 back into the object. */
#include "common.h"

void moby_show_with_linked_parts(char *moby)
{
    int i;
    char **part;
    char *mobyClass;

    mobyClass = *(char **)(moby + 0x24);
    *(unsigned int *)(moby + 0x98) = *(unsigned int *)(mobyClass + 0x10);
    *(unsigned short *)(moby + 0x34) &= 0xFFFE;
    part = (char **)(*(char **)(moby + 0x68) + 0x14);
    *(unsigned char *)(moby + 0x31) = 1;
    for (i = 0; i < 3; i++) {
        if (*part != 0) {
            *(unsigned short *)(*part + 0x34) &= 0xFFFE;
            *(unsigned char *)(*part + 0x31) = 1;
            *(unsigned short *)(*part + 0x34) &= 0xFF7F;
            *(long long *)(moby + 0x38) = *(long long *)(*part + 0x38);
        }
        part++;
    }
}

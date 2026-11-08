/* Links the live entries of the object table into the update list, then runs
   each live object: animation unless flag 0x40 is set, its update hook
   (call_hook, as in RAC1's update_visible_resident_objects), and bounds refresh
   unless flag 4 is set. Built with -G8 -g. */
#include "common.h"

extern int D_L00_001FACE0 __attribute__((nosda));
extern char *D_L00_001B1EA8;
extern char *D_L00_001B1EA8_1 __attribute__((sda));
extern char *D_L00_001B1E9C;
extern void func_002A05A8(void *object);
extern void func_002A0F48(void *object);

void func_L00_0032CF60(void)
{
    char *scan, *object, *last = 0;

    D_L00_001FACE0 = 0;
    D_L00_001B1EA8 = 0;
    for (scan = D_L00_001B1E9C; *(unsigned char *)(scan + 0x20) != 255; scan += 0x100) {
        if ((*(unsigned char *)(scan + 0x20) & 0x80) == 0 &&
            (*(unsigned short *)(scan + 0x34) & 2) == 0) {
            if (last != 0)
                *(char **)(last + 0x28) = scan;
            else
                D_L00_001B1EA8_1 = scan;
            last = scan;
        }
    }
    if (last != 0)
        *(char **)(last + 0x28) = 0;
    object = D_L00_001B1EA8;
    while (object != 0) {
        if (*(signed char *)(object + 0x20) >= 0) {
            if ((*(unsigned short *)(object + 0x34) & 0x40) == 0)
                func_002A05A8(object);
            call_hook(*(void **)(object + 0x64), object);
            if ((*(unsigned short *)(object + 0x34) & 4) == 0)
                func_002A0F48(object);
        }
        object = *(char **)(object + 0x28);
    }
}

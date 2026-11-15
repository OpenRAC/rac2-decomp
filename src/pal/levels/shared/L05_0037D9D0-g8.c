#include "include_asm.h"
#include "names.h"
extern char *D_L05_001B251C;
extern int D_L05_00225DD0[];
extern int D_L05_00225E50[];
extern int D_L05_001FB220[];
extern int moby_get_motion_data(char *object);
extern int level_get_saved_value(void);
extern void moby_init_spawned_sub_object(char *object, int flag);

/* Offers the entry to every registered object with the same id, then walks the entry's list
   and offers each object it names to the handler. */
void func_PAL_L05_0037D9D0(char *object, int handler)
{
    unsigned char *obj = (unsigned char *)object;
    int count;
    int i;
    unsigned short *p;
    int off;

    if (D_L05_001FB220[obj[0x21]] == 0)
        return;

    count = level_get_saved_value();
    for (i = 0; i < count; i++) {
        char *e = (char *)D_L05_00225DD0[i];

        if (*(short *)(e + 0xAA) == *(short *)(obj + 0xAA)) {
            void (*fn)(char *) = (void (*)(char *))D_L05_00225E50[i];

            if (fn != 0)
                fn(e);
        }
    }

    p = (unsigned short *)D_L05_001FB220[obj[0x21]];
    do {
        char *base;

        off = (p[0] & 0x7FFF) << 8;
        base = D_L05_001B251C;
        if (moby_get_motion_data(base + off) != 0) {
            base = D_L05_001B251C;
            moby_init_spawned_sub_object(base + off, handler);
        }
    } while (*(short *)p++ >= 0);
}

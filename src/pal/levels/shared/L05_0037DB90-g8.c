#include "include_asm.h"

extern int D_L05_001AC4D8 __attribute__((sda));
extern char *D_L05_001B251C;
extern int D_L05_00225DD0[];
extern int D_L05_001FB220[];
extern int func_002ED688(char *object);
extern void func_PAL_L05_0037D610(char *object, int flag);

/* Finds the free entry of the level list that belongs to id and spawns it there. */
char *func_PAL_L05_0037DB90(int id, int flag)
{
    int i;
    char *spawned = 0;

    for (i = 0; i < D_L05_001AC4D8; i++) {
        char *obj = (char *)D_L05_00225DD0[i];
        if (*(short *)(obj + 0xAA) == id) {
            short *entry;
            int list = D_L05_001FB220[*(unsigned char *)(obj + 0x21)];
            if (list == 0)
                return 0;
            entry = (short *)list;
            do {
                unsigned int offset = (*entry & 0x7FFF) << 8;
                char *v = (char *)func_002ED688(D_L05_001B251C + offset);
                if (v != 0 && *(int *)(v + 0x110) == 0) {
                    spawned = D_L05_001B251C + offset;
                    func_PAL_L05_0037D610(spawned, flag);
                    break;
                }
            } while (*entry++ >= 0);
            return spawned;
        }
    }
    return spawned;
}

#include "include_asm.h"
#include "names.h"

extern int D_L05_001A9CD8;
extern void func_0029BCC8(void);

/* Returns the saved value and then calls a shared helper. */
int func_L05_003251A0(void) {
    int value = D_L05_001A9CD8;
    func_0029BCC8();
    return value;
}

extern int D_L05_001A9D48[1] __attribute__((sda));

/* Replaces the shared step with its table entry, leaving a negative step alone. */
int func_L05_00324DB8(void)
{
    int step = GetSavedValueAndRelease();

    if (step >= 0)
        step = D_L05_001A9D48[step];
    return step;
}

extern int D_L05_001A9CD0;

/* Stores the given value plus one in a shared counter. */
void func_L05_003263F8(int value) {
    D_L05_001A9CD0 = value + 1;
}

extern int D_L05_001AC4D8 __attribute__((sda));
extern int D_L05_00225DD0[];
extern int D_L05_00225E50[];
extern int D_L05_00225ED0[];
extern int D_L05_00225F50[];

/* Adds an object and its callback to the end of the live object list. */
void func_L05_00379E60(int object, int data, int callback, int extra) {
    int count = D_L05_001AC4D8;
    D_L05_00225DD0[count] = object;
    D_L05_00225E50[count] = data;
    D_L05_00225ED0[count] = callback;
    D_L05_00225F50[count] = extra;
    D_L05_001AC4D8 = count + 1;
}

/* Walk the live object list and return the first one whose id matches. */
/* Standalone declarations recovered from src/levels/shared/L05_003008C0-g8.c. */
extern int D_L05_001AC4D8 __attribute__((sda));

extern int D_L05_00225DD0[];

/* Returns the first live object with the given class id, or 0. */
int func_L05_00379ED0(int classId) {
    int i;

    for (i = 0; i < D_L05_001AC4D8; i++) {
        char *item = (char *)D_L05_00225DD0[i];

        if (*(short *)(item + 0xAA) == classId)
            return (int)item;
    }
    return 0;
}

#include "names.h"
typedef int TI128 __attribute__((mode(TI)));

extern char *func_3224B0(int);
extern void func_300D78(char *);

/* Creates a linked object that follows a parent and a target. It returns 1 if the object
   was made. */
int moby_spawn_linked(char *parent_arg, char *target_arg, float value_a, float value_b)
{
    char *parent = parent_arg;
    char *target = target_arg;
    char *child = func_3224B0(0x12B2);
    char *child_vars;

    if (child != 0) {
        *(int *)(child + 0xB8) = (int)parent;
        *(unsigned char *)(child + 0x30) = 0xFF;
        *(TI128 *)(child + 0x10) = *(TI128 *)(parent + 0x10);
        *(TI128 *)(child + 0xF0) = *(TI128 *)(parent + 0xF0);
        func_300D78(child + 0xC0);
        child_vars = *(char **)(child + 0x68);
        *(int *)(child_vars + 0x10) = (int)parent;
        *(int *)(child_vars + 0x24) = (int)target;
        *(float *)(child_vars + 0x20) = value_a;
        *(float *)(child_vars + 0x28) = value_b;
        return 1;
    }
    return 0;
}

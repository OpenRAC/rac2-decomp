#include "include_asm.h"
#include "names.h"

/* Handles one shadow record according to its kind and returns a pointer to the next record. */
char *func_002DF750(char *record)
{
    extern void func_002E0408(char *);
    extern void func_002E0558(char *);
    if (*(short *)record == 0) {
        build_shadow_sphere_outline(record);
        record += 0x20;
    } else if (*(short *)record == 1) {
        BuildShadowBoxOutline(record);
        record += 0x30;
    }
    return record;
}


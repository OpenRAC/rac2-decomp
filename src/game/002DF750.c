#include "include_asm.h"
#include "names.h"

/* Handles one shadow record according to its kind and returns a pointer to the next record. */
char *gfx_shadow_process_record(char *record)
{
    extern void build_shadow_sphere_outline(char *);
    extern void shadow_build_box_outline(char *);
    if (*(short *)record == 0) {
        build_shadow_sphere_outline(record);
        record += 0x20;
    } else if (*(short *)record == 1) {
        shadow_build_box_outline(record);
        record += 0x30;
    }
    return record;
}


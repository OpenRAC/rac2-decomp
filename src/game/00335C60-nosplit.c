#include "include_asm.h"
#include "names.h"

extern char g_object_release_vtable[];
extern void pool_free_cell(unsigned char *, unsigned char *);
extern void object_reset_type_and_free(void *, int);

typedef struct Obj335C60 {
    void *f00;
    void *f04;
    char pad08[0x20];
    unsigned char *f28;
    unsigned char *f2C;
} Obj335C60;

/* Sets the object type pointer, releases the attached data and runs the shared base cleanup. */
void object_release_data_and_cleanup(Obj335C60 *obj, int flags)
{
    obj->f04 = g_object_release_vtable;
    pool_free_cell(obj->f2C, obj->f28);
    object_reset_type_and_free(obj, flags);
}

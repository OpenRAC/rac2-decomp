#include "include_asm.h"
#include "names.h"




extern void *F449e2f67_FUN_003361A8(char *p);
extern char *F449e2f67_FUN_00336968(char *p);
extern void *F449e2f67_FUN_003366D0(char *p);

extern char *cam_init_object_table_a(char *p);
extern char *cam_init_object_table_d(char *p);
extern char *cam_init_object_table_c(char *p);

/* Initializes a chain of 14 camera/sub-object tables at fixed offsets and returns the base pointer. */
char *sub_object_init_chain_us2(char *object)
{
    cam_init_object_table_a(object);
    cam_init_object_table_a(object + 76);
    cam_init_object_table_a(object + 152);
    cam_init_object_table_a(object + 228);
    cam_init_object_table_a(object + 304);
    cam_init_object_table_a(object + 380);
    cam_init_object_table_d(object + 456);
    cam_init_object_table_d(object + 544);
    cam_init_object_table_c(object + 632);
    cam_init_object_table_d(object + 696);
    cam_init_object_table_d(object + 784);
    cam_init_object_table_d(object + 872);
    cam_init_object_table_d(object + 960);
    cam_init_object_table_d(object + 1048);
    return object;
}




/* Same table-chain initializer, a second copy used by another menu. */
char *sub_object_init_chain_copy_us2(char *object)
{
    cam_init_object_table_a(object);
    cam_init_object_table_a(object + 76);
    cam_init_object_table_a(object + 152);
    cam_init_object_table_a(object + 228);
    cam_init_object_table_a(object + 304);
    cam_init_object_table_a(object + 380);
    cam_init_object_table_d(object + 456);
    cam_init_object_table_d(object + 544);
    cam_init_object_table_c(object + 632);
    cam_init_object_table_d(object + 696);
    cam_init_object_table_d(object + 784);
    cam_init_object_table_d(object + 872);
    cam_init_object_table_d(object + 960);
    cam_init_object_table_d(object + 1048);
    return object;
}







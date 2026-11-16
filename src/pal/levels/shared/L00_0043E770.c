#include "include_asm.h"
#include "names.h"




extern void *F449e2f67_FUN_003361A8(char *object);
extern char *F449e2f67_FUN_00336968(char *object);
extern void *F449e2f67_FUN_003366D0(char *object);

/* Initialises the chain of sub-objects (six at 76-byte steps, then the larger ones) and returns the base pointer. */
char *sub_object_init_chain_pal(char *object)
{
    F449e2f67_FUN_003361A8(object);
    F449e2f67_FUN_003361A8(object + 76);
    F449e2f67_FUN_003361A8(object + 152);
    F449e2f67_FUN_003361A8(object + 228);
    F449e2f67_FUN_003361A8(object + 304);
    F449e2f67_FUN_003361A8(object + 380);
    F449e2f67_FUN_00336968(object + 456);
    F449e2f67_FUN_00336968(object + 544);
    F449e2f67_FUN_003366D0(object + 632);
    F449e2f67_FUN_00336968(object + 696);
    F449e2f67_FUN_00336968(object + 784);
    F449e2f67_FUN_00336968(object + 872);
    F449e2f67_FUN_00336968(object + 960);
    F449e2f67_FUN_00336968(object + 1048);
    return object;
}


/* Initialises the chain of sub-objects (six at 76-byte steps, then the larger ones) and returns the base pointer. */
char *sub_object_init_chain_copy_pal(char *object)
{
    F449e2f67_FUN_003361A8(object);
    F449e2f67_FUN_003361A8(object + 76);
    F449e2f67_FUN_003361A8(object + 152);
    F449e2f67_FUN_003361A8(object + 228);
    F449e2f67_FUN_003361A8(object + 304);
    F449e2f67_FUN_003361A8(object + 380);
    F449e2f67_FUN_00336968(object + 456);
    F449e2f67_FUN_00336968(object + 544);
    F449e2f67_FUN_003366D0(object + 632);
    F449e2f67_FUN_00336968(object + 696);
    F449e2f67_FUN_00336968(object + 784);
    F449e2f67_FUN_00336968(object + 872);
    F449e2f67_FUN_00336968(object + 960);
    F449e2f67_FUN_00336968(object + 1048);
    return object;
}


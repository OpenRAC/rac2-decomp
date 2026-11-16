#include "include_asm.h"

#include "common.h"
extern char *moby_get_motion_data(char *);
extern void follower_set_push_vector(char *, char *);
extern void FastVecSub(char *, char *, char *);
extern void vec_scale_to_length(char *, char *, float);
extern int g_path_pointer_table[];

/* Starts the entity the object's record names: places the object at the
   record's pose, builds the entity's matrix from it and sets its timer. */
void func_PAL_L15_0043C978(char *arg)
{
    char *pos = arg + 0x10;
    char *ent;
    char *rec;
    char *src;
    char *mat;

    rec = *(char **)(arg + 0x68);
    ent = moby_get_motion_data(arg);
    *(int *)(rec + 0x26C) = 0;
    src = (char *)g_path_pointer_table[*(int *)(rec + 0x268)];
    *(int *)(rec + 0x26C) = 1;
    qcopy(pos, src + 0x10);
    follower_set_push_vector(arg, src + 0x20);
    mat = ent + 0x90;
    FastVecSub(mat, ent + 0x60, pos);
    vec_scale_to_length(mat, mat, 0.10000001f);
    *(int *)(ent + 0x130) = 1666667;
}

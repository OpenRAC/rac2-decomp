#include "include_asm.h"

#include "common.h"
extern char *moby_get_motion_data(char *);
extern void follower_set_push_vector(char *, char *);
extern void FastVecSub(char *, char *, char *);
extern void vec_scale_to_length(char *, char *, float);
extern int g_path_pointer_table[];

/* Starts the entity the object's record names: places the object at the
   record's pose, builds the entity's matrix from it and sets its timer. */
void gorn_path_mover_start_follow_pal(char *moby)
{
    char *moby_pos = moby + 0x10;
    char *motion;
    char *vars;
    char *path_point;
    char *push_vec;

    vars = *(char **)(moby + 0x68);
    motion = moby_get_motion_data(moby);
    *(int *)(vars + 0x26C) = 0;
    path_point = (char *)g_path_pointer_table[*(int *)(vars + 0x268)];
    *(int *)(vars + 0x26C) = 1;
    qcopy(moby_pos, path_point + 0x10);
    follower_set_push_vector(moby, path_point + 0x20);
    push_vec = motion + 0x90;
    FastVecSub(push_vec, motion + 0x60, moby_pos);
    vec_scale_to_length(push_vec, push_vec, 0.10000001f);
    *(int *)(motion + 0x130) = 1666667;
}

#include "common.h"

extern char *func_002ED688(char *);
extern void func_002EE920(char *, char *);
extern void func_00282CF0(char *, char *, char *);
extern void func_00282F20(char *, char *, float);
extern int D_001FE480[];

/* Starts the entity the object's record names: places the object at the
   record's pose, builds the entity's matrix from it and sets its timer. */
void func_L15_00436C68(char *arg)
{
    char *pos = arg + 0x10;
    char *ent;
    char *rec;
    char *src;
    char *mat;

    rec = *(char **)(arg + 0x68);
    ent = func_002ED688(arg);
    *(int *)(rec + 0x26C) = 0;
    src = (char *)D_001FE480[*(int *)(rec + 0x268)];
    *(int *)(rec + 0x26C) = 1;
    qcopy(pos, src + 0x10);
    func_002EE920(arg, src + 0x20);
    mat = ent + 0x90;
    FastVecSub(mat, ent + 0x60, pos);
    vec_scale_to_length(mat, mat, 0.083333336f);
    *(int *)(ent + 0x130) = 2000000;
}

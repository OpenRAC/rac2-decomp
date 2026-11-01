#include "include_asm.h"

#include "common.h"
extern char *func_002ED688(char *);
extern void func_002EE920(char *, char *);
extern void func_00282CF0(char *, char *, char *);
extern void func_00282F20(char *, char *, float);
extern int D_001FE480[];

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
    ent = func_002ED688(arg);
    *(int *)(rec + 0x26C) = 0;
    src = (char *)D_001FE480[*(int *)(rec + 0x268)];
    *(int *)(rec + 0x26C) = 1;
    qcopy(pos, src + 0x10);
    func_002EE920(arg, src + 0x20);
    mat = ent + 0x90;
    func_00282CF0(mat, ent + 0x60, pos);
    func_00282F20(mat, mat, 0.10000001f);
    *(int *)(ent + 0x130) = 1666667;
}

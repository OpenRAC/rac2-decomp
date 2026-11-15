#include "names.h"
/* Copies the requested vector into the child record and returns its flags.
   The fourth helper slot is a deliberately unused address of a reserved 16-byte local. */
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
extern unsigned int func_L00_0032C638(unsigned int);
extern void func_L02_00332D28(char *,char *,void *,void *,int);
int func_L22_003300E8(char *object, Quad *value)
{
    char *child=(char *)GetObjectVarsWord18((unsigned int)object);
    Vector position, scratch;
    int result;
    if(child) {
        *(Quad *)(child+0xa0)=*value;
        position.q=*(Quad *)(object+0x10);
        MoveObjectAndResolveCollisions(object,child,&position,&scratch,0);
        result=*(int *)(child+0x94);
    } else result=8;
    return result;
}

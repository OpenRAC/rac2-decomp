#include "names.h"
/* Copies the requested vector into the child record and returns its flags.
   The fourth helper slot is a deliberately unused address of a reserved 16-byte local. */
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
extern void *moby_get_vars_word_18(unsigned int);
extern void coll_move_resolve_collisions(char *,char *,void *,void *,int);
int moby_copy_vector_to_child(char *object, Quad *value)
{
    char *child=(char *)moby_get_vars_word_18((unsigned int)object);
    Vector position, scratch;
    int result;
    if(child) {
        *(Quad *)(child+0xa0)=*value;
        position.q=*(Quad *)(object+0x10);
        coll_move_resolve_collisions(object,child,&position,&scratch,0);
        result=*(int *)(child+0x94);
    } else result=8;
    return result;
}

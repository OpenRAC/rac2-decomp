#include "names.h"
/* A union keeps the vector field at a fixed stack offset without extending
 * the lifetime of a cast-derived pointer across the matrix helper calls. */
typedef int Quad __attribute__((mode(TI)));
extern void euler_to_matrix(void *, void *);
extern void copy_matrix_rotation(void *, void *);
extern void multiply_matrix(void *, void *, void *);
extern void copy_matrix3x4(void *, void *);
extern void transform_vector(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void func_002A10E8(void *);
/* Keeps the attached piece in place next to its parent, easing its height and copying the parent's turn. */
void tether_attach_to_parent(char *parent, char *context)
{
    Quad matrices[12];
    union { Quad quad; float f[4]; } offset;
    Quad result;
    char *child;
    float *height;
    if (*(char **)(context+0x20)==0) return;
    offset.quad=0;
    offset.f[1]=0.11f;
    child=*(char **)(context+0x20);
    height=(float *)(*(char **)(child+0x68)+0xC);
    if (*height>0.45f) *height=*height-0.05f;
    else if (*height<0.45f) *height=*height+0.05f;
    child=*(char **)(context+0x20);
    *(float *)(child+0xF8)=-1.5707963705062866f;
    euler_to_matrix(matrices+4, (*(char **)(context+0x20))+0xF0);
    copy_matrix_rotation(matrices+8,parent+0xC0);
    multiply_matrix(matrices,matrices+8,matrices+4);
    copy_matrix3x4((*(char **)(context+0x20))+0xC0,matrices);
    transform_vector(&result,&offset,matrices);
    FastVecAdd((*(char **)(context+0x20))+0x10,&result,parent+0x10);
    func_002A10E8(*(char **)(context+0x20));
}

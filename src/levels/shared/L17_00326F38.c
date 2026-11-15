#include "include_asm.h"
#include "names.h"

extern void func_2EF398(void *, void *, void *);

extern void func_2EEF40(void *, void *, float);

extern void func_2EEEB8(void *, void *, void *);

/* transforms a point given in three floats through the sub-object's matrix, rescales it and
   writes it back through the descriptor */
/* Turns a point given as three numbers into world space using the object's matrix and size, and adds it to the output. */
void vec_local_to_world(char *object, char *output, float x, float y, float z)
{
    float point[3];

    point[0] = x;
    point[1] = y;
    point[2] = z;
    func_2EF398(point, point, object + 0xC0);
    func_2EEF40(point, point, *(float *)(object + 0x2C));
    func_2EEEB8(output, output, point);
}


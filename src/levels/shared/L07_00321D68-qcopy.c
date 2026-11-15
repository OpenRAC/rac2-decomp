#include "include_asm.h"
#include "names.h"
typedef int Quad __attribute__((mode(TI)));
extern unsigned int func_L00_0032C638(unsigned int);
extern float func_00282E20(void *);
extern void func_002B5678(void *, void *, void *, void *);

/* Set the control motion, preserve the starting position for the step helper,
   and return its recorded result (8 when no control is attached). */
/* Sets the way a controlled object should move this frame and returns the result of the step. */
int func_L07_00321D68(char *object, void *motion)
{
    float position[4];
    float output[4];
    char *control = (char *)GetObjectVarsWord18((unsigned int)object);
    int result;
    if (control) {
        *(Quad *)(control + 0xa0) = *(Quad *)motion;
        *(Quad *)position = *(Quad *)(object + 0x10);
        *(float *)(control + 0xb0) = vec_length_xy(control + 0xa0);
        ApplyVelocityAndResolveCollisions(object, control, position, output);
        result = *(int *)(control + 0x94);
    } else {
        result = 8;
    }
    return result;
}

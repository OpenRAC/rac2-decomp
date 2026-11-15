#include "include_asm.h"
#include "names.h"
typedef int Quad __attribute__((mode(TI)));
extern char D_L00_001B8E20[];
extern void cam_resolve_position(void *, int);
extern float FastVecDot(void *, void *);
extern void FastVecScale(void *, void *, float);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_clear_128(void *);
/* Projects the direction onto the fixed axes and initializes the linked vectors. */
void cam_init_state_vectors(char *self)
{
    float direction[4], projected[4], offset[4];
    char *data = *(char **)(self + 0x70);
    char *base = D_L00_001B8E20;
    char *axis = base + 0x30;
    char *position = data + 0x60;
    char *end;
    float dot;
    float *temp;
    cam_resolve_position(direction, 0);
    dot = FastVecDot(direction, axis);
    end = data + 0x160;
    temp = projected;
    FastVecScale(temp, axis, dot);
    FastVecSub(position, direction, projected);
    *(Quad *)(data + 0x70) = *(Quad *)projected;
    FastVecAdd(position, position, data + 0x70);
    base += 0x20;
    FastVecScale(offset, base, *(float *)(position + 0xB0));
    FastVecAdd(data + 0xA0, offset, position);
    FastVecAdd(data + 0xF0, offset, position);
    vec_clear_128(data + 0x100);
    position[0xC4] = 0;
    *(float *)(position + 0xC8) = 1.0f;
    position[0xC5] = 0;
    *(short *)(position + 0xC6) = 0;
    *(Quad *)(data + 0xC0) = *(Quad *)position;
    vec_clear_128(data + 0xD0);
    vec_clear_128(data + 0xE0);
    FastVecScale(offset, base, *(float *)(end + 0x30));
    FastVecAdd(data + 0xB0, offset, position);
}

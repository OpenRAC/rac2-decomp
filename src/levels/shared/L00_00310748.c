#include "include_asm.h"
#include "names.h"
typedef int Q128 __attribute__((mode(TI)));

typedef struct {
    int f0;
    int count;
} Hdr_310748;

typedef struct {
    char pad0[4];
    float f4;
    char pad8[0x10 - 8];
    float v10[4];
} Ent_310748;

typedef struct {
    char pad0[0x10];
    float v10[4];
    char pad20[0x2C - 0x20];
    float f2C;
    char pad30[0x98 - 0x30];
    Hdr_310748 *hdr;
    char pad9C[0xC0 - 0x9C];
    float mC0[4];
} Obj_310748;

extern void func_00283698(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_002830C0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);

/* Transforms a point into the object's space and stores it, scaled, in the given table entry. */
void func_L00_00310748(Obj_310748 *self, int idx, void *p, float x, float y)
{
    float matrix[16];
    float vec[4];
    char *cursor = (char *)self->hdr;
    float scale;

    if (idx < (((Hdr_310748 *)cursor)->count >> 5)) {
        scale = 1024.0f / self->f2C;
        cursor += idx * 32 + 0x10;
        matrix_from_basis_rows(matrix, self->mC0);
        FastVecSub(vec, p, self->v10);
        transform_vector(vec, vec, matrix);
        FastVecScale(vec, vec, scale);
        *(Q128 *)((Ent_310748 *)cursor)->v10 = *(Q128 *)vec;
        ((Ent_310748 *)cursor)->f4 = y * scale;
        ((Ent_310748 *)cursor)->v10[3] = x * scale;
    }
}

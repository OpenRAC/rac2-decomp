#include "names.h"
/* Reconstructed from retail; standalone all-placement checks pass in all three releases.
 * The lead must still verify strict linked builds. */
typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    TI128 v0, v1, v2;
    TI128 matrix[3];
} LocalF3E0;

extern char *CreateMoby(int);
extern void euler_rotation_basis(void *, void *);
extern int cam_compute_view_direction(void *, void *, int);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern float FastVecDot(void *, void *);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecScale(void *, void *, float);
extern float math_fast_sin_or_cos_a(float);
extern void quaternion_to_rotation_basis(void *, void *);
extern void multiply_matrix3x3(void *, void *, void *);
extern void moby_mark_spawned(void *);
extern char *D_L00_001B0838 __attribute__((sda));
extern char g_hero_moby[];

/* Creates a blast moby (class 3301) at the given spot, stores its direction, turns it to match
   the surface, and replaces the previous blast moby. */
char *blast_spawn(TI128 *position, TI128 *direction)
{
    LocalF3E0 local;
    char *p = CreateMoby(0xCE5 /* moby class 3301 */);
    char *data = *(char **)(p + 0x68);
    char *basis;
    char *axis;
    char *point;
    float half;
    short header;

    if (p != 0) {
        header = 0xFF;
        *(short *)(p + 0x32) = header;
        *(char *)(p + 0x30) = header;
        *(unsigned short *)(p + 0x34) |= 0x100;
        *(char *)(p + 0x20) = 0;
        point = p + 0x10;
        *(TI128 *)point = *position;
        *(TI128 *)data = *direction;
        basis = p + 0xC0;
        axis = p + 0xE0;
        euler_rotation_basis(basis, *(char **)g_hero_moby + 0xF0);
        cam_compute_view_direction(point, &local.v2, 1);
        vec_scale_to_length(&local.v2, &local.v2, 1.0f);
        FastVecCross(&local.v1, axis, &local.v2);
        half = FastVecDot(axis, &local.v2) * 0.5f;
        FastVecScale(&local.v0, &local.v1, math_fast_sin_or_cos_b(half));
        *(float *)((char *)&local.v0 + 12) = math_fast_sin_or_cos_a(half);
        quaternion_to_rotation_basis(&local.v0, local.matrix);
        multiply_matrix3x3(basis, local.matrix, basis);
        if (D_L00_001B0838 != 0)
            moby_mark_spawned(D_L00_001B0838);
        D_L00_001B0838 = p;
    }
    return p;
}

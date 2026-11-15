#include "names.h"
typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    TI128 v0, v1, v2, v3;
    char pad[0x20];
} Local51C0;

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
extern char *D_L00_001B05DC __attribute__((sda));
extern char g_hero_moby[];

/* Creates the Mini-Nuke blast object at a position, turns it to face along the given direction, and replaces any earlier blast. */
char *mini_nuke_blast_create(TI128 *position, TI128 *direction)
{
    Local51C0 local;
    char *blast = CreateMoby(0xC06 /* moby class 3078 */);
    char *data = *(char **)(blast + 0x68);
    char *basis;
    char *axis;
    char *point;
    float half;
    short header;

    if (blast != 0) {
        header = 0xFF;
        *(short *)(blast + 0x32) = header;
        *(char *)(blast + 0x30) = header;
        *(unsigned short *)(blast + 0x34) |= 0x100;
        *(char *)(blast + 0x20) = 0;
        point = blast + 0x10;
        *(TI128 *)point = *position;
        *(TI128 *)data = *direction;
        basis = blast + 0xC0;
        axis = blast + 0xE0;
        euler_rotation_basis(basis, *(char **)g_hero_moby + 0xF0);
        cam_compute_view_direction(point, &local.v2, 1);
        vec_scale_to_length(&local.v2, &local.v2, 1.0f);
        FastVecCross(&local.v1, axis, &local.v2);
        half = FastVecDot(axis, &local.v2) * 0.5f;
        FastVecScale(&local.v0, &local.v1, math_fast_sin_or_cos_b(half));
        *(float *)((char *)&local.v0 + 12) = math_fast_sin_or_cos_a(half);
        quaternion_to_rotation_basis(&local.v0, &local.v3);
        multiply_matrix3x3(basis, &local.v3, basis);
        if (D_L00_001B05DC != 0)
            moby_mark_spawned(D_L00_001B05DC);
        D_L00_001B05DC = blast;
    }
    return blast;
}

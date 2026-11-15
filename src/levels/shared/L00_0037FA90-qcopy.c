#include "include_asm.h"
#include "names.h"

/* func_L00_0037FA90 is a unit of its own: the 16-byte constant the level copies into
   the local vector needs the opt-in grouped quadword-copy profile (-frac2-qcopy,
   config/cflags.txt), which gives retail's `lui $v1 ; addiu $v1 ; lq $v0,0($v1) ;
   sq $v0,0($sp)`. The default profile keeps the address in $v0 and the quadword in
   $v1, the two registers swapped.

   The block is built from the level's stored vectors, placed, and the reach against
   the level's limit decides the near or the far branch. */

typedef int L00_0037FA90_TI128 __attribute__((mode(TI)));

extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern int CollLine(void *, void *, int, void *, int);
extern void FastVecSub(void *, void *, void *);
extern float FastVecDot(void *, void *);
extern float math_fast_sin_or_cos_a(float);
extern void FastVecCross(void *, void *, void *);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern void FastVecScale(void *, void *, float);

extern L00_0037FA90_TI128 D_L00_001BF220;
/* The input at +0x230 and the lower vector share this measured data block. */
extern char g_camera_l00_position[0x240];

/* The level's own data: the vector block the reach is measured against and the
   pointer the shared test takes. */
typedef struct {
    unsigned char pad000[0x760];
    unsigned char f760[0x1b30];
    void *f2290;
} L00_0037FA90_Data;

extern L00_0037FA90_Data g_hero_state;

/* Works out a smooth aim direction from the level's stored vectors, bending it toward a fixed direction when it is close, or straight to it otherwise. */
void math_compute_aim_direction(char *result, char *target, float blend, float lookAhead, float maxAngle)
{
    char *origin = g_camera_l00_position + 0x230;
    char probe[16];
    char axis[16];
    float alignment;

    vec_scale_to_length(probe, origin, lookAhead);
    origin -= 0x230;
    FastVecAdd(probe, probe, origin);
    if (CollLine(origin, probe, 0, g_hero_state.f2290, 0) != 0)
        *(L00_0037FA90_TI128 *)probe = D_L00_001BF220;
    FastVecSub(result, probe, target);
    vec_scale_to_length(result, result, 1.0f);
    alignment = FastVecDot(result, g_hero_state.f760);
    if (alignment < math_fast_sin_or_cos_a(maxAngle)) {
        FastVecCross(axis, result, g_hero_state.f760);
        math_apply_axis_rotation_to_quat(result, g_hero_state.f760, axis, maxAngle);
        vec_scale_to_length(result, result, blend);
    } else {
        FastVecScale(result, result, blend);
    }
}

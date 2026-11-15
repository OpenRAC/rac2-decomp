#include "include_asm.h"
#include "names.h"

extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(float *, float *, float *);
extern float FastVecLength(float *);
extern void vec_scale_to_length(float *, float *, float);
extern void FastVecScale(void *, void *, float);
extern int PlayMobySound(int, int, void *);
extern float math_ease_out_quad(float);
extern int moby_move_and_collide(void *, void *, int, float, float, float);
extern float MobySpringTurn(void *, float, float, float, float, void *);
extern char D_L06_00188660[];

/* Steps the follower's weight toward its goal and blends the state vectors; returns 1 on arrival. */
int func_PAL_L06_004248E8(char *object, float a, float b, float c, float d)
{
    char *rec;
    float dist;
    float cur;
    char *state = *(char **)(object + 0x68);
    int done = 0;
    float range = b * 0.020000001f;
    float ratio;
    char *vec;
    float v[4];
    float unit = a * 0.00040000002f;

    FastVecSub(v, (float *)(state + 0x220), (float *)(object + 0x10));
    dist = FastVecLength(v);
    cur = FastVecLength((float *)(state + 0x230));
    rec = D_L06_00188660 + *(int *)(state + 0x254) * 0x70;
    ratio = cur / unit;
    if (*(char **)(rec + 0x88) != object || *(unsigned char *)(rec + 0x74) == 0)
        *(int *)(state + 0x254) = PlayMobySound(0, 4, object);
    if (dist < cur * ratio) {
        cur -= unit;
        done = 1;
    } else {
        cur += unit * math_ease_out_quad((range - cur) / range);
    }
    vec_scale_to_length(v, v, cur);
    vec = state + 0x230;
    FastVecScale(vec, vec, d);
    FastVecScale(v, v, 1.0f - d);
    FastVecAdd(vec, vec, v);
    moby_move_and_collide(object, vec, 0, 0.0f, 1.5f, 0.0f);
    MobySpringTurn(object, c, 0.0008377582f, 0.0025132746f, 0.04188791f, state + 0x25C);
    return done;
}

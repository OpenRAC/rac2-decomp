#include "include_asm.h"

extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(float *, float *, float *);
extern float func_00282DF0(float *);
extern void func_00282F20(float *, float *, float);
extern void func_00282D30(void *, void *, float);
extern int func_002E5CF8(int, int, void *);
extern float func_002A7798(float);
extern void func_002A8240(void *, void *, int, float, float, float);
extern void func_002A7CA0(void *, float, float, float, float, void *);
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

    func_00282CF0(v, (float *)(state + 0x220), (float *)(object + 0x10));
    dist = func_00282DF0(v);
    cur = func_00282DF0((float *)(state + 0x230));
    rec = D_L06_00188660 + *(int *)(state + 0x254) * 0x70;
    ratio = cur / unit;
    if (*(char **)(rec + 0x88) != object || *(unsigned char *)(rec + 0x74) == 0)
        *(int *)(state + 0x254) = func_002E5CF8(0, 4, object);
    if (dist < cur * ratio) {
        cur -= unit;
        done = 1;
    } else {
        cur += unit * func_002A7798((range - cur) / range);
    }
    func_00282F20(v, v, cur);
    vec = state + 0x230;
    func_00282D30(vec, vec, d);
    func_00282D30(v, v, 1.0f - d);
    func_00282CC0(vec, vec, v);
    func_002A8240(object, vec, 0, 0.0f, 1.5f, 0.0f);
    func_002A7CA0(object, c, 0.0008377582f, 0.0025132746f, 0.04188791f, state + 0x25C);
    return done;
}

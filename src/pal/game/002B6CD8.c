#include "include_asm.h"
#include "names.h"

typedef struct { float x; float y; int pad[2]; } T16_Fd6e0d08a;
extern void *func_L00_0032C638_1(void *, void *);
extern int path_set_follower_nodes(void *, void *, int, int);
extern float func_00283248_9(float, float);
extern int moby_step_controller(void *, void *, float);
extern float func_00282E80_4(void *, void *);

/* Computes the x/y difference between one 16-byte record of the second handle and the record after the first handle's base, dispatches through three helpers and walks a short counter field up or down by one when the last helper's float result stays under a stored threshold. */
int path_follow_nodes_pal(char *s1, char *s2)
{
    char *s0;
    float r;

    s0 = (char *)func_L00_0032C638_1(s1, s2);
    if (s0 == 0)
        return 0;
    if ((int)s2 != *(int *)(s0 + 196))
        path_set_follower_nodes(s1, s2, -1, 0);
    r = func_00283248_9(((T16_Fd6e0d08a *)(s2 + (*(short *)(s0 + 200) << 4)))[1].x - ((T16_Fd6e0d08a *)s1)[1].x,
                ((T16_Fd6e0d08a *)(s2 + (*(short *)(s0 + 200) << 4)))[1].y - ((T16_Fd6e0d08a *)s1)[1].y);
    moby_step_controller(s1, &((T16_Fd6e0d08a *)s2)[*(short *)(s0 + 202) + 1], r);
    if (func_00282E80_4(&((T16_Fd6e0d08a *)s1)[1], &((T16_Fd6e0d08a *)s2)[*(short *)(s0 + 200) + 1])
        <= *(float *)(s0 + 52)) {
        if (*(short *)(s0 + 202) == *(short *)(s0 + 200))
            return 1;
        if (*(short *)(s0 + 202) < *(short *)(s0 + 200))
            *(short *)(s0 + 200) = (unsigned short)*(short *)(s0 + 200) - 1;
        else
            *(short *)(s0 + 200) = (unsigned short)*(short *)(s0 + 200) + 1;
    }
    return 0;
}


#include "include_asm.h"
#include "names.h"

typedef struct { float x; float y; int pad[2]; } T16_Fd6e0d08a;
extern void *func_L00_0032C638_1(void *, void *);
extern int path_set_follower_nodes(void *, void *, int, int);
extern float func_00283248_9(float, float);
extern int moby_step_controller(void *, void *, float);
extern float func_00282E80_4(void *, void *);

/* Computes the x/y difference between one 16-byte record of the second handle and the record after the first handle's base, dispatches through three helpers and walks a short counter field up or down by one when the last helper's float result stays under a stored threshold. */
int path_follow_nodes_pal(char *object, char *nodes)
{
    char *follower;
    float heading;

    follower = (char *)func_L00_0032C638_1(object, nodes);
    if (follower == 0)
        return 0;
    if ((int)nodes != *(int *)(follower + 196))
        path_set_follower_nodes(object, nodes, -1, 0);
    heading = func_00283248_9(((T16_Fd6e0d08a *)(nodes + (*(short *)(follower + 200) << 4)))[1].x - ((T16_Fd6e0d08a *)object)[1].x,
                ((T16_Fd6e0d08a *)(nodes + (*(short *)(follower + 200) << 4)))[1].y - ((T16_Fd6e0d08a *)object)[1].y);
    moby_step_controller(object, &((T16_Fd6e0d08a *)nodes)[*(short *)(follower + 202) + 1], heading);
    if (func_00282E80_4(&((T16_Fd6e0d08a *)object)[1], &((T16_Fd6e0d08a *)nodes)[*(short *)(follower + 200) + 1])
        <= *(float *)(follower + 52)) {
        if (*(short *)(follower + 202) == *(short *)(follower + 200))
            return 1;
        if (*(short *)(follower + 202) < *(short *)(follower + 200))
            *(short *)(follower + 200) = (unsigned short)*(short *)(follower + 200) - 1;
        else
            *(short *)(follower + 200) = (unsigned short)*(short *)(follower + 200) + 1;
    }
    return 0;
}


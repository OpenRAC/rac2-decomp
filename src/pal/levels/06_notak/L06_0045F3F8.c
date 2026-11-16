#include "include_asm.h"

#include "common.h"
extern u8 *g_moby_l06_table MACRO_ADDR;
extern void moby_transform_joint_to_world(void *, int, void *);
extern void vec_scale_to_length(char *, char *, float);
extern void func_PAL_002A7E68(char *, int, int, int);
extern void FastVecScale(char *, char *, float);
extern float moby_get_anim_value(char *);
extern void make_hit_descriptor(void *, char *, int, void *, float);
extern int coll_process_hit(void *, float, int, char *, void *);
extern void *g_hit_l06_result;
extern void moby_transform_joint_to_world(void *, int, void *);
extern void *g_hit_l06_result;

/* Runs the shared pickup test: when the object is in the given state and the draw is inside the window, aims at the target and, on a hit with the expected tag, hands over to the next state. */
void actor_try_pickup_transition_pal(char *obj, float lo, char *self, float hi, int kind, int sub, float scale, float reach, float range,
                       int anim, int link, int next, void *tag)
{
    float dir[4] __attribute__((aligned(16)));
    char aim[0x30] __attribute__((aligned(16)));
    float probe[4] __attribute__((aligned(16)));
    float roll = moby_get_anim_value(obj);
    char *vec;

    if (*(u8 *)(obj + 0x20) == kind && *(u8 *)(obj + 0x42) == sub && lo < roll && roll < hi) {
        vec = self + 0xC0;
        vec_scale_to_length((char *)dir, vec, scale);
        dir[2] = 1.0f;
        make_hit_descriptor(aim, obj, 1, dir, reach);
        moby_transform_joint_to_world(obj, 0, probe);
        if (coll_process_hit(probe, range, 0x21, obj, aim) != 0 && g_hit_l06_result == tag) {
            FastVecScale(vec, vec, -1.0f);
            *(float *)(self + 0xC8) = -0.060000002f;
            if (*(u8 *)(obj + 0x43) != anim)
                func_PAL_002A7E68(obj, anim, link, 5);
            *(u8 *)(obj + 0x20) = next;
        }
    }
}


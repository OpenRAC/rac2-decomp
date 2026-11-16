#include "names.h"
/* func_PAL_L04_00408A58, the PAL copy of func_L04_004045E0: the same C, where func_L04_00403530
   becomes func_PAL_L04_00407940; func_L04_004027B0 becomes func_PAL_L04_00406B68;
   func_L04_00400EE0 becomes func_PAL_L04_00405268; func_L04_004044B8 becomes
   func_PAL_L04_00408930; func_L04_00404100 becomes func_PAL_L04_00408578; 300 becomes 250. */
#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef struct { Quad v[3]; } __attribute__((aligned(16))) Axes4045E0;

extern char g_tether_zero_vec[];
extern Quad g_collision_quad;
extern const Axes4045E0 g_hoverbike_axes;

extern float fast_vec_dist(void *, void *);
extern void moby_update_ground_check(void *);
extern int coll_test_point(void *, int, void *, float);
extern void racer_compute_route_lengths(u8 *);
extern void FastVecScale(void *, void *, float);
extern float math_random_float_range(float, float);
extern void func_PAL_L04_00407940(u8 *, u8 *);
extern void func_PAL_L04_00406B68(u8 *, u8 *);
extern void func_PAL_L04_00405268(u8 *, u8 *);
extern void racer_update_checkpoint_progress_pal(u8 *, u8 *);
extern void racer_update_bike_lean_pal(u8 *, u8 *);
extern s32 FindNearestRoutePointIndex(void *, void *, s32);
extern float IntToFloat(int);
extern void anim_sample_key_track(float, float, void *, void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern int math_fast_helper_a(void *, float);
extern float FastVecDot(void *, void *);
extern void FindNearestRoutePoint(u8 *, u8 *, void *, void *, void *, void *);

/* Update of the path follower: state 0 lands it, scales its three axes and draws six random
   phases; state 2 runs its behaviours while the leader is not waiting; state 3 walks to the
   nearest path node and, after 300 frames, leaves for the leader once it is 5 units away and
   out of sight; state 4 drops both targets. The leader's own state can hold it entirely. */
void enemy_hoverbike_update_pal(u8 *obj)
{
    u8 *st = *(u8 **)(obj + 0x68);
    u8 *e;
    u8 *es;
    u8 *pos;
    u8 *dst;
    u8 *src;
    f32 *ph;
    union {
        Axes4045E0 axes;
        f32 d[4];
    } u;
    f32 scale;
    f32 f;
    int k;
    int i;
    Quad t0, t1, t2;
    int j;
    f32 *q;

    *(f32 *)(obj + 0x2C) = *(f32 *)(*(u8 **)(obj + 0x24) + 0x24) * 0.25f;
    obj[0x30] = 0xFF;
    *(s16 *)(obj + 0x32) = 0x7F;
    if (obj[0x31] != 0 && fast_vec_dist(obj + 0x10, g_tether_zero_vec) < 9.0f) {
        moby_update_ground_check(obj);
        obj[0x6F] = 8;
    }
    if (*(u8 **)(st + 0x164) != 0) {
        if ((*(u8 **)(st + 0x164))[0x20] == 1 || (*(u8 **)(st + 0x164))[0x20] == 4 || (*(u8 **)(st + 0x164))[0x20] == 0)
            return;
        if ((*(u8 **)(st + 0x164))[0x20] == 2 && (u8)((*(u8 **)(st + 0x164))[0xBC] - 5) < 2)
            (*(s32 *)(st + 0x1B8))++;
    }
    switch (obj[0x20]) {
    case 0:
        if (coll_test_point(obj + 0x10, 4, obj, *(f32 *)(st + 0x90)))
            *(Quad *)(obj + 0x10) = g_collision_quad;
        *(Quad *)(st + 0xB0) = *(Quad *)(obj + 0x10);
        *(Quad *)(st + 0xC0) = *(Quad *)(obj + 0xF0);
        dst = st + 0x200;
        ph = (f32 *)(st + 0x184);
        racer_compute_route_lengths(obj);
        obj[0x20] = 1;
        *(s32 *)(st + 0x30) = 0;
        t0 = g_hoverbike_axes.v[0];
        t1 = g_hoverbike_axes.v[1];
        t2 = g_hoverbike_axes.v[2];
        *(u16 *)(obj + 0x34) |= 0x41;
        obj[0x62] = 1;
        u.axes.v[0] = t0;
        u.axes.v[1] = t1;
        u.axes.v[2] = t2;
        scale = *(f32 *)(obj + 0x2C) / *(f32 *)(*(u8 **)(obj + 0x24) + 0x24);
        src = (u8 *)&u.axes;
        for (i = 2; i >= 0; i--) {
            FastVecScale(dst, src, scale);
            src += 0x10;
            dst += 0x10;
        }
        q = ph;
        for (j = 5; j >= 0; j--)
            *q++ = math_random_float_range(0.0f, 1.0f);
        return;
    case 1:
        break;
    case 2:
        if (*(u8 **)(st + 0x164) != 0 && (*(u8 **)(st + 0x164))[0x20] == 2 && (*(u8 **)(st + 0x164))[0xBC] == 0)
            return;
        func_PAL_L04_00407940(obj, st);
        func_PAL_L04_00406B68(obj, st);
        func_PAL_L04_00405268(obj, st);
        racer_update_checkpoint_progress_pal(obj, st);
        racer_update_bike_lean_pal(obj, st);
        return;
    case 3:
        if (*(u16 *)(obj + 0x96) == 0) {
            k = FindNearestRoutePointIndex(obj, *(u8 **)(st + 0x110), 1);
            *(Quad *)(obj + 0x10) = *(Quad *)(*(u8 **)(st + 0x110) + k * 16 + 0x10);
            f = IntToFloat(k) * *(f32 *)(*(u8 **)(st + 0x110) + 0x1C) +
                (*(s32 *)(st + 0x244) != 0 ? 15.0f : 5.0f);
            *(f32 *)(st + 0xA8) = f;
            anim_sample_key_track(f, *(f32 *)(*(u8 **)(st + 0x110) + 0x1C), *(u8 **)(st + 0x110),
                          st + 0x114, st + 0x118, st + 0xF0);
        }
        if (*(u16 *)(obj + 0x96) >= 250 && (e = *(u8 **)(st + 0x164)) != 0) {
            pos = obj + 0x10;
            es = *(u8 **)(e + 0x68);
            FastVecSub(u.d, pos, e + 0x10);
            if (math_fast_helper_a(pos, 60.0f) == -1 && FastVecDot(u.d, u.d) > 25.0f) {
                *(s32 *)(obj + 0x98) = *(s32 *)(*(u8 **)(obj + 0x24) + 0x10);
                *(u16 *)(obj + 0x34) = (*(u16 *)(obj + 0x34) & 0xFFBE) | 0x1400;
                if (*(u8 **)(st + 0x8C) != 0)
                    *(u16 *)(*(u8 **)(st + 0x8C) + 0x34) &= 0xFFBE;
                FindNearestRoutePoint(obj, es, st + 0x120, st + 0x124, st + 0x11C, *(void **)(st + 0x160));
                obj[0x20] = 2;
            }
        }
        (*(u16 *)(obj + 0x96))++;
        break;
    case 4:
        *(s32 *)(obj + 0x48) = 0;
        if (*(u8 **)(st + 0x8C) != 0)
            *(s32 *)(*(u8 **)(st + 0x8C) + 0x48) = 0;
        obj[0x20] = 1;
        break;
    }
}

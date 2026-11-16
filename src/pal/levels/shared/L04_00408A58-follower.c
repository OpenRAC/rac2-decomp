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
extern void UpdateRouteFollowerPace_pal(u8 *, u8 *);
extern void racer_update_boost_pad_contact_pal(u8 *, u8 *);
extern void hoverbike_update_racing_movement_pal(u8 *, u8 *);
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
void enemy_hoverbike_update_pal(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68);
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

    *(f32 *)(moby + 0x2C) = *(f32 *)(*(u8 **)(moby + 0x24) + 0x24) * 0.25f;
    moby[0x30] = 0xFF;
    *(s16 *)(moby + 0x32) = 0x7F;
    if (moby[0x31] != 0 && fast_vec_dist(moby + 0x10, g_tether_zero_vec) < 9.0f) {
        moby_update_ground_check(moby);
        moby[0x6F] = 8;
    }
    if (*(u8 **)(vars + 0x164) != 0) {
        if ((*(u8 **)(vars + 0x164))[0x20] == 1 || (*(u8 **)(vars + 0x164))[0x20] == 4 || (*(u8 **)(vars + 0x164))[0x20] == 0)
            return;
        if ((*(u8 **)(vars + 0x164))[0x20] == 2 && (u8)((*(u8 **)(vars + 0x164))[0xBC] - 5) < 2)
            (*(s32 *)(vars + 0x1B8))++;
    }
    switch (moby[0x20]) {
    case 0:
        if (coll_test_point(moby + 0x10, 4, moby, *(f32 *)(vars + 0x90)))
            *(Quad *)(moby + 0x10) = g_collision_quad;
        *(Quad *)(vars + 0xB0) = *(Quad *)(moby + 0x10);
        *(Quad *)(vars + 0xC0) = *(Quad *)(moby + 0xF0);
        dst = vars + 0x200;
        ph = (f32 *)(vars + 0x184);
        racer_compute_route_lengths(moby);
        moby[0x20] = 1;
        *(s32 *)(vars + 0x30) = 0;
        t0 = g_hoverbike_axes.v[0];
        t1 = g_hoverbike_axes.v[1];
        t2 = g_hoverbike_axes.v[2];
        *(u16 *)(moby + 0x34) |= 0x41;
        moby[0x62] = 1;
        u.axes.v[0] = t0;
        u.axes.v[1] = t1;
        u.axes.v[2] = t2;
        scale = *(f32 *)(moby + 0x2C) / *(f32 *)(*(u8 **)(moby + 0x24) + 0x24);
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
        if (*(u8 **)(vars + 0x164) != 0 && (*(u8 **)(vars + 0x164))[0x20] == 2 && (*(u8 **)(vars + 0x164))[0xBC] == 0)
            return;
        UpdateRouteFollowerPace_pal(moby, vars);
        racer_update_boost_pad_contact_pal(moby, vars);
        hoverbike_update_racing_movement_pal(moby, vars);
        racer_update_checkpoint_progress_pal(moby, vars);
        racer_update_bike_lean_pal(moby, vars);
        return;
    case 3:
        if (*(u16 *)(moby + 0x96) == 0) {
            k = FindNearestRoutePointIndex(moby, *(u8 **)(vars + 0x110), 1);
            *(Quad *)(moby + 0x10) = *(Quad *)(*(u8 **)(vars + 0x110) + k * 16 + 0x10);
            f = IntToFloat(k) * *(f32 *)(*(u8 **)(vars + 0x110) + 0x1C) +
                (*(s32 *)(vars + 0x244) != 0 ? 15.0f : 5.0f);
            *(f32 *)(vars + 0xA8) = f;
            anim_sample_key_track(f, *(f32 *)(*(u8 **)(vars + 0x110) + 0x1C), *(u8 **)(vars + 0x110),
                          vars + 0x114, vars + 0x118, vars + 0xF0);
        }
        if (*(u16 *)(moby + 0x96) >= 250 && (e = *(u8 **)(vars + 0x164)) != 0) {
            pos = moby + 0x10;
            es = *(u8 **)(e + 0x68);
            FastVecSub(u.d, pos, e + 0x10);
            if (math_fast_helper_a(pos, 60.0f) == -1 && FastVecDot(u.d, u.d) > 25.0f) {
                *(s32 *)(moby + 0x98) = *(s32 *)(*(u8 **)(moby + 0x24) + 0x10);
                *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) & 0xFFBE) | 0x1400;
                if (*(u8 **)(vars + 0x8C) != 0)
                    *(u16 *)(*(u8 **)(vars + 0x8C) + 0x34) &= 0xFFBE;
                FindNearestRoutePoint(moby, es, vars + 0x120, vars + 0x124, vars + 0x11C, *(void **)(vars + 0x160));
                moby[0x20] = 2;
            }
        }
        (*(u16 *)(moby + 0x96))++;
        break;
    case 4:
        *(s32 *)(moby + 0x48) = 0;
        if (*(u8 **)(vars + 0x8C) != 0)
            *(s32 *)(*(u8 **)(vars + 0x8C) + 0x48) = 0;
        moby[0x20] = 1;
        break;
    }
}

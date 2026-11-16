/* func_PAL_L04_00407940, the PAL copy of func_L04_00403530: the same C for 50 Hz, with the per-frame speeds scaled by 6/5 and the frame counts by 5/6. */
#include "common.h"

/* Own unit: the branch to the padding nop after the 15.0f constant needs -frac2-hazard-labels. */

#define INT_AT(p, o) (*(int *)((p) + (o)))
#define SHORT_AT(p, o) (*(short *)((p) + (o)))
#define FLOAT_AT(p, o) (*(float *)((p) + (o)))
#define PTR_AT(p, o) (*(unsigned char **)((p) + (o)))

typedef unsigned int PathQuad __attribute__((mode(TI)));

extern int g_is_pal_video MACRO_ADDR;
extern int g_current_lap __attribute__((sda));

extern void UpdateRacerRouteChoice_pal(void *);
extern float IntToFloat(int);
extern int GetCollHitMaterial(void);
extern float math_fabs(float);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern float mat_fast_helper_a(float, float);
extern float fast_subtract_rotations(float, float);
extern void anim_start_blended(void *, int, int, int);
extern int vec_find_nearest_point_index(void *, void *);
extern float fast_vec_dist(void *, void *);
extern float math_distance_to_line(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecCross(void *, void *, void *);
extern float vec_distance_xy(void *, void *);
extern void anim_sample_key_track(float, float, void *, void *, void *, void *);
extern float FastDiffRots(float, float);
extern int FindNearestRoutePointIndex(void *, void *, int);
extern float math_random_float_range(float, float);
extern int FloatToInt(float);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void add_vectors(void *, void *, void *);

/* Paces a route follower: derives its speed from the time left and from a peer at +0x164,
   steers its lateral offset (+0x16C) and advances its point on the route at +0x110. */
void UpdateRouteFollowerPace_pal(unsigned char *moby, unsigned char *vars)
{
    float to_next[4], to_peer[4], cross[4], tmp[4];
    unsigned char *peer_vars;
    float speed, distance;
    int i, neighbor, next, old_index;

    if (INT_AT(vars, 0x180))
        INT_AT(vars, 0x180)--;
    if (SHORT_AT(vars, 0x17E))
        SHORT_AT(vars, 0x17E)--;
    {
        float extra = FLOAT_AT(vars, 0x2D0);

        if (g_is_pal_video)
            speed = (FLOAT_AT(vars, 0x1B4) - FLOAT_AT(vars, 0x11C))
                    / ((FLOAT_AT(vars, 0x1B0) + extra) - (float)INT_AT(vars, 0x1B8) * 0.02f);
        else
            speed = (FLOAT_AT(vars, 0x1B4) - FLOAT_AT(vars, 0x11C))
                    / ((FLOAT_AT(vars, 0x1B0) + extra) - (float)INT_AT(vars, 0x1B8) * 0.016666668f);
    }
    FLOAT_AT(vars, 0x2D4) = speed;
    if (speed < 6.645f)
        FLOAT_AT(vars, 0x2D4) = 6.645f;
    if (INT_AT(vars, 0x1C0) > 0)
        return;

    UpdateRacerRouteChoice_pal(moby);

    if (speed < 0.0f
        || (speed >= 22.15f && INT_AT(vars, 0x160) >= 2
            && FLOAT_AT(vars, 0x11C) / FLOAT_AT(vars, 0x1B4) > 0.66f))
        speed = 22.15f;
    if (speed > 28.15f)
        speed = 28.15f;
    if (speed < 13.29f)
        speed = 13.29f;
    FLOAT_AT(vars, 0x134) = speed * 0.020000001f - IntToFloat(vars[0xA2] - 1) * 0.014f;

    if (PTR_AT(vars, 0x164) && !vars[0xA5] && GetCollHitMaterial() != 5) {
        float delta;
        unsigned char *peer = PTR_AT(vars, 0x164);

        peer_vars = PTR_AT(peer, 0x68);
        delta = FLOAT_AT(peer_vars, 0x310) - FLOAT_AT(vars, 0x11C);
        /* Re-reading the peer's state here lets jump threading skip the identical test below. */
        if (FLOAT_AT(vars, 0x11C) + 12.0f < FLOAT_AT(peer_vars, 0x310)
            && FLOAT_AT(vars, 0x11C) > FLOAT_AT(peer_vars, 0x310) - 150.0f
            && g_current_lap >= INT_AT(vars, 0x160)
            && PTR_AT(peer_vars, 0x730) != moby
            && PTR_AT(vars, 0x164)[0xBC] == 5)
            FLOAT_AT(vars, 0x134) += (delta - 12.0f) * 0.002f;
        if (PTR_AT(vars, 0x164)[0xBC] == 5 && !INT_AT(peer_vars, 0x724) && delta > 1.0f && delta < 10.0f) {
            PTR_AT(peer_vars, 0x734) = moby;
            INT_AT(peer_vars, 0x720) = 1;
        }
        if (INT_AT(vars, 0x168) && vars[0xA2] != 1 && math_fabs(delta) < 10.0f
            && INT_AT(vars, 0x160) >= g_current_lap) {
            int closest;

            FLOAT_AT(vars, 0x134) += (delta * 0.020000001f) + (delta * 0.020000001f);
            if (FLOAT_AT(vars, 0x11C) > FLOAT_AT(peer_vars, 0x310) && !INT_AT(vars, 0x180)
                && !SHORT_AT(vars, 0x17E) && PTR_AT(vars, 0x8C)) {
                float lead = FLOAT_AT(vars, 0x11C) - FLOAT_AT(peer_vars, 0x310);

                if (lead < 10.0f && lead > 2.0f && !math_random_int_below(1)) {
                    unsigned char *target = PTR_AT(vars, 0x164);
                    float angle = fast_subtract_rotations(FLOAT_AT(moby, 0xF8),
                                                mat_fast_helper_a(FLOAT_AT(target, 0x10) - FLOAT_AT(moby, 0x10),
                                                              FLOAT_AT(target, 0x14) - FLOAT_AT(moby, 0x14)));

                    if (angle > 0.0f)
                        anim_start_blended(PTR_AT(vars, 0x8C), 8, 0, 10);
                    else
                        anim_start_blended(PTR_AT(vars, 0x8C), 7, 0, 10);
                    INT_AT(vars, 0x180) = (math_random_int_range(120, 180) * 5 + 2) / 6;
                } else if (FLOAT_AT(vars, 0x11C) - FLOAT_AT(peer_vars, 0x310) > -5.0f && !math_random_int_below(3)) {
                    unsigned char *target = PTR_AT(vars, 0x164);
                    float angle = fast_subtract_rotations(FLOAT_AT(moby, 0xF8),
                                                mat_fast_helper_a(FLOAT_AT(target, 0x10) - FLOAT_AT(moby, 0x10),
                                                              FLOAT_AT(target, 0x14) - FLOAT_AT(moby, 0x14)));

                    if (angle > 0.0f)
                        anim_start_blended(PTR_AT(vars, 0x8C), 5, 0, 10);
                    else
                        anim_start_blended(PTR_AT(vars, 0x8C), 6, 0, 10);
                    INT_AT(vars, 0x180) = (math_random_int_range(120, 300) * 5 + 2) / 6;
                } else
                    INT_AT(vars, 0x180) = 50;
            }
            *(PathQuad *)to_next = *(PathQuad *)(PTR_AT(vars, 0x164) + 0x10);
            closest = vec_find_nearest_point_index(to_next, PTR_AT(vars, 0x110));
            if (closest == 0 || closest == INT_AT(PTR_AT(vars, 0x110), 0) - 1)
                FLOAT_AT(vars, 0x16C) = 0;
            else {
                float next_dist, prev_dist;
                int prev;

                next = closest + 1;
                prev = closest - 1;
                next_dist = fast_vec_dist(PTR_AT(vars, 0x110) + 16 + next * 16, PTR_AT(vars, 0x164) + 16);
                prev_dist = fast_vec_dist(PTR_AT(vars, 0x110) + 16 + prev * 16, PTR_AT(vars, 0x164) + 16);
                neighbor = prev;
                if (next_dist < prev_dist)
                    neighbor = next;
                FLOAT_AT(vars, 0x16C) = math_distance_to_line(PTR_AT(vars, 0x110) + 16 + closest * 16,
                                                          PTR_AT(vars, 0x110) + 16 + neighbor * 16,
                                                          PTR_AT(vars, 0x164) + 16);
                FastVecSub(tmp, PTR_AT(vars, 0x110) + 16 + next * 16, PTR_AT(vars, 0x110) + 16 + closest * 16);
                *(PathQuad *)to_next = *(PathQuad *)tmp;
                FastVecSub(tmp, PTR_AT(vars, 0x164) + 16, PTR_AT(vars, 0x110) + 16 + closest * 16);
                *(PathQuad *)to_peer = *(PathQuad *)tmp;
                FastVecCross(cross, to_next, to_peer);
                if (cross[2] > 0.0f)
                    FLOAT_AT(vars, 0x16C) = -FLOAT_AT(vars, 0x16C);
                if (FLOAT_AT(vars, 0x16C) > 1.5f)
                    FLOAT_AT(vars, 0x16C) = 1.5f;
                if (FLOAT_AT(vars, 0x16C) < -1.5f)
                    FLOAT_AT(vars, 0x16C) = -1.5f;
            }
            INT_AT(vars, 0x174) = -1000;
        } else if ((float)INT_AT(vars, 0x174) < 0.0f)
            FLOAT_AT(vars, 0x16C) = 0.0f;
        if (FLOAT_AT(vars, 0x134) > 0.563f)
            FLOAT_AT(vars, 0x134) = 0.563f;
        if (FLOAT_AT(vars, 0x134) < 0.1772f)
            FLOAT_AT(vars, 0x134) = 0.1772f;
    }

    old_index = INT_AT(vars, 0x114);
    distance = vec_distance_xy(vars + 0xF0, moby + 0x10);
    if ((INT_AT(vars, 0x244) && distance < 15.0f) || (!INT_AT(vars, 0x244) && distance < 5.0f)) {
        FLOAT_AT(vars, 0xA8) += (INT_AT(vars, 0x244) ? 15.0f : 5.0f) - distance;
        if (FLOAT_AT(PTR_AT(vars, 0x110), 0x1C) * IntToFloat(INT_AT(PTR_AT(vars, 0x110), 0)) < FLOAT_AT(vars, 0xA8))
            FLOAT_AT(vars, 0xA8) -= FLOAT_AT(PTR_AT(vars, 0x110), 0x1C) * IntToFloat(INT_AT(PTR_AT(vars, 0x110), 0));
        anim_sample_key_track(FLOAT_AT(vars, 0xA8), FLOAT_AT(PTR_AT(vars, 0x110), 0x1C), PTR_AT(vars, 0x110),
                      vars + 0x114, vars + 0x118, vars + 0xF0);
    } else {
        anim_sample_key_track(FLOAT_AT(vars, 0xA8), FLOAT_AT(PTR_AT(vars, 0x110), 0x1C), PTR_AT(vars, 0x110),
                      vars + 0x114, vars + 0x118, vars + 0xF0);
    }
    {
        float f = FastDiffRots(FLOAT_AT(moby, 0xF8),
                                mat_fast_helper_a(FLOAT_AT(vars, 0xF0) - FLOAT_AT(moby, 0x10),
                                              FLOAT_AT(vars, 0xF4) - FLOAT_AT(moby, 0x14)));

        if (f > 1.047197699546814f) {
            i = FindNearestRoutePointIndex(moby, PTR_AT(vars, 0x110), 0);
            {
                float along = IntToFloat(i) * FLOAT_AT(PTR_AT(vars, 0x110), 0x1C);

                f = along + (INT_AT(vars, 0x244) ? 15.0f : 5.0f);
            }
            FLOAT_AT(vars, 0xA8) = f;
            anim_sample_key_track(f, FLOAT_AT(PTR_AT(vars, 0x110), 0x1C), PTR_AT(vars, 0x110),
                          vars + 0x114, vars + 0x118, vars + 0xF0);
        }
    }
    for (i = old_index; i <= INT_AT(vars, 0x114); i++) {
        unsigned char *point = PTR_AT(vars, 0x110) + i * 16;
        float f = FLOAT_AT(point, 0x1C);

        if (f >= 1000.0f) {
            FLOAT_AT(vars, 0x16C) += math_random_float_range(-0.25f, 0.25f);
            if (FLOAT_AT(vars, 0x16C) > 1.5f)
                FLOAT_AT(vars, 0x16C) = 1.5f;
            if (FLOAT_AT(vars, 0x16C) < -1.5f)
                FLOAT_AT(vars, 0x16C) = -1.5f;
            INT_AT(vars, 0x174) = FloatToInt((math_random_float_range(3.0f, 6.0f) * 300.0f + 2.0f) * 0.16666667f);
        } else if (f <= -1000.0f) {
            FLOAT_AT(vars, 0x16C) = 0.0f;
            INT_AT(vars, 0x174) = -1000;
        }
    }
    if (INT_AT(vars, 0x174) > 0) {
        INT_AT(vars, 0x174)--;
        if (INT_AT(vars, 0x174) == -1) {
            FLOAT_AT(vars, 0x16C) += math_random_float_range(-0.25f, 0.25f);
            if (FLOAT_AT(vars, 0x16C) > 1.5f)
                FLOAT_AT(vars, 0x16C) = 1.5f;
            if (FLOAT_AT(vars, 0x16C) < -1.5f)
                FLOAT_AT(vars, 0x16C) = -1.5f;
            INT_AT(vars, 0x174) = FloatToInt((math_random_float_range(3.0f, 6.0f) * 300.0f + 2.0f) * 0.16666667f);
        }
    }
    distance = FLOAT_AT(vars, 0x170) + FLOAT_AT(vars, 0x16C);
    to_next[0] = math_fast_sin_or_cos_a(FastAddRotations(FLOAT_AT(moby, 0xF8), 1.5707964897155762f)) * distance;
    to_next[1] = math_fast_sin_or_cos_b(FastAddRotations(FLOAT_AT(moby, 0xF8), 1.5707964897155762f)) * distance;
    to_next[2] = 0.0f;
    add_vectors(to_peer, vars + 0xF0, to_next);
}

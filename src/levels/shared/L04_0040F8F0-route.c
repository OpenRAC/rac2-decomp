#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    float x, y, z, w;
} RoutePoint;

typedef struct {
    int count;
    int pad04[3];
    RoutePoint points[1];
} Route;

typedef struct {
    char pad00[0x10];
    float pos[4];
} RouteObject;

typedef struct {
    char pad000[0x1A8];
    int route;
    int links[4];
    int exits[4];
    int entries[4];
} RouteState;

extern Route *g_route_path_table[];
extern char g_route_frame_origin[] __attribute__((sda));
extern char g_route_frame_delta[] __attribute__((sda));
extern char g_route_frame_forward[] __attribute__((sda));
extern char g_route_frame_side[] __attribute__((sda));

extern void FastVecSub(void *, void *, void *);
extern float func_L00_002EE290(void *);
extern float math_fabs(float);
extern float FastVecDot(void *, void *);
extern void FastVecCross(void *, void *, void *);
extern float fast_vec_dist(void *, void *);
extern void set_identity_rotation_rows(void *);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern void func_001290E0(void *, void *);
extern float math_closest_point_on_segment(void *, void *, void *, void *);

/* Rebuilds the frame at D_L04_001B3190 from a segment, keeping the previous direction
   when the new one is degenerate or reversed. */
#define UPDATE_FRAME(projection, from, to, flatten) { \
    *(TI128 *)D_L04_001B3190 = *(TI128 *)(projection); \
    func_00282CF0(delta0, from, to); \
    if (flatten) delta0[2] = 0; \
    if (func_00282C48(func_00282DB0(delta0, delta0)) < 0.01f) \
        qcopy_nc(D_L04_001B31A0, saved); \
    else qcopy_nc(D_L04_001B31A0, delta0); \
    func_001290E0(D_L04_001B31A0, D_L04_001B31A0); \
    if (func_00282DB0(D_L04_001B31A0, saved) <= 0) \
        qcopy_nc(D_L04_001B31A0, saved); \
    func_00282DD8(D_L04_001B31B0, D_L04_001B31C0, D_L04_001B31A0); \
    func_001290E0(D_L04_001B31B0, D_L04_001B31B0); \
}

/* Distance of the object along its route, measured on the segments either side of `point`
   of the current route (link -1) or of one of its links. */
float ProjectLinkedRouteDistance(RouteObject *object, RouteState *state, int link, int point, int mode, int update)
{
    float saved[4] __attribute__((aligned(16)));
    float delta0[4] __attribute__((aligned(16)));
    float delta1[4] __attribute__((aligned(16)));
    float projected0[4] __attribute__((aligned(16)));
    float projected1[4] __attribute__((aligned(16)));
    Route *base = g_route_path_table[state->route];
    int orient = point >= 2;
    Route *path, *other = 0;
    int next, previous;
    float distance, value;

    qcopy_nc(saved, g_route_frame_delta);
    if (update && orient) set_identity_rotation_rows(g_route_frame_delta);

    if (link == -1) {
        int before = base->count - 1, after = base->count + 1;
        int wrapPrev = (point + before) % base->count;
        int wrapNext = (point + after) % base->count;

        math_closest_point_on_segment(projected0, &base->points[wrapPrev], &base->points[point], object->pos);
        math_closest_point_on_segment(projected1, &base->points[point], &base->points[wrapNext], object->pos);
        FastVecSub(delta0, projected0, object->pos);
        FastVecSub(delta1, projected1, object->pos);
        distance = func_L00_002EE290(delta0);
        if (distance < func_L00_002EE290(delta1)) {
            if (update && orient) UPDATE_FRAME(projected0, &base->points[point], &base->points[wrapPrev], 1)
            distance = fast_vec_dist(projected0, &base->points[wrapPrev]);
            return IntToFloat(wrapPrev) * base->points[0].w + distance;
        } else {
            if (update && orient) UPDATE_FRAME(projected1, &base->points[wrapNext], &base->points[point], 1)
            distance = fast_vec_dist(projected1, &base->points[point]);
            return IntToFloat(point) * base->points[0].w + distance;
        }
    }

    path = g_route_path_table[state->links[link]];
    next = point + 1;
    previous = point - 1;
    if (previous == -1) {
        if (state->entries[link] != -1)
            other = g_route_path_table[state->links[state->entries[link]]];
        else other = base;
        math_closest_point_on_segment(projected0, &other->points[FloatToInt(path->points[1].w)], &path->points[point], object->pos);
        math_closest_point_on_segment(projected1, &path->points[point], &path->points[next], object->pos);
        FastVecSub(delta0, projected0, object->pos);
        FastVecSub(delta1, projected1, object->pos);
        distance = func_L00_002EE290(delta0);
        if (distance < func_L00_002EE290(delta1)) {
            if (update && orient) UPDATE_FRAME(projected0, &path->points[point], &other->points[FloatToInt(path->points[1].w)], 0)
            return path->points[3].w - fast_vec_dist(projected0, &path->points[point]);
        }
        previous = 0;
    } else if (next > path->count - 1) {
        if (state->exits[link] != -1)
            other = g_route_path_table[state->links[state->exits[link]]];
        else other = base;
        math_closest_point_on_segment(projected0, &path->points[point], &path->points[previous], object->pos);
        math_closest_point_on_segment(projected1, &other->points[FloatToInt(path->points[2].w)], &path->points[point], object->pos);
        FastVecSub(delta0, projected0, object->pos);
        FastVecSub(delta1, projected1, object->pos);
        distance = func_L00_002EE290(delta0);
        if (func_L00_002EE290(delta1) < distance) {
            if (update && orient) UPDATE_FRAME(projected1, &path->points[point], &other->points[FloatToInt(path->points[2].w)], 0)
            return path->points[4].w + fast_vec_dist(projected1, &path->points[point]);
        }
        next = point;
    }

    math_closest_point_on_segment(projected0, &path->points[previous], &path->points[point], object->pos);
    math_closest_point_on_segment(projected1, &path->points[point], &path->points[next], object->pos);
    FastVecSub(delta0, projected0, object->pos);
    FastVecSub(delta1, projected1, object->pos);
    distance = func_L00_002EE290(delta0);
    if (distance < func_L00_002EE290(delta1)) {
        if (update && orient) UPDATE_FRAME(projected0, &path->points[point], &path->points[previous], 0)
        distance = fast_vec_dist(projected0, &path->points[previous]);
        value = IntToFloat(previous) * path->points[0].w + distance;
    } else {
        if (update && orient) UPDATE_FRAME(projected1, &path->points[next], &path->points[point], 0)
        distance = fast_vec_dist(projected1, &path->points[point]);
        value = IntToFloat(point) * path->points[0].w + distance;
    }
    value /= (float)path->count * path->points[0].w;
    return (path->points[4].w - path->points[3].w) * value + path->points[1].w * base->points[0].w;
}

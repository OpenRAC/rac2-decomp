#include "include_asm.h"

#include "common.h"
typedef int ControllerQuad __attribute__((mode(TI)));
extern unsigned int ref_L13_004095F8_00(unsigned int);
extern void FastVecSub(void *, void *, void *);
extern void matrix_from_basis_rows(void *, void *);
extern void ref_L13_004095F8_01(char *, char *, int);
extern void moby_rotate_away_from_dir(void *, void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void moby_follow_platform(char *, char *);
extern void moby_probe_ground(char *, char *);
extern void creature_compute_motion_pal(char *, char *, void *, ControllerQuad *, void *, void *, char *);
extern void creature_push_from_walls(char *, char *, void *, void *, char *);
extern void creature_resolve_ground_coll(char *, char *, char *, char *, char *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern int CollLine(void *, void *, int, void *, void *);
extern int g_game_l13_frame_counter MACRO_ADDR;
extern char g_collision_l13_result[];

/* 0x40 inverse basis, 0x30 rotation and complete 16-byte vectors correspond
 * to the extents read/written by the current helper implementations. The two
 * reserved vector arguments are forwarded but never dereferenced by either
 * helper; they are not read before initialization or cleared artificially. */
int creature_move_along_ground_pal(char *object, char *target)
{
    float difference[4];
    float inverse[4][4];
    float normal[4];
    float rotation[3][4];
    float previous[4];
    float reserved0[4], reserved1[4];
    float start[4], end[4];
    char *transform;
    char *data = (char *)ref_L13_004095F8_00((unsigned int)object);
    if (!data) return 8;
    if (g_game_l13_frame_counter == *(int *)(data + 0xbc)) return *(int *)(data + 0x94);
    FastVecSub(difference, target, object + 0x10);
    transform = (char *)inverse;
    matrix_from_basis_rows(transform, object + 0xc0);
    ref_L13_004095F8_01(object, (char *)normal, 0);
    moby_rotate_away_from_dir(object + 0xc0, normal, rotation);
    matrix_mul_vec3(data + 0xa0, data + 0xa0, rotation);
    *(int *)(data + 0x98) = *(int *)(data + 0x94);
    *(int *)(data + 0x94) = 0;
    moby_follow_platform(object, data);
    qcopy(previous, object + 0x10);
    if (g_game_l13_frame_counter - *(int *)(data + 0xbc) >= 2 || !*(int *)(data + 0xbc)) {
        moby_probe_ground(object, data);
        *(int *)(data + 0xb4) = 0;
        *(int *)(data + 0x9c) |= -3;
        ((unsigned char *)data)[0xea] = 255;
        qzero(data + 0xa0);
    }
    *(int *)(data + 0xbc) = g_game_l13_frame_counter;
    creature_compute_motion_pal(object, data, target, (ControllerQuad *)difference, reserved0, reserved1, transform);
    creature_push_from_walls(object, data, previous, reserved1, transform);
    creature_resolve_ground_coll(object, data, target, (char *)previous, transform);
    vec_scale_to_length(start, object + 0xe0, 0.1f);
    vec_scale_to_length(end, object + 0xe0, -3.0f);
    FastVecAdd(start, start, object + 0x10);
    FastVecAdd(end, end, object + 0x10);
    if (CollLine(start, end, 2, object, 0)) qcopy(object + 0x10, g_collision_l13_result + 0x20);
    return *(int *)(data + 0x94);
}


typedef struct {
    char pad0[0xC4];
    char *path;
    short cur;
    short goal;
} Walk_409840;
extern Walk_409840 *ref_L13_00409840_00(char *);
extern int path_set_follower_nodes(void *, void *, int, int);
extern float vec_distance_xy(void *, void *);
extern int creature_move_along_ground_pal(char *, char *);
extern int g_current_map_index __attribute__((section(".sdata")));

int AdvancePathWaypoint_pal(char *obj, char *path)
{
    Walk_409840 *w = ref_L13_00409840_00(obj);

    if (w == 0)
        return 0;
    if (path != w->path)
        path_set_follower_nodes(obj, path, -1, 0);
    if (g_current_map_index == 0x45) {
        creature_move_along_ground_pal(obj, path + (w->cur * 16 + 0x10));
        if (vec_distance_xy(obj + 0x10, path + (w->cur * 16 + 0x10)) <= 0.5f) {
            if (w->goal == w->cur)
                return 1;
            if (w->goal < w->cur)
                w->cur = w->cur - 1;
            else
                w->cur = w->cur + 1;
        }
    } else {
        creature_move_along_ground_pal(obj, path + (w->goal * 16 + 0x10));
        if (vec_distance_xy(obj + 0x10, path + (w->goal * 16 + 0x10)) <= 0.5f) {
            if (w->goal == w->cur)
                return 1;
            if (w->goal < w->cur)
                w->cur = w->cur - 1;
            else
                w->cur = w->cur + 1;
        }
    }
    return 0;
}


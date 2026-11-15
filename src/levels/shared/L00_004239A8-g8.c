#include "common.h"

/* func_L00_004239A8 needs -G8 for the $gp-relative bias constant. The bias is a read-only
 * tuning value: retail schedules its load across the preceding halfword store, which only an
 * unchanging (const) read allows. */
typedef int TI128 __attribute__((mode(TI)));

extern char g_follow_camera_object[];
extern char D_L00_001BF220_1[];
extern char D_L00_001BF230[];
extern const float D_L00_001B14D0 __attribute__((sda));
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float FastVecDot(void *, void *);
extern int coll_find_nearby_shape_points(void *, float);
extern int coll_test_point(void *, float, void *, void *);
extern void *cam_follow_constrain_distance(char *, void *, int, int);

/* Probes up to three positions from the owner block's blend point, records which probe
   succeeded, classifies the view direction into the +0x38 flag and hands the result on. */
void *cam_follow_probe_collision(char *object)
{
    char *camera_state = *(char **)(object + 0x70);
    char *controller = camera_state + 0x1F0;
    void *transform = camera_state + 0x60;
    char *movement = camera_state + 0x160;
    TI128 probe_point, direction;
    void *hero_state;
    void *target;
    void *result;
    float threshold;
    float dot;
    int found_first = 0;
    int found_second = 0;
    int i = 0;
    char *camera_object = g_follow_camera_object + 0x10;

    FastVecAdd(&probe_point, camera_state + 0xB0, movement);
    *(short *)(controller + 0x38) = 2;
    hero_state = *(void **)(*(char **)g_follow_camera_object + 0x70);
    target = *(void **)(controller + 0x48);
    threshold = D_L00_001B14D0 + *(float *)((char *)hero_state + 0x234) * *(float *)((char *)hero_state + 0x22C) *
              (*(float *)((char *)hero_state + 0x230) - 1.0f);
    while (i < 3) {
        if (coll_find_nearby_shape_points(&probe_point, threshold))
            found_first = 1;
        else if (!coll_test_point(&probe_point, threshold, target, *(void **)(camera_object + 0xC4)))
            break;
        else
            found_second = 1;
        if (*(short *)(controller + 0x38) != 0) {
            FastVecSub(&direction, D_L00_001BF220_1, &probe_point);
            vec_scale_to_length(&direction, &direction, 1.0f);
            dot = FastVecDot(camera_object + 0x30, &direction);
            if (dot > 0.75f)
                *(short *)(controller + 0x38) = 1;
            else if (dot < -0.75f)
                *(short *)(controller + 0x38) = -1;
            else
                *(short *)(controller + 0x38) = 0;
        }
        qcopy(&probe_point, D_L00_001BF230);
        i++;
    }
    result = cam_follow_constrain_distance(object, &probe_point, found_first, found_second);
    FastVecAdd(controller + 0x20, (char *)transform + 0x50, movement);
    if (*(short *)(controller + 0x38) == 2)
        *(short *)(controller + 0x38) = 0;
    return result;
}

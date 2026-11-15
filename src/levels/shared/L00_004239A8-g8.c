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
    char *cameraState = *(char **)(object + 0x70);
    char *controller = cameraState + 0x1F0;
    void *transform = cameraState + 0x60;
    char *movement = cameraState + 0x160;
    TI128 probePoint, direction;
    void *heroState;
    void *target;
    void *result;
    float threshold;
    float dot;
    int foundFirst = 0;
    int foundSecond = 0;
    int i = 0;
    char *cameraObject = g_follow_camera_object + 0x10;

    FastVecAdd(&probePoint, cameraState + 0xB0, movement);
    *(short *)(controller + 0x38) = 2;
    heroState = *(void **)(*(char **)g_follow_camera_object + 0x70);
    target = *(void **)(controller + 0x48);
    threshold = D_L00_001B14D0 + *(float *)((char *)heroState + 0x234) * *(float *)((char *)heroState + 0x22C) *
              (*(float *)((char *)heroState + 0x230) - 1.0f);
    while (i < 3) {
        if (coll_find_nearby_shape_points(&probePoint, threshold))
            foundFirst = 1;
        else if (!coll_test_point(&probePoint, threshold, target, *(void **)(cameraObject + 0xC4)))
            break;
        else
            foundSecond = 1;
        if (*(short *)(controller + 0x38) != 0) {
            FastVecSub(&direction, D_L00_001BF220_1, &probePoint);
            vec_scale_to_length(&direction, &direction, 1.0f);
            dot = FastVecDot(cameraObject + 0x30, &direction);
            if (dot > 0.75f)
                *(short *)(controller + 0x38) = 1;
            else if (dot < -0.75f)
                *(short *)(controller + 0x38) = -1;
            else
                *(short *)(controller + 0x38) = 0;
        }
        qcopy(&probePoint, D_L00_001BF230);
        i++;
    }
    result = cam_follow_constrain_distance(object, &probePoint, foundFirst, foundSecond);
    FastVecAdd(controller + 0x20, (char *)transform + 0x50, movement);
    if (*(short *)(controller + 0x38) == 2)
        *(short *)(controller + 0x38) = 0;
    return result;
}

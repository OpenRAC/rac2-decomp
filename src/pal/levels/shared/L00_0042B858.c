#include "include_asm.h"
#include "names.h"

extern void coll_visit_grid_entries(int);
extern void func_L00_00425490_1(int);
extern void ship_read_steer_and_throttle(int, float *, float *);
extern void cam_vehicle_update_turn(int, float, float);
extern void FollowCameraHideObstructions(int);
extern void cam_follow_move_eye(int);
extern void follow_camera_build_view(int);

/* runs a fixed sequence of seven callees on one object handle, passing the address of two stack floats to the third callee and then their values to the fourth */
void cam_follow_run_frame_pal(int object)
{
    float x;
    float y;

    coll_visit_grid_entries(object);
    func_L00_00425490_1(object);
    ship_read_steer_and_throttle(object, &x, &y);
    cam_vehicle_update_turn(object, x, y);
    FollowCameraHideObstructions(object);
    cam_follow_move_eye(object);
    follow_camera_build_view(object);
}


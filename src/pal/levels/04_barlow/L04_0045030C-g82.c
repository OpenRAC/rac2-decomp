#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern f32 D_L04_001B1870 __attribute__((sda));
extern u8 D_L04_001BFAC0[];
extern TI128 D_L04_001BFB00;
extern f32 mat_fast_helper_a(f32, f32);
extern f32 FastAddRotations(f32, f32);
extern void MobySpringTurn(void *, float *, f32, f32, f32, f32);
extern int FloatToInt(f32);
extern void func_PAL_L04_0033F000(void *, void *);
extern void path_push_point_away(int, void *, void *, f32);
extern void moby_transform_point_and_rotation_by_parent(void *, void *, void *, void *, void *, void *);
extern f32 coll_probe_ground_height_below(void *, int, f32);
extern int moby_get_private_value_2(void *);
extern void mat_build_axis_angle_rotation(void *, void *, f32);
typedef struct {
    u8 pad0[0x140]; int steps; f32 time;
    u8 pad148[0x240-0x148]; f32 target[2];
    u8 pad248[0x2f0-0x248]; int channel;
    u8 pad2f4[0x310-0x2f4]; f32 turn, heading;
    u8 pad318[8]; void *ground; f32 velocity;
} D428Data;
typedef struct {
    u8 pad0[0x10]; f32 position[4]; u8 state;
    u8 pad21[0x68-0x21]; D428Data *data;
    u8 pad6c[0x95-0x6c]; u8 animation;
    u8 pad96[0xf0-0x96]; union { TI128 q; f32 f[4]; } rotation;
} D428Object;

void func_PAL_L04_00452DE8(D428Object *object) {
    union { TI128 q; f32 f[4]; } angles;
    TI128 rotation;
    D428Data *data = object->data;
    f32 heading, floor;
    if (object->state == 4) {
        heading = mat_fast_helper_a(data->target[0] - object->position[0],
                               data->target[1] - object->position[1]);
        heading = FastAddRotations(heading, data->heading);
        MobySpringTurn(object, &data->turn, heading, 0.05f, 0.3f, 0.12566373f);
        data->steps = FloatToInt(D_L04_001B1870 * 1024.0f);
        data->time = D_L04_001B1870;
        func_PAL_L04_0033F000(object, &data->steps);
        if (data->channel != -1)
            path_push_point_away(data->channel, object->position, object->position, D_L04_001B1870);
    } else if (object->state == 5) {
        heading = mat_fast_helper_a(data->target[0] - object->position[0],
                               data->target[1] - object->position[1]);
        heading = FastAddRotations(heading, data->heading);
        MobySpringTurn(object, &data->turn, heading, 0.05f, 0.3f, 0.12566373f);
    }
    if (data->ground) {
        angles.q = 0;
        moby_transform_point_and_rotation_by_parent(object, data->ground, object->position, &object->rotation, object->position, &angles);
        object->rotation.f[2] = angles.f[2];
    }
    if (object->animation != 3) {
        data->velocity += 0.00392f;
        object->position[2] -= data->velocity - 2.0f;
        floor = coll_probe_ground_height_below(object->position, 0, 0.5f);
        object->position[2] -= 2.0f;
        if (object->position[2] < floor) {
            u8 *controller = D_L04_001BFAC0;
            if (*(void **)(controller + 0x18) && moby_get_private_value_2(*(void **)(controller + 0x18))) {
                data->ground = *(void **)(controller + 0x18);
            } else if (data->ground) {
                data->ground = 0;
            }
            object->position[2] = floor;
            data->velocity = 0;
            if (data->ground) {
                rotation = object->rotation.q;
                angles.q = D_L04_001BFB00;
                mat_build_axis_angle_rotation(&angles, &rotation, object->rotation.f[2]);
            }
        }
    }
}

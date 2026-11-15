/* func_L04_0044D428: its own -G8 unit with -frac2-zero-ti-por (the stack clear of
 * the ground angles keeps retail's por + sq). */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
extern f32 D_L04_001B1870 __attribute__((sda));
extern u8 D_L04_001BFAC0[];
extern TI128 D_L04_001BFB00;
extern f32 func_00283248(f32, f32);
extern f32 func_00283B98(f32, f32);
/* RAC1's counterpart MobySpringTurn (func_L00_002592B0, same body: clamp, spring
 * step, add to the moby's heading) returns void; no RAC2 caller uses a result. */
extern void func_002A7CA0(void *, float *, f32, f32, f32, f32);
extern int func_00283CF0(f32);
extern void func_L04_0033D0C0(void *, void *);
extern void func_002C9218(int, void *, void *, f32);
extern void func_002AD0E0(void *, void *, void *, void *, void *, void *);
extern f32 func_002A89A8(void *, int, f32);
extern int func_002AD0B0(void *);
extern void func_L04_00344568(void *, void *, f32);

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

/* Turns the enemy toward its target while it walks and keeps it on the ground each frame, riding moving ground if there is any. */
void func_L04_0044D428(D428Object *object) {
    union { TI128 q; f32 f[4]; } angles;
    TI128 rotation;
    D428Data *data = object->data;
    f32 heading, floor;
    if (object->state == 4) {
        heading = FastMatrixHelperA(data->target[0] - object->position[0],
                               data->target[1] - object->position[1]);
        heading = FastAddRotations(heading, data->heading);
        MobySpringTurn(object, &data->turn, heading, 0.05f, 0.3f, 0.10471977293491364f);
        data->steps = FloatToInt(D_L04_001B1870 * 1024.0f);
        data->time = D_L04_001B1870;
        ProbeAheadOfObject(object, &data->steps);
        if (data->channel != -1)
            PushPointAwayFromPath(data->channel, object->position, object->position, D_L04_001B1870);
    } else if (object->state == 5) {
        heading = FastMatrixHelperA(data->target[0] - object->position[0],
                               data->target[1] - object->position[1]);
        heading = FastAddRotations(heading, data->heading);
        MobySpringTurn(object, &data->turn, heading, 0.05f, 0.3f, 0.10471977293491364f);
    }
    if (data->ground) {
        angles.q = 0;
        TransformPointAndRotationByParent(object, data->ground, object->position, &object->rotation, object->position, &angles);
        object->rotation.f[2] = angles.f[2];
    }
    if (object->animation != 3) {
        data->velocity += 0.0027222223579883575f;
        object->position[2] -= data->velocity - 2.0f;
        floor = ProbeGroundHeightBelow(object->position, 0, 0.5f);
        object->position[2] -= 2.0f;
        if (object->position[2] < floor) {
            u8 *controller = D_L04_001BFAC0;
            if (*(void **)(controller + 0x18) && GetMobyPrivateValue2(*(void **)(controller + 0x18))) {
                data->ground = *(void **)(controller + 0x18);
            } else if (data->ground) {
                data->ground = 0;
            }
            object->position[2] = floor;
            data->velocity = 0;
            if (data->ground) {
                rotation = object->rotation.q;
                angles.q = D_L04_001BFB00;
                BuildAxisAngleRotation(&angles, &rotation, object->rotation.f[2]);
            }
        }
    }
}

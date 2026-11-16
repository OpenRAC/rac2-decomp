#include "include_asm.h"
#include "common.h"
extern char *moby_get_motion_data(unsigned char *);
extern float FastVecLength(void *);
extern void vec_scale_to_length(void *, void *, float);
extern float g_follower_speed_limit __attribute__((sda));

typedef float Vec000[4] __attribute__((aligned(16)));
typedef struct {
    char pad0[0x30];
    float rot[4];   /* 0x30: Euler angles; x is eased and clamped here, y and z follow velocity */
    float smooth_rot[4]; /* 0x40 */
    char pad50[0x40];
    float velocity[4]; /* 0x90 */
    char padA0[0xA0];
    float axis_scale;   /* 0x140 */
} Obj002EE000;

extern int follower_get_state(unsigned char *);
extern float vec_length_xy(void *);
extern float mat_fast_helper_a(float, float);
extern float fast_subtract_rotations(float, float);
extern float FastDiffRots(float, float);
extern void mat_build_rotation_from_angles(void *, void *);
extern void vec_fast_normalize3(void *, void *, void *, float);
extern void quaternion_to_rotation_basis(void *, void *);
extern float g_follower_max_scale __attribute__((sda));
extern char *g_camera_state_ptr NOT_SDA;

/* Tilts an object to lean into its turns, based on how it is moving. */
void UpdateBankedOrientation(unsigned char *owner)
{
    Obj002EE000 *obj = (Obj002EE000 *)moby_get_motion_data(owner);
    Vec000 old;
    Vec000 temp;
    float sign;
    float speed;
    float turn_amount;

    if (!obj)
        return;
    if (follower_get_state(owner) != 8 && follower_get_state(owner) != 9) {
        qcopy(old, obj->rot);
        speed = vec_length_xy(obj->velocity);
        sign = 1.0f;
        obj->rot[1] = -mat_fast_helper_a(speed, obj->velocity[2]);
        obj->rot[2] = mat_fast_helper_a(obj->velocity[0], obj->velocity[1]);
        if (fast_subtract_rotations(obj->rot[2], old[2]) < 0.0f)
            sign = -1.0f;
        turn_amount = FastDiffRots(old[2], obj->rot[2]);
        if (follower_get_state(owner) != 2 && follower_get_state(owner) != 12) {
            obj->rot[0] *= 0.98f;
            obj->rot[0] += (turn_amount * -sign) * (g_follower_max_scale * 1.4137166738510132f) * 8.0f;
            if (obj->rot[0] > 1.4137166738510132f)
                obj->rot[0] = 1.4137166738510132f;
            else if (obj->rot[0] < -1.4137166738510132f)
                obj->rot[0] = -1.4137166738510132f;
            mat_build_rotation_from_angles(temp, obj->rot);
            quaternion_to_rotation_basis(temp, owner + 0xC0);
        } else {
            mat_build_rotation_from_angles(temp, obj->rot);
            vec_fast_normalize3(obj->smooth_rot, obj->smooth_rot, temp, 0.0125f);
            quaternion_to_rotation_basis(obj->smooth_rot, owner + 0xC0);
        }
    } else {
        char *p = g_camera_state_ptr;

        vec_scale_to_length(owner + 0xC0, p + 0x10, obj->axis_scale);
        vec_scale_to_length(owner + 0xE0, p, -1.0f);
        vec_scale_to_length(owner + 0xD0, p + 0x20, -1.0f);
    }
}

/* Measures how fast the object is moving and caps it at the top speed. */
void follower_limit_speed(unsigned char *owner)
{
    char *data = (char *)moby_get_motion_data(owner);
    if (data) {
        char *vector = data + 0x90;
        float length = FastVecLength(vector);
        float limit = g_follower_speed_limit;
        *(float *)(data + 0x124) = length;
        if (limit < length) {
            vec_scale_to_length(vector, vector, limit);
            *(float *)(data + 0x124) = g_follower_speed_limit;
        }
    }
}

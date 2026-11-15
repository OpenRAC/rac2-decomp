#include "common.h"
/* Camera id/state fields are independently observed at the same offsets
 * as the public RAC1 Camera prefix (origin/main 1d8228cc). */
typedef struct {
    unsigned char bytes00[0x70];
    char *state;
    unsigned char bytes74[0x12];
    short id;
} CameraInitPrefix;
extern unsigned char g_hero_state[];


#ifndef RAC2_T_V4_F0FBA48D3
#define RAC2_T_V4_F0FBA48D3
typedef int V4_F0fba48d3 __attribute__((mode(TI)));
#endif

extern void func_00282CF0_2(void *b, void *c, void *d);

extern void FastVecAdd(void *c, void *c2, void *s);

extern void FastVecScale(void *dst, void *src, float k);

extern float func_00282DB0_1(char *local, char *p);

extern void vec_clear_128(void *a);





/* Sets up the follow camera from the hero's position and facing. It starts the camera just behind the hero. */
void cam_follow_init_from_hero(CameraInitPrefix *camera)
{
    char *camera_state;
    char *transform;
    char *near_point;
    char *far_point;
    char *movement;
    char *hero;
    char *work_ptr;
    char *hero_position;
    V4_F0fba48d3 *quad_dest;
    char back_direction[16];
    char offset_buf[16];

    if (camera->id != 0)
        return;

    hero = (char *)g_hero_state + 0x2C0;
    work_ptr = camera->state;
    movement = work_ptr + 0x160;
    transform = work_ptr + 0x60;
    camera_state = work_ptr;
    work_ptr = back_direction;

    FastVecScale(work_ptr, hero, -1.0f);
    /* The hero's position, 0x240 below the facing direction the call above uses. */
    hero_position = hero - 0x240;
    *(V4_F0fba48d3 *)transform = *(V4_F0fba48d3 *)hero_position;
    quad_dest = (V4_F0fba48d3 *)(camera_state + 0xC0);
    *quad_dest = *(V4_F0fba48d3 *)transform;
    near_point = camera_state + 0xB0;
    far_point = camera_state + 0xF0;
    FastVecScale(camera_state + 0x70, back_direction, func_00282DB0_1(transform, back_direction));
    vec_clear_128(camera_state + 0xD0);
    vec_clear_128(camera_state + 0xE0);
    vec_clear_128(camera_state + 0x100);
    FastVecScale(offset_buf, back_direction, *(float *)(movement + 0x30));
    FastVecAdd(near_point, offset_buf, transform);
    FastVecScale(offset_buf, back_direction, *(float *)(transform + 0xB0));
    FastVecAdd(far_point, offset_buf, transform);
    quad_dest = (V4_F0fba48d3 *)(camera_state + 0xA0);
    *quad_dest = *(V4_F0fba48d3 *)far_point;
    func_00282CF0_2(movement, (char *)camera + 0x30, near_point);
    quad_dest = (V4_F0fba48d3 *)(camera_state + 0x170);
    *quad_dest = *(V4_F0fba48d3 *)movement;
    *(V4_F0fba48d3 *)camera_state = *(V4_F0fba48d3 *)((char *)camera + 0x30);
    FastVecAdd(camera_state + 0x210, near_point, movement);
    *(int *)(camera_state + 0x240) = 0;
}
